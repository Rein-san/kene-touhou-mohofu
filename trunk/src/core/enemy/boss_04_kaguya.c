
#include "bullet_object.h"

/*---------------------------------------------------------
	輝夜
	かぐや
	-------------------------------------------------------
	ボスタイマー未対応
---------------------------------------------------------*/

typedef struct _boss03_data
{
	BOSS_BASE boss_base;
//	int state;
	int health_flag;
	int identity;		// 固有番号
//	int level;

} BOSS03_DATA;

// FLG_FIRE1 弾フラグ。真ん中の宝物が壊れていて、かつ指定位置に付いた時。onになる。
//#define FLG_FIRE1 0x01/*左上の藍い娘(宝物)が指定位置に付いたか*/
//#define FLG_FIRE2 0x02/*右上の碧の娘(宝物)が指定位置に付いたか*/
//
#define FLG_DOLL0 0x04/*輝夜本人*/
#define FLG_DOLL1 0x08/*左上の藍い娘(宝物)*/
#define FLG_DOLL2 0x10/*右上の碧の娘(宝物)*/
#define FLG_DOLL3 0x20/*左前の宝物*/
#define FLG_DOLL4 0x40/*真中の紅い娘(宝物)*/
#define FLG_DOLL5 0x80/*右前の宝物*/

#define FLG_ALL_DOLL   (FLG_DOLL1|FLG_DOLL2|FLG_DOLL3|FLG_DOLL4|FLG_DOLL5)/*輝夜以外*/
#define FLG_ALL_CAST   (FLG_DOLL0|FLG_ALL_DOLL)/*全員*/

/*---------------------------------------------------------

---------------------------------------------------------*/

static unsigned int b01flags/*=0*/;
static int b01level;

static int b01state;
static int bb_angle512;

static SPRITE *sb03[6];

/*---------------------------------------------------------
人員の配置メモ
[1][0][2]
[3][4][5]
---------------------------------------------------------*/

/* boss wurde von player-weapon ber??rt */
static void callback_enemy_boss03_hitbyweapon_dummy(SPRITE *s, SPRITE *t/*, int angle*/)
{	/* 完全に姿を現すまで攻撃は、すべて無効とする。 */
}
/*	s = ボス本体 boss sprite
	t = プレイヤーの弾 player's weapon */
static void callback_enemy_boss03_hitbyweapon(SPRITE *s, SPRITE *t/*, int angle*/)
{
	explosion_add_type(t->x256,t->y256,/*0,*/EXPLOSION_MINI00);/*先に実行した方が速い*/
	//parsys_add(NULL,100,0,t->x,t->y,30,0,0,50,PIXELATE,NULL);
//
	WEAPON_BASE *w		= (WEAPON_BASE *)t->data;
	BOSS03_DATA *data	= (BOSS03_DATA *)s->data;
//
			int i_id;
			i_id = data->identity;
//
	{	int b_health_alter_low1024;
		b_health_alter_low1024 = (data->boss_base.health & (1024-1));/* 直前の下位1024 */
		data->boss_base.health -= w->strength;/* ボス攻撃して体力減らす */
		if (b_health_alter_low1024 < (data->boss_base.health & (1024-1)))/* 形態変更したら */
		{
			if (0==i_id)	// 輝夜かどうかチェック
			{
				item_create_for_boss(s, ITEM_CREATE_MODE_02);
			}
		}
	}
//
	if (data->boss_base.health <= 15)
	{
		if (0==data->health_flag)
		{
			data->health_flag = 1;
			explosion_add_type(s->x256+((s->w128)),s->y256+((s->h128)),/*0,*/EXPLOSION_FIRE08);
		}
		if (data->boss_base.health <= 0)/* 該当者の体力切れなら */
		{
			data->boss_base.health = 0;
			//
			explosion_add_type(s->x256+((s->w128)),s->y256+((s->h128)),/*0,*/EXPLOSION_ZAKO04/*EXPLOSION_FIRE08*/);
			s->flags			&= (~(SP_FLAG_VISIBLE));
			item_create_for_boss(s, ITEM_CREATE_MODE_02);
			player_add_score(data->boss_base.score);
			{
				b01flags			|= (FLG_DOLL0<<i_id);/* 倒した人をONにする */
				if (0==i_id)	// 輝夜かどうかチェック
				{
					b01flags |= FLG_ALL_CAST;	// 輝夜を倒すと皆破壊される。
				}
			}
		}
	}
//
	if (FLG_ALL_CAST==(b01flags&FLG_ALL_CAST))/*全員倒した？*/		/* boss komplett zerst??t */
	{
		item_create_for_boss(s, ITEM_CREATE_MODE_01);
//
		player_set_destoroy_boss();
		int i;
		for (i=0; i<6; i++)
		{
		//	explosion_add_type(sb03[i]->x256+((sb03[i]->w)<<7),sb03[i]->y256+((sb03[i]->h)<<7),/*(ra_nd()&(16-1)/*%20*/),*/EXPLOSION_FIRE08);
			explosion_add_circle(sb03[i], 1);	/* player_set_destoroy_boss(); B02_BOSS_DESTROY が必要 */
			sb03[i]->type = SP_DELETE;
		}
		/* コールバック登録 */
		((PLAYER_DATA *)player->data)->callback_boss_hitbyweapon = callback_enemy_boss03_hitbyweapon_dummy; /* ダミーコールバック登録 */
	}
}

/*---------------------------------------------------------

---------------------------------------------------------*/
#if 0
static void enemy_boss03_setpos(int xxx, int yyy)
{
int x256;
int y256;
	x256 = (xxx<<8);
	y256 = (yyy<<8);
//
	sb03[1]->x256 = x256;
	sb03[0]->x256 = x256 + ((sb03[1]->w128+sb03[1]->w128));
	sb03[2]->x256 = x256 + ((sb03[1]->w128+sb03[1]->w128)) + ((sb03[0]->w128+sb03[0]->w128));
//
	sb03[1]->y256 = y256;
	sb03[0]->y256 = y256;
	sb03[2]->y256 = y256;
//
	sb03[3]->x256 = x256;
	sb03[4]->x256 = x256 + ((sb03[3]->w128+sb03[3]->w128));
	sb03[5]->x256 = x256 + ((sb03[3]->w128+sb03[3]->w128)) + ((sb03[4]->w128+sb03[4]->w128));
//
	sb03[3]->y256 = y256 + ((sb03[1]->h128+sb03[1]->h128));
	sb03[4]->y256 = y256 + ((sb03[0]->h128+sb03[0]->h128));
	sb03[5]->y256 = y256 + ((sb03[2]->h128+sb03[2]->h128));
}
//#else
static void enemy_boss03_setpos(int xxx, int yyy)
{
int x256;
int y256;
	x256 = (xxx<<8);
	y256 = (yyy<<8);
//
	sb03[1]->x256 = x256;
	sb03[0]->x256 = x256 + (t256(34));
	sb03[2]->x256 = x256 + (t256(34 + 54));
//
	sb03[1]->y256 = y256;
	sb03[0]->y256 = y256;
	sb03[2]->y256 = y256;
//
	sb03[3]->x256 = x256;
	sb03[4]->x256 = x256 + (t256(34));
	sb03[5]->x256 = x256 + (t256(34 + 54));
//
	sb03[3]->y256 = y256 + (t256(45));
	sb03[4]->y256 = y256 + (t256(45));
	sb03[5]->y256 = y256 + (t256(45));
}
#endif
static void enemy_boss03_setpos(int xxx, int yyy)
{
int x256;
int y256;
	x256 = (xxx<<8);
	y256 = (yyy<<8);
//
	sb03[0]->x256 = x256 + (t256(34));
	sb03[0]->y256 = y256;
//
	bb_angle512++;
int aa_angle512;
	aa_angle512 = bb_angle512;
int jj;
	for (jj=1; jj<6; jj++)
	{
		aa_angle512 += 102;/* 102.4== 512/5 */
		mask512(aa_angle512);
		sb03[jj]->x256 = sb03[0]->x256 + ((cos512((aa_angle512))*45));
		sb03[jj]->y256 = sb03[0]->y256 + ((sin512((aa_angle512))*45));
	}
}
/*---------------------------------------------------------

---------------------------------------------------------*/

/*int where / 0: left, 1: right, 2: bombenhagel */
//	switch (where)//	case 2:
static void enemy_boss01_nway_fire(BOSS03_DATA *data)
{
	static int hari=0;
	hari--;
	hari &= 32;
	play_voice_auto_track(VOICE14_YOKAI1_E_SHOT01);
//
	int hari_no_iro;
	hari_no_iro = BULLET_HARI32_00_AOI;
	/* 4面の場合---- */
	if (1==b01level/*0==data->level*/)
	{
		unsigned short iro_tbl[8] =
		{
/**/		BULLET_HARI32_01_AKA,
/*1*/		BULLET_HARI32_01_AKA,
/*2*/		BULLET_HARI32_03_DAIDAI,
/*3*/		BULLET_HARI32_02_KIIRO,
/*4*/		BULLET_HARI32_00_AOI,
/*5*/		BULLET_HARI32_00_AOI,
/**/		BULLET_HARI32_00_AOI,
/**/		BULLET_HARI32_00_AOI,
		};
		hari_no_iro = iro_tbl[(((data->boss_base.health)&(0xfc00) )>>10)];
	}
//
	int angle512;
	for (angle512=deg_360_to_512(0); angle512</*=*/deg_360_to_512(360/*180*/);
	//	angle512+=/*22*/21+hari-difficulty/*deg_360_to_512(20)*/		/* 23本(360) ← 8本(180) */
		angle512+=(/*22*/18+hari-difficulty-difficulty/*deg_360_to_512(20)*/)		/* 最低 == 10 == 48本(360)	*/
		)
	{
		bullet_create_offset_dan_type(sb03[4],
			(int)(/*6*/ (0x100)+(ra_nd()&0x2ff)/*t256(2.5)*/),
			angle512,
			/*offsx*/t256(0)/*(src->w/2)*/,
			/*offsy*/t256(0)/*(src->h/2)*/,
			hari_no_iro
		);
	}
}

/*---------------------------------------------------------

---------------------------------------------------------*/

static void enemy_boss03_LR_dole_fire(void)
{
//	case 0:/*LEFT*/
	if (0==(b01flags&FLG_DOLL1)/*sb03[3]->flags&SP_FLAG_VISIBLE*/)
	{	bullet_create_aka_maru_jikinerai(sb03[1], t256(difficulty+1)/*5*/);}
//	case 1:/*RIGHT*/
	if (0==(b01flags&FLG_DOLL2)/*sb03[5]->flags&SP_FLAG_VISIBLE*/)
	{	bullet_create_aka_maru_jikinerai(sb03[2], t256(difficulty+1)/*5*/);}
}

/*---------------------------------------------------------

---------------------------------------------------------*/

static void center_shot(BOSS03_DATA *data)
{
	/* 4面の場合---- */
	if (1==b01level/*0==data->level*/)
	{
		int kakudo;
		kakudo = (127-16);
		kakudo += ((ra_nd())&(32-1));
		switch ((data->boss_base.health)&(0xfc00) )
		{
		case (3<<10):/*not_break;*/
			bullet_create_n_way_dan_sa_type(sb03[0], t256(0.6), kakudo, (int)(512/24), BULLET_UROKO14_03_MIDORI,	24);
			bullet_create_n_way_dan_sa_type(sb03[0], t256(1.4), kakudo, (int)(512/24), BULLET_UROKO14_05_KIIRO, 	24);
		case (2<<10):/*not_break;*/
		case (4<<10):/*not_break;*/
			bullet_create_n_way_dan_sa_type(sb03[0], t256(1.0), kakudo, (int)(512/24), BULLET_UROKO14_00_AOI,		24);
			bullet_create_n_way_dan_sa_type(sb03[0], t256(1.8), kakudo, (int)(512/24), BULLET_UROKO14_04_MIZUIRO,	24);
		case (5<<10):/*not_break;*/
		case (1<<10):/*not_break;*/
			bullet_create_n_way_dan_sa_type(sb03[0], t256(1.2), kakudo, (int)(512/24), BULLET_UROKO14_02_YUKARI,	24);
			bullet_create_n_way_dan_sa_type(sb03[0], t256(0.8), kakudo, (int)(512/24), BULLET_UROKO14_01_AKA,		24);
			bullet_create_n_way_dan_sa_type(sb03[0], t256(2.0), kakudo, (int)(512/24), BULLET_UROKO14_01_AKA,		24);
			break;
		}
	}
}

/*---------------------------------------------------------

---------------------------------------------------------*/

// [***090114		いろいろと追加します。
//3面と4面の差別化。
//4面には新しく追加した弾軌道を組み込む。
static void enemy_boss03_move(SPRITE *c)
{
	BOSS03_DATA *data = (BOSS03_DATA *)c->data;
	static int xxx;
	static int yyy;
	static int www;
	static int firewait3;
	static int bomb_n;
	int i;
	switch (/*data->state*/b01state)
	{
	case 0:
	//	firewait1	=45;
	//	firewait2	=4;
		firewait3	=0;
		bomb_n		=0;
			//	xxx 	= GAME_WIDTH/2-((sb03[1]->w128+sb03[0]->w128+sb03[2]->w128)>>8);	//ウィンドウ幅の変更
				xxx 	= GAME_WIDTH/2-((34+54+34)/2);	//ウィンドウ幅の変更
				yyy 	= -100; 			enemy_boss03_setpos(xxx,yyy);					{	/*data->state*/b01state=1;						}	break;
	case 1: 	yyy+=1; 					enemy_boss03_setpos(xxx,yyy);	if (yyy>= 0)	{	/*data->state*/b01state=2; www=0;
			//	((PLAYER_DATA *)player->data)->bo ssmode=B05_BE FORE_LOAD;
				((PLAYER_DATA *)player->data)->state_flag |= STATE_FLAG_10_IS_LOAD_SCRIPT;	}	break;/*下*/
	case 2:
			//	if (((PLAYER_DATA *)player->data)->bo ssmode==B00_NONE/*B01_BA TTLE*/)
			if ( ((((PLAYER_DATA *)player->data)->state_flag) & STATE_FLAG_05_IS_BOSS) )	{
								www+=1; 									if (www>=40)	{	/*data->state*/b01state=3;					}	}	break;
	case 3: 	yyy+=1; 					enemy_boss03_setpos(xxx,yyy);	if (yyy>=30)	{	/*data->state*/b01state=4; www=0;
			/* プレイヤー弾受け付け、コールバックを登録 */
			((PLAYER_DATA *)player->data)->callback_boss_hitbyweapon=callback_enemy_boss03_hitbyweapon; 										}	break;/*下*/
/*完全に姿を現す*/
	case 4: 					www+=1; 									if (www>=30)	{	/*data->state*/b01state=5; www=0;				}	break;
	case 5: 	yyy+=1; xxx-=2; www+=1; 	enemy_boss03_setpos(xxx,yyy);	if (www>=60)	{	/*data->state*/b01state=6;						}	break;/*左下*/
	case 6: 	yyy-=1; xxx+=2; www-=1; 	enemy_boss03_setpos(xxx,yyy);	if (www<= 0)	{	/*data->state*/b01state=7; center_shot(data);	}	break;/*右上*/
	case 7: 	yyy+=1; xxx+=2; www+=1; 	enemy_boss03_setpos(xxx,yyy);	if (www>=60)	{	/*data->state*/b01state=8;						}	break;/*右下*/
	case 8: 	yyy-=1; xxx-=2; www-=1; 	enemy_boss03_setpos(xxx,yyy);	if (www<= 0)	{	/*data->state*/b01state=4; center_shot(data);	}	break;/*左上*/
	}
	if (/*((BOSS03_DATA *)sb03[0]->data)*/ /*data->state*/b01state > 2)
	{
	static int firewait1=45;
		firewait1-=1;
		if (firewait1<=0)
		{
			firewait1=45;
			static unsigned int firewait2=0;
			firewait2--;
			firewait2 &= (4-1);
			if (0==firewait2)
			{
				enemy_boss01_nway_fire(data);/*enemy_boss03_fire(2);*/
			}
			else
			{
				/* 3面の場合左右が撃つ */
				if (1!=b01level/*0==data->level*/)
				{
					enemy_boss03_LR_dole_fire();/*enemy_boss03_fire(0);enemy_boss03_fire(1);*/
				}
			}
		}
	}
	/* 4面の場合跳ねる珠 */
	if (1==b01level/*0==data->level*/)
	{
		if (data->boss_base.health <= 1000+1024)
		//switch ( (data->boss_base.health)&0xfc00 )
		{
		//case (0<<10):
			{	firewait3--;}
			if (firewait3 < 0)
			{
				if (data->boss_base.health > 200+1024)
				{	firewait3 = ((data->boss_base.health)>>2);}
				else
				{	firewait3 = 50;}
			//
				if (bomb_n < 32)
				{	bomb_n++;}
				for (i=0; i<=(int)(bomb_n/3); i++)
				{
					bullet_create_hazumi_dan(c,
						t256(0.05)+(difficulty<<6), 		/* speed256 t256(5.0) */
						(/*(M_PI*2)*/512*3*i/(bomb_n+1))	/* angle512 */
																/*+ra d2deg512(1)*/, /*←多分括弧書かなかったミス*/
						(t256(0.07)),						/* delta256 */	/*17.92==t256(0.07)*/
						difficulty/*2*/ 					/* bound_counts */
					);		/* [***090116		微調整 */
				}
			}
		//	else
		//	{	firewait3--;}
		//	break;
		}
	}
//	あとでコールバックにして共通化する。
	{
		data->boss_base.boss_timer -= 1/*fps_fa ctor*/;
		#if 1/*時間切れ(色々問題あるのでとりあえず無効)*/
		if ((data->boss_base.boss_timer < 1))
		{
			data->boss_base.boss_timer = (60*64);
		//	if ((data->state1 < SAKUYA_05_KEITAI/*4*/))
		//	{
		//		//レミリア戦の開始イベントが見れなくなっちゃうのでここは無効
		//		#if (0==USE_REMILIA)
		//		/* vs REMILIA */
		//		if (2==select_player)
		//		{data->boss_base.health=0/*1*/;}
		//		else
		//		#endif
		//		{data->boss_base.health 	= ((/*4*/SAKUYA_05_KEITAI*1024)-1)-(data->state1<<10/**1024*/);}
		//		sakuya_put_items(/*c,*/s);
		//	}
		}
		#endif
	}
//
}

/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/

void add_boss_kaguya(STAGE_DATA *l)/*int lv*/
{
	int lv;
	lv	= l->user_y;
//
	b01level	= lv+1;
	b01flags	= 0;
	bb_angle512 = 0;

//	sb03[1] = spr ite_add_file 0("boss/boss04_0.png"/*"boss03-lo.png"*/, 2, PRIORITY_03_ENEMY, 0);
//	sb03[0] = spr ite_add_file 0("boss/boss04_1.png"/*"boss03-mo.png"*/, 2, PRIORITY_03_ENEMY, 0);
//	sb03[2] = spr ite_add_file 0("boss/boss04_2.png"/*"boss03-ro.png"*/, 2, PRIORITY_03_ENEMY, 0);
//	sb03[3] = spr ite_add_file 0("boss/boss04_3.png"/*"boss03-lu.png"*/, 2, PRIORITY_03_ENEMY, 0);
//	sb03[4] = spr ite_add_file 0("boss/boss04_4.png"/*"boss03-mu.png"*/, 2, PRIORITY_03_ENEMY, 0);
//	sb03[5] = spr ite_add_file 0("boss/boss04_5.png"/*"boss03-ru.png"*/, 2, PRIORITY_03_ENEMY, 0);

//	sb03[0] = sprite_add_res(BASE_BOSS_KAGUYA_1_PNG);/* w54 h45 */
//	sb03[1] = sprite_add_res(BASE_BOSS_KAGUYA_0_PNG);/* w34 h45  */
//	sb03[2] = sprite_add_res(BASE_BOSS_KAGUYA_2_PNG);/* w34 h45  */
//	sb03[3] = sprite_add_res(BASE_BOSS_KAGUYA_3_PNG);/* w34 h45  */
//	sb03[4] = sprite_add_res(BASE_BOSS_KAGUYA_4_PNG);/* w54 h45  */
//	sb03[5] = sprite_add_res(BASE_BOSS_KAGUYA_5_PNG);/* w34 h45  */

	/*data->state*/b01state=0;
	int i;
	for (i=0; i<6; i++)
	{
		sb03[i] = sprite_add_res(BASE_BOSS_KAGUYA_PNG);
		sb03[i]->flags			|= (SP_FLAG_VISIBLE|SP_FLAG_COLISION_CHECK);
		sb03[i]->anim_speed 	= 0;
		sb03[i]->anim_frame 	= i/*0*/;
		sb03[i]->type			= SP_BOSS/*SP_BOSS03*/;
		BOSS03_DATA *data;
		data					= mmalloc(sizeof(BOSS03_DATA));
		sb03[i]->data			= data;
		data->identity			= i;		// 固有番号
		data->health_flag		= 0;
//
		if (0==lv)		// [***090114		追加
		{
			if (0==i)/* 輝夜本人 */
			{
				data->boss_base.health		= (difficulty<<10/*[x1024]*/)+2047+1024;
			//	data->boss_base.score		= score(3000)+score(2000)*difficulty;
				data->boss_base.score		= adjust_score_by_difficulty(score(2000000));	/* 200万 (計400万==(200万)+(5x40万)) */
			}
			else/* 小物類 */
			{
				data->boss_base.health		= (difficulty<<8/*[x256]*/)+ 200+1024;
			//	data->boss_base.score		= score(600)*(difficulty+1);
				data->boss_base.score		= adjust_score_by_difficulty(score( 400000));	/* 40万 */
			}
		}
		else/* 全部一緒 */
		{
			data->boss_base.health		= (difficulty<<6/*[x64]*/)+ 200+1024;
		//	data->boss_base.score		= score(500)*(difficulty+1);
			data->boss_base.score		= adjust_score_by_difficulty(score( 500000));	/* 50万 (計300万==6x50万) */
		}
		if (0==i)/* 輝夜本人 */
		{
			sb03[i]->callback_mover = enemy_boss03_move;
		}
		data->boss_base.boss_timer		= 60*64;	/*	[] */
	}
	//
	((PLAYER_DATA *)player->data)->boss=sb03[0];
	/* コールバック登録 */
	((PLAYER_DATA *)player->data)->callback_boss_hitbyweapon=callback_enemy_boss03_hitbyweapon_dummy;	/* ダミーコールバック登録 */
}
//	((PLAYER_DATA *)player->data)->bo ssmode=B00_NONE/*B01_BA TTLE*/;

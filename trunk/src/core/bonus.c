
/*---------------------------------------------------------
	アイテム関連
---------------------------------------------------------*/

#include "support.h"
#include "bonus.h"


/*---------------------------------------------------------
	アイテムの移動
---------------------------------------------------------*/

/* 個々のアイテムのステータスデーター */
typedef struct
{
	#if 1
	int strength;/*union WEAPON_BASE*/		/*なんかアイテムに殺されるので追加？？？*/
	#endif
	/*dou ble*/int y_sum256;	/* アイテム投げ出し用 y軸 積算値(y軸、上方がマイナス) */
	/*dou ble*/int angle512;
	int flags00;				// 収集フラグ	// [***090116		変更
//	自動収集
	int flag_first; 			/* firstフラグ */
	/*dou ble*/int x_sa256; 	/* 差分 x */
	/*dou ble*/int y_sa256; 	/* 差分 y */
} ITEM_DATA;
extern int effect_sound_hosi;
static void move_items(SPRITE *src)
{
	ITEM_DATA *data = (ITEM_DATA *)src->data;
	/* 自動収集モードのどれかが作動してたら、 */
	if (0 != (
		(((PLAYER_DATA *)player->data)->state_flag) &
		(STATE_FLAG_01_PLAYER_UP_AUTO_GET_ITEM |		/* MAX時の上回収 */
		 STATE_FLAG_02_BOMB_AUTO_GET_ITEM | 			/* ボム発動中のみ回収 */
		 STATE_FLAG_03_SCORE_AUTO_GET_ITEM				/* ボス撃破時の一時回収 */
		) ))
	{
		data->flags00 |= ITEM_MOVE_FLAG_01_COLLECT/*1*/;	/* そのアイテムは自動収集にする */
	}
	/* 自動収集でなければ、単純に放物線を描いて落ちる */
	if (0 == ((data->flags00)&ITEM_MOVE_FLAG_01_COLLECT))
	{
		if (data->y_sum256 < t256(3) )			// [***090123.0220	変更5=>4=>3
		{
			data->y_sum256 += data->angle512;		/* x1.5 */
		}
		src->y256 += (/*t256_to_dou ble*/(data->y_sum256))/**fps_fa ctor*/;
		if (src->y256 > GAME_HEIGHT*256)
		{
			((PLAYER_DATA *)player->data)->chain_point = 0;
			src->type = SP_DELETE;				/* 画面外に出たらおしまい */
		}
	}
	else	/* 自動収集ならば、自分に集まる */
	{
		data->y_sum256--;
		if (1 > data->y_sum256)
		{
			data->y_sum256 = 0;
		}
		if (0 == data->flag_first)
		{
			data->flag_first = 1;
			data->y_sum256 = t256(1.0); 	/*5*0.5*/
		}
		data->x_sa256 = (src->x256 - player->x256);
		data->y_sa256 = (src->y256 - player->y256);
		/*自分に集まる*/
		int aaa_x256;
		int aaa_y256;
		aaa_x256 = ((data->x_sa256 * data->y_sum256)>>8);	/**fps_fa ctor*/
		aaa_y256 = ((data->y_sa256 * data->y_sum256)>>8);	/**fps_fa ctor*/
		if ( (SP_ITEM_05_HOSI) == (src->type))	/* 星点のみ特別処理 */
		{
			if (
				//	(/*10*/64/*16*/ > data->y_sum256) ||
				(
					(t256(8) > abs(aaa_x256)) &&
					(t256(8) > abs(aaa_y256))
				)
			)
			{
				src->type = SP_DELETE;/* 星点のみ特別処理 */				/* おしまい */
				/*effect_sound_number=*/ effect_sound_hosi=1;/*play_voice_auto_track(VOICE05_BONUS);*/
			}
		}
		src->x256 = player->x256 + (aaa_x256);	/**fps_fa ctor*/
		src->y256 = player->y256 + (aaa_y256);	/**fps_fa ctor*/
	}
}

/*---------------------------------------------------------
	アイテム出現させる子関数
---------------------------------------------------------*/

static SPRITE *item_mono_create(SPRITE *src/*int x, int y*/, int sel_type)
{
//	アイテムの種類を選ぶ
	SPRITE *s;
//	s			= spr ite_add_file 0("bonus_items.png", 8, PRIORITY_04_ITEM, 0);	s->anim_speed=0;
	s			= sprite_add_res(BASE_BONUS_ITEMS_PNG);
	sel_type &= 0x07;
	s->anim_frame = ((/*SP_ITEM_FIRE_POWER-*/sel_type)/*&0x07*/);
//	出現位置を決める
	#define OFFSET_X64		(32*256)/* 64はずらし分 2のn乗の必要有り */
	#define ITEM_WIDTH16	(16*256)/* 16はアイテム幅 */
	#define ITEM_X_LIMIT	(GAME_WIDTH*256+OFFSET_X64-ITEM_WIDTH16)
	int x256;
	x256 = src->x256;
	x256 += ((ra_nd()&((OFFSET_X64+OFFSET_X64)-1)));
	if (x256 < OFFSET_X64)
	{
		x256 = OFFSET_X64;
	}
	else
	if (x256 > (ITEM_X_LIMIT))
	{
		x256 = (ITEM_X_LIMIT);
	}
//	登録する
	s->x256 			= (x256)-(OFFSET_X64);
	s->y256 			= src->y256;
//	sel_type &= 0x07;
	sel_type |= SP_ITEM_00_P001;
	s->type 			= sel_type;
	s->callback_mover	= move_items;
	if ( SP_ITEM_05_HOSI == sel_type )	/* 星点のみ特別処理 */
	{
		/* 紅は、こうらしい */
		if ( USER_BOMOUT_WAIT > ((PLAYER_DATA *)player->data)->bomber_time )
		{	/* ボム中(設定無敵時間中)は100pts.(稼げない) */
			bonus_info_score_nodel(s, SCORE_100);/*自動消去へ仕様変更s->type=SP_DELETE;*/
		}
		else/*星点*/
		{	/* ボム後の実質無敵期間中はこちら(稼げる) */
			/* ((graze/3)*10)+(500) pts */
			bonus_info_any_score_nodel(s, (score(500)+(((((PLAYER_DATA *)player->data)->graze_point*86)>>8)/*(pd->graze_point/3)*/)) );/*自動消去へ仕様変更c->type=SP_DELETE;*/
		}
		s->flags			|= (SP_FLAG_VISIBLE|SP_FLAG_TIME_OVER);/*当たり判定なし*/
	}
	else
	{
		s->flags			|= (SP_FLAG_VISIBLE|SP_FLAG_COLISION_CHECK|SP_FLAG_TIME_OVER);
	}
	return (s);
	#undef OFFSET_X64
	#undef ITEM_WIDTH16
	#undef ITEM_X_LIMIT
}

/*---------------------------------------------------------
	アイテムを登録して出現させる
---------------------------------------------------------*/

/* [***090125	追加: up_flags の ITEM_MOVE_FLAG_01_COLLECT ビットがオンでプレイヤーに集まります。 */
void item_create(SPRITE *src/*int x, int y*/, int item_type, int num_of_creates, int up_flags)
{
	int i;
	for (i=0; i<num_of_creates; i++)
	{
		SPRITE *s;
		s			= item_mono_create(src, item_type);
		if (NULL==s) return;
//
		ITEM_DATA *data;
		data				= mmalloc(sizeof(ITEM_DATA));
		s->data 			= data;
		data->strength		= 0;		/*なんかアイテムに殺されるので追加？？？*/
		/* 画面下方に居る程、投げ出し速度を速くする */
	//	data->y_sum256		= t256(-5*0.5); 	//ちょっと変更
	//	data->y_sum256		= t256(-2*0.5); 	/* アイテム投げ出し初期値(y軸、上方がマイナス) */
	//	data->y_sum256		= -(/*256*/((int)(src->y))<<1)-(ra_nd()&0xff);	/* アイテム投げ出し初期値(y軸、上方がマイナス) */
		data->y_sum256		= -(/*256*/((src->y256)>>7))-(ra_nd()&0xff);	/* アイテム投げ出し初期値(y軸、上方がマイナス) */
		data->angle512		= 6;	/* 6.51898646904403967309077986986488 ra d2deg512(0.08);*/
		data->flags00		= (up_flags&ITEM_MOVE_FLAG_01_COLLECT);
		data->flag_first	= 0;
	}
}

/*---------------------------------------------------------
	ボス用アイテム作成
---------------------------------------------------------*/
//	#define ITEM_CREATE_MODE_01 	(12*0)
//	#define ITEM_CREATE_MODE_02 	(12*1)
void item_create_for_boss(SPRITE *src, int item_create_mode)
{
	#define ITEM_01 	(4*0)
	#define ITEM_02 	(4*1)
	#define ITEM_03 	(4*2)
	#define ITEM_MAX	(4*3)
	const signed short item_tbl[ITEM_MAX*2] =
	{	/* easy, normal, hard, lunatic */
	/*mode 0: 撃破後 */
		SP_ITEM_00_P001,	SP_ITEM_02_BOMB,	SP_ITEM_01_P008,	SP_ITEM_06_TENSU,
		SP_ITEM_04_P128,	SP_ITEM_01_P008,	SP_ITEM_02_BOMB,	SP_ITEM_01_P008,
		SP_ITEM_03_1UP, 	SP_ITEM_00_P001,	SP_ITEM_02_BOMB,	SP_ITEM_02_BOMB,
	/*mode 1: 撃破中 */
		SP_ITEM_01_P008,	SP_ITEM_01_P008,	SP_ITEM_01_P008,	SP_ITEM_06_TENSU,
		SP_ITEM_00_P001,	SP_ITEM_00_P001,	SP_ITEM_00_P001,	SP_ITEM_01_P008,
		SP_ITEM_02_BOMB,	SP_ITEM_00_P001,	SP_ITEM_00_P001,	SP_ITEM_00_P001,
	};
	item_create(src, item_tbl[		   difficulty+item_create_mode]/*SP_ITEM_01_P008 */, player_now_stage/*5*/, ITEM_MOVE_FLAG_06_RAND_XY);
	item_create(src, item_tbl[ ITEM_02+difficulty+item_create_mode]/*SP_ITEM_04_P128 */, 1, ITEM_MOVE_FLAG_06_RAND_XY);
	item_create(src, item_tbl[ ITEM_03+difficulty+item_create_mode]/*SP_ITEM_03_1UP  */, 1, ITEM_MOVE_FLAG_06_RAND_XY);
	item_create(src, SP_ITEM_05_HOSI, 16/*7*/, (ITEM_MOVE_FLAG_01_COLLECT|ITEM_MOVE_FLAG_06_RAND_XY) );/*星点を出す*/
}
//	item_create(sb03[i], SP_ITEM_05_HOSI, 16/*7*/, (ITEM_MOVE_FLAG_01_COLLECT|ITEM_MOVE_FLAG_06_RAND_XY) );/*星点を出す*/
//	item_create(sb01[i], SP_ITEM_05_HOSI, 16/*7*/, (ITEM_MOVE_FLAG_01_COLLECT|ITEM_MOVE_FLAG_06_RAND_XY) );/*星点を出す*/
//
//	item_create(s, SP_ITEM_05_HOSI, 16/*7*/, (ITEM_MOVE_FLAG_01_COLLECT|ITEM_MOVE_FLAG_06_RAND_XY) );/*星点を出す*/
//	item_create(s, SP_ITEM_00_P001, 5, ITEM_MOVE_FLAG_06_RAND_XY);/*3*/
//	item_create(s, SP_ITEM_01_P008, 1, ITEM_MOVE_FLAG_06_RAND_XY);
//
//	item_create(s, SP_ITEM_05_HOSI, 5, ITEM_MOVE_FLAG_01_COLLECT);/*星点を出す*/
//	item_create(s, SP_ITEM_00_P001, 5, ITEM_MOVE_FLAG_06_RAND_XY);
//	item_create(s, SP_ITEM_01_P008, 1, ITEM_MOVE_FLAG_06_RAND_XY);
//
//	/* むしろ難しいのでFと残機出すべき */
//	item_create(s, SP_ITEM_01_P008, 	5, ITEM_MOVE_FLAG_06_RAND_XY);
//	item_create(s, SP_ITEM_04_P128, 	1, ITEM_MOVE_FLAG_06_RAND_XY);
//	item_create(s, SP_ITEM_03_1UP,		1, ITEM_MOVE_FLAG_06_RAND_XY);
//
//	item_create(sb01[i], SP_ITEM_COIN,7);

/*---------------------------------------------------------
	総ての敵弾を消して、指定アイテムに変える
---------------------------------------------------------*/
extern SPRITE *sprite_list000_head;
void item_from_bullets(int put_item_num)
{
	SPRITE *s = sprite_list000_head;/* スプライト リストの先頭 から探す */
	while (NULL != s)/* スプライト リストの最後まで調べる */
	{
		if (/*SP_BULLET*/SP_GROUP_BULLETS & s->type)
		{
			item_create(s, put_item_num/*SP_ITEM_05_HOSI*/, 1, (ITEM_MOVE_FLAG_01_COLLECT|ITEM_MOVE_FLAG_06_RAND_XY) );
			s->type = SP_DELETE;
		}
		s = s->next;/*次*/
	}
}

/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/


/*---------------------------------------------------------
	スコア関連(取った得点を小さな漢字で説明表示)
---------------------------------------------------------*/

/* スコアキャッシュ最大4096文字 */
#define MAX_SCORE_CHACHE (0x1000)

/* 非表示の識別 */
#define SCORE_DELETE (0)

/* スコアキャッシュのデーター形式 */
typedef struct
{
	int time_out;	/* 表示時間 / 表示アルファ値 */
	int number; 	/* 表示文字番号(0 ... 9) [一桁の数字] */
	int x256;		/* 表示 x 座標(256固定小数点形式) */
	int y256;		/* 表示 y 座標(256固定小数点形式) */
} SCORE_CHACHE_DATA;

static SCORE_CHACHE_DATA score_number_chache[MAX_SCORE_CHACHE];

/*---------------------------------------------------------
	スコアキャッシュすべて消す
---------------------------------------------------------*/

void clear_score_chache(void)
{
	int i;
	for (i=0; i<MAX_SCORE_CHACHE; i++)
	{
		score_number_chache[i].time_out = SCORE_DELETE;
	}
}

/*---------------------------------------------------------
	sdl_screen[SDL_00_SCREEN]サーフェイスに、スコアをレンダリング
---------------------------------------------------------*/

//	   void font07_render_scorenum_xy( int time_out, int number, int x256, int y256)
//atic void font07_render_scorenum_xy(SCORE_CHACHE_DATA *aaa){}
void draw_score_chache(void)
{
//				SDL_Rect s,d;
//				s.w=(8); d.w=(8);
//				s.h=(8); d.h=(8);
	if (SDL_MUSTLOCK(sdl_screen[SDL_00_SCREEN]))	{	SDL_LockSurface(sdl_screen[SDL_00_SCREEN]); }/*ロックする*/
	int i;
	for (i=0; i<MAX_SCORE_CHACHE; i++)
	{
		SCORE_CHACHE_DATA *aaa;
		aaa = &(score_number_chache[i]);
		if (SCORE_DELETE < aaa->time_out)
		{
			aaa->time_out -= 2;
			{
			//	font07_render_scorenum_xy(
				//	(aaa->time_out),
				//	(aaa->number),
				//	(aaa->x256)/*dx*/,
				//	(aaa->y256)/*dy*/
			//		&(score_number_chache[i])
			//		);
//				s.x = ((aaa->number)<<3)+(8);
//				s.y = 0;
//				d.x = (t256_floor(aaa->x256));
//				d.y = (t256_floor(aaa->y256))/*+((aaa->time_out)>>5) 上に移動*/;
//				#if 0
//				/*遅い*/
//				SDL_SetAlpha(font07_img,SDL_SRCALPHA,(aaa->time_out));
//				#endif
//				SDL_BlitSurface(font07_img,&s,sdl_screen[SDL_00_SCREEN],&d);
				Uint16 alpha256;	alpha256 = (aaa->time_out);

				Uint16 *pd;
				{
					Uint32 y2562 = ((aaa->y256)&0x1ff00);
					pd = (Uint16 *)sdl_screen[SDL_00_SCREEN]->pixels + (y2562+y2562) + (t256_floor(aaa->x256));/*x 512/256 */
				}
				int iii;	iii = (aaa->number);
				int yyy;
				for (yyy=0; yyy<6; yyy++)
				{
					#define v (0)
					#define M (1)
					#define f8(a,b,c,d, e,f,g,h) ((a<<0)|(b<<1)|(c<<2)|(d<<3)|(e<<4)|(f<<5)|(g<<6)|(h<<7))
					static const Uint8 score_font_08x05[/*(6*10)*/(64)] =
					{
f8(v,v,v,M,M,v,v,v),f8(v,v,v,v,v,v,v,v),f8(v,v,v,v,v,v,v,v),f8(v,v,v,v,v,v,v,v),f8(v,v,v,v,v,v,v,v),f8(v,M,M,M,M,M,v,v),f8(v,v,v,M,v,v,v,v),f8(v,M,v,v,v,v,v,v),f8(v,v,M,M,v,v,v,v),f8(v,v,M,v,v,v,v,v),
f8(v,v,M,v,v,M,v,v),f8(v,v,v,v,v,v,v,v),f8(v,v,v,v,v,v,v,v),f8(v,M,M,M,M,v,v,v),f8(M,M,M,M,M,M,M,v),f8(v,v,v,M,v,v,v,v),f8(v,M,M,M,M,M,M,v),f8(v,M,v,v,M,M,M,v),f8(v,v,v,M,M,v,v,v),f8(v,v,M,M,M,M,v,v),
f8(v,M,v,v,v,v,M,v),f8(v,v,v,v,v,v,v,v),f8(v,v,M,M,M,v,v,v),f8(v,v,v,v,v,v,v,v),f8(M,v,M,v,M,v,M,v),f8(v,v,M,M,M,M,v,v),f8(v,v,v,v,v,v,v,v),f8(M,M,M,M,M,v,v,v),f8(v,v,v,v,M,v,v,v),f8(M,M,M,v,v,M,v,v),
f8(v,M,v,v,v,v,M,v),f8(v,M,M,M,M,M,M,v),f8(v,v,v,v,v,v,v,v),f8(v,v,M,M,v,v,v,v),f8(M,M,M,v,M,M,M,v),f8(v,v,M,v,v,M,v,v),f8(v,v,M,v,v,M,v,v),f8(v,M,v,v,v,v,v,v),f8(v,M,v,v,M,M,v,v),f8(v,v,M,v,M,M,v,v),
f8(v,v,M,v,v,M,v,v),f8(v,v,v,v,v,v,v,v),f8(v,v,v,v,v,v,v,v),f8(v,v,v,v,v,v,v,v),f8(M,v,v,v,v,v,M,v),f8(v,M,M,v,M,M,v,v),f8(v,M,M,v,v,M,M,v),f8(v,M,v,v,v,v,v,v),f8(v,M,v,v,v,M,M,v),f8(v,M,M,v,M,v,v,v),
f8(v,v,v,M,M,v,v,v),f8(v,v,v,v,v,v,v,v),f8(M,M,M,M,M,M,M,v),f8(M,M,M,M,M,M,M,v),f8(M,M,M,M,M,M,M,v),f8(M,M,M,M,M,M,M,v),f8(M,M,v,v,v,v,M,M),f8(v,v,M,M,M,M,M,v),f8(M,v,v,v,v,v,M,M),f8(M,M,v,v,v,M,M,M),
						/*dummy*/0,0,0,0
					};
					#undef v
					#undef M
					#undef f8
					{
						const Uint8 ddd = score_font_08x05[iii];
						int kkk;
						kkk = 1;
						int xxx;
						for (xxx=0; xxx<8; xxx++)
						{
							if (ddd & (kkk) )
							{	/* 汎用転送(アルファ任意) */
							#define bgRGB (*pd)
							#define fgRGB (0xffff)
							(*pd) = (Uint16)MAKECOL16(
								(((GETR16F(fgRGB) * (alpha256)) + (GETR16F(bgRGB) * (256 - alpha256))) >> 8),
								(((GETG16F(fgRGB) * (alpha256)) + (GETG16F(bgRGB) * (256 - alpha256))) >> 8),
								(((GETB16F(fgRGB) * (alpha256)) + (GETB16F(bgRGB) * (256 - alpha256))) >> 8)	);
							}
							pd++;
							kkk += kkk;
						}
					}
					pd += (512-8);
					iii += 10;
				}
			}
		}
	}
	if (SDL_MUSTLOCK(sdl_screen[SDL_00_SCREEN]))	{	SDL_UnlockSurface(sdl_screen[SDL_00_SCREEN]);	}/*ロック解除*/
}

/*---------------------------------------------------------
	一桁の数字を、キャッシュに登録する
---------------------------------------------------------*/

static void regist_score(int number, int x256, int y256)
{
	if (t256(380) < x256)	{ return; }
//
	static int index=0; 	/* 登録出来そうな位置 */
//	int iii;
//	iii = 0;	/* 最大登録数まで全部探す */
//	do
//	{
		index++;
		index &= (MAX_SCORE_CHACHE-1);
		/* 使用中 */
//		if (SCORE_DELETE < score_number_chache[index].time_out)
//		{
//			;	/* 登録できないので次を探す。 */
//		}
//		/* 未使用 */
//		else //if (1 > score_number_chache[index].time_out)
		{
			/* キャッシュに登録する */
			score_number_chache[index].time_out = (127*2);/*	60*2*2 =:= 2 [sec]*/
			score_number_chache[index].number	= number;
			score_number_chache[index].x256 	= x256;
			score_number_chache[index].y256 	= y256;
//			iii = MAX_SCORE_CHACHE; 	/* 見つかったよ */
		}
//		iii++;
//	} while (MAX_SCORE_CHACHE > iii);	/* 全部探した？ */
}

/*---------------------------------------------------------
	スコアを一桁の数字に分解し、キャッシュに登録する
---------------------------------------------------------*/

static void bonus_info_shered_add_score10_value(SPRITE *src, int score_value)
{
	int y256;	y256 = src->y256;
	if (t256((0)) > y256)	{ return; }
//
	int x256;	x256 = src->x256;
	int jjj;
	int i;
	jjj=0;
	/* 999990点以上は999990点の表示にする */
	if (99999 < score_value) {	score_value = 99999;  }   /* MAX 999990[pts] */
	i = 0; while ( 9999 < score_value) { score_value -= 10000; i++; jjj=1; }; if (0!=jjj) { regist_score(i, x256, y256); }	x256 += t256(8);
	i = 0; while (	999 < score_value) { score_value -=  1000; i++; jjj=1; }; if (0!=jjj) { regist_score(i, x256, y256); }	x256 += t256(8);
	i = 0; while (	 99 < score_value) { score_value -=   100; i++; jjj=1; }; if (0!=jjj) { regist_score(i, x256, y256); }	x256 += t256(8);
	i = 0; while (	  9 < score_value) { score_value -=    10; i++; jjj=1; }; if (0!=jjj) { regist_score(i, x256, y256); }	x256 += t256(8);
	i = 0; while (	  0 < score_value) { score_value--; 	   i++; jjj=1; }; if (0!=jjj) { regist_score(i, x256, y256); }	x256 += t256(8);
	regist_score(0, x256, y256);/* "0" スコアの末尾は必ず０ */
}

/*---------------------------------------------------------
	取ったアイテムの得点を説明表示(任意得点の場合)
---------------------------------------------------------*/

void bonus_info_any_score_nodel(SPRITE *src/*int x, int y*/, int score_num)
{
	player_add_score(score_num);
	bonus_info_shered_add_score10_value(src, score_num);
}

/*---------------------------------------------------------
	取ったアイテムの得点を説明表示(固定得点の場合)
---------------------------------------------------------*/

void bonus_info_score_nodel(SPRITE *src/*int x, int y*/, int score_type)
{
	static const unsigned short score_tbl[32] =
	{
		score(76800), score(   10), score(	 20), score(   30),
		score(	 40), score(   50), score(	 60), score(   70),
		score(	 80), score(   90), score(	100), score(  200),
		score(	300), score(  400), score(	500), score(  600),
		//
		score(	700), score(  800), score(	900), score( 1000),
		score( 2000), score( 3000), score( 4000), score( 5000),
		score( 6000), score( 7000), score( 8000), score( 9000),
		score(10000), score(11000), score(12000), score(51200),
	};
	int score_num;	score_num = score_tbl[(score_type)/*&(32-1)*/];
	bonus_info_any_score_nodel(src, score_num);
}

/*---------------------------------------------------------
	スコア加算されると、必ずここが呼ばれる。
	ここでエクステンドチェック(残機が得点で増えるチェック)を
	する予定。(だけど、まだ作っていない)
---------------------------------------------------------*/

void player_add_score(int score_num)
{
	((PLAYER_DATA *)player->data)->my_score += score_num;
	/* エクステンドチェック */

}

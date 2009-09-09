
#include "bullet_object.h"

/*---------------------------------------------------------
		"毛玉1",	"BADGUY",
	-------------------------------------------------------
	本家毛玉
---------------------------------------------------------*/

typedef struct
{
	ENEMY_BASE base;
	int state;
	int tx256;
	int ty256;
	int vx256;
	int vy256;
	int speed256;
	int time_out;

} KEDAMA1_DATA;

static int level;

#define NUM_OF_ENEMIES (10)
//#define NUM_OF_ENEMIES (16)

/*---------------------------------------------------------
	敵やられ
---------------------------------------------------------*/

static void lose_kedama1(SPRITE *s)
{
//	case SP_ZAKO_08_KEDAMA1:
//	if (rand_percent(10))
	{
		item_create(s, enemy_get_random_item(), 1, (ITEM_MOVE_FLAG_01_COLLECT|ITEM_MOVE_FLAG_06_RAND_XY)/*(up_flags)*/ );
	}
}

/*---------------------------------------------------------
	敵移動
---------------------------------------------------------*/
enum
{
	ST00 = 0,
	ST01,
	ST02,
	ST03,
}
;
static void move_kedama1(SPRITE *s)
{
	KEDAMA1_DATA *data = (KEDAMA1_DATA *)s->data;
	switch (data->state)
	{
	case ST00:	/* ばらばらに登場させる */
		data->time_out -= 1/**fps_fa ctor*/;
		if (0 > data->time_out)
		{
			data->time_out	= 64;
			data->state++;	/* 登場する */
		}
		break;
	case ST01:	/* 登場する */
		{	int angle512;
			angle512=atan_512(data->ty256-s->y256-t256(64)/*+(20)*/,data->tx256-s->x256);
			data->vx256 =((sin512(angle512)));
			data->vy256 =((cos512(angle512)));
		}
		if ((s->x256 >= player->x256) ||
			(s->y256 > /*(480-80)*/t256(GAME_HEIGHT/2)/*(272-32)*/ ) )
		{
			data->state++/* = ST01*/;
			data->tx256 	= t256(-100);
			data->ty256 	= t256(0)/*((player->y256)&(128-1))*/;
			data->speed256	= /*6*/t256(2.5/*5.0*/)	/**fps_fa ctor*/;
		}
		break;/*??? [***090215 追加 */
	case ST02:
		data->time_out -= 1/**fps_fa ctor*/;
		if (0==(data->time_out & 0x0f))
		{
			if (0 < /*data->*/level)
			{
				bullet_create_n_way_dan_sa_type(s,
					t256(1.0), //t256(1.0)+t256((/*data->*/level)>>1),
					ANGLE_JIKI_NERAI_DAN,
					(int)(512/24),
					BULLET_KOME_01_AOI+(s->x256&0x07),
					(3+difficulty+difficulty));
			}
		}
		if (0 > data->time_out)
		{
			data->state++;
		}
		break;
	case ST03:
		{	int angle512;
			angle512=atan_512(data->ty256-s->y256-t256(64)/*+(20)*/,data->tx256-s->x256);
			data->vx256 =((sin512(angle512)));
			data->vy256 =((cos512(angle512)));
		}
		if (s->x256 <= -((s->w128+s->w128)))
		{
			s->type = SP_DELETE;
		}
		break;/*??? [***090215 追加 */
	}

	/* CCWの場合 */
	s->x256+=(((data->vx256)*data->speed256)>>8);
	s->y256+=(((data->vy256)*data->speed256)>>8);
}

/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/

void add_zako_kedama1(STAGE_DATA *l)/*int lv*/
{
	/*data->*/level 	= l->user_y;
	int i;
	for (i=0; i<NUM_OF_ENEMIES; i++)
	{
		SPRITE *s;
		s					= sprite_add_res(BASE_KEDAMA16_PNG);	//s->anim_speed=5; /*3*/ /*9"ba dguy.png"*/
		s->anim_speed		= /*-*/3; /*逆転アニメ禁止に変更*/
		s->type 			= SP_ZAKO/*_08_KEDAMA1*/;
		s->flags			|= (SP_FLAG_VISIBLE|SP_FLAG_COLISION_CHECK|SP_FLAG_TIME_OVER);
		s->callback_mover	= move_kedama1;
		s->callback_loser	= lose_kedama1;
		s->anim_frame		= 0;
		switch (i&3/*i%5*/)
		{
		case 0: s->x256 	=				   (ra_nd()&((64*256)-1))/*ra_nd()%40*/; break;
		case 1: s->x256 	= t256(GAME_WIDTH)-(ra_nd()&((64*256)-1))/*ra_nd()%40*/; break; 	// GAME_WIDTH ウィンドウ幅の変更
		case 2: s->x256 	= t256(200)+	   (ra_nd()&((64*256)-1))/*ra_nd()%40*/; break;
		case 3: s->x256 	= t256(90)+ 	   (ra_nd()&((64*256)-1))/*ra_nd()%40*/; break;
	//	case 4: s->x256 	= t256(310)+	   (ra_nd()&((64*256)-1))/*ra_nd()%40*/; break;
		}
		s->y256 			= ((ra_nd()&((32*256)-1))-t256(80));//	(ra_nd()%40-90);
		KEDAMA1_DATA *data;
		data				= mmalloc(sizeof(KEDAMA1_DATA));
		s->data 			= data;
		data->base.score	= score(/*50*/5*2)*(level+1);
		data->base.health	= (8*8)+(difficulty<<2)/*(1+(difficulty<<2))*/;/*やわらかすぎ*/
		data->state 		= ST00;
		data->time_out		= 64+(i<<4);
		data->tx256 		= player->x256;
		data->ty256 		= player->y256;
		data->vx256 			= (0);
		data->vy256 			= (0);
	//	data->speed256		= /*fps_fa ctor**/((ra_nd()&((256*2)-1)))*(1+difficulty+level/3);
		data->speed256		= /*fps_fa ctor**/((ra_nd()&((256*2)-1))) + ((difficulty<<8)+ (level<<7/**86*2*/) );
	}
}
#undef NUM_OF_ENEMIES


/*---------------------------------------------------------
	東方模倣風	〜 Toho Imitation Style.
	プロジェクトページ http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
		"毛玉1",	"BADGUY",
	-------------------------------------------------------
	本家毛玉
---------------------------------------------------------*/

/*---------------------------------------------------------
	敵移動
---------------------------------------------------------*/

static void my_nerai(SPRITE *src)
{
	obj_send1->cx256 	= (src->target_x256);						/* 弾源x256 */
	obj_send1->cy256 	= (src->target_y256-t256(64)/*+(20)*/); 	/* 弾源y256 */
	tmp_angleCCW1024_src_nerai(obj_send1, src);
	src->vx256 = ((sin1024(src->tmp_angleCCW1024)));
	src->vy256 = ((cos1024(src->tmp_angleCCW1024)));
}

static void move_kedama1(SPRITE *src)
{
	if (512 > src->jyumyou)/* 退場 */
	{
		my_nerai(src);
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (512+64 > src->jyumyou)/* */
	{
		if (0==(src->jyumyou & 0x0f))
		{
			if (ENEMY_LAST_SHOT_LINE256 > src->cy256)	/* このラインより下からは敵が撃たない */
			{
				obj_send1->cx256 					= src->cx256;
				obj_send1->cy256 					= src->cy256;
				br.BULLET_REGIST_speed256			= t256(1.0);	//t256(1.0)+t256((src->enemy_rank)>>1),
				br.BULLET_REGIST_angle1024			= ANGLE_JIKI_NERAI_DAN;
				br.BULLET_REGIST_div_angle1024		= (int)(1024/24);
				br.BULLET_REGIST_bullet_obj_type	= BULLET_KOME_00_SIRO+(src->cx256&0x07);
				br.BULLET_REGIST_n_way				= (3+difficulty+difficulty);
				br.BULLET_REGIST_regist_type		= REGIST_TYPE_00_MULTI_VECTOR;
				bullet_regist_vector();
			}
		}
	}
	else
//	if (512+64+64 > src->jyumyou)	/* 登場する */
	{
		my_nerai(src);
		{
			SPRITE *zzz_player;
			zzz_player = &obj00[FIX_OBJ_00_PLAYER];
			if (//(src->cx256 >= zzz_player->cx256) ||
				(src->cy256 > t256(GAME_HEIGHT/2) ) /*(480-80)*/ /*(272-32)*/
			 )
			{
				src->vy256 = (-src->vy256);
				src->jyumyou	= (512+64-1);
				/* 第二目標は、 */
				src->target_x256		= t256(((480-128)/2));	//= t256(-100);
				src->target_y256		= t256(0);/*((zzz_player->cy256)&(128-1))*/
				src->speed256			= t256(2.5/*5.0*/);/*fps_factor*/	/*6*/
			}
		}
	}
	/* 移動する */
	src->cx256 += (((src->vx256)*src->speed256)>>8);
	src->cy256 += (((src->vy256)*src->speed256)>>8);
	/* アニメ(回転) */
	src->rotationCCW1024 += (10);
	mask1024(src->rotationCCW1024);
}

/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/

global void add_zako_kedama1(STAGE_DATA *l)
{
	SPRITE *h;
	h							= sprite_add_gu_error();
	if (NULL!=h)/* 登録できた場合のみ */
	{
		add_zako_common(l, h);
		h->m_Hit256R			= ZAKO_ATARI16_PNG;
		h->type 				= TEKI_59_HAI_KEDAMA;
		h->color32				= MAKE32RGBA(0xff, 0xff, 0xff, 0xaa);		/*白っぽく */
		h->callback_mover		= move_kedama1;
	//
		h->jyumyou			= (512+64+64);
		{
			/* 第一目標はプレイヤーのいた位置 */
			SPRITE *zzz_player;
			zzz_player = &obj00[FIX_OBJ_00_PLAYER];
			h->target_x256				= (zzz_player->cx256);
			h->target_y256				= (zzz_player->cy256);
		}
		h->vx256				= (0);
		h->vy256				= (0);
	//	h->speed256 			= ((ra_nd()&((256*2)-1)))*(1+difficulty+enemy_rank/3);/*fps_factor*/
		h->speed256 			= ((ra_nd()&((256*2)-1))) + ((difficulty<<8)+ (/*enemy_rank*/5<<7/**86*2*/) );/*fps_factor*/
	}
}

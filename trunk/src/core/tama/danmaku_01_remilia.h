
/*---------------------------------------------------------
	レミリア っぽいもの
	-------------------------------------------------------

---------------------------------------------------------*/
static void remilia_shot00(SPRITE *src)
{
	#if (1)
//	voice_play(VOICE14_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
	bullet_play_04_auto(VOICE14_BOSS_KOUGEKI_01);
	#endif
//
	// ■  [大玉弾]
//	br.BULLET_REGIST_speed256			= (t256(3.5));							/* 弾速 */
//	br.BULLET_REGIST_speed256			= (t256(2.25)); 							/* 弾速 */
	br.BULLET_REGIST_speed256			= (t256(6.00)); 							/* 弾速 */
	br.BULLET_REGIST_div_angle65536 	= (int)(65536/48);						/* 分割角度 */
//	br.BULLET_REGIST_regist_type		= REGIST_TYPE_00_MULTI_VECTOR;/*現在種類が無い*/
	br.BULLET_REGIST_bullet_obj_type	= BULLET_OODAMA32_01_AKA;				/* [赤大玉弾] */
	br.BULLET_REGIST_angle65536 		= src->tmp_angleCCW65536;/*自機ねらい角*/
	br.BULLET_REGIST_n_way				= (1);									/* [1way] */
//	br.BULLET_REGIST_speed_offset		= -t256(1);/* 減速弾？ */
	br.BULLET_REGIST_speed_offset		= -t256(4);/* 減速弾？ */

	bullet_regist_angle();
	// ■  [中玉弾]
	br.BULLET_REGIST_speed256			= (t256(4.00)); 							/* 弾速 */
	br.BULLET_REGIST_speed_offset		= -t256(2);/* 減速弾？ */
	br.BULLET_REGIST_bullet_obj_type	= BULLET_MARU10_01_AKA; 			/* [赤大中弾] */
	u32 ii;
	for (ii=0; ii<8; ii++)
	{
		br.BULLET_REGIST_angle65536 		= src->tmp_angleCCW65536 + ((ra_nd()) & ((65536/8)-1)) - ((65536/16)-1);/*自機ねらい角*/
		bullet_regist_angle();
	}
	// ■  [小玉弾]
	br.BULLET_REGIST_speed256			= (t256(2.00)); 							/* 弾速 */
	br.BULLET_REGIST_speed_offset		= -t256(1);/* 減速弾？ */
	br.BULLET_REGIST_bullet_obj_type	= BULLET_MARU8_01_AKA;				/* [赤大中弾] */
	for (ii=0; ii<(0x02<<difficulty); ii++)/*(16)*/
	{
		br.BULLET_REGIST_angle65536 		= src->tmp_angleCCW65536 + ((ra_nd()) & ((65536/4)-1)) - ((65536/8)-1);/*自機ねらい角*/
		bullet_regist_angle();
	}

}
/*---------------------------------------------------------
	レミリア 通常攻撃2 っぽいもの
	-------------------------------------------------------
	1秒撃ったら、3秒休む(移動)。

---- ---- ---- ----
0000 0011 1111 1111
---------------------------------------------------------*/

static void danmaku_create_1f_remilia_kougeki2(SPRITE *src)
{
//	if (0xc0==((src->boss_base_danmaku_time_out)&0xc0))
	if (0xc0==((src->boss_base_danmaku_time_out)&0xc7))/* ８回に一回 */
	{
				/* 中心座標なので、オフセットなし==ボス中心から弾出す。 */
		//	obj_send1->cx256 					= (src->cx256)+t256(24.0);							/* 弾源x256 */
		//	obj_send1->cy256 					= (src->cy256)+t256( 8.0);							/* 弾源y256 */
			obj_send1->cx256 					= (src->cx256);							/* 弾源x256 */
			obj_send1->cy256 					= (src->cy256);							/* 弾源y256 */
		#if 0
		/* 撃つターン 8弾 */
		if (0x0000==((src->boss_base_danmaku_time_out)&0x30))
		{
			/* 自機狙い撃ち */
			remilia_shot00(src);
		}
		else
		if (0x0100==((src->boss_base_danmaku_time_out)&0x30))
		{
			/* CW 撃ち */
			remilia_shot00(src);
		}
		else
		if (0x0200==((src->boss_base_danmaku_time_out)&0x30))
		{
			/* CCW 撃ち */
			remilia_shot00(src);
		}
		else
	//	if (0x0300==((src->boss_base_danmaku_time_out)&0x30))
		{
		//	/* 一気撃ち */
			/* 自機狙い撃ち */
			remilia_shot00(src);
		}
		#endif

		if (0==(((src->boss_base_danmaku_time_out)+0x100)&0x200))
		{
			{
				SPRITE *zzz_player;
				zzz_player = &obj00[FIX_OBJ_00_PLAYER];
				tmp_angleCCW65536_src_nerai(zzz_player, obj_send1);/*自機ねらい角作成*/
			}
			src->tmp_angleCCW65536		= obj_send1->tmp_angleCCW65536;/*自機ねらい角*/
			#if (1)
			src->tmp_angleCCW65536		-= (ra_nd()) & ((65536/32)-1);/* [謎の修正] 現状狙わないのでゲームにならないから仕方なく。 */
			#endif
		}
		else
		{
			src->tmp_angleCCW65536		+= (((src->boss_base_danmaku_time_out)&0x20)<<5)-( ((65536/24)-1));/* */
		}
		remilia_shot00(src);
	}
//	else
//	{
//		/* 休み */
//		;
//	}
}


/*---------------------------------------------------------
	東方模倣風	〜 Toho Imitation Style.
	プロジェクトページ http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	"メイド4",		"CIR",	rwingx_cir
	-------------------------------------------------------
	右側から二列縦隊で現れ、下に向かい。下で旋回。
	中央から上昇し、右側に向かい。上で旋回。
	右側から下に向かい。画面外へ退場。
---------------------------------------------------------*/

/*---------------------------------------------------------
	敵やられ
---------------------------------------------------------*/

static void lose_meido4(SPRITE *src)
{
	item_create(src, SP_ITEM_05_TENSU, 1, ITEM_MOVE_FLAG_06_RAND_XY);
}


/*---------------------------------------------------------
	敵移動
---------------------------------------------------------*/

static void move_meido4(SPRITE *src)
{
	if (512 > src->jyumyou)/* 退場 */ /* down */
	{
		src->speed256 += t256(0.1);/*加速*/
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (512+512 > src->jyumyou)/* turn */
	{	/* CCWの場合 */
		src->tmp_angleCCW1024 -= (10);		/*2*/ /*cv1024r(360-2)*/ /*fps_factor*/
		mask1024(src->tmp_angleCCW1024);
		if (src->tmp_angleCCW1024 > cv1024r(270) )	/* ほぼ真下を向いたら */
		{
			src->tmp_angleCCW1024 = cv1024r((0));		/* 真下に強制補正 */
			src->jyumyou = (512-1);
			src->speed256 = t256(1.0);	/*6.0*/
		}
	}
	else
	if (512+512+512 > src->jyumyou)/* up */
	{
		if (src->cy256 < t256(64/*50*/)) 	/* 中心付近を越えて上がったら、少し速度を落とす */
		{
			src->jyumyou = (512+512-1);
			src->speed256 = t256(1.5);		/*3.0*/
		}
	}
	else
	if (512+512+512+512 > src->jyumyou)/* 下で旋回 / turn */
	{	/* CCWの場合 */
		src->tmp_angleCCW1024 += (10);		/*4*/ /*cv1024r(360-2)*/ /*fps_factor*/
		mask1024(src->tmp_angleCCW1024);
		if ( src->tmp_angleCCW1024 > cv1024r((180)) )		/* ほぼ真上を向いたら */
		{
			src->tmp_angleCCW1024 = cv1024r((180)); 	/* 真上に強制補正 */
			src->jyumyou = (512+512+512-1);
			src->speed256 = t256(2.0);		/*8.0*/ 	/* 速度を落とす */
		}
	}
	else
//	if (512+512+512+512+512 > src->jyumyou)/* 下に向かう / down */
	{
		if (src->cy256 > t256(128))			/* 中心付近を越えて下がったら、少し速度を落とす */	/*200*/
		{
			src->jyumyou = (512+512+512+512-1);
			src->speed256 = t256(2.5);		/* 速度を落とす */	/*3.0*/
		}
	}
	/*以下rwingx.cと同じ*/
	src->cx256+=((sin1024((src->tmp_angleCCW1024))*src->speed256)>>8);/*fps_factor*/ 	/* CCWの場合 */
	src->cy256+=((cos1024((src->tmp_angleCCW1024))*src->speed256)>>8);/*fps_factor*/
	/* アニメーション */
	zako_anime_type01(src, TEKI_36_YOUSEI3_1);
}


/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/

global void add_zako_meido4(STAGE_DATA *l)
{
	SPRITE *h;
	h							= sprite_add_gu_error();
	if (NULL!=h)/* 登録できた場合のみ */
	{
		add_zako_common(l, h);
		h->m_Hit256R			= ZAKO_ATARI16_PNG;
		h->type 				= TEKI_36_YOUSEI3_1;/*SP_ZAKO*/ /*_15_MEIDO4*/
		h->callback_mover		= move_meido4;
		h->callback_loser		= lose_meido4;
		h->tmp_angleCCW1024 	= cv1024r(0);		/* 真下 */	/* CCWの場合 */
		h->speed256 			= t256(3.0);	/*6.0*/
		h->jyumyou = (512+512+512+512+512-1);
	}
}
//	h->callback_hit_enemy	= callback_hit_zako;

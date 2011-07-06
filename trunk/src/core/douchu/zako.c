
#include "douchu.h"

/*---------------------------------------------------------
	東方模倣風	〜 Toho Imitation Style.
	プロジェクトページ http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ザコは纏める予定。
---------------------------------------------------------*/
//extern void zako_anime_type01(SPRITE *src, int type_base);
//extern void zako_anime_type02(SPRITE *src, int type_base);

#if 0/* めも */
/* ボス共通規格 */
	#define target_x256 		user_data00 	/* 目標x座標 */
	#define target_y256 		user_data01 	/* 目標y座標 */
	#define vvv256				user_data02 	/* 目標座標への到達割合 */
	#define boss_time_out		user_data03 	/* 制限時間 */
#endif


/*---------------------------------------------------------
	ザコ移動共通
---------------------------------------------------------*/
	#define target_x256 			user_data00
	#define target_y256 			user_data01
	#define radius256				user_data02
static void zako_move_type11_radius(SPRITE *src)
{
	src->cx256 = ((sin1024((src->tmp_angleCCW1024))*(src->radius256))>>8)+(src->target_x256);/* CCWの場合 */
	src->cy256 = ((cos1024((src->tmp_angleCCW1024))*(src->radius256))>>8)+(src->target_y256);
}
	#define speed256				user_data04 	/* 速度 */
	#define kaisu_nnn				user_data05 	/* 繰り返した回数のカウンタ */

/*---------------------------------------------------------
	ザコアニメ共通
---------------------------------------------------------*/
static void zako_anime_type01(SPRITE *src, int type_base)
{
	src->type				= (type_base)+((((src->tmp_angleCCW1024)&(1024-1)))>>7);
}
static void zako_anime_type02(SPRITE *src, int type_base)
{
	src->type				= (type_base)+((src->jyumyou>>2)&(4-1));
}


/*---------------------------------------------------------

---------------------------------------------------------*/
	#define MAHOU_TEKI_wait1		user_data04
	#define MAHOU_TEKI_wait2		user_data05
	#define start_y256				user_data06
#include "zako_11_mahoujin.h"			/* 魔方陣[A/B] */

	#define limit_y256				user_data05 	/* 仮想地面 */
#include "zako_10_inyou1.h" 			/* 竜巻 陰陽玉 */

//	#define speed256				user_data04 	/* 速度 */
	#define vx_r					user_data05 	/* 回転方向(回転量) */
	#define px256					user_data06 	/* 仮想x位置(反転用) */
#include "zako_11_tatsumaki1.h" 		/* 竜巻 陰陽玉 */

//	#define target_x256 			user_data00
//	#define target_y256 			user_data01
//	#define radius256				user_data02
	/* 敵の向き tmp_angleCCW1024  */
#include "zako_12_kakomi1.h"			/* 妖怪 */
#include "zako_04_aka_kedama.h" 		/* 妖怪 */


//	#define speed256				user_data04
	#define max_y256				user_data05
#include "zako_03_yukari2.h"			/* 毛玉 */
	#define target_x256 			user_data00
	#define target_y256 			user_data01
#include "zako_06_midori_kedama1.h" 	/* 毛玉 */
	#define wait1					user_data04 	/* 上下に動いたカウンタ */
//	#define kaisu_nnn				user_data05 	/* 繰り返した回数のカウンタ */
#include "zako_07_midori_kedama2.h" 	/* 毛玉 */

	#define target_x256 			user_data00
	#define target_y256 			user_data01
//	#define speed256				user_data04
#include "zako_08_kedama1.h"			/* 毛玉 */
	#define kougeki_type			user_data05
	#define USE_X_HOUKOU (1)
#include "zako_09_kedama2.h"			/* 毛玉 */


	/* 敵の向き tmp_angleCCW1024  */
	#define gra_anime_type			user_data04 	/* グラタイプ */
#include "zako_01_obake1.h" 			/* [C妖精]その他ザコ */
//	#define target_x256 			user_data00
//	#define target_y256 			user_data01
//	#define radius256				user_data02
	#define flag1					user_data05
#include "zako_02_obake2.h" 			/* [C妖精]その他ザコ */
	#define USE_X_HOUKOU_karasu (0)
	#define KARASU3_houkou			user_data05
#include "zako_05_karasu1.h"			/* [C妖精]その他ザコ */


//	#define speed256				user_data04
#include "zako_13_meido1.h" 			/* [B妖精]中妖精 */
//	#define speed256				user_data04
#include "zako_14_meido2.h" 			/* [B妖精]中妖精 */
	#define clip_left256			user_data00
	#define clip_right256			user_data01
	#define turnspeed1024			user_data03
//	#define speed256				user_data04
//	#define kaisu_nnn				user_data05 	/* ターンする回数 */
#include "zako_15_meido3.h" 			/* [B妖精]中妖精 */
//	#define speed256				user_data04
#include "zako_16_meido4.h" 			/* [B妖精]中妖精 */

	/* 敵の向き tmp_angleCCW1024  */
//	#define speed256				user_data04 	/* 速度 */
#include "zako_17_ao_yousei1.h" 		/* [A妖精]小妖精 */
//	#define kaisu_nnn				user_data05 	/* 弾を撃つ回数 */
#include "zako_18_ao_yousei2.h" 		/* [A妖精]小妖精 */
	#define USE_X_HOUKOU_ao3 (0)
	#define KARASU3_houkou			user_data05
#include "zako_19_ao_yousei3.h" 		/* [A妖精]小妖精 */
	/* 敵の向き tmp_angleCCW1024  */
//	#define speed256				user_data04 	/* 速度 */
#include "zako_20_ao_yousei4.h" 		/* [A妖精]小妖精 */


/*
src->jyumyou		 ---a bc--
src->yx_an im_frame  yyyy xxxx
src->yx_an im_frame  --1a --bc
*/

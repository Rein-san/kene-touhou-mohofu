
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	インクルードファイルについて
---------------------------------------------------------*/

/*---------------------------------------------------------
	基本設定
	本ゲームの基本設定をこのファイルに書きます。
---------------------------------------------------------*/

#ifndef _MY_GAME_MAIN_H_
#define _MY_GAME_MAIN_H_

/*	インクルードファイル自体の基本設定	*/

/* 0:しない。 1:する。 [メモリゼロクリアー機能]
	1:なら、my_calloc()した際に 確保したメモリを0クリアーします。0ならしません。
	大量に弾を出す場合どちらがいいか判りません(0:速いがバグる可能性、1:遅いが安定度は高い)が、
	1:の方がいろんな意味でバグ抑制できます。 */
//#define USE_MEM_CLEAR (0)
#define USE_MEM_CLEAR (1)

/* 0:使わない。1:使う。 1:キーコンフィグ使う。0:キーコンフィグ機能OFF */
//#define USE_KEY_CONFIG (0)
#define USE_KEY_CONFIG (1)

/* 0:使わない。1:使う。  [1:キーコンフィグ使う場合で] 1:方向キーのキーコンフィグを使う。0:方向キーのキーコンフィグ機能OFF */
#define USE_KEY_CONFIG_ALLOW (0)

/* 0:しない。 1:する。	コンティニューした場合、スコアランキング */
#define USE_CONTINUED_RANKING	(0)

/* 0:しない。 1:する。 エクステンドチェック */
//#define USE_EXTEND_CHECK (0)
#define USE_EXTEND_CHECK (1)

/* 0:しない。 1:する。 カンスト(スコアカウンター ストップ)チェック */
//#define USE_MAX_SCORE_COUNTER_STOP_CHECK (0)
#define USE_MAX_SCORE_COUNTER_STOP_CHECK (0)
/*
カンストは 99,9999,9990pts (99億点)ですが、チョットぐらいの調整じゃカンストしそうにない。
(グレイズを10万の位まで稼いだり、いろいろ実験してみたけど...)
アリス：カンストなんて無いわ！
*/


/* 0:しない。 1:する。 パーサー(設定読み込み時の字句解析)についてのデバッグ機能。 */
#define USE_PARTH_DEBUG (0)


/* 0:しない。 1:する。 実験用。一部対応していない。有効にするととても遅い。 */
#define USE_32BIT_DRAW_MODE (0)

/* 0:しない。 1:する。 easyの場合、5面終わりでBAD END。 */
//#define US E_EASY_BADEND (1)


/* 0:しない。 1:する。 (r36)現在0固定。現状の方式だと1は無理なので、改良予定。 */
#define USE_AFTER_LOAD_STAGE (0)


/*---------------------------------------------------------
	使用設定(次にインクルード)
	本システムをどのように使うか個別の設定
---------------------------------------------------------*/

/* 色設定 */
#if (0==USE_32BIT_DRAW_MODE)
	#define USE_PSP_5551	0
	//#define USE_PSP_5551	1
	#if (1==USE_PSP_5551)
		#define SDL_GU_PSM_0000 		GU_PSM_5551
		/*(PSPSDKの場合5-5-5-1)*/
		/*(pspのSDLでは特殊な操作しない限り5-5-5-0) */
		/* 5-5-5-1*/
		#define PSP_DEPTH16 			(16)
		#define SDL_5551_15 			(15)
		#define PSP_SCREEN_FORMAT_RMASK (0x001f)
		#define PSP_SCREEN_FORMAT_GMASK (0x03e0)
		#define PSP_SCREEN_FORMAT_BMASK (0x7c00)
		#define PSP_SCREEN_FORMAT_AMASK (0x8000)
		#define PSP_SCREEN_FORMAT_LMASK (0x7bde)
	#else
		#define SDL_GU_PSM_0000 		GU_PSM_5650
		/* 5-6-5-0 */
		#define PSP_DEPTH16 			(16)
		#define SDL_5551_15 			(16)
		#define PSP_SCREEN_FORMAT_RMASK (0x001f)
		#define PSP_SCREEN_FORMAT_GMASK (0x07e0)
		#define PSP_SCREEN_FORMAT_BMASK (0xf800)
		#define PSP_SCREEN_FORMAT_AMASK (0x0000)
		#define PSP_SCREEN_FORMAT_LMASK (0xf7de)
	#endif
#else
		/* 色32bitモード */
		#define SDL_GU_PSM_0000 		GU_PSM_8888
		/* 5-6-5-0 */
		#define PSP_DEPTH16 			(32)
		#define SDL_5551_15 			(32)
		#define PSP_SCREEN_FORMAT_RMASK (0x000000ff)
		#define PSP_SCREEN_FORMAT_GMASK (0x0000ff00)
		#define PSP_SCREEN_FORMAT_BMASK (0x00ff0000)
		#define PSP_SCREEN_FORMAT_AMASK (0xff000000)
		#define PSP_SCREEN_FORMAT_LMASK (0xfefefefe)
#endif

//(1==US E_GU)
//	#define SD L_VRAM_SCREEN	vr am_screen
	#define SDL_PSP_BUFFER_WIDTH512 PSP_BUFFER_WIDTH512
	#if 1
		/* ソフトウェアーで Zソート */
		#define USE_ZBUFFER 	(0)
	#else
		/* ハードウェアーでソート */
		#define USE_ZBUFFER 	(1)
	#endif

#if 0
// SDL */
	//#define SD L_VRAM_SCREEN		sdl_screen[SDL_00_VIEW_SCREEN]
	//#define SD L_PSP_BUFFER_WIDTH512	PSP_WIDTH480
#endif


/*---------------------------------------------------------
	インクルードファイルについて
---------------------------------------------------------*/

#if (0)

ファイル名の先頭が "000_" で始まる物は "game_main.h" 以外からインクルードしないでください。

これら "000_" で始まる物は 現状単に分割してあるだけで、分割してある意味はあまりありません。
判りにくくならないならば、適当に整理して纏める予定です。
(000_audio.h とか 000_support.h とかは、現状でも完全に機能で分割されています。
これらは纏めると判りにくくなるので纏めません。)

基本的に "game_main.h" をインクルードして、それ以外はインクルードしません。
例外はあります。

以下例外
---------------------------------------------------------
☆ シナリオ関連は考慮中なので、シナリオ関連を使う場合(主に漢字描画)
 "game_main.h" の後で、"kaiwa_system.h" を 直接インクルードします。
---------------------------------------------------------
☆ ファイル関連も拡張予定があります。ファイル関連を使う場合、
 "game_main.h" の後で、"111_my_file.h" を 直接インクルードします。
---------------------------------------------------------
☆ 道中の場合、道中共通処理が入るかもしれないので、
 "game_main.h" の代わりに "douchu.h" を 直接インクルードします。
---------------------------------------------------------
☆ ボスの場合、ボス共通処理が入るかもしれないので、
 "game_main.h" の代わりに "boss.h" を 直接インクルードします。
---------------------------------------------------------
☆ 描画関連場合、仕様がさっぱり決まってないので例外です。
---------------------------------------------------------

#endif /* (0) */

/*---------------------------------------------------------
	各種マクロ等
---------------------------------------------------------*/
#include "000_support.h"	/* (特殊。一番最初にインクルード) */

/*---------------------------------------------------------
	基本関数
---------------------------------------------------------*/
#include "000_my_math.h"

/*---------------------------------------------------------
	スプライト オブジェクト
---------------------------------------------------------*/

#include "000_object_system.h"
#include "000_gu_obj_type.h"

/*---------------------------------------------------------
	弾システム
	カードCPU
	発弾システム
	レーザーシステム
	レイヤーシステム
---------------------------------------------------------*/

#include "000_tama_system.h"

/*---------------------------------------------------------
	ゲームコアサポート
---------------------------------------------------------*/

#include "000_core_support.h"

/*---------------------------------------------------------
	ゲームコアシステム
---------------------------------------------------------*/

#include "000_game_core.h"


/* Gu Render */
#include "000_gu_render.h"



#else
	include error!!
error! "このファイルは何度もインクルードしません。"
#endif /* _MY_GAME_MAIN_H_ */

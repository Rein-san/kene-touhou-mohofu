
/*---------------------------------------------------------
 �����͕핗 �` Toho Imitation Style.
  �v���W�F�N�g�y�[�W http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���~���A ���ۂ��J�[�h���`���܂��B
---------------------------------------------------------*/

local void remilia_oyasumi_kougeki(SPRITE *src)
{
	// ��  [��ʒe]
//	HATSUDAN_01_speed256			= (t256(3.5));						/* �e�� */
//	HATSUDAN_01_speed256			= (t256(2.25)); 					/* �e�� */
	HATSUDAN_01_speed256			= (t256(6.00)); 					/* �e�� */
//	HATSUDAN_02_speed_offset		= -t256(1);/* �����e�H */
	HATSUDAN_02_speed_offset		= -t256(4);/* �����e�H */
	HATSUDAN_03_angle65536			= (16384)+(((REG_10_BOSS_SPELL_TIMER)&0x40)<<8);/* ���@�_���p */
	HATSUDAN_04_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	HATSUDAN_05_bullet_obj_type 	= BULLET_OODAMA32_01_AKA;			/* [�ԑ�ʒe] */
	hatudan_system_regist_single();
	// ��  [���ʒe]
	HATSUDAN_01_speed256			= (t256(4.00)); 					/* �e�� */
	HATSUDAN_02_speed_offset		= -t256(2);/* �����e�H */
	HATSUDAN_05_bullet_obj_type 	= (BULLET_MARU10_BASE + TAMA_IRO_01_AKA);			/* [�ԑ咆�e] */
	u32 ii;
	for (ii=0; ii<8; ii++)
	{
		HATSUDAN_03_angle65536		= src->tmp_angleCCW65536 + ((ra_nd()) & ((65536/8)-1)) - ((65536/16)-1);/* ���@�_���p */
		hatudan_system_regist_single();
	}
	// ��  [���ʒe]
	HATSUDAN_01_speed256			= (t256(2.00)); 					/* �e�� */
	HATSUDAN_02_speed_offset		= -t256(1);/* �����e�H */
	HATSUDAN_05_bullet_obj_type 	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);				/* [�ԑ咆�e] */
	for (ii=0; ii<(u32)(0x02<<(REG_0f_GAME_DIFFICULTY)); ii++)/*(16)*/
	{
		HATSUDAN_03_angle65536		= src->tmp_angleCCW65536 + ((ra_nd()) & ((65536/4)-1)) - ((65536/8)-1);/* ���@�_���p */
		hatudan_system_regist_single();
	}
	#if (0)
//	voice_play(VOICE15_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
	bullet_play_04_auto(VOICE15_BOSS_KOUGEKI_01);
	#endif
}


local void remilia_shot00(SPRITE *src)
{
	// ��  [��ʒe]
//	HATSUDAN_01_speed256			= (t256(3.5));						/* �e�� */
//	HATSUDAN_01_speed256			= (t256(2.25)); 					/* �e�� */
	HATSUDAN_01_speed256			= (t256(6.00)); 					/* �e�� */
//	HATSUDAN_02_speed_offset		= -t256(1);/* �����e�H */
	HATSUDAN_02_speed_offset		= -t256(4);/* �����e�H */
	HATSUDAN_03_angle65536			= src->tmp_angleCCW65536;/* ���@�_���p */
	HATSUDAN_04_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	HATSUDAN_05_bullet_obj_type 	= BULLET_OODAMA32_01_AKA;			/* [�ԑ�ʒe] */
	hatudan_system_regist_single();
	// ��  [���ʒe]
	HATSUDAN_01_speed256			= (t256(4.00)); 					/* �e�� */
	HATSUDAN_02_speed_offset		= -t256(2);/* �����e�H */
	HATSUDAN_05_bullet_obj_type 	= (BULLET_MARU10_BASE + TAMA_IRO_01_AKA);			/* [�ԑ咆�e] */
	u32 ii;
	for (ii=0; ii<8; ii++)
	{
		HATSUDAN_03_angle65536		= src->tmp_angleCCW65536 + ((ra_nd()) & ((65536/8)-1)) - ((65536/16)-1);/* ���@�_���p */
		hatudan_system_regist_single();
	}
	// ��  [���ʒe]
	HATSUDAN_01_speed256			= (t256(2.00)); 					/* �e�� */
	HATSUDAN_02_speed_offset		= -t256(1);/* �����e�H */
	HATSUDAN_05_bullet_obj_type 	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);				/* [�ԑ咆�e] */
	for (ii=0; ii<(u32)(0x02<<(REG_0f_GAME_DIFFICULTY)); ii++)/*(16)*/
	{
		HATSUDAN_03_angle65536		= src->tmp_angleCCW65536 + ((ra_nd()) & ((65536/4)-1)) - ((65536/8)-1);/* ���@�_���p */
		hatudan_system_regist_single();
	}
	#if (1)
//	voice_play(VOICE15_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
	bullet_play_04_auto(VOICE15_BOSS_KOUGEKI_01);
	#endif
}


/*---------------------------------------------------------
	���~���A �ʏ�U��2 ���ۂ�����
	-------------------------------------------------------
	1�b��������A3�b�x��(�ړ�)�B

---- ---- ---- ----
0000 0011 1111 1111
---------------------------------------------------------*/

local void spell_create_1f_remilia_kougeki2(SPRITE *src)
{
	if (0x80==((REG_10_BOSS_SPELL_TIMER)&0x80))/* �㔼 */
	{
	//	if (0xc0==((REG_10_BOSS_SPELL_TIMER)&0xc0))
		if (0xc0==((REG_10_BOSS_SPELL_TIMER)&0xc7))/* �W��Ɉ�� */
		{
			#if 0
			/* ���^�[�� 8�e */
					if (0x0000==((REG_10_BOSS_SPELL_TIMER)&0x30))	{	remilia_shot00(src);	}	/* ���@�_������ */
			else	if (0x0100==((REG_10_BOSS_SPELL_TIMER)&0x30))	{	remilia_shot00(src);	}	/* CW ���� */
			else	if (0x0200==((REG_10_BOSS_SPELL_TIMER)&0x30))	{	remilia_shot00(src);	}	/* CCW ���� */
			else/*	if (0x0300==((REG_10_BOSS_SPELL_TIMER)&0x30)) */	{	remilia_shot00(src);	}	/* ���@�_������ */	/* ��C���� */
			#endif
			if (0==(((REG_10_BOSS_SPELL_TIMER)+0x100)&0x200))
			{
				calculate_jikinerai();/* ���@�_���p�쐬 */
				src->tmp_angleCCW65536		= HATSUDAN_03_angle65536;/* ���@�_���p */
			}
			else
			{
				src->tmp_angleCCW65536		+= (((REG_10_BOSS_SPELL_TIMER)&0x20)<<5)-( ((65536/24)-1));/* */
			}
			remilia_shot00(src);
		}
	}
	/* �{���͋x�݂����ǁA���܂�ɊȒP�Ȃ̂ōU�� */
	else
	{
/*
8421
1111 f	- - - -
1110 e	- - - -
1101 d	- - - -
1100 c	- - - L
1011 b	- - - -
1010 a	- - - -
1001 9	- - - -
1000 8	- - - L
0111 7	- - - -
0110 6	- - H -
0101 5	- - - -
0100 4	- - H L
0011 3	- - - -
0010 2	- N H -
0001 1	- - - -
0000 0	e N H L
*/
		/* �x�� */
		const u8 aaa[4] =
		{
			0xff,	/* easy */
			0x0d,	/* NORMAL */
			0x09,	/* HARD */
			0x03,	/* LUNATIC */
		};
		if ( 0==((REG_10_BOSS_SPELL_TIMER) & aaa[(REG_0f_GAME_DIFFICULTY)] ))
		{
			remilia_oyasumi_kougeki(src);
		}
	}
}


/*---------------------------------------------------------
	���f�u�u���h�E�c�F�y�V���̎􂢁v
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[�e���O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
#define TAMA_DATA_10_TAMA_OKI_KANKAKU	src->hatudan_register_user_data10
local void tamaoki_danmaku_01_callback(SPRITE *src)/* ��u�� */
{
	/*(225==1+224==1+7*32)*/
//	if ((HATUDAN_ITI_NO_JIKAN-224) < src->jyumyou)/* ���e�G�t�F�N�g�ォ��[224]�J�E���g�����̒e */
	if ((HATUDAN_ITI_NO_JIKAN-225) < src->jyumyou)/* ���e�G�t�F�N�g�ォ��[225]�J�E���g�����̒e */
	{
		if (0==(src->hatudan_register_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))/*TAMA_SPEC_AKA_AO_KUNAI_BIT*/
		{	/*CW(���v���)*/
		//	src->rotationCCW1024 -= (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src->rotationCCW1024 -= (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		else
		{	/*CCW(�����v���)*/
		//	src->rotationCCW1024 += (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src->rotationCCW1024 += (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		src->hatudan_register_speed65536	+= (1<<8);			/* �e�� */
	//
	//	if (0==(src->jyumyou&0x0f))/*16���1��e��u��*/
	//	if (0==(src->jyumyou&0x07))/*8���1��e��u��*/
		TAMA_DATA_10_TAMA_OKI_KANKAKU--;
		if (0 > TAMA_DATA_10_TAMA_OKI_KANKAKU)
		{
			TAMA_DATA_10_TAMA_OKI_KANKAKU = REG_09_REG1;//[�萔1]n��Ɉ��e��u���B
			//
		//	REG_02_DEST_X	= (src->cx256); 	/* �e��x256 �{�X���S���甭�e�B */
		//	REG_03_DEST_Y	= (src->cy256); 	/* �e��y256 �{�X���S���甭�e�B */
			set_REG_DEST_XY(src);
			REG_00_SRC_X	= (REG_0c_REG4);
			REG_01_SRC_Y	= (REG_0d_REG5);
			tmp_angleCCW65536_src_nerai();//_bbb(zzz_player, dest);
		//
			/* �e��x256 y256 �e�̒��S���甭�e�B */
		//	set_REG_DEST_XY(src);
			HATSUDAN_01_speed256			= t256(0);	/* �e�� */
			HATSUDAN_02_speed_offset		= t256(0);/*(�e�X�g)*/
		//	HATSUDAN_03_angle65536			= (0);	/* ��p�x */
			HATSUDAN_04_tama_spec			= (DANMAKU_LAYER_02)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_05_bullet_obj_type 	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);		/* [�Ԓe] */
			hatudan_system_regist_single();/* (r33-) */
		}
	}
	else	/* ���e�� 225 �J�E���g�ȏ�͒e�������B */
	{
		/* (�ʏ�e�֕ϐg����) */
		src->hatudan_register_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	danmaku_00_standard_angle_mover(src);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_B_move_angle_001(src);/*(�p�x�e�ړ�)*/
}
/*---------------------------------------------------------
	[�e���O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local void tahane_danmaku_02_callback(SPRITE *src)/* �쒵�� */
{
	if ((HATUDAN_ITI_NO_JIKAN-128) == src->jyumyou)/* ���e�G�t�F�N�g�ォ��[128]�J�E���g �̒e */
	{
		src->hatudan_register_speed65536 = (1<<16); 		/* �e�� */
		/* (�ʏ�e�֕ϐg����) */
		src->hatudan_register_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	danmaku_00_standard_angle_mover(src);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_B_move_angle_001(src);/*(�p�x�e�ړ�)*/
}
/*---------------------------------------------------------
	[�������Z�N�V����]
	-------------------------------------------------------
	[�萔1]n��Ɉ��e��u���B
	0easy:			16
	1normal:		12
	2hard:			8
	3lunatic:		4
---------------------------------------------------------*/
local void spell_init_28_remilia_tama_oki(SPRITE *src)
{
//	TAMA_DATA_10_TAMA_OKI_KANKAKU	= (0);// �J�E���^
	REG_09_REG1 	= ( (16)-((REG_0f_GAME_DIFFICULTY)<<2));//[�萔1]n��Ɉ��e��u���B
//	REG_09_REG1 	= (t256(1.5)+((REG_0f_GAME_DIFFICULTY)<<6));//[�萔1]�J�̑��x
//	REG_0a_REG2 	= ((1024/2)+(1024/24)+(REG_0f_GAME_DIFFICULTY<<3));//[�萔2]�ԐN�i�C���Ȃ���p�x
//	card.danmaku_callback[0] = danmaku_00_standard_angle_mover;/*(�ʏ�e�p)*/
	card.danmaku_callback[1] = tamaoki_danmaku_01_callback;/*(��u���p)*/
	card.danmaku_callback[2] = tahane_danmaku_02_callback;/*(�쒵�˗p)*/
//	card.danmaku_callback[3] = NULL;/*(���g�p)*/
}

/*---------------------------------------------------------
	[���e�Z�N�V����]
	-------------------------------------------------------
	����(r35)�̃X�y�J�V�X�e���̏ꍇ�A�d�l��
	�X�y�J���܂����郌�W�X�^�l��ێ��ł��Ȃ��B
	(�X�y�J���n�܂�^�C�~���O�ŋ����I�Ƀ��W�X�^��0�N���A����Ă��܂���)
	-------------------------------------------------------
	�g�p���W�X�^:
	REG_0c_REG4 	���e��A�W�܂�X���W(t256�`��)
	REG_0d_REG5 	���e��A�W�܂�Y���W(t256�`��)
---------------------------------------------------------*/
local void spell_create_28_remilia_tama_oki(SPRITE *src)
{
	if ( (SPELL_TIME_0256-1)==((REG_10_BOSS_SPELL_TIMER) ))/*(��Ԏn��)*/
	{
	//	add_zako_sakuya_doll_02_tama_oki(src);/* ��u���ǉ� */
		HATSUDAN_01_speed256			= t256(1.0);	/* �e�� */
		HATSUDAN_02_speed_offset		= t256(5);/*(�e�X�g)*/
		HATSUDAN_03_angle65536			= 0;	/* ��p�x */
		HATSUDAN_04_tama_spec			= (DANMAKU_LAYER_01)|((ra_nd()) & TAMA_SPEC_KAITEN_HOUKOU_BIT)|(0)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_05_bullet_obj_type 	= BULLET_KNIFE20_04_AOI;		/* [�i�C�t�e] */
		HATSUDAN_06_n_way				= (13); 	/* [13way] */		/* ���e�� */
		HATSUDAN_07_div_angle65536		= (int)(65536/(13));	/* �����p�x(65536[360/360�x]�� 18 ����) */
		hatudan_system_regist_katayori_n_way();/* (r33-) */
		u32 aaa = ra_nd();
		REG_0c_REG4 = ((aaa    )&0xff00) + t256(((480-128-32-256)/2));
		REG_0d_REG5 = ((aaa<<8 )&0xff00) + t256(((272-256)/2));
		#if (1)
	//	voice_play(VOICE15_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
		bullet_play_04_auto(VOICE15_BOSS_KOUGEKI_01);
		#endif
	}
}
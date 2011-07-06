
/*---------------------------------------------------------
 �����͕핗  �` Toho Imitation Style.
  �v���W�F�N�g�y�[�W http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�˖��� ���̒e���𐶐����܂��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	��	�ʏ�U��1(�Ƃ肠�����ʏ�U��2�̃R�s�y)
	-------------------------------------------------------
		��(12)�e
		��(12)�e
		��(12)�e
	-------------------------------------------------------
	�Ƃ肠�����A�܂��������ĂȂ��B
	�Ƃ������A�܂������Ⴄ�B
	�u�ʏ�U��1�v�͂悭�킩��Ȃ��B�̂ŁA�F�X�ς����Ⴄ�Ǝv���B
---------------------------------------------------------*/

static void danmaku_create_15_aya_misogi1(SPRITE *src)
{
//	if ((0x10)==((src->boss_base_danmaku_time_out)&0x1f))/* (16���1��)(128�Ȃ�v8��) */
	if ((0x40)==((src->boss_base_danmaku_time_out)&0x7f))/* (16���1��)(128�Ȃ�v8��) */
	{
		#if (1)
	//	voice_play(VOICE14_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
		bullet_play_04_auto(VOICE14_BOSS_KOUGEKI_01);
		#endif
	//
#if 0/*�S���ʒe*/
		{
			tmp_angleCCW65536_src_nerai(obj_player, src);/*���@�_���p�쐬*/
			br.BULLET_REGIST_speed256			= (t256(1.75)); 									/* �e�� */	/* 3.5 2.5 2.0*/
			br.BULLET_REGIST_angle65536 		= (src->tmp_angleCCW65536); 								/* ���@�_���e */
			br.BULLET_REGIST_div_angle65536 	= (int)(65536/(6*8))/* HOUGA_12_RED_DIV_ANGLE */;	/*(int)(1024/(48))*/	/* �����p�x(1024[360/360�x]�� 48 ����) */	/* 1����n���������p�x */
			br.BULLET_REGIST_bullet_obj_type	= BULLET_KOME_01_AOI;//BULLET_KOME_02_AKA;								/* [�ԐF�Ēe] */
			br.BULLET_REGIST_n_way				= (6*8)/* HOUGA_08_RED_NUMS */; 		/*(48)*/				/* [48way] */	/* ���e�� */
			br.BULLET_REGIST_speed_offset		= t256(0);/*�Ă���*/
		//	br.BULLET_REGIST_regist_type		= REGIST_TYPE_00_MULTI_VECTOR;/*���ݎ�ނ�����*/
			bullet_regist_angle();
		}
#endif
	}
//	if ((0x02)==((src->boss_base_danmaku_time_out)&0x03))/* (2���1��)(8�񖈂ɔ��e) */
//	if ((0x08)==((src->boss_base_danmaku_time_out)&0x0f))/* (2���1��)(8�񖈂ɔ��e) */
	if ((0x08)==((src->boss_base_danmaku_time_out)&0x0f))/* (2���1��)(8�񖈂ɔ��e) */
	{
		static int aaa_angle65536;
		static int bbb_angle65536;
//		br.BULLET_REGIST_speed256			= (t256(1.75)); 										/* �e�� */		/*3.5 2.5 2.0*/
//		br.BULLET_REGIST_speed256			= (t256(0.75)); 										/* �e�� */		/*3.5 2.5 2.0*/
		br.BULLET_REGIST_div_angle65536 	= (int)(65536/(2))/* HOUGA_04_YEL_DIV_ANGLE */; 		/*(int)(1024/(6))*/ 	/* �����p�x(1024[360/360�x]�� 6 ����) */	/* 1����n���������p�x */
		br.BULLET_REGIST_n_way				= (2)/* HOUGA_00_YEL_NUMS */;				/*(6)*/ 				/* [1way] */	/* ���e�� */
//		br.BULLET_REGIST_speed_offset		= t256(0);/*�Ă���*/
	//	br.BULLET_REGIST_regist_type		= REGIST_TYPE_00_MULTI_VECTOR;/*���ݎ�ނ�����*/
//
	//	#define NUM_12_OF_CIRCLE_ONE	(12)/* ���(�����12�e) */
		#define NUM_12_OF_CIRCLE_ONE	(9)
	//	const unsigned int aaa = (((~(src->boss_base_danmaku_time_out))>>3)&0x1f);/* �e�L�g�[�ɑ傫�����Ă݂�B */
		const unsigned int aaa = (((~(src->boss_base_danmaku_time_out))>>3)&0x1f);/* �e�L�g�[�ɑ傫�����Ă݂�B */
		unsigned int jj;
		for (jj=0; jj<(65536);	jj += (65536/NUM_12_OF_CIRCLE_ONE))/* ��� */
		{
				/* ���S���W�Ȃ̂ŁA�I�t�Z�b�g�Ȃ�==�{�X���S����e�o���B */
		//	obj_send1->cx256 					= (src->cx256)+t256(25.0)+(sin65536((jj))*16);				/* �e��x256 */
		//	obj_send1->cy256 					= (src->cy256)+t256(16.0)+(cos65536((jj))*16);				/* �e��y256 */
		//	obj_send1->cx256 					= (src->cx256)+t256(25.0)+(sin65536((jj))*(16+(aaa)));				/* �e��x256 */
		//	obj_send1->cy256 					= (src->cy256)+t256(16.0)+(cos65536((jj))*(16+(aaa)));				/* �e��y256 */
			obj_send1->cx256 					= (src->cx256) +(sin65536((jj))*(16+(aaa)));				/* �e��x256 */
			obj_send1->cy256 					= (src->cy256) +(cos65536((jj))*(16+(aaa)));				/* �e��y256 */
		//�������
			// �����(��CCW������A�����CCW)
			br.BULLET_REGIST_bullet_obj_type	= BULLET_MARU12_02_AOI;//BULLET_KOME_05_KIIRO;								/* [���F�Ēe] */
			br.BULLET_REGIST_angle65536 		= (( (aaa_angle65536))&(65536-1));				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
			br.BULLET_REGIST_speed256			= (t256(0.75)); 										/* �e�� */		/*3.5 2.5 2.0*/
			br.BULLET_REGIST_speed_offset		= t256(0);/*�Ă���*/
			bullet_regist_angle();
		//����
			// �t���(��CCW������A�E���CW)
			br.BULLET_REGIST_bullet_obj_type	= BULLET_MARU12_01_AKA;//BULLET_KOME_05_KIIRO;								/* [���F�Ēe] */
			br.BULLET_REGIST_angle65536 		= (( (bbb_angle65536))&(65536-1));				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
			br.BULLET_REGIST_speed256			= (t256(0.50)); 										/* �e�� */		/*3.5 2.5 2.0*/
			br.BULLET_REGIST_speed_offset		= t256(1);/*�Ă���*/
			bullet_regist_angle();
		}
		// ��]��
		aaa_angle65536 += (int)(	  (65536/(22)));/* HOUGA_16_YEL_ROTATE_ANGLE */ 						/*(1024/(6*8))*/		/* �p�x(1024[360/360�x]�� 48����) */
		bbb_angle65536 += (int)(65536-(65536/(15)));/* HOUGA_16_YEL_ROTATE_ANGLE */ 						/*(1024/(6*8))*/		/* �p�x(1024[360/360�x]�� 48����) */
	}
}


/*---------------------------------------------------------
	��	�ʏ�U��2
	-------------------------------------------------------
	normal
		��(12)�e	CW�e������								�E��45�x����J�n
		��(12)�e	CCW�e���x��(�e��2.5�{���炢�H)		����45�x����J�n
	-------------------------------------------------------
	luna
		��(12)�e	CW�e������								�E��45�x����J�n
		��(12)�e	CCW�e���x��(�e��1.5�{���炢�H)		����45�x����J�n
	-------------------------------------------------------
	???�B
---------------------------------------------------------*/

static void danmaku_create_23_aya_misogi2(SPRITE *src)
{
//	if ((0x10)==((src->boss_base_danmaku_time_out)&0x1f))/* (16���1��)(128�Ȃ�v8��) */
	if ((0x40)==((src->boss_base_danmaku_time_out)&0x7f))/* (16���1��)(128�Ȃ�v8��) */
	{
		#if (1)
	//	voice_play(VOICE14_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
		bullet_play_04_auto(VOICE14_BOSS_KOUGEKI_01);
		#endif
	}
//	if ((0x02)==((src->boss_base_danmaku_time_out)&0x03))/* (2���1��)(8�񖈂ɔ��e) */
//	if ((0x08)==((src->boss_base_danmaku_time_out)&0x0f))/* (2���1��)(8�񖈂ɔ��e) */
	if ((0x08)==((src->boss_base_danmaku_time_out)&0x0f))/* (2���1��)(8�񖈂ɔ��e) */
	{
		static int aaa_angle65536;
		static int bbb_angle65536;
//		br.BULLET_REGIST_speed256			= (t256(1.75)); 										/* �e�� */		/*3.5 2.5 2.0*/
//		br.BULLET_REGIST_speed256			= (t256(0.75)); 										/* �e�� */		/*3.5 2.5 2.0*/
		br.BULLET_REGIST_div_angle65536 	= (int)(65536/(2))/* HOUGA_04_YEL_DIV_ANGLE */; 		/*(int)(1024/(6))*/ 	/* �����p�x(1024[360/360�x]�� 6 ����) */	/* 1����n���������p�x */
		br.BULLET_REGIST_n_way				= (2)/* HOUGA_00_YEL_NUMS */;				/*(6)*/ 				/* [1way] */	/* ���e�� */
//		br.BULLET_REGIST_speed_offset		= t256(0);/*�Ă���*/
	//	br.BULLET_REGIST_regist_type		= REGIST_TYPE_00_MULTI_VECTOR;/*���ݎ�ނ�����*/
//
	//	#define NUM_12_OF_CIRCLE_ONE	(12)/* ���(�����12�e) */
		#define NUM_12_OF_CIRCLE_ONE	(9)
		unsigned int jj;
		for (jj=0; jj<(65536);	jj += (65536/NUM_12_OF_CIRCLE_ONE))/* ��� */
		{
				/* ���S���W�Ȃ̂ŁA�I�t�Z�b�g�Ȃ�==�{�X���S����e�o���B */
		//	obj_send1->cx256 					= (src->cx256)+t256(25.0)+(sin65536((jj))*16);				/* �e��x256 */
		//	obj_send1->cy256 					= (src->cy256)+t256(16.0)+(cos65536((jj))*16);				/* �e��y256 */
			obj_send1->cx256 					= (src->cx256) +(sin65536((jj))*16);				/* �e��x256 */
			obj_send1->cy256 					= (src->cy256) +(cos65536((jj))*16);				/* �e��y256 */
		// [�������]
			// �����(��CCW������A�����CCW)
			br.BULLET_REGIST_bullet_obj_type	= BULLET_MARU12_02_AOI;//BULLET_KOME_05_KIIRO;								/* [���F�Ēe] */
			br.BULLET_REGIST_angle65536 		= (( (aaa_angle65536))&(65536-1));							/* ���˒��S�p�x / ����@�\(���@�_��/��) */
			br.BULLET_REGIST_speed256			= (t256(0.75)); 											/* �e�� */		/*3.5 2.5 2.0*/
			br.BULLET_REGIST_speed_offset		= t256(0);/*�Ă���*/
			bullet_regist_angle();
		// [����]
			// �t���(��CCW������A�E���CW)
			br.BULLET_REGIST_bullet_obj_type	= BULLET_MARU12_01_AKA;//BULLET_KOME_05_KIIRO;								/* [���F�Ēe] */
			br.BULLET_REGIST_angle65536 		= (( (bbb_angle65536))&(65536-1));							/* ���˒��S�p�x / ����@�\(���@�_��/��) */
			br.BULLET_REGIST_speed256			= (t256(0.50)); 											/* �e�� */		/*3.5 2.5 2.0*/
			br.BULLET_REGIST_speed_offset		= t256(1);/*�Ă���*/
			bullet_regist_angle();
		}
		// ��]��
		aaa_angle65536 += (int)(	  (65536/(22)));/* HOUGA_16_YEL_ROTATE_ANGLE */ 						/*(1024/(6*8))*/		/* �p�x(1024[360/360�x]�� 48����) */
		bbb_angle65536 += (int)(65536-(65536/(15)));/* HOUGA_16_YEL_ROTATE_ANGLE */ 						/*(1024/(6*8))*/		/* �p�x(1024[360/360�x]�� 48����) */
	}
}













/*---------------------------------------------------------
	��	�򕄁u�V�̔��ˁv
	-------------------------------------------------------
	�U�wx32�����e
	-------------------------------------------------------
	�����W�J���A�������E22.5/360�x[1��/16����]�͈̔͂͒e�����Ȃ��B

		 /|X
		/ | X
	   /  |  X
	  /   |   X
	 /	  |    X
	/	  | 	X
	22.5  | 22.5
	�e�����Ȃ��͈� == [1��/16����] + [1��/16����]
	����̃X�N�V�����瑪��Ƃ����B
	-------------------------------------------------------
	�����ǁApsp���Ɗp�x���L��������B
	�㉺�؂�Ă���(�Q�[���t�B�[���h��)���L�̉�ʂ�����A�����������񂾂낤�ȁB
	����(�ڂ̍��o):
	�����l���c�Ȃ̕��Ɖ��Ȃ̕��𒅂��ꍇ�A�c�Ȃ̕��̕���(�S�̂�)�ׂ�������B
	�����e���ł����E�g���~���O���ăJ�b�g����ƁA�ڂ̍��o�ōׂ�������B
	�����e���ł��㉺�g���~���O���ăJ�b�g����ƁA�ڂ̍��o�ő���������B
	���̏ꍇ(psp)���������ɓ�������A�ڂ̍��o�ŋɒ[�ɑ���������B
	-------------------------------------------------------
	������Ƃ����āA�p�x�����߂���A�S�̂��k�����Ē�������ƁA�]�v�����Q�ɋ߂Â��C������B
	�l�I�ɂ́A�u����(��)���v����Ԃ�肽�������񂾂��Apsp�̉�ʋ�������A����(r32)����(��)���͖����Q���ۂ��B
	����(��)���͖����Q���ۂ����A����(��)���͂ł���B
	-------------------------------------------------------
	����(��)��:���ɒ���t���Ȃ���A���̗̑͂����U���@�B(�U���n�ȊO��z��B�U���n�ȊO�ōU���ł���)
	����(��)��:�P�ɒe���(��)���邾���A�U���ł��Ȃ��B�U���n�Ȃ�U���ł��邩���m��Ȃ����z��O(����̖͕핗�ł͏o���Ȃ�)�B
	���̒e���͒P�ɒe���(��)���邾���Ȃ�ȒP�B
	-------------------------------------------------------
	����(r32)�ł͍U�����w�b�^������Ȃ��������ɕς��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	��	�򕄁u�V�̔��ˁv(�g��12�ےe��S�e��~�B���݂̍��W��V��_���W�ɕύX����B������ς���)
	-------------------------------------------------------
---------------------------------------------------------*/

static void exchange_damnaku_aya_tomeru(void)
{
//	int check_type;
//	check_type = br.BULLET_REGIST_bullet_obj_type;/* ���ׂ�^�C�v���󂯎�� */
	int ii;
	for (ii=0; ii<SPRITE_444POOL_MAX; ii++ )/* �S�����ׂ�B */
	{
		SPRITE *s;
		s = &obj44[ii];
	//	if (check_type == (s->type) )	/* ���̐e���Ԓe�Ȃ� */
		if (is_tama_grouip08(BULLET_MARU12_00_SIRO) == is_tama_grouip08(s->type) )	/* �g��12�ےe�Ȃ� */
		{
			s->tra65536 					= t256(0);		/* ���������e */
			s->speed65536					= t256(0);		/* �e�� */
		}
	}
}


/*---------------------------------------------------------
	��	�򕄁u�V�̔��ˁv(�g��12�ےe��S�e����������)
	-------------------------------------------------------
	�����e(���m�ɂ͓������e)�Ȃ̂ɁA�����e�Ɍ����Ȃ���
	�����e(���m�ɂ͓����x�e�A����==0)�Ɍ������Ⴄ��肪����B

---------------------------------------------------------*/

static void exchange_damnaku_aya_saikasoku(void)
{
//	int check_type;
//	check_type = br.BULLET_REGIST_bullet_obj_type;/* ���ׂ�^�C�v���󂯎�� */
//	int jj = 0;
	int add_angle = 0;
	int ii;
	for (ii=0; ii<SPRITE_444POOL_MAX; ii++ )/* �S�����ׂ�B */
	{
		SPRITE *s;
		s = &obj44[ii];
	//	if (check_type == (s->type) )	/* ���̐e���Ԓe�Ȃ� */
		if (is_tama_grouip08(BULLET_MARU12_00_SIRO) == is_tama_grouip08(s->type) )	/* �g��12�ےe�Ȃ� */
		{
		//	s_change_meirin_yajirusi_one(s);
			/* �e�̌��ݍ��W���A�V��_���W�Ƃ���B */
			s->tx256 = (s->cx256);		/* ��_���W�ɃZ�b�g */
			s->ty256 = (s->cy256);		/* ��_���W�ɃZ�b�g */
			s->radius256 = t256(0); 	/* ��_���W�ɂȂ����̂Ŕ��a�� 0 �ɂ���B */
			/*	*/
			#if 0
		//	s->rotationCCW1024				= (ra_nd()&((1024)-1)); 			/* ���� */	/* �����͗����łȂ��C������ */
			#else
			/* ���Ȃ��Ƃ��������͖{���ɋ߂��B ���A�S�R�Ⴄ�B */
			/* ���Z�Œ�l(KOTEITI_7777)�ȊO�̗v���Ƃ��āA�e�����X�g�̃T�C�Y�Ń��[�v����ׁA�e�����X�g�̃T�C�Y�� */
			/* ���݂� 1024 ����A�{���Ɠ��� 640 �Ɍ��点�΁A����\���͂���B */
		//	#define KOTEITI_1234 (1234<<6)
			#define KOTEITI_1234 (78976)
			add_angle += (KOTEITI_1234);
		//	s->rotationCCW1024				= (add_angle>>6);			/* ���� */
		//	s->rotationCCW1024				= ((((add_angle>>6)&(512-1))+(256*(4-1)))&(1024-1));			/* ����(��(180/360[�x])�ɂ��������Ȃ�) */
			s->rotationCCW1024				= ((((add_angle>>6)&(256-1))+(128*(8-1)))&(1024-1));			/* ����(��( 90/360[�x])�ɂ��������Ȃ�) */
			#endif
			s->tra65536 					= t256(1);	/* (1) ���������e */
		//	�`���m(�p�[�t�F�N�g�t���[�Y)�̏ꍇ�͐�ɕϐg���邪�A��(�V�̔���)�̏ꍇ�͌�ŕϐg����B
			s->type 						= (BULLET_MARU10_03_AOI);	/* �ےe */
			reflect_sprite_spec444(s, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
		}
	}
}

static void danmaku_create_22_aya_yatimata(SPRITE *src)
{
	if ((32*20)-1==((src->boss_base_danmaku_time_out) ))/* ��1.0[�b](==64flame)�e���W�J */
	{
		//	voice_play(VOICE14_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
			bullet_play_04_auto(VOICE14_BOSS_KOUGEKI_01);
		//
				/* ���S���W�Ȃ̂ŁA�I�t�Z�b�g�Ȃ�==�{�X���S����e�o���B */
	//		obj_send1->cx256 					= (src->cx256)+t256(25.0);				/* �e��x256 */
	//		obj_send1->cy256 					= (src->cy256)+t256(16.0);				/* �e��y256 */
	//		obj_send1->cx256 					= (src->cx256)+t256(16.0);				/* �e��x256 */
	//		obj_send1->cy256 					= (src->cy256)+t256(16.0);				/* �e��y256 */
			obj_send1->cx256 					= (src->cx256);				/* �e��x256 */
			obj_send1->cy256 					= (src->cy256);				/* �e��y256 */
		//	obj_send1->rotationCCW1024			= (src->rotationCCW1024);				/* �e��y256 */
		//
		/* �e���� */
		unsigned int j;
		for (j=0; j<6; j++ )/* �U�w�B */
		{
			br.BULLET_REGIST_speed256				= (t256(0.5) ); 			/* �e��(psp�̉�ʂ͋���) */

			br.BULLET_REGIST_angle65536 			= (65536/16)/* */;			/* ���� */
			br.BULLET_REGIST_div_angle65536 		= ((65536-(65536/8))/32);				/* �����p�x(�e�����Ȃ��͈͂�����32����) */	/* (ra_nd16>>4) == ����(0-4095) */
			br.BULLET_REGIST_bullet_obj_type		= BULLET_MARU12_00_SIRO;	/* �ےe */

			br.BULLET_REGIST_n_way					= (32); 		/* [32way] */			/* 32�����e */

		//	br.BULLET_REGIST_speed_offset			= t256(-5); 		/* (-5) (-3)���������e */	/* ���̕����ɂȂ邩������ */
		//	br.BULLET_REGIST_speed_offset			= t256(-j);/*�Ă���*/
		//	br.BULLET_REGIST_speed_offset			= t256(j<<2);/* x4�{ �Ă���*/
			br.BULLET_REGIST_speed_offset			= (j<<(2+8));/* x4�{ �Ă���*/
		//	br.BULLET_REGIST_regist_type			= REGIST_TYPE_00_MULTI_VECTOR;		/* ���݂��ꂵ���Ȃ����v�� */
			bullet_regist_angle();	/* �p�x�e�Ƃ��ēo�^ */
		}
	}
	else
	if ((32*18)==((src->boss_base_danmaku_time_out) ))/* ��0.33[�b](==20flame)��~ */
	{
		/* �����ł͌��ʉ��Ȃ� */
		/* �S�e��~ */
		exchange_damnaku_aya_tomeru();/*�S�ăX�g�b�v*/
	}
	else
	if (/*(32*17)*/((32*18)-20)==((src->boss_base_danmaku_time_out) ))/* �~�܂��Ă���20flame�� */
	{
		/* �~�܂����������A�����n�߂鎞�Ɍ��ʉ��炵������������ۂ��B */
		#if (1)
	//	voice_play(VOICE14_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
	//	bullet_play_04_auto(VOICE11_BOSS_KIRARIN);		/* ���ʉ�: ������ */
		voice_play(VOICE11_BOSS_KIRARIN, TRACK03_SHORT_MUSIC);		/* ���ʉ�: ������ */
		voice_play(VOICE11_BOSS_KIRARIN, TRACK04_TEKIDAN);			/* ���ʉ�: ������ */
		/* �厖�Ȏ��Ȃ̂łQ�񌾂��܂����B */
		#endif
		/* �ړ� */
		exchange_damnaku_aya_saikasoku();/*�ĉ���*/
	}

}



/*---------------------------------------------------------
	�Ǖ�c�u�R�_�n��v(normal)
	�Ǖ��u�V��V���̏ƚ��v(luna)
	-------------------------------------------------------
	���񂺂����ĂȂ�...
---------------------------------------------------------*/
// 4096 == 65536/16
// 3855.05882352941176470588235294118 == 65536/17
//	240.941176470588235294117647058824 == ((65536/16)-(16636/17)) ����
static void danmaku_create_26_aya_saifu(SPRITE *src)
{
	static unsigned int zzz;
	static	 signed int ggg;
	if ((DANMAKU_9999_TIME-1)==((src->boss_base_danmaku_time_out) ))/* ������ */
	{
		zzz = 64;
		ggg = 0;
	}
	ggg--;
	if (0 > ggg)
	{
		ggg = zzz;
		#define min_24zzz (26)
		zzz -= difficulty;
		if (min_24zzz > zzz)		{	zzz = min_24zzz;		}
		#undef min_24zzz
	{
				/* ���S���W�Ȃ̂ŁA�I�t�Z�b�g�Ȃ�==�{�X���S����e�o���B */
		obj_send1->cx256 					= (src->cx256);				/* �e��x256 */
		obj_send1->cy256 					= (src->cy256);				/* �e��y256 */
	//	obj_send1->cx256 					= (src->cx256)+t256(25.0);				/* �e��x256 */
	//	obj_send1->cy256 					= (src->cy256)+t256(16.0);				/* �e��y256 */
		//
//		br.BULLET_REGIST_speed256			= (t256(1.00)); 										/* �e�� */
		br.BULLET_REGIST_speed256			= (t256(0.50)); 										/* �e�� */
		br.BULLET_REGIST_div_angle65536 	= (int)(65536/(16*5));	/* �����p�x(65536[360/360�x]�� 8 ����) */	/* 1����n���������p�x */
		br.BULLET_REGIST_angle65536 		= ((0));				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		{	const unsigned int cc_type[4] =
			{
				BULLET_MARU8_05_MIDORI,
				BULLET_MARU8_00_SIRO, 			// �Ǖ��u�R�_�n��v(normal)
				BULLET_KOME_06_KI_IRO,
				BULLET_KOME_06_KI_IRO,			// �Ǖ��u�V��V���̏ƚ��v(luna)
			};
			br.BULLET_REGIST_bullet_obj_type	= cc_type[difficulty];								/* [ �e] */
		}
		br.BULLET_REGIST_n_way				= (16*5);			/*(6)*/ 				/* [1way] */	/* ���e�� */
//		br.BULLET_REGIST_speed_offset		= t256(0);/*�Ă���*/
		br.BULLET_REGIST_speed_offset		= t256(1);/*�Ă���*/
	//	br.BULLET_REGIST_regist_type		= REGIST_TYPE_00_MULTI_VECTOR;/*���ݎ�ނ�����*/
		bullet_regist_angle();
	}
	}
//	if ((0x02)==((src->boss_base_danmaku_time_out)&0x03))/* (2���1��)(8�񖈂ɔ��e) */
	if ((0x04)==((src->boss_base_danmaku_time_out)&0x07))/* (2���1��)(8�񖈂ɔ��e) */
	{
		static unsigned int bbb;
		bbb += 77;
		static unsigned int aaa;
		aaa++;
		aaa &= (0x07);
		if (0==aaa) 	{	aaa++;	};
		//
				/* ���S���W�Ȃ̂ŁA�I�t�Z�b�g�Ȃ�==�{�X���S����e�o���B */
		obj_send1->cx256 					= (src->cx256);				/* �e��x256 */
		obj_send1->cy256 					= (src->cy256);				/* �e��y256 */
	//	obj_send1->cx256 					= (src->cx256)+t256(25.0);				/* �e��x256 */
	//	obj_send1->cy256 					= (src->cy256)+t256(16.0);				/* �e��y256 */
		//
//		br.BULLET_REGIST_speed256			= (t256(1.00)); 										/* �e�� */
		br.BULLET_REGIST_speed256			= (t256(0.50)); 										/* �e�� */
	//	br.BULLET_REGIST_div_angle65536 	= (int)(65536/(16))-(((sin1024(( ra_nd() & src->boss_base_danmaku_time_out)))&0xff));		/*(int)(1024/(6))*/ 	/* �����p�x(1024[360/360�x]�� 6 ����) */	/* 1����n���������p�x */
		br.BULLET_REGIST_div_angle65536 	= (int)(65536/(16/*8*/));	/* �����p�x(65536[360/360�x]�� 8 ����) */	/* 1����n���������p�x */
//		br.BULLET_REGIST_angle65536 		= ((65536/2));				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		{	const unsigned int ba_type[4] =
			{
				BULLET_KOME_03_AOI,
				BULLET_KOME_03_AOI, 		// �Ǖ��u�R�_�n��v(normal)
				BULLET_UROKO14_05_KIIRO,
				BULLET_UROKO14_05_KIIRO,	// �Ǖ��u�V��V���̏ƚ��v(luna)
			};
			br.BULLET_REGIST_bullet_obj_type	= ba_type[difficulty];								/* [ �e] */
		}
	//	br.BULLET_REGIST_n_way				= (17); 			/*(6)*/ 				/* [1way] */	/* ���e�� */
		br.BULLET_REGIST_n_way				= (16/*8*/);			/*(6)*/ 				/* [1way] */	/* ���e�� */
//		br.BULLET_REGIST_speed_offset		= t256(0);/*�Ă���*/
		br.BULLET_REGIST_speed_offset		= t256(1);/*�Ă���*/
	//	br.BULLET_REGIST_regist_type		= REGIST_TYPE_00_MULTI_VECTOR;/*���ݎ�ނ�����*/
//
//		br.BULLET_REGIST_angle65536 		= (int)((65536*1/4))+(src->boss_base_danmaku_time_out&0xff);				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		br.BULLET_REGIST_angle65536 		= ((bbb));				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		if (0==((src->boss_base_danmaku_time_out)&0x08))
		{
//			br.BULLET_REGIST_angle65536 		= (int)((65536*3/4))+(src->boss_base_danmaku_time_out&0xff);				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
			br.BULLET_REGIST_angle65536 		= -(bbb);				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		}
		bullet_regist_angle();
	}
}

/*---------------------------------------------------------
	��	�댯�Ȏ�e	�l�`�e��
	-------------------------------------------------------
	�e�L�g�[
---------------------------------------------------------*/
extern void add_zako_aya_doll(SPRITE *src);/* ���l�`�e�� */
static void danmaku_create_0f_aya_doll(SPRITE *src)
{
	if (50==((src->boss_base_danmaku_time_out) ))
	{
		#if (1)
	//	voice_play(VOICE14_BOSS_KOUGEKI_01, TRACK04_TEKIDAN);
		bullet_play_04_auto(VOICE14_BOSS_KOUGEKI_01);
		#endif
	//
		add_zako_aya_doll(src);
	}
}

#if 0
/*---------------------------------------------------------
	��ʒe
---------------------------------------------------------*/

static void bullet_create_aya_kougeki_03(SPRITE *src)
{
	s_bullet_create_aya_oodama3(src, /*�d�l�ύX*/(t256(4.0)+(difficulty<<7))/*, 10*/);
}


/*---------------------------------------------------------
	�댯�Ȏ�e
---------------------------------------------------------*/

static void bullet_create_aya_kougeki_02(SPRITE *src)
{
	add_zako_aya_doll(src);
};
#endif

/*---------------------------------------------------------
	�J�~��e
	-------------------------------------------------------
---------------------------------------------------------*/

static void danmaku_create_2a_amefuri_test(SPRITE *src)
{
	if (0==((src->boss_base_danmaku_time_out)&0x03))	// 4�J�E���g��1����8way�e������
	{
				/* ���S���W�Ȃ̂ŁA�I�t�Z�b�g�Ȃ�==�{�X���S����e�o���B */
		obj_send1->cx256 						= (src->cx256);
		obj_send1->cy256 						= (src->cy256);
	//	obj_send1->cx256 						= (src->cx256)+t256(25.0);
	//	obj_send1->cy256 						= (src->cy256)+t256(50.0);
		//
		unsigned int j;
		for (j=(0); j<(8); j++)
		{
			/* �V���b�g */
		//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
			br.BULLET_REGIST_speed256				= (t256(1.5)+(difficulty<<6));
			br.BULLET_REGIST_angle1024				= (1024/4)+(1024/8)+(j<<5)+((src->boss_base_danmaku_time_out>>2)&0x3f);
//			br.BULLET_REGIST_div_angle1024			= (int)(1024/64);
//	//		br.BULLET_REGIST_bullet_obj_type		= BULLET_CAP16_04_KOME_SIROI;			/* [���Ēe] */	/* �e�O�� */
	//		br.BULLET_REGIST_n_way					= (8);					/*(4-difficulty)*/
//	//		br.BULLET_REGIST_regist_type			= REGIST_TYPE_02_GRAVITY02;
			br.BULLET_REGIST_jyuryoku_dan_delta256	= ((ra_nd()&0x03)+2);//t256(0.04)
			br.BULLET_REGIST_bullet_obj_type		= (BULLET_KOME_03_AOI); 	/* �e�O�� */
			br.BULLET_REGIST_regist_type			= REGIST_TYPE_02_GRAVITY02;
			bullet_regist_vector();
		}
	}
}
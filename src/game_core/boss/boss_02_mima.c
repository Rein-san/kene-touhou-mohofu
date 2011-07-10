
#include "boss.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	�v���W�F�N�g�y�[�W http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	����
	Mitei Madakimattenai.
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	�{�X�s���A�� 1�`��
---------------------------------------------------------*/
extern void add_zako_mima_dolls(SPRITE *src);
global void mima_01_keitai(SPRITE *src)
{
	static int mima_zako_tuika_timer = 0;	/* �G���A�ǉ��^�C�}�[�B�ǉ��Ԋu�����܂�Z�����Ȃ��B */
	if (0<mima_zako_tuika_timer)
	{
		mima_zako_tuika_timer--;
	}
	//
	static int mima_jikan;	/* �J�[�h�ǉ��^�C�}�[�B�e�L�g�[�B */
	mima_jikan--;
	/* �J�[�h�������ĂȂ��ꍇ�ɒǉ� */
//	if (SPELL_00==card.card_number) 	/* �J�[�h�����I���Ȃ�J�[�h���� */
	if (0 > mima_jikan) 				/* �J�[�h�����I���Ȃ�J�[�h���� */
	{
		const unsigned char aa_ra_nd = ra_nd();
		if (0==(aa_ra_nd&0x03))
		{
			if (0==mima_zako_tuika_timer)
			{
			//	mima_zako_tuika_timer = (128);
				mima_zako_tuika_timer = (256);
				add_zako_mima_dolls(src);
			}
		}
		mima_jikan = /*(123)*/(64) + (aa_ra_nd&0x3f);
		//
		src->BOSS_DATA_05_boss_base_state777++;
		src->BOSS_DATA_05_boss_base_state777 &= (8-1);
	//	if (0!=(src->BOSS_DATA_05_boss_base_state777))/*(r32)*/
		if (0!=(aa_ra_nd & 0xc0))/*(r33)*/
		{
			static const POINT_u16 hosi_no_zahyou[(8)] = /* �ڕW���W */
			{	/* {(x),(y)}, */
				{(171),( 18)},	/* ��l�������� */
				{(202),( 92)},	/* �k�l����(5)�� */
				{(257),(107)},	/* �k�l����(6)�� */
				{(339),( 74)},	/* �k�l����(7)�� */
				{(	5),(116)},	/* �k�l����(1)�� */
				{(	6),( 46)},	/* �k�l����(2)�� */
				{(107),( 26)},	/* �k�l����(3)�� */
				{(133),( 78)},	/* �k�l����(4)�� */
			};
			/* �ړ����W�����߂� */
			src->BOSS_DATA_00_target_x256 = ((hosi_no_zahyou[src->BOSS_DATA_05_boss_base_state777].x)<<8);
			src->BOSS_DATA_01_target_y256 = ((hosi_no_zahyou[src->BOSS_DATA_05_boss_base_state777].y)<<8);
			/* �J�[�h�����߂� */
			card_maikai_init_and_get_spell_number(src); 	/* ���݂̌`�ԂŌ��Ă�J�[�h�ԍ����J�[�h�V�X�e���ɐݒ�B */
		}
		else
		{
			/* �ړ����W�����߂� */
			SPRITE *zzz_player;
			zzz_player = &obj99[OBJ_HEAD_02_KOTEI+FIX_OBJ_00_PLAYER];
			src->BOSS_DATA_00_target_x256 = (zzz_player->cx256);
			#if 0
		//	if (t256(16.0) > (src->BOSS_DATA_01_target_y256))
			if ( (((zzz_player->cy256)-t256(16.0))>>16) )
			{
				src->BOSS_DATA_01_target_y256 = t256(16.0);
			}
			else
			#endif
			{
				src->BOSS_DATA_01_target_y256 = (zzz_player->cy256);
		//		src->BOSS_DATA_01_target_y256 -= t256(8.0); 	/* ??? ���̂��I�������Ȃ��B */
			}
			#if 1
			/* �J�[�h�����߂� */
			card.card_number	= SPELL_19_mima_sekkin; 	/* �J�[�h���Z�b�g */
			card_maikai_init(src);/*(r35-, �J�[�h�̏������B�J�[�h���ς��Ɩ���s���K�v������)*/
			#endif
		}
		src->BOSS_DATA_04_toutatu_wariai256 = t256(1.0);	/* �U���A�j���[�V���� */
	}
	boss_yuudou_idou_nomi(src);
	boss_yuudou_hiritu_keisan(src);
}
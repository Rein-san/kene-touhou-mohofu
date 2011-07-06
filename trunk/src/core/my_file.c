
#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗	�` Toho Imitation Style.
	�v���W�F�N�g�y�[�W http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�t�@�C���֘A����
	-------------------------------------------------------
	�t�@�C���֘A�̃T�|�[�g���[�`���́A�����ɋL�q���Ă��������B

	�G�o���f�[�^�[(dat/xxxx.txt)�t�@�C���ǂݍ���
	�V�i���I�X�N���v�g(text/xxxx.txt)�t�@�C���ǂݍ���
	�n�C�X�R�A�t�@�C���ǂݍ��݁^�ۑ�
	�ݒ�ǂݍ��݁^�ۑ�
	��ʕۑ�
---------------------------------------------------------*/

#include "111_my_file.h"
//#include <malloc.h>/* free(); */

// '|' ',' ',' const char kugiri_1_char
#define KUGIRI_KAMMA_1_CHAR 		(',')
#define COMMENT_SEMIKORON_1_CHAR	(';')

/*---------------------------------------------------------
	shift jis�R�[�h�A�S�p1�o�C�g�ڂ��ǂ������肷��q�֐�
---------------------------------------------------------*/

/*static*/global int is_kanji_1st(/*unsigned char*/int/*int*/ high_byte)
{
	#if 1
	high_byte &= 0xff;/**/
	return (
		((high_byte >= 0x81) && (high_byte <= 0x9f)) ||
		((high_byte >= 0xe0) && (high_byte <= 0xfd))
	);
	#else
	high_byte ^= 0x20;
	high_byte += (0x100-0xa1);
	high_byte &= 0xff;/**/
	return (high_byte < 0x3du);
	#endif
}


/*---------------------------------------------------------
	�X�N���v�g�t�@�C���̕����񕔕��̓ǂݍ���
	-------------------------------------------------------
	shift jis ������2byte�ڂ������̏ꍇ��
	�G�X�P�[�v�V�[�N�G���X������2byte�ڂ������̏ꍇ�ł�
	��肪�Ȃ�
---------------------------------------------------------*/

/*static*/global char *load_my_file_get_str(char *str, char *buffer, int *end_arg)
{
	int string_error_limiter;
	string_error_limiter = 200;/* 200 �����ȏ�̓G���[ */
	/*unsigned char*/int high_byte;
	{loop:;
		high_byte = ((*str) & 0xff);
		/* �󕶎���̉\�������邩��A�n�߂ɔ��� */
		if (KUGIRI_KAMMA_1_CHAR == high_byte)	/* ','��؂�ł����܂��̏ꍇ */
		{
			goto kamma_end;
		}
		else
		if (13 == high_byte)	/* '\n'==13(�s��)�ł����܂��̏ꍇ */
		{
	//	ret13_end:
			*end_arg = 1;/* �s���ł��B */
		kamma_end:
			*buffer = '\0'; 	/* EOS ��ǉ� */
			return (str);
		}
		else					/* �������]������K�v�̂���ꍇ */
		{
			int flag;
			flag = 0;
			if (is_kanji_1st(high_byte)) /* shift jis ���� */
			{
				;	//	*buffer++ = *str++;/* 1byte�� */
			}
			else
			{
				if ('\\' == high_byte)		/* �G�X�P�[�v�V�[�N�G���X����(escape sequence) */
				{
					;	//	*buffer++ = *str++;/* ���� */
				}
				else					/* ���p���� */
				{
					flag = 1;
				}
			}
			if (0==flag)	/* ���p�����ȊO(shift jis �����A�G�X�P�[�v�V�[�N�G���X����)�� 2 byte�]�� */
			{
				*buffer++ = *str++;
			}
			*buffer++ = *str++; 	/* 1 byte�͕K���]�� */
			/* �G���[�`�F�b�N */
			{
				string_error_limiter--;
				if (0 >= string_error_limiter)
				{
					return ((char *)NULL);
				}
			}
		}
		goto loop;
	}
}


/*---------------------------------------------------------
	�ėp���̂܂�łȂ��ǂݍ��݊֘A�B�q�֐�
	-------------------------------------------------------
	�W�����o�͂�psp�ł͒x������̂�sce�̊֐����g���B(�Q�[�����̏��������y����)
	�G���[�`�F�b�N�Ƃ��S�R�����̂Œ��ӂ̎�
---------------------------------------------------------*/

//atic char buffer_text_1_line[128];	/* parth text, 1 line buffer */ 	/* ��������s�̎擾 */
/*static*/ char buffer_text_1_line[256];	/* parth text, 1 line buffer */ 	/* ��������s�̎擾 */
/*static*/ char my_fopen_file_name[256];	/* fopen����t�@�C���� (128) */
#if 1
static unsigned long file_size;
static unsigned long file_seek;
//static char *my_buf;
//static void *malloc_buf;
static char *malloc_buf;

/*static*/global void *my_fopen(void/*const char *my_fopen_file_name*/ /*, const char *dummy*/)
{
	SceUID fd;
	fd = sceIoOpen((char *)my_fopen_file_name, PSP_O_RDONLY, 0777);
	if (0 == fd)
	{
		goto error111;
	}
	file_size = sceIoLseek32(fd, 0, PSP_SEEK_END);
	file_seek = 0;

	malloc_buf = malloc(file_size);
	if (NULL == malloc_buf)
	{
		sceIoClose(fd);
		goto error111;
	}
	sceIoLseek32(fd, 0, PSP_SEEK_SET);
	sceIoRead( fd, malloc_buf, file_size);
	sceIoClose(fd);
//	my_buf = malloc_buf;
//
	return (malloc_buf);
error111:
	return (NULL);
}
global int my_file_now_size(void)
{
	return (file_size);
}


static int my_fgets(void/*char *buffer_name, int num, char *wfp*/)
{
	int ii;
	ii = 0;
	char aaa;
//	char bbb;
//bbb=0;
	fgets_loop:;
	aaa = /*buffer_name*/buffer_text_1_line[ii] = /*my_buf*/malloc_buf[file_seek]/*(*my_buf)*/;
//	my_buf++;
	ii++;
	file_seek++;
	if (0x0a == aaa)	return (1);
	if (file_size < file_seek)	return (0)/*NULL*/;
	goto fgets_loop;
//	error(ERR_FATAL, "TEST %s\nno: %d (%s)",buffer_name,errno,strerror(errno));
//	return (NULL);
}
/*static*/global int my_file_fgets(void/*char *buffer_name, int num, char *wfp*/)
{
ggg_loop:;
	int ii;
	ii = my_fgets();
	/* ';'�Ŏn�܂�s�̓R�����g�s�Ȃ̂ŁA�������Ȃ��Ŏ��̍s�܂Ŕ�΂��B */
	if (COMMENT_SEMIKORON_1_CHAR == (buffer_text_1_line[0]))
	{	goto ggg_loop;/*continue;*/ }
	return (ii);
}
/*static*/global void my_fclose(void/*void *wfp*/)
{
	free(malloc_buf);
}
//(????)
	/*static*/global void my_fseek_begin(void/*void *wfp*/)
	{
	//	file_seek = 0;
	}
#else
	#define my_fopen	fopen
	#define my_fgets	fgets
	#define my_fclose	fclose
#endif

//#define FILE_NAME_SETTING_TXT "setting.ini"
#define FILE_NAME_SETTING_TXT	DIRECTRY_NAME_DATA_STR "/setting.txt"


/*---------------------------------------------------------
	�n�C�X�R�A�t�@�C���֘A����
---------------------------------------------------------*/

/*---------------------------------------------------------
	�ݒ�t�@�C���֘A����
---------------------------------------------------------*/
static int ini_load_item(/*FILE *fp,*/ char *search, char *str_result)
{
//	char buffer_text_1_line[128];		/* �s�o�b�t�@ */
	char item_name[32/*30*/];			/* �R���t�B�O���ږ� */
//	int int_result; int_result = -1;
	/* ��������� */
	my_fseek_begin();//fseek(fp, 0L, SEEK_SET);
	{loop:;
	//	while (/*NULL*/0 != fgets(buffer_text_1_line,128,fp))
	//	if (/*NULL*/0 != fgets(buffer_text_1_line,128,fp))
		if (/*NULL*/0 != my_file_fgets(/*buffer_text_1_line,128,fp*/))
		{
			char *ch;					/* �����ʒu */
			ch = buffer_text_1_line;
			/* skiped lines. */
			#if 0
			/* '\n'�������̂��I�������Ȃ�(???) */
			if ('\n'==(*ch))		{	goto loop;/*continue;*/ }	/* ���s�݂̂̍s�͋�s�Ȃ̂ł��Ȃ��łƂ΂� */
			while (isspace(*ch))	{	ch++;					}	/* �󔒂�TAB������ */
			#else
			{my_isspace:;
				if (' '>=(*ch))
				{
					ch++;
					if (0x0a==(*ch))
					{	goto loop;/*continue;*/ }	/* skiped null line. */
					else
					{	goto my_isspace;	}
				}
			}
			#endif
			/* ';'�Ŏn�܂�s�̓R�����g�s�Ȃ̂ŁA���̍s�܂Ŕ�΂��B */
//			if (COMMENT_SEMIKORON_1_CHAR==(*ch))	{	goto loop;/*continue;*/ }	/* ';'�Ŏn�܂�s�̓R�����g�Ȃ̂ł��Ȃ��łƂ΂� */
			//
		//	error(ERR_FATAL, "test %s\n", c );/*test k0a,1 */
			//
			{char *sc = item_name;
				int i=0;
				while (KUGIRI_KAMMA_1_CHAR != (*ch))	/* ��؂�',' ��T�� */
				{
					i++;
					if (30 < i) 	{	return (-1);	}	/* >= 30 ����������G���[ */
					*sc++ = *ch++;
				}
				ch++;		/* ��؂�',' �𖳎� (',' �̕����Ƃ΂�) */
				*sc = 0;	// '\0' ��ǋL�B  NULL
			}
			//
		//	error(ERR_FATAL, "test %s | %s\n", c, item_name);/*test 1\n | k0a  */
			//
			if (0==tiny_strcmp(item_name, search))
			{
				if (NULL==str_result) // �Ώۂ𐮐��Ƃ��ĉ�͂���B(PARTH_MODE_INT) */
				{
					char re_s[32/*30*/];
					char *re_e = re_s;
				//	while ('\n' != (*ch))		/* int�̕��͐�������Ȃ����͔r�����Ă����݂�����������Ȃ��B(13�łȂ���ok) */
					while (0x0a != (*ch))		/* int�̕��͐�������Ȃ����͔r�����Ă����݂�����������Ȃ��B(13�łȂ���ok) */
					{
						*re_e++ = *ch++;
					}
					re_e = 0;
					/*int_result =*/return (atoi(re_s));
//					goto my_exit;
			//		break;
				}
				else // �Ώۂ𕶎���Ƃ��ĉ�͂���B (PARTH_MODE_CHAR) */
				{
					char *re_e = str_result;
				//	while (0x0d != (*ch)/*13*/) /* char�̕���\n����Ȃ���13�ɂ��Ȃ��Ƃ����Ǝ���Ă���Ȃ���B(13�łȂ���ng) */
					while (0x0a != (*ch))		/* char�̕���\n����Ȃ���13�ɂ��Ȃ��Ƃ����Ǝ���Ă���Ȃ���B(13�łȂ���ng) */
					{
						*re_e++ = *ch++;
					}
					re_e = 0;
					/*int_result =*/return (1);/* ok */
//					goto my_exit;
			//		break;
				}
			}
			goto loop;
		}
	}
//my_exit:
//	return (int_result);
	return (-1);/* ������Ȃ�������G���[ */
}


static const char *my_config_title[OPTION_CONFIG_08_MAX]=
{
	"player",
	"bomb",
	"bgm",
	"sound",
	"current_difficulty",
	"current_player",
	"analog",
	"open",
};
//extern char str_pa ss_word[]; 	/* [***090222 */
extern int select_player;
extern void set_default_key(int *key_setting_map, int key_setting_type);
extern void set_default_option(int *option_setting_map);
extern void check_limit_value_option(int *option_setting_map);
global void ini_load(void)
{
	#if 1
	// �v�]���������̂őS�͂őΉ�
//	sceIoMkdir(const char *aaa_dir, SceMode mode);
	sceIoMkdir("ms0:/PICTURE", 0777);	/* "ms0:/PICTURE"���Ȃ��ꍇ�A
	"ms0:/PICTURE/�����͕핗"�����Ȃ��̂ŁA�K���K�v�B
	�Ȃ��ꍇ�A���������̂ł͂Ȃ��āA�ň��u�n���O�A�b�v�����肷��v�B
	(SDL���̂������ċC�����邯��???)
	*/
//	sceIoMkdir("ms0:/PICTURE/�����͕핗/", 0777);/* �o���Ȃ� */
	sceIoMkdir("ms0:/PICTURE/�����͕핗", 0777);/* �o���� */
	#endif

//	FILE *fp;
//	char my_fopen_file_name[128/*64 50*/];
//	strcpy(my_fopen_file_name, "./" FILE_NAME_SETTING_TXT);
	strcpy(my_fopen_file_name, FILE_NAME_SETTING_TXT);
	int tmp;
	int int_result;
	int_result = 0;/* �ُ� */
	int ng1;
	ng1 = 0;/*fopen()����*/
//
//	if ( NULL == /* fp =*/ fopen(my_fopen_file_name, "r"))
	if ( NULL == /* fp =*/ my_fopen(/*my_fopen_file_name, "r"*/))
	{
		ng1 = 1;/*fopen()���s*/ goto error00;/* return (-1); */
	}
	/* �L�[�R���t�B�O�ݒ�̓ǂݍ��� */
	{
		char bufaaa[4];
		bufaaa[0] = 'K';
		bufaaa[1] = '0';
//		bufaaa[2] = ('a'+i);
		bufaaa[3] = 0;
		int i;
		for (i=0; i<KEY_NUM12_MAX; i++)
		{
			bufaaa[2] = ('a'+i);
		//
		//	CONFIG_LOAD_ITEM( bufaaa,				pad_config[i]	);
			tmp = ini_load_item(/*fp,*/ bufaaa, NULL);
			if (-1 != tmp)	{	pad_config[i] = tmp;	}
			else			{	goto error00/*return (-1)*/;	}
		}
	}
	/* �I�v�V�����ݒ�̓ǂݍ��� */
	{
		int i;
		for (i=0; i<OPTION_CONFIG_08_MAX; i++)
		{
		//	CONFIG_LOAD_ITEM( (char *)my_config_title[i],				option_config[i]	);
			tmp = ini_load_item(/*fp,*/ (char *)my_config_title[i], NULL);
			if (-1 != tmp)	{	option_config[i] = tmp; }
			else			{	goto error00/*return (-1)*/;	}
		}
	}
	int_result = 1;/* ���� */
//
error00:
	/* high_score load */
	{	int ng2;
		int tmpscore;
		ng2 = ng1;
		tmpscore = 0;
		char tmp_str_pl[8];
		//-----------------01234567
		strcpy(tmp_str_pl,"SCORE00");
		tmp_str_pl[7] = 0;/* �O�̈� */
//
		int j;
		for (j=0; j<MAX_8_SAVE_PLAYERS; j++)
		{
			tmp_str_pl[5] = '0'+j;/* PLAYER */
			int i;
			for (i=0; i<5; i++)
			{
				tmp_str_pl[6] = '0'+i;/* score rank number. ���� */
				if (0==ng2)
				{
				//#define tmp_str32 buffer_text_1_line
					char tmp_str32[64/*50*/];
				//	if (1 == fscanf(fp, "%23s\n", tmp_str32 ))
				//	if (0 != my_fgets(/*fp, "%23s\n", tmp_str32*/ ))
					int aaa;
					aaa = ini_load_item(tmp_str_pl, tmp_str32 );
					if (-1 != aaa)
					{
						/* ���ߍ��� */
						high_score_table[j][i].final_stage = tmp_str32[1/*10*/]-('0');

					//	strncpy(high_score_table[j][i].name, &tmp_str32[10], 3);
						high_score_table[j][i].name[0] = tmp_str32[2/*10*/];
						high_score_table[j][i].name[1] = tmp_str32[3/*11*/];
						high_score_table[j][i].name[2] = tmp_str32[4/*12*/];
						high_score_table[j][i].name[3] = tmp_str32[5/*13*/];
//
						high_score_table[j][i].name[4] = tmp_str32[6/*14*/];
						high_score_table[j][i].name[5] = tmp_str32[7/*15*/];
						high_score_table[j][i].name[6] = tmp_str32[8/*16*/];
						high_score_table[j][i].name[7] = tmp_str32[9/*16*/];
						char tmp_str16[64/*50*/];
						strcpy(tmp_str16, &tmp_str32[10/*5 13*/]);
						tmpscore = atoi(tmp_str16);
//						tmpscore /= 10;
					}
					else/* �G���[ */
					{
						ng2 = 1;
					}
				}
			/*	else // ���O�� ini_load_item() �ŃG���[���N�����ꍇ�ɏ���������̂� ����else�����B */
			//	if (1==ng2) /* psp��0���W�X�^������̂�0�Ɣ�r�����ق������� */
				if (0!=ng2)
				{
					high_score_table[j][i].final_stage = (6-i); 	/* ���B�X�e�[�W */
					static const int init_score_tbl[5] =
					{
						score(100000000),	//	score(70000000),		//score(50000000),
						score( 50000000),	//	score(60000000),		//score(4000000),
						score( 10000000),	//	score(50000000),		//score(300000),
						score(	5000000),	//	score(10000000),		//score(20000),
						score(	1000000),	//	score( 5000000),		//score(1000),
					};
				//	strcpy(high_score_table[j][i].name,"12345678"/*"DEN"*/);
				//	strcpy(high_score_table[j][i].name,"ZUN     "/*"DEN"*/);
					strcpy(high_score_table[j][i].name,"NANASHI "/*"DEN"*/);
					tmpscore = init_score_tbl[i];
				}
				high_score_table[j][i].score = tmpscore;
			}
		}
	//	top_score = high_score_table[0][0].score;	// ��ɕ\������n�C�R�A�̎擾=>score.c�ŗ��p
	}
//
	if (0==ng1)
	{
		my_fclose (/*fp*/); 	//fclose(fp);
	}
	//return (int_result)/*1*/;

	if (0==(int_result)) // 090110
	{
//		chooseModDir();
		set_default_key(pad_config, 0/*0==type 01 �͕핗 �W��*/);
		set_default_option(option_config);/* OPTION_CONFIG_00_PLAYER ���� OPTION_CONFIG_03_SOUND �܂Őݒ� */
	//	option_config[OPTION_CONFIG_04_CURRENT_DIFFICULTY]	= 0;
	//	option_config[OPTION_CONFIG_05_CURRENT_PLAYER]		= 0;
	//	option_config[OPTION_CONFIG_06_ANALOG]				= 0;
		option_config[OPTION_CONFIG_07_OPEN]				= 0x0500;
	}
//
	/* �͈͊O�`�F�b�N(�͈͊O�̏ꍇ�͏C��) */
	check_limit_value_option(option_config);/* */
	/* �ǂݍ��񂾃f�[�^�[�ŏ����ݒ� */
	difficulty		= option_config[OPTION_CONFIG_04_CURRENT_DIFFICULTY];
	select_player	= option_config[OPTION_CONFIG_05_CURRENT_PLAYER];
//	if (-1 == ini_load_item(/*fp,*/ "pa ssword", st r_pass_word))	{	goto error00;/* return (-1); */ 	}

	#if 1/*�C������*/
//	�͈͊O�̏ꍇ�͏C��
//	if (difficulty>3 || 0>difficulty)/* (easy)0 1 2 3(Lunatic) */
//	{	difficulty = 0/* 0==easy 2*/;}
	difficulty		&= 0x03;
	select_player	&= 0x07;
	#endif
}



static void write_buf(/*FILE *fp*/SceUID fd, char *str_buf)
{
//	const char k = 13;
//	fprintf(fp, "%s%c\n", str_buf,	k);
	char *str_buf_head;
	str_buf_head = str_buf;
	unsigned int len;
	len = 0;
	while (0!=(*str_buf))
	{
		len++;
		str_buf++;
	};
	/* �������͕핗�̃t�@�C���`����[CR+LF]�������̂Ō݊������B */
	*str_buf=0x0d;	len++;	str_buf++;/*[CR]*/
	*str_buf=0x0a;	len++;	str_buf++;/*[LF]*/
//	fprintf(fp, "%s\n", str_buf);
	sceIoWrite(fd, str_buf_head, len/*sizeof(int)*/ /**save_data_size*/ /*, 1, fp*/);
}
global void ini_save(void)
{
//	FILE *fp;
//	char buf[64/*50*/];
	char buf[128/*64 50*/];
	strcpy(buf, "./" FILE_NAME_SETTING_TXT);
//	fp = fopen(buf, "w");
	SceUID fd = sceIoOpen(buf, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
//	if (fd < 0)
//	{
//		/*"�Z�[�u�f�[�^���Ȃ��B"*/
//	}
//	if ( NULL == fp)	{	return; 	}
//

	/* ���̂��I���s���Ȃ� */
	#define USE_MEMO (0)
	#if (1==USE_MEMO)
	//---------------------------
	strcpy(buf,
		"; �����͕핗(r32) configuration file.\n"
		";---------------------------\n"
		"\n"
		"; �L�[�R���t�B�O�ݒ�\n"
	);
	write_buf(/*fp,*/fd, buf);
	#endif	/* (USE_MEMO) */
	//
	{
		unsigned int i;
		for (i=0; i<KEY_NUM12_MAX; i++)
		{
			sprintf(buf,
				"K0%c,%d",
				('a'+i),
				pad_config[i]);
			write_buf(/*fp,*/fd, buf);
		}
	}
	//---------------------------
	#if (1==USE_MEMO)
	strcpy(buf, "; �I�v�V�����ݒ�\n" );
	write_buf(/*fp,*/fd, buf);
	#endif	/* (USE_MEMO) */
	option_config[OPTION_CONFIG_04_CURRENT_DIFFICULTY]	= difficulty;
	option_config[OPTION_CONFIG_05_CURRENT_PLAYER]		= select_player;

	{
		unsigned int i;
		for (i=0; i<OPTION_CONFIG_08_MAX; i++)
		{
			sprintf(buf,
				"%s,%d",
				my_config_title[i],
				option_config[i]);
			write_buf(/*fp,*/fd, buf);
		}
	}
	//---------------------------
	#if (1==USE_MEMO)
	strcpy(buf, "; ���̋L�^\n" );
	write_buf(/*fp,*/fd, buf);
	#endif	/* (USE_MEMO) */
	/* high_score save */
	{unsigned int j;
		for (j=0; j<MAX_8_SAVE_PLAYERS; j++)
		{	unsigned int i;
			for (i=0; i<5; i++)
			{
				sprintf(buf,
					"SCORE" 		/* == dummy */
					"%c"			/* player number */
					"%c"			/* rank number */
					"," 			/* == ��؂� dummy */
					"0" 			/* practice mode */
					"%c"			/* final stage */
					"%8s"			/* name */
					"%09d"/*"0"*/,	/* score */
				//
					(j+'0'),		/* player number */
					(i+'0'),		/* score rank number */
									/* practice mode */
					(high_score_table[j][i].final_stage+'0'),				/* final stage */
					high_score_table[j][i].name,
					high_score_table[j][i].score
				);	write_buf(/*fp,*/fd, buf);
			}
		}
	}
	sceIoClose(fd);/*	fclose(fp);*/
}

/*---------------------------------------------------------
	��ʕۑ��@�\
---------------------------------------------------------*/
extern void gu_save_screen(void);
global void save_screen_shot(void)
{
	static int screen_num = 0;
/*static*/ char screen_buf[64/*32 20*/];
//	sp rintf(screen_buf,"ms0:/PICTURE/Toho_Moho%d.bmp", screen_num);		// �ۑ��ꏊ�̕ύX�B
//	strcpy(screen_buf,"ms0:/PICTURE/�����͕핗/Toho_MohoZ.bmp");	//	�u33�����ڂ��������������v
//	strcpy(screen_buf,"ms0:/PICTURE/kene/MohoZ.bmp");	/* "ms0:/PICTURE/kene/"�̍쐬���@���킩��Ȃ� */
//	strcpy(screen_buf,"ms0:/PICTURE/Toho_MohoZ.bmp");				//	�u22�����ڂ��������������v
	strcpy(screen_buf,"ms0:/PICTURE/�����͕핗/�X�N�V��_Z.bmp");	//	�u33�����ڂ��������������v
//	-------------------0123456789012345678901234567890123
//	-------------------0000000000111111111122222222223333
	screen_num++;
	screen_num &= 0x1f;
	screen_buf[33/*22*/]= ((9+1)<screen_num)?(('A'-(9+1)-1)+screen_num):(('0'-1)+screen_num);
	gu_save_screen();
	SDL_SaveBMP(sdl_screen[SDL_00_VIEW_SCREEN], screen_buf);
	psp_clear_screen();
}
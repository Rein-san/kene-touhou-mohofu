#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "game_main.h"

//static extern int thescript(void);
extern int script_init(char *filename, char *bg_name,int width);

/* SDL_FreeSurface(); �� psp�ł͑��������Ɠ����Ȃ��̂� ���̑΍� */
extern void script_system_init(void);/* �g�ݍ��� */
extern void script_system_exit(void);/* �O�� */



/* �O�����烁�b�Z�[�W�E�B���h�E�Ɋ�����`�悷��ꍇ�̃��Z�b�g */
extern void script_message_window_clear(void);

/* �O�����烁�b�Z�[�W�E�B���h�E�Ɋ�����`���B */
//static extern int print_kanji(SDL_Surface *drawmap, SDL_Rect *rect, const char *str, int color_type, int wait);
extern /*static*/ int print_kanji(/*SDL_Surface *drawmap,*/ SDL_Rect *rect, const char *str, int color_type, int wait);

#endif /* _SCENARIO_H_ */
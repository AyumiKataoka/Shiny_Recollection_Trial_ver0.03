#ifndef __GAMETITLE_H__
#define __GAMETITLE_H__

#include <DxLib.h>
#include "main.h"

#define TITLE_MOVE_START_MAX_FLAME 120				// �wSTART�x�I��������R�~�����[�h�ֈڍs����̂ɕK�v�ȃt���[����
#define TITLE_MENU_MESSAGE_X 480					// �^�C�g����ʃ��j���[�I�����̂w���W�i���j
#define START_MESSEAGE_Y 60						// �wSTART�x�x���W
#define CONFIG_MESSEAGE_Y (START_MESSEAGE_Y + 200)	// �wCONFIG�x�x���W�i���j
#define EXIT_MESSAGE_Y (CONFIG_MESSEAGE_Y + 200)	// �wEXIT�x�x���W�i���j
#define TITLE_MENU_MESSAGE_SPACE_Y 290				// �^�C�g����ʂ̊e���j���[��y���W�Ԋu
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icft=click_flag_title�j
// �Ȃ���saveload�t�@�C���̃R�[�h�Ɏg���Ă����̂ł��̂܂�
extern BOOL cft_exit_main_commu;		// �R�~����ʂɈړ�
extern BOOL cft_quit_game;				// �Q�[�����I��
extern BOOL cft_sound_room_main_commu;	// �T�E���h���[����ʂɈړ�
extern BOOL cft_commu_list;				// �R�~�����X�g��ʂɈړ�
//extern BOOL cft_commu_edit;				// �R�~���G�f�B�b�g��ʂɈړ�

extern BOOL flag_next_start;	// �j���[�Q�[���J�n���̈ړ������t���O

extern int next_start_frame_count;	// �wSTART�x�I������̌o�߃t���[����

extern float coordinat_title_choice_left;		// �����I�����n�_x���W
extern float coordinat_title_choice_right;		// �E���I�����n�_x���W
extern float coordinat_title_choice_load_y;		// �I�����wLOAD�xy���W
extern float coordinat_title_choice_config_y;	// �I�����wCONFIG�xy���W
extern float coordinat_title_choice_exit_y;		// �I�����wEXIT�xy���W

void GameTitleNext();				// �^�C�g����ʏ�Ԉȍ~����
void GameTitle();					// GameTitle��Ԃ̃��C������
void GameTitleControl();			// �^�C�g����ʑ��쏈��
void GameTitleFlame();				// �^�C�g�����[�h���P�t���[�����ɍs���鏈��
void GameTitleCoordinateSetting();	// �^�C�g����ʂŎg���l�X�ȍ��W���i�āj��`����
void DrawGameTitle();				// �^�C�g����ʂ̕`�揈��

int DrawTitleStringColor(float x, float y, int breadth, float length);	// �^�C�g�����j���[�̕����F��Ԃ�

#endif

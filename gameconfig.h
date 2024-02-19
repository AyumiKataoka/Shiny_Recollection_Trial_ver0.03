#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#include <DxLib.h>
#include "main.h"

#define CONFIG_MESSEAGE_GRAPH_MODE_X 100	// ��ʃ��[�h�x�_X���W
#define CONFIG_MESSEAGE_GRAPH_MODE_Y 100	// ��ʃ��[�h�x�_Y���W
#define CONFIG_MESSEAGE_TITLE_Y 100			// �wTITLE�x�x���W
#define CONFIG_LINE_SPACE 72				// �ݒ胂�[�h�s��
#define CONFIG_MESSAGE_SPEED_NUMBER 3		// ���b�Z�[�W�X�s�[�h�I������

// �I�v�V�������ځw��ʃ��[�h�x�̎��
enum IMGOptionWindowType
{
	IO_WINDOW_TYPE_FULL_SCREEN,	// �t���X�N
	IO_WINDOW_TYPE_WINDOW		// �E�B���h�E
};

extern char* config_message_message_speed[3];	// �ݒ胂�[�h�ŕ`�悳���w�����X�s�[�h�x�I���̕����̎��

extern BOOL config_before_mc;	// ���C���R�~������ݒ胂�[�h�ɗ�����
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfc=click_flag_config�j
extern BOOL cfc_move_title;				// �^�C�g����ʂֈړ�
extern BOOL cfc_window_mode_change[2];	// �E�B���h�E�A�t���X�N���[����؂�ւ���
extern BOOL cfc_screen_change_720p;		// �E�B���h�E�𑜓x��720px�ɂ���
extern BOOL cfc_screen_change_1080p;	// �E�B���h�E�𑜓x��1080px�ɂ���
extern BOOL cfc_bgm_down;				// �a�f�l���ʂ�������
extern BOOL cfc_bgm_up;					// �a�f�l���ʂ��グ��
extern BOOL cfc_se_down;				// �r�d���ʂ�����
extern BOOL cfc_se_up;					// �r�d���ʂ𑝉�
extern BOOL cfc_message_slow;			// ���b�Z�[�W���x��x��
extern BOOL cfc_message_fast;			// ���b�Z�[�W���x�𑬂�
extern BOOL cfc_dialog_change;			// �_�C�A���O�{�b�N�X�\���t���O��؂�ւ�
extern BOOL cfc_text_window_clear[2];	// ���b�Z�[�W���ߓx�𑝌�

extern float config_retu2_x;									// �Q��ڍ���X���W
extern float config_coordinate_icon_back_x;						// �wBACK�x�A�C�R�����[x���W
extern float config_coordinate_icon_back_y;						// �wBACK�x�A�C�R����[y���W
extern float config_coordinate_full_screen_switch_x[2];			// �t���X�N���[���؂�ւ��X�C�b�`X���W
extern float config_coordinate_full_screen_switch_y;			// �t���X�N���[���؂�ւ��X�C�b�`Y���W
extern float config_coordinate_screen_resolution_switch_y;		// ��ʉ𑜓x�؂�ւ��X�C�b�`Y���W
extern float config_coordinate_screen_resolution_switch_1920_x;	// ��ʉ𑜓x�؂�ւ��X�C�b�`�i1920�~1080�jX���W
extern float config_bgm_message_y;								// �a�f�l���ʊ֌WY���W
extern float config_coordinate_arrow_down_x;					// ����󍶒[X���W
extern float config_bgm_volume_up_x;							// �a�f�l�w���x����X���W
extern float config_se_message_y;								// �r�d���ʊ֌WY���W
extern float config_message_speed_y;							// �R�~�����b�Z�[�W���x�֌WY���W
extern float config_text_window_clear_y;						// �e�L�X�g�E�B���h�E���ߓx�֌WY���W
extern float config_coordinate_message_speed_x[3];				// ���b�Z�[�W���x�I�����e���[x���W

void GameConfigNext(BOOL x);						// �ݒ胂�[�h�ڍs����
void GameConfig();										// GAME_CONFIG��Ԃ̃��C������
void GameConfigControl();								// �ݒ��ʎ����쏈��
void GameConfigMessageSpeedChange(BOOL x);				// �R�~���̕����X�s�[�h�Ɋւ���v�f��ύX����
void CoordinateSetting();								// �Q�[���Ŏg���l�X�ȍ��W���i�āj��`����
void GameConfigCoordinateSetting();						// �ݒ��ʂŎg���l�X�ȍ��W���i�āj��`����
void DrawGameConfig();									// �ݒ��ʎ��`�揈��
void DrawOptionArrow(int x , int y, float z, BOOL a);	// �ݒ胂�[�h�̖���`�悷��ۂ̋��ʏ���
#endif

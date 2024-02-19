#ifndef __GAMEMAINCOMMUNICATION_H__
#define __GAMEMAINCOMMUNICATION_H__

#include <DxLib.h>
#include "main.h"

#define COMMU_MESSEAGE_TITLE_Y 100	// �wTITLE�x�x���W
#define	COMMU_CHARACTER_MAX 3			// �R�~���ŕ`�悳���L�����N�^�[�̍ő�l��
// �䎌��`�悷��ۂɕK�v�ȃ|�C���g�̐ݒ�ɉ����������ʁi�P�����ɂ�60�K�v�łP�t���[����x�|�C���g��������j
#define COMMU_COUNT_SLOW 8		// �x��
#define COMMU_COUNT_NORMAL 12	// ����
#define COMMU_COUNT_FAST 30		// ����

#define COMMU_CHARACTER_CHANGE_MAX 60		// �L�����ύX�����Ɏg���t���[����
#define COMMU_CHARACTER_CHANGE_MAX_FAST 30	// �L���������ύX�����Ɏg���t���[����
#define COMMU_EYE_ANIMATION_FLAME 6			// �u���A�j���[�V�����̂P�����f���t���[����
#define COMMU_MOUSE_ANIMATION_NUMBER 13		// ���p�N�֘A�̏����ɕK�v�Ȓ萔
#define COMMU_MOUSE_ANIMATION_FLAME 6		// ���p�N�A�j���[�V�����̂P�����f���t���[����
#define COMMU_BACKGROUND_FLAME_MAX 60		// �w�i�ύX�����Ɏg���t���[�����̍ő�l
#define COMMU_CHARACTER_SPACE 630.0f		// ���E�ɂ����ۂ̈ړ��s�N�Z����

enum CommuStatusType
{
	// �ʏ�A				�t���[�����ɂ�鎩���i�s�A	�I�[�g���ʉ��A		�I����
	COMMU_STATUS_NORMAL,	COMMU_STATUS_AUTO,			COMMU_STATUS_SE,	COMMU_STATUS_ALTENATIVE
};
extern CommuStatusType g_commustatus;
// �\���I�����̎�ށi���j
enum AltenativeNumberType
{
	// �Q�A				�R��
	ALTENATIVE_NUMBER_2,	ALTENATIVE_NUMBER_3
};
extern AltenativeNumberType g_altenativenumber;
// �R�~�������i�s��Ԃ̎��
enum CommuAutoType
{
	// �ʏ�A			�I�[�g�A		�X�L�b�v
	COMMU_AUTO_NORMAL,	COMMU_AUTO_ON,	COMMU_AUTO_SKIP
};
extern CommuAutoType g_commuauto;
// �`�悳���L�����̓���\��^�C�v
enum CommuCharacterFaceType
{
	// �ʏ�A	���ځA		�Ί����
	CCF_NORMAL, CCF_CLOSE_EYE,	CCF_CLOSE_EYE_SMILE
};
extern CommuCharacterFaceType g_commu_character_face[3];

class AlternativeCoordinate
{
	static float y_upper;	// �㑤y���W	
	static float y_under;	// ����y���W
public:
	static void SetYUpper(float x) { y_upper = x; }
	static void SetYUnder(float x) { y_under = x; }
	static float GetYUpper() { return y_upper; }
	static float GetYUnder() { return y_under; }
};
// �e�L�X�g���O
class TextLog
{
	char character[32] = "";			// �䎌��
	char line[128] = "";				// �䎌
	int line_number = 0;				// �R�~�����ł̍s
	static BOOL mode;					// �\��������t���O
	static int top_id_now;				// ���ݍŏ㕔�ɕ\������Ă���䎌�̂h�c�ԍ�
	static int next_input_id;			// ���ɂh�c��������ԍ�
	static int page;					// �y�[�W��
	static const int PAGES_LINE_NUMBER;	// �P�y�[�W���̑䎌��
public:
	void Input();	// �e�L�X�g���O����͂���
	static void Draw();	// �`�悷��
	static void SetMode(BOOL x) { mode = x; }
	static void SetPage(int x);
	static void Reset();
	char* GetLine() { return line; }
	static BOOL GetMode() { return mode; }
	static int GetNIID() { return next_input_id; }
	static int GetPage() { return page; }
	static int GetPagesLineNumber() { return PAGES_LINE_NUMBER; }
};
extern class TextLog text_log[];

extern BOOL commu_mode_background;	// �r�d���ς�肫��܂ŃN���b�N����ł��Ȃ��悤�ɂ���t���O
extern BOOL commu_mode_distance;	// �\������Ă���L�������Q�l�̍ہA�ϓ��ɕ��ׂ邩
extern BOOL commu_mode_menu;		// ���j���[�̓��e��\������
extern BOOL commu_mode_text_off;	// �e�L�X�g�t�@�C���܂߂��S�Ă̂t�h���\���ɂ���
extern BOOL commu_before_cs;		// �R�~���̉{�����n�߂�O�̓R�~���Z���N�g���[�h�����������ʂ���
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfgmc=click_flag_game_main_communication�j
extern BOOL cfgmc_move_title;		// �^�C�g����ʂֈړ�
extern BOOL cfgmc_cell_count;		// �R�~���̏������̂��̂�
extern BOOL cfgmc_change_auto;		// �I�[�g���[�h�؂�ւ���
extern BOOL cfgmc_change_skip;		// �X�L�b�v���[�h�؂�ւ���
extern BOOL cfgmc_exit_save;		// �Z�[�u���[�h�ֈڍs
extern BOOL cfgmc_exit_load;		// ���[�h���[�h�ֈڍs
extern BOOL cfgmc_exit_option;		// �ݒ胂�[�h�ֈڍs
extern BOOL cfgmc_change_menu;		// ���j���[���[�h�؂�ւ���
extern BOOL cfgmc_change_text_off;	// �e�L�X�g�I�t���[�h�؂�ւ���

extern char String[][256];																					// ������`��p�e�X�g�R�[�h
extern char* commu_bgm_name;																				// �R�~���ła�f�l���Đ����ꂽ�ہA�\������閼�O

extern int CursorX, CursorY;	// ���z��ʏ�ł̕����\���J�[�\���̈ʒu
extern int KeyWaitFlag;			// �{�^�������҂��t���O
extern int Count;				// �t���[���J�E���^

extern int commu_number;											// ���ݎQ�Ƃ���Ă���R�~���h�c
extern int cell_number;												// �Q�Ƃ����Z���̍s��
extern int commu_character[3];										// �`�悳���L����
extern int commu_character_blink_limit[3];							// �܂΂��������I����܂ł̎c��t���[����
extern int commu_character_talk_limit[3];							// ���p�N�����I����܂ł̎c��t���[����
extern int commu_character_before[3];								// �؂�ւ��O�̃L�����N�^�[
extern int commu_character_after[3];								// �؂�ւ���̃L�����N�^�[
extern int commu_character_visibility_count[COMMU_CHARACTER_MAX];	// �L�����N�^�[�s�����x�؂�ւ�����������܂ł̃t���[����
extern int commu_background;										// �w�i
extern int commu_background_before;									// �؂�ւ��O�̔w�i
extern int commu_background_visibility_count;						// �w�i�؂�ւ�����������܂ł̃t���[����
extern int commu_bgm_flame;											// �a�f�l���؂�ւ���Ă���̌o�߃t���[����
extern int commu_altenative_string_line[3];							// �e�I�����̍s��
extern int commu_message_point;										// �䎌��`�悷��ۂɕK�v�ȃ|�C���g
extern int commu_auto_count;										// �I�[�g���[�h�Ŏ��s�Ɏ����ōs�����߂̃J�E���g
extern int commu_frame_auto_count;									// �wframe_auto�x�Ŏ��s�Ɏ����ōs�����߂̃J�E���g
extern int text_window_clear_percentage;							// �e�L�X�g�E�B���h�E���ߓx

extern float commu_play_time;						// �v���C���ԁi�b�j
extern float commu_altenative_string_center_x[3];	// �I���������񒆐Sx���W
extern float commu_coordinate_icon_auto_x;			// �wauto�x�A�C�R��x���W
extern float commu_coordinate_icon_auto_y;			// �wauto�x�A�C�R��y���W
extern float commu_coordinate_icon_skip_y;			// �wSKIP�x�A�C�R����[y���W
extern float commu_coordinate_icon_save_y;			// �wSAVE�x�A�C�R����[y���W
extern float commu_coordinate_icon_load_y;			// �wLOAD�x�A�C�R����[y���W
extern float commu_coordinate_icon_option_y;		// �wOPTION�x�A�C�R����[y���W
extern float commu_coordinate_icon_menu_y;			// �wMENU�x�A�C�R����[y���W
extern float commu_coordinate_icon_tf_x;			// �wTEXT OFF�x�A�C�R�����[x���W

void GameMainCommunicationNext(int x, BOOL y, int z);	// �R�~����ʈڍs����
void GameMainCommunication();							// GameMainCommunication��Ԃ̃��C������
void GameMainCommunicationControl();					// �R�~����ʑ��쏈��
void GameMainCommunicationAuto();						//	�I�[�g���[�h���n�m�ɂȂ�ۂ̏���
void GameMainCommunicationFlame();						// �R�~�����[�h���P�t���[�����ɍs���鏈��
void GameMainCommunicationNextLine();					// �R�~����ԂŁA���s�̏������s��
void GameMainCommunicationEnd();						// �R�~���I������
void GameMainCommunicationAltenative(int x);			// �I������I�񂾍ۂ̋��ʏ���
void GameMainCommunicationCoordinateSetting();			// �R�~����ʂŎg���A�C�R���̍��W���i�āj��`���鏈��
void GameMainCommunicationMoji(BOOL x);					// �R�~����ʂŕ�����`�悷�邽�߂ɍs������
void GameMainCommunicationMojiAltenative(int x);		// �R�~����ʂőI�����p������`�悷�邽�߂ɍs������
void DrawGameMainCommunication();						// �R�~����ʂ̕`�揈��
void DrawTextWindow(int x);								// �e�L�X�g�E�B���h�E��`�悷��

int DrawGameMainCommunicationMouseAnimation(int i);		// �`�悷����p�N�̉摜�𔻕ʂ���
#endif

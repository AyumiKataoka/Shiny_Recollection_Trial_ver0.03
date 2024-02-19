#ifndef __MAIN_H__
#define __MAIN_H__

#include <DxLib.h>
#include <ctime>
#include <cstdlib>	// �����irand()�j�����̂��߂ɕK�v
#include <iostream>
#include <math.h>	// �ݏ�v�Z�̂��߂ɕK�v
#include <sys/stat.h>	// �t�@�C�������݂��邩���ׂ邽�߂ɕK�v
#include <fstream>
#include <filesystem>

//#include "gamemain.h"
#include "loading.h"
#include "functionprogram.h"
#include "gametitle.h"
#include "gamemaincommunication.h"
#include "gamemap.h"
#include "gamemusic.h"
#include "gameconfig.h"
#include "gamesaveload.h"
#include "gametutorialend.h"
#include "soundroom.h"
#include "gamecommuselect.h"
#include "gamecommuedit.h"
#include "globaldefinition.h"
#include "radiobutton.h"
// �f�o�b�O�A�������p
#include "debugprogram.h"

#define PI 3.1415926535897932384626433832795f	// �~����
//#define MODE_NUMBER 8							// ���[�h�̐��i�p�Y���A�G���h���X�A�A�[�P�[�h�A�u�r�A�ݒ�A�����A�I���j
#define MODE_DEFAULT_X 100			// �e���[�h��`�悷�镶���̐�ΓI�w���W���l
#define MODE_DEFAULT_Y 180						// �e���[�h��`�悷�镶���̐�ΓI�x���W���l�i�������j
#define MODE_CHANGE_Y 33						// �e���[�h��`�悷��ۂ̂x���W�̂���i�������j
#define WINDOW_SIZE_X 1920						// �Q�[���E�B���h�E�̃I���W�i���T�C�Y����
#define WINDOW_SIZE_Y 1080						// �Q�[���E�B���h�E�̃I���W�i���T�C�Y�c��
#define	SAVE_DATA_NUMBER 60						// �Z�[�u�f�[�^���i�I�[�g�Z�[�u�͏����j
#define COMMU_NUMBER_MAX 256					// �쐬�ł���R�~���̍ő吔
#define COMMU_MAP_LIMIT 10						// �}�b�v��ʂň�����R�~���̏��
#define CS_COMMU_LIMIT 10						// �R�~���Z���N�g��ʂň�����R�~���I�����̏��

#define MOJI_SIZE 24	// �����̃T�C�Y
// ���z�e�L�X�g�o�b�t�@�̉��T�C�Y�c�T�C�Y
#define STRBUF_WIDTH 50	// ���X��48���������V���j���R�I�Ɂw��s�ő�25�����x�Ə�����Ă����̂ŁA������ɍ��킹��悤�ɏC��
#define STRBUF_HEIGHT 20

#define STR(var) #var
// �O���[�o���ϐ�
// ���Ԍv���p�ϐ�
extern int g_lasttime;
extern float g_frametime;
extern int g_timerstart;

enum GameState
{
	GAME_FIRST_LOAD,	GAME_OPENING,	GAME_TITLE,		GAME_MENU,			GAME_MAIN_COMMUNICATION,	
	GAME_MAP,			GAME_CONFIG,	GAME_SAVELOAD,	GAME_TUTORIAL_END,	GAME_SOUNDROOM,
	GAME_COMMU_SELECT,	GAME_COMMU_EDIT,
	GAME_CLEAR,			
	GAME_PAUSE,			GAME_WINNERMESSAGE,
	GAME_TUTORIAL,		GAME_CONTINUE,		GAME_DEMONSTRATION,	GAME_ENDING,
};
extern GameState g_gamestate;
enum SaveFileID
{
	SAVE_ID_NULL, SAVE_ID_001
};
extern SaveFileID g_saveid;
// ���b�Z�\�W���x�̎��
enum CommuMessageSpeedType
{
	// �x���A					���ʁA						����
	COMMU_MESSAGE_SPEED_SLOW, COMMU_MESSAGE_SPEED_NORMAL, COMMU_MESSAGE_SPEED_FAST
};
extern CommuMessageSpeedType g_commumessagespeed;
// �N���b�N����`�F�b�N�̎��
enum ClickFlagCheckType
{
	// �ʏ�i����ȏ������Ȃ��j�A	�R�~����ԁE���j���[�֌W�A	�R�~����ԁE�e�L�X�g�I�t���[�h�֌W
	CFC_NORMAL,						CFC_COMMU_MENU,				CFC_COMMU_TEXT
};
// �R�~���̎�ށi���O�j
enum class CommuType
{
	OP,
	TUTORIAL,
	STILL_OP,		// �X�`���̌��ŗpOP
	MEGURU0,		// 0�͏o��R�~��
	MEGURU1,
	MEGURU2,
	MEGURU5,
	KOGANE0,		// 0�͏o��R�~��
	KOGANE1,
	KOGANE2,
	KOGANE_STILL,
	JURI0,			// 0�͏o��R�~��
	JURI1,
	JURI2,
	JURI_STILL,
	RINZE0,			// 0�͏o��R�~��
	RINZE1,
	RINZE2,
	CHIYUKI0,		// 0�͏o��R�~��
	CHIYUKI1,
	CHIYUKI2,
	CHIYUKI_STILL,
	FRIEND,				// �t�����h�R�~��
	TUTORIAL_END,		// �̌��ŏI��
	TUTORIAL_STILL_END,	// �X�`���̌��ŏI��
	TEST1,
	TEST2,
	TEST3,
	TEST4,
	TEST5,
	EDIT
};

#pragma region �\����
// �Z�[�u�f�[�^��ۑ����邽�߂ɕK�v�ȍ\���́i�ǂ����Ă��Ō��ȊO�̏ꏊ�ɗv�f�𑝂₵�����Ȃ珑�����ݗp�̍\���̂�ʌɗp�ӂ���H�j
struct SystemData
{
	BOOL full_screen;					// �t���X�N���[���̃t���O
	BOOL screen_resolution;				// �𑜓x�̃t���O�iTRUE�Ȃ�1080px�j
	int vol_bgm;						// �a�f�l����
	int vol_se;							// �r�d����
	int text_window_clear;				// �e�L�X�g�E�B���h�E�����x
	CommuMessageSpeedType string_speed;	// �����X�s�[�h
	BOOL dialog_appear;					// �_�C�A���O�{�b�N�X�\���t���O
	void SetECL(int x, BOOL y) { edit_character_load[x] = y; };
	BOOL GetECL(int x) { return edit_character_load[x]; }
private:
	BOOL edit_character_load[9];		// �G�f�B�b�g���[�h�ł̌ʓǂݍ��݃t���O�i�������������X�����G�̐l�����ǉ�����邩������Ȃ��̂ő����ݒ肵�Ă���j
};
extern SystemData system_data;
// �R�~���̃X�e�[�^�X�i�R�~���̎�ނ̔z��ϐ��͏㕔�ɂ���wCommuType�xenum�N���X�j
struct CommuData
{
	// ����̃R�~�������\�������^�C�~���O�̎��
	enum class MapUpperType
	{
		DEFAULT = 3,
		MEGURU0 = 5,
		KOGANE0,
		JURI0,
		RINZE0,
		CHIYUKI0,
		FRIEND_CG_MEGURU
	};
	int id;					// �R�~���h�c
	char path[256];			// �p�X
	//const char* path;		// �p�X
	char title[256];		// �R�~���^�C�g��
	int appear_timing;		// �o���^�C�~���O
	int character_icon;		// �L�����N�^�[�A�C�R��
	int map_zone;			// ���݃}�b�v�ꏊ
	float map_coordinate_x;	// ���S����̏o���w���W����
	float map_coordinate_y;	// ���S����̏o���x���W����
	void SetTitle(char* c) { sprintf_s(title, 256, c); }
	char* GetTitle() { return title; }	
	int GetID() { return id; }
	static void SetGMapUpperType(MapUpperType x) { g_mapuppertype = x; }
	static void SetData(int x, int y);	// �l�X�ȃf�[�^���Z�b�g���� 
	static MapUpperType GetGMapUpperType() { return g_mapuppertype; }
private:
	static MapUpperType g_mapuppertype;
};
extern CommuData commu_data[COMMU_NUMBER_MAX], commu_data_map[COMMU_MAP_LIMIT], commu_data_map_choice;
// �R�~���{�����[�h�ŕ\�������R�~���̏��
class CSDisplayCommuState
{
public:
	int id;		// �R�~���̂h�c
	char* name;	// �R�~���^�C�g��
	void StateReset()
	{
		id = 0;
		name = (char*)"";
	}
	void StateChange(CommuData* x)
	{
		id = x->id;
		name = x->title;
	}
};
extern CSDisplayCommuState cs_displat_commu[CS_COMMU_LIMIT];
#pragma endregion
// �l�X�ȃ��[�h��֐��Ŏg����^���O���[�o���ϐ�
class GlobalStaticVariable
{
	static int commu_number;						// �R�~������
	static const BOOL mode_trial;					// �̌��Ń��[�h�p�t���O
	static const int RESOLUTION_SIZE_ORIGINAL_X;	// �I���W�i�����𑜓x
protected:
	static constexpr int CELL_LIMIT = 1024;	// �s���E��
public:
	static void SetCommuNumber(int num) { commu_number = num; }
	static void CommuNumberCount() {commu_number++; }
	static BOOL GetModeTrial() { return mode_trial; }
	static int GetCommuNumber() { return commu_number; }
	static int GetRSOriginalX() { return RESOLUTION_SIZE_ORIGINAL_X; }
	static int GetCellLimit() { return CELL_LIMIT; }
};
// �R�~���Z�[�u�f�[�^�\���́i���j
struct CommuSaveData : public GlobalStaticVariable
{
	static constexpr int CHARACTER_NUMBER = 5;
private:
	char time[256] = "";							// �N��������������
	int week;										// �Q�[�����Ԃ̌��T
	int commu_id;									// �R�~���i0�Ȃ�}�b�v��ʁj
	int cell;										// �R�~�����s
	int map_appear_id;								// ����̃R�~�������\�������^�C�~���O
	int number_met[CHARACTER_NUMBER];				// �e�L�����̃R�~���I����
	int line_jump[CELL_LIMIT];						// �I�����A�s�W�����v�旚��
	BOOL trial_still_viewed[CHARACTER_NUMBER] = {};	// �X�`���̌��łŎg���L�����ʂ̃R�~�������I�����t���O
public:
	float play_second;	// �v���C���ԁi�b�j
	void ChangeTimeString()
	{
		DATEDATA Date;		// DX���C�u�����Ǝ��̍\����
		GetDateTime(&Date);	// ���ݎ����𓾂�
		sprintf_s(time, 256, "%04d/%02d/%02d %d�F%02d", Date.Year, Date.Mon, Date.Day, Date.Hour, Date.Min);
	}
	// �Z�[�u�f�[�^����ǂݍ���ő������ꍇ
	void ChangeTimeString(char* c) { sprintf_s(time, 256, c); }

	void ChangeSaveData(int import_w, int import_co, int import_ce, int x)	// �Q�[�������T,�R�~���h�c,�R�~���s,�A�C�R���o���^�C�v
	{
		week = import_w;
		commu_id = import_co;
		cell = import_ce;
		map_appear_id = x;
	}
	void SetNumberMet(int x, int y) { number_met[x] = y; }
	// �I�����̃W�����v�旚��
	void SetLineJump();
	// �ʂ̃Z�[�u�f�[�^����W�����v�旚���擾
	void SetLineJumpSave(int x, int y) { line_jump[x] = y; }

	void SetTrialStillViewed(int x, BOOL y) { trial_still_viewed[x] = y; }
	// �����o�ϐ����擾
	BOOL GetTrialStillViewed(int x) { return trial_still_viewed[x]; }	// �X�`���̌��łŎg���L�����ʂ̃R�~�������I�����t���O
	char* GetTimeString() { return time; }								// �N��������������
	int GetWeek() { return week; }										// �Q�[�������T
	int GetCommuID() { return commu_id; }								// �R�~���h�c
	int GetCell() { return cell; }										// �R�~���s
	int GetMapAppearID() { return map_appear_id; }						// ����̃R�~�������\�������^�C�~���O
	int GetNumberMet(int x) { return number_met[x]; }					// �e�L�����̃R�~���I����
	int GetLineJump(int x) { return line_jump[x]; }
	static int GetCharacterNumber() { return CHARACTER_NUMBER; }
	// �`��n
};
extern CommuSaveData commu_save_data[SAVE_DATA_NUMBER], commu_save_data_memory;
// �L�[�g���K�[����
class KeyTrigger
{
	static constexpr int KEY_NUMBER = 2;			// �g����L�[�̌�
	static BOOL key_prev[KeyTrigger::KEY_NUMBER];	// ���O�̏��
public:
	enum class Type
	{
		LEFT,
		RIGHT
	};
	static BOOL Trigger(int key, KeyTrigger::Type y);	// �L�[�g���K�[����
};

extern BOOL g_upkey_prev[2];	// ���O�̂`�{�^���̏��
extern BOOL g_downkey_prev[2];	// ���O�̉��L�[�̏��
extern BOOL g_leftkey_prev[2];	// ���O�̍��L�[�̏��
extern BOOL g_rightkey_prev[2];	// ���O�̉E�L�[�̏��
extern BOOL g_enterkey_prev[2];	// ���O�̃G���^�[�L�[�̏��
extern BOOL quit_game;			// �Q�[�����I�������邩���ʂ���t���O
//extern BOOL mode_title;			// ���݃^�C�g����ʂɂ��邩���ʂ���t���O
extern BOOL flag_full_hd_ok;	// �t���g�c�ɂ��v���C���\�����ʂ���
extern BOOL flag_full_hd_now;	// ���݂̉𑜓x���t���g�c�����ʂ���
extern BOOL flag_mode_window;	// �t���X�N���[���A�E�B���h�E�̏�Ԃ𔻕ʂ���t���O
extern BOOL flag_dialog_appear;	// �_�C�A���O�{�b�N�X���o��������t���O
// �}�b�v��ʗp
extern BOOL cfgm_commu_check[COMMU_MAP_LIMIT];	// �I���R�~���{����ʂ�\������
// �R�~���Z���N�g�p
extern BOOL cfcs_move_commu[CS_COMMU_LIMIT];	// �I�����ꂽ�R�~�����{������t���O
// �̌��Ń��[�h��p
//extern BOOL mode_trial;	// ���݃g���C�A�����[�h�����ʂ���
// �f�o�b�O���[�h��p
extern BOOL mode_debug;	// ���݃f�o�b�O���[�h�����ʂ���

extern char OneMojiBuf[3];	// �P�������ꎞ�L���z��

extern char StringBuf[STRBUF_HEIGHT][STRBUF_WIDTH + 2];	// ���z�e�L�X�g�o�b�t�@
// �J�[�\��
extern int select_cursor;
extern int mode_cursor;

extern int title_wait_time;			// �^�C�g����ʂɐ؂�ւ��������
extern int now_title_wait_time;		// �^�C�g����ʂɐ؂�ւ���Ă���o�߂�������
extern int demo_count;				// �f����ʂɐ؂�ւ������
extern int InputHandle;		// ��������͂���ۂɕK�v�ȃn���h��
extern int monitor_resolution_x;	// ���C�����j�^�[X���W
extern int monitor_resolution_y;	// ���C�����j�^�[Y���W

extern int MouseX, MouseY;					// �}�E�X���W�擾�ɕK�v�ȕϐ�
extern int StringSizeX, StringSizeY, StringLine;	// �����T�C�Y�擾�ɕK�v�ȕϐ�
extern int DrawPointX, DrawPointY;	// ������`��̈ʒu
extern int SP, CP;					// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
extern int EndFlag;					// �������P�������`�悷�鏈���̏I���t���O

extern int screen_size_x;	// �Q�[���̉��𑜓x
extern int screen_size_y;	// �Q�[���̏c�𑜓x

extern float bairitu;	// ���݉𑜓x�ɉ������e�v�f�̔{��
// �}�b�v���[�h�֌W
extern float draw_map_character_icon_x[COMMU_MAP_LIMIT];		// �L�����A�C�R��x���W�n�_
extern float draw_map_character_icon_y[COMMU_MAP_LIMIT];		// �L�����A�C�R��y���W�n�_
extern float draw_map_coordinate_hukidasi_x[COMMU_MAP_LIMIT];	// �����o��x���W�n�_
extern float draw_map_coordinate_hukidasi_y[COMMU_MAP_LIMIT];	// �����o��y���W�n�_
// �R�~���Z���N�g���[�h�֌W
extern float commu_select_coordinate_alternative_y[CS_COMMU_LIMIT];	// �R�~���I�������[y���W

// �֐��v���g�^�C�v�錾
void ScreenResolutionChange();	// ��ʉ𑜓x���`����
void DrawGameOpening();																					// �^�C�g���f��
void DrawGameMenu();																					// ���[�h�I��
void DrawGameClear();
void DrawGameTutorial();																				// �������[�h
void DrawGameContinue();																				// �R���e�j���[���
void DrawGameEnding();																					// �G���f�B���O
// �L�[�g���K�[�����i�{�^����������Ă��Ȃ���ԂŃ{�^���������ꂽ���m�F����j
BOOL IsUPKeyTrigger(int key, int y);	// ��L�[
BOOL IsDOWNKeyTrigger(int key, int y);	// ���L�[
BOOL IsLEFTKeyTrigger(int key, int y);	// ���L�[
BOOL IsRIGHTKeyTrigger(int key, int y);	// �E�L�[
BOOL IsENTERKeyTrigger(int key, int y);	// �G���^�[�L�[
BOOL ClickFlagCheck(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a);											// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ�
BOOL ClickFlagCheck2(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a);											// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ��ifloat�ϐ��wbairitu�x��������j
BOOL ClickFlagCheckF2(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, ClickFlagCheckType type);	// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ��i�񋓒萔�ɉ����ď����̃t���O���ǉ������j
/*---------------------------
���ʃ\�[�X
---------------------------*/
extern int progress_frame;				// �Q�[���J�n����o�߂����t���[�����i�P�^60�b�j
extern int progress_frame_time;			// �O��̌o�߃t���[�����J�E���g��������
extern int progress_frame_need_time;	// �O��̌o�߃t���[�����J�E���g����̂ɕK�v�Ȏ���

#endif

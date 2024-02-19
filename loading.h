#ifndef __LOADING_H__
#define __LOADING_H__

#include <DxLib.h>
#include "main.h"
#include "gamemap.h"
// �����̃T�C�Y
#define FONT_SIZE_27 27			
#define FONT_SIZE_15 15			
#define FONT_SIZE_12 12
#define FONT_SIZE_ORIGINAL 27				// �Q�[���Ŏg�p����镶���̃I���W�i���T�C�Y
#define FONT_SIZE_ORIGINAL_COMMU_NAME 48	// �Q�[���Ŏg�p����镶���̃I���W�i���T�C�Y�i�R�~�������O�j
#define FONT_SIZE_ORIGINAL_COMMU_LINE 40	// �Q�[���Ŏg�p����镶���̃I���W�i���T�C�Y�i�䎌�j
#define FONT_SIZE_ORIGINAL_TIPS 36			// �Q�[���Ŏg�p����镶���̃I���W�i���T�C�Y�itips�j

// �f�ފ֌W�̒萔�i���㑝�����Ă����j
#pragma region ver0.00292���쎞�R�����g���R�[�h
//#define BACKGROUND_NUMBER 2					// �w�i�̐�
//#define CHARACTER_GRAPH_NUMBER 2			// �L�����N�^�[�����G���g����l��
#pragma endregion
#pragma region ver0.00601���쎞�R�����g���R�[�h
//#define BACKGROUND_NUMBER 5					// �w�i�̐�
#pragma endregion
#pragma region ver0.00605���쎞�R�����g���R�[�h
//#define BACKGROUND_NUMBER 10				// �w�i�̐�
#pragma endregion
#pragma region ver0.00392���쎞�R�����g���R�[�h
//#define CHARACTER_GRAPH_NUMBER 5			// �L�����N�^�[�����G���g����l��
#pragma endregion
#define CHARACTER_GRAPH_NUMBER 7			// �L�����N�^�[�����G���g����l��
#pragma region ver0.0039���쎞�R�����g���R�[�h
//#define CHARACTER_GRAPH_PAUSE_NUMBER 4		// �L�����N�^�[�����G�̃|�[�Y�ő吔
#pragma endregion
#define CHARACTER_GRAPH_PAUSE_NUMBER 10		// �L�����N�^�[�����G�̃|�[�Y�ő吔
#pragma region ver0.016���쎞�R�����g���R�[�h
//#define CHARACTER_GRAPH_CLOTHES_NUMBER 6	// �L�����N�^�[�����G�̈ߑ��ő吔
#pragma endregion
#define CHARACTER_GRAPH_CLOTHES_NUMBER 10	// �L�����N�^�[�����G�̈ߑ��ő吔
#pragma region ver0.00292���쎞�R�����g���R�[�h
//#define CHARACTER_GRAPH_FACE_NUMBER 3		// �L�����N�^�[�����G�̕\������ډ\��
#pragma endregion
#pragma region ver0.0031���쎞�R�����g���R�[�h
//#define CHARACTER_GRAPH_FACE_NUMBER 7		// �L�����N�^�[�����G�̕\������ډ\��
#pragma endregion
#define CHARACTER_GRAPH_FACE_NUMBER 10		// �L�����N�^�[�����G�̕\������ډ\��
#define CHARACTER_GRAPH_EYE_NUMBER 6		// �L�����N�^�[�����G�̖ڂ̐�
#define CHARACTER_GRAPH_MOUSE_NUMBER 3		// �L�����N�^�[�����G�̌��̐�
#define CHARACTER_GRAPH_EYE_BLOW_NUMBER 3	// �L�����N�^�[�����G�̔��т̐�
#define MAP_HUKIDASI_NUMBER 3				// �}�b�v�L�����A�C�R�����͂ސ����o���̐�
#pragma region ver0.00295���쎞�R�����g���R�[�h
//#define BGM_NUMBER 18						// �a�f�l�̐�
//#define BGM_NUMBER 17					// �a�f�l�̐�
#pragma endregion
#pragma region ver0.00391���쎞�R�����g���R�[�h
//#define BGM_NUMBER 25						// �a�f�l�̐�
#pragma endregion
#pragma region ver0.0051���쎞�R�����g���R�[�h
//#define BGM_NUMBER 31						// �a�f�l�̐�
#pragma endregion
#define BGM_NUMBER 35						// �a�f�l�̐�
#pragma region ver0.00295���쎞�R�����g���R�[�h
//#define SE_NUMBER 31						// �r�d�̐�
#pragma endregion
#pragma region ver0.0035a���쎞�R�����g���R�[�h
//#define SE_NUMBER 35						// �r�d�̐�
#pragma endregion
#pragma region ver0.00607���쎞�R�����g���R�[�h
//#define SE_NUMBER 54						// �r�d�̐�
#pragma endregion
#define SE_NUMBER 256						// �r�d�̏���l�i���ꂪ���Ȃ��ƃT�E���h���[���̍��W��ύX����֐��ŕs�����������j
// �`��p�萔
#define LOADING_ICON_FLAME_MAX 160		// ���[�f�B���O�A�C�R�����P�����邽�߂ɕK�v�ȃt���[����

extern const char* load_name[CHARACTER_GRAPH_NUMBER];	// �L�����N�^�[�����G�ǂݍ��݂̍ۂɎg���閼�O���

enum BGMIDName
{
	BN_OP,				// �I�[�v�j���O

	BN_NICHIJOU_1,		// ����E�P
	BN_NICHIJOU_2,		// ����E�Q
	BN_NICHIJOU_3,		// ����E�R
	BN_NICHIJOU_4,		// ����E�S
	BN_NICHIJOU_5,		// ����E�T
	BN_NICHIJOU_6,		// ����E�U

	BN_HAPPENING,		// �n�v�j���O
	BN_UGLY,			// �s��
	BN_CRY,				// �߂���
	BN_AFTER_SCHOOL,	// �[��
	BN_DETEMINATION,	// ����
	BN_NIGHT,			// ��
	#pragma region ver0.0051���쎞�R�����g���R�[�h
	//BN_NIGHT_PIANO,		// ��i�s�A�m�j
#pragma endregion
	BN_MUSIC_ROOM,		// ���y��
	BN_DOTABATA,		// �ǂ��΂�
	BN_NIGHT_SKY,		// ���
	BN_CONFESSION,		// ����
	BN_KAIDAN,			// ���k
	BN_MYSTERY,			// �䔭��
	BN_UNEASINESS,		// �s��
	BN_RECOLLECTION,	// ��z
	BN_BATTLE,			// �o�g��
	BN_WILL,			// ���S
	BN_CHASER,			// �ǐՐl

	BN_TUTOMU,			// �Z��
	BN_JURI,			// ����
	BN_HADUKI,			// �͂Â�
	BN_MEGURU,			// �߂���
	BN_RINZE,			// �z��
	BN_CHIYUKI,			// ���
	BN_KOGANE,			// ����

	BN_TITLE,			// �^�C�g��
	BN_MAP,				// �}�b�v
	BN_OPMB,			// OP_�I���S�[��
	BN_SENTAKUSHI		// �I����
};
extern BGMIDName bgmid_test;
#pragma region ver0.00707���쎞�R�����g���R�[�h
// �r�d�h�c���X�g
//enum SEIDName
//{
//	SN_WIND_CHIME,				// �E�B���h�`���C��
//	SN_CLAP,					// ����
//	SN_CLAP_MULTI,				// ����i�吨�j
//	SN_CHIME,					// �`���C��
//	SN_BASKETBALL_DRIBBLE,		// �o�X�P�b�g�{�[���h���u��
//	SN_FOOT_STEP,				// ����
//	SN_FOOT_STEP_LOOP,			// �����i���[�v�j
//	SN_CURTAIN,					// �J�[�e��
//	SN_DOOR_OPEN,				// �X�̃h�A���J����
//	SN_SLIDING_DOOR,			// �����˂��J����
//	SN_KNOCK,					// �m�b�N
//	SN_BIRD_CTY,				// ���̂�������
//	SN_WIND,					// ��
//	SN_ALTERNATIVE,				// �I���������肷��
//	SN_LIBBER,					// ��̐��̗���̉�
//	SN_LIBBER_LONG,				// ��̐��̗���̉� Long Ver
//	SN_RUSTRE,					// �z���C���
//	SN_BASKETBALL_GAUL,			// �o�X�P�b�g�{�[�����S�[��
//	SN_COLLOSION,				// �l�Ɛl�Ƃ��Ԃ���
//	SN_CAT,						// �L�̖���
//	SN_PAPER_MAP_MOVE,			// �}�b�v���ړ�����r�d
//	SN_CLAP_1TAP,				// �n�C�^�b�`
//	SN_CLAP_2TAP,				// ���@����
//	SN_CROWEB_STUDENTS_SHORT,	// �����������Ă��鐶�k�����̐�
//	SN_CROWEB_STUDENTS_LONG,	// �����������Ă��鐶�k�����̐�Long  Ver
//	SN_SHOES,					// �V���[�Y�̉�
//	SN_KEYBOARD_TYPING,			// �L�[�{�[�h��@��
//	SN_KEYBOARD_TYPING_LOOP,	// �L�[�{�[�h��@���i���[�v�j
//	SN_PAPER_FLYING,			// �����U��΂鉹
//	SN_PHONE_NOTICE_NOTE,		// �g�сE�ʒm
//	SN_TUMBLE,					// �]�ԁi�����[�j
//	SN_CHAIR_STANDUP,			// �֎q�𗧂�
//	SN_GATAGATA,				// �K�^�K�^�Ƃ�������
//	SN_PHONE_CALL,				// �g�сE���M��
//	SN_ICON_TAP,				// �A�C�R������������
//	SN_AGEMONO,					// �g���������鉹
//	SN_FLASH_BACK,				// �t���b�V���o�b�N
//	SN_HOWAN4,					// �v���o����
//	SN_DOOR_OPEN_GATYA,			// �J���˂̉�
//	SN_GASAGASA,				// �K�T�K�T
//	SN_DASH,					// �삯�鑫��
//	SN_OPEN_WINDOW,				// �����J���鉹
//	SN_PEN_WRITE,				// ����������
//	SN_PEN_WRITE_LOOP,			// ����������(LOOP)
//	SN_DOOR_OPEN_SILENT,		// �Â��Ɍ˂��J��
//	SN_CHAIR_SITDOWN,			// �֎q�ɍ���
//	SN_SEMI,					// �Z�~�̐�
//	SN_JAGUTI_OPEN,				// �������J��
//	SN_JAGUTI_CLOASE,			// �������~�߂鉹
//	SN_SCEAN_CHANGE_IN,			// ��ʓ]��IN
//	SN_SCEAN_CHANGE_OUT,		// ��ʓ]��OUT
//	SN_STARTSCEAN_NOTE,			// �X�^�[�g��ʑI��
//	SN_START,					// Start
//	SN_FLUID_WATER,				// �����̉�
//	SN_FLUID_WATER_LOOP,		// �����̉�(LOOP)
//	SN_GAAN,					// ���[��
//	SN_HUG						// ��������
//};
#pragma endregion

// �a�f�l�̏��
enum BGMStateType
{
	BGM_STANDBY,	// �ҋ@
	BGM_PLAY,		// �Đ�
	BGM_FADE_IN,	// �t�F�[�h�C���Đ�
	BGM_FADE_OUT,	// �t�F�[�h�A�E�g��~
	BGM_STOP		// ��~
};
// �I�v�V�����t�h�摜�̎��
enum IMGOptionType
{
	IMG_OPTION_BACKGROUND,	// �w�i
	IMG_OPTION_PAPER,		// ��
	IMG_OPTION_MENU,		// ���j���[
	IMG_OPTION_TITLE,		// OPTION�}�[�N
	IMG_OPTION_PIXEL_720,	// �𑜓x720p
	IMG_OPTION_PIXEL_1080,	// �𑜓x1080p
};
struct ImageHandles
{
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//int text_window;																																	// �e�L�X�g�E�B���h�E
#pragma endregion
	int text_loading;																																	// �wNow Loading�x
	int commu_list;																																		// �wCommu List�x
	int icon_commu_option;																																// �R�~���I�v�V����
	int icon_loading;																																	// ���[�f�B���O�A�C�R��
	int icon_auto[2];																																	//	�wAUTO�x�A�C�R��
	int icon_skip[2];																																	//	�wSKIP�x�A�C�R��
	int icon_save[2];																																	//	�wSAVE�x�A�C�R��
	int icon_load[2];																																	//	�wLOAD�x�A�C�R��
	int icon_menu[2];																																	//	�wMENU�x�A�C�R��
	int icon_text_off;																																	//	�wTEXT_OFF�x�A�C�R��
	int icon_back;																																		//	�wBACK�x�A�C�R��
	int icon_title;																																		//	�wTITLE�x�A�C�R��
	int icon_exit;																																		//	�wEXIT�x�A�C�R��
	#pragma region ver0.0072���쎞�R�����g���R�[�h
	//int icon_save_file;																																	// �Z�[�u�t�@�C��
#pragma endregion
	#pragma region ver0.0081���쎞�R�����g���R�[�h
	//int icon_save_file_page[2];																															// �Z�[�u�t�@�C���̃y�[�W
#pragma endregion
	#pragma region ver0.00706���쎞�R�����g���R�[�h
	//int ui_month;																																		// ���̂t�h�i�S���j
#pragma endregion
	int ui_tips;																																		// tips�p�t�h
	int ui_map[3];																																		// �}�b�v
	#pragma region ver0.0038���쎞�R�����g���R�[�h
	//int ui_map_icon[1];																																	// �}�b�v���̃L�����A�C�R��
#pragma endregion
	int ui_map_icon[6];																																	// �}�b�v���̃L�����A�C�R��
	int ui_map_hukidasi[3];																																// �}�b�v���̐����o���A�C�R��
	int ui_map_check;																		// 
	int ui_map_check_choice[2];																															// �R�~���ړ��m�F���̑I����
	#pragma region ver0.007���쎞�R�����g���R�[�h
	//int altenative[3];																																	// �I����
#pragma endregion
	#pragma region ver0.0039���쎞�R�����g���R�[�h
	//int background[2];																																	// �w�i
#pragma endregion
	#pragma region ver0.00605���쎞�R�����g���R�[�h
	//int background[BACKGROUND_NUMBER];																													// �w�i
#pragma endregion
	#pragma region ver0.0029���쎞�R�����g���R�[�h
	//int character_body[1][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER];																// �L�����N�^�[���́A����[�L����][�|�[�Y][����]
	//int character_face[1][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_EYE_NUMBER + CHARACTER_GRAPH_MOUSE_NUMBER];		// �L�����N�^�[��p�[�c[�L����][�|�[�Y][����][�ڂƌ��̍��v]
	//int character_eyebrow[1][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_EYE_BLOW_NUMBER];							// �L�����N�^�[���уp�[�c[�L����][�|�[�Y][����][���т̍��v]
#pragma endregion
	int character_body[CHARACTER_GRAPH_NUMBER][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER];																							// �L�����N�^�[���́A����[�L����][�|�[�Y][����]
	int character_face[CHARACTER_GRAPH_NUMBER][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_FACE_NUMBER][CHARACTER_GRAPH_EYE_NUMBER + CHARACTER_GRAPH_MOUSE_NUMBER];	// �L�����N�^�[��p�[�c[�L����][�|�[�Y][����][����][�ڂƌ��̍��v]
	int character_eyebrow[CHARACTER_GRAPH_NUMBER][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_FACE_NUMBER][CHARACTER_GRAPH_EYE_BLOW_NUMBER];							// �L�����N�^�[���уp�[�c[�L����][�|�[�Y][����][����][���т̍��v]
	// �R�~���Z���N�g��
	int commu_select_type;	//	�R�~����ޑI����
	int commu_select;		//	�R�~���I����
};
extern ImageHandles g_imghandles;

class CharacterImage
{
public:
	void SetLoadFlag(int x) { load_flag[x] = TRUE; }
	static constexpr int CHARACTER_NUMBER = 7;	// �l��
	static constexpr int PAUSE_NUMBER = 10;		// �|�[�Y�ő吔
	#pragma region ver0.016���쎞�R�����g���R�[�h
	//static constexpr int CLOTHES_NUMBER = 6;	// �ߑ��ő吔
#pragma endregion
	static constexpr int CLOTHES_NUMBER = 10;	// �ߑ��ő吔
	static constexpr int FACE_NUMBER = 10;		// �\������ډ\��
	static constexpr int EYE_NUMBER = 6;		// �ڂ̐�
	static constexpr int MOUSE_NUMBER = 3;		// ���̐�
	static constexpr int EYE_BLOW_NUMBER = 3; 	// ���т̐�
	static void SetFlagAll(BOOL b);				// �S�Ă̓ǂݍ��݃t���O���w��̐^�U�ɃZ�b�g����
	static void SetLoadEdit(int x, BOOL y) { load_edit[x] = y; }
	static void LoadFlagCheck();				// �ǂݍ��މ摜�̎�ނ��`�F�b�N����
	static void DeleteAll();					// �S�Ă̗����G������������폜����
	static BOOL Load();							// �ǂݍ��ݏ���
	static BOOL GetLoadEdit(int x) { return load_edit[x]; }
	static int GetCharacterMember() { return CHARACTER_NUMBER; }
private:
	BOOL load_flag[CharacterImage::FACE_NUMBER];			// �ǂݍ��݃t���O
	BOOL load_flag_finished[CharacterImage::FACE_NUMBER];	// �ǂݍ��݊����t���O
	static const char* LOAD_NAME[CharacterImage::CHARACTER_NUMBER];
	static BOOL load_edit[CharacterImage::CHARACTER_NUMBER];	// �G�f�B�b�g���[�h�ł̌ʓǂݍ��݃t���O
	int handle;																									// ���̃n���h��
	int handle_face[CharacterImage::FACE_NUMBER][CharacterImage::EYE_NUMBER + CharacterImage::MOUSE_NUMBER];	// ���̃n���h��
	int handle_eyebrow[CharacterImage::FACE_NUMBER][CharacterImage::EYE_BLOW_NUMBER];							// ���уn���h��
};
extern CharacterImage image_character[CharacterImage::CHARACTER_NUMBER][CharacterImage::PAUSE_NUMBER][CharacterImage::CLOTHES_NUMBER];

//struct SoundHandles
//{
//	int BGM[BGM_NUMBER];
//	//int SE[SE_NUMBER];
//};
//extern SoundHandles g_sndhandles;
// �a�f�l�i���O�͉����́wMusicStringData�x�N���X�ɂ���j
class BGMData
{
	char path[256] = "";
	BOOL load = FALSE;			// �ǂݍ��ݏ����œǂݍ��ނ��̂����ʂ���
	BOOL load_finished = FALSE;	// �ǂݍ��݊����t���O
	BOOL not_release = FALSE;	// ��������������ŉ�����Ȃ��t���O
	int handle = 0;
	const int LOOP_POS = 0;		// ���[�v�����ۂ̍ĊJ�ʒu
	const int LOOP_START = 0;	// ���[�v����ʒu
public:
	BGMData(char *c, BOOL x, int y, int z) : not_release(x), LOOP_POS(y), LOOP_START(z){sprintf_s(path, 256, "media\\BGM\\%s.wav", c);}
	static constexpr int NUMBER = BGM_NUMBER;	// ��
	void SetLoad(BOOL x) { load = x; }
	void SetLoop();	// ���[�v�֌W�̈ʒu��ݒ肷��
	BOOL GetLoad() { return load; }
	BOOL GetNotRelease() { return not_release; }
	BOOL GetHandle() { return handle; }
	static void LoadFirst();		// �������������Ȃ���ނ̂a�f�l��ǂݍ���	
	static void SetLoadAll(BOOL x);	// �S�Ă�load�ϐ���ύX����
	static void LoadFlagCheck();	// �ǂݍ��ނa�f�l���`�F�b�N����
	static void DeleteAll();		// �S�Ă̂a�f�l������������폜����
	static void Load();				// ���[�h����
	static int GetNumber() { return NUMBER; }
};
extern BGMData bgm[BGM_NUMBER];
// ���ʉ�
class SEData
{
	char path[256] = "";			// �ǂݍ��ݗp�p�X
	char name[256] = "";			// �Q�[��������
	BOOL loop;						// ���[�v�t���O
	BOOL load_finished;				// �ǂݍ��݊����t���O
	int Handle;
	static int number;				// ����
	static int commu_start_time;	// �R�~���X�^�[�g�r�d�Đ����~���b
public:
	// �h�c���X�g
	enum class IDName
	{
		WIND_CHIME,				// �E�B���h�`���C��
		CLAP,					// ����
		CLAP_MULTI,				// ����i�吨�j
		CHIME,					// �`���C��
		BASKETBALL_DRIBBLE,		// �o�X�P�b�g�{�[���h���u��
		FOOT_STEP,				// ����
		FOOT_STEP_LOOP,			// �����i���[�v�j
		CURTAIN,				// �J�[�e��
		DOOR_OPEN,				// �X�̃h�A���J����
		SLIDING_DOOR,			// �����˂��J����
		KNOCK,					// �m�b�N
		BIRD_CTY,				// ���̂�������
		WIND,					// ��
		ALTERNATIVE,			// �I���������肷��
		LIBBER,					// ��̐��̗���̉�
		LIBBER_LONG,			// ��̐��̗���̉� Long Ver
		RUSTRE,					// �z���C���
		BASKETBALL_GAUL,		// �o�X�P�b�g�{�[�����S�[��
		COLLOSION,				// �l�Ɛl�Ƃ��Ԃ���
		CAT,					// �L�̖���
		PAPER_MAP_MOVE,			// �}�b�v���ړ�����r�d
		CLAP_1TAP,				// �n�C�^�b�`
		CLAP_2TAP,				// ���@����
		CROWEB_STUDENTS_SHORT,	// �����������Ă��鐶�k�����̐�
		CROWEB_STUDENTS_LONG,	// �����������Ă��鐶�k�����̐�Long  Ver
		SHOES,					// �V���[�Y�̉�
		KEYBOARD_TYPING,		// �L�[�{�[�h��@��
		KEYBOARD_TYPING_LOOP,	// �L�[�{�[�h��@���i���[�v�j
		PAPER_FLYING,			// �����U��΂鉹
		PHONE_NOTICE_NOTE,		// �g�сE�ʒm
		TUMBLE,					// �]�ԁi�����[�j
		CHAIR_STANDUP,			// �֎q�𗧂�
		GATAGATA,				// �K�^�K�^�Ƃ�������
		PHONE_CALL,				// �g�сE���M��
		ICON_TAP,				// �A�C�R������������
		AGEMONO,				// �g���������鉹
		FLASH_BACK,				// �t���b�V���o�b�N
		HOWAN4,					// �v���o����
		DOOR_OPEN_GATYA,		// �J���˂̉�
		GASAGASA,				// �K�T�K�T
		DASH,					// �삯�鑫��
		OPEN_WINDOW,			// �����J���鉹
		PEN_WRITE,				// ����������
		PEN_WRITE_LOOP,			// ����������(LOOP)
		DOOR_OPEN_SILENT,		// �Â��Ɍ˂��J��
		CHAIR_SITDOWN,			// �֎q�ɍ���
		SEMI,					// �Z�~�̐�
		JAGUTI_OPEN,			// �������J��
		JAGUTI_CLOASE,			// �������~�߂鉹
		SCEAN_CHANGE_IN,		// ��ʓ]��IN
		SCEAN_CHANGE_OUT,		// ��ʓ]��OUT
		STARTSCEAN_NOTE,		// �X�^�[�g��ʑI��
		START,					// Start
		FLUID_WATER,			// �����̉�
		FLUID_WATER_LOOP,		// �����̉�(LOOP)
		GAAN,					// ���[��
		HUG,					// ��������
		PING_PONG,				// �s���|��
		HORROR,					// �z���[
		SENTAKUSHI,				// �R�~���I����
		START_EFFECT,			// �^�C�g�����
		DASH_ROOM,				// �삯�鑫��(����)
		COMMU_START				// �R�~���X�^�[�g
	};
	SEData(char *c_path, char *c_name, BOOL x)	// ��O�̃t�H���_�Ɗg���q��`�����p�X��,�Q�[��������,���[�v�r�d�t���O
	{
		sprintf_s(path, 256, "media\\SE\\%s.wav"  ,c_path);	
		sprintf_s(name, 256, c_name);
		loop = x;
		number++;
	}
	// ���[�h����
	void Load()
	{
		Handle = LoadSoundMem(path);	// �r�d��ǂݍ���
		load_finished = TRUE;			// �r�d��ǂݍ��񂾃`�F�b�N���s��
	}

	void PlayBack() { PlaySoundMem(Handle, DX_PLAYTYPE_BACK); }	// �Đ�����i���[�v�Ȃ��j
	// �t���O�ɉ����ă��[�v������
	void Play() 
	{ 
		if (loop == FALSE) { PlaySoundMem(Handle, DX_PLAYTYPE_BACK); }
		else { PlaySoundMem(Handle, DX_PLAYTYPE_LOOP); }
	}

	char* GetName() { return name; }					// ���O���擾����
	BOOL GetLoadFinished() { return load_finished; }	// �ǂݍ��݊����t���O���擾����
	int GetHandle() { return Handle; }	// �����n���h�����擾����
	static void SetCommuStartTime() { commu_start_time = GetNowCount(); }
	// �R�~���X�^�[�g�r�d�Đ�����Q�b�o�߂��Ă�����TRUE��Ԃ�
	static BOOL CheckCommuStartTime() { return (commu_start_time < GetNowCount() - 2000) ? TRUE : FALSE; }

	static int GetNumber() { return number; }
};
extern SEData se[];
// �摜�̏c����
struct GraphSize
{
	float x;
	float y;
};
#pragma region ver0.0026a���쎞�R�����g���R�[�h
//extern GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check, size_ui_map_check_choice, size_commu_altenative;
#pragma endregion
#pragma region ver0.007���쎞�R�����g���R�[�h
//extern GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check, size_commu_altenative;
#pragma endregion
extern GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check;

// �{���␳���s�����摜�c����
struct GraphSize2
{
	int ox;		// �{���␳���|���Ă��Ȃ����X��x���W
	int oy;		// �{���␳���|���Ă��Ȃ����X��y���W
	float x;
	float y;
};
//										�wCommu List�x												�wTEXT OFF�x�A�C�R���A	�Z�[�u�t�@�C���y�[�W�A						�}�b�v�ړ��m�F�p�I�����A	�}�b�v�L�����A�C�R���A	�����o���A									�R�~���Z���N�g���R�~����ޑI�����A	�R�~���Z���N�g���R�~���I����
#pragma region ver0.0072���쎞�R�����g���R�[�h
//extern GraphSize2 size_icon_loading,	size_icon_commu_list,	size_text_loading, size_icon_auto,	size_icon_text_off,		size_icon_sl_file_page, size_icon_sl_file,	size_ui_map_check_choice,	size_ui_map_icon2,		size_ui_map_hukidasi[MAP_HUKIDASI_NUMBER],	size_ui_cs_alternative_type,		size_ui_cs_alternative;
#pragma endregion
extern GraphSize2 size_icon_loading, size_icon_commu_list, size_text_loading, size_icon_auto, size_icon_text_off, size_icon_sl_file_page, size_ui_map_check_choice, size_ui_map_icon2, size_ui_map_hukidasi[MAP_HUKIDASI_NUMBER], size_ui_cs_alternative_type, size_ui_cs_alternative;
#pragma region ver0.0053���쎞�R�����g���R�[�h
//// �R�~�����e
////typedef struct state
//struct state
//{
//	char command[256];
//	int move_commu_number;					// �ړ���R�~���h�c
//	char name[256];
//	char name2[256];						// �����ɒ���Q�l�ڂ̖��O
//	char line[256];							// �䎌
//	int line_mouse;							// ����ۂ̌��p�N�^�C�v
//	int character[3];						// �`�悷��L�����A����
//	int character_face_etc[3];				// �L�����̓���\��h�c
//	int character_change;					// �L�����N�^�[�ύX�^�C�v
//	int character_even_distance;			// �L�����N�^�[�����ψꉻ�̃I���I�t
//	int background;							// �`��w�i
//	BackgroundChangeType background_change;	// �w�i�ύX�^�C�v
//	int bgm;								// �Đ�����a�f�l
//	BGMChangeType bgm_change;				// �a�f�l�؂�ւ��^�C�v
//	int se;									// �Đ�����r�d
//	char altenative_message[3][128];		// �I������
//	int altenative_jump[3];					// �I�����̃W�����v��̍s
//	// �R�}���h��ύX����
//	void CommandChange(char* c){ sprintf_s(command, 256, c); }	// ���������
//	// �e����R�}���h�p���l��ύX����
//	void CommandNumberChange(int x){ move_commu_number = x; }	// ���l
//	// �䎌���ύX����i���͕�����Łj
//	void LineCharacterChange(int x, int y) 	// �ҏW�䎌��p�z��ϐ�,���������
//	{
//		if(x == 0){ GetKeyInputString(name, y); }		
//		else { GetKeyInputString(name2, y); }
//	}
//	// �䎌���ύX����ichar�ϐ��Łj
//	void LineCharacterChange(int x, char* c) 	// �ҏW�䎌��p�z��ϐ�,���������
//	{
//		if(x == 0){ sprintf_s(name, 256, c); }
//		else{ sprintf_s(name2, 256, c); }
//	}	
//	void LineChange(int x) { GetKeyInputString(line, x); }	// �䎌��ύX����ix�F���������j
//	void LineChange(char* c) { sprintf_s(line, 256, c); }	// �䎌��ύX����ichar�ϐ��ŁAc�F���������j
//	void LineMouseChange(int x) { line_mouse = x; }				// ���p�N�^�C�v��ύX����ix�F������l�j
//	// �G�f�B�b�g���[�h��character[x]�̐��l��ς���ۂ̋��ʏ���
//	void CharacterIDChange(int x, int y, int z) // �ύX����L�����N�^�[,�ύX����ID���l�̌��̈�,�ύX��̐���
//	{
//		int a = (int)pow(10, y - 1);
//		int b = character[x] / a;
//		if (b >= 10) { b %= 10; }
//		character[x] = character[x] - a * b + a * z;
//	}
//	// �L�����̓���\���ύX����				
//	void CFECHANGE(int x, int y) { character_face_etc[x] = y; }	// �L�����N�^�[,���l
//	// �L�����N�^�[�ύX�^�C�v��ύX����
//	void CCCHANGE(int x) { character_change = x; }
//	// �L�����ԋ����ψꉻ��ύX����
//	void CDUCHANGE(int x) { character_even_distance = x; }	// �ύX���鐔�l
//	// �w�i��ύX����
//	void BackgroundChange(int x) { background = x; }	// �ύX����
//	// �w�i�ύX�^�C�v��ύX����
//	void BackgroundChangeTypeChange(BackgroundChangeType x) { background_change = x; }	// �ύX���鐔�l
//	// �Đ��a�f�l��ύX����
//	void BGMChange(int x) { bgm = x; }	// �a�f�l�p�ϐ�
//	// �a�f�l�ύX�^�C�v��ύX����
//	void BCTChange(BGMChangeType x) { bgm_change = x; }
//	// �r�d���l��ύX����
//	void SEChange(int x) { se = x; }	// ��p�ϐ�
//	// �I�����������ύX����
//	void AlternativeChange(int x, int y) { GetKeyInputString(altenative_message[x], y); }// �I�����p�ϐ�,���������
//	// �I�����W�����v��s��ύX����
//	void AlternativeJumpChange(int x, int y) { altenative_jump[x] = y; }	// �I�����p�ϐ�,���l
//	// �R�}���h�����擾����
//	char* GetCommand() { return command; }
//	// �P�l�ڂ̑䎌�喼���擾����
//	char* GetLineCharacterName(){ return name; }
//	// �Q�l�ڂ̑䎌�喼���擾����
//	char* GetLineCharacterName2() { return name2; }
//	// �䎌��������擾����
//	char* GetLine() { return line; };
//	// �I�����̕�������擾����
//	char* GetAlternativeString(int x){ return altenative_message[x]; }
//	// �R�}���h�p���l���擾����
//	int GetCommandNumber(){ return move_commu_number; }
//	// ����ۂ̌��p�N�^�C�v���擾����
//	int GetLineMouse(){ return line_mouse; }
//	// �`�悷��L�����p�ϐ��l���擾����
//	int GetCharacter(int x){ return character[x]; }	// �L�����̈ʒu
//	// �L�����̓���\��h�c���擾����
//	int GetCFE(int x){ return character_face_etc[x];}	// �L�����̈ʒu
//	// �L�����N�^�[�ύX�^�C�v���l���擾����
//	int GetCC() { return character_change; }
//	// �L�����ԋ����ψꉻ���擾����
//	int GetCDU() { return character_even_distance; }
//	// �w�i�p�ϐ����擾����
//	int GetBackground() { return background; }
//	// �a�f�l�p�ϐ����擾����
//	int GetBGM() { return bgm; }
//	// �r�d�p�ϐ����擾����
//	int GetSE() { return se; }
//	// �I�����W�����v��p�ϐ����擾����
//	int GetAlternativeJump(int x){ return altenative_jump[x]; }	// �I����
//	// �w�i�ύX�^�C�v�p�ϐ����擾����
//	BackgroundChangeType GetBackgroundChangeType() { return background_change; }
//	// �a�f�l�ύX�^�C�v�p�z��萔���擾����
//	BGMChangeType GetBGMCT() { return bgm_change; }
//
//};
//#pragma region ver0.0034���쎞�R�����g���R�[�h
////extern state HM[512][128];
//#pragma endregion
//extern state HM[512][COMMU_LINE_MAX], commu_state_edit[COMMU_LINE_MAX + 1];
#pragma endregion
// BGM�̏�ԁiBGM_NUMBER�萔������̂�gamemusic.h�ɒu���Ȃ��j
struct BGMState
{
	BGMStateType state;	// ���
	int	vol;			// ���ʂɊւ��ϐ�
};
extern BGMState g_bgmstate[BGM_NUMBER];
// �a�f�l�^�C�g���f�[�^�i�񋓒萔�̓s����soundroom.h�ɋL�q���Ă��Ȃ��j
class MusicStringData
{
public:
	char* name;
	void NameChange(int x)
	{
		enum BGMIDName y;
		y = static_cast<BGMIDName>(x);	// ������񋓌^�ɕϊ�����
		switch (y)
		{
		#pragma region ver0.0026���쎞�R�����g���R�[�h
		//case BN_NICHIJOU_1:		name = "����E�P";		break;
		//case 1:					name = "����E�Q";		break;
		//case 2:					name = "����E�R";		break;
		//case 3:					name = "�n�v�j���O";	break;
		//case 4:					name = "�s��";			break;
		//case 5:					name = "�߂���";		break;
		//case BN_AFTER_SCHOOL:	name = "�[��";			break;
		//case BN_DETEMINATION:	name = "����";			break;
		//case BN_NIGHT:			name = "��";			break;
		//case BN_MUSIC_ROOM:		name = "���y��";		break;
		//case BN_TUTOMU:			name = "�Z��";			break;
		//case BN_JURI:			name = "����";			break;
		//case BN_HADUKI:			name = "�͂Â�";		break;
		//case BN_MEGURU:			name = "�߂���";		break;
		//case BN_RINZE:			name = "�z��";			break;
		//case BN_CHIYUKI:		name = "���";			break;
		//case BN_TITLE:			name = "���C��";		break;
		//case BN_MAP:			name = "�}�b�v";		break;
		//default:				name = "";				break;
#pragma endregion
		case -1:				name = (char*)"�a�f�l��~";		break;
		case BN_OP:				name = (char*)"�n�o";			break;
		case BN_NICHIJOU_1:		name = (char*)"����1";		break;
		case BN_NICHIJOU_2:		name = (char*)"����2";		break;
		case BN_NICHIJOU_3:		name = (char*)"����3";		break;
		case BN_NICHIJOU_4:		name = (char*)"����4";		break;
		case BN_NICHIJOU_5:		name = (char*)"����5";		break;
		case BN_NICHIJOU_6:		name = (char*)"����6";		break;
		case BN_HAPPENING:		name = (char*)"�n�v�j���O";		break;
		case BN_UGLY:			name = (char*)"�s��";			break;
		case BN_CRY:			name = (char*)"�߂���";			break;
		case BN_AFTER_SCHOOL:	name = (char*)"�[��";			break;
		case BN_DETEMINATION:	name = (char*)"����";			break;
		case BN_NIGHT:			name = (char*)"��";				break;
		#pragma region ver0.0051���쎞�R�����g���R�[�h
		//case BN_NIGHT_PIANO:	name = (char*)"�� �s�A�mver";	break;
#pragma endregion
		case BN_MUSIC_ROOM:		name = (char*)"���y��";			break;
		case BN_DOTABATA:		name = (char*)"�ǂ��΂�";		break;
		case BN_NIGHT_SKY:		name = (char*)"���";			break;
		case BN_CONFESSION:		name = (char*)"����";			break;
		case BN_KAIDAN:			name = (char*)"���k";			break;
		case BN_MYSTERY:		name = (char*)"�䔭��";			break;
		case BN_UNEASINESS:		name = (char*)"�s��";			break;
		case BN_RECOLLECTION:	name = (char*)"��z";			break;
		case BN_BATTLE:			name = (char*)"�o�g��";			break;
		case BN_WILL:			name = (char*)"���S";			break;
		case BN_CHASER:			name = (char*)"�ǐՐl";			break;
		case BN_TUTOMU:			name = (char*)"�Z��BGM";		break;
		case BN_JURI:			name = (char*)"����BGM";		break;
		case BN_HADUKI:			name = (char*)"�͂Â�BGM";		break;
		case BN_MEGURU:			name = (char*)"�߂���BGM";		break;
		case BN_RINZE:			name = (char*)"�z��BGM";		break;
		case BN_CHIYUKI:		name = (char*)"���BGM";		break;
		case BN_KOGANE:			name = (char*)"����BGM";		break;
		case BN_TITLE:			name = (char*)"���C��";			break;
		case BN_MAP:			name = (char*)"�}�b�v";			break;
		case BN_OPMB:			name = (char*)"OP_�I���S�[��";	break;
		case BN_SENTAKUSHI:		name = (char*)"�I����";			break;
		default:				name = (char*)"";				break;
		}
	}
	char* GetName() { return name; }
};
extern MusicStringData music_string[], music_string_stop;

extern char* bgm_name[BGM_NUMBER];

extern int loading_icon_flame;		// ���[�f�B���O�A�C�R���`��p�o�߃t���[��
extern int g_time_first_load_start;	// FIRST_LOAD���[�h���n�܂����~���b
extern int g_time_load_start;		// ���t���[���Ń��[�h���J�n�����~���b
// �t�H���g
extern int g_font1;					// ����������
//extern int g_font2;					// ����������蕶��
extern int g_font3;					// �e�𑜓x�Ή�����
extern int g_font_commu_name;		// �R�~����ԑ䎌��p����
extern int g_font_commu_line;		// �R�~����ԑ䎌�p����
extern int g_font_tips;				// tips�p����

extern BOOL debug_mute;																																// �a�f�l��ǂݍ��ނ����ʂ���f�o�b�O�@�\
extern BOOL load_bgm_finished[BGM_NUMBER];																											// �a�f�l�����ɓǂݍ��܂�Ă邩���ʂ���
#pragma region ver0.00607���쎞�R�����g���R�[�h
//extern BOOL load_se_finished[SE_NUMBER];																											// �r�d�����ɓǂݍ��܂�Ă邩���ʂ���
#pragma endregion

void DrawLoading();								// ���[�h�Ɋ֌W����`�揈��
void LoadFont();								// �Q��ȏ�ǂݍ��܂��\��������t�H���g���`����
void GraphSizeChange(GraphSize2 *pgs, int x);	// ������ꂽ�摜�T�C�Y�l���X�N���[���{���ɉ������l�ɂ���
#pragma region ver0.0029���쎞�R�����g���R�[�h
//void LoadGameImageCharacterBody(int x, int *y);	// �L�����N�^�[�̐g�̕�����ǂݍ���
#pragma endregion
//void LoadGameImageCharacterBody(int x, int* y, char* z);	// �L�����N�^�[�̐g�̕�����ǂݍ���
void LoadGameImageCharacterBody(int x, int* y, const char* z, int a);	// �L�����N�^�[�̐g�̕�����ǂݍ���

BOOL LoadGameImage();
#pragma region ver0.017���쎞�R�����g���R�[�h
//BOOL LoadBGM(BGMIDName x);						// �a�f�l��ǂݍ���
//BOOL LoadBGM2(SoundHandles *x, int y, char *z);	// LoadBGM���ł̋��ʏ���
#pragma endregion
BOOL LoadSE();									// �r�d��ǂݍ���

#endif

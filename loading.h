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
#define CHARACTER_GRAPH_NUMBER 7			// �L�����N�^�[�����G���g����l��
#define CHARACTER_GRAPH_PAUSE_NUMBER 10		// �L�����N�^�[�����G�̃|�[�Y�ő吔
#define CHARACTER_GRAPH_CLOTHES_NUMBER 10	// �L�����N�^�[�����G�̈ߑ��ő吔
#define CHARACTER_GRAPH_FACE_NUMBER 10		// �L�����N�^�[�����G�̕\������ډ\��
#define CHARACTER_GRAPH_EYE_NUMBER 6		// �L�����N�^�[�����G�̖ڂ̐�
#define CHARACTER_GRAPH_MOUSE_NUMBER 3		// �L�����N�^�[�����G�̌��̐�
#define CHARACTER_GRAPH_EYE_BLOW_NUMBER 3	// �L�����N�^�[�����G�̔��т̐�
#define MAP_HUKIDASI_NUMBER 3				// �}�b�v�L�����A�C�R�����͂ސ����o���̐�
#define BGM_NUMBER 35						// �a�f�l�̐�
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
	int ui_tips;																																		// tips�p�t�h
	int ui_map[3];																																		// �}�b�v
	int ui_map_icon[6];																																	// �}�b�v���̃L�����A�C�R��
	int ui_map_hukidasi[3];																																// �}�b�v���̐����o���A�C�R��
	int ui_map_check;																		// 
	int ui_map_check_choice[2];																															// �R�~���ړ��m�F���̑I����
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
extern GraphSize2 size_icon_loading, size_icon_commu_list, size_text_loading, size_icon_auto, size_icon_text_off, size_icon_sl_file_page, size_ui_map_check_choice, size_ui_map_icon2, size_ui_map_hukidasi[MAP_HUKIDASI_NUMBER], size_ui_cs_alternative_type, size_ui_cs_alternative;
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

void DrawLoading();								// ���[�h�Ɋ֌W����`�揈��
void LoadFont();								// �Q��ȏ�ǂݍ��܂��\��������t�H���g���`����
void GraphSizeChange(GraphSize2 *pgs, int x);	// ������ꂽ�摜�T�C�Y�l���X�N���[���{���ɉ������l�ɂ���
//void LoadGameImageCharacterBody(int x, int* y, char* z);	// �L�����N�^�[�̐g�̕�����ǂݍ���
void LoadGameImageCharacterBody(int x, int* y, const char* z, int a);	// �L�����N�^�[�̐g�̕�����ǂݍ���

BOOL LoadGameImage();
BOOL LoadSE();									// �r�d��ǂݍ���

#endif

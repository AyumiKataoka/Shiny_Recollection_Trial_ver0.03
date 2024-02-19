// �w�`�w�b�_�ɂ���萔���a�w�b�_�̔z�񐔂Ƃ��Ďg�p����x���̏󋵂ɂȂ����ہA�������܂Ƃ߂Ă��̃t�@�C���Ő錾������
#pragma once

#ifndef __GLOBALDEFINITION_H__
#define __GLOBALDEFINITION_H__

#include <DxLib.h>
#include "main.h"

#define HIT_JUDGEMENT_IMAGE_NUMBER_MAP 4			// �}�b�v��ʂł̓����蔻��t���摜���i3�F�Z�[�u�A�C�R���A�S�F���[�h�A�C�R���j
#define COMMU_LINE_MAX 1024							// �P�R�~�����ɑ���ł���ő�s��
#define COMMU_LINE_MAX_EDIT (COMMU_LINE_MAX + 1)	// �G�f�B�b�g���[�h�ŕҏW�ł���ő�s����
//#define BACKGROUND_NUMBER 41						// �w�i�̐�
#define	ALTENATIVE_MAX_NUMBER 3						// �Q�[�����Ŏg���I�����̍ő吔
#define STRBUF_ALTENATIVE_WIDTH 64					// �I�����p���z�e�L�X�g�o�b�t�@�̉��T�C�Y
#define STRBUF_ALTENATIVE_HEIGHT 3					// �I�����p���z�e�L�X�g�o�b�t�@�̏c�T�C�Y

extern int ClickX, ClickY, Button, LogType;	// �N���b�N�����ɕK�v�ȕϐ�

BOOL ClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a);									// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ��i�͈͍��W��float�j

// �L�����N�^�[�ύX�^�C�v
enum CommuCharacterChangeType
{
	// �����x����ւ��A			�u������ւ��A	�����x����ւ��i�����j
	CCC_TRANSPARENCY_NORMAL,	CCC_INSTANT,	CCC_TRANSPARENCY_FAST
};
// �w�i�ύX���@�̎��
enum BackgroundChangeType
{
	// �񓧖��x����ւ��A			�u���b�N�A�E�g�A			�z���C�g�A�E�g
	BACKGROUND_CHANGE_VISIBILITY, BACKGROUND_CHANGE_BLACKOUT, BACKGROUND_CHANGE_WHITEOUT
};
extern BackgroundChangeType g_backgroundchange;
// �a�f�l�؂�ւ��̎��
enum BGMChangeType
{
	BGM_CHANGE_FO_P,	// �ʏ�
	BGM_CHANGE_FO_FI,	// �t�F�[�h�C���Đ�
	BGM_CHANGE_S_P,		// �}��~
	BGM_CHANGE_S_FI		// �}��~���t�F�[�h�C���Đ�
};
// �R�~�����e
struct state
{
	char command[256];
	int move_commu_number;							// �ړ���R�~���h�c
	char name[256];
	char name2[256];								// �����ɒ���Q�l�ڂ̖��O
	char line[256];									// �䎌
	int line_mouse;									// ����ۂ̌��p�N�^�C�v
	int character[3];								// �`�悷��L�����A����
	int character_face_etc[3];						// �L�����̓���\��h�c
	int character_change = CCC_TRANSPARENCY_FAST;	// �L�����N�^�[�ύX�^�C�v
	int character_even_distance;					// �L�����N�^�[�����ψꉻ�̃I���I�t
	int background;									// �`��w�i
	BackgroundChangeType background_change;			// �w�i�ύX�^�C�v
	int bgm;										// �Đ�����a�f�l
	BGMChangeType bgm_change;						// �a�f�l�؂�ւ��^�C�v
	int se;											// �Đ�����r�d
	char altenative_message[3][128];				// �I������
	int altenative_jump[3];							// �I�����̃W�����v��̍s
	// �R�}���h��ύX����
	void CommandChange(char* c) { sprintf_s(command, 256, "%s",c); }	// ���������
	// �e����R�}���h�p���l��ύX����
	void CommandNumberChange(int x) { move_commu_number = x; }	// ���l
	// �䎌���ύX����i���͕�����Łj
	void LineCharacterChange(int x, int y) 	// �ҏW�䎌��p�z��ϐ�,���������
	{
		if (x == 0) { GetKeyInputString(name, y); }
		else { GetKeyInputString(name2, y); }
	}
	// �䎌���ύX����ichar�ϐ��Łj
	void LineCharacterChange(int x, char* c) 	// �ҏW�䎌��p�z��ϐ�,���������
	{
		if (x == 0) { sprintf_s(name, 256, c); }
		else { sprintf_s(name2, 256, c); }
	}
	void LineChange(int x) { GetKeyInputString(line, x); }		// �䎌��ύX����ix�F���������j
	void LineChange(char* c) { sprintf_s(line, 256, c); }		// �䎌��ύX����ichar�ϐ��ŁAc�F���������j
	void LineConnection(char* c) { sprintf_s(line, 256, "%s@%s", line, c); }	// �䎌��ڑ�����ic�F���������j
	void LineMouseChange(int x) { line_mouse = x; }				// ���p�N�^�C�v��ύX����ix�F������l�j
	void CharacterIDChange(int x, int y) { character[x] = y; }	// �L�����N�^�[��S�v�f�ύX����ix�F�ύX����L�����N�^�[,y�F�ύX��̐����j
	// �G�f�B�b�g���[�h��character[x]�̐��l��ς���ۂ̋��ʏ���
	void CharacterIDChange(int x, int y, int z) // �ύX����L�����N�^�[,�ύX����ID���l�̌��̈�,�ύX��̐���
	{
		int a = (int)pow(10, y - 1);
		int b = character[x] / a;
		if (b >= 10) { b %= 10; }
		character[x] = character[x] - a * b + a * z;
	}
	// �L�����̓���\���ύX����				
	void CFECHANGE(int x, int y) { character_face_etc[x] = y; }	// �L�����N�^�[,���l
	// �L�����N�^�[�ύX�^�C�v��ύX����
	void CCCHANGE(int x) { character_change = x; }
	// �L�����ԋ����ψꉻ��ύX����
	void CDUCHANGE(int x) { character_even_distance = x; }	// �ύX���鐔�l
	// �w�i��ύX����
	void BackgroundChange(int x) { background = x; }	// �ύX����
	// �w�i�ύX�^�C�v��ύX����
	void BackgroundChangeTypeChange(BackgroundChangeType x) { background_change = x; }	// �ύX���鐔�l
	// �Đ��a�f�l��ύX����
	void BGMChange(int x) { bgm = x; }	// �a�f�l�p�ϐ�
	// �a�f�l�ύX�^�C�v��ύX����
	void BCTChange(BGMChangeType x) { bgm_change = x; }
	// �r�d���l��ύX����
	void SEChange(int x) { se = x; }	// ��p�ϐ�
	// �I�����������ύX����
	void AlternativeChange(int x, int y) { GetKeyInputString(altenative_message[x], y); }	// �I�����p�ϐ�,���������
	// �I�����������ύX����ichar�ϐ��Łj
	void AlternativeChange(int x, char* c) { sprintf_s(altenative_message[x], 128, c); }	// �I�����p�ϐ�,���������
	// �I�����W�����v��s��ύX����
	void AlternativeJumpChange(int x, int y) { altenative_jump[x] = y; }	// �I�����p�ϐ�,���l
	// �I�񂾑I�����̃W�����v�旚�����Z�b�g����
	static void SetAlternativeMoveNumber(int x, int y) { alternative_move_number[x] = y; }
	// �R�}���h�����擾����
	char* GetCommand() { return command; }
	// �P�l�ڂ̑䎌�喼���擾����
	char* GetLineCharacterName() { return name; }
	// �Q�l�ڂ̑䎌�喼���擾����
	char* GetLineCharacterName2() { return name2; }
	// �䎌��������擾����
	char* GetLine() { return line; };
	// �I�����̕�������擾����
	char* GetAlternativeString(int x) { return altenative_message[x]; }
	// �R�}���h�p���l���擾����
	int GetCommandNumber() { return move_commu_number; }
	// ����ۂ̌��p�N�^�C�v���擾����
	int GetLineMouse() { return line_mouse; }
	// �`�悷��L�����p�ϐ��l���擾����
	int GetCharacter(int x) { return character[x]; }	// �L�����̈ʒu
	// �L�����̓���\��h�c���擾����
	int GetCFE(int x) { return character_face_etc[x]; }	// �L�����̈ʒu
	// �L�����N�^�[�ύX�^�C�v���l���擾����
	int GetCC() { return character_change; }
	// �L�����ԋ����ψꉻ���擾����
	int GetCDU() { return character_even_distance; }
	// �w�i�p�ϐ����擾����
	int GetBackground() { return background; }
	// �a�f�l�p�ϐ����擾����
	int GetBGM() { return bgm; }
	// �r�d�p�ϐ����擾����
	int GetSE() { return se; }
	// �I�����W�����v��p�ϐ����擾����
	int GetAlternativeJump(int x) { return altenative_jump[x]; }	// �I����
	// �I�񂾑I�����̃W�����v�旚���Q�b�g
	static int GetAlternativeMoveNumber(int x) { return alternative_move_number[x]; }
	// �w�i�ύX�^�C�v�p�ϐ����擾����
	BackgroundChangeType GetBackgroundChangeType() { return background_change; }
	// �a�f�l�ύX�^�C�v�p�z��萔���擾����
	BGMChangeType GetBGMCT() { return bgm_change; }
private:
	static int alternative_move_number[COMMU_LINE_MAX];	// �I�񂾑I�����̃W�����v�旚��
};
extern state HM[512][COMMU_LINE_MAX], commu_state_edit[COMMU_LINE_MAX + 1];
// 
// �摜�f�[�^
class ImgData
{
protected:
	// �z�u����鍶�[�A��[���W
	float coordinate_x = 0;
	float coordinate_y = 0;
public:
	int Handle = 0;		// �摜�n���h��
	int size_ox = 0;	// �{���␳���|���Ă��Ȃ����X�̉���
	int size_oy = 0;	// �{���␳���|���Ă��Ȃ����X�̏c��
	float size_x = 0;	// �l�X�ȏ����ň�������
	float size_y = 0;	// �l�X�ȏ����ň����c��
	// ���W�l���`����
	void CoordinateSetting(float x, float y)
	{
		coordinate_x = x;
		coordinate_y = y;
	}
	// �ǂݍ��ݏ���
	BOOL Load(char* s, BOOL x, float bairitu)	// �t�@�C�����A�T�C�Y�ǂݍ��݃t���O�A�{���i�قڒ萔�j
	{
		Handle = LoadGraph(s);
		if (Handle == -1) { return FALSE; }
		// �t���O�������Ă���Ȃ瑼�̕`�揈���ň����摜������`����
		if (x == TRUE)
		{
			GetGraphSize(Handle, &size_ox, &size_oy);
			size_x = size_ox * bairitu;
			size_y = size_oy * bairitu;
		}

		return TRUE;
	}
	// �摜��`�悷��
	void DrawImage() { DrawExtendGraphF(coordinate_x, coordinate_y, coordinate_x + size_x, coordinate_y + size_y, Handle, TRUE); }
	// Y���W���w�肵�ĉ摜��`�悷��
	void DrawImageCoordinateY(float y){ DrawExtendGraphF(coordinate_x, y, coordinate_x + size_x, y + size_y, Handle, TRUE); }
	// �n���h�����擾����
	int GetHandle() { return Handle; }
	// ���W���擾����
	float GetCoordinateX() { return coordinate_x; }
	float GetCoordinateY() { return coordinate_y; }
	// �摜�̊e�I���W�i�������l���擾����
	int GetOriginalSizeX() { return size_ox; }
	int GetOriginalSizeY() { return size_oy; }
	// �摜�̊e�����l���擾����
	float GetSizeX() { return size_x; }
	float GetSizeY() { return size_y; }
};
//									�I�v�V�����ŃA�C�R���ł��Ȃ��ϓ����Ȃ����́i���A���A�����A�^�C�g���A�𑜓x�~�Q�j�A	�I�v�V�����I�����p���A	���b�Z�[�W���x�A				��ʃ��[�h�̎��
extern ImgData	image_dialog[2], image_option[6], image_option_arrow[2], image_option_message_speed[3], image_option_window_type[2],
				//											���ӕ��A											�}�b�v�I�����w�i
				image_text_window[2][4], image_icon_option, image_cautionary_message, image_icon_commu_edit,	image_map_background;
// �����蔻������摜�f�[�^�iHJ�Fhit judgement�j
class ImgDataHJ : public ImgData
{
	BOOL click_judgement;				// �N���b�N����
public:
	void CJChange(BOOL x) { click_judgement = x; }

	BOOL CJReturn() { return click_judgement; }
	// �N���b�N���菈�����s��
	BOOL JudgementClickCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, TRUE, FALSE) == TRUE) 
		{ 
			click_judgement = TRUE; 
			return TRUE;
		}
		return FALSE;
	}
	// ���������̔�����s��
	BOOL JudgementReleaseCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, FALSE, click_judgement) == TRUE) { return TRUE; }
		return FALSE;
	}
};
//					�^�C�g����ʗp�A�}�b�v��ʗp�A									�I����
extern ImgDataHJ	hjimage_title,	hjimage_map[HIT_JUDGEMENT_IMAGE_NUMBER_MAP],	hjimage_alternative[ALTENATIVE_MAX_NUMBER];
// �w�i�摜�f�[�^
class ImgDataBG : public ImgData
{
	BOOL use = FALSE;		// �i�f�o�b�O�p�j�Ăяo���ꂽ�t���O
	char name[256] = "";	// ���O
	static int number;		// �摜����
public:
	enum class EnumConstant
	{
		STAFF_ROOM = 9,
		OFFICE = 24
	};
	ImgDataBG(char* c);
	void SetUse(BOOL x) { use = x; }
	// �T���l�p�w�i��`��
	void DrawImageSamune() { DrawExtendGraphF(coordinate_x, coordinate_y, (coordinate_x + size_x) / 2, (coordinate_y + size_y) / 2, Handle, TRUE); }

	BOOL GetUse() { return use; }
	char* GetName() { return name; }
	int GetNumber() { return number; }
};
extern ImgDataBG bgimage[];
// �����A�摜���̃T�C�Y�{���f�[�^�imagnification�F�{���j
class MagnificationData
{
protected:
	static float magnification;	// �`��֌W�̃Q�[���𑜓x�{��
public:
	void ChangeMagnification(float x) { magnification = x; }
};
// �}�b�v�`���[�g���A���R�~���p�w�i�摜�f�[�^
class ImgDataBGTutorial : public ImgData, public MagnificationData
{
	char path[256];						// �ǂݍ��݃p�X
	static int number;					// �摜����
	static int draw_image_number;		// �����ڂ̉摜��`�悷�邩���ʂ���h�c
	static float screen_y;				// �X�N���[����y���W
	static const int SCREEN_Y_INITIAL;	// �X�N���[���̏���y���W
public:
	ImgDataBGTutorial(char* c)
	{
		sprintf_s(path, 256, c);
		number++;
	}
	// �摜��`�悷��
	void DrawImageTutorial(float y) { DrawExtendGraphF(coordinate_x, y * magnification, coordinate_x + size_x, y * magnification + size_y, Handle, TRUE); }

	static void SetNumber(int value) { number = value; }
	static void SetDrawImageNumber(int value) { draw_image_number = value; }
	static void SetScreenY(float y) { screen_y = y; }
	// �X�N���[���̂x���W�����炷
	static void ScreenYMove();
	// �����i�R�~���s���j�ɉ����ĕ`�悷������摜��ς���
	static void DIMCheck(int x)
	{
		//switch (x - 2)
		switch (x - 1)	// �C���̂��ߐ��l��ύX���Ă���
		{
		case 30:
		case 61:
		case 113:
			draw_image_number = 1;
			break;
		case 31:	
		case 35:
			draw_image_number = 3;
			break;
		case 32:
		case 39:
			draw_image_number = 7;
			break;
		case 33:	draw_image_number = 2;	break;
		case 36:	draw_image_number = 5;	break;
		case 42:	draw_image_number = 10;	break;
		case 47:	draw_image_number = 9;	break;
		case 48:	draw_image_number = 8;	break;
		case 50:	draw_image_number = 11;	break;
		case 52:	draw_image_number = 12;	break;
		case 54:	draw_image_number = 13;	break;
		case 55:	draw_image_number = 0;	break;
		case 92:	draw_image_number = 14;	break;
		case 104:	draw_image_number = 15;	break;
		case 108:	draw_image_number = 16;	break;
		default:
			break;
		}
	}
	// �v�f�����Z�b�g����
	static void Reset();
	
	char* GetPath() { return path; }
	static int GetNumber() { return number; }
	static int GetDrawImageNumber() { return draw_image_number; }
	static float GetScreenY() { return screen_y; }
};
extern ImgDataBGTutorial tutorial_image[];
// �\�ߔ{����ǂݍ��މ摜�f�[�^
class ImaDataName : public ImgData, public MagnificationData
{
public:
	static constexpr int TITLE_BORDER_NUMBER = 211;
	BOOL LoadName(char* c, BOOL x)	// �t�@�C�����A�T�C�Y�ǂݍ��݃t���O
	{
		Handle = LoadGraph(c);
		if (Handle == -1) { return FALSE; }
		// �t���O�������Ă���Ȃ瑼�̕`�揈���ň����摜������`����
		if (x == TRUE)
		{
			GetGraphSize(Handle, &size_ox, &size_oy);
			size_x = size_ox * magnification;
			size_y = size_oy * magnification;
		}
		return TRUE;
	}
	// �{���������񂾏�ō��W�l���`����
	void CoordinateSettingName(float x, float y);
	static int GetTitleBorderNumber() { return TITLE_BORDER_NUMBER; }
};
extern ImaDataName image_title_border[ImaDataName::TITLE_BORDER_NUMBER];
// �\�ߔ{���A�p�X��ǂݍ��މ摜�f�[�^
class ImgData2 : public ImgData, public MagnificationData
{
	char path[256] = "";
	static int notice_count;						// �x�����w�i�̓����x�����p���l
	static const int NOTICE_COUNT_MILLI_SECOND;		// �x�����w�i�̓����x�����ɕK�v�ȃ~���b
public:
	static constexpr int IMC_NUMBER = 9;
	static constexpr int LOG_BACKGROUND_NUMBER = 2;
	static constexpr int LOG_TEXT_WINDOW_NUMBER = 5;
	ImgData2(char* c) { sprintf_s(path, 256, c); }
	// �����ɔ{�����g��Ȃ��ǂݍ��ݏ���
	BOOL Load2(BOOL x)	// �t�@�C�����A�T�C�Y�ǂݍ��݃t���O
	{
		Handle = LoadGraph(path);
		if (Handle == -1) { return FALSE; }
		// �t���O�������Ă���Ȃ瑼�̕`�揈���ň����摜������`����
		if (x == TRUE)
		{
			GetGraphSize(Handle, &size_ox, &size_oy);
			size_x = size_ox * magnification;
			size_y = size_oy * magnification;
		}
		return TRUE;
	}
	// �{���������񂾏�ō��W�l���`����
	void CoordinateSetting2(float x, float y);

	void SetPath(char* c){ sprintf_s(path, 256, c); }
	void DrawImageNotice();			// �x�����w�i��p�̕`�揈��
	static int GetNoticeCount() { return notice_count; }
};
extern ImgData2 bgimage_notice,												bgimage_title,			image_title_logo,		image_title_logo_stilltrial,							bgimage_sukashi,
				image_finish_check,											bgimage_room_teacher,	image_saveload_mode[2],	image_bl_background[ImgData2::LOG_BACKGROUND_NUMBER],	image_map_character[ImgData2::IMC_NUMBER],
				image_log_text_window[ImgData2::LOG_TEXT_WINDOW_NUMBER],	bgimage_non_month;
// �̌��ŏI���p�w�i�摜�Ɋւ���f�[�^
class ImgDataTutorialEnd : public ImgData2
{
	static BOOL white_out;			// �̌��ŏI���w�i�O�̔����ڂ����̓��ߓx�J�E���g��؂�ւ���t���O
	static int count;				// �̌��ŃA���P�[�g�w�i�̓����x�����p���l 
	static int count_wait;			// �̌��ŏI�����[�h�ő���\�ɂȂ�̂ɕK�v�ȃJ�E���g���l
	static const int COUNT_LIMIT;	// �̌��ŃA���P�[�g�w�i�̓����x�����p�̌��E���l
public:
	ImgDataTutorialEnd(char* c) : ImgData2(c) {}
	void DrawImageTutorialEnd();	// �̌��ŏI���w�i��p�̕`�揈��
	static void SetWhiteOut(int x) { white_out = x; }
	static void SetCount(int x) { count = x; }
	static void SetCountWait(int x) { count_wait = x; }
	static void CountReset();	// �̌��ŏI���ɕK�v�ȗv�f�����Z�b�g����
	static int GetCountWait() { return count_wait; }
};
extern ImgDataTutorialEnd bgimage_tutorial_end;
// �}�b�v��ʌ��T�\���O�g�p�摜�f�[�^
class ImgDataMapFrame : public ImgData2
{
	static int frame_number;	// �}�b�v�O�g�摜��
public:
	ImgDataMapFrame(char* c) : ImgData2(c) { frame_number++; }
	static int GetMapFrameNumber() { return frame_number; }	// �}�b�v�O�g�摜�������擾
};
extern ImgDataMapFrame ui_map_month[];
// �}�b�v��ʈړ��m�F�p�摜�f�[�^
class ImgDataMapQuestion : public ImgData2
{
	static int number;	// �摜��
public:
	enum class Type
	{
		FRIEND_ALL = 5
	};
	ImgDataMapQuestion(char* c) : ImgData2(c) { number++; }
	static int GetNumber() { return number; }
};
extern ImgDataMapQuestion image_map_question[];
// �^�C�g����ʃL�����p�摜�f�[�^
class ImgDataTitleCharacter : public ImgData2
{
	static int character_number;
public:
	ImgDataTitleCharacter(char* c) : ImgData2(c) { character_number++; }
	static int GetTitleCharacterNumber() { return character_number; }	
};
extern ImgDataTitleCharacter image_title_character[];
// �Z�[�u���[�h��ʊm�F�摜�f�[�^
class ImgDataSLCheck : public ImgData2
{
	static int image_number;	// �摜��
public:
	// ���
	enum class Type
	{
		SAVE,
		LOAD,
		EXIT
	};

	ImgDataSLCheck(char* c) : ImgData2(c) { image_number++; }
	static int GetSLCImageNumber() { return image_number; }
};
extern ImgDataSLCheck image_sl_check_message[];
// �\�ߔ{���A�p�X��ǂݍ��ޓ����蔻��t���摜�f�[�^
class ImgDataHJ2 : public ImgData2
{
	BOOL click_judgement = FALSE;					// �N���b�N����
public:
	// �Z�[�u���[�h���[�h�A�C�R���̊e�@�\
	enum class SaveLoadIconType
	{
		SAVE,
		LOAD,
		BACK,
		TITLE,
		EXIT
	};

	static constexpr int OPTION_ICON_NUMBER = 5;	// �I�v�V�������Ŏg���A�C�R����
	static constexpr int TEXT_LOG_ARROW_NUMBER = 4;		// �e�L�X�g���O�Ŏg���A�C�R����
	ImgDataHJ2(char* c) : ImgData2(c) {};
	void CJChange(BOOL x) { click_judgement = x; }

	BOOL GetCJ() { return click_judgement; }
	// �N���b�N���菈�����s��
	BOOL JudgementClickCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, TRUE, FALSE) == TRUE)
		{
			click_judgement = TRUE;
			return TRUE;
		}
		return FALSE;
	}

	BOOL JudgementClickCheckFlag(BOOL x);	// �����t���N���b�N���菈�����s��
	// ���������̔�����s��
	BOOL JudgementReleaseCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, FALSE, click_judgement) == TRUE) { return TRUE; }
		return FALSE;
	}
	static int GetOptionIconNumber() { return OPTION_ICON_NUMBER; }
};
extern ImgDataHJ2	image_icon_save_file[][2],			image_icon_sl_page[],				image_icon_new_option[ImgDataHJ2::OPTION_ICON_NUMBER],	image_icon_config_dialog[][2],	image_icon_config_text_speed[][2],
					image_icon_map_move_alternative[2],	image_icon_map_collision_detection,	image_icon_log,											image_icon_log_back,			image_icon_text_log[ImgDataHJ2::TEXT_LOG_ARROW_NUMBER];
// �^�C�g����ʗp�����蔻��t���摜�f�[�^
class ImgDataHJTitle : public ImgDataHJ2
{
	static BOOL flag_count;							// �^�C�g����ʌo�߃t���[�����𑦍ő�ɂ���t���O
	static int menu_number;							// �^�C�g�����j���[�̍��ڐ�
	static int count_frame;							// �^�C�g����ʂł̌o�߃t���[����
	//static int extra_handle;						// �wEXTRA�x�̂R���ډ摜�n���h��
public:
	enum class TYPE
	{
		START,
		LOAD,
		CONTINUE,
		OPTION,
		EXTRA,
		EXIT
	};
	ImgDataHJTitle(char* c, BOOL x) : ImgDataHJ2(c)
	{
		// �ǂݍ��݉񐔂𔼕��ɂ��鏈��
		if (x == TRUE) { menu_number++; }
	}
	static void SetFlagCount(BOOL x) { flag_count = x; }
	static void SetCountFrame(int x) { count_frame = x; }
	static void DrawTitleImage();	// �^�C�g����ʂɊւ���摜��`�悳����
	static BOOL GetFlagCount() { return flag_count; }
	static int GetMenuNumber(){ return menu_number; }
	static int GetCountFrame() { return count_frame; }
};
extern ImgDataHJTitle image_title_menu[][2];
// �m�F��ʗp�I����
class ImgDataIconCheck : public ImgDataHJ2
{
	static const int IMAGE_NUMBER;	// �摜��
public:
	ImgDataIconCheck(char* c) : ImgDataHJ2(c){}
	static int GetImageNumber() { return IMAGE_NUMBER; }
};
extern ImgDataIconCheck image_icon_check[];
// �}�b�v��ʐ����o���A�C�R��
class ImgDataIconMapCharacter : public ImgDataHJ2
{
	static int number;	// �l��
public:
	ImgDataIconMapCharacter(char* c) : ImgDataHJ2(c) { number++; }
	static int GetNumber() { return number; }
};
extern ImgDataIconMapCharacter image_icon_map_character[];
// �t�H���g�f�[�^�i�\��j
class FontData : public MagnificationData
{
	char name[64];			// �t�H���g������
	int size;				// �T�C�Y
	int handle = 0;			// �t�H���g�n���h��
	static int font_number;	// �g���Ă�t�H���g�̐�
public:
	enum class Type
	{
		f1,
		f2,
		f3,
		f4,
		MAP_TITLE,
		SAVE_DATA,
		CONFIG_VOLUME
	};
	// ������ԃt�H���g��`
	FontData(char* c, int x)
	{
		sprintf_s(name, 64, c);
		size = x;
		font_number++;
	}
	
	void Create();
	int	GetHandle() { return handle; }			// �n���h�����擾����
	int GetFontNumber() { return font_number; }	// �g�p�t�H���g�����擾����
};
extern FontData font[];
// ������f�[�^
class StringData
{
	char string[256] = "";	// ������
	int f_id = 0;			// �t�H���g�h�c
	int color;				// �����F
	float c_x;				// x���W
	float c_y;				// x���W
public:
	StringData(unsigned int c, int x) 
	{ 
		color = c;
		f_id = x;
	}
	// ���W�l���`����
	void ChangeCoordinate(float x, float y)
	{
		c_x = x;
		c_y = y;
	}
	// �������`�悷��
	void DrawString() { DrawFormatStringFToHandle(c_x, c_y, color, font[f_id].GetHandle(), string); }
	// x���W���w�肵�ĕ������`�悷��
	void DrawStringSpecifyX(float s_x) { DrawFormatStringFToHandle(s_x, c_y, color, font[f_id].GetHandle(), string); }
	// ��������w�肵�ĕ`�悷��
	void DrawStringSpecifyString(char* c) { DrawFormatStringFToHandle(c_x, c_y, color, font[f_id].GetHandle(), c); }
	// x���W�l���擾����
	float GetX() { return c_x; }
};
extern StringData line_character;
// �Z�[�u�f�[�^�̃T���l
class SaveDataImage : public MagnificationData
{
	int handle = 0;			// �摜�n���h��
	float coordinate_x = 0;	// X���W
	float coordinate_y = 0;	// Y���W
public:
	void SetCoordinate(float x, float y);
	void Blend(int x, BOOL y);	// �摜����������
	void LoadHandel(int x);		// �t�H���_���ɂ���T���l�摜��ǂݍ���
	int GetHandle() { return handle; }
	static constexpr int LIMIT_NUMBER = 60;
};
extern SaveDataImage save_data_image[SaveDataImage::LIMIT_NUMBER];

extern char StringBufAltenative[ALTENATIVE_MAX_NUMBER][STRBUF_ALTENATIVE_HEIGHT][STRBUF_ALTENATIVE_WIDTH + 2];	// �I�����p���z�e�L�X�g�o�b�t�@�i���T�C�Y�i�R�Ԗځj�̐����͓K���j

#endif

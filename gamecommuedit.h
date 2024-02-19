#pragma once
#ifndef __GAMECOMMUEDIT_H__
#define __GAMECOMMUEDIT_H__

#include <DxLib.h>
#include "main.h"

#define EDIT_CHARACTER_ALTERNATIVE_X_LIMIT 6	// �L�����N�^�[�I�����̉��s��

// ���݉��̋@�\��ҏW���Ă��邩
enum EditType
{
	EDIT_DEFAULT,			EDIT_LINES_CHARACTER,	EDIT_LINES_CHARACTER2,	EDIT_LINES,				EDIT_COMMAND,
	// �e�L�X�g�E�B���h�E�̐F						���p�N�^�C�v
	EDIT_TEXT_WINDOW,		EDIT_COMMAND_NUMBER,	EDIT_LINES_MOUSE,		EDIT_CHARACTER_LEFT,	EDIT_CHARACTER_CENTER,
	EDIT_CHARACTER_RIGHT,	EDIT_BACKGROUND,		EDIT_BGM,				EDIT_SE
};
extern EditType g_edittype;
// �L�����N�^�[�̂ǂ̕�����ҏW���Ă��邩�i�����֐��̓s���㏇�Ԃ��t�ɂ��Ă���j
enum EditCharacterType
{
	EDIT_CHARACTER_EXPRESSION,	EDIT_CHARACTER_COSTUME,	EDIT_CHARACTER_PAUSE,	EDIT_CHARACTER_BODY
};
extern EditCharacterType g_editcharactertype;
// �f�t�H���g��Ԃł̑I����
enum EditSelectType
{
	EDIT_SELECT_COMMAND,			EDIT_SELECT_LINES_CHARACTER,	EDIT_SELECT_LINES_CHARACTER2,			EDIT_SELECT_LINES,			EDIT_SELECT_LINES_MOUSE,
	EDIT_SELECT_CHARACTER_LEFT,		EDIT_SELECT_FE_LEFT,			EDIT_SELECT_CHARACTER_CENTER,			EDIT_SELECT_FE_CENTER,		EDIT_SELECT_CHARACTER_RIGHT,
	EDIT_SELECT_FE_RIGHT,			EDIT_CHARACTER_CHANGE_TYPE,		EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM, EDIT_SELECT_BACKGROUND,		EDIT_SELECT_BACKGROUND_CHANGE_TYPE,
	EDIT_SELECT_BGM,				EDIT_SELECT_BGM_CHANGE_TYPE,	EDIT_SELECT_SE
};
#define EDIT_SELECT_PAGE_MAX EDIT_SELECT_SE	// �R�~���G�f�B�^�[�̃y�[�W�E�[
// �����ݓ��͂��Ă���R�}���h�n������
enum CommandInputStringType
{
	CIS_NULL,					CIS_FRAME_AUTO,				CIS_ALTERNATIVE2_1,			CIS_ALTERNATIVE2_2,			CIS_ALTERNATIVE3_1,
	CIS_ALTERNATIVE3_2,			CIS_ALTERNATIVE3_3,			CIS_ALTERNATIVE_JUMP2_1,	CIS_ALTERNATIVE_JUMP2_2,	CIS_ALTERNATIVE_JUMP3_1,
	CIS_ALTERNATIVE_JUMP3_2,	CIS_ALTERNATIVE_JUMP3_3,	CIS_MOVE_SELL,				CIS_MOVE_COMMU,
};
extern CommandInputStringType g_commandinputstring;
// ��������T���l�p���l�̎��
enum EditSamuneSearchType
{
	ESS_CHARACTER_LEFT, ESS_CHARACTER_CENTER, ESS_CHARACTER_RIGHT, ESS_CHARACTER_DISTANCE,	ESS_BACKGROUND,
	ESS_BGM
};
// �w�i�̖��O�i�Ȃ�ƂȂ���肭�����Ă���̂ŕs����N����\���͂���j
//class BackgroundName
//{
//	char name[256];
//public:
//	BackgroundName(char *c){sprintf_s(name, 256, c);}
//	char* GetName(){return name;}
//};
//extern class BackgroundName background_name[];
//BackgroundName::BackgroundName(char *c)
//{
//	//name = c;
//	sprintf_s(name, 256, c);
//}
// 
// �w�i

// �G�f�B�b�g���[�h�֌W�Ŏ�Ɏg����^���O���[�o���ϐ��A�萔
class GlobalStaticEdit
{
	// �w�i�I����
	static int background_alternative_row;					// ��J�[�\��
	static int background_alternative_line;					// �s�J�[�\��
	static int background_alternative_line_limit;			// �s�̍ő吔
	static int background_alternative_line_draw;			// �P�i�ڂɕ`�悷��s
	static const int BACKGROUND_ALTERNATIVE_LINE_NUMBER;	// �P�s�ɕ��Ԕw�i��
public:
	static void SetBackgroundAlternativeRow(int x);
	static void SetBackgroundAlternativeLine(int x);
	static void SetBackgroundAlternativeLineLimit(int x) { background_alternative_line_limit = x; }
	static int GetBackgroundAlternativeRow() { return background_alternative_row; }
	static int GetBackgroundAlternativeLine() { return background_alternative_line; }
	static int GetBackgroundAlternativeLineNumber() { return BACKGROUND_ALTERNATIVE_LINE_NUMBER; }
};

extern char c_global_function[256];	// char�֐��̕Ԃ�l�Ƃ��Ďg���ϐ��i���[�J���z��ϐ���return�ň����Ȃ��̂ŃO���[�o���ϐ��ɂ���K�v������j

extern BOOL commu_edit_input_string;	// �i�䎌��ҏW���Ɂj�����̓��͂��s���Ă����Ԃ�
extern BOOL g_inputbkey_prev;		// ���O�̃L�[�{�[�h�a�L�[�̏��
extern BOOL g_1key_prev;			// ���O�̃L�[�{�[�h1�L�[�̏��
extern BOOL g_2key_prev;			// ���O�̃L�[�{�[�h2�L�[�̏��
extern BOOL g_3key_prev;			// ���O�̃L�[�{�[�h3�L�[�̏��
extern BOOL g_4key_prev;			// ���O�̃L�[�{�[�h4�L�[�̏��
extern BOOL g_5key_prev;			// ���O�̃L�[�{�[�h5�L�[�̏��
extern BOOL g_6key_prev;			// ���O�̃L�[�{�[�h6�L�[�̏��
extern BOOL g_7key_prev;			// ���O�̃L�[�{�[�h7�L�[�̏��
extern BOOL g_8key_prev;			// ���O�̃L�[�{�[�h8�L�[�̏��
extern BOOL g_9key_prev;			// ���O�̃L�[�{�[�h9�L�[�̏��
extern BOOL g_0key_prev;			// ���O�̃L�[�{�[�h0�L�[�̏��
extern BOOL edit_insert_prev;		// ���O�̑}�����씻��̏��
extern BOOL edit_copy_paste_prev;	// ���O�̃R�s�y���씻��̏��
extern BOOL edit_delete_prev;		// ���O�̍s�폜�̏��

extern int edit_row;													// ���ݕҏW���悤�Ƃ��Ă������
extern int edit_row_background;											// ���ݕҏW���悤�Ƃ��Ă���w�i�̃y�[�W
extern int edit_row_bgm;												// ���ݕҏW���悤�Ƃ��Ă���a�f�l�̃y�[�W
extern int edit_row_se;													// ���ݕҏW���悤�Ƃ��Ă���r�d�̃y�[�W
extern int edit_line;													// ���ݕҏW���Ă���s��
extern int edit_play_bgm;												// �G�f�B�b�g���[�h�Ō��ݗ���Ă���a�f�l�h�c
extern int edit_character_id[256][EDIT_CHARACTER_ALTERNATIVE_X_LIMIT];	// �����G�I�����ɕK�v�ȃL�����h�c
extern int edit_character_alternative_row;								// �L�����I�����p�̗�J�[�\��
extern int edit_character_alternative_line;								// �L�����I�����p�̍s�J�[�\��
extern int edit_character_alternative_line_limit;						// �L�����I�����p�̍s�̍ő吔

void GameCommuEdit();											// GAME_COMMU_EDIT��Ԃ̃��C������
void GameCommuEditControl();									// �R�~���G�f�B�b�g��ʑ��쏈��
void GameCommuEditTextWindow(int x);							// �e�L�X�g�E�B���h�E�F�ύX�̍ۂ̋��ʏ���
void GameCommuEditAlternativeInput(CommandInputStringType x);	// �I������������͂̍ۂ̋��ʏ���
void GameCommuEditInputString(int x, BOOL y, char* c);			// �������͏�Ԉڍs�̋��ʏ���
void GameCommuEditLineErase(int x);								// �s���e�S�폜�̋��ʏ���
#pragma region ver0.00704���쎞�R�����g���R�[�h
//void GameCommuEditLineCopy(int x, int y);						// �s���e�R�s�[�̋��ʏ���
#pragma endregion
void GameCommuEditLineCopy(int x, int y, int z);				// �s���e�R�s�[�̋��ʏ���
void GameCommuEditLinesMouse(int x);							// ���p�N�^�C�v�ϐ�����̋��ʏ���
void GameCommuEditLinesCharacter(char* c);						// �䎌��ϐ�������̋��ʏ���
void GameCommuEditCharacter(int x, int y, int z);				// �L�����N�^�[�p�ϐ���������̍ۂ̋��ʏ���
void GameCommuEditCharacterCursorMove(int x);					// �L���������G�I�����u���ړ�����L�������������ړ�����ۂ̋��ʏ���
void GameCommuEditCharacterChange(int x);						// �L�����ύX�^�C�v��ύX����ۂ̋��ʏ���
void GameCommuEditBackground(int x);							// �w�i�ϐ�����̋��ʏ���
void GameCommuEditBGM(int x);									// �a�f�l�ϐ�����̋��ʏ���
void GameCommuEditSE(int x);									// �r�d�ϐ�����̋��ʏ���
void DrawGameCommuEdit();										// �R�~���G�f�B�b�g��ʂ̕`�揈��

char* GetSEString(int x);	// se�̈������當������擾����

BOOL IsINPUTBKeyTrigger();	// �L�[�{�[�hB�L�[
BOOL Is1KeyTrigger();		// 1�L�[
BOOL Is2KeyTrigger();		// 2�L�[
BOOL Is3KeyTrigger();		// 3�L�[
BOOL Is4KeyTrigger();		// 4�L�[
BOOL Is5KeyTrigger();		// 5�L�[
BOOL Is6KeyTrigger();		// 6�L�[
BOOL Is7KeyTrigger();		// 7�L�[
BOOL Is8KeyTrigger();		// 8�L�[
BOOL Is9KeyTrigger();		// 9�L�[
BOOL Is0KeyTrigger();		// 0�L�[
BOOL IsInsertTrigger();		// �}������
BOOL IsCopyPasteTrigger();	// �R�s�y����
BOOL IsDeleteTrigger();		// �s�폜����

int GetEditSamuneNumber(EditSamuneSearchType y);	// �k���Č�������^�C�v�̃T���l���̗v�f�Ɋւ�鐔�l��T���ۂ̋��ʏ���

#endif

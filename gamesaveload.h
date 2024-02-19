#pragma once
#ifndef __GAMESAVELOAD_H__
#define __GAMESAVELOAD_H__

#include <DxLib.h>
#include "main.h"
#include "globaldefinition.h"

#define SL_FILE_PAGE_NUMBER 10	// �Z�[�u�f�[�^�̃y�[�W��
#define SL_FILE_NUMBER 6		// �P�y�[�W���̃Z�[�u�f�[�^��

enum SaveLoadBeforeMode
{
	// �^�C�g���A		�R�~���A			�}�b�v
	SL_BEFORE_TITLE,	SL_BEFORE_COMMU,	SL_BEFORE_MAP,
};
extern SaveLoadBeforeMode g_sl_bm_status;
// �Z�[�u�A���[�h���[�h�Ɋ֌W����֐��Ŏ�Ɏg����^���O���[�o���ϐ��A�萔
class GlobalStaticSaveLoad
{
	static int samune_background_id;	// �T���l�w�i�ۑ��̂��߂ɕK�v�Ȃh�c�ϐ�
public:
	static constexpr int FILE_PAGE_NUMBER = 6;	// �S�y�[�W��
	static constexpr int FILE_NUMBER = 10;		// 1�y�[�W���̃t�@�C����
	static void SetSamuneBackgroundID(int x) { samune_background_id = x; }
	static int GetSamuneBackgroundID() { return samune_background_id; }
	static int GetFilePageNumber() { return FILE_PAGE_NUMBER; }
	static int GetFileNumber() { return FILE_NUMBER; }
};

extern float sl_coordinate_mode_icon_x;							// �i���[�h�ړ��n�A�C�R��x���W
extern float sl_coordinate_icon_save_y;							// �wSAVE�x�A�C�R��y���W
extern float sl_coordinate_icon_load_y;							// �wLOAD�x�A�C�R��y���W
extern float sl_coordinate_icon_back_y;							// �wBACK�x�A�C�R��y���W
extern float sl_coordinate_icon_title_y;						// �wTITLE�x�A�C�R��y���W
extern float sl_coordinate_icon_exit_y;							// �wEXIT�x�A�C�R��y���W
extern float sl_coordinate_icon_sf_x[6];						// �e�Z�[�u�t�@�C���̍��[x���W
extern float sl_coordinate_icon_sf_y[6];						// �e�Z�[�u�t�@�C���̏�[y���W

extern BOOL mode_save;			// �Z�[�uor���[�h��Ԃ𔻕ʂ���
// �^�C�g����ʂ���ړ��������̃t���O
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfsl=click_flag_save_load�j
//extern BOOL cfsl_;		// 

void GameSaveLoadNext(BOOL x, SaveLoadBeforeMode y);	// �Z�[�u�E���[�h��ʈڍs����
void GameSaveLoad();									// GAME_SAVELOAD��Ԃ̃��C������
void GameSaveLoadControl();								// �Z�[�u���[�h��ʑ��쏈��
void GameSave(int x);									// �����ɉ������ԍ��̃f�[�^�ɃZ�[�u����
void GameLoad(int x);									// �����ɉ������ԍ��̃f�[�^�����[�h����
void GameSaveLoadCoordinateSetting();					// �Z�[�u�E���[�h��ʂŎg���l�X�ȍ��W���i�āj��`����
void DrawGameSaveLoad();								// �Z�[�u�E���[�h��ʂ̕`�揈��

void CheckMessage();									// �m�F���b�Z�[�W��Ԃ̃��C������
void CheckMessageControl();								// �m�F���b�Z�[�W���쏈��
void DrawCheckMessage();								// �m�F���b�Z�[�W�̕`�揈��
//�f�o�b�N�p
void dbClickgamesaveload(bool p1 = FALSE, bool p2 = FALSE, bool p3 = FALSE);
bool dbClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, std::string massage = "�����蔻�肠��");

#endif

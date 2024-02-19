#pragma once
#ifndef __GAMECOMMUSELECT_H__
#define __GAMECOMMUSELECT_H__

#include <DxLib.h>
#include "main.h"

#define COMMU_SELECT_CHARACTER_NUMBER 5	// �L�����N�^�[�A�C�R����
#define COMMU_SELECT_C_TYPE_NUMBER 3	// �I���ł���R�~���̎�ނ̐�
// �\�������R�~���̎��
enum CommuUpperState
{
	// ����
	CPS_COMMON,	CPS_MEGURU, CPS_KOGANE, CPS_JURI, CPS_RINZE, CPS_CHIYUKI, CPS_TEST
};
extern CommuUpperState g_commuupperstate;

// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfcs=click_flag_commu_select�j
extern BOOL cfcs_move_title;											// �^�C�g����ʂֈړ�
extern BOOL cfcs_commu_type_change[COMMU_SELECT_C_TYPE_NUMBER];			// �\������R�~���̎�ނ̐؂�ւ���
extern BOOL cfcs_commu_character_change[COMMU_SELECT_CHARACTER_NUMBER];	// �\������R�~���̃L�����̐؂�ւ���

extern int commu_select_display;	// �\����������R�~���̌�

extern float commu_select_coordinate_title_x;										// �wTITLE�x�A�C�R�����[x���W
extern float commu_select_coordinate_title_y;										// �wTITLE�x�A�C�R����[y���W
extern float commu_select_coordinate_c_type_x[COMMU_SELECT_C_TYPE_NUMBER];			// �R�~����ޑI�������[x���W
extern float commu_select_coordinate_c_type_y;										// �R�~����ޑI������[y���W
extern float commu_select_coordinate_alternative_x;									// �R�~���I�������[x���W�iY���W��main.h�j
extern float commu_select_coordinate_character_x;									// �L�����A�C�R�����[x���W
extern float commu_select_coordinate_character_y[COMMU_SELECT_CHARACTER_NUMBER];	// �L�����A�C�R����[y���W

void GameCommuSelectNext();					// �R�~���Z���N�g��ʈڍs����
void GameCommuSelect();						// GameCommuSelect��Ԃ̃��C������
void GameCommuSelectControl();				// �R�~���Z���N�g��ʑ��쏈��
void GameCommuSelectAlternativeCheck();		// �\��������R�~������������
void GameCommuSelectCoordinateSetting();	// �R�~���Z���N�g��ʂŎg���l�X�ȍ��W���i�āj��`����
void DrawGameCommuSelect();					// �R�~���Z���N�g���̕`�揈��

BOOL GameMapControlCTYPECheck(BOOL x);			// �R�~����ޑI�����N���b�N�m�F�p�֐�
BOOL GameMapControlCCharacterCheck(BOOL x);		// �R�~���L�����I�����N���b�N�m�F�p�֐�
BOOL GameMapControlCAlternativeCheck(BOOL x);	// �R�~���I�����N���b�N�m�F�p�֐�

#endif

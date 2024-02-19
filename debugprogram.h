#ifndef __DEBUGPROGRAM_H__
#define __DEBUGPROGRAM_H__

#include <DxLib.h>
#include "main.h"
// ���
enum DebugType
{
	DEBUG_MAIN,				// main�֐��ŌĂяo�����f�o�b�O
	DEBUG_LOAD				// �Z�[�u�f�[�^���[�h�Ƃ͕ʂ̏������[�h�i�㏑���j����
};
// �o�͂��郍�O�̎��
enum class LogOutputType
{
	LOAD_FLAG,
	LOAD_CHECK,
	CELL_CHARACTER,		// �s���莞�̊e�����G
	LOG_MESSAGE,		// ���O���[�h�ŕ\������镶����
	NOT_USE_BACKGROUND	// �g���Ȃ��w�i�̂h�c�Ɩ��O
};
// �f�o�b�O�Ɋ֌W����֐����Ŏ�Ɏg����^���O���[�o���ϐ��A�萔
class GlobalStaticDebug
{
	static BOOL log;	// ���O���o�͂�����
public:
	static BOOL GetLog() { return log; }
};

extern int debug_local_int[2];	// ���[�J���ϐ�����p�ϐ��iint�j

extern double debug_local_double_1;	// ���[�J���ϐ�����p�ϐ��idouble�j
//�t���O
extern BOOL debug_load;					// �Z�[�u�f�[�^���[�h�Ƃ͕ʂ̏������[�h�i�㏑���j����
extern BOOL debug_window;				// �E�B���h�E�𑜓x��ύX����
extern BOOL debug_bgm_load_cut;			// �a�f�l�̃��[�h���s��Ȃ��悤�ɂ���
extern BOOL debug_character_load_cut;	// �����G�̃��[�h���s��Ȃ��悤�ɂ���
extern BOOL debug_escape_check;			// E�L�[�̓��͂ŋ����I��������
extern BOOL debug_keyboard;				// �L�[�{�[�h�ɉ������f�o�b�O�������s��
extern BOOL debug_message;				// ��Ԃɉ��������b�Z�[�W���o�͂���
extern BOOL debug_hit_judge;			// �����蔻���\������
extern BOOL debug_entrance_before;		// ���w�O�R�~���B�e���[�h�ɂ���
extern BOOL debug_dialog_through;		// �𑜓x�_�C�A���O�{�b�N�X�����𖳎����Ďw�肵���𑜓x�ɂ���

void DebugProgram(DebugType x);	// �f�o�b�O�v���O�������ʏ����i�Ăяo���v���O�����̎�ށj
void DebugLoad();				// �Z�[�u�f�[�^���[�h�Ƃ͕ʂ̏������[�h�i�㏑���j����
void DebugWindowChange();		// �E�B���h�E�𑜓x��ύX����
void DebugEscapeCheck();		// E�L�[�̓��͂ŋ����I��������
void DebugProgramControl();		// �f�o�b�O���[�h���̑��쏈��
void DebugLog(LogOutputType x);		// ���O�֌W�̏���
// �`��n
void DebugMessage();															// ��Ԃɉ��������b�Z�[�W���o�͂���
void DebugDrawClickJudge(int x1, int y1, int x2, int y2, int r, int g, int b);	// �N���b�N����p�`��֐�

BOOL DebugLoadCheckCharacter();	// �����G���[�h���s�����m�F����
BOOL DebugLoadCheckBGM();		// �a�f�l���[�h���s�����m�F����
#endif

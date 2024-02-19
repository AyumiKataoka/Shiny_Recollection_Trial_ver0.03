#ifndef __FUNCTIONPROGRAM_H__
#define __FUNCTIONPROGRAM_H__

#include <DxLib.h>
#include "main.h"
//�@�Q�[�W�̎n�_
enum DrawGaugeEnd
{
	GAUGE_END_LEFT,		// �����n�_
	GAUGE_END_RIGHT		// �E���n�_
};

extern int moji_retu_count;	// �`��ɕK�v�ȗ�
extern int moji_gyou_count;	// �`��ɕK�v�ȍs��
// �悭�g����֐�
void FlagChange(BOOL *pf);																		// �t���O��؂�ւ���
void DrawGauge(DrawGaugeEnd x, int y, int z, int a, int b, int c, int d, int e);				// �Q�[�W��`�悷��
void DrawMessageWindow(int a, int b, int c, int d);												// ���b�Z�[�W�E�B���h�E��\������
void DrawMessageWindow2(int a, int b, int c, int d, int x, int co1, int co2);					// ���b�Z�[�W�E�B���h�E��F�A�g�̑������w�肵�ĕ\������
void DrawStringNumber(int x, int y, int number, int absolute_figure, int color, int font);		// String�֐��������Đ�����`�悷��
void NextDrawCharString();																		// �������P�������`�悷��O�ɍs������
void NextNDCNumberCheck();																			// ������`�悷��̂ɉ��񉽍s�K�v�����ׂ�O�ɍs������

void Kaigyou2();	// �e�L�X�g�o�b�t�@�̉��s�����֐�

int CursorMove(int a, int b, int c);															// �J�[�\���𓮂���
int CallDrawX(int a, int b, int c, int d, int e);												// �Q�l�ΐ��ʂŁA���Ώ̂ɕ`�悷����̂�x���W�����߂�
int DrawCharString(int x, int y, int xl, char c, char c2, char c3, int color, int ms);			// �������P�������`�悷��								
int Kaigyou(void);
int DCSNumberCheck(int x, int y, int xl, char c, char c2, char c3, int ms, int *retu, int *gyou);	// ������`�悷��̂ɉ��񉽍s�K�v�����ׁA�������

#endif

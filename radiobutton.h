#pragma once
#ifndef __RADIOBUTTON_H__
#define __RADIOBUTTON_H__

#include <DxLib.h>
#include "main.h"

// �_�C�A���O�{�b�N�X�֌W����֐��Ŏ�Ɏg����^���O���[�o���ϐ��A�萔
class GlobalStaticDialog
{
public:
	static constexpr int WIDTH = 129;
	static constexpr int HEIGHT = 147;	// �c��
	static int GetWidth() { return WIDTH; }
	static int GetHeight() { return HEIGHT; }
};

extern BOOL dialog_not_push;	// �_�C�A���O�{�b�N�X�ł�����Ɓw�Q�[���N���x�������ꂽ���m�F����t���O

//	�_�C�A���O�{�b�N�X�v���V�[�W���[
LRESULT CALLBACK DlgProc1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
#pragma once
#ifndef __RADIOBUTTON_H__
#define __RADIOBUTTON_H__

#include <DxLib.h>
#include "main.h"

// ダイアログボックス関係する関数で主に使われる疑似グローバル変数、定数
class GlobalStaticDialog
{
public:
	static constexpr int WIDTH = 129;
	static constexpr int HEIGHT = 147;	// 縦幅
	static int GetWidth() { return WIDTH; }
	static int GetHeight() { return HEIGHT; }
};

extern BOOL dialog_not_push;	// ダイアログボックスできちんと『ゲーム起動』が押されたか確認するフラグ

//	ダイアログボックスプロシージャー
LRESULT CALLBACK DlgProc1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
#pragma once
#ifndef __GAMECOMMUSELECT_H__
#define __GAMECOMMUSELECT_H__

#include <DxLib.h>
#include "main.h"

#define COMMU_SELECT_CHARACTER_NUMBER 5	// キャラクターアイコン数
#define COMMU_SELECT_C_TYPE_NUMBER 3	// 選択できるコミュの種類の数
// 表示されるコミュの種類
enum CommuUpperState
{
	// 共通
	CPS_COMMON,	CPS_MEGURU, CPS_KOGANE, CPS_JURI, CPS_RINZE, CPS_CHIYUKI, CPS_TEST
};
extern CommuUpperState g_commuupperstate;

// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfcs=click_flag_commu_select）
extern BOOL cfcs_move_title;											// タイトル画面へ移動
extern BOOL cfcs_commu_type_change[COMMU_SELECT_C_TYPE_NUMBER];			// 表示するコミュの種類の切り替えを
extern BOOL cfcs_commu_character_change[COMMU_SELECT_CHARACTER_NUMBER];	// 表示するコミュのキャラの切り替えを

extern int commu_select_display;	// 表示させられるコミュの個数

extern float commu_select_coordinate_title_x;										// 『TITLE』アイコン左端x座標
extern float commu_select_coordinate_title_y;										// 『TITLE』アイコン上端y座標
extern float commu_select_coordinate_c_type_x[COMMU_SELECT_C_TYPE_NUMBER];			// コミュ種類選択肢左端x座標
extern float commu_select_coordinate_c_type_y;										// コミュ種類選択肢上端y座標
extern float commu_select_coordinate_alternative_x;									// コミュ選択肢左端x座標（Y座標はmain.h）
extern float commu_select_coordinate_character_x;									// キャラアイコン左端x座標
extern float commu_select_coordinate_character_y[COMMU_SELECT_CHARACTER_NUMBER];	// キャラアイコン上端y座標

void GameCommuSelectNext();					// コミュセレクト画面移行処理
void GameCommuSelect();						// GameCommuSelect状態のメイン処理
void GameCommuSelectControl();				// コミュセレクト画面操作処理
void GameCommuSelectAlternativeCheck();		// 表示させるコミュを検索する
void GameCommuSelectCoordinateSetting();	// コミュセレクト画面で使う様々な座標を（再）定義する
void DrawGameCommuSelect();					// コミュセレクト時の描画処理

BOOL GameMapControlCTYPECheck(BOOL x);			// コミュ種類選択肢クリック確認用関数
BOOL GameMapControlCCharacterCheck(BOOL x);		// コミュキャラ選択肢クリック確認用関数
BOOL GameMapControlCAlternativeCheck(BOOL x);	// コミュ選択肢クリック確認用関数

#endif

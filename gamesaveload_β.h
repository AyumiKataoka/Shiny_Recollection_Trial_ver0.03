#pragma once
#ifndef __GAMESAVELOAD_H__
#define __GAMESAVELOAD_H__

#include <DxLib.h>
#include "main.h"

#define SL_FILE_PAGE_NUMBER 10	// セーブデータのページ数
#define SL_FILE_NUMBER 6		// １ページ内のセーブデータ数

enum SaveLoadBeforeMode
{
	// タイトル、		コミュ、			マップ
	SL_BEFORE_TITLE,	SL_BEFORE_COMMU,	SL_BEFORE_MAP,
};
extern SaveLoadBeforeMode g_sl_bm_status;

extern float sl_coordinate_mode_icon_x;							// 格モード移動系アイコンx座標
extern float sl_coordinate_icon_save_y;							// 『SAVE』アイコンy座標
extern float sl_coordinate_icon_load_y;							// 『LOAD』アイコンy座標
extern float sl_coordinate_icon_back_y;							// 『BACK』アイコンy座標
extern float sl_coordinate_icon_title_y;						// 『TITLE』アイコンy座標
extern float sl_coordinate_icon_exit_y;							// 『EXIT』アイコンy座標
extern float sl_coordinate_icon_sf_page_x[SL_FILE_PAGE_NUMBER];	// 各セーブファイルページの左端x座標
extern float sl_coordinate_icon_sf_page_y;						// セーブファイルページの上端y座標
extern float sl_coordinate_icon_sf_x[6];						// 各セーブファイルの左端x座標
extern float sl_coordinate_icon_sf_y[6];						// 各セーブファイルの上端y座標

extern BOOL mode_save;			// セーブorロード状態を判別する
extern BOOL save_load_check;	// 指定したデータでセーブ（ロード）するのか確認する
// タイトル画面から移動したかのフラグ
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfsl=click_flag_save_load）
//extern BOOL cfsl_;		// 

void GameSaveLoadNext(BOOL x, SaveLoadBeforeMode y);	// セーブ・ロード画面移行処理
void GameSaveLoad();									// GAME_SAVELOAD状態のメイン処理
void GameSaveLoadControl();								// セーブロード画面操作処理
void GameSave(int x);									// 引数に応じた番号のデータにセーブする
void GameLoad(int x);									// 引数に応じた番号のデータをロードする
void GameSaveLoadCoordinateSetting();					// セーブ・ロード画面で使う様々な座標を（再）定義する
void DrawGameSaveLoad();								// セーブ・ロード画面の描画処理

//ここから将伍P追加関数

void CheckMessage();
void CheckMessageControl();
void DrawCheckMessage();

#endif

#pragma once
#ifndef __GAMESAVELOAD_H__
#define __GAMESAVELOAD_H__

#include <DxLib.h>
#include "main.h"
#include "globaldefinition.h"

#define SL_FILE_PAGE_NUMBER 10	// セーブデータのページ数
#define SL_FILE_NUMBER 6		// １ページ内のセーブデータ数

enum SaveLoadBeforeMode
{
	// タイトル、		コミュ、			マップ
	SL_BEFORE_TITLE,	SL_BEFORE_COMMU,	SL_BEFORE_MAP,
};
extern SaveLoadBeforeMode g_sl_bm_status;
// セーブ、ロードモードに関係する関数で主に使われる疑似グローバル変数、定数
class GlobalStaticSaveLoad
{
	static int samune_background_id;	// サムネ背景保存のために必要なＩＤ変数
public:
	static constexpr int FILE_PAGE_NUMBER = 6;	// 全ページ数
	static constexpr int FILE_NUMBER = 10;		// 1ページ内のファイル数
	static void SetSamuneBackgroundID(int x) { samune_background_id = x; }
	static int GetSamuneBackgroundID() { return samune_background_id; }
	static int GetFilePageNumber() { return FILE_PAGE_NUMBER; }
	static int GetFileNumber() { return FILE_NUMBER; }
};

extern float sl_coordinate_mode_icon_x;							// 格モード移動系アイコンx座標
extern float sl_coordinate_icon_save_y;							// 『SAVE』アイコンy座標
extern float sl_coordinate_icon_load_y;							// 『LOAD』アイコンy座標
extern float sl_coordinate_icon_back_y;							// 『BACK』アイコンy座標
extern float sl_coordinate_icon_title_y;						// 『TITLE』アイコンy座標
extern float sl_coordinate_icon_exit_y;							// 『EXIT』アイコンy座標
extern float sl_coordinate_icon_sf_x[6];						// 各セーブファイルの左端x座標
extern float sl_coordinate_icon_sf_y[6];						// 各セーブファイルの上端y座標

extern BOOL mode_save;			// セーブorロード状態を判別する
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

void CheckMessage();									// 確認メッセージ状態のメイン処理
void CheckMessageControl();								// 確認メッセージ操作処理
void DrawCheckMessage();								// 確認メッセージの描画処理
//デバック用
void dbClickgamesaveload(bool p1 = FALSE, bool p2 = FALSE, bool p3 = FALSE);
bool dbClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, std::string massage = "当たり判定あり");

#endif

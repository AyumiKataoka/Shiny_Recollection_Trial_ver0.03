#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#include <DxLib.h>
#include "main.h"

#define CONFIG_MESSEAGE_GRAPH_MODE_X 100	// 画面モード支点X座標
#define CONFIG_MESSEAGE_GRAPH_MODE_Y 100	// 画面モード支点Y座標
#define CONFIG_MESSEAGE_TITLE_Y 100			// 『TITLE』Ｙ座標
#define CONFIG_LINE_SPACE 72				// 設定モード行間
#define CONFIG_MESSAGE_SPEED_NUMBER 3		// メッセージスピード選択肢数

// オプション項目『画面モード』の種類
enum IMGOptionWindowType
{
	IO_WINDOW_TYPE_FULL_SCREEN,	// フルスク
	IO_WINDOW_TYPE_WINDOW		// ウィンドウ
};

extern char* config_message_message_speed[3];	// 設定モードで描画される『文字スピード』選択の文字の種類

extern BOOL config_before_mc;	// メインコミュから設定モードに来たか
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfc=click_flag_config）
extern BOOL cfc_move_title;				// タイトル画面へ移動
extern BOOL cfc_window_mode_change[2];	// ウィンドウ、フルスクリーンを切り替える
extern BOOL cfc_screen_change_720p;		// ウィンドウ解像度を720pxにする
extern BOOL cfc_screen_change_1080p;	// ウィンドウ解像度を1080pxにする
extern BOOL cfc_bgm_down;				// ＢＧＭ音量を下げる
extern BOOL cfc_bgm_up;					// ＢＧＭ音量を上げる
extern BOOL cfc_se_down;				// ＳＥ音量を減少
extern BOOL cfc_se_up;					// ＳＥ音量を増加
extern BOOL cfc_message_slow;			// メッセージ速度を遅く
extern BOOL cfc_message_fast;			// メッセージ速度を速く
extern BOOL cfc_dialog_change;			// ダイアログボックス表示フラグを切り替え
extern BOOL cfc_text_window_clear[2];	// メッセージ透過度を増減

extern float config_retu2_x;									// ２列目項目X座標
extern float config_coordinate_icon_back_x;						// 『BACK』アイコン左端x座標
extern float config_coordinate_icon_back_y;						// 『BACK』アイコン上端y座標
extern float config_coordinate_full_screen_switch_x[2];			// フルスクリーン切り替えスイッチX座標
extern float config_coordinate_full_screen_switch_y;			// フルスクリーン切り替えスイッチY座標
extern float config_coordinate_screen_resolution_switch_y;		// 画面解像度切り替えスイッチY座標
extern float config_coordinate_screen_resolution_switch_1920_x;	// 画面解像度切り替えスイッチ（1920×1080）X座標
extern float config_bgm_message_y;								// ＢＧＭ音量関係Y座標
extern float config_coordinate_arrow_down_x;					// 左矢印左端X座標
extern float config_bgm_volume_up_x;							// ＢＧＭ『→』文字X座標
extern float config_se_message_y;								// ＳＥ音量関係Y座標
extern float config_message_speed_y;							// コミュメッセージ速度関係Y座標
extern float config_text_window_clear_y;						// テキストウィンドウ透過度関係Y座標
extern float config_coordinate_message_speed_x[3];				// メッセージ速度選択肢各左端x座標

void GameConfigNext(BOOL x);						// 設定モード移行処理
void GameConfig();										// GAME_CONFIG状態のメイン処理
void GameConfigControl();								// 設定画面時操作処理
void GameConfigMessageSpeedChange(BOOL x);				// コミュの文字スピードに関する要素を変更する
void CoordinateSetting();								// ゲームで使う様々な座標を（再）定義する
void GameConfigCoordinateSetting();						// 設定画面で使う様々な座標を（再）定義する
void DrawGameConfig();									// 設定画面時描画処理
void DrawOptionArrow(int x , int y, float z, BOOL a);	// 設定モードの矢印を描画する際の共通処理
#endif

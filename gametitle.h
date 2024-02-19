#ifndef __GAMETITLE_H__
#define __GAMETITLE_H__

#include <DxLib.h>
#include "main.h"

#define TITLE_MOVE_START_MAX_FLAME 120				// 『START』選択時からコミュモードへ移行するのに必要なフレーム数
#define TITLE_MENU_MESSAGE_X 480					// タイトル画面メニュー選択肢のＸ座標（仮）
#define START_MESSEAGE_Y 60						// 『START』Ｙ座標
#define CONFIG_MESSEAGE_Y (START_MESSEAGE_Y + 200)	// 『CONFIG』Ｙ座標（仮）
#define EXIT_MESSAGE_Y (CONFIG_MESSEAGE_Y + 200)	// 『EXIT』Ｙ座標（仮）
#define TITLE_MENU_MESSAGE_SPACE_Y 290				// タイトル画面の各メニューのy座標間隔
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cft=click_flag_title）
// なぜかsaveloadファイルのコードに使われていたのでそのまま
extern BOOL cft_exit_main_commu;		// コミュ画面に移動
extern BOOL cft_quit_game;				// ゲームを終了
extern BOOL cft_sound_room_main_commu;	// サウンドルーム画面に移動
extern BOOL cft_commu_list;				// コミュリスト画面に移動
//extern BOOL cft_commu_edit;				// コミュエディット画面に移動

extern BOOL flag_next_start;	// ニューゲーム開始時の移動処理フラグ

extern int next_start_frame_count;	// 『START』選択からの経過フレーム数

extern float coordinat_title_choice_left;		// 左側選択肢始点x座標
extern float coordinat_title_choice_right;		// 右側選択肢始点x座標
extern float coordinat_title_choice_load_y;		// 選択肢『LOAD』y座標
extern float coordinat_title_choice_config_y;	// 選択肢『CONFIG』y座標
extern float coordinat_title_choice_exit_y;		// 選択肢『EXIT』y座標

void GameTitleNext();				// タイトル画面状態以降処理
void GameTitle();					// GameTitle状態のメイン処理
void GameTitleControl();			// タイトル画面操作処理
void GameTitleFlame();				// タイトルモード時１フレーム毎に行われる処理
void GameTitleCoordinateSetting();	// タイトル画面で使う様々な座標を（再）定義する
void DrawGameTitle();				// タイトル画面の描画処理

int DrawTitleStringColor(float x, float y, int breadth, float length);	// タイトルメニューの文字色を返す

#endif

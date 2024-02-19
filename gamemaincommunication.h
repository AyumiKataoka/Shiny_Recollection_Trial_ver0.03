#ifndef __GAMEMAINCOMMUNICATION_H__
#define __GAMEMAINCOMMUNICATION_H__

#include <DxLib.h>
#include "main.h"

#define COMMU_MESSEAGE_TITLE_Y 100	// 『TITLE』Ｙ座標
#define	COMMU_CHARACTER_MAX 3			// コミュで描画されるキャラクターの最大人数
// 台詞を描画する際に必要なポイントの設定に応じた増加量（１文字につき60必要で１フレームにxポイント増加する）
#define COMMU_COUNT_SLOW 8		// 遅い
#define COMMU_COUNT_NORMAL 12	// 普通
#define COMMU_COUNT_FAST 30		// 速い

#define COMMU_CHARACTER_CHANGE_MAX 60		// キャラ変更処理に使うフレーム数
#define COMMU_CHARACTER_CHANGE_MAX_FAST 30	// キャラ高速変更処理に使うフレーム数
#define COMMU_EYE_ANIMATION_FLAME 6			// 瞬きアニメーションの１枚を映すフレーム数
#define COMMU_MOUSE_ANIMATION_NUMBER 13		// 口パク関連の処理に必要な定数
#define COMMU_MOUSE_ANIMATION_FLAME 6		// 口パクアニメーションの１枚を映すフレーム数
#define COMMU_BACKGROUND_FLAME_MAX 60		// 背景変更処理に使うフレーム数の最大値
#define COMMU_CHARACTER_SPACE 630.0f		// 左右にずれる際の移動ピクセル数

enum CommuStatusType
{
	// 通常、				フレーム数による自動進行、	オート効果音、		選択肢
	COMMU_STATUS_NORMAL,	COMMU_STATUS_AUTO,			COMMU_STATUS_SE,	COMMU_STATUS_ALTENATIVE
};
extern CommuStatusType g_commustatus;
// 表示選択肢の種類（個数）
enum AltenativeNumberType
{
	// ２つ、				３つ
	ALTENATIVE_NUMBER_2,	ALTENATIVE_NUMBER_3
};
extern AltenativeNumberType g_altenativenumber;
// コミュ自動進行状態の種類
enum CommuAutoType
{
	// 通常、			オート、		スキップ
	COMMU_AUTO_NORMAL,	COMMU_AUTO_ON,	COMMU_AUTO_SKIP
};
extern CommuAutoType g_commuauto;
// 描画されるキャラの特殊表情タイプ
enum CommuCharacterFaceType
{
	// 通常、	閉じ目、		笑顔閉じ目
	CCF_NORMAL, CCF_CLOSE_EYE,	CCF_CLOSE_EYE_SMILE
};
extern CommuCharacterFaceType g_commu_character_face[3];

class AlternativeCoordinate
{
	static float y_upper;	// 上側y座標	
	static float y_under;	// 下側y座標
public:
	static void SetYUpper(float x) { y_upper = x; }
	static void SetYUnder(float x) { y_under = x; }
	static float GetYUpper() { return y_upper; }
	static float GetYUnder() { return y_under; }
};
// テキストログ
class TextLog
{
	char character[32] = "";			// 台詞主
	char line[128] = "";				// 台詞
	int line_number = 0;				// コミュ内での行
	static BOOL mode;					// 表示させるフラグ
	static int top_id_now;				// 現在最上部に表示されている台詞のＩＤ番号
	static int next_input_id;			// 次にＩＤを代入する番号
	static int page;					// ページ数
	static const int PAGES_LINE_NUMBER;	// １ページ毎の台詞数
public:
	void Input();	// テキストログを入力する
	static void Draw();	// 描画する
	static void SetMode(BOOL x) { mode = x; }
	static void SetPage(int x);
	static void Reset();
	char* GetLine() { return line; }
	static BOOL GetMode() { return mode; }
	static int GetNIID() { return next_input_id; }
	static int GetPage() { return page; }
	static int GetPagesLineNumber() { return PAGES_LINE_NUMBER; }
};
extern class TextLog text_log[];

extern BOOL commu_mode_background;	// ＳＥが変わりきるまでクリック操作できないようにするフラグ
extern BOOL commu_mode_distance;	// 表示されているキャラが２人の際、均等に並べるか
extern BOOL commu_mode_menu;		// メニューの内容を表示する
extern BOOL commu_mode_text_off;	// テキストファイル含めた全てのＵＩを非表示にする
extern BOOL commu_before_cs;		// コミュの閲覧を始める前はコミュセレクトモードだったか判別する
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfgmc=click_flag_game_main_communication）
extern BOOL cfgmc_move_title;		// タイトル画面へ移動
extern BOOL cfgmc_cell_count;		// コミュの情報を次のものに
extern BOOL cfgmc_change_auto;		// オートモード切り替えを
extern BOOL cfgmc_change_skip;		// スキップモード切り替えを
extern BOOL cfgmc_exit_save;		// セーブモードへ移行
extern BOOL cfgmc_exit_load;		// ロードモードへ移行
extern BOOL cfgmc_exit_option;		// 設定モードへ移行
extern BOOL cfgmc_change_menu;		// メニューモード切り替えを
extern BOOL cfgmc_change_text_off;	// テキストオフモード切り替えを

extern char String[][256];																					// 文字列描画用テストコード
extern char* commu_bgm_name;																				// コミュでＢＧＭが再生された際、表示される名前

extern int CursorX, CursorY;	// 仮想画面上での文字表示カーソルの位置
extern int KeyWaitFlag;			// ボタン押し待ちフラグ
extern int Count;				// フレームカウンタ

extern int commu_number;											// 現在参照されているコミュＩＤ
extern int cell_number;												// 参照されるセルの行数
extern int commu_character[3];										// 描画されるキャラ
extern int commu_character_blink_limit[3];							// まばたきをし終えるまでの残りフレーム数
extern int commu_character_talk_limit[3];							// 口パクをし終えるまでの残りフレーム数
extern int commu_character_before[3];								// 切り替え前のキャラクター
extern int commu_character_after[3];								// 切り替え後のキャラクター
extern int commu_character_visibility_count[COMMU_CHARACTER_MAX];	// キャラクター不透明度切り替えが完了するまでのフレーム数
extern int commu_background;										// 背景
extern int commu_background_before;									// 切り替え前の背景
extern int commu_background_visibility_count;						// 背景切り替えが完了するまでのフレーム数
extern int commu_bgm_flame;											// ＢＧＭが切り替わってからの経過フレーム数
extern int commu_altenative_string_line[3];							// 各選択肢の行数
extern int commu_message_point;										// 台詞を描画する際に必要なポイント
extern int commu_auto_count;										// オートモードで次行に自動で行くためのカウント
extern int commu_frame_auto_count;									// 『frame_auto』で次行に自動で行くためのカウント
extern int text_window_clear_percentage;							// テキストウィンドウ透過度

extern float commu_play_time;						// プレイ時間（秒）
extern float commu_altenative_string_center_x[3];	// 選択肢文字列中心x座標
extern float commu_coordinate_icon_auto_x;			// 『auto』アイコンx座標
extern float commu_coordinate_icon_auto_y;			// 『auto』アイコンy座標
extern float commu_coordinate_icon_skip_y;			// 『SKIP』アイコン上端y座標
extern float commu_coordinate_icon_save_y;			// 『SAVE』アイコン上端y座標
extern float commu_coordinate_icon_load_y;			// 『LOAD』アイコン上端y座標
extern float commu_coordinate_icon_option_y;		// 『OPTION』アイコン上端y座標
extern float commu_coordinate_icon_menu_y;			// 『MENU』アイコン上端y座標
extern float commu_coordinate_icon_tf_x;			// 『TEXT OFF』アイコン左端x座標

void GameMainCommunicationNext(int x, BOOL y, int z);	// コミュ画面移行処理
void GameMainCommunication();							// GameMainCommunication状態のメイン処理
void GameMainCommunicationControl();					// コミュ画面操作処理
void GameMainCommunicationAuto();						//	オートモードがＯＮになる際の処理
void GameMainCommunicationFlame();						// コミュモード時１フレーム毎に行われる処理
void GameMainCommunicationNextLine();					// コミュ状態で、次行の処理を行う
void GameMainCommunicationEnd();						// コミュ終了処理
void GameMainCommunicationAltenative(int x);			// 選択肢を選んだ際の共通処理
void GameMainCommunicationCoordinateSetting();			// コミュ画面で使うアイコンの座標を（再）定義する処理
void GameMainCommunicationMoji(BOOL x);					// コミュ画面で文字を描画するために行う処理
void GameMainCommunicationMojiAltenative(int x);		// コミュ画面で選択肢用文字を描画するために行う処理
void DrawGameMainCommunication();						// コミュ画面の描画処理
void DrawTextWindow(int x);								// テキストウィンドウを描画する

int DrawGameMainCommunicationMouseAnimation(int i);		// 描画する口パクの画像を判別する
#endif

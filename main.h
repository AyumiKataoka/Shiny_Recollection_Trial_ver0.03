#ifndef __MAIN_H__
#define __MAIN_H__

#include <DxLib.h>
#include <ctime>
#include <cstdlib>	// 乱数（rand()）生成のために必要
#include <iostream>
#include <math.h>	// 累乗計算のために必要
#include <sys/stat.h>	// ファイルが存在するか調べるために必要
#include <fstream>
#include <filesystem>

//#include "gamemain.h"
#include "loading.h"
#include "functionprogram.h"
#include "gametitle.h"
#include "gamemaincommunication.h"
#include "gamemap.h"
#include "gamemusic.h"
#include "gameconfig.h"
#include "gamesaveload.h"
#include "gametutorialend.h"
#include "soundroom.h"
#include "gamecommuselect.h"
#include "gamecommuedit.h"
#include "globaldefinition.h"
#include "radiobutton.h"
// デバッグ、下書き用
#include "debugprogram.h"

#define PI 3.1415926535897932384626433832795f	// 円周率
//#define MODE_NUMBER 8							// モードの数（パズル、エンドレス、アーケード、ＶＳ、設定、説明、終了）
#define MODE_DEFAULT_X 100			// 各モードを描画する文字の絶対的Ｘ座標数値
#define MODE_DEFAULT_Y 180						// 各モードを描画する文字の絶対的Ｙ座標数値（下書き）
#define MODE_CHANGE_Y 33						// 各モードを描画する際のＹ座標のずれ（下書き）
#define WINDOW_SIZE_X 1920						// ゲームウィンドウのオリジナルサイズ横幅
#define WINDOW_SIZE_Y 1080						// ゲームウィンドウのオリジナルサイズ縦幅
#define	SAVE_DATA_NUMBER 60						// セーブデータ個数（オートセーブは除く）
#define COMMU_NUMBER_MAX 256					// 作成できるコミュの最大数
#define COMMU_MAP_LIMIT 10						// マップ画面で扱われるコミュの上限
#define CS_COMMU_LIMIT 10						// コミュセレクト画面で扱われるコミュ選択肢の上限

#define MOJI_SIZE 24	// 文字のサイズ
// 仮想テキストバッファの横サイズ縦サイズ
#define STRBUF_WIDTH 50	// 元々は48だったがシャニリコ鯖に『一行最大25文字』と書かれていたので、そちらに合わせるように修正
#define STRBUF_HEIGHT 20

#define STR(var) #var
// グローバル変数
// 時間計測用変数
extern int g_lasttime;
extern float g_frametime;
extern int g_timerstart;

enum GameState
{
	GAME_FIRST_LOAD,	GAME_OPENING,	GAME_TITLE,		GAME_MENU,			GAME_MAIN_COMMUNICATION,	
	GAME_MAP,			GAME_CONFIG,	GAME_SAVELOAD,	GAME_TUTORIAL_END,	GAME_SOUNDROOM,
	GAME_COMMU_SELECT,	GAME_COMMU_EDIT,
	GAME_CLEAR,			
	GAME_PAUSE,			GAME_WINNERMESSAGE,
	GAME_TUTORIAL,		GAME_CONTINUE,		GAME_DEMONSTRATION,	GAME_ENDING,
};
extern GameState g_gamestate;
enum SaveFileID
{
	SAVE_ID_NULL, SAVE_ID_001
};
extern SaveFileID g_saveid;
// メッセ―ジ速度の種類
enum CommuMessageSpeedType
{
	// 遅い、					普通、						速い
	COMMU_MESSAGE_SPEED_SLOW, COMMU_MESSAGE_SPEED_NORMAL, COMMU_MESSAGE_SPEED_FAST
};
extern CommuMessageSpeedType g_commumessagespeed;
// クリック判定チェックの種類
enum ClickFlagCheckType
{
	// 通常（特殊な条件がない）、	コミュ状態・メニュー関係、	コミュ状態・テキストオフモード関係
	CFC_NORMAL,						CFC_COMMU_MENU,				CFC_COMMU_TEXT
};
// コミュの種類（名前）
enum class CommuType
{
	OP,
	TUTORIAL,
	STILL_OP,		// スチル体験版用OP
	MEGURU0,		// 0は出会いコミュ
	MEGURU1,
	MEGURU2,
	MEGURU5,
	KOGANE0,		// 0は出会いコミュ
	KOGANE1,
	KOGANE2,
	KOGANE_STILL,
	JURI0,			// 0は出会いコミュ
	JURI1,
	JURI2,
	JURI_STILL,
	RINZE0,			// 0は出会いコミュ
	RINZE1,
	RINZE2,
	CHIYUKI0,		// 0は出会いコミュ
	CHIYUKI1,
	CHIYUKI2,
	CHIYUKI_STILL,
	FRIEND,				// フレンドコミュ
	TUTORIAL_END,		// 体験版終了
	TUTORIAL_STILL_END,	// スチル体験版終了
	TEST1,
	TEST2,
	TEST3,
	TEST4,
	TEST5,
	EDIT
};

#pragma region 構造体
// セーブデータを保存するために必要な構造体（どうしても最後列以外の場所に要素を増やしたいなら書き込み用の構造体を別個に用意する？）
struct SystemData
{
	BOOL full_screen;					// フルスクリーンのフラグ
	BOOL screen_resolution;				// 解像度のフラグ（TRUEなら1080px）
	int vol_bgm;						// ＢＧＭ音量
	int vol_se;							// ＳＥ音量
	int text_window_clear;				// テキストウィンドウ透明度
	CommuMessageSpeedType string_speed;	// 文字スピード
	BOOL dialog_appear;					// ダイアログボックス表示フラグ
	void SetECL(int x, BOOL y) { edit_character_load[x] = y; };
	BOOL GetECL(int x) { return edit_character_load[x]; }
private:
	BOOL edit_character_load[9];		// エディットモードでの個別読み込みフラグ（もしかしたら後々立ち絵の人物が追加されるかもしれないので多く設定している）
};
extern SystemData system_data;
// コミュのステータス（コミュの種類の配列変数は上部にある『CommuType』enumクラス）
struct CommuData
{
	// 特定のコミュだけ表示されるタイミングの種類
	enum class MapUpperType
	{
		DEFAULT = 3,
		MEGURU0 = 5,
		KOGANE0,
		JURI0,
		RINZE0,
		CHIYUKI0,
		FRIEND_CG_MEGURU
	};
	int id;					// コミュＩＤ
	char path[256];			// パス
	//const char* path;		// パス
	char title[256];		// コミュタイトル
	int appear_timing;		// 出現タイミング
	int character_icon;		// キャラクターアイコン
	int map_zone;			// 所在マップ場所
	float map_coordinate_x;	// 中心からの出現Ｘ座標ずれ
	float map_coordinate_y;	// 中心からの出現Ｙ座標ずれ
	void SetTitle(char* c) { sprintf_s(title, 256, c); }
	char* GetTitle() { return title; }	
	int GetID() { return id; }
	static void SetGMapUpperType(MapUpperType x) { g_mapuppertype = x; }
	static void SetData(int x, int y);	// 様々なデータをセットする 
	static MapUpperType GetGMapUpperType() { return g_mapuppertype; }
private:
	static MapUpperType g_mapuppertype;
};
extern CommuData commu_data[COMMU_NUMBER_MAX], commu_data_map[COMMU_MAP_LIMIT], commu_data_map_choice;
// コミュ閲覧モードで表示されるコミュの情報
class CSDisplayCommuState
{
public:
	int id;		// コミュのＩＤ
	char* name;	// コミュタイトル
	void StateReset()
	{
		id = 0;
		name = (char*)"";
	}
	void StateChange(CommuData* x)
	{
		id = x->id;
		name = x->title;
	}
};
extern CSDisplayCommuState cs_displat_commu[CS_COMMU_LIMIT];
#pragma endregion
// 様々なモードや関数で使われる疑似グローバル変数
class GlobalStaticVariable
{
	static int commu_number;						// コミュ総数
	static const BOOL mode_trial;					// 体験版モード用フラグ
	static const int RESOLUTION_SIZE_ORIGINAL_X;	// オリジナル横解像度
protected:
	static constexpr int CELL_LIMIT = 1024;	// 行限界数
public:
	static void SetCommuNumber(int num) { commu_number = num; }
	static void CommuNumberCount() {commu_number++; }
	static BOOL GetModeTrial() { return mode_trial; }
	static int GetCommuNumber() { return commu_number; }
	static int GetRSOriginalX() { return RESOLUTION_SIZE_ORIGINAL_X; }
	static int GetCellLimit() { return CELL_LIMIT; }
};
// コミュセーブデータ構造体（仮）
struct CommuSaveData : public GlobalStaticVariable
{
	static constexpr int CHARACTER_NUMBER = 5;
private:
	char time[256] = "";							// 年月日時分文字列
	int week;										// ゲーム時間の月週
	int commu_id;									// コミュ（0ならマップ画面）
	int cell;										// コミュ内行
	int map_appear_id;								// 特定のコミュだけ表示されるタイミング
	int number_met[CHARACTER_NUMBER];				// 各キャラのコミュ選択回数
	int line_jump[CELL_LIMIT];						// 選択肢、行ジャンプ先履歴
	BOOL trial_still_viewed[CHARACTER_NUMBER] = {};	// スチル体験版で使うキャラ別のコミュを見終えたフラグ
public:
	float play_second;	// プレイ時間（秒）
	void ChangeTimeString()
	{
		DATEDATA Date;		// DXライブラリ独自の構造体
		GetDateTime(&Date);	// 現在時刻を得る
		sprintf_s(time, 256, "%04d/%02d/%02d %d：%02d", Date.Year, Date.Mon, Date.Day, Date.Hour, Date.Min);
	}
	// セーブデータから読み込んで代入する場合
	void ChangeTimeString(char* c) { sprintf_s(time, 256, c); }

	void ChangeSaveData(int import_w, int import_co, int import_ce, int x)	// ゲーム内月週,コミュＩＤ,コミュ行,アイコン出現タイプ
	{
		week = import_w;
		commu_id = import_co;
		cell = import_ce;
		map_appear_id = x;
	}
	void SetNumberMet(int x, int y) { number_met[x] = y; }
	// 選択肢のジャンプ先履歴
	void SetLineJump();
	// 別のセーブデータからジャンプ先履歴取得
	void SetLineJumpSave(int x, int y) { line_jump[x] = y; }

	void SetTrialStillViewed(int x, BOOL y) { trial_still_viewed[x] = y; }
	// メンバ変数を取得
	BOOL GetTrialStillViewed(int x) { return trial_still_viewed[x]; }	// スチル体験版で使うキャラ別のコミュを見終えたフラグ
	char* GetTimeString() { return time; }								// 年月日時分文字列
	int GetWeek() { return week; }										// ゲーム内月週
	int GetCommuID() { return commu_id; }								// コミュＩＤ
	int GetCell() { return cell; }										// コミュ行
	int GetMapAppearID() { return map_appear_id; }						// 特定のコミュだけ表示されるタイミング
	int GetNumberMet(int x) { return number_met[x]; }					// 各キャラのコミュ選択回数
	int GetLineJump(int x) { return line_jump[x]; }
	static int GetCharacterNumber() { return CHARACTER_NUMBER; }
	// 描画系
};
extern CommuSaveData commu_save_data[SAVE_DATA_NUMBER], commu_save_data_memory;
// キートリガー処理
class KeyTrigger
{
	static constexpr int KEY_NUMBER = 2;			// 使われるキーの個数
	static BOOL key_prev[KeyTrigger::KEY_NUMBER];	// 直前の状態
public:
	enum class Type
	{
		LEFT,
		RIGHT
	};
	static BOOL Trigger(int key, KeyTrigger::Type y);	// キートリガー処理
};

extern BOOL g_upkey_prev[2];	// 直前のＡボタンの状態
extern BOOL g_downkey_prev[2];	// 直前の下キーの状態
extern BOOL g_leftkey_prev[2];	// 直前の左キーの状態
extern BOOL g_rightkey_prev[2];	// 直前の右キーの状態
extern BOOL g_enterkey_prev[2];	// 直前のエンターキーの状態
extern BOOL quit_game;			// ゲームを終了させるか判別するフラグ
//extern BOOL mode_title;			// 現在タイトル画面にいるか判別するフラグ
extern BOOL flag_full_hd_ok;	// フルＨＤによるプレイが可能か判別する
extern BOOL flag_full_hd_now;	// 現在の解像度がフルＨＤか判別する
extern BOOL flag_mode_window;	// フルスクリーン、ウィンドウの状態を判別するフラグ
extern BOOL flag_dialog_appear;	// ダイアログボックスを出現させるフラグ
// マップ画面用
extern BOOL cfgm_commu_check[COMMU_MAP_LIMIT];	// 選択コミュ閲覧画面を表示する
// コミュセレクト用
extern BOOL cfcs_move_commu[CS_COMMU_LIMIT];	// 選択されたコミュを閲覧するフラグ
// 体験版モード専用
//extern BOOL mode_trial;	// 現在トライアルモードか判別する
// デバッグモード専用
extern BOOL mode_debug;	// 現在デバッグモードか判別する

extern char OneMojiBuf[3];	// １文字分一時記憶配列

extern char StringBuf[STRBUF_HEIGHT][STRBUF_WIDTH + 2];	// 仮想テキストバッファ
// カーソル
extern int select_cursor;
extern int mode_cursor;

extern int title_wait_time;			// タイトル画面に切り替わった時間
extern int now_title_wait_time;		// タイトル画面に切り替わってから経過した時間
extern int demo_count;				// デモ画面に切り替わった回数
extern int InputHandle;		// 文字を入力する際に必要なハンドル
extern int monitor_resolution_x;	// メインモニターX座標
extern int monitor_resolution_y;	// メインモニターY座標

extern int MouseX, MouseY;					// マウス座標取得に必要な変数
extern int StringSizeX, StringSizeY, StringLine;	// 文字サイズ取得に必要な変数
extern int DrawPointX, DrawPointY;	// 文字列描画の位置
extern int SP, CP;					// 参照する文字列番号と文字列中の文字ポインタ
extern int EndFlag;					// 文字を１文字ずつ描画する処理の終了フラグ

extern int screen_size_x;	// ゲームの横解像度
extern int screen_size_y;	// ゲームの縦解像度

extern float bairitu;	// 現在解像度に応じた各要素の倍率
// マップモード関係
extern float draw_map_character_icon_x[COMMU_MAP_LIMIT];		// キャラアイコンx座標始点
extern float draw_map_character_icon_y[COMMU_MAP_LIMIT];		// キャラアイコンy座標始点
extern float draw_map_coordinate_hukidasi_x[COMMU_MAP_LIMIT];	// 吹き出しx座標始点
extern float draw_map_coordinate_hukidasi_y[COMMU_MAP_LIMIT];	// 吹き出しy座標始点
// コミュセレクトモード関係
extern float commu_select_coordinate_alternative_y[CS_COMMU_LIMIT];	// コミュ選択肢左端y座標

// 関数プロトタイプ宣言
void ScreenResolutionChange();	// 画面解像度を定義する
void DrawGameOpening();																					// タイトルデモ
void DrawGameMenu();																					// モード選択
void DrawGameClear();
void DrawGameTutorial();																				// 説明モード
void DrawGameContinue();																				// コンテニュー画面
void DrawGameEnding();																					// エンディング
// キートリガー処理（ボタンが押されていない状態でボタンが押されたか確認する）
BOOL IsUPKeyTrigger(int key, int y);	// 上キー
BOOL IsDOWNKeyTrigger(int key, int y);	// 下キー
BOOL IsLEFTKeyTrigger(int key, int y);	// 左キー
BOOL IsRIGHTKeyTrigger(int key, int y);	// 右キー
BOOL IsENTERKeyTrigger(int key, int y);	// エンターキー
BOOL ClickFlagCheck(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a);											// クリックされたタイミングや状況に応じたフラグを返す
BOOL ClickFlagCheck2(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a);											// クリックされたタイミングや状況に応じたフラグを返す（float変数『bairitu』をかける）
BOOL ClickFlagCheckF2(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, ClickFlagCheckType type);	// クリックされたタイミングや状況に応じたフラグを返す（列挙定数に応じて条件のフラグが追加される）
/*---------------------------
共通ソース
---------------------------*/
extern int progress_frame;				// ゲーム開始から経過したフレーム数（１／60秒）
extern int progress_frame_time;			// 前回の経過フレームをカウントした時間
extern int progress_frame_need_time;	// 前回の経過フレームをカウントするのに必要な時間

#endif

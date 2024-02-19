#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include <DxLib.h>
#include "main.h"

#define COMMU_CHARACTER_NUMBER 5	// 個別コミュが存在するキャラの総数
#define GAME_ALL_WEAK 2				// ４月３週目から数えて、必要な週の数（現在は体験版なので２）
// 移動先マップの状態
enum MapDestinationType
{
	MAP_DESTINATION_LEFT, MAP_DESTINATION_CENTER, MAP_DESTINATION_RIGHT
};
extern MapDestinationType g_map_destination;
// tips代入用文字列
struct TipsStringData
{
	char* string;
	float x;		// 文字列表示X座標
};
extern TipsStringData tips_string[2];
// tips関係の構造体
struct TipsData
{
	int id;										// ID数字
	char tips[256];								// 内容
	BOOL appear;								// 出現済みフラグ
	static constexpr int LOAD_LIMIT = 128;
	static void NumberCount() { number++; };	// numberをカウントする
	// 何故constexprがあるのか不明
	static constexpr int GetNumber() { return number; }
private:
	static int	number;	// 個数
};
extern TipsData tips_data[TipsData::LOAD_LIMIT];
// マップ関係で主に使われる疑似グローバル変数、定数
class GlobalStaticMap
{
	static BOOL trial_commu_viewed[COMMU_CHARACTER_NUMBER];	// スチル体験版でコミュを見たフラグ
public:
	static constexpr int WEEK_INITIAL_VALUE = 12;	//	初期の月週
	static void TrialCommuViewedReset();
	static void SetTrialCommuViewed(int x, BOOL y) { trial_commu_viewed[x] = y; }
	static BOOL GetTrialCommuViewed(int x) { return trial_commu_viewed[x]; }
	static int GetWeekInitialValue() { return WEEK_INITIAL_VALUE; }
};

extern BOOL map_move_commu_check;	// 選択したコミュを閲覧するか確認するフラグ
extern BOOL map_commu_upper[3][2];	// マップ画面にコミュアイコンが出現するか
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfgm=click_flag_game_map）
/*
extern BOOL cfgm_move_left;						// 左マップへ移動
extern BOOL cfgm_move_right;					// 右マップへ移動
*/
extern BOOL cfgm_commu_check_ok;				// 選択コミュへ移行する
extern BOOL cfgm_commu_check_no;				// 選択コミュ閲覧画面を解除する

extern int game_week_number;							// ゲーム中の月、週を参照する変数
extern int commu_look_count[COMMU_CHARACTER_NUMBER];	// マップ画面からアイコンを選択し、（フレンドコミュ以外の）各キャラのコミュを見た回数
//extern int select_map_number;							// 選ばれているマップＵＩ
extern int map_font_arrow;								// マップ画面矢印のフォントサイズ

extern float draw_map_plus_x;				// マップＵＩに加算するx座標値
//extern float map_arrow_left_x;				// 左側に行く矢印のx座標値
//extern float map_arrow_right_x;				// 右側に行く矢印のx座標値
extern float draw_map_space;				// 各マップ間の隙間
extern float draw_map_commu_choice_x[2];						// コミュ移動選択肢x座標始点
extern float draw_map_commu_choice_y;							// コミュ移動選択肢y座標始点

void GameMapNext();						// マップ画面移行処理
void GameMap();							// GAME_MAP状態のメイン処理
void GameMapControl();					// マップ画面操作処理
void GameMapFlame();					// マップモード時１フレーム毎に行われる処理
void GameMapTipsSubstitution();			// tips文字列データを代入する
void GameMapCoordinateSetting();		// マップ画面で使う様々な座標を（再）定義する
void DrawGameMap();						// マップモード時描画処理

BOOL GameMapUpperCheck(int x, int y);	// 対応するキャラコミュが出現するかチェックする
BOOL GameMapControlCommuCheck(BOOL x);	// マップアイコンクリック確認用関数
#endif

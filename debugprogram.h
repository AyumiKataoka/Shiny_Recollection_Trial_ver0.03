#ifndef __DEBUGPROGRAM_H__
#define __DEBUGPROGRAM_H__

#include <DxLib.h>
#include "main.h"
// 種類
enum DebugType
{
	DEBUG_MAIN,				// main関数で呼び出されるデバッグ
	DEBUG_LOAD				// セーブデータロードとは別の情報をロード（上書き）する
};
// 出力するログの種類
enum class LogOutputType
{
	LOAD_FLAG,
	LOAD_CHECK,
	CELL_CHARACTER,		// 行送り時の各立ち絵
	LOG_MESSAGE,		// ログモードで表示される文字列
	NOT_USE_BACKGROUND	// 使われない背景のＩＤと名前
};
// デバッグに関係する関数等で主に使われる疑似グローバル変数、定数
class GlobalStaticDebug
{
	static BOOL log;	// ログを出力させる
public:
	static BOOL GetLog() { return log; }
};

extern int debug_local_int[2];	// ローカル変数代入用変数（int）

extern double debug_local_double_1;	// ローカル変数代入用変数（double）
//フラグ
extern BOOL debug_load;					// セーブデータロードとは別の情報をロード（上書き）する
extern BOOL debug_window;				// ウィンドウ解像度を変更する
extern BOOL debug_bgm_load_cut;			// ＢＧＭのロードを行わないようにする
extern BOOL debug_character_load_cut;	// 立ち絵のロードを行わないようにする
extern BOOL debug_escape_check;			// Eキーの入力で強制終了させる
extern BOOL debug_keyboard;				// キーボードに応じたデバッグ処理を行う
extern BOOL debug_message;				// 状態に応じたメッセージを出力する
extern BOOL debug_hit_judge;			// 当たり判定を表示する
extern BOOL debug_entrance_before;		// 入学前コミュ撮影モードにする
extern BOOL debug_dialog_through;		// 解像度ダイアログボックス処理を無視して指定した解像度にする

void DebugProgram(DebugType x);	// デバッグプログラム共通処理（呼び出すプログラムの種類）
void DebugLoad();				// セーブデータロードとは別の情報をロード（上書き）する
void DebugWindowChange();		// ウィンドウ解像度を変更する
void DebugEscapeCheck();		// Eキーの入力で強制終了させる
void DebugProgramControl();		// デバッグモード中の操作処理
void DebugLog(LogOutputType x);		// ログ関係の処理
// 描画系
void DebugMessage();															// 状態に応じたメッセージを出力する
void DebugDrawClickJudge(int x1, int y1, int x2, int y2, int r, int g, int b);	// クリック判定用描画関数

BOOL DebugLoadCheckCharacter();	// 立ち絵ロードを行うか確認する
BOOL DebugLoadCheckBGM();		// ＢＧＭロードを行うか確認する
#endif

#pragma once
#ifndef __GAMECOMMUEDIT_H__
#define __GAMECOMMUEDIT_H__

#include <DxLib.h>
#include "main.h"

#define EDIT_CHARACTER_ALTERNATIVE_X_LIMIT 6	// キャラクター選択肢の横行個数

// 現在何の機能を編集しているか
enum EditType
{
	EDIT_DEFAULT,			EDIT_LINES_CHARACTER,	EDIT_LINES_CHARACTER2,	EDIT_LINES,				EDIT_COMMAND,
	// テキストウィンドウの色						口パクタイプ
	EDIT_TEXT_WINDOW,		EDIT_COMMAND_NUMBER,	EDIT_LINES_MOUSE,		EDIT_CHARACTER_LEFT,	EDIT_CHARACTER_CENTER,
	EDIT_CHARACTER_RIGHT,	EDIT_BACKGROUND,		EDIT_BGM,				EDIT_SE
};
extern EditType g_edittype;
// キャラクターのどの部分を編集しているか（代入や関数の都合上順番を逆にしている）
enum EditCharacterType
{
	EDIT_CHARACTER_EXPRESSION,	EDIT_CHARACTER_COSTUME,	EDIT_CHARACTER_PAUSE,	EDIT_CHARACTER_BODY
};
extern EditCharacterType g_editcharactertype;
// デフォルト状態での選択肢
enum EditSelectType
{
	EDIT_SELECT_COMMAND,			EDIT_SELECT_LINES_CHARACTER,	EDIT_SELECT_LINES_CHARACTER2,			EDIT_SELECT_LINES,			EDIT_SELECT_LINES_MOUSE,
	EDIT_SELECT_CHARACTER_LEFT,		EDIT_SELECT_FE_LEFT,			EDIT_SELECT_CHARACTER_CENTER,			EDIT_SELECT_FE_CENTER,		EDIT_SELECT_CHARACTER_RIGHT,
	EDIT_SELECT_FE_RIGHT,			EDIT_CHARACTER_CHANGE_TYPE,		EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM, EDIT_SELECT_BACKGROUND,		EDIT_SELECT_BACKGROUND_CHANGE_TYPE,
	EDIT_SELECT_BGM,				EDIT_SELECT_BGM_CHANGE_TYPE,	EDIT_SELECT_SE
};
#define EDIT_SELECT_PAGE_MAX EDIT_SELECT_SE	// コミュエディターのページ右端
// 今現在入力しているコマンド系文字列
enum CommandInputStringType
{
	CIS_NULL,					CIS_FRAME_AUTO,				CIS_ALTERNATIVE2_1,			CIS_ALTERNATIVE2_2,			CIS_ALTERNATIVE3_1,
	CIS_ALTERNATIVE3_2,			CIS_ALTERNATIVE3_3,			CIS_ALTERNATIVE_JUMP2_1,	CIS_ALTERNATIVE_JUMP2_2,	CIS_ALTERNATIVE_JUMP3_1,
	CIS_ALTERNATIVE_JUMP3_2,	CIS_ALTERNATIVE_JUMP3_3,	CIS_MOVE_SELL,				CIS_MOVE_COMMU,
};
extern CommandInputStringType g_commandinputstring;
// 検索するサムネ用数値の種類
enum EditSamuneSearchType
{
	ESS_CHARACTER_LEFT, ESS_CHARACTER_CENTER, ESS_CHARACTER_RIGHT, ESS_CHARACTER_DISTANCE,	ESS_BACKGROUND,
	ESS_BGM
};
// 背景の名前（なんとなく上手くいっているので不具合が起きる可能性はある）
//class BackgroundName
//{
//	char name[256];
//public:
//	BackgroundName(char *c){sprintf_s(name, 256, c);}
//	char* GetName(){return name;}
//};
//extern class BackgroundName background_name[];
//BackgroundName::BackgroundName(char *c)
//{
//	//name = c;
//	sprintf_s(name, 256, c);
//}
// 
// 背景

// エディットモード関係で主に使われる疑似グローバル変数、定数
class GlobalStaticEdit
{
	// 背景選択肢
	static int background_alternative_row;					// 列カーソル
	static int background_alternative_line;					// 行カーソル
	static int background_alternative_line_limit;			// 行の最大数
	static int background_alternative_line_draw;			// １段目に描画する行
	static const int BACKGROUND_ALTERNATIVE_LINE_NUMBER;	// １行に並ぶ背景数
public:
	static void SetBackgroundAlternativeRow(int x);
	static void SetBackgroundAlternativeLine(int x);
	static void SetBackgroundAlternativeLineLimit(int x) { background_alternative_line_limit = x; }
	static int GetBackgroundAlternativeRow() { return background_alternative_row; }
	static int GetBackgroundAlternativeLine() { return background_alternative_line; }
	static int GetBackgroundAlternativeLineNumber() { return BACKGROUND_ALTERNATIVE_LINE_NUMBER; }
};

extern char c_global_function[256];	// char関数の返り値として使う変数（ローカル配列変数をreturnで扱えないのでグローバル変数にする必要がある）

extern BOOL commu_edit_input_string;	// （台詞主編集時に）文字の入力を行っている状態か
extern BOOL g_inputbkey_prev;		// 直前のキーボードＢキーの状態
extern BOOL g_1key_prev;			// 直前のキーボード1キーの状態
extern BOOL g_2key_prev;			// 直前のキーボード2キーの状態
extern BOOL g_3key_prev;			// 直前のキーボード3キーの状態
extern BOOL g_4key_prev;			// 直前のキーボード4キーの状態
extern BOOL g_5key_prev;			// 直前のキーボード5キーの状態
extern BOOL g_6key_prev;			// 直前のキーボード6キーの状態
extern BOOL g_7key_prev;			// 直前のキーボード7キーの状態
extern BOOL g_8key_prev;			// 直前のキーボード8キーの状態
extern BOOL g_9key_prev;			// 直前のキーボード9キーの状態
extern BOOL g_0key_prev;			// 直前のキーボード0キーの状態
extern BOOL edit_insert_prev;		// 直前の挿入操作判定の状態
extern BOOL edit_copy_paste_prev;	// 直前のコピペ操作判定の状態
extern BOOL edit_delete_prev;		// 直前の行削除の状態

extern int edit_row;													// 現在編集しようとしているもの
extern int edit_row_background;											// 現在編集しようとしている背景のページ
extern int edit_row_bgm;												// 現在編集しようとしているＢＧＭのページ
extern int edit_row_se;													// 現在編集しようとしているＳＥのページ
extern int edit_line;													// 現在編集している行数
extern int edit_play_bgm;												// エディットモードで現在流れているＢＧＭＩＤ
extern int edit_character_id[256][EDIT_CHARACTER_ALTERNATIVE_X_LIMIT];	// 立ち絵選択時に必要なキャラＩＤ
extern int edit_character_alternative_row;								// キャラ選択肢用の列カーソル
extern int edit_character_alternative_line;								// キャラ選択肢用の行カーソル
extern int edit_character_alternative_line_limit;						// キャラ選択肢用の行の最大数

void GameCommuEdit();											// GAME_COMMU_EDIT状態のメイン処理
void GameCommuEditControl();									// コミュエディット画面操作処理
void GameCommuEditTextWindow(int x);							// テキストウィンドウ色変更の際の共通処理
void GameCommuEditAlternativeInput(CommandInputStringType x);	// 選択肢文字列入力の際の共通処理
void GameCommuEditInputString(int x, BOOL y, char* c);			// 文字入力状態移行の共通処理
void GameCommuEditLineErase(int x);								// 行内容全削除の共通処理
#pragma region ver0.00704制作時コメント化コード
//void GameCommuEditLineCopy(int x, int y);						// 行内容コピーの共通処理
#pragma endregion
void GameCommuEditLineCopy(int x, int y, int z);				// 行内容コピーの共通処理
void GameCommuEditLinesMouse(int x);							// 口パクタイプ変数代入の共通処理
void GameCommuEditLinesCharacter(char* c);						// 台詞主変数代入時の共通処理
void GameCommuEditCharacter(int x, int y, int z);				// キャラクター用変数代入処理の際の共通処理
void GameCommuEditCharacterCursorMove(int x);					// キャラ立ち絵選択時瞬時移動するキャラを検索し移動する際の共通処理
void GameCommuEditCharacterChange(int x);						// キャラ変更タイプを変更する際の共通処理
void GameCommuEditBackground(int x);							// 背景変数代入の共通処理
void GameCommuEditBGM(int x);									// ＢＧＭ変数代入の共通処理
void GameCommuEditSE(int x);									// ＳＥ変数代入の共通処理
void DrawGameCommuEdit();										// コミュエディット画面の描画処理

char* GetSEString(int x);	// seの引数から文字列を取得する

BOOL IsINPUTBKeyTrigger();	// キーボードBキー
BOOL Is1KeyTrigger();		// 1キー
BOOL Is2KeyTrigger();		// 2キー
BOOL Is3KeyTrigger();		// 3キー
BOOL Is4KeyTrigger();		// 4キー
BOOL Is5KeyTrigger();		// 5キー
BOOL Is6KeyTrigger();		// 6キー
BOOL Is7KeyTrigger();		// 7キー
BOOL Is8KeyTrigger();		// 8キー
BOOL Is9KeyTrigger();		// 9キー
BOOL Is0KeyTrigger();		// 0キー
BOOL IsInsertTrigger();		// 挿入操作
BOOL IsCopyPasteTrigger();	// コピペ操作
BOOL IsDeleteTrigger();		// 行削除操作

int GetEditSamuneNumber(EditSamuneSearchType y);	// 遡って検索するタイプのサムネ文の要素に関わる数値を探す際の共通処理

#endif

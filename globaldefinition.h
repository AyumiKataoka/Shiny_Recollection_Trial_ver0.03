// 『Ａヘッダにある定数をＢヘッダの配列数として使用する』等の状況になった際、それらをまとめてこのファイルで宣言させる
#pragma once

#ifndef __GLOBALDEFINITION_H__
#define __GLOBALDEFINITION_H__

#include <DxLib.h>
#include "main.h"

#define HIT_JUDGEMENT_IMAGE_NUMBER_MAP 4			// マップ画面での当たり判定付き画像個数（3：セーブアイコン、４：ロードアイコン）
#define COMMU_LINE_MAX 1024							// １コミュ内に代入できる最大行数
#define COMMU_LINE_MAX_EDIT (COMMU_LINE_MAX + 1)	// エディットモードで編集できる最大行数目
//#define BACKGROUND_NUMBER 41						// 背景の数
#define	ALTENATIVE_MAX_NUMBER 3						// ゲーム中で使う選択肢の最大数
#define STRBUF_ALTENATIVE_WIDTH 64					// 選択肢用仮想テキストバッファの横サイズ
#define STRBUF_ALTENATIVE_HEIGHT 3					// 選択肢用仮想テキストバッファの縦サイズ

extern int ClickX, ClickY, Button, LogType;	// クリック処理に必要な変数

BOOL ClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a);									// クリックされたタイミングや状況に応じたフラグを返す（範囲座標がfloat）

// キャラクター変更タイプ
enum CommuCharacterChangeType
{
	// 透明度入れ替え、			瞬時入れ替え、	透明度入れ替え（高速）
	CCC_TRANSPARENCY_NORMAL,	CCC_INSTANT,	CCC_TRANSPARENCY_FAST
};
// 背景変更方法の種類
enum BackgroundChangeType
{
	// 非透明度入れ替え、			ブラックアウト、			ホワイトアウト
	BACKGROUND_CHANGE_VISIBILITY, BACKGROUND_CHANGE_BLACKOUT, BACKGROUND_CHANGE_WHITEOUT
};
extern BackgroundChangeType g_backgroundchange;
// ＢＧＭ切り替えの種類
enum BGMChangeType
{
	BGM_CHANGE_FO_P,	// 通常
	BGM_CHANGE_FO_FI,	// フェードイン再生
	BGM_CHANGE_S_P,		// 急停止
	BGM_CHANGE_S_FI		// 急停止＆フェードイン再生
};
// コミュ内容
struct state
{
	char command[256];
	int move_commu_number;							// 移動先コミュＩＤ
	char name[256];
	char name2[256];								// 同時に喋る２人目の名前
	char line[256];									// 台詞
	int line_mouse;									// 喋る際の口パクタイプ
	int character[3];								// 描画するキャラ、差分
	int character_face_etc[3];						// キャラの特殊表情ＩＤ
	int character_change = CCC_TRANSPARENCY_FAST;	// キャラクター変更タイプ
	int character_even_distance;					// キャラクター距離均一化のオンオフ
	int background;									// 描画背景
	BackgroundChangeType background_change;			// 背景変更タイプ
	int bgm;										// 再生するＢＧＭ
	BGMChangeType bgm_change;						// ＢＧＭ切り替えタイプ
	int se;											// 再生するＳＥ
	char altenative_message[3][128];				// 選択肢文
	int altenative_jump[3];							// 選択肢のジャンプ先の行
	// コマンドを変更する
	void CommandChange(char* c) { sprintf_s(command, 256, "%s",c); }	// 代入文字列
	// 各特定コマンド用数値を変更する
	void CommandNumberChange(int x) { move_commu_number = x; }	// 数値
	// 台詞主を変更する（入力文字列版）
	void LineCharacterChange(int x, int y) 	// 編集台詞主用配列変数,代入文字列
	{
		if (x == 0) { GetKeyInputString(name, y); }
		else { GetKeyInputString(name2, y); }
	}
	// 台詞主を変更する（char変数版）
	void LineCharacterChange(int x, char* c) 	// 編集台詞主用配列変数,代入文字列
	{
		if (x == 0) { sprintf_s(name, 256, c); }
		else { sprintf_s(name2, 256, c); }
	}
	void LineChange(int x) { GetKeyInputString(line, x); }		// 台詞を変更する（x：代入文字列）
	void LineChange(char* c) { sprintf_s(line, 256, c); }		// 台詞を変更する（char変数版、c：代入文字列）
	void LineConnection(char* c) { sprintf_s(line, 256, "%s@%s", line, c); }	// 台詞を接続する（c：代入文字列）
	void LineMouseChange(int x) { line_mouse = x; }				// 口パクタイプを変更する（x：代入数値）
	void CharacterIDChange(int x, int y) { character[x] = y; }	// キャラクターを全要素変更する（x：変更するキャラクター,y：変更後の数字）
	// エディットモードでcharacter[x]の数値を変える際の共通処理
	void CharacterIDChange(int x, int y, int z) // 変更するキャラクター,変更するID数値の桁の位,変更後の数字
	{
		int a = (int)pow(10, y - 1);
		int b = character[x] / a;
		if (b >= 10) { b %= 10; }
		character[x] = character[x] - a * b + a * z;
	}
	// キャラの特殊表情を変更する				
	void CFECHANGE(int x, int y) { character_face_etc[x] = y; }	// キャラクター,数値
	// キャラクター変更タイプを変更する
	void CCCHANGE(int x) { character_change = x; }
	// キャラ間距離均一化を変更する
	void CDUCHANGE(int x) { character_even_distance = x; }	// 変更する数値
	// 背景を変更する
	void BackgroundChange(int x) { background = x; }	// 変更する
	// 背景変更タイプを変更する
	void BackgroundChangeTypeChange(BackgroundChangeType x) { background_change = x; }	// 変更する数値
	// 再生ＢＧＭを変更する
	void BGMChange(int x) { bgm = x; }	// ＢＧＭ用変数
	// ＢＧＭ変更タイプを変更する
	void BCTChange(BGMChangeType x) { bgm_change = x; }
	// ＳＥ数値を変更する
	void SEChange(int x) { se = x; }	// 専用変数
	// 選択肢文字列を変更する
	void AlternativeChange(int x, int y) { GetKeyInputString(altenative_message[x], y); }	// 選択肢用変数,代入文字列
	// 選択肢文字列を変更する（char変数版）
	void AlternativeChange(int x, char* c) { sprintf_s(altenative_message[x], 128, c); }	// 選択肢用変数,代入文字列
	// 選択肢ジャンプ先行を変更する
	void AlternativeJumpChange(int x, int y) { altenative_jump[x] = y; }	// 選択肢用変数,数値
	// 選んだ選択肢のジャンプ先履歴をセットする
	static void SetAlternativeMoveNumber(int x, int y) { alternative_move_number[x] = y; }
	// コマンド名を取得する
	char* GetCommand() { return command; }
	// １人目の台詞主名を取得する
	char* GetLineCharacterName() { return name; }
	// ２人目の台詞主名を取得する
	char* GetLineCharacterName2() { return name2; }
	// 台詞文字列を取得する
	char* GetLine() { return line; };
	// 選択肢の文字列を取得する
	char* GetAlternativeString(int x) { return altenative_message[x]; }
	// コマンド用数値を取得する
	int GetCommandNumber() { return move_commu_number; }
	// 喋る際の口パクタイプを取得する
	int GetLineMouse() { return line_mouse; }
	// 描画するキャラ用変数値を取得する
	int GetCharacter(int x) { return character[x]; }	// キャラの位置
	// キャラの特殊表情ＩＤを取得する
	int GetCFE(int x) { return character_face_etc[x]; }	// キャラの位置
	// キャラクター変更タイプ数値を取得する
	int GetCC() { return character_change; }
	// キャラ間距離均一化を取得する
	int GetCDU() { return character_even_distance; }
	// 背景用変数を取得する
	int GetBackground() { return background; }
	// ＢＧＭ用変数を取得する
	int GetBGM() { return bgm; }
	// ＳＥ用変数を取得する
	int GetSE() { return se; }
	// 選択肢ジャンプ先用変数を取得する
	int GetAlternativeJump(int x) { return altenative_jump[x]; }	// 選択肢
	// 選んだ選択肢のジャンプ先履歴ゲット
	static int GetAlternativeMoveNumber(int x) { return alternative_move_number[x]; }
	// 背景変更タイプ用変数を取得する
	BackgroundChangeType GetBackgroundChangeType() { return background_change; }
	// ＢＧＭ変更タイプ用配列定数を取得する
	BGMChangeType GetBGMCT() { return bgm_change; }
private:
	static int alternative_move_number[COMMU_LINE_MAX];	// 選んだ選択肢のジャンプ先履歴
};
extern state HM[512][COMMU_LINE_MAX], commu_state_edit[COMMU_LINE_MAX + 1];
// 
// 画像データ
class ImgData
{
protected:
	// 配置される左端、上端座標
	float coordinate_x = 0;
	float coordinate_y = 0;
public:
	int Handle = 0;		// 画像ハンドル
	int size_ox = 0;	// 倍率補正を掛けていない元々の横幅
	int size_oy = 0;	// 倍率補正を掛けていない元々の縦幅
	float size_x = 0;	// 様々な処理で扱う横幅
	float size_y = 0;	// 様々な処理で扱う縦幅
	// 座標値を定義する
	void CoordinateSetting(float x, float y)
	{
		coordinate_x = x;
		coordinate_y = y;
	}
	// 読み込み処理
	BOOL Load(char* s, BOOL x, float bairitu)	// ファイル名、サイズ読み込みフラグ、倍率（ほぼ定数）
	{
		Handle = LoadGraph(s);
		if (Handle == -1) { return FALSE; }
		// フラグが立っているなら他の描画処理で扱う画像幅も定義する
		if (x == TRUE)
		{
			GetGraphSize(Handle, &size_ox, &size_oy);
			size_x = size_ox * bairitu;
			size_y = size_oy * bairitu;
		}

		return TRUE;
	}
	// 画像を描画する
	void DrawImage() { DrawExtendGraphF(coordinate_x, coordinate_y, coordinate_x + size_x, coordinate_y + size_y, Handle, TRUE); }
	// Y座標を指定して画像を描画する
	void DrawImageCoordinateY(float y){ DrawExtendGraphF(coordinate_x, y, coordinate_x + size_x, y + size_y, Handle, TRUE); }
	// ハンドルを取得する
	int GetHandle() { return Handle; }
	// 座標を取得する
	float GetCoordinateX() { return coordinate_x; }
	float GetCoordinateY() { return coordinate_y; }
	// 画像の各オリジナル幅数値を取得する
	int GetOriginalSizeX() { return size_ox; }
	int GetOriginalSizeY() { return size_oy; }
	// 画像の各幅数値を取得する
	float GetSizeX() { return size_x; }
	float GetSizeY() { return size_y; }
};
//									オプションでアイコンでもなく変動しないもの（机、紙、文字、タイトル、解像度×２）、	オプション選択肢用矢印、	メッセージ速度、				画面モードの種類
extern ImgData	image_dialog[2], image_option[6], image_option_arrow[2], image_option_message_speed[3], image_option_window_type[2],
				//											注意文、											マップ選択時背景
				image_text_window[2][4], image_icon_option, image_cautionary_message, image_icon_commu_edit,	image_map_background;
// 当たり判定を持つ画像データ（HJ：hit judgement）
class ImgDataHJ : public ImgData
{
	BOOL click_judgement;				// クリック判定
public:
	void CJChange(BOOL x) { click_judgement = x; }

	BOOL CJReturn() { return click_judgement; }
	// クリック判定処理を行う
	BOOL JudgementClickCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, TRUE, FALSE) == TRUE) 
		{ 
			click_judgement = TRUE; 
			return TRUE;
		}
		return FALSE;
	}
	// 放す処理の判定を行う
	BOOL JudgementReleaseCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, FALSE, click_judgement) == TRUE) { return TRUE; }
		return FALSE;
	}
};
//					タイトル画面用、マップ画面用、									選択肢
extern ImgDataHJ	hjimage_title,	hjimage_map[HIT_JUDGEMENT_IMAGE_NUMBER_MAP],	hjimage_alternative[ALTENATIVE_MAX_NUMBER];
// 背景画像データ
class ImgDataBG : public ImgData
{
	BOOL use = FALSE;		// （デバッグ用）呼び出されたフラグ
	char name[256] = "";	// 名前
	static int number;		// 画像総数
public:
	enum class EnumConstant
	{
		STAFF_ROOM = 9,
		OFFICE = 24
	};
	ImgDataBG(char* c);
	void SetUse(BOOL x) { use = x; }
	// サムネ用背景を描画
	void DrawImageSamune() { DrawExtendGraphF(coordinate_x, coordinate_y, (coordinate_x + size_x) / 2, (coordinate_y + size_y) / 2, Handle, TRUE); }

	BOOL GetUse() { return use; }
	char* GetName() { return name; }
	int GetNumber() { return number; }
};
extern ImgDataBG bgimage[];
// 文字、画像等のサイズ倍率データ（magnification：倍率）
class MagnificationData
{
protected:
	static float magnification;	// 描画関係のゲーム解像度倍率
public:
	void ChangeMagnification(float x) { magnification = x; }
};
// マップチュートリアルコミュ用背景画像データ
class ImgDataBGTutorial : public ImgData, public MagnificationData
{
	char path[256];						// 読み込みパス
	static int number;					// 画像総数
	static int draw_image_number;		// 何枚目の画像を描画するか判別するＩＤ
	static float screen_y;				// スクリーンのy座標
	static const int SCREEN_Y_INITIAL;	// スクリーンの初期y座標
public:
	ImgDataBGTutorial(char* c)
	{
		sprintf_s(path, 256, c);
		number++;
	}
	// 画像を描画する
	void DrawImageTutorial(float y) { DrawExtendGraphF(coordinate_x, y * magnification, coordinate_x + size_x, y * magnification + size_y, Handle, TRUE); }

	static void SetNumber(int value) { number = value; }
	static void SetDrawImageNumber(int value) { draw_image_number = value; }
	static void SetScreenY(float y) { screen_y = y; }
	// スクリーンのＹ座標をずらす
	static void ScreenYMove();
	// 引数（コミュ行数）に応じて描画する説明画像を変える
	static void DIMCheck(int x)
	{
		//switch (x - 2)
		switch (x - 1)	// 修正のため数値を変更している
		{
		case 30:
		case 61:
		case 113:
			draw_image_number = 1;
			break;
		case 31:	
		case 35:
			draw_image_number = 3;
			break;
		case 32:
		case 39:
			draw_image_number = 7;
			break;
		case 33:	draw_image_number = 2;	break;
		case 36:	draw_image_number = 5;	break;
		case 42:	draw_image_number = 10;	break;
		case 47:	draw_image_number = 9;	break;
		case 48:	draw_image_number = 8;	break;
		case 50:	draw_image_number = 11;	break;
		case 52:	draw_image_number = 12;	break;
		case 54:	draw_image_number = 13;	break;
		case 55:	draw_image_number = 0;	break;
		case 92:	draw_image_number = 14;	break;
		case 104:	draw_image_number = 15;	break;
		case 108:	draw_image_number = 16;	break;
		default:
			break;
		}
	}
	// 要素をリセットする
	static void Reset();
	
	char* GetPath() { return path; }
	static int GetNumber() { return number; }
	static int GetDrawImageNumber() { return draw_image_number; }
	static float GetScreenY() { return screen_y; }
};
extern ImgDataBGTutorial tutorial_image[];
// 予め倍率を読み込む画像データ
class ImaDataName : public ImgData, public MagnificationData
{
public:
	static constexpr int TITLE_BORDER_NUMBER = 211;
	BOOL LoadName(char* c, BOOL x)	// ファイル名、サイズ読み込みフラグ
	{
		Handle = LoadGraph(c);
		if (Handle == -1) { return FALSE; }
		// フラグが立っているなら他の描画処理で扱う画像幅も定義する
		if (x == TRUE)
		{
			GetGraphSize(Handle, &size_ox, &size_oy);
			size_x = size_ox * magnification;
			size_y = size_oy * magnification;
		}
		return TRUE;
	}
	// 倍率を見込んだ上で座標値を定義する
	void CoordinateSettingName(float x, float y);
	static int GetTitleBorderNumber() { return TITLE_BORDER_NUMBER; }
};
extern ImaDataName image_title_border[ImaDataName::TITLE_BORDER_NUMBER];
// 予め倍率、パスを読み込む画像データ
class ImgData2 : public ImgData, public MagnificationData
{
	char path[256] = "";
	static int notice_count;						// 警告文背景の透明度調整用数値
	static const int NOTICE_COUNT_MILLI_SECOND;		// 警告文背景の透明度調整に必要なミリ秒
public:
	static constexpr int IMC_NUMBER = 9;
	static constexpr int LOG_BACKGROUND_NUMBER = 2;
	static constexpr int LOG_TEXT_WINDOW_NUMBER = 5;
	ImgData2(char* c) { sprintf_s(path, 256, c); }
	// 引数に倍率を使わない読み込み処理
	BOOL Load2(BOOL x)	// ファイル名、サイズ読み込みフラグ
	{
		Handle = LoadGraph(path);
		if (Handle == -1) { return FALSE; }
		// フラグが立っているなら他の描画処理で扱う画像幅も定義する
		if (x == TRUE)
		{
			GetGraphSize(Handle, &size_ox, &size_oy);
			size_x = size_ox * magnification;
			size_y = size_oy * magnification;
		}
		return TRUE;
	}
	// 倍率を見込んだ上で座標値を定義する
	void CoordinateSetting2(float x, float y);

	void SetPath(char* c){ sprintf_s(path, 256, c); }
	void DrawImageNotice();			// 警告文背景専用の描画処理
	static int GetNoticeCount() { return notice_count; }
};
extern ImgData2 bgimage_notice,												bgimage_title,			image_title_logo,		image_title_logo_stilltrial,							bgimage_sukashi,
				image_finish_check,											bgimage_room_teacher,	image_saveload_mode[2],	image_bl_background[ImgData2::LOG_BACKGROUND_NUMBER],	image_map_character[ImgData2::IMC_NUMBER],
				image_log_text_window[ImgData2::LOG_TEXT_WINDOW_NUMBER],	bgimage_non_month;
// 体験版終了用背景画像に関するデータ
class ImgDataTutorialEnd : public ImgData2
{
	static BOOL white_out;			// 体験版終了背景前の白いぼかしの透過度カウントを切り替えるフラグ
	static int count;				// 体験版アンケート背景の透明度調整用数値 
	static int count_wait;			// 体験版終了モードで操作可能になるのに必要なカウント数値
	static const int COUNT_LIMIT;	// 体験版アンケート背景の透明度調整用の限界数値
public:
	ImgDataTutorialEnd(char* c) : ImgData2(c) {}
	void DrawImageTutorialEnd();	// 体験版終了背景専用の描画処理
	static void SetWhiteOut(int x) { white_out = x; }
	static void SetCount(int x) { count = x; }
	static void SetCountWait(int x) { count_wait = x; }
	static void CountReset();	// 体験版終了に必要な要素をリセットする
	static int GetCountWait() { return count_wait; }
};
extern ImgDataTutorialEnd bgimage_tutorial_end;
// マップ画面月週表示外枠用画像データ
class ImgDataMapFrame : public ImgData2
{
	static int frame_number;	// マップ外枠画像個数
public:
	ImgDataMapFrame(char* c) : ImgData2(c) { frame_number++; }
	static int GetMapFrameNumber() { return frame_number; }	// マップ外枠画像枚数を取得
};
extern ImgDataMapFrame ui_map_month[];
// マップ画面移動確認用画像データ
class ImgDataMapQuestion : public ImgData2
{
	static int number;	// 画像個数
public:
	enum class Type
	{
		FRIEND_ALL = 5
	};
	ImgDataMapQuestion(char* c) : ImgData2(c) { number++; }
	static int GetNumber() { return number; }
};
extern ImgDataMapQuestion image_map_question[];
// タイトル画面キャラ用画像データ
class ImgDataTitleCharacter : public ImgData2
{
	static int character_number;
public:
	ImgDataTitleCharacter(char* c) : ImgData2(c) { character_number++; }
	static int GetTitleCharacterNumber() { return character_number; }	
};
extern ImgDataTitleCharacter image_title_character[];
// セーブロード画面確認画像データ
class ImgDataSLCheck : public ImgData2
{
	static int image_number;	// 画像数
public:
	// 種類
	enum class Type
	{
		SAVE,
		LOAD,
		EXIT
	};

	ImgDataSLCheck(char* c) : ImgData2(c) { image_number++; }
	static int GetSLCImageNumber() { return image_number; }
};
extern ImgDataSLCheck image_sl_check_message[];
// 予め倍率、パスを読み込む当たり判定付き画像データ
class ImgDataHJ2 : public ImgData2
{
	BOOL click_judgement = FALSE;					// クリック判定
public:
	// セーブロードモードアイコンの各機能
	enum class SaveLoadIconType
	{
		SAVE,
		LOAD,
		BACK,
		TITLE,
		EXIT
	};

	static constexpr int OPTION_ICON_NUMBER = 5;	// オプション等で使うアイコン数
	static constexpr int TEXT_LOG_ARROW_NUMBER = 4;		// テキストログで使うアイコン数
	ImgDataHJ2(char* c) : ImgData2(c) {};
	void CJChange(BOOL x) { click_judgement = x; }

	BOOL GetCJ() { return click_judgement; }
	// クリック判定処理を行う
	BOOL JudgementClickCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, TRUE, FALSE) == TRUE)
		{
			click_judgement = TRUE;
			return TRUE;
		}
		return FALSE;
	}

	BOOL JudgementClickCheckFlag(BOOL x);	// 条件付きクリック判定処理を行う
	// 放す処理の判定を行う
	BOOL JudgementReleaseCheck()
	{
		if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, FALSE, click_judgement) == TRUE) { return TRUE; }
		return FALSE;
	}
	static int GetOptionIconNumber() { return OPTION_ICON_NUMBER; }
};
extern ImgDataHJ2	image_icon_save_file[][2],			image_icon_sl_page[],				image_icon_new_option[ImgDataHJ2::OPTION_ICON_NUMBER],	image_icon_config_dialog[][2],	image_icon_config_text_speed[][2],
					image_icon_map_move_alternative[2],	image_icon_map_collision_detection,	image_icon_log,											image_icon_log_back,			image_icon_text_log[ImgDataHJ2::TEXT_LOG_ARROW_NUMBER];
// タイトル画面用当たり判定付き画像データ
class ImgDataHJTitle : public ImgDataHJ2
{
	static BOOL flag_count;							// タイトル画面経過フレーム数を即最大にするフラグ
	static int menu_number;							// タイトルメニューの項目数
	static int count_frame;							// タイトル画面での経過フレーム数
	//static int extra_handle;						// 『EXTRA』の３枚目画像ハンドル
public:
	enum class TYPE
	{
		START,
		LOAD,
		CONTINUE,
		OPTION,
		EXTRA,
		EXIT
	};
	ImgDataHJTitle(char* c, BOOL x) : ImgDataHJ2(c)
	{
		// 読み込み回数を半分にする処理
		if (x == TRUE) { menu_number++; }
	}
	static void SetFlagCount(BOOL x) { flag_count = x; }
	static void SetCountFrame(int x) { count_frame = x; }
	static void DrawTitleImage();	// タイトル画面に関する画像を描画させる
	static BOOL GetFlagCount() { return flag_count; }
	static int GetMenuNumber(){ return menu_number; }
	static int GetCountFrame() { return count_frame; }
};
extern ImgDataHJTitle image_title_menu[][2];
// 確認画面用選択肢
class ImgDataIconCheck : public ImgDataHJ2
{
	static const int IMAGE_NUMBER;	// 画像数
public:
	ImgDataIconCheck(char* c) : ImgDataHJ2(c){}
	static int GetImageNumber() { return IMAGE_NUMBER; }
};
extern ImgDataIconCheck image_icon_check[];
// マップ画面吹き出しアイコン
class ImgDataIconMapCharacter : public ImgDataHJ2
{
	static int number;	// 人数
public:
	ImgDataIconMapCharacter(char* c) : ImgDataHJ2(c) { number++; }
	static int GetNumber() { return number; }
};
extern ImgDataIconMapCharacter image_icon_map_character[];
// フォントデータ（予定）
class FontData : public MagnificationData
{
	char name[64];			// フォント文字列
	int size;				// サイズ
	int handle = 0;			// フォントハンドル
	static int font_number;	// 使われてるフォントの数
public:
	enum class Type
	{
		f1,
		f2,
		f3,
		f4,
		MAP_TITLE,
		SAVE_DATA,
		CONFIG_VOLUME
	};
	// 初期状態フォント定義
	FontData(char* c, int x)
	{
		sprintf_s(name, 64, c);
		size = x;
		font_number++;
	}
	
	void Create();
	int	GetHandle() { return handle; }			// ハンドルを取得する
	int GetFontNumber() { return font_number; }	// 使用フォント数を取得する
};
extern FontData font[];
// 文字列データ
class StringData
{
	char string[256] = "";	// 文字列
	int f_id = 0;			// フォントＩＤ
	int color;				// 文字色
	float c_x;				// x座標
	float c_y;				// x座標
public:
	StringData(unsigned int c, int x) 
	{ 
		color = c;
		f_id = x;
	}
	// 座標値を定義する
	void ChangeCoordinate(float x, float y)
	{
		c_x = x;
		c_y = y;
	}
	// 文字列を描画する
	void DrawString() { DrawFormatStringFToHandle(c_x, c_y, color, font[f_id].GetHandle(), string); }
	// x座標を指定して文字列を描画する
	void DrawStringSpecifyX(float s_x) { DrawFormatStringFToHandle(s_x, c_y, color, font[f_id].GetHandle(), string); }
	// 文字列を指定して描画する
	void DrawStringSpecifyString(char* c) { DrawFormatStringFToHandle(c_x, c_y, color, font[f_id].GetHandle(), c); }
	// x座標値を取得する
	float GetX() { return c_x; }
};
extern StringData line_character;
// セーブデータのサムネ
class SaveDataImage : public MagnificationData
{
	int handle = 0;			// 画像ハンドル
	float coordinate_x = 0;	// X座標
	float coordinate_y = 0;	// Y座標
public:
	void SetCoordinate(float x, float y);
	void Blend(int x, BOOL y);	// 画像を合成する
	void LoadHandel(int x);		// フォルダ内にあるサムネ画像を読み込む
	int GetHandle() { return handle; }
	static constexpr int LIMIT_NUMBER = 60;
};
extern SaveDataImage save_data_image[SaveDataImage::LIMIT_NUMBER];

extern char StringBufAltenative[ALTENATIVE_MAX_NUMBER][STRBUF_ALTENATIVE_HEIGHT][STRBUF_ALTENATIVE_WIDTH + 2];	// 選択肢用仮想テキストバッファ（横サイズ（３番目）の数字は適当）

#endif

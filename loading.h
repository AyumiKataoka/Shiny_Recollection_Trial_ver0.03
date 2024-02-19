#ifndef __LOADING_H__
#define __LOADING_H__

#include <DxLib.h>
#include "main.h"
#include "gamemap.h"
// 文字のサイズ
#define FONT_SIZE_27 27			
#define FONT_SIZE_15 15			
#define FONT_SIZE_12 12
#define FONT_SIZE_ORIGINAL 27				// ゲームで使用される文字のオリジナルサイズ
#define FONT_SIZE_ORIGINAL_COMMU_NAME 48	// ゲームで使用される文字のオリジナルサイズ（コミュ中名前）
#define FONT_SIZE_ORIGINAL_COMMU_LINE 40	// ゲームで使用される文字のオリジナルサイズ（台詞）
#define FONT_SIZE_ORIGINAL_TIPS 36			// ゲームで使用される文字のオリジナルサイズ（tips）

// 素材関係の定数（今後増加していく）
#pragma region ver0.00292制作時コメント化コード
//#define BACKGROUND_NUMBER 2					// 背景の数
//#define CHARACTER_GRAPH_NUMBER 2			// キャラクター立ち絵が使われる人数
#pragma endregion
#pragma region ver0.00601制作時コメント化コード
//#define BACKGROUND_NUMBER 5					// 背景の数
#pragma endregion
#pragma region ver0.00605制作時コメント化コード
//#define BACKGROUND_NUMBER 10				// 背景の数
#pragma endregion
#pragma region ver0.00392制作時コメント化コード
//#define CHARACTER_GRAPH_NUMBER 5			// キャラクター立ち絵が使われる人数
#pragma endregion
#define CHARACTER_GRAPH_NUMBER 7			// キャラクター立ち絵が使われる人数
#pragma region ver0.0039制作時コメント化コード
//#define CHARACTER_GRAPH_PAUSE_NUMBER 4		// キャラクター立ち絵のポーズ最大数
#pragma endregion
#define CHARACTER_GRAPH_PAUSE_NUMBER 10		// キャラクター立ち絵のポーズ最大数
#pragma region ver0.016制作時コメント化コード
//#define CHARACTER_GRAPH_CLOTHES_NUMBER 6	// キャラクター立ち絵の衣装最大数
#pragma endregion
#define CHARACTER_GRAPH_CLOTHES_NUMBER 10	// キャラクター立ち絵の衣装最大数
#pragma region ver0.00292制作時コメント化コード
//#define CHARACTER_GRAPH_FACE_NUMBER 3		// キャラクター立ち絵の表情差分搭載可能数
#pragma endregion
#pragma region ver0.0031制作時コメント化コード
//#define CHARACTER_GRAPH_FACE_NUMBER 7		// キャラクター立ち絵の表情差分搭載可能数
#pragma endregion
#define CHARACTER_GRAPH_FACE_NUMBER 10		// キャラクター立ち絵の表情差分搭載可能数
#define CHARACTER_GRAPH_EYE_NUMBER 6		// キャラクター立ち絵の目の数
#define CHARACTER_GRAPH_MOUSE_NUMBER 3		// キャラクター立ち絵の口の数
#define CHARACTER_GRAPH_EYE_BLOW_NUMBER 3	// キャラクター立ち絵の眉毛の数
#define MAP_HUKIDASI_NUMBER 3				// マップキャラアイコンを囲む吹き出しの数
#pragma region ver0.00295制作時コメント化コード
//#define BGM_NUMBER 18						// ＢＧＭの数
//#define BGM_NUMBER 17					// ＢＧＭの数
#pragma endregion
#pragma region ver0.00391制作時コメント化コード
//#define BGM_NUMBER 25						// ＢＧＭの数
#pragma endregion
#pragma region ver0.0051制作時コメント化コード
//#define BGM_NUMBER 31						// ＢＧＭの数
#pragma endregion
#define BGM_NUMBER 35						// ＢＧＭの数
#pragma region ver0.00295制作時コメント化コード
//#define SE_NUMBER 31						// ＳＥの数
#pragma endregion
#pragma region ver0.0035a制作時コメント化コード
//#define SE_NUMBER 35						// ＳＥの数
#pragma endregion
#pragma region ver0.00607制作時コメント化コード
//#define SE_NUMBER 54						// ＳＥの数
#pragma endregion
#define SE_NUMBER 256						// ＳＥの上限値（これが少ないとサウンドルームの座標を変更する関数で不具合が発生する）
// 描画用定数
#define LOADING_ICON_FLAME_MAX 160		// ローディングアイコンが１周するために必要なフレーム数

extern const char* load_name[CHARACTER_GRAPH_NUMBER];	// キャラクター立ち絵読み込みの際に使われる名前情報

enum BGMIDName
{
	BN_OP,				// オープニング

	BN_NICHIJOU_1,		// 日常・１
	BN_NICHIJOU_2,		// 日常・２
	BN_NICHIJOU_3,		// 日常・３
	BN_NICHIJOU_4,		// 日常・４
	BN_NICHIJOU_5,		// 日常・５
	BN_NICHIJOU_6,		// 日常・６

	BN_HAPPENING,		// ハプニング
	BN_UGLY,			// 不穏
	BN_CRY,				// 悲しい
	BN_AFTER_SCHOOL,	// 夕方
	BN_DETEMINATION,	// 決意
	BN_NIGHT,			// 夜
	#pragma region ver0.0051制作時コメント化コード
	//BN_NIGHT_PIANO,		// 夜（ピアノ）
#pragma endregion
	BN_MUSIC_ROOM,		// 音楽室
	BN_DOTABATA,		// どたばた
	BN_NIGHT_SKY,		// 夜空
	BN_CONFESSION,		// 告白
	BN_KAIDAN,			// 怪談
	BN_MYSTERY,			// 謎発生
	BN_UNEASINESS,		// 不安
	BN_RECOLLECTION,	// 回想
	BN_BATTLE,			// バトル
	BN_WILL,			// 決心
	BN_CHASER,			// 追跡人

	BN_TUTOMU,			// 校長
	BN_JURI,			// 樹里
	BN_HADUKI,			// はづき
	BN_MEGURU,			// めぐる
	BN_RINZE,			// 凛世
	BN_CHIYUKI,			// 千雪
	BN_KOGANE,			// 恋鐘

	BN_TITLE,			// タイトル
	BN_MAP,				// マップ
	BN_OPMB,			// OP_オルゴール
	BN_SENTAKUSHI		// 選択肢
};
extern BGMIDName bgmid_test;
#pragma region ver0.00707制作時コメント化コード
// ＳＥＩＤリスト
//enum SEIDName
//{
//	SN_WIND_CHIME,				// ウィンドチャイム
//	SN_CLAP,					// 拍手
//	SN_CLAP_MULTI,				// 拍手（大勢）
//	SN_CHIME,					// チャイム
//	SN_BASKETBALL_DRIBBLE,		// バスケットボールドリブル
//	SN_FOOT_STEP,				// 足音
//	SN_FOOT_STEP_LOOP,			// 足音（ループ）
//	SN_CURTAIN,					// カーテン
//	SN_DOOR_OPEN,				// 店のドアを開ける
//	SN_SLIDING_DOOR,			// 引き戸を開ける
//	SN_KNOCK,					// ノック
//	SN_BIRD_CTY,				// 鳥のさえずり
//	SN_WIND,					// 風
//	SN_ALTERNATIVE,				// 選択肢を決定する
//	SN_LIBBER,					// 川の水の流れの音
//	SN_LIBBER_LONG,				// 川の水の流れの音 Long Ver
//	SN_RUSTRE,					// 布が擦れる
//	SN_BASKETBALL_GAUL,			// バスケットボールがゴール
//	SN_COLLOSION,				// 人と人とがぶつかる
//	SN_CAT,						// 猫の鳴き声
//	SN_PAPER_MAP_MOVE,			// マップを移動するＳＥ
//	SN_CLAP_1TAP,				// ハイタッチ
//	SN_CLAP_2TAP,				// 手を叩く音
//	SN_CROWEB_STUDENTS_SHORT,	// 部活動をしている生徒たちの声
//	SN_CROWEB_STUDENTS_LONG,	// 部活動をしている生徒たちの声Long  Ver
//	SN_SHOES,					// シューズの音
//	SN_KEYBOARD_TYPING,			// キーボードを叩く
//	SN_KEYBOARD_TYPING_LOOP,	// キーボードを叩く（ループ）
//	SN_PAPER_FLYING,			// 紙が散らばる音
//	SN_PHONE_NOTICE_NOTE,		// 携帯・通知
//	SN_TUMBLE,					// 転ぶ（ずさー）
//	SN_CHAIR_STANDUP,			// 椅子を立つ音
//	SN_GATAGATA,				// ガタガタとした物音
//	SN_PHONE_CALL,				// 携帯・着信音
//	SN_ICON_TAP,				// アイコンを押した音
//	SN_AGEMONO,					// 揚げ物をする音
//	SN_FLASH_BACK,				// フラッシュバック
//	SN_HOWAN4,					// 思い出す音
//	SN_DOOR_OPEN_GATYA,			// 開き戸の音
//	SN_GASAGASA,				// ガサガサ
//	SN_DASH,					// 駆ける足音
//	SN_OPEN_WINDOW,				// 窓を開ける音
//	SN_PEN_WRITE,				// 文字を書く
//	SN_PEN_WRITE_LOOP,			// 文字を書く(LOOP)
//	SN_DOOR_OPEN_SILENT,		// 静かに戸を開く
//	SN_CHAIR_SITDOWN,			// 椅子に座る
//	SN_SEMI,					// セミの声
//	SN_JAGUTI_OPEN,				// 水道を開く
//	SN_JAGUTI_CLOASE,			// 水道を止める音
//	SN_SCEAN_CHANGE_IN,			// 場面転換IN
//	SN_SCEAN_CHANGE_OUT,		// 場面転換OUT
//	SN_STARTSCEAN_NOTE,			// スタート画面選択
//	SN_START,					// Start
//	SN_FLUID_WATER,				// 水道の音
//	SN_FLUID_WATER_LOOP,		// 水道の音(LOOP)
//	SN_GAAN,					// がーん
//	SN_HUG						// 抱きつく音
//};
#pragma endregion

// ＢＧＭの状態
enum BGMStateType
{
	BGM_STANDBY,	// 待機
	BGM_PLAY,		// 再生
	BGM_FADE_IN,	// フェードイン再生
	BGM_FADE_OUT,	// フェードアウト停止
	BGM_STOP		// 停止
};
// オプションＵＩ画像の種類
enum IMGOptionType
{
	IMG_OPTION_BACKGROUND,	// 背景
	IMG_OPTION_PAPER,		// 紙
	IMG_OPTION_MENU,		// メニュー
	IMG_OPTION_TITLE,		// OPTIONマーク
	IMG_OPTION_PIXEL_720,	// 解像度720p
	IMG_OPTION_PIXEL_1080,	// 解像度1080p
};
struct ImageHandles
{
	#pragma region ver0.0042制作時コメント化コード
	//int text_window;																																	// テキストウィンドウ
#pragma endregion
	int text_loading;																																	// 『Now Loading』
	int commu_list;																																		// 『Commu List』
	int icon_commu_option;																																// コミュオプション
	int icon_loading;																																	// ローディングアイコン
	int icon_auto[2];																																	//	『AUTO』アイコン
	int icon_skip[2];																																	//	『SKIP』アイコン
	int icon_save[2];																																	//	『SAVE』アイコン
	int icon_load[2];																																	//	『LOAD』アイコン
	int icon_menu[2];																																	//	『MENU』アイコン
	int icon_text_off;																																	//	『TEXT_OFF』アイコン
	int icon_back;																																		//	『BACK』アイコン
	int icon_title;																																		//	『TITLE』アイコン
	int icon_exit;																																		//	『EXIT』アイコン
	#pragma region ver0.0072制作時コメント化コード
	//int icon_save_file;																																	// セーブファイル
#pragma endregion
	#pragma region ver0.0081制作時コメント化コード
	//int icon_save_file_page[2];																															// セーブファイルのページ
#pragma endregion
	#pragma region ver0.00706制作時コメント化コード
	//int ui_month;																																		// 月のＵＩ（４月）
#pragma endregion
	int ui_tips;																																		// tips用ＵＩ
	int ui_map[3];																																		// マップ
	#pragma region ver0.0038制作時コメント化コード
	//int ui_map_icon[1];																																	// マップ時のキャラアイコン
#pragma endregion
	int ui_map_icon[6];																																	// マップ時のキャラアイコン
	int ui_map_hukidasi[3];																																// マップ時の吹き出しアイコン
	int ui_map_check;																		// 
	int ui_map_check_choice[2];																															// コミュ移動確認時の選択肢
	#pragma region ver0.007制作時コメント化コード
	//int altenative[3];																																	// 選択肢
#pragma endregion
	#pragma region ver0.0039制作時コメント化コード
	//int background[2];																																	// 背景
#pragma endregion
	#pragma region ver0.00605制作時コメント化コード
	//int background[BACKGROUND_NUMBER];																													// 背景
#pragma endregion
	#pragma region ver0.0029制作時コメント化コード
	//int character_body[1][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER];																// キャラクター胴体、服装[キャラ][ポーズ][服装]
	//int character_face[1][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_EYE_NUMBER + CHARACTER_GRAPH_MOUSE_NUMBER];		// キャラクター顔パーツ[キャラ][ポーズ][服装][目と口の合計]
	//int character_eyebrow[1][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_EYE_BLOW_NUMBER];							// キャラクター眉毛パーツ[キャラ][ポーズ][服装][眉毛の合計]
#pragma endregion
	int character_body[CHARACTER_GRAPH_NUMBER][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER];																							// キャラクター胴体、服装[キャラ][ポーズ][服装]
	int character_face[CHARACTER_GRAPH_NUMBER][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_FACE_NUMBER][CHARACTER_GRAPH_EYE_NUMBER + CHARACTER_GRAPH_MOUSE_NUMBER];	// キャラクター顔パーツ[キャラ][ポーズ][服装][感情][目と口の合計]
	int character_eyebrow[CHARACTER_GRAPH_NUMBER][CHARACTER_GRAPH_PAUSE_NUMBER][CHARACTER_GRAPH_CLOTHES_NUMBER][CHARACTER_GRAPH_FACE_NUMBER][CHARACTER_GRAPH_EYE_BLOW_NUMBER];							// キャラクター眉毛パーツ[キャラ][ポーズ][服装][感情][眉毛の合計]
	// コミュセレクト時
	int commu_select_type;	//	コミュ種類選択肢
	int commu_select;		//	コミュ選択肢
};
extern ImageHandles g_imghandles;

class CharacterImage
{
public:
	void SetLoadFlag(int x) { load_flag[x] = TRUE; }
	static constexpr int CHARACTER_NUMBER = 7;	// 人数
	static constexpr int PAUSE_NUMBER = 10;		// ポーズ最大数
	#pragma region ver0.016制作時コメント化コード
	//static constexpr int CLOTHES_NUMBER = 6;	// 衣装最大数
#pragma endregion
	static constexpr int CLOTHES_NUMBER = 10;	// 衣装最大数
	static constexpr int FACE_NUMBER = 10;		// 表情差分搭載可能数
	static constexpr int EYE_NUMBER = 6;		// 目の数
	static constexpr int MOUSE_NUMBER = 3;		// 口の数
	static constexpr int EYE_BLOW_NUMBER = 3; 	// 眉毛の数
	static void SetFlagAll(BOOL b);				// 全ての読み込みフラグを指定の真偽にセットする
	static void SetLoadEdit(int x, BOOL y) { load_edit[x] = y; }
	static void LoadFlagCheck();				// 読み込む画像の種類をチェックする
	static void DeleteAll();					// 全ての立ち絵をメモリから削除する
	static BOOL Load();							// 読み込み処理
	static BOOL GetLoadEdit(int x) { return load_edit[x]; }
	static int GetCharacterMember() { return CHARACTER_NUMBER; }
private:
	BOOL load_flag[CharacterImage::FACE_NUMBER];			// 読み込みフラグ
	BOOL load_flag_finished[CharacterImage::FACE_NUMBER];	// 読み込み完了フラグ
	static const char* LOAD_NAME[CharacterImage::CHARACTER_NUMBER];
	static BOOL load_edit[CharacterImage::CHARACTER_NUMBER];	// エディットモードでの個別読み込みフラグ
	int handle;																									// 胴体ハンドル
	int handle_face[CharacterImage::FACE_NUMBER][CharacterImage::EYE_NUMBER + CharacterImage::MOUSE_NUMBER];	// 胴体ハンドル
	int handle_eyebrow[CharacterImage::FACE_NUMBER][CharacterImage::EYE_BLOW_NUMBER];							// 眉毛ハンドル
};
extern CharacterImage image_character[CharacterImage::CHARACTER_NUMBER][CharacterImage::PAUSE_NUMBER][CharacterImage::CLOTHES_NUMBER];

//struct SoundHandles
//{
//	int BGM[BGM_NUMBER];
//	//int SE[SE_NUMBER];
//};
//extern SoundHandles g_sndhandles;
// ＢＧＭ（名前は下部の『MusicStringData』クラスにある）
class BGMData
{
	char path[256] = "";
	BOOL load = FALSE;			// 読み込み処理で読み込むものか判別する
	BOOL load_finished = FALSE;	// 読み込み完了フラグ
	BOOL not_release = FALSE;	// メモリ解放処理で解放しないフラグ
	int handle = 0;
	const int LOOP_POS = 0;		// ループした際の再開位置
	const int LOOP_START = 0;	// ループする位置
public:
	BGMData(char *c, BOOL x, int y, int z) : not_release(x), LOOP_POS(y), LOOP_START(z){sprintf_s(path, 256, "media\\BGM\\%s.wav", c);}
	static constexpr int NUMBER = BGM_NUMBER;	// 個数
	void SetLoad(BOOL x) { load = x; }
	void SetLoop();	// ループ関係の位置を設定する
	BOOL GetLoad() { return load; }
	BOOL GetNotRelease() { return not_release; }
	BOOL GetHandle() { return handle; }
	static void LoadFirst();		// メモリ解放されない種類のＢＧＭを読み込む	
	static void SetLoadAll(BOOL x);	// 全てのload変数を変更する
	static void LoadFlagCheck();	// 読み込むＢＧＭをチェックする
	static void DeleteAll();		// 全てのＢＧＭをメモリから削除する
	static void Load();				// ロード処理
	static int GetNumber() { return NUMBER; }
};
extern BGMData bgm[BGM_NUMBER];
// 効果音
class SEData
{
	char path[256] = "";			// 読み込み用パス
	char name[256] = "";			// ゲーム内名称
	BOOL loop;						// ループフラグ
	BOOL load_finished;				// 読み込み完了フラグ
	int Handle;
	static int number;				// 総個数
	static int commu_start_time;	// コミュスタートＳＥ再生時ミリ秒
public:
	// ＩＤリスト
	enum class IDName
	{
		WIND_CHIME,				// ウィンドチャイム
		CLAP,					// 拍手
		CLAP_MULTI,				// 拍手（大勢）
		CHIME,					// チャイム
		BASKETBALL_DRIBBLE,		// バスケットボールドリブル
		FOOT_STEP,				// 足音
		FOOT_STEP_LOOP,			// 足音（ループ）
		CURTAIN,				// カーテン
		DOOR_OPEN,				// 店のドアを開ける
		SLIDING_DOOR,			// 引き戸を開ける
		KNOCK,					// ノック
		BIRD_CTY,				// 鳥のさえずり
		WIND,					// 風
		ALTERNATIVE,			// 選択肢を決定する
		LIBBER,					// 川の水の流れの音
		LIBBER_LONG,			// 川の水の流れの音 Long Ver
		RUSTRE,					// 布が擦れる
		BASKETBALL_GAUL,		// バスケットボールがゴール
		COLLOSION,				// 人と人とがぶつかる
		CAT,					// 猫の鳴き声
		PAPER_MAP_MOVE,			// マップを移動するＳＥ
		CLAP_1TAP,				// ハイタッチ
		CLAP_2TAP,				// 手を叩く音
		CROWEB_STUDENTS_SHORT,	// 部活動をしている生徒たちの声
		CROWEB_STUDENTS_LONG,	// 部活動をしている生徒たちの声Long  Ver
		SHOES,					// シューズの音
		KEYBOARD_TYPING,		// キーボードを叩く
		KEYBOARD_TYPING_LOOP,	// キーボードを叩く（ループ）
		PAPER_FLYING,			// 紙が散らばる音
		PHONE_NOTICE_NOTE,		// 携帯・通知
		TUMBLE,					// 転ぶ（ずさー）
		CHAIR_STANDUP,			// 椅子を立つ音
		GATAGATA,				// ガタガタとした物音
		PHONE_CALL,				// 携帯・着信音
		ICON_TAP,				// アイコンを押した音
		AGEMONO,				// 揚げ物をする音
		FLASH_BACK,				// フラッシュバック
		HOWAN4,					// 思い出す音
		DOOR_OPEN_GATYA,		// 開き戸の音
		GASAGASA,				// ガサガサ
		DASH,					// 駆ける足音
		OPEN_WINDOW,			// 窓を開ける音
		PEN_WRITE,				// 文字を書く
		PEN_WRITE_LOOP,			// 文字を書く(LOOP)
		DOOR_OPEN_SILENT,		// 静かに戸を開く
		CHAIR_SITDOWN,			// 椅子に座る
		SEMI,					// セミの声
		JAGUTI_OPEN,			// 水道を開く
		JAGUTI_CLOASE,			// 水道を止める音
		SCEAN_CHANGE_IN,		// 場面転換IN
		SCEAN_CHANGE_OUT,		// 場面転換OUT
		STARTSCEAN_NOTE,		// スタート画面選択
		START,					// Start
		FLUID_WATER,			// 水道の音
		FLUID_WATER_LOOP,		// 水道の音(LOOP)
		GAAN,					// がーん
		HUG,					// 抱きつく音
		PING_PONG,				// ピンポン
		HORROR,					// ホラー
		SENTAKUSHI,				// コミュ選択肢
		START_EFFECT,			// タイトル画面
		DASH_ROOM,				// 駆ける足音(室内)
		COMMU_START				// コミュスタート
	};
	SEData(char *c_path, char *c_name, BOOL x)	// 手前のフォルダと拡張子を覗いたパス名,ゲーム内名称,ループＳＥフラグ
	{
		sprintf_s(path, 256, "media\\SE\\%s.wav"  ,c_path);	
		sprintf_s(name, 256, c_name);
		loop = x;
		number++;
	}
	// ロード処理
	void Load()
	{
		Handle = LoadSoundMem(path);	// ＳＥを読み込む
		load_finished = TRUE;			// ＳＥを読み込んだチェックを行う
	}

	void PlayBack() { PlaySoundMem(Handle, DX_PLAYTYPE_BACK); }	// 再生する（ループなし）
	// フラグに応じてループさせる
	void Play() 
	{ 
		if (loop == FALSE) { PlaySoundMem(Handle, DX_PLAYTYPE_BACK); }
		else { PlaySoundMem(Handle, DX_PLAYTYPE_LOOP); }
	}

	char* GetName() { return name; }					// 名前を取得する
	BOOL GetLoadFinished() { return load_finished; }	// 読み込み完了フラグを取得する
	int GetHandle() { return Handle; }	// 音声ハンドルを取得する
	static void SetCommuStartTime() { commu_start_time = GetNowCount(); }
	// コミュスタートＳＥ再生から２秒経過していたらTRUEを返す
	static BOOL CheckCommuStartTime() { return (commu_start_time < GetNowCount() - 2000) ? TRUE : FALSE; }

	static int GetNumber() { return number; }
};
extern SEData se[];
// 画像の縦横幅
struct GraphSize
{
	float x;
	float y;
};
#pragma region ver0.0026a制作時コメント化コード
//extern GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check, size_ui_map_check_choice, size_commu_altenative;
#pragma endregion
#pragma region ver0.007制作時コメント化コード
//extern GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check, size_commu_altenative;
#pragma endregion
extern GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check;

// 倍率補正を行った画像縦横幅
struct GraphSize2
{
	int ox;		// 倍率補正を掛けていない元々のx座標
	int oy;		// 倍率補正を掛けていない元々のy座標
	float x;
	float y;
};
//										『Commu List』												『TEXT OFF』アイコン、	セーブファイルページ、						マップ移動確認用選択肢、	マップキャラアイコン、	吹き出し、									コミュセレクト時コミュ種類選択肢、	コミュセレクト時コミュ選択肢
#pragma region ver0.0072制作時コメント化コード
//extern GraphSize2 size_icon_loading,	size_icon_commu_list,	size_text_loading, size_icon_auto,	size_icon_text_off,		size_icon_sl_file_page, size_icon_sl_file,	size_ui_map_check_choice,	size_ui_map_icon2,		size_ui_map_hukidasi[MAP_HUKIDASI_NUMBER],	size_ui_cs_alternative_type,		size_ui_cs_alternative;
#pragma endregion
extern GraphSize2 size_icon_loading, size_icon_commu_list, size_text_loading, size_icon_auto, size_icon_text_off, size_icon_sl_file_page, size_ui_map_check_choice, size_ui_map_icon2, size_ui_map_hukidasi[MAP_HUKIDASI_NUMBER], size_ui_cs_alternative_type, size_ui_cs_alternative;
#pragma region ver0.0053制作時コメント化コード
//// コミュ内容
////typedef struct state
//struct state
//{
//	char command[256];
//	int move_commu_number;					// 移動先コミュＩＤ
//	char name[256];
//	char name2[256];						// 同時に喋る２人目の名前
//	char line[256];							// 台詞
//	int line_mouse;							// 喋る際の口パクタイプ
//	int character[3];						// 描画するキャラ、差分
//	int character_face_etc[3];				// キャラの特殊表情ＩＤ
//	int character_change;					// キャラクター変更タイプ
//	int character_even_distance;			// キャラクター距離均一化のオンオフ
//	int background;							// 描画背景
//	BackgroundChangeType background_change;	// 背景変更タイプ
//	int bgm;								// 再生するＢＧＭ
//	BGMChangeType bgm_change;				// ＢＧＭ切り替えタイプ
//	int se;									// 再生するＳＥ
//	char altenative_message[3][128];		// 選択肢文
//	int altenative_jump[3];					// 選択肢のジャンプ先の行
//	// コマンドを変更する
//	void CommandChange(char* c){ sprintf_s(command, 256, c); }	// 代入文字列
//	// 各特定コマンド用数値を変更する
//	void CommandNumberChange(int x){ move_commu_number = x; }	// 数値
//	// 台詞主を変更する（入力文字列版）
//	void LineCharacterChange(int x, int y) 	// 編集台詞主用配列変数,代入文字列
//	{
//		if(x == 0){ GetKeyInputString(name, y); }		
//		else { GetKeyInputString(name2, y); }
//	}
//	// 台詞主を変更する（char変数版）
//	void LineCharacterChange(int x, char* c) 	// 編集台詞主用配列変数,代入文字列
//	{
//		if(x == 0){ sprintf_s(name, 256, c); }
//		else{ sprintf_s(name2, 256, c); }
//	}	
//	void LineChange(int x) { GetKeyInputString(line, x); }	// 台詞を変更する（x：代入文字列）
//	void LineChange(char* c) { sprintf_s(line, 256, c); }	// 台詞を変更する（char変数版、c：代入文字列）
//	void LineMouseChange(int x) { line_mouse = x; }				// 口パクタイプを変更する（x：代入数値）
//	// エディットモードでcharacter[x]の数値を変える際の共通処理
//	void CharacterIDChange(int x, int y, int z) // 変更するキャラクター,変更するID数値の桁の位,変更後の数字
//	{
//		int a = (int)pow(10, y - 1);
//		int b = character[x] / a;
//		if (b >= 10) { b %= 10; }
//		character[x] = character[x] - a * b + a * z;
//	}
//	// キャラの特殊表情を変更する				
//	void CFECHANGE(int x, int y) { character_face_etc[x] = y; }	// キャラクター,数値
//	// キャラクター変更タイプを変更する
//	void CCCHANGE(int x) { character_change = x; }
//	// キャラ間距離均一化を変更する
//	void CDUCHANGE(int x) { character_even_distance = x; }	// 変更する数値
//	// 背景を変更する
//	void BackgroundChange(int x) { background = x; }	// 変更する
//	// 背景変更タイプを変更する
//	void BackgroundChangeTypeChange(BackgroundChangeType x) { background_change = x; }	// 変更する数値
//	// 再生ＢＧＭを変更する
//	void BGMChange(int x) { bgm = x; }	// ＢＧＭ用変数
//	// ＢＧＭ変更タイプを変更する
//	void BCTChange(BGMChangeType x) { bgm_change = x; }
//	// ＳＥ数値を変更する
//	void SEChange(int x) { se = x; }	// 専用変数
//	// 選択肢文字列を変更する
//	void AlternativeChange(int x, int y) { GetKeyInputString(altenative_message[x], y); }// 選択肢用変数,代入文字列
//	// 選択肢ジャンプ先行を変更する
//	void AlternativeJumpChange(int x, int y) { altenative_jump[x] = y; }	// 選択肢用変数,数値
//	// コマンド名を取得する
//	char* GetCommand() { return command; }
//	// １人目の台詞主名を取得する
//	char* GetLineCharacterName(){ return name; }
//	// ２人目の台詞主名を取得する
//	char* GetLineCharacterName2() { return name2; }
//	// 台詞文字列を取得する
//	char* GetLine() { return line; };
//	// 選択肢の文字列を取得する
//	char* GetAlternativeString(int x){ return altenative_message[x]; }
//	// コマンド用数値を取得する
//	int GetCommandNumber(){ return move_commu_number; }
//	// 喋る際の口パクタイプを取得する
//	int GetLineMouse(){ return line_mouse; }
//	// 描画するキャラ用変数値を取得する
//	int GetCharacter(int x){ return character[x]; }	// キャラの位置
//	// キャラの特殊表情ＩＤを取得する
//	int GetCFE(int x){ return character_face_etc[x];}	// キャラの位置
//	// キャラクター変更タイプ数値を取得する
//	int GetCC() { return character_change; }
//	// キャラ間距離均一化を取得する
//	int GetCDU() { return character_even_distance; }
//	// 背景用変数を取得する
//	int GetBackground() { return background; }
//	// ＢＧＭ用変数を取得する
//	int GetBGM() { return bgm; }
//	// ＳＥ用変数を取得する
//	int GetSE() { return se; }
//	// 選択肢ジャンプ先用変数を取得する
//	int GetAlternativeJump(int x){ return altenative_jump[x]; }	// 選択肢
//	// 背景変更タイプ用変数を取得する
//	BackgroundChangeType GetBackgroundChangeType() { return background_change; }
//	// ＢＧＭ変更タイプ用配列定数を取得する
//	BGMChangeType GetBGMCT() { return bgm_change; }
//
//};
//#pragma region ver0.0034制作時コメント化コード
////extern state HM[512][128];
//#pragma endregion
//extern state HM[512][COMMU_LINE_MAX], commu_state_edit[COMMU_LINE_MAX + 1];
#pragma endregion
// BGMの状態（BGM_NUMBER定数があるのでgamemusic.hに置けない）
struct BGMState
{
	BGMStateType state;	// 状態
	int	vol;			// 音量に関わる変数
};
extern BGMState g_bgmstate[BGM_NUMBER];
// ＢＧＭタイトルデータ（列挙定数の都合上soundroom.hに記述していない）
class MusicStringData
{
public:
	char* name;
	void NameChange(int x)
	{
		enum BGMIDName y;
		y = static_cast<BGMIDName>(x);	// 数字を列挙型に変換する
		switch (y)
		{
		#pragma region ver0.0026制作時コメント化コード
		//case BN_NICHIJOU_1:		name = "日常・１";		break;
		//case 1:					name = "日常・２";		break;
		//case 2:					name = "日常・３";		break;
		//case 3:					name = "ハプニング";	break;
		//case 4:					name = "不穏";			break;
		//case 5:					name = "悲しい";		break;
		//case BN_AFTER_SCHOOL:	name = "夕方";			break;
		//case BN_DETEMINATION:	name = "決意";			break;
		//case BN_NIGHT:			name = "夜";			break;
		//case BN_MUSIC_ROOM:		name = "音楽室";		break;
		//case BN_TUTOMU:			name = "校長";			break;
		//case BN_JURI:			name = "樹里";			break;
		//case BN_HADUKI:			name = "はづき";		break;
		//case BN_MEGURU:			name = "めぐる";		break;
		//case BN_RINZE:			name = "凛世";			break;
		//case BN_CHIYUKI:		name = "千雪";			break;
		//case BN_TITLE:			name = "メイン";		break;
		//case BN_MAP:			name = "マップ";		break;
		//default:				name = "";				break;
#pragma endregion
		case -1:				name = (char*)"ＢＧＭ停止";		break;
		case BN_OP:				name = (char*)"ＯＰ";			break;
		case BN_NICHIJOU_1:		name = (char*)"日常1";		break;
		case BN_NICHIJOU_2:		name = (char*)"日常2";		break;
		case BN_NICHIJOU_3:		name = (char*)"日常3";		break;
		case BN_NICHIJOU_4:		name = (char*)"日常4";		break;
		case BN_NICHIJOU_5:		name = (char*)"日常5";		break;
		case BN_NICHIJOU_6:		name = (char*)"日常6";		break;
		case BN_HAPPENING:		name = (char*)"ハプニング";		break;
		case BN_UGLY:			name = (char*)"不穏";			break;
		case BN_CRY:			name = (char*)"悲しい";			break;
		case BN_AFTER_SCHOOL:	name = (char*)"夕方";			break;
		case BN_DETEMINATION:	name = (char*)"決意";			break;
		case BN_NIGHT:			name = (char*)"夜";				break;
		#pragma region ver0.0051制作時コメント化コード
		//case BN_NIGHT_PIANO:	name = (char*)"夜 ピアノver";	break;
#pragma endregion
		case BN_MUSIC_ROOM:		name = (char*)"音楽室";			break;
		case BN_DOTABATA:		name = (char*)"どたばた";		break;
		case BN_NIGHT_SKY:		name = (char*)"夜空";			break;
		case BN_CONFESSION:		name = (char*)"告白";			break;
		case BN_KAIDAN:			name = (char*)"怪談";			break;
		case BN_MYSTERY:		name = (char*)"謎発生";			break;
		case BN_UNEASINESS:		name = (char*)"不安";			break;
		case BN_RECOLLECTION:	name = (char*)"回想";			break;
		case BN_BATTLE:			name = (char*)"バトル";			break;
		case BN_WILL:			name = (char*)"決心";			break;
		case BN_CHASER:			name = (char*)"追跡人";			break;
		case BN_TUTOMU:			name = (char*)"校長BGM";		break;
		case BN_JURI:			name = (char*)"樹里BGM";		break;
		case BN_HADUKI:			name = (char*)"はづきBGM";		break;
		case BN_MEGURU:			name = (char*)"めぐるBGM";		break;
		case BN_RINZE:			name = (char*)"凛世BGM";		break;
		case BN_CHIYUKI:		name = (char*)"千雪BGM";		break;
		case BN_KOGANE:			name = (char*)"恋鐘BGM";		break;
		case BN_TITLE:			name = (char*)"メイン";			break;
		case BN_MAP:			name = (char*)"マップ";			break;
		case BN_OPMB:			name = (char*)"OP_オルゴール";	break;
		case BN_SENTAKUSHI:		name = (char*)"選択肢";			break;
		default:				name = (char*)"";				break;
		}
	}
	char* GetName() { return name; }
};
extern MusicStringData music_string[], music_string_stop;

extern char* bgm_name[BGM_NUMBER];

extern int loading_icon_flame;		// ローディングアイコン描画用経過フレーム
extern int g_time_first_load_start;	// FIRST_LOADモードが始まったミリ秒
extern int g_time_load_start;		// 現フレームでロードを開始したミリ秒
// フォント
extern int g_font1;					// 小さい文字
//extern int g_font2;					// 小さい縁取り文字
extern int g_font3;					// 各解像度対応文字
extern int g_font_commu_name;		// コミュ状態台詞主用文字
extern int g_font_commu_line;		// コミュ状態台詞用文字
extern int g_font_tips;				// tips用文字

extern BOOL debug_mute;																																// ＢＧＭを読み込むか判別するデバッグ機能
extern BOOL load_bgm_finished[BGM_NUMBER];																											// ＢＧＭが既に読み込まれてるか判別する
#pragma region ver0.00607制作時コメント化コード
//extern BOOL load_se_finished[SE_NUMBER];																											// ＳＥが既に読み込まれてるか判別する
#pragma endregion

void DrawLoading();								// ロードに関係する描画処理
void LoadFont();								// ２回以上読み込まれる可能性があるフォントを定義する
void GraphSizeChange(GraphSize2 *pgs, int x);	// 代入された画像サイズ値をスクリーン倍率に応じた値にする
#pragma region ver0.0029制作時コメント化コード
//void LoadGameImageCharacterBody(int x, int *y);	// キャラクターの身体部分を読み込む
#pragma endregion
//void LoadGameImageCharacterBody(int x, int* y, char* z);	// キャラクターの身体部分を読み込む
void LoadGameImageCharacterBody(int x, int* y, const char* z, int a);	// キャラクターの身体部分を読み込む

BOOL LoadGameImage();
#pragma region ver0.017制作時コメント化コード
//BOOL LoadBGM(BGMIDName x);						// ＢＧＭを読み込む
//BOOL LoadBGM2(SoundHandles *x, int y, char *z);	// LoadBGM内での共通処理
#pragma endregion
BOOL LoadSE();									// ＳＥを読み込む

#endif

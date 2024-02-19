#include "gamemaincommunication.h"
CommuStatusType g_commustatus;
AltenativeNumberType g_altenativenumber;			// 表示選択肢の種類（個数）
CommuAutoType g_commuauto;							// コミュ自動進行状態の種類
CommuCharacterFaceType g_commu_character_face[3];	// 描画されるキャラの特殊表情タイプ

float AlternativeCoordinate::y_upper = 0;
float AlternativeCoordinate::y_under = 0;
/* TextLogクラス ---------*/
BOOL TextLog::mode = FALSE;
int TextLog::top_id_now = 0;
int TextLog::next_input_id = 0;
int TextLog::page = 1;
const int TextLog::PAGES_LINE_NUMBER = 4;
TextLog text_log[COMMU_LINE_MAX];
// テキストログを代入する
void TextLog::Input()
{
	// （選択肢場面だったらスキップする処理）

	// 台詞が０文字だったらスキップする
	if (std::strcmp(HM[commu_number][cell_number].GetLine(), "") != 0)
	{
		sprintf_s(line, 128, HM[commu_number][cell_number].GetLine());
		// 台詞主（現在はキャラサムネを表示するためだけなので中点をつける必要はない）
		sprintf_s(character, 32, "%s%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name, HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2);

		line_number = cell_number;	// コミュ内での行
		next_input_id++;
	}
}
// 描画する
void TextLog::Draw()
{
	// 背景、ロゴ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int i = 0; i < ImgData2::LOG_BACKGROUND_NUMBER; i++) { image_bl_background[i].DrawImage(); }

	for (int i = 0; i < 4; i++)
	{
		// 台詞
		BOOL end = FALSE;
		// 参照する文字列番号と文字列中の文字ポインタ
		int CP_A = 0;
		// 仮想画面上での文字表示カーソルの位置
		int CursorX_A = 0;
		int CursorY_A = 0;

		int y = 0;		// 永久ループ回避用テスト変数
		int	row = 1;	// 台詞行数
		// 選択肢用仮想テキストバッファ（横サイズ（２番目）の数字は適当）
		char StringBuf[STRBUF_ALTENATIVE_HEIGHT][STRBUF_ALTENATIVE_WIDTH + 2] = {"", "", ""};
		do
		{
			char Moji = 0;
			#pragma region ver0.021制作時コメント化コード
			//// 文字の描画
			//Moji = text_log[i].line[CP_A];
			//switch (Moji)
			//{
			//case '@':	// 改行文字
			//	// 改行処理および参照文字位置を一つすすめる
			//	CursorY_A++;
			//	CursorX_A = 0;
			//	CP_A++;
			//	row++;	// 描画座標参照に使われる行数をカウントする
			//	break;
			//default:	// その他の文字
			//	// １文字のバイト数を取得
			//	int Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &HM[commu_number][cell_number].line[CP_A]);
			//	// １文字テキストバッファに代入
			//	for (int moji_i = 0; moji_i < Bytes; moji_i++) { StringBuf[CursorY_A][CursorX_A + moji_i] = text_log[i].line[CP_A + moji_i]; }
			//	// 参照文字位置を１文字のバイト数分進める
			//	CP_A += Bytes;
			//	// カーソルを一文字のバイト数分進める
			//	CursorX_A += Bytes;
			//	// テキストバッファ横幅からはみ出たら改行する
			//	if (CursorX_A >= STRBUF_ALTENATIVE_WIDTH)
			//	{
			//		CursorY_A++;
			//		CursorX_A = 0;
			//	}
			//	break;
			//}
			//// 参照文字列の終端まで行っていたら参照文字列を進める
			//if (text_log[i].line[CP_A] == '\0') { end = TRUE; }

			//y++;
#pragma endregion
			// 文字の描画
			Moji = text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A];
			switch (Moji)
			{
			case '@':	// 改行文字
				// 改行処理および参照文字位置を一つすすめる
				CursorY_A++;
				CursorX_A = 0;
				CP_A++;
				row++;	// 描画座標参照に使われる行数をカウントする
				break;
			default:	// その他の文字
				// １文字のバイト数を取得
				int Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A]);
				// １文字テキストバッファに代入
				for (int moji_i = 0; moji_i < Bytes; moji_i++) { StringBuf[CursorY_A][CursorX_A + moji_i] = text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A + moji_i]; }
				// 参照文字位置を１文字のバイト数分進める
				CP_A += Bytes;
				// カーソルを一文字のバイト数分進める
				CursorX_A += Bytes;
				// テキストバッファ横幅からはみ出たら改行する
				if (CursorX_A >= STRBUF_ALTENATIVE_WIDTH)
				{
					CursorY_A++;
					CursorX_A = 0;
				}
				break;
			}
			// 参照文字列の終端まで行っていたら参照文字列を進める
			if (text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A] == '\0') { end = TRUE; }

			y++;
		} while (end == FALSE && y < 255);
		/* 描画 ---------*/
		int z = 180;

		int x = -1;
		if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "主人公") == 0) { x = 0; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "めぐる") == 0) { x = 1; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "恋鐘") == 0) { x = 2; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "樹里") == 0) { x = 3; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "凛世") == 0) { x = 4; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "千雪") == 0) { x = 5; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "はづき") == 0) { x = 6; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "校長") == 0) { x = 7; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "") != 0) { x = 8; }
		/* テキストウィンドウ ---------*/
		int a = 0;
		// 台詞が表示し終わっていて、チェック行の台詞で『text_window_color』コマンドを使っているなら
		#pragma region ver0.031制作時コメント化コード
		//if (((page - 1) * PAGES_LINE_NUMBER + i < next_input_id) && std::strcmp(HM[commu_number][i + (page - 1) * PAGES_LINE_NUMBER].GetCommand(), "text_window_color") == 0)
#pragma endregion
		if (((page - 1) * PAGES_LINE_NUMBER + i < next_input_id) && std::strcmp(HM[commu_number][text_log[i + (page - 1) * PAGES_LINE_NUMBER].line_number].GetCommand(), "text_window_color") == 0)
		{
			#pragma region ver0.031制作時コメント化コード
			//switch (HM[commu_number][i + (page - 1) * PAGES_LINE_NUMBER].GetCommandNumber())
#pragma endregion
			switch (HM[commu_number][text_log[i + (page - 1) * PAGES_LINE_NUMBER].line_number].GetCommandNumber())
			{
			case 1: a = 4;	break;
			case 2: a = 1;	break;
			case 3: a = 2;	break;
			case 4: a = 3;	break;
			default:		break;
			}
		}
		else
		{
			if (x == 0) { a = 1; }
			else if (x >= 1 && x <= 5) { a = 2; }
			else if (x == 6 || x == 8) { a = 3; }
			else if (x == 7) { a = 4; }
		}
		// バックログ用
		char c[256];
		sprintf_s(c, 256, "セリフ%d・%d\n", i + (page - 1) * PAGES_LINE_NUMBER, a);
		LogFileAdd(c);

		image_log_text_window[a].DrawImageCoordinateY((i * z + 222) * bairitu);
		/*-----------------------------*/
		// 台詞主ＵＩ
		if (x >= 0) { image_map_character[x].DrawImageCoordinateY((i * z + 270) * bairitu); }

		if ((page - 1) * PAGES_LINE_NUMBER + i < next_input_id)
		{
			for (int j = 0; j < row; j++)
			{
				DrawFormatStringFToHandle(180 * bairitu, (i * z + j * 45 + 240) * bairitu, GetColor(0, 0, 0), g_font_commu_line, StringBuf[j]);
				//DebugLog(LogOutputType::LOG_MESSAGE);
				// バックログ用
				//char c[256];
				//sprintf_s(c, 256, "%s\n", StringBuf[j]);
				//LogFileAdd(c);
			}
		}
		/*---------------*/
	}
	// ページ数
	char c[256];
	sprintf_s(c, 256, "%d／%d\n", page, (next_input_id - 1) / PAGES_LINE_NUMBER + 1);
	DrawFormatStringFToHandle(165 * bairitu, bairitu * 930, GetColor(0, 0, 0), g_font_commu_line, c);
	// 矢印アイコン
	for (int i = 0; i < ImgDataHJ2::TEXT_LOG_ARROW_NUMBER; i++){image_icon_text_log[i].DrawImage();}
	// BACKアイコン
	image_icon_log_back.DrawImage();
}
// ページ数をセットし上下限を超えないよう修正する
void TextLog::SetPage(int x)
{
	int y = (next_input_id - 1) / PAGES_LINE_NUMBER + 1;	// 最大のページ数
	int z = page;	// ＳＥ判定用変更前ページ数
	page = x;
	if (page < 1) { page = 1; }
	else if (page > y) { page = y; }
	if (page != z) { SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE)); }	// ＳＥを鳴らす

}
// 状態をリセットする
void TextLog::Reset()
{
	for (int i = 0; i < COMMU_LINE_MAX; i++)
	{
		sprintf_s(text_log[i].character, 32, "");
		sprintf_s(text_log[i].line, 128, "");
		text_log[i].line_number = 0;
	}
	next_input_id = 0;
	page = 1;
}
/*------------------------*/

BOOL commu_mode_background = FALSE;	// ＳＥが変わりきるまでクリック操作できないようにするフラグ
BOOL commu_mode_distance = FALSE;	// 表示されているキャラが２人の際、均等に並べるか
BOOL commu_mode_menu = FALSE;		// メニューの内容を表示する
BOOL commu_mode_text_off = FALSE;	// テキストファイル含めた全てのＵＩを非表示にする
BOOL commu_before_cs = FALSE;		// コミュの閲覧を始める前はコミュセレクトモードだったか判別する
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cft=click_flag_title）
BOOL cfgmc_move_title = FALSE;		// タイトル画面へ移動
#pragma region ver0.007制作時コメント化コード
//BOOL cfgmc_altenative[3];			// 選択肢を選択
#pragma endregion
BOOL cfgmc_cell_count = FALSE;		// コミュの情報を次のものにする
BOOL cfgmc_change_auto = FALSE;		// オートモード切り替えを
BOOL cfgmc_change_skip = FALSE;		// スキップモード切り替えを
BOOL cfgmc_exit_save = FALSE;		// セーブモードへ移行
BOOL cfgmc_exit_load = FALSE;		// ロードモードへ移行
BOOL cfgmc_change_menu = FALSE;		// メニューモード切り替えを
BOOL cfgmc_change_text_off = FALSE;	// テキストオフモード切り替えを
BOOL cfgmc_exit_option = FALSE;		// 設定モードへ移行

char String[][256] = 
{
	"",
	"E",
};
char* commu_bgm_name;																				// コミュでＢＧＭが再生された際、表示される名前

int CursorX, CursorY;	// 仮想画面上での文字表示カーソルの位置
int KeyWaitFlag;			// ボタン押し待ちフラグ
int Count;				// フレームカウンタ

int commu_number = 0;					// 現在参照されているコミュＩＤ
int cell_number = 0;					// 参照されるセルの行数
int commu_character[3];						// 描画されるキャラＩＤ（キャラ、服装、ポーズ等）
int commu_character_blink_limit[3];			// まばたきをし終えるまでの残りフレーム数
int commu_character_talk_limit[3];			// 口パクをし終えるまでの残りフレーム数
int commu_character_before[3];				// 切り替え前のキャラクター
int commu_character_after[3];				// 切り替え後のキャラクター
#pragma region ver0.00294制作時コメント化コード
//int commu_character_visibility_count = 0;	// キャラクター不透明度切り替えが完了するまでのフレーム数
#pragma endregion
int commu_character_visibility_count[COMMU_CHARACTER_MAX];	// キャラクター不透明度切り替えが完了するまでのフレーム数
int commu_background;						// 背景
int commu_background_before;				// 切り替え前の背景
int commu_background_visibility_count = 0;	// 背景切り替えが完了するまでのフレーム数
int commu_bgm_flame = 180;					// ＢＧＭが切り替わってからの経過フレーム数
int commu_altenative_string_line[3];		// 各選択肢の行数
int commu_message_point = 0;				// 台詞を描画する際に必要なポイント
int commu_auto_count = 0;					// 次行に自動で行くためのカウント
int commu_frame_auto_count = 0;				// 『frame_auto』で次行に自動で行くためのカウント
int text_window_clear_percentage = 0;		// テキストウィンドウ透過度
/* 文字列描画用テストコード---------*/
int moji_i, moji_j;
int Bytes;
/* ---------------------------------*/

float commu_play_time = 0;					// プレイ時間（秒）
#pragma region ver0.007制作時コメント化コード
//float commu_altenative_x[3];				// 選択肢x座標
#pragma endregion
#pragma region ver0.00704制作時コメント化コード
//float commu_altenative_y_upper = 0;			// 上側選択肢y座標
//float commu_altenative_y_under = 0;			// 下側選択肢y座標
#pragma endregion
float commu_altenative_string_center_x[3];	// 選択肢文字列中心x座標
float commu_coordinate_icon_auto_x = 0;		// 『auto』アイコンx座標
float commu_coordinate_icon_auto_y = 0;		// 『auto』アイコンy座標
float commu_coordinate_icon_skip_y = 0;		// 『SKIP』アイコン上端y座標
float commu_coordinate_icon_save_y = 0;		// 『SAVE』アイコン上端y座標
float commu_coordinate_icon_load_y = 0;		// 『LOAD』アイコン上端y座標
float commu_coordinate_icon_option_y = 0;	// 『OPTION』アイコン上端y座標
float commu_coordinate_icon_menu_y = 0;		// 『MENU』アイコン上端y座標
float commu_coordinate_icon_tf_x = 0;		// 『TEXT OFF』アイコン左端x座標

// コミュ画面移行処理
#pragma region ver0.00396制作時コメント化コード
//void GameMainCommunicationNext(int x)	// 参照されるコミュID
#pragma endregion
void GameMainCommunicationNext(int x, BOOL y, int z)	// 参照されるコミュID, コミュセレクト画面から来たか,セル番号
{
	g_gamestate = GAME_MAIN_COMMUNICATION;
	MusicPlay(-1);	// ＢＧＭ停止
	// 描画位置の初期位置セット
	CursorX = 0;
	CursorY = 0;
	// 参照文字位置をセット
	SP = 0;	// １行目の
	CP = 0;	// ０文字
	// フォントのサイズセット
	SetFontSize(MOJI_SIZE);
	// フレームカウンタ初期化
	Count = 0;
	// 読み込みセル行数初期化
	//cell_number = 0;
	#pragma region ver0.00607制作時コメント化コード
	//cell_number = -1;	// 別の処理ですぐ『0』になるので、ズレ防止
#pragma endregion
	cell_number = z - 1;	// 別の処理ですぐ『0』になるので、ズレ防止

	commu_number = x;		// 現在参照コミュIDを変更

	// 立ち絵読み込みテスト
	CharacterImage::SetFlagAll(FALSE);
	CharacterImage::LoadFlagCheck();
	if (mode_debug == FALSE) { CharacterImage::DeleteAll(); }	// デバッグモードなら一々消さない
	#pragma region ver0.0091制作時コメント化コード
	//CharacterImage::Load();
#pragma endregion
	if (CharacterImage::Load() == FALSE) { quit_game = TRUE; }
	// ＢＧＭ読み込み
	BGMData::SetLoadAll(FALSE);									// 読み込み前のリセット処理
	BGMData::LoadFlagCheck();									// どれを読み込むかチェック
	if (mode_debug == FALSE) { BGMData::DeleteAll(); }			// 不必要なＢＧＭを削除（デバッグモードなら一々消さない）
	BGMData::Load();											// 読み込む

	DebugLog(LogOutputType::LOAD_FLAG);

	commu_before_cs = y;	// どのモードから来たか記憶
	// リセット処理等
	for (int i = 0; i < 3; i++){ commu_character[i] = 0; }	// キャラクターの立ち絵状態
	commu_mode_distance = FALSE;							// 表示されているキャラが２人の際、均等に並べるか
	TextLog::Reset();										// テキストログ
	// マップ画面のコミュスタートＳＥが鳴っている限りループし続ける
	while (SEData::CheckCommuStartTime() == FALSE) {}

	GameMainCommunicationNextLine();						// 最初の行要素を読み込む
	g_commustatus = COMMU_STATUS_NORMAL;					// コミュの状態
	commu_message_point = 0;								// 台詞を描画する際に必要なポイント
	// 選択肢のジャンプ先履歴
	for (int i = 0; i < COMMU_LINE_MAX; i++) { state::SetAlternativeMoveNumber(i, 0); }	

	#pragma region ver0.0033制作時コメント化コード
	//commu_mode_distance = FALSE;							// 表示されているキャラが２人の際、均等に並べるか
#pragma endregion
	#pragma region ver0.00704制作時コメント化コード
	//g_commuauto = COMMU_AUTO_NORMAL;						// コミュ自動進行状態
#pragma endregion
	if (g_commuauto == COMMU_AUTO_SKIP) { g_commuauto = COMMU_AUTO_NORMAL; }	// コミュ自動進行状態
	// チュートリアルモードに必要な要素をリセットする
	ImgDataBGTutorial::Reset();
	// （デバッグ用）使われる背景のフラグを立てる
	for (int i = 0; i < COMMU_LINE_MAX; i++) 
	{ 
		if (HM[commu_number][i].GetBackground() > 0) { bgimage[HM[commu_number][i].GetBackground() - 1].SetUse(TRUE); }
	}
}
// GameMainCommunication状態のメイン処理
void GameMainCommunication()
{
	GameMainCommunicationControl();
	GameMainCommunicationFlame();
	DrawGameMainCommunication();
}
// コミュ画面操作処理
void GameMainCommunicationControl()
{
	// マウスのボタンが押されたり離されたりしたかどうかの情報を取得する
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		// 左ボタンが押されていたら
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				#pragma region ver0.0081制作時コメント化コード
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfgmc_move_title = TRUE; }
//				#pragma region ver0.007制作時コメント化コード
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[0], commu_altenative_y_upper, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, TRUE, FALSE) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ cfgmc_altenative[0] = TRUE; }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[1], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, TRUE, FALSE) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ cfgmc_altenative[1] = TRUE; }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[2], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, TRUE, FALSE) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ cfgmc_altenative[2] = TRUE; }
//#pragma endregion
//				else if (hjimage_alternative[0].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
#pragma endregion
				// バックログ表示時は基本的な操作ができない
				if (TextLog::GetMode() == FALSE)
				{
					if (hjimage_alternative[0].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
					else if (hjimage_alternative[1].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
					else if (hjimage_alternative[2].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
					#pragma region ver0.0028制作時コメント化コード
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE){ cfgmc_change_auto = TRUE; }
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE){ cfgmc_change_skip = TRUE; }
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfgmc_exit_save = TRUE; }
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfgmc_exit_load = TRUE; }
#pragma endregion
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_change_auto = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_change_skip = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_exit_save = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_exit_load = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_option_y, image_icon_option.size_x, image_icon_option.size_y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_exit_option = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_menu_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_TEXT) == TRUE) { cfgmc_change_menu = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_tf_x, commu_coordinate_icon_menu_y, size_icon_text_off.x, size_icon_text_off.y, TRUE, FALSE, CFC_COMMU_TEXT) == TRUE) { cfgmc_change_text_off = TRUE; }
					// ログ
					else if (image_icon_log.JudgementClickCheckFlag(commu_mode_menu == TRUE && commu_mode_text_off == FALSE) == TRUE) {}
					else { cfgmc_cell_count = TRUE; }
				}
				// バックログ表示時
				else
				{
					if(image_icon_log_back.JudgementClickCheck() == TRUE){}
					else if(image_icon_text_log[0].JudgementClickCheck() == TRUE){}
					else if (image_icon_text_log[1].JudgementClickCheck() == TRUE) {}
					else if (image_icon_text_log[2].JudgementClickCheck() == TRUE) {}
					else if (image_icon_text_log[3].JudgementClickCheck() == TRUE) {}
				}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				#pragma region ver0.0081制作時コメント化コード
//				// タイトル画面へ移動
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfgmc_move_title) == TRUE){ GameTitleNext(); }
//				// 選択肢に対応した行にジャンプする（『ジャンプ先の行－１』行目まで飛んだ後、GameMainCommunicationNextLine関数を呼び出す）
//				// （選択肢を選んだらテキストオフ機能が解除されるようにする？）
//				#pragma region ver0.007制作時コメント化コード
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[0], commu_altenative_y_upper, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, FALSE, cfgmc_altenative[0]) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ GameMainCommunicationAltenative(0); }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[1], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, FALSE, cfgmc_altenative[1]) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ GameMainCommunicationAltenative(1); }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[2], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, FALSE, cfgmc_altenative[2]) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ GameMainCommunicationAltenative(2); }
//#pragma endregion
//				else if (hjimage_alternative[0].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(0); }
#pragma endregion
				// バックログ表示時は基本的な操作ができない
				if (TextLog::GetMode() == FALSE)
				{
					if (hjimage_alternative[0].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(0); }
					else if (hjimage_alternative[1].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(1); }
					else if (hjimage_alternative[2].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(2); }
					#pragma region ver0.0028制作時コメント化コード
					// オートモードを切り替え
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_auto) == TRUE)
	//				{ 
	//					// 通常、スキップ状態なら
	//					if (g_commuauto != COMMU_AUTO_ON)
	//					{
	//						#pragma region ver0.0024制作時コメント化コード
	//						//g_commuauto = COMMU_AUTO_ON;
	//						//commu_auto_count;
	//#pragma endregion
	//						GameMainCommunicationAuto();
	//					}
	//					// オートモードなら通常に戻す
	//					else{ g_commuauto = COMMU_AUTO_NORMAL; }
	//					// ＳＥを鳴らす
	//					SEPlay(SN_ALTERNATIVE);
	//				}
	//				// スキップモード切り替え
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_skip) == TRUE)
	//				{
	//					// 通常、オート状態ならスキップモードにする
	//					if (g_commuauto != COMMU_AUTO_SKIP){ g_commuauto = COMMU_AUTO_SKIP; }
	//					// スキップモードなら通常に戻す
	//					else{ g_commuauto = COMMU_AUTO_NORMAL; }
	//					// ＳＥを鳴らす
	//					SEPlay(SN_ALTERNATIVE);
	//				}
	//				// セーブモードへ移行
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_save) == TRUE) { GameSaveLoadNext(TRUE, SL_BEFORE_COMMU); }
	//				// ロードモードへ移行
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_load) == TRUE) { GameSaveLoadNext(FALSE, SL_BEFORE_COMMU); }
#pragma endregion
					// オートモードを切り替え
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_auto) == TRUE && commu_mode_menu == TRUE)
					{
						// 通常、スキップ状態なら
						if (g_commuauto != COMMU_AUTO_ON) { GameMainCommunicationAuto(); }
						// オートモードなら通常に戻す
						else { g_commuauto = COMMU_AUTO_NORMAL; }
						// ＳＥを鳴らす
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}
					// スキップモード切り替え
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_skip) == TRUE && commu_mode_menu == TRUE)
					{
						// 通常、オート状態ならスキップモードにする
						if (g_commuauto != COMMU_AUTO_SKIP) { g_commuauto = COMMU_AUTO_SKIP; }
						// スキップモードなら通常に戻す
						else { g_commuauto = COMMU_AUTO_NORMAL; }
						// ＳＥを鳴らす
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}
					// セーブモードへ移行
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_save) == TRUE && commu_mode_menu == TRUE)
					{
						GameSaveLoadNext(TRUE, SL_BEFORE_COMMU);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// ＳＥを鳴らす
					}
					// ロードモードへ移行
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_load) == TRUE && commu_mode_menu == TRUE)
					{
						GameSaveLoadNext(FALSE, SL_BEFORE_COMMU);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// ＳＥを鳴らす
					}
					// オプションモードへ移行
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_option_y, image_icon_option.size_x, image_icon_option.size_y, FALSE, cfgmc_exit_option) == TRUE && commu_mode_menu == TRUE)
					{
						GameConfigNext(TRUE);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// ＳＥを鳴らす
					}
					// メニューモードを切り替える
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_menu_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_menu) == TRUE)
					{
						FlagChange(&commu_mode_menu);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// ＳＥを鳴らす
					}
					// 画面のＵＩを非表示にする（テキストオフモードにする）
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_tf_x, commu_coordinate_icon_menu_y, size_icon_text_off.x, size_icon_text_off.y, FALSE, cfgmc_change_text_off) == TRUE)
					{
						g_commuauto = COMMU_AUTO_NORMAL;	// オート、スキップモードを解除する
						commu_mode_text_off = TRUE;
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// ＳＥを鳴らす
					}
					// ログ
					else if (image_icon_log.JudgementReleaseCheck() == TRUE) 
					{ 
						TextLog::SetMode(TRUE); 
						TextLog::SetPage((TextLog::GetNIID() - 1) / TextLog::GetPagesLineNumber() + 1);
						// ＳＥを鳴らす
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}

					else if (cfgmc_cell_count == TRUE && g_commustatus == COMMU_STATUS_NORMAL && commu_mode_background == FALSE)
					{
						// テキストオフモードならそれを解除する
						if (commu_mode_text_off == TRUE) { commu_mode_text_off = FALSE; }
						// 文が描画されきっていなければ全て描画し、既にされているなら次の行へ行く
						#pragma region ver0.0028制作時コメント化コード
//GameMainCommunicationNextLine();
//if (EndFlag == 0){ GameMainCommunicationMoji(TRUE); }
#pragma endregion
						else if (EndFlag == 0) { GameMainCommunicationMoji(TRUE); }
						else { GameMainCommunicationNextLine(); }
					}
				}
				// バックログ表示時
				else
				{
					if (image_icon_log_back.JudgementReleaseCheck() == TRUE) 
					{
						TextLog::SetMode(FALSE); 
						// ＳＥを鳴らす
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}
					else if (image_icon_text_log[0].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(1); }
					else if (image_icon_text_log[1].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(TextLog::GetPage() - 1); }
					else if (image_icon_text_log[2].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(TextLog::GetPage() + 1); }
					else if (image_icon_text_log[3].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(TextLog::GetNIID() / TextLog::GetPagesLineNumber() + 1); }


					// shiftキーが押されていれば端まで移動
					//BOOL x = (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT)) ? TRUE : FALSE;
					//if (KeyTrigger::Trigger(key, KeyTrigger::Type::LEFT) == TRUE) { TextLog::SetPage(x == FALSE ? TextLog::GetPage() - 1 : 1); }
					//else if (KeyTrigger::Trigger(key, KeyTrigger::Type::RIGHT) == TRUE) { TextLog::SetPage(x == FALSE ? TextLog::GetPage() + 1 : TextLog::GetNIID() / TextLog::GetPagesLineNumber() + 1); }
				}
				// 全てのフラグを戻す
				cfgmc_move_title = FALSE;												// タイトル画面へ移動
				#pragma region ver0.007制作時コメント化コード
				//for (int i = 0; i < 3; i++){ cfgmc_altenative[i] = FALSE; }	// 選択肢を選択
#pragma endregion
				for (int i = 0; i < 3; i++) { hjimage_alternative[i].CJChange(FALSE); }	// 選択肢を選択
				cfgmc_cell_count = FALSE;				// コミュの情報を次のものにする
				cfgmc_change_auto = FALSE;				// オートモード切り替え
				cfgmc_change_skip = FALSE;				// スキップモード切り替え
				cfgmc_exit_save = FALSE;				// セーブモード移行
				cfgmc_exit_load = FALSE;				// ロードモード移行
				cfgmc_exit_option = FALSE;				// 設定モードへ移行
				cfgmc_change_menu = FALSE;				// メニューモード切り替え
				cfgmc_change_text_off = FALSE;			// テキストオフモード切り替え
				image_icon_log.CJChange(FALSE);			// テキストログ表示
				image_icon_log_back.CJChange(FALSE);	// バックログ用『BACK』
			}
		}
	}
}
//	オートモードがＯＮになる際の処理
void GameMainCommunicationAuto()
{
	// オートモードにし、専用のカウントを初期化する
	g_commuauto = COMMU_AUTO_ON;
	commu_auto_count;
}
// コミュモード時１フレーム毎に行われる処理
void GameMainCommunicationFlame()
{
	commu_bgm_flame++;	// ＢＧＭ名描画用経過フレーム数をカウントする
	// 『auto_se』モードならＳＥが鳴り終えたかチェックし、鳴り終わっているなら次の行に進む（１なら再生、-1ならエラー）
	#pragma region ver0.00607制作時コメント化コード
	//if (g_commustatus == COMMU_STATUS_SE && CheckSoundMem(g_sndhandles.SE[HM[commu_number][cell_number].se - 1]) == 0)
#pragma endregion
	if (g_commustatus == COMMU_STATUS_SE && CheckSoundMem(se[HM[commu_number][cell_number].se - 1].GetHandle()) == 0)
	{
		g_commustatus = COMMU_STATUS_NORMAL;
		GameMainCommunicationNextLine();
	}
	// 『COMMU_STATUS_AUTO』ならカウントダウンを行い、0になったら次の行に進む
	if (g_commustatus == COMMU_STATUS_AUTO)
	{
		// スキップモードなら、即座にカウントを0にするがスキップ本来の処理で次行にいかせるため次行に行く処理を飛ばす
		if (g_commuauto == COMMU_AUTO_SKIP) { commu_frame_auto_count = 0; }
		else { commu_frame_auto_count--; }
		if (commu_frame_auto_count == 0)
		{
			g_commustatus = COMMU_STATUS_NORMAL;
			//if(g_commuauto != COMMU_AUTO_SKIP){ GameMainCommunicationNextLine(); }			
			if (g_commuauto != COMMU_AUTO_SKIP && commu_number >= 0) { GameMainCommunicationNextLine(); }
		}
	}
	// 出現しているキャラに、瞬きに関する処理を行う
	#pragma region ver0.00294制作時コメント化コード
//	if (commu_character[1] > 0)
//	{
//		#pragma region ver0.00291制作時コメント化コード
//		// 瞬きをし終えている状態なら残り時間を再セットする
//		//if (commu_character_blink_limit[1]-- <= 0){ commu_character_blink_limit[1] = 180; }
//#pragma endregion
//		// 瞬きをし終えている状態なら残り時間を再セットする
//		commu_character_blink_limit[1]-- ;
//		if (g_commu_character_face[1] == CCF_CLOSE_EYE || g_commu_character_face[1] == CCF_CLOSE_EYE_SMILE)
//		{
//			if (commu_character_blink_limit[1] > COMMU_EYE_ANIMATION_FLAME * 3) { commu_character_blink_limit[1] = COMMU_EYE_ANIMATION_FLAME * 3; }
//			else if (commu_character_blink_limit[1] < COMMU_EYE_ANIMATION_FLAME + 1) { commu_character_blink_limit[1] = COMMU_EYE_ANIMATION_FLAME + 1; }
//		}
//		else if(commu_character_blink_limit[1] <= 0){ commu_character_blink_limit[1] = 180; }
//	}
#pragma endregion
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		if (commu_character[i] > 0)
		{
			// 瞬きをし終えている状態なら残り時間を再セットする
			commu_character_blink_limit[i]--;
			if (g_commu_character_face[i] == CCF_CLOSE_EYE || g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE)
			{
				if (commu_character_blink_limit[i] > COMMU_EYE_ANIMATION_FLAME * 3) { commu_character_blink_limit[i] = COMMU_EYE_ANIMATION_FLAME * 3; }
				else if (commu_character_blink_limit[i] < COMMU_EYE_ANIMATION_FLAME + 1) { commu_character_blink_limit[i] = COMMU_EYE_ANIMATION_FLAME + 1; }
			}
			else if (commu_character_blink_limit[i] <= 0) { commu_character_blink_limit[i] = 180; }
		}
	}
	// 設定に応じて、台詞を描画する際に必要なポイントを加算する
	#pragma region ver0.0021制作時コメント化コード
	//if (g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW){ commu_message_point += COMMU_COUNT_SLOW; }
#pragma endregion
	if (g_commuauto == COMMU_AUTO_SKIP){ commu_message_point += COMMU_COUNT_FAST * 4; }
	else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW){ commu_message_point += COMMU_COUNT_SLOW; }
	else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL){ commu_message_point += COMMU_COUNT_NORMAL; }
	else{ commu_message_point += COMMU_COUNT_FAST; }
	// 台詞主と描画されているキャラをチェックし（めぐるが１）しゃべりが終わってないなら口パクのカウント数を再セットする
	for (int i = 0; i < 3; i++)
	{
		if (commu_character_talk_limit[i] >= 1){ commu_character_talk_limit[i]--; }
	}
	for (int i = 0; i < 3; i++)
	{
		const char* x = "";
		#pragma region ver0.0029制作時コメント化コード
		//switch (commu_character[i] / 10 - 1)
#pragma endregion
		switch (commu_character[i] / 1000 - 1)
		{
		case 0: x = "めぐる";	break;
		case 1: x = "恋鐘";		break;
		case 2: x = "樹里";		break;
		case 3: x = "凛世";		break;
		case 4: x = "千雪";		break;
		case 5: x = "はづき";	break;
		case 6: x = "校長";		break;
		default:				break;
		}

		// 開きっぱなし
		if (HM[commu_number][cell_number].line_mouse == 2)
		{
			if (commu_character_talk_limit[i] < COMMU_MOUSE_ANIMATION_FLAME){ commu_character_talk_limit[i] = COMMU_MOUSE_ANIMATION_FLAME * 4 - 1; }
			else if (commu_character_talk_limit[i] == COMMU_MOUSE_ANIMATION_FLAME * 2){ commu_character_talk_limit[i]++; }
		}
		// 【描画されているキャラクターと台詞主が一致している、台詞口パクタイプが『閉じる、開きっぱなし』以外である】事が共通条件
		#pragma region ver0.0029制作時コメント化コード
		//else if (commu_character[i] / 10 == 1 && strcmp(HM[commu_number][cell_number].name, "めぐる") == 0 && HM[commu_number][cell_number].line_mouse != -1)
#pragma endregion
		#pragma region ver0.00605制作時コメント化コード
		//else if (/*commu_character[i] / 10 == 1 &&*/ strcmp(HM[commu_number][cell_number].name, x) == 0 && HM[commu_number][cell_number].line_mouse != -1)
#pragma endregion
		else if ((strcmp(HM[commu_number][cell_number].name, x) == 0 && HM[commu_number][cell_number].line_mouse != -1) || HM[commu_number][cell_number].line_mouse == 3)
		{
			if (EndFlag == 0)
			{
				// 口パク
				if ((HM[commu_number][cell_number].line_mouse == 0 || HM[commu_number][cell_number].line_mouse == 3)&& commu_character_talk_limit[i] <= 0){ commu_character_talk_limit[i] = COMMU_MOUSE_ANIMATION_NUMBER * COMMU_MOUSE_ANIMATION_FLAME - 1; }
				// 台詞終了まで開く
				else if (HM[commu_number][cell_number].line_mouse == 1)
				{ 
					if (commu_character_talk_limit[i] < COMMU_MOUSE_ANIMATION_FLAME){ commu_character_talk_limit[i] = COMMU_MOUSE_ANIMATION_FLAME * 4 - 1; }
					else if(commu_character_talk_limit[i] == COMMU_MOUSE_ANIMATION_FLAME * 2){ commu_character_talk_limit[i]++; }
				}
			}
		}
	}
	// キャラクター変更に関わる変数のカウントを減らし、0になったら次の行へ進む
	#pragma region ver0.00294制作時コメント化コード
	//if (commu_character_visibility_count > 0)
	//{
	//	commu_character_visibility_count--;
	//	if (commu_character_visibility_count <= 0)
	//	{
	//		commu_mode_background = FALSE;
	//		GameMainCommunicationNextLine();
	//	}
	//}
#pragma endregion
	BOOL flag_x = FALSE;	// 複数のキャラを変える場合、跳ぶ行数が２以上になってしまうため、フラグ制にしている
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		if (commu_character_visibility_count[i] > 0)
		{
			commu_character_visibility_count[i]--;
			if (commu_character_visibility_count[i] <= 0) { flag_x = TRUE; }
		}
	}
	if (flag_x == TRUE)
	{
		commu_mode_background = FALSE;
		GameMainCommunicationNextLine();
	}
	// 背景変更に関わる変数のカウントを減らし、０になったら次の行へ進む
	if (commu_background_visibility_count > 0)
	{ 
		commu_background_visibility_count--; 
		//if (commu_background_visibility_count <= 0)
		if (commu_background_visibility_count <= 0 && commu_number >= 0)
		{
			commu_mode_background = FALSE;
			GameMainCommunicationNextLine();
		}
	}
	// コミュ自動タイプが通常ではなく、ＳＥオート再生or選択肢状態ではなく、キャラクター変更、背景変更が行われなく、文字が描画されきった状態ならカウントを進め、一定数になったら次行に行く
	if (g_commuauto != COMMU_AUTO_NORMAL && g_commustatus == COMMU_STATUS_NORMAL && commu_mode_background == FALSE && EndFlag == 1)
	{
		if (g_commuauto == COMMU_AUTO_ON)
		{
			commu_auto_count++;
			#pragma region ver0.021制作時コメント化コード
			//if (commu_auto_count > 40)
#pragma endregion
			if (commu_auto_count > 80)
			{
				commu_auto_count = 1;
				//GameMainCommunicationNextLine();

				if (commu_number >= 0) { GameMainCommunicationNextLine(); }
			}
		}
		// スキップモードならカウントなしで次行に行く
		//else { GameMainCommunicationNextLine(); }
		else if(commu_number >= 0){ GameMainCommunicationNextLine(); }
	}
	// 選択肢出現時、プレイ時間に応じて選択肢のX座標を変える（Y座標はそのままなので同じ値）
	// マップ移動矢印の座標を（再）定義する
	//float x = screen_size_x * 0.54f;
	//float y = bairitu * 705;														// 両矢印の中心からのずれ
	//float z = (22.5f - (progress_frame % 45)) * bairitu;
	//hjimage_map[0].CoordinateSetting(x - y - hjimage_map[0].size_x / 2 - abs(z), screen_size_y / 2.0f);
	//hjimage_map[1].CoordinateSetting(x + y - hjimage_map[1].size_x / 2 + abs(z), screen_size_y / 2.0f);
	// 選択肢x座標
	//float x = hjimage_alternative[0].size_x * bairitu / 2;																	// 画像の中心から左端のずれ
	float x = hjimage_alternative[0].size_x / 2;																	// 画像の中心から左端のずれ
	float y = bairitu * (150 + abs(22.5f - (progress_frame % 45)));																								// 選択肢y座標支点
	#pragma region ver0.00704制作時コメント化コード
//commu_altenative_y_under = y + bairitu * hjimage_alternative[0].size_y * 2 / 3;	//（ 倍率のえいきょうを２きうけてる？）下選択肢y座標
	//commu_altenative_y_under = y + hjimage_alternative[0].size_y * 2 / 3;	//（ 倍率のえいきょうを２きうけてる？）下選択肢y座標
	//commu_altenative_y_upper = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_y_under : y;					// 上側選択肢y座標（２択時、下側と同じy座標になる）
#pragma endregion
	AlternativeCoordinate::SetYUnder(y + hjimage_alternative[0].size_y * 2 / 3);
	AlternativeCoordinate::SetYUpper(g_altenativenumber == ALTENATIVE_NUMBER_2 ? AlternativeCoordinate::GetYUnder() : y);
	//float z = bairitu * (hjimage_alternative[0].size_x + 54);																		// ３択時、左、右選択肢中心x座標の、中央からのずれ
	float z = hjimage_alternative[0].size_x + bairitu * 54;																		// ３択時、左、右選択肢中心x座標の、中央からのずれ
	#pragma region ver0.00704制作時コメント化コード
	//hjimage_alternative[2].CoordinateSetting(screen_size_x / 2 - x + z, commu_altenative_y_under);
	//hjimage_alternative[1].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? hjimage_alternative[2].GetCoordinateX() : screen_size_x / 2 - x - z, commu_altenative_y_under);
	//hjimage_alternative[0].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? screen_size_x / 2 - x - z : screen_size_x / 2 - x, commu_altenative_y_upper);
#pragma endregion
	hjimage_alternative[2].CoordinateSetting(screen_size_x / 2 - x + z, AlternativeCoordinate::GetYUnder());
	hjimage_alternative[1].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? hjimage_alternative[2].GetCoordinateX() : screen_size_x / 2 - x - z, AlternativeCoordinate::GetYUnder());
	hjimage_alternative[0].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? screen_size_x / 2 - x - z : screen_size_x / 2 - x, AlternativeCoordinate::GetYUpper());
	// 選択肢文字列中心x座標
	float a = (float)(screen_size_x / 2);
	commu_altenative_string_center_x[0] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? a - z : (float)(screen_size_x / 2);
	commu_altenative_string_center_x[2] = a + z;
	commu_altenative_string_center_x[1] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_string_center_x[2] : a - z;

	//float x = (22.5f - (progress_frame % 45)) * bairitu;
	//for (int i = 0; i < ALTENATIVE_MAX_NUMBER; i++) { hjimage_alternative[i].CoordinateSetting(); }

	commu_play_time += 1.0f / 60;		// プレイ時間を60分の１秒カウントする
	// マップ説明コミュでスクリーンを上げ下げする
	if (commu_number == static_cast<int>(CommuType::TUTORIAL)) { ImgDataBGTutorial::ScreenYMove(); }
}
// コミュ状態で、次行の処理を行う
void GameMainCommunicationNextLine()
{
	cell_number++;
	// 次行セルコマンドが『move_sell』なら指定行に跳ぶ
	if (strcmp(HM[commu_number][cell_number].command, "move_sell") == 0)
	{
		// 行ジャンプ履歴を記憶する
		state::SetAlternativeMoveNumber(cell_number - 2, HM[commu_number][cell_number].GetCommandNumber());

		cell_number = HM[commu_number][cell_number].move_commu_number - 2;
	}	
	if (strcmp(HM[commu_number][cell_number].command, "auto_se") == 0){ g_commustatus = COMMU_STATUS_SE; }	// 次行セルコマンドが『auto_se』なら次行ＳＥ再生が終わるまで操作が自動になるフラグを立てる
	// 次行セルコマンドが『frame_auto』なら『指定フレーム数語次行に行く状態』にする
	else if (strcmp(HM[commu_number][cell_number].command, "frame_auto") == 0)
	{ 
		g_commustatus = COMMU_STATUS_AUTO; 
		commu_frame_auto_count = HM[commu_number][cell_number].move_commu_number;
	}
	// 次行セルコマンドが『end』ならコミュを終了させる
	#pragma region ver0.00706制作時コメント化コード
//	else if (strcmp(HM[commu_number][cell_number].command, "end") == 0)
//	{ 
//		// コミュセレクトによる閲覧の場合、コミュセレクト画面に戻る
//		#pragma region ver0.00396制作時コメント化コード
//		//GameMapNext();
//#pragma endregion
//		//commu_before_cs == FALSE ? GameMapNext() : GameCommuSelectNext();
//		if (commu_before_cs == FALSE)
//		{
//			switch (commu_number)
//			{
//			case COMMU_TYPE_OP:	GameMainCommunicationNext(COMMU_TYPE_TUTORIAL, FALSE, 0);	break;
//			case COMMU_TYPE_TUTORIAL:
//				GameMainCommunicationNext(COMMU_TYPE_TUTORIAL, FALSE, 0);
//				break;
//			case COMMU_TYPE_MEGURU0:
//				CommuData::SetGMapUpperType(CommuData::MapUpperType::RINZE0);
//			default:			GameMapNext();												break;
//			}			
//		}
//		else { GameCommuSelectNext(); }
//	}
#pragma endregion
	else if (strcmp(HM[commu_number][cell_number].command, "end") == 0)
	{ 
		GameMainCommunicationEnd();
		return;
	}
	// 次行セルコマンドが『move_commu』なら次列の番号に応じたコミュに移動する
	else if (strcmp(HM[commu_number][cell_number].command, "move_commu") == 0)
	{ 
		// コミュセレクトによる閲覧の場合、コミュセレクト画面に戻る
		#pragma region ver0.00607制作時コメント化コード
		//commu_before_cs == FALSE ? GameMainCommunicationNext(HM[commu_number][cell_number].move_commu_number, FALSE) : GameCommuSelectNext();
#pragma endregion
		commu_before_cs == FALSE ? GameMainCommunicationNext(HM[commu_number][cell_number].move_commu_number, FALSE, 0) : GameCommuSelectNext();
	}
	// 次行セルコマンドが『altenative』なら選択肢を選べる状態にする
	else if (strcmp(HM[commu_number][cell_number].command, "altenative_2") == 0 || strcmp(HM[commu_number][cell_number].command, "altenative_3") == 0)
	{ 
		g_commustatus = COMMU_STATUS_ALTENATIVE;
		g_altenativenumber = strcmp(HM[commu_number][cell_number].command, "altenative_2") == 0 ? ALTENATIVE_NUMBER_2 : ALTENATIVE_NUMBER_3;
		// 選択肢文字描画に必要な処理を行う
		for (int i = 0; i < g_altenativenumber + 2; i++)
		{
			commu_altenative_string_line[i] = 1;																	// 選択肢文字の行数を初期化する
			#pragma region ver0.00704制作時コメント化コード
			//for (int j = 0; j < STRBUF_ALTENATIVE_HEIGHT; j++) { sprintf_s(StringBufAltenative[i][j], 64, ""); }	// 文字列初期化
#pragma endregion
			// 文字列初期化
			for (int j = 0; j < STRBUF_ALTENATIVE_HEIGHT; j++)
			{
				// グローバル変数のchar文字を初期化する際はsprintf_sでなく0を代入する必要がある
				for (int k = 0; k < STRBUF_ALTENATIVE_WIDTH + 2; k++){StringBufAltenative[i][j][k] = 0;}
			}	
			GameMainCommunicationMojiAltenative(i);
		}
		// 選択肢数に応じて関係する座標を再定義する
		GameMainCommunicationCoordinateSetting();
	}
	// キャラ立ち絵変更チェック
	for (int i = 0; i < 3; i++)
	{
		#pragma region ver0.0072制作時コメント化コード
		//if (HM[commu_number][cell_number].character[i] != 0)
#pragma endregion
		if (HM[commu_number][cell_number].character[i] != 0)
		{
			// 特殊表情をリセットする
			g_commu_character_face[i] = CCF_NORMAL;

			#pragma region ver0.0021制作時コメント化コード
			// （キャラクター切り替え方法が不透明度入れ替えなら）直前（直後）のキャラクター画像を合成する
			//if (HM[commu_number][cell_number].character_change == 0)
#pragma endregion
			// （キャラクター切り替え方法が不透明度入れ替えで、スキップモードでなければ）直前（直後）のキャラクター画像を合成する
			#pragma region ver0.007制作時コメント化コード
			//if (HM[commu_number][cell_number].character_change == 0 && g_commuauto != COMMU_AUTO_SKIP)
#pragma endregion
			if (HM[commu_number][cell_number].character_change != CCC_INSTANT && g_commuauto != COMMU_AUTO_SKIP)
			{
				commu_character_talk_limit[i] = 0;	// 透明度入れ替えキャラ変更の際、口が開きっぱなしになるバグを直す処理
				#pragma region ver0.0029制作時コメント化コード
				//if (commu_character[i] >= 2)
				//{
				//	LoadGameImageCharacterBody(commu_character[i] % 10, &commu_character_before[i]);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][DrawGameMainCommunicationMouseAnimation()], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_eyebrow[commu_character[i] / 10 - 1][commu_character[i] % 10][0][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
				//else{ DeleteGraph(commu_character_before[i]); }
				//// 直後のキャラクター
				//if (HM[commu_number][cell_number].character[i] + 1 >= 2)
				//{
				//	int x = HM[commu_number][cell_number].character[i];
				//	LoadGameImageCharacterBody(x % 10, &commu_character_after[i]);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 10 - 1][x % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 10 - 1][x % 10][0][DrawGameMainCommunicationMouseAnimation()], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 10 - 1][x % 10][0][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
				//else{ DeleteGraph(commu_character_after[i]); }
#pragma endregion
				#pragma region ver0.00291制作時コメント化コード
				// （衣装はめぐるなら２恋鐘は４で仮実装）
				//if (commu_character[i] >= 2)	// 現在は問題ないが『2』でいいのかは不明
				//{
				//	LoadGameImageCharacterBody(commu_character[i] / 100 % 10, &commu_character_before[i], load_name[commu_character[i] / 1000 - 1], commu_character[i] / 10 % 10);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_eyebrow[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
				//else { DeleteGraph(commu_character_before[i]); }
				//// 直後のキャラクター（服装がその場しのぎの処理になっている可能性がある？）
				//if (HM[commu_number][cell_number].character[i] + 1 >= 2)
				//{
				//	int x = HM[commu_number][cell_number].character[i];
				//	LoadGameImageCharacterBody(x / 100 % 10, &commu_character_after[i], load_name[x / 1000 - 1], x / 10 % 10);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
#pragma endregion
				if (commu_character[i] >= 2)	// 現在は問題ないが『2』でいいのかは不明
				{
					LoadGameImageCharacterBody(commu_character[i] / 100 % 10, &commu_character_before[i], load_name[commu_character[i] / 1000 - 1], commu_character[i] / 10 % 10);
					GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
					//																																														commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2;
					GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);
					GraphBlend(commu_character_before[i], g_imghandles.character_eyebrow[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				}
				else { DeleteGraph(commu_character_before[i]); }
				// 直後のキャラクター（服装がその場しのぎの処理になっている可能性がある？）
				if (HM[commu_number][cell_number].character[i] + 1 >= 2)
				{
					int x = HM[commu_number][cell_number].character[i];
					LoadGameImageCharacterBody(x / 100 % 10, &commu_character_after[i], load_name[x / 1000 - 1], x / 10 % 10);
					#pragma region ver0.0039制作時コメント化コード
					//GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
#pragma endregion
					// 目
					int y = (commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2;
					if (HM[commu_number][cell_number].character_face_etc[i] == 1) { y = 0; }
					else if (HM[commu_number][cell_number].character_face_etc[i] == 2) { y = 3; }
					GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][y], 255, DX_GRAPH_BLEND_NORMAL);

					GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);

					// 眉毛（閉じ目or笑顔閉じ目なら0にする）
					#pragma region ver0.0039制作時コメント化コード
					//GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][2], 255, DX_GRAPH_BLEND_NORMAL);
#pragma endregion
					GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][HM[commu_number][cell_number].character_face_etc[i] >= 1 ? 0 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				}
				else { DeleteGraph(commu_character_after[i]); }
			}

			commu_character[i] = HM[commu_number][cell_number].character[i];
			#pragma region ver0.007制作時コメント化コード
			//if (HM[commu_number][cell_number].character_change == 0)
#pragma endregion
			if (HM[commu_number][cell_number].character_change != CCC_INSTANT)
			{
				//	透明度入れ替え用のフレーム数
				int x = (HM[commu_number][cell_number].GetCC() == CCC_TRANSPARENCY_NORMAL) ? COMMU_CHARACTER_CHANGE_MAX : COMMU_CHARACTER_CHANGE_MAX_FAST;

				commu_mode_background = TRUE;	// キャラクター入れ替え処理が終わるまで操作できないようにする
				// キャラ切り替えに必要なフレーム数をセットする（スキップモードなら残り１Ｆにする）
				#pragma region ver0.00294制作時コメント化コード
				//commu_character_visibility_count = g_commuauto != COMMU_AUTO_SKIP ? COMMU_CHARACTER_CHANGE_MAX + 1 : 1;
#pragma endregion
				#pragma region ver0.007制作時コメント化コード
				//commu_character_visibility_count[i] = g_commuauto != COMMU_AUTO_SKIP ? COMMU_CHARACTER_CHANGE_MAX + 1 : 1;
#pragma endregion
				commu_character_visibility_count[i] = g_commuauto != COMMU_AUTO_SKIP ? x + 1 : 1;
			}
		}
		// 特殊表情を確認・変更する（switch文ならエラーは起きない？）
		//if (HM[commu_number][cell_number].character_face_etc[i] != 0) { HM[commu_number][cell_number].character_face_etc[i] == -1 ? g_commu_character_face[i] = CCF_NORMAL : g_commu_character_face[i] = HM[commu_number][cell_number].character_face_etc[i]; }
		switch (HM[commu_number][cell_number].character_face_etc[i])
		{
		case -1:					g_commu_character_face[i] = CCF_NORMAL;				break;
		case CCF_CLOSE_EYE:			g_commu_character_face[i] = CCF_CLOSE_EYE;			break;
		case CCF_CLOSE_EYE_SMILE:	g_commu_character_face[i] = CCF_CLOSE_EYE_SMILE;	break;
		default:																		break;
		}
	}
	// キャラクター距離均一モード変更チェック
	if (HM[commu_number][cell_number].character_even_distance != 0){ commu_mode_distance = (HM[commu_number][cell_number].character_even_distance == 1 ? TRUE : FALSE); }
	// 背景変更チェック
	if (HM[commu_number][cell_number].background != 0)
	{
		if (cell_number != 0)
		{
			commu_mode_background = TRUE;											// 背景が変わりきるまで操作できないようにする
			commu_background_visibility_count = COMMU_BACKGROUND_FLAME_MAX + 1;		// 背景切り替えに必要なフレーム数をセットする
			commu_background_before = commu_background;								// 直前の背景を記憶する
			g_backgroundchange = HM[commu_number][cell_number].background_change;	// 背景変更タイプを代入する
		}
		if (cell_number == 75 - 2)
		{
			quit_game = TRUE;
			return;
		}
		if (HM[commu_number][cell_number].background == -1)
		{
			commu_background = 0;
			GlobalStaticSaveLoad::SetSamuneBackgroundID(0);	// セーブ時にサムネを問題なく保存できるようにする処理
		}
		else
		{ 
			// バグ回避用の変数
			int x = (HM[commu_number][cell_number].background - 1 >= 0 ? HM[commu_number][cell_number].background - 1 : 0);
			commu_background = bgimage[x].Handle; 

			GlobalStaticSaveLoad::SetSamuneBackgroundID(x + 1);	// セーブ時にサムネを問題なく保存できるようにする処理
		}
	}
	// ＢＧＭ変更チェック
	if (HM[commu_number][cell_number].bgm != 0)
	{
		// -1ならBGM停止
		if (HM[commu_number][cell_number].bgm == -1){ MusicPlay(HM[commu_number][cell_number].bgm - 1); }
		else
		{
			MusicPlay(HM[commu_number][cell_number].bgm - 1); // 数字に対応したBGMに変更する
			// ＢＧＭ名を表示するために必要な要素を代入する
			commu_bgm_name = bgm_name[HM[commu_number][cell_number].bgm - 1];
			commu_bgm_flame = -1;
		}
	}
	// ＳＥ再生チェック（SKIPモードなら再生しない）
	#pragma region ver0.00393制作時コメント化コード
	//if (HM[commu_number][cell_number].se != 0){ SEPlay(HM[commu_number][cell_number].se - 1); }
#pragma endregion
	#pragma region ver0.017制作時コメント化コード
	//if (HM[commu_number][cell_number].se != 0 && g_commuauto != COMMU_AUTO_SKIP) { SEPlay(HM[commu_number][cell_number].se - 1); }
#pragma endregion
	if (HM[commu_number][cell_number].se != 0 && (g_commuauto != COMMU_AUTO_SKIP || HM[commu_number][cell_number].se == -1)) { SEPlay(HM[commu_number][cell_number].se - 1); }

	sprintf_s(String[0], 256, "%sE", HM[commu_number][cell_number].line);	// 文字を代入
	/* （選択肢表示状態でなければ）台詞描画に関する要素を初期化する---------*/
	if (g_commustatus != COMMU_STATUS_ALTENATIVE)
	{
		// 仮想テキストバッファ
		for (moji_i = 0; moji_i < STRBUF_HEIGHT; moji_i++)
		{
			for (moji_j = 0; moji_j < STRBUF_WIDTH + 2; moji_j++)
			{
				StringBuf[moji_i][moji_j] = 0;
			}
		}
		//描画文字位置
		CursorY = 0;
		CursorX = 0;
		// 参照文字位置
		SP = 0;	// １行目の
		CP = 0;	// ０文字

		EndFlag = 0;	// 終了フラグ
	}
	/*----------------------------------------------------------------------*/
	// テキストログ
	text_log[TextLog::GetNIID()].Input();

	DebugLog(LogOutputType::CELL_CHARACTER);
}
// コミュ終了処理
void GameMainCommunicationEnd()
{
	// コミュセレクトによる閲覧の場合、コミュセレクト画面に戻る
	if (commu_before_cs == FALSE)
	{
		// 旧体験版の挙動
		if (GlobalStaticVariable::GetModeTrial() == FALSE)
		{
			switch (commu_number)
			{
			case static_cast<int>(CommuType::OP):	GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL), FALSE, 0);	break;
			case static_cast<int>(CommuType::TUTORIAL):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::MEGURU0);
				GameMapNext();
				// 体験版0.01のデータで３月４週のデータをロードした際不具合が起きないようにする処理も兼ねている
				if (game_week_number > GlobalStaticMap::GetWeekInitialValue()) { game_week_number--; }
				break;
			case static_cast<int>(CommuType::MEGURU0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::RINZE0);
				GameMapNext();
				game_week_number--;
				break;
			case static_cast<int>(CommuType::KOGANE0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::CHIYUKI0);
				GameMapNext();
				game_week_number--;
				break;
			case static_cast<int>(CommuType::JURI0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::DEFAULT);
				GameMapNext();
				break;
			case static_cast<int>(CommuType::RINZE0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::KOGANE0);
				GameMapNext();
				break;
			case static_cast<int>(CommuType::CHIYUKI0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::JURI0);
				GameMapNext();
				game_week_number--;
				break;
			case static_cast<int>(CommuType::FRIEND):			GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL_END), FALSE, 0);	break;
			case static_cast<int>(CommuType::TUTORIAL_END):
				g_gamestate = GAME_TUTORIAL_END;
				ImgDataTutorialEnd::CountReset();
				MusicPlay(-2);
				break;
			default:
				#pragma region ver0.00904制作時コメント化コード
				//if (game_week_number == 17) { GameMainCommunicationNext(COMMU_TYPE_FRIEND, FALSE, 0); }
#pragma endregion
				if (game_week_number == 17)
				{
					// コミュを視聴したタイミングが５月２週ならめぐるフレンドＣＧコミュだけ選択できる
					CommuData::SetGMapUpperType(CommuData::MapUpperType::FRIEND_CG_MEGURU);
					GameMapNext();
					game_week_number--;
				}
				else { GameMapNext(); }
				break;
			}
		}
		// 体験版の挙動
		else
		{
			game_week_number--;	// スチル体験版ではカレンダー機能は必要ない
			// 特定のコミュを閲覧し終えたら閲覧フラグを立てる
			switch (commu_number)
			{
			case static_cast<int>(CommuType::MEGURU5):			GlobalStaticMap::SetTrialCommuViewed(0, TRUE);	break;
			case static_cast<int>(CommuType::KOGANE_STILL):		GlobalStaticMap::SetTrialCommuViewed(1, TRUE);	break;
			case static_cast<int>(CommuType::JURI_STILL):		GlobalStaticMap::SetTrialCommuViewed(2, TRUE);	break;
			case static_cast<int>(CommuType::RINZE0):			GlobalStaticMap::SetTrialCommuViewed(3, TRUE);	break;
			case static_cast<int>(CommuType::CHIYUKI_STILL):	GlobalStaticMap::SetTrialCommuViewed(4, TRUE);	break;
			default:																							break;
			}

			BOOL x = TRUE;
			for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++)
			{
				if (GlobalStaticMap::GetTrialCommuViewed(i) == FALSE) { x = FALSE; }
			}
			if(x == FALSE){ GameMapNext(); }
			// スチル体験版終了コミュを閲覧し終えたら体験版を終了する
			else if (commu_number == static_cast<int>(CommuType::TUTORIAL_STILL_END))
			{
				g_gamestate = GAME_TUTORIAL_END;
				ImgDataTutorialEnd::CountReset();
				MusicPlay(-2);
			}
			// 全ての特定コミュを閲覧し終えたらスチル体験版終了コミュを開始する
			else{ GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL_STILL_END), FALSE, 0); }
		}
	}
	else { GameCommuSelectNext(); }

	SEPlay(-2);	//ＳＥを停止する
}
// 選択肢を選んだ際の共通処理
void GameMainCommunicationAltenative(int x)	// 選択肢ＩＤ
{
	int y = HM[commu_number][cell_number].altenative_jump[x] - 3;
	state::SetAlternativeMoveNumber(cell_number, y + 1);	// セーブデータ用数値に数値を保存する
	cell_number = y;
	g_commustatus = COMMU_STATUS_NORMAL;
	SEPlay(static_cast<int>(SEData::IDName::SENTAKUSHI));
	GameMainCommunicationNextLine();
}
// コミュ画面で使う選択肢関係（andアイコン）の座標を（再）定義する処理
void GameMainCommunicationCoordinateSetting()
{
	#pragma region ver0.007制作時コメント化コード

	//float x = size_commu_altenative.x * bairitu / 2;																		// 画像の中心から左端のずれ
	//float y = bairitu * 150;																								// 選択肢y座標支点
	//commu_altenative_y_under = y + bairitu * size_commu_altenative.y * 2 / 3;												// 下選択肢y座標
	//commu_altenative_y_upper = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_y_under : y;					// 上側選択肢y座標（２択時、下側と同じy座標になる）
	//float z = bairitu * (size_commu_altenative.x + 54);																		// ３択時、左、右選択肢中心x座標の、中央からのずれ
	//commu_altenative_x[2] = screen_size_x / 2 - x + z;																		// 選択肢３x座標
	//commu_altenative_x[1] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_x[2] : screen_size_x / 2 - x - z;	// 選択肢２x座標
	//commu_altenative_x[0] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? screen_size_x / 2 - x - z : screen_size_x / 2 - x;	// 選択肢１x座標
	//// 選択肢文字列中心x座標
	//float a = (float)(screen_size_x / 2);
	//commu_altenative_string_center_x[0] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? a - z : (float)(screen_size_x / 2);
	//commu_altenative_string_center_x[2] = a + z;
	//commu_altenative_string_center_x[1] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_string_center_x[2] : a - z;
#pragma endregion
	// 『auto』アイコン（座標は仮）
	commu_coordinate_icon_auto_x = screen_size_x - bairitu * 48 - size_icon_auto.x;
	commu_coordinate_icon_auto_y = screen_size_y - bairitu * 375 - size_icon_auto.y;
	// 『SKIP』アイコン（座標は仮）
	#pragma region ver0.0028制作時コメント化コード
	//commu_coordinate_icon_skip_y = screen_size_y - bairitu * 240 + size_icon_auto.y / 2;
#pragma endregion
	commu_coordinate_icon_skip_y = commu_coordinate_icon_auto_y + size_icon_auto.y * 1.5f;
	// 『SAVE』アイコン（座標は仮）
	commu_coordinate_icon_save_y = commu_coordinate_icon_skip_y + size_icon_auto.y * 1.5f;
	// 『LOAD』アイコン（座標は仮）
	commu_coordinate_icon_load_y = commu_coordinate_icon_save_y + size_icon_auto.y * 1.5f;
	// 『OPTION』アイコン（座標は仮）
	commu_coordinate_icon_option_y = commu_coordinate_icon_load_y + size_icon_auto.y * 1.5f;
	// 『MENU』アイコン
	commu_coordinate_icon_menu_y = screen_size_y - bairitu * 48 - size_icon_auto.y;
	// 『TEXT OFF』アイコン
	commu_coordinate_icon_tf_x = bairitu * 15;
	// テキスト用ログ（現在の製品版ならクリックできない位置に置く）
	//if(mode_debug == TRUE){image_icon_log.CoordinateSetting(commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y - size_icon_auto.y * 1.5f);}
	//else{ image_icon_log.CoordinateSetting2(-2048, -2048);}
	image_icon_log.CoordinateSetting(commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y - size_icon_auto.y * 1.5f);	// バックログ用『BACK』
	image_icon_log_back.CoordinateSetting2(1825, 957);
	// バックログ用矢印
	for (int i = 0; i < ImgDataHJ2::TEXT_LOG_ARROW_NUMBER; i++)
	{
		int x = i - 2 + (i < 2 ? 0 : 1);
		image_icon_text_log[i].CoordinateSetting2(WINDOW_SIZE_X / 2 + image_icon_text_log[0].GetSizeX() * 2 * x - image_icon_text_log[0].GetSizeX() / 2, 945);
	}
	// バックログ用テキストウィンドウ（同じ画像を複数回使う可能性があるのでX座標だけでいい）
	float tl_ui_x = 27;
	for (int i = 0; i < ImgData2::LOG_TEXT_WINDOW_NUMBER; i++){image_log_text_window[i].CoordinateSetting2(tl_ui_x, 0);}
	// テキストログ用キャラＵＩ
	for(int i = 0; i < ImgData2::IMC_NUMBER; i++){image_map_character[i].CoordinateSetting2(tl_ui_x, 0);}
}
// コミュ画面で文字を描画するために行う処理
//void GameMainCommunicationMoji()
void GameMainCommunicationMoji(BOOL x)	// 瞬時に全ての文を表示させるフラグ
{
	/* 文字列描画用テストコード---------*/
	// サウンドノベル風文字列描画を行う
	// ただし終了フラグが１だった場合は処理をしない
	// （ログ表示中は処理を無視する）
	if (TextLog::GetMode() == FALSE)
	{
		do
		{
			if (EndFlag == 0)
			{
				char Moji = 0;

				// ボタン押し待ちフラグがたっていた場合はボタンが押されるまでここで終了
				if (KeyWaitFlag == 1)
				{
					if (ProcessMessage() == 0 && CheckHitKeyAll() != 0) { KeyWaitFlag = 0; }	// ボタンが押されていたら解除
				}
				else
				{
					// 文字の描画
					Moji = String[SP][CP];
					switch (Moji)
					{
					case '@':	// 改行文字
						// 改行処理および参照文字位置を一つすすめる
						Kaigyou2();
						CP++;
						break;
					case 'B':	// ボタン押し待ち文字
						// ボタンが離されるまで待つ
						while (ProcessMessage() == 0 && CheckHitKeyAll() != 0) {}
						// ボタン押し待ちフラグをたてる
						KeyWaitFlag = 1;
						CP++;
						break;
					case 'E':	// 終了文字
						// 終了フラグを立てるおよび参照文字位置を一つ進める
						EndFlag = 1;
						CP++;
						break;
					case 'C':	// クリア文字
						// 仮想テキストバッファを初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
						for (moji_i = 0; moji_i < STRBUF_HEIGHT; moji_i++)
						{
							for (moji_j = 0; moji_j < STRBUF_WIDTH + 2; moji_j++) { StringBuf[moji_i][moji_j] = 0; }
						}
						CursorY = 0;
						CursorX = 0;
						CP++;
						break;
					default:	// その他の文字
						// １文字のバイト数を取得
						Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &String[SP][CP]);
						// １文字テキストバッファに代入
						for (moji_i = 0; moji_i < Bytes; moji_i++) { StringBuf[CursorY][CursorX + moji_i] = String[SP][CP + moji_i]; }
						// 参照文字位置を１文字のバイト数分進める
						CP += Bytes;
						// カーソルを一文字のバイト数分進める
						CursorX += Bytes;
						// テキストバッファ横幅からはみ出たら改行する
#pragma region ver0.0034制作時コメント化コード
//if (CursorX >= STRBUF_WIDTH){ Kaigyou2(); }
#pragma endregion
						if (CursorX > STRBUF_WIDTH) { Kaigyou2(); }

						break;
					}
					// 参照文字列の終端まで行っていたら参照文字列を進める
					if (String[SP][CP] == '\0')
					{
						SP++;
						CP = 0;
					}
				}
			}
		} while (x == TRUE && EndFlag == 0);
	}
	/*----------------------------------*/
}
// コミュ画面で選択肢用文字を描画するために行う処理
void GameMainCommunicationMojiAltenative(int x)	// 指定された選択肢
{
	BOOL end = FALSE;
	// 参照する文字列番号と文字列中の文字ポインタ
	//int SP_A = 0;
	int CP_A = 0;
	// 仮想画面上での文字表示カーソルの位置
	int CursorX_A = 0;
	int CursorY_A = 0;

	int y = 0;			// 永久ループ回避用テスト変数
	do
	{
		char Moji;

		// 文字の描画
		Moji = HM[commu_number][cell_number].altenative_message[x][CP_A];
		switch (Moji)
		{
		case '@':	// 改行文字
			// 改行処理および参照文字位置を一つすすめる
			CursorY_A++;
			CursorX_A = 0;
			CP_A++;
			commu_altenative_string_line[x]++;	// 描画座標参照に使われる行数をカウントする
			break;
		//case 'E':	// 終了文字
		//	// 終了フラグを立てるおよび参照文字位置を一つ進める
		//	EndFlag = 1;
		//	CP++;
		//	break;
		default:	// その他の文字
			// １文字のバイト数を取得
			Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &HM[commu_number][cell_number].altenative_message[x][CP_A]);
			// １文字テキストバッファに代入
			for (moji_i = 0; moji_i < Bytes; moji_i++){ StringBufAltenative[x][CursorY_A][CursorX_A + moji_i] = HM[commu_number][cell_number].altenative_message[x][CP_A + moji_i]; }
			// 参照文字位置を１文字のバイト数分進める
			CP_A += Bytes;
			// カーソルを一文字のバイト数分進める
			CursorX_A += Bytes;
			// テキストバッファ横幅からはみ出たら改行する
			if (CursorX_A >= STRBUF_ALTENATIVE_WIDTH)
			{ 
				CursorY_A++;
				CursorX_A = 0;
			}
			break;
		}
		// 参照文字列の終端まで行っていたら参照文字列を進める
		if (HM[commu_number][cell_number].altenative_message[x][CP_A] == '\0'){ end = TRUE; }

		y++;
	} while (end == FALSE && y < 255);
}
// コミュ画面の描画処理
void DrawGameMainCommunication()
{
	/* 背景 ---------*/
	#pragma region ver0.0022制作時コメント化コード
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background, TRUE);
#pragma endregion
	// マップ説明時事務室（現在背景の瞬時入れ替え機能がないので手入力）
	#pragma region ver0.00904制作時コメント化コード
	//if (commu_number == COMMU_TYPE_TUTORIAL) 
#pragma endregion
	if (commu_number == static_cast<int>(CommuType::TUTORIAL))
	{
		int x = cell_number + 2;
		if (x == 28) { commu_background = bgimage[44].GetHandle(); }
		else if(x == 122){ commu_background = bgimage[43].GetHandle(); }
	}

	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, (g_backgroundchange != BACKGROUND_CHANGE_VISIBILITY && commu_background_visibility_count > COMMU_BACKGROUND_FLAME_MAX / 2) ? commu_background_before : commu_background, TRUE);

	ImgDataBGTutorial::DIMCheck(cell_number + 2);
	#pragma region ver0.00904制作時コメント化コード
	//if(commu_number == COMMU_TYPE_TUTORIAL)
#pragma endregion
	if (commu_number == static_cast<int>(CommuType::TUTORIAL))
	{
		int x = cell_number + 2;
		if (x <= 55 || x >= 62) { tutorial_image[0].DrawImageTutorial(ImgDataBGTutorial::GetScreenY()); }
		if (ImgDataBGTutorial::GetDrawImageNumber() > 0) { tutorial_image[ImgDataBGTutorial::GetDrawImageNumber()].DrawImageTutorial(ImgDataBGTutorial::GetScreenY()); }
	}
	/*---------------*/
	#pragma region ver0.0022制作時コメント化コード
	//if (g_backgroundchange == BACKGROUND_CHANGE_VISIBILITY)
	//{
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_background_visibility_count * 255 / COMMU_BACKGROUND_FLAME_MAX);
	//	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background_before, TRUE);
	//}
	//else
	//{
	//	int background_color = g_backgroundchange == BACKGROUND_CHANGE_BLACKOUT ? GetColor(0, 0, 0) : GetColor(255, 255, 255);
	//	if (commu_background_visibility_count > COMMU_BACKGROUND_FLAME_MAX / 2){ DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background_before, TRUE); }	// ブラック（ホワイト）アウトしきるまで直前の背景を映す
	//	int x = (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count) * (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count < 0 ? -1 : 1);
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_BACKGROUND_FLAME_MAX / 2 - x) * 255 / (COMMU_BACKGROUND_FLAME_MAX / 2));
	//	DrawBox(0, 0, screen_size_x, screen_size_y, background_color, TRUE);
	//}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#pragma endregion

	#pragma region ver0.0021制作時コメント化コード
	// 指定の変数が60以上になったら文字を書き出す
	//if (commu_message_point >= 60)
#pragma endregion
	// 指定の変数が60以上になっている限り文字を書き出す
	while (commu_message_point >= 60)
	{
		commu_message_point -= 60;
		GameMainCommunicationMoji(FALSE);
	}
	// キャラ立ち絵
	// キャラが２人＆キャラ間均等がオンか調べる
	BOOL same_distance_left = FALSE;	// 左側のキャラがもう決まってるか判別するフラグ
	int draw_character_now = 0;
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		if (commu_character[i] > 0){ draw_character_now++; }
	}

	#pragma region ver0.007制作時コメント化コード
	//for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
#pragma endregion
	for (int j = 0; j < COMMU_CHARACTER_MAX; j++)
	{
		// 真ん中のキャラを最前面に置くための変数
		int i = 0;
		if (j == 1) { i = 2; }
		else if (j == 2) { i = 1; }

		#pragma region ver0.00604制作時コメント化コード
		//float x = (i * 630 - 630.0f) * bairitu;	// キャラの配置場所によって変わるx座標
#pragma endregion
		float x = (i * COMMU_CHARACTER_SPACE - COMMU_CHARACTER_SPACE) * bairitu;	// キャラの配置場所によって変わるx座標
		// キャラが２人＆キャラ間均等がオンなら強制的に座標を変える
		if (draw_character_now == 2 && commu_mode_distance == TRUE)
		{ 
			x = (same_distance_left == FALSE ? -1 : 1) * 360.0f * bairitu;
			if (same_distance_left == FALSE){ same_distance_left = TRUE; }
		}	
		#pragma region ver0.0021制作時コメント化コード
		//if (commu_character_visibility_count >= 1)
#pragma endregion
		#pragma region ver0.00294制作時コメント化コード
		//if (commu_character_visibility_count >= 1 && g_commuauto != COMMU_AUTO_SKIP)	// スキップモードの場合、ラグ回避のため入れ替え用の画像を作成しないようにしているのでこの処理を飛ばす
		//{
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_character_visibility_count * 255 / COMMU_CHARACTER_CHANGE_MAX);
		//	DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_before[i], TRUE);
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_CHARACTER_CHANGE_MAX - commu_character_visibility_count) * 255 / COMMU_CHARACTER_CHANGE_MAX);
		//	DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_after[i], TRUE);
		//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//}
#pragma endregion
		if (commu_character_visibility_count[i] >= 1 && g_commuauto != COMMU_AUTO_SKIP)	// スキップモードの場合、ラグ回避のため入れ替え用の画像を作成しないようにしているのでこの処理を飛ばす
		{
			// 透明度入れ替え開始時のフレーム数
			int y = (HM[commu_number][cell_number].GetCC() == CCC_TRANSPARENCY_NORMAL) ? COMMU_CHARACTER_CHANGE_MAX : COMMU_CHARACTER_CHANGE_MAX_FAST;

			#pragma region ver0.007制作時コメント化コード
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_character_visibility_count[i] * 255 / COMMU_CHARACTER_CHANGE_MAX);
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_before[i], TRUE);
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_CHARACTER_CHANGE_MAX - commu_character_visibility_count[i]) * 255 / COMMU_CHARACTER_CHANGE_MAX);
#pragma endregion
			// 255に近いほど描画しようとしているものが濃く描画される
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_character_visibility_count[i] * 255 / y);
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_before[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (y - commu_character_visibility_count[i]) * 255 / y);
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_after[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (commu_character[i] >= 1)
		{
			#pragma region ver0.0029制作時コメント化コード
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_body[commu_character[i] / 10 - 1][commu_character[i] % 10][0], TRUE);
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);
			//// 眉毛（テスト）
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_eyebrow[commu_character[i] / 10 - 1][commu_character[i] % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);

			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][DrawGameMainCommunicationMouseAnimation()], TRUE);
#pragma endregion
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_body[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10], TRUE);
			#pragma region ver0.00291制作時コメント化コード
			////																																																							 まばたきをし終えるまでのフレーム数が1以上且つ、18（6×3）以下なら、										 残りフレーム数に5を足した数値を6で割った後、2で割った際の余りを返す、違っていれば2を返す（フレーム数19以上なら開きっぱなし）	
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);

#pragma endregion
			int y = (commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2;	// 目パーツに使う変数（まばたきをし終えるまでのフレーム数が1以上且つ、18（6×3）以下なら、残りフレーム数に5を足した数値を6で割った後、2で割った際の余りを返す、違っていれば2を返す（フレーム数19以上なら開きっぱなし））
			if (g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE && y == 0) { y = 3; }																																					// 特殊表情が『笑顔閉じ目』なら通常の閉じ目の時に差し替える
			for (int k = 0; k < 3; k++)
			{
				if(commu_character[k] < -1000 || commu_character[k] >= 10000)
				{
					quit_game = TRUE;
					return;
				}
			}
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][y], TRUE);

			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_eyebrow[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);	// 眉毛（テスト）
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][DrawGameMainCommunicationMouseAnimation(i)], TRUE);
		}
	}
	// コミュオプションアイコン
	//DrawExtendGraphF(screen_size_x - (45 * bairitu) - size_commu_option.x * bairitu, screen_size_y - 45 * bairitu - size_commu_option.y * bairitu, screen_size_x - 45 * bairitu, screen_size_y - bairitu * 45, g_imghandles.icon_commu_option, TRUE);	

	if (g_backgroundchange == BACKGROUND_CHANGE_VISIBILITY)
	{
		// 透明度入れ替え
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_background_visibility_count * 255 / COMMU_BACKGROUND_FLAME_MAX);
		DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background_before, TRUE);
	}
	else
	{
		// ブラックアウト、ホワイトアウト
		int background_color = g_backgroundchange == BACKGROUND_CHANGE_BLACKOUT ? GetColor(0, 0, 0) : GetColor(255, 255, 255);
		int x = (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count) * (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count < 0 ? -1 : 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_BACKGROUND_FLAME_MAX / 2 - x) * 255 / (COMMU_BACKGROUND_FLAME_MAX / 2));
		DrawBox(0, 0, screen_size_x, screen_size_y, background_color, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// コミュ選択肢
	if (g_commustatus == COMMU_STATUS_ALTENATIVE)
	{
		// 選択肢等のＵＩ以外のものを暗くする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		#pragma region ver0.007制作時コメント化コード
		//DrawExtendGraphF(commu_altenative_x[0], commu_altenative_y_upper, commu_altenative_x[0] + size_commu_altenative.x * bairitu, commu_altenative_y_upper + size_commu_altenative.y * bairitu, g_imghandles.altenative[0], TRUE);
		//DrawExtendGraphF(commu_altenative_x[1], commu_altenative_y_under, commu_altenative_x[1] + size_commu_altenative.x * bairitu, commu_altenative_y_under + size_commu_altenative.y * bairitu, g_imghandles.altenative[1], TRUE);
		//if (g_altenativenumber == ALTENATIVE_NUMBER_3){ DrawExtendGraphF(commu_altenative_x[2], commu_altenative_y_under, commu_altenative_x[2] + size_commu_altenative.x * bairitu, commu_altenative_y_under + size_commu_altenative.y * bairitu, g_imghandles.altenative[2], TRUE); }
#pragma endregion		
		for (int i = 0; i < g_altenativenumber + 2; i++)
		{
			hjimage_alternative[i].DrawImage();
			// 選択肢文字列を１行毎に中央揃えした上で描画する
			#pragma region ver0.007制作時コメント化コード
//for (int j = 0; j < commu_altenative_string_line[i]; j++){ DrawFormatStringFToHandle(commu_altenative_string_center_x[i] - GetDrawFormatStringWidthToHandle(g_font3, StringBufAltenative[i][j]) / 2, (i == 0 ? commu_altenative_y_upper : commu_altenative_y_under) + bairitu * size_commu_altenative.y / 2 - bairitu * FONT_SIZE_ORIGINAL / 2 - (commu_altenative_string_line[i] - 1) * FONT_SIZE_ORIGINAL / 2 + j * FONT_SIZE_ORIGINAL, GetColor(0, 0, 0), g_font3, StringBufAltenative[i][j]); }
#pragma endregion
			#pragma region ver0.00704制作時コメント化コード
			//for (int j = 0; j < commu_altenative_string_line[i]; j++) { DrawFormatStringFToHandle(commu_altenative_string_center_x[i] - GetDrawFormatStringWidthToHandle(g_font_commu_line, StringBufAltenative[i][j]) / 2, (i == 0 ? commu_altenative_y_upper : commu_altenative_y_under) + bairitu * hjimage_alternative[0].size_y / 2 - bairitu * FONT_SIZE_ORIGINAL_COMMU_LINE / 2 - (commu_altenative_string_line[i] - 1) * FONT_SIZE_ORIGINAL_COMMU_LINE / 2 + j * FONT_SIZE_ORIGINAL_COMMU_LINE, GetColor(0, 0, 0), g_font_commu_line, StringBufAltenative[i][j]); }
#pragma endregion
			//																																																				基本Y座標、																			選択肢の中心に寄せる数値						フォントサイズ分ずらす数値																																						
			for (int j = 0; j < commu_altenative_string_line[i]; j++) { DrawFormatStringFToHandle(commu_altenative_string_center_x[i] - GetDrawFormatStringWidthToHandle(g_font_commu_line, StringBufAltenative[i][j]) / 2, (i == 0 ? AlternativeCoordinate::GetYUpper() : AlternativeCoordinate::GetYUnder()) + /*bairitu **/ hjimage_alternative[0].size_y / 2 - FONT_SIZE_ORIGINAL_COMMU_LINE / 2 * bairitu - (commu_altenative_string_line[i] - 1) * FONT_SIZE_ORIGINAL_COMMU_LINE / 2 * bairitu + j * FONT_SIZE_ORIGINAL_COMMU_LINE * bairitu, GetColor(0, 0, 0), g_font_commu_line, StringBufAltenative[i][j]); }
		}
	}
	if (commu_mode_text_off == FALSE && TextLog::GetMode() == FALSE)
	{
		#pragma region ver0.0042制作時コメント化コード
		// テキストウィンドウ（透明度テスト中）
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90 * 255 / 100);
		//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.text_window, TRUE);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#pragma endregion
		/* テキストウィンドウ ---------*/
		int x[2] = {0, 0};
		for (int i = 0; i < 2; i++)
		{
			char c[256] = "";	// 台詞主
			if (i == 0) { sprintf_s(c, 256, HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name); }
			else { sprintf_s(c, 256, HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2); }
			if (strcmp(c, "めぐる") == 0 || strcmp(c, "恋鐘") == 0 || strcmp(c, "樹里") == 0 || strcmp(c, "凛世") == 0 || strcmp(c, "千雪") == 0)
			{
				int y = 0;
				x[i] = 1; 
			}
			else if (strcmp(c, "主人公") == 0) { x[i] = 2; }
			else if (strcmp(c, "はづき") == 0) { x[i] = 3; }
			else if (strcmp(c, "校長") == 0) { x[i] = 4; }
			else if (strcmp(c, "") != 0) { x[i] = 5; }
		}
		// コマンドが『text_window_color』ならコマンド用の値に応じて強制的に色を変える
		if(strcmp(HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].GetCommand(), "text_window_color") == 0)
		{
			switch (HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].GetCommandNumber())
			{
			case 2:		DrawTextWindow(1);	break;
			case 3:		DrawTextWindow(2);	break;
			case 4:		DrawTextWindow(3);	break;
			default:	DrawTextWindow(0);	break;
			}			
		}
		else if (x[0] == 1 || x[1] == 1) { DrawTextWindow(2); }	// ヒロインの名前があればピンク
		else if (x[0] == 2 || x[1] == 2) { DrawTextWindow(1); }	// 主人公の名前があれば水色
		else if (x[0] == 3 || x[1] == 3) { DrawTextWindow(3); }	// はづきの名前があれば緑
		else if (x[0] == 4 || x[1] == 4) { DrawTextWindow(0); }	// 校長の名前がのあれば灰色
		else if (x[0] == 5 || x[1] == 5) { DrawTextWindow(3); }	// モブの名前がのあれば緑
		else { DrawTextWindow(1); }								// 名前がない地の文の時などは水色
		/*-----------------------------*/
		// 台詞主、台詞（選択肢出現時は１つ前の台詞になる）
		#pragma region ver0.0111制作時コメント化コード
		//DrawFormatStringFToHandle(bairitu * 270, bairitu * 726, GetColor(20, 20, 20), g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name);
		////DrawFormatStringFToHandle(bairitu * 270, bairitu * 726, GetColor(20, 20, 20), g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name);
		////if (HM[commu_number][cell_number].name2 != NULL){ DrawFormatStringFToHandle(bairitu * 240 + GetDrawFormatStringWidthToHandle(g_font3, HM[commu_number][cell_number].name), bairitu * 720, GetColor(0, 0, 0), g_font3, "・%s", HM[commu_number][cell_number].name2); }
		////if (HM[commu_number][cell_number].name2[0] != NULL){ DrawFormatStringFToHandle(bairitu * 240 + GetDrawFormatStringWidthToHandle(g_font3, HM[commu_number][cell_number].name), bairitu * 720, GetColor(0, 0, 0), g_font3, "・%s", HM[commu_number][cell_number].name2); }	// こういう感じでないとうまくいかない
		//if (HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2[0] != NULL){ DrawFormatStringFToHandle(bairitu * 270 + GetDrawFormatStringWidthToHandle(g_font_commu_name, "%s",HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name), bairitu * 726, GetColor(0, 0, 0), g_font_commu_name, "・%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2); }	// こういう感じでないとうまくいかない
#pragma endregion
		if (commu_number >= 0)
		{
			DrawFormatStringFToHandle(bairitu * 270, bairitu * 726, GetColor(20, 20, 20), g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name);
			// name2[0] = name2の1バイト目
			if (HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2[0] != NULL) { DrawFormatStringFToHandle(bairitu * 270 + GetDrawFormatStringWidthToHandle(g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name), bairitu * 726, GetColor(0, 0, 0), g_font_commu_name, "・%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2); }	// こういう感じでないとうまくいかない
		}
		// テキストバッファの描画
		for (moji_i = 0; moji_i < STRBUF_HEIGHT; moji_i++)
		{ 
			// 文字の影
			//DrawFormatStringFToHandle(bairitu * (255 + 1.5f), moji_i * bairitu * FONT_SIZE_ORIGINAL_COMMU_LINE * 1.5f + bairitu * (840 + 1.5f), GetColor(40, 40, 40), g_font_commu_line, StringBuf[moji_i]);
			// 文字
			DrawFormatStringFToHandle(bairitu * 255, moji_i * bairitu * FONT_SIZE_ORIGINAL_COMMU_LINE * 1.5f + bairitu * 840, GetColor(20, 20, 20), g_font_commu_line, StringBuf[moji_i]); 
		}
	}
	// 透かしＵＩ
	else if(commu_mode_text_off == TRUE)
	{
		#pragma region ver0.0072制作時コメント化コード
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		//bgimage_sukashi.DrawImage();
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#pragma endregion
		bgimage_sukashi.DrawImage();
	}
	// ＢＧＭ名（非描画状態）
	float bgm_y = (commu_bgm_flame >= 20 && commu_bgm_flame < 160) ? 0 : commu_bgm_flame - 90.0f;
	if (bgm_y >= 1){ bgm_y *= -1; }
	if (bgm_y <= -1){ bgm_y += 70; }
	//if (commu_bgm_name != NULL){ DrawFormatStringFToHandle(0, bgm_y * (FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y) / 20, GetColor(255, 255, 255), g_font3, commu_bgm_name); }
	// 入学前コミュ撮影時は非表示にするもの
	if ((debug_entrance_before == FALSE && commu_mode_text_off == FALSE) && (TextLog::GetMode() == FALSE))
	{
		// 右上の『TITLE』
		//DrawStringFToHandle(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, "TITLE", DrawTitleStringColor(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL), g_font3);

		if (commu_mode_menu == TRUE)
		{
			// 『LOG』アイコン
			image_icon_log.DrawImage();
			// 『auto』アイコン
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_auto_y + size_icon_auto.y, g_commuauto != COMMU_AUTO_ON ? g_imghandles.icon_auto[0] : g_imghandles.icon_auto[1], TRUE);
			// 『SKIP』アイコン
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_skip_y + size_icon_auto.y, g_commuauto != COMMU_AUTO_SKIP ? g_imghandles.icon_skip[0] : g_imghandles.icon_skip[1], TRUE);
			// 『SAVE』アイコン
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE);
			// 『LOAD』アイコン
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[0], TRUE);
			// 『OPTION』アイコン
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_option_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_option_y + size_icon_auto.y, image_icon_option.Handle, TRUE);
		}
		// 『MENU』アイコン（仮画像）
		DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_menu_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_menu_y + size_icon_auto.y, g_imghandles.icon_menu[commu_mode_menu], TRUE);
		// 『TEXT OFF』アイコン
		DrawExtendGraphF(commu_coordinate_icon_tf_x, commu_coordinate_icon_menu_y, commu_coordinate_icon_tf_x + size_icon_text_off.x, commu_coordinate_icon_menu_y + size_icon_text_off.y, g_imghandles.icon_text_off, TRUE);
	}
	// テキストログ
	if (TextLog::GetMode() == TRUE) { TextLog::Draw(); }
}
// テキストウィンドウを描画する
void DrawTextWindow(int x)	// ウィンドウの色
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (100 - text_window_clear_percentage) * 255 / 100);
	#pragma region ver0.00605制作時コメント化コード
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[0][0].Handle, TRUE);
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[1][0].Handle, TRUE);
#pragma endregion
	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[0][x].Handle, TRUE);
	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[1][x].Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
// 描画する口パクの画像を判別する
int DrawGameMainCommunicationMouseAnimation(int i)	// 喋るキャラクターの位置
{
	int x = 3;
	switch (commu_character_talk_limit[i] / COMMU_MOUSE_ANIMATION_FLAME % COMMU_MOUSE_ANIMATION_NUMBER)
	{
	case 0: x = 3;															break;
	case 1: x = 4;															break;
	case 2: x = 5;															break;
	case 3: x = 4;															break;
	case 4: x = 5;															break;
	case 5: x = 4;															break;
	case 6: x = 3;	if (EndFlag == 1){ commu_character_talk_limit[i] = 0; }	break;	// 既に台詞が終わっている場合は口を開かないようにする
	case 7: x = 5;															break;
	case 8: x = 4;															break;
	case 9: x = 5;															break;
	case 10: x = 4;															break;
	case 11: x = 5;															break;
	case 12: x = 4;															break;
	default:																break;
	}

	#pragma region ver0.00291制作時コメント化コード
	//return x;
#pragma endregion
	return x + CHARACTER_GRAPH_EYE_NUMBER - 3;
}

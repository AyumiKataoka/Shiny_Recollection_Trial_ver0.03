#include "gametitle.h"
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cft=click_flag_title）
// なぜかsaveloadファイルのコードに使われていたのでそのまま
BOOL cft_exit_main_commu = FALSE;		// コミュ画面に移動
BOOL cft_quit_game = FALSE;				// ゲームを終了
BOOL cft_sound_room_main_commu = FALSE;	// サウンドルーム画面に移動
BOOL cft_commu_list = FALSE;				// コミュリスト画面に移動
//BOOL cft_commu_edit = FALSE;			// コミュエディット画面に移動

BOOL flag_next_start = FALSE;	// ニューゲーム開始時の移動処理フラグ

int next_start_frame_count = -1;	// 『START』選択からの経過フレーム数

float coordinat_title_choice_left = 0;		// 左側選択肢始点x座標
float coordinat_title_choice_right = 0;		// 右側選択肢始点x座標
float coordinat_title_choice_load_y = 0;	// 選択肢『LOAD』y座標
float coordinat_title_choice_config_y = 0;	// 選択肢『CONFIG』y座標
float coordinat_title_choice_exit_y = 0;	// 選択肢『EXIT』y座標

// タイトル画面状態以降処理
void GameTitleNext()
{
	g_gamestate = GAME_TITLE;
	if (ImgDataHJTitle::GetCountFrame() > 0) { MusicPlay(BN_TITLE); }	// タイトルＢＧＭを再生する
	SEPlay(-2);															// ループ効果音を停止する
	flag_next_start = FALSE;											// ニューゲーム選択時フラグをリセットする
	next_start_frame_count = -1;										// 『START』選択からの経過フレーム数をリセットする
}
// GameTitle状態のメイン処理
void GameTitle()
{
	GameTitleControl();
	GameTitleFlame();
	DrawGameTitle();
}
// タイトル画面操作処理
void GameTitleControl()
{
	// マウスのボタンが押されたり離されたりしたかどうかの情報を取得する
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0 && flag_next_start == FALSE)
	{
		// 左ボタンが押されていたら
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::START)][0].JudgementClickCheck() == TRUE) {}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::EXIT)][0].JudgementClickCheck() == TRUE && mode_debug == TRUE) {}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::LOAD)][0].JudgementClickCheck() == TRUE && mode_debug == TRUE) {}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::OPTION)][0].JudgementClickCheck() == TRUE && mode_debug == TRUE) {}
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, (float)GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3), FONT_SIZE_ORIGINAL * bairitu, TRUE, FALSE) == TRUE) { cft_sound_room_main_commu = TRUE; }
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_load_y, size_icon_commu_list.x, size_icon_commu_list.y, TRUE, FALSE) == TRUE) { cft_commu_list = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_config_y, size_icon_commu_list.x, size_icon_commu_list.y, TRUE, FALSE) == TRUE) { cft_commu_edit = TRUE; }	// 画像幅がコミュリストのものを使っている
				else if (hjimage_title.JudgementClickCheck() == TRUE) {}	// 画像幅がコミュリストのものを使っている
				else { ImgDataHJTitle::SetFlagCount(TRUE); }
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数

				// コミュ画面へ移動
				if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::START)][0].JudgementReleaseCheck() == TRUE)
				{
					flag_next_start = TRUE;															// ニューゲーム処理状態のフラグを立てる
					SEPlay(static_cast<int>(SEData::IDName::START));
					MusicPlay(-1);																	// ＢＧＭ停止タイミングテスト
					for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++) { commu_look_count[i] = 0; }	// キャラ別コミュ閲覧回数をリセットする
					CommuData::SetGMapUpperType(CommuData::MapUpperType::DEFAULT);	//	特定コミュ表示タイミング初期化
					// カレンダー初期化
					game_week_number = GlobalStaticMap::GetWeekInitialValue();
				}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::EXIT)][0].JudgementReleaseCheck() == TRUE) { quit_game = TRUE; }
				// ロード画面へ移動
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::LOAD)][0].JudgementReleaseCheck() == TRUE)
				{
					GameSaveLoadNext(FALSE, SL_BEFORE_TITLE);
					SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));
				}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::OPTION)][0].JudgementReleaseCheck() == TRUE)
				{
					GameConfigNext(FALSE);
					SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));
				}
				// サウンドルームへ移動
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, (float)GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3), FONT_SIZE_ORIGINAL * bairitu, FALSE, cft_sound_room_main_commu) == TRUE && mode_debug == TRUE){ g_gamestate = GAME_SOUNDROOM; }
				// コミュリストへ移動
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_load_y, size_icon_commu_list.x, size_icon_commu_list.y, FALSE, cft_commu_list) == TRUE && mode_debug == TRUE)
				{ 
					GameCommuSelectNext();
					// 立ち絵読み込み
					for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { image_character[i][0][0].SetLoadFlag(1); }
					CharacterImage::Load();
				}
				// コミュエディットモードへ移動
				//else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_config_y, size_icon_commu_list.x, size_icon_commu_list.y, FALSE, cft_commu_edit) == TRUE) { g_gamestate = GAME_COMMU_EDIT; }	// 画像幅がコミュリストのものを使っている
				else if (hjimage_title.JudgementReleaseCheck() == TRUE && mode_debug == TRUE)	// 画像幅がコミュリストのものを使っている
				{ 
					g_gamestate = GAME_COMMU_EDIT; 
					MusicPlay(-1);	// ＢＧＭ停止
					// 立ち絵を読み込む
					CharacterImage::SetFlagAll(TRUE);
					CharacterImage::Load();
					// ＢＧＭを読み込む
					BGMData::SetLoadAll(TRUE);
					BGMData::Load();
				}
				else if (ImgDataHJTitle::GetFlagCount() == TRUE)
				{
					if(ImgDataHJTitle::GetCountFrame() < 9999){ImgDataHJTitle::SetCountFrame(9999);}
					SEPlay(-2);	// ループ効果音を停止する
				}
				// 全てのフラグを戻す
				cft_commu_list = FALSE;					// コミュリスト画面に移動する
				//cft_commu_edit = FALSE;			// コミュエディット画面に移動
				ImgDataHJTitle::SetFlagCount(FALSE);	// タイトル画面経過フレーム数を即最大にする
				// 各選択肢
				for (int i = 0; i < ImgDataHJTitle::GetMenuNumber(); i++) { image_title_menu[i][0].CJChange(FALSE); }
					
				hjimage_title.CJChange(FALSE);	// コミュエディット画面に移動
			}
		}
	}
	/* マウスホイール関係 ---------*/
	//if (MouseX >= MAIN_MENU_X && MouseX < WINDOW_SIZE_X - MAIN_BUILDING_SIZE_X - DIVIDE_X)
	//{
	//	draw_status_plus_y += GetMouseWheelRotVol() * 15;
	//	if (draw_status_plus_y > 0){ draw_status_plus_y = 0; }
	//}
	//// 右画面
	//else if (MouseX >= WINDOW_SIZE_X - MAIN_BUILDING_SIZE_X && draw_window_right_length > WINDOW_SIZE_Y)
	//{
	//	draw_wr_plus_y += GetMouseWheelRotVol() * 15;
	//	if (draw_wr_plus_y > 0){ draw_wr_plus_y = 0; }
	//	else if (draw_wr_plus_y < WINDOW_SIZE_Y - draw_window_right_length){ draw_wr_plus_y = WINDOW_SIZE_Y - draw_window_right_length; }
	//}
	/* エディットモードキャラ別読み込みフラグ切り替え ---------*/
	if (mode_debug == TRUE)
	{
		if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
		{
			for (int i = 0; i < CharacterImage::GetCharacterMember(); i++)
			{
				if (CheckHitKey(KEY_INPUT_1 + i) == TRUE){CharacterImage::SetLoadEdit(i, TRUE);}
			}
		}
		else if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE)
		{
			for (int i = 0; i < CharacterImage::GetCharacterMember(); i++)
			{
				if (CheckHitKey(KEY_INPUT_1 + i) == TRUE) { CharacterImage::SetLoadEdit(i, FALSE); }
			}
		}
	}
}
// タイトルモード時１フレーム毎に行われる処理
void GameTitleFlame()
{
	// ニューゲーム処理時ならカウントを行い、規定値以上になったらコミュモードにする
	if (flag_next_start == TRUE)
	{
		next_start_frame_count++;
		if (next_start_frame_count >= TITLE_MOVE_START_MAX_FLAME)
		{
			// 体験版のオンオフで最初のコミュ内容が変わる
			if (GlobalStaticVariable::GetModeTrial() == FALSE) { GameMainCommunicationNext(0, FALSE, 0); }
			else
			{
				GlobalStaticMap::TrialCommuViewedReset();
				GameMainCommunicationNext(static_cast<int>(CommuType::STILL_OP), FALSE, 0);
			}
			
			commu_play_time = 0;	// プレイ時間を初期化
		}
	}
}
// タイトル画面で使う様々な座標を（再）定義する
void GameTitleCoordinateSetting()
{
	coordinat_title_choice_left = bairitu * TITLE_MENU_MESSAGE_X;
	coordinat_title_choice_right = screen_size_x - TITLE_MENU_MESSAGE_X * bairitu - GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3);	// 右側選択肢始点x座標
	coordinat_title_choice_load_y = bairitu * (START_MESSEAGE_Y + TITLE_MENU_MESSAGE_SPACE_Y);												// 選択肢『LOAD』y座標
	coordinat_title_choice_config_y = coordinat_title_choice_load_y + bairitu * TITLE_MENU_MESSAGE_SPACE_Y;									// 選択肢『CONFIG』y座標
	coordinat_title_choice_exit_y = coordinat_title_choice_config_y + bairitu * TITLE_MENU_MESSAGE_SPACE_Y;									// 選択肢『EXIT』y座標
	hjimage_title.CoordinateSetting(screen_size_x - hjimage_title.GetSizeX(), coordinat_title_choice_load_y);											// 『『Commu Edit』』のx、y座標
	// タイトルロゴのX座標
	image_title_logo.CoordinateSetting(screen_size_x - image_title_logo.GetSizeX(), 0);	
}
// タイトル画面の描画処理
void DrawGameTitle()
{
	// 関連画像
	ImgDataHJTitle::DrawTitleImage();
	if (mode_debug == TRUE)
	{
		// サウンドテスト（デバッグ）
		DrawStringFToHandle(coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, "SOUNDROOM", DrawTitleStringColor(coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
		// コミュリスト（現在はデバッグ用途）
		DrawExtendGraphF(coordinat_title_choice_right, coordinat_title_choice_load_y, coordinat_title_choice_right + size_icon_commu_list.x, coordinat_title_choice_load_y + size_icon_commu_list.y, g_imghandles.commu_list, TRUE);
		// コミュエディット（デバッグ、右下座標をコミュリストのままにしているのでバグが起きるかもしれない）
		hjimage_title.DrawImage();
	}
	// ニューゲーム時の白背景
	if (flag_next_start == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, next_start_frame_count * 255 / TITLE_MOVE_START_MAX_FLAME);
		DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(255, 255, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
// タイトルメニューの文字色を返す
int DrawTitleStringColor(float x, float y, int breadth, float length)	// 始点x座標,始点y座標,横幅範囲,縦幅範囲
{
	int color = MouseX >= x && MouseX < x + breadth && MouseY >= y && MouseY < y + length ? GetColor(255, 255, 255) : GetColor(128, 128, 128);
	return color;
}

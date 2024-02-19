#include "gameconfig.h"

#pragma region ver0.0026制作時コメント化コード
//char* config_message_message_speed[3] = {"ゆっくり", "ふつう", "はやい"};	// 設定モードで描画される『文字スピード』選択の文字の種類
#pragma endregion
char* config_message_message_speed[3] = { (char*)"ゆっくり", (char*)"ふつう", (char*)"はやい" };	// 設定モードで描画される『文字スピード』選択の文字の種類

BOOL config_before_mc = FALSE;	// タイトルではなくメインコミュから設定モードに来たか
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfc=click_flag_config）
BOOL cfc_move_title = FALSE;// タイトル画面へ移動
#pragma region ver0.0042制作時コメント化コード
//BOOL cfc_window_mode_change = FALSE;	// ウィンドウ、フルスクリーンを切り替える
#pragma endregion
BOOL cfc_window_mode_change[2];			// ウィンドウ、フルスクリーンを切り替える
BOOL cfc_screen_change_720p = FALSE;	// ウィンドウ解像度を720pxにする
BOOL cfc_screen_change_1080p = FALSE;	// ウィンドウ解像度を1080pxにする
BOOL cfc_bgm_down = FALSE;				// ＢＧＭ音量を下げる
BOOL cfc_bgm_up = FALSE;				// ＢＧＭ音量を上げる
BOOL cfc_se_down = FALSE;				// ＳＥ音量を下げる
BOOL cfc_se_up = FALSE;					// ＳＥ音量を上げる
BOOL cfc_message_slow = FALSE;			// メッセージ速度を遅くする
BOOL cfc_message_fast = FALSE;			// メッセージ速度を速くする
BOOL cfc_dialog_change = FALSE;			// ダイアログボックス表示フラグを切り替え
BOOL cfc_text_window_clear[2];			// メッセージ透過度を増減

float config_retu2_x = 0;										// ２列目項目X座標
float config_coordinate_icon_back_x = 0;						// 『BACK』アイコン左端x座標
float config_coordinate_icon_back_y = 0;						// 『BACK』アイコン上端y座標
#pragma region ver0.0042制作時コメント化コード
//float config_coordinate_full_screen_switch_x = 0;				// フルスクリーン切り替えスイッチX座標
#pragma endregion
float config_coordinate_full_screen_switch_x[2];				// フルスクリーン切り替えスイッチX座標
float config_coordinate_full_screen_switch_y = 0;				// フルスクリーン切り替えスイッチY座標
float config_coordinate_screen_resolution_switch_y = 0;			// 画面解像度切り替えスイッチY座標
float config_coordinate_screen_resolution_switch_1920_x = 0;	// 画面解像度切り替えスイッチ（1920×1080）X座標
float config_bgm_message_y = 0;									// ＢＧＭ音量関係Y座標
float config_coordinate_arrow_down_x = 0;						// 左矢印左端X座標
float config_bgm_volume_up_x = 0;								// ＢＧＭ『→』文字X座標
float config_se_message_y = 0;									// ＳＥ音量関係Y座標
float config_message_speed_y = 0;								// コミュメッセージ速度関係Y座標
float config_text_window_clear_y = 0;							// テキストウィンドウ透過度関係Y座標
float config_coordinate_message_speed_x[3];						// メッセージ速度選択肢各左端x座標

// 設定モード移行処理
void GameConfigNext(BOOL x)	// メインコミュ画面から移行してきたか
{
	g_gamestate = GAME_CONFIG;
	config_before_mc = x;
}
// GAME_CONFIG状態のメイン処理
void GameConfig()
{
	GameConfigControl();
	DrawGameConfig();
}
// 設定画面時操作処理
void GameConfigControl()
{
	// マウスのボタンが押されたり離されたりしたかどうかの情報を取得する
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		#pragma region ver0.0042制作時コメント化コード
//		// 左ボタンが押されていたら
//		if ((Button & MOUSE_INPUT_LEFT) != 0)
//		{
//			if (LogType == MOUSE_INPUT_LOG_DOWN)
//			{
//				BOOL x = FALSE;	// 以降の処理から抜け出す変数
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_move_title = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_full_screen_switch_y, (float)GetDrawStringWidthToHandle("□", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_window_mode_change = TRUE; }
//				#pragma region ver0.0041制作時コメント化コード
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("□", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_screen_change_720p = TRUE; }
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("□", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_screen_change_1080p = TRUE; }
//#pragma endregion
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_bgm_down = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_bgm_up = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_se_message_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_se_down = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_se_up = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_message_slow = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_message_fast = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, TRUE, FALSE) == TRUE) { cfc_dialog_change = TRUE; }
//			}
//			else if (LogType != MOUSE_INPUT_LOG_DOWN)
//			{
//				BOOL x = FALSE;	// 以降の処理から抜け出す変数
//				// タイトル画面へ移動
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_move_title) == TRUE){ GameTitleNext(); }
//				// ウィンドウ、フルスクリーンを切り替える
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_full_screen_switch_y, (float)GetDrawStringWidthToHandle("□", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_window_mode_change) == TRUE)
//				{ 
//					// 今現在ウィンドウならフルスクに、フルスクならウィンドウにする
//					ChangeWindowMode(flag_mode_window = GetWindowModeFlag() == TRUE ? FALSE : TRUE);
//					SetMouseDispFlag(TRUE);									// マウスを表示状態にする
//				}
//
//				#pragma region ver0.0041制作時コメント化コード
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("□", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_screen_change_720p) == TRUE)
//				//{ 
//				//	flag_full_hd_now = FALSE;
//				//	ScreenResolutionChange();
//				//}
//
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("□", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_screen_change_1080p) == TRUE)
//				//{
//				//	if(flag_full_hd_ok == TRUE)	// フルＨＤ描画が可能なら
//				//	{
//				//		flag_full_hd_now = TRUE;
//				//		ScreenResolutionChange();
//				//	}
//				//}
//#pragma endregion
//				// 音量を下げる
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_bgm_down) == TRUE)
//				{ 
//					bgm_volume -= 5; 
//					ChangeBGMVolume();
//				}
//				// 音量を上げる
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_bgm_up) == TRUE)
//				{ 
//					bgm_volume += 5;
//					ChangeBGMVolume();
//				}
//				// ＳＥ音量を下げる
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_se_message_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_se_down) == TRUE)
//				{ 
//					se_volume -= 5;
//					ChangeSEVolume();
//				}
//				// ＳＥ音量を上げる
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_se_up) == TRUE)
//				{ 
//					se_volume += 5;
//					ChangeSEVolume();
//				}
//				// 音量変動によって下（上）限値を過ぎた場合、修正する
//				if (bgm_volume < 0){ bgm_volume = 0; }
//				else if (bgm_volume > 100){ bgm_volume = 100; }
//				if (se_volume < 0){ se_volume = 0; }
//				else if (se_volume > 100){ se_volume = 100; }
//				// メッセージ速度を変更する
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_slow) == TRUE){ GameConfigMessageSpeedChange(FALSE); }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_fast) == TRUE){ GameConfigMessageSpeedChange(TRUE); }
//				// ダイアログボックス表示フラグを切り替える
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, FALSE, cfc_dialog_change) == TRUE) { FlagChange(&flag_dialog_appear); }
//				// 全てのフラグを戻す
//				cfc_move_title = FALSE;				// タイトル画面へ移動
//				cfc_window_mode_change = FALSE;		// ウィンドウ、フルスクリーンを切り替える
//				cfc_screen_change_720p = FALSE;		// ウィンドウ解像度を720pxにする
//				cfc_screen_change_1080p = FALSE;	// ウィンドウ解像度を1080pxにする
//				cfc_bgm_down = FALSE;				// ＢＧＭ音量を下げる
//				cfc_bgm_up = FALSE;					// ＢＧＭ音量を上げる
//				cfc_se_down = FALSE;				// ＳＥ音量を下げる
//				cfc_se_up = FALSE;					// ＳＥ音量を上げる
//				cfc_message_slow = FALSE;			// メッセージ速度を遅くする
//				cfc_message_fast = FALSE;			// メッセージ速度を速くする
//				cfc_dialog_change = FALSE;			// ダイアログボックス表示フラグを切り替える
//			}
//		}
#pragma endregion
		// 左ボタンが押されていたら
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				#pragma region ver0.0043制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
#pragma endregion
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_icon_back_x, config_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_FULL_SCREEN], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_x, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_y, TRUE, FALSE) == TRUE) { cfc_window_mode_change[IO_WINDOW_TYPE_FULL_SCREEN] = TRUE; }
				else if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_WINDOW], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_x, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_y, TRUE, FALSE) == TRUE) { cfc_window_mode_change[IO_WINDOW_TYPE_WINDOW] = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, TRUE, FALSE) == TRUE) { cfc_bgm_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, TRUE, FALSE) == TRUE) { cfc_bgm_up = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, TRUE, FALSE) == TRUE) { cfc_se_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, TRUE, FALSE) == TRUE) { cfc_se_up = TRUE; }

				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, TRUE, FALSE) == TRUE) { cfc_text_window_clear[FALSE] = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, TRUE, FALSE) == TRUE) { cfc_text_window_clear[TRUE] = TRUE; }

				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfc_message_slow = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfc_message_fast = TRUE; }
				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, TRUE, FALSE) == TRUE) { cfc_dialog_change = TRUE; }
				else if (image_icon_config_dialog[0][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_dialog[1][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_text_speed[0][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_text_speed[1][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_text_speed[2][0].JudgementClickCheck() == TRUE) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				#pragma region ver0.0043制作時コメント化コード
				// タイトル画面へ移動
				//if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_move_title) == TRUE) { GameTitleNext(); }
#pragma endregion
				// 設定画面の前にいたモードに移行
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_icon_back_x, config_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfc_move_title) == TRUE)
				{
					if (config_before_mc == FALSE) { GameTitleNext(); }
					else{ g_gamestate = GAME_MAIN_COMMUNICATION; }
				}
				// ウィンドウ、フルスクリーンを切り替える
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_FULL_SCREEN], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_x, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_y, FALSE, cfc_window_mode_change[IO_WINDOW_TYPE_FULL_SCREEN]) == TRUE)
				{
					// 今現在ウィンドウならフルスクにする
					if (flag_mode_window == TRUE)
					{ 
						flag_mode_window = FALSE;
						ChangeWindowMode(FALSE);
					}
					SetMouseDispFlag(TRUE);									// マウスを表示状態にする
				}
				else if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_WINDOW], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_x, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_y, FALSE, cfc_window_mode_change[IO_WINDOW_TYPE_WINDOW]) == TRUE)
				{
					// 今現在フルスクならウィンドウにする
					if (flag_mode_window == FALSE)
					{
						flag_mode_window = TRUE;
						ChangeWindowMode(TRUE);
					}
					SetMouseDispFlag(TRUE);									// マウスを表示状態にする
				}

				// 音量を下げる
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, FALSE, cfc_bgm_down) == TRUE)
				{
					bgm_volume -= 5;
					ChangeBGMVolume();
				}
				// 音量を上げる
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, FALSE, cfc_bgm_up) == TRUE)
				{
					bgm_volume += 5;
					ChangeBGMVolume();
				}
				// ＳＥ音量を下げる
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, FALSE, cfc_se_down) == TRUE)
				{
					se_volume -= 5;
					ChangeSEVolume();
				}
				// ＳＥ音量を上げる
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, FALSE, cfc_se_up) == TRUE)
				{
					se_volume += 5;
					ChangeSEVolume();
				}
				// メッセージウィンドウ透過度を下げる
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, FALSE, cfc_text_window_clear[FALSE]) == TRUE && text_window_clear_percentage >= 20)
				{ 
					text_window_clear_percentage -= 20;
					if (text_window_clear_percentage < 0) { text_window_clear_percentage = 0; }
				}
				// メッセージウィンドウ透過度を上げる
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, FALSE, cfc_text_window_clear[TRUE]) == TRUE && text_window_clear_percentage <= 80)
				{
					text_window_clear_percentage += 20;
					if (text_window_clear_percentage > 100) { text_window_clear_percentage = 100; }
				}
				// 音量変動によって下（上）限値を過ぎた場合、修正する
				if (bgm_volume < 0) { bgm_volume = 0; }
				else if (bgm_volume > 100) { bgm_volume = 100; }
				if (se_volume < 0) { se_volume = 0; }
				else if (se_volume > 100) { se_volume = 100; }
				// メッセージ速度を変更する
				#pragma region ver0.0081制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_slow) == TRUE) { GameConfigMessageSpeedChange(FALSE); }
				//if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_fast) == TRUE) { GameConfigMessageSpeedChange(TRUE); }
#pragma endregion
				else if (image_icon_config_text_speed[0][0].JudgementReleaseCheck() == TRUE) { g_commumessagespeed = COMMU_MESSAGE_SPEED_SLOW; }
				else if (image_icon_config_text_speed[1][0].JudgementReleaseCheck() == TRUE) { g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; }
				else if (image_icon_config_text_speed[2][0].JudgementReleaseCheck() == TRUE) { g_commumessagespeed = COMMU_MESSAGE_SPEED_FAST; }
				// ダイアログボックス表示フラグを切り替える
				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, FALSE, cfc_dialog_change) == TRUE) { FlagChange(&flag_dialog_appear); }
				else if (image_icon_config_dialog[0][0].JudgementReleaseCheck() == TRUE) { flag_dialog_appear = TRUE; }
				else if (image_icon_config_dialog[1][0].JudgementReleaseCheck() == TRUE) { flag_dialog_appear = FALSE;}
				// 全てのフラグを戻す
				cfc_move_title = FALSE;												// タイトル画面へ移動
				#pragma region ver0.0042制作時コメント化コード
				//cfc_window_mode_change = FALSE;		// ウィンドウ、フルスクリーンを切り替える
#pragma endregion
				for (int i = 0; i < 2; i++) { cfc_window_mode_change[i] = FALSE; }	// ウィンドウ、フルスクリーンを切り替える
				cfc_screen_change_720p = FALSE;										// ウィンドウ解像度を720pxにする
				cfc_screen_change_1080p = FALSE;									// ウィンドウ解像度を1080pxにする
				cfc_bgm_down = FALSE;												// ＢＧＭ音量を下げる
				cfc_bgm_up = FALSE;													// ＢＧＭ音量を上げる
				cfc_se_down = FALSE;												// ＳＥ音量を下げる
				cfc_se_up = FALSE;													// ＳＥ音量を上げる
				cfc_message_slow = FALSE;											// メッセージ速度を遅くする
				cfc_message_fast = FALSE;											// メッセージ速度を速くする
				//cfc_dialog_change = FALSE;											// ダイアログボックス表示フラグを切り替える
				// ダイアログボックス表示フラグを切り替える
				for (int i = 0; i < 2; i++) { image_icon_config_dialog[i][0].CJChange(FALSE); }

				for (int i = 0; i < 2; i++) { cfc_text_window_clear[i]; }			// メッセージ透過度を増減
			}
		}
	}
}
// コミュの文字スピードに関する要素を変更する
void GameConfigMessageSpeedChange(BOOL x)	// 文字を遅くするか速くするかのフラグ
{
	// スピードを変更する
	if (x == FALSE)
	{
		if (g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL){ g_commumessagespeed = COMMU_MESSAGE_SPEED_SLOW; }
		else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_FAST){ g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; }
	}
	else
	{
		if (g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL){ g_commumessagespeed = COMMU_MESSAGE_SPEED_FAST; }
		else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW){ g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; }
	}
}
// ゲームで使う様々な座標を（再）定義する
void CoordinateSetting()
{
	GameConfigCoordinateSetting();
	GameMainCommunicationCoordinateSetting();
	GameMapCoordinateSetting();
	GameTitleCoordinateSetting();
	SoundRoomCoordinateSetting();		// サウンドルーム
	GameSaveLoadCoordinateSetting();	// セーブ、ロード画面
	GameCommuSelectCoordinateSetting();	// コミュセレクト画面
}
// 設定画面で使う様々な座標を（再）定義する
void GameConfigCoordinateSetting()
{
	config_retu2_x = bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X + GetDrawStringWidthToHandle("メッセージ速度　", 16, g_font3);																								// ２列目項目X座標
	config_coordinate_icon_back_x = screen_size_x - size_icon_auto.x - bairitu * 99;																																	// 『BACK』アイコン左端x座標
	config_coordinate_icon_back_y = bairitu * 99;																																										// 『BACK』アイコン上端y座標
	#pragma region ver0.0042制作時コメント化コード
	//config_coordinate_full_screen_switch_x = config_retu2_x + GetDrawStringWidthToHandle("フルスクリーン ", 15, g_font3);																								// フルスクリーン切り替えスイッチX座標
	//config_coordinate_full_screen_switch_y = bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y;																																	// フルスクリーン切り替えスイッチY座標
	//config_coordinate_screen_resolution_switch_y = config_coordinate_full_screen_switch_y + bairitu * 50;																												// 画面解像度切り替えスイッチY座標
	//config_coordinate_screen_resolution_switch_1920_x = config_coordinate_full_screen_switch_x[0/*適当*/] + GetDrawStringWidthToHandle("1920×1080", 10, g_font3) + bairitu * 160;													// 画面解像度切り替えスイッチ（1920×1080）X座標
	//config_bgm_message_y = config_coordinate_screen_resolution_switch_y + bairitu * CONFIG_LINE_SPACE * 2;																// ＢＧＭ音量関係Y座標
#pragma endregion
	config_coordinate_screen_resolution_switch_y = bairitu * 630;																																						// 画面解像度切り替えスイッチY座標
	config_coordinate_screen_resolution_switch_1920_x = bairitu * 1050;																																					// 画面解像度切り替えスイッチ（1920×1080）X座標
	config_bgm_message_y = bairitu * 339;																																												// ＢＧＭ音量関係Y座標
	config_coordinate_arrow_down_x = image_option_arrow[0].size_x + bairitu * 1275;																																		// 左矢印左端X座標
	#pragma region ver0.0042制作時コメント化コード
	//config_bgm_volume_up_x = config_retu2_x + bairitu * 200;																											// ＢＧＭ『→』文字X座標
#pragma endregion
	config_bgm_volume_up_x = config_coordinate_arrow_down_x + bairitu * 150;																																			// ＢＧＭ『→』文字X座標
	config_se_message_y = config_bgm_message_y + bairitu * CONFIG_LINE_SPACE;																																			// ＢＧＭ音量関係Y座標
	#pragma region ver0.0042制作時コメント化コード
	//config_message_speed_y = config_se_message_y + bairitu * CONFIG_LINE_SPACE * 2;																						// コミュメッセージ速度関係Y座標
#pragma endregion
	config_text_window_clear_y = config_se_message_y + bairitu * CONFIG_LINE_SPACE;																																		// テキストウィンドウ透過度関係Y座標
	config_message_speed_y = config_text_window_clear_y + bairitu * CONFIG_LINE_SPACE;																																	// コミュメッセージ速度関係Y座標
	for (int i = 0; i < CONFIG_MESSAGE_SPEED_NUMBER; i++) { config_coordinate_message_speed_x[i] = bairitu * 1290 + (i - 1) * image_option_message_speed[0].size_x * 1.5f - image_option_message_speed[0].size_x / 2; }	// メッセージ速度選択肢各左端x座標
	for (int i = 0; i < 2; i++) { config_coordinate_full_screen_switch_x[i] = (i == 0 ? -0.75f : 0.75f) * image_option_window_type[i].size_x + bairitu * 1200; }														// フルスクリーン切り替えスイッチX座標
	config_coordinate_full_screen_switch_y = config_message_speed_y + bairitu * CONFIG_LINE_SPACE * 2;																													// フルスクリーン切り替えスイッチY座標
	// ダイアログボックス表示のオンオフ画像
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++) { image_icon_config_dialog[i][j].CoordinateSetting2(1302.0f + i * 105, 758); }
	}
	// テキストメッセージ速度画像
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			const float X = 1024.0f + (i >= 1 ? 160 : 0) + (i == 2 ? 220 : 0);	// 可読性恒常のための定数化
			image_icon_config_text_speed[i][j].CoordinateSetting2(
				X, 548);
		}
	}
}
// 設定画面時描画処理
void DrawGameConfig()
{
	// アイコンではない画像
	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[0].Handle, TRUE);
	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[1].Handle, TRUE);

	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[2].Handle, TRUE);
	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[3].Handle, TRUE);
	
	#pragma region ver0.0042制作時コメント化コード
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y, "画面モード", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y, "フルスクリーン", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_coordinate_full_screen_switch_x, config_coordinate_full_screen_switch_y, GetWindowModeFlag() == FALSE ? "■" : "□", GetColor(255, 255, 255), g_font3);
#pragma endregion
	#pragma region ver0.0041制作時コメント化コード
	//DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, "1280×720", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_coordinate_full_screen_switch_x, config_coordinate_screen_resolution_switch_y, screen_size_x == 1280 ? "■" : "□", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_coordinate_full_screen_switch_x + bairitu * 100, config_coordinate_screen_resolution_switch_y, "1920×1080", (flag_full_hd_ok == TRUE) ? GetColor(255, 255, 255) : GetColor(128, 128, 128), g_font3);	// フルＨＤにできないモニター解像度なら灰色にする
	//DrawStringFToHandle(config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, screen_size_x == 1920 ? "■" : "□", GetColor(255, 255, 255), g_font3);
#pragma endregion
	#pragma region ver0.0042制作時コメント化コード
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_coordinate_screen_resolution_switch_y, "現在解像度", GetColor(255, 255, 255), g_font3);
	////DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, (flag_full_hd_now == FALSE) ? "1280×720" : "1920×1080", GetColor(255, 255, 255), g_font3);
	//if (flag_full_hd_now == FALSE) { DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, "1280×720", GetColor(255, 255, 255), g_font3); }
	//else { DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, "1920×1080", GetColor(255, 255, 255), g_font3); }
#pragma endregion
	float image_pixel_size = image_option[flag_full_hd_now == FALSE ? IMG_OPTION_PIXEL_720 : IMG_OPTION_PIXEL_1080].size_x;
	DrawExtendGraphF(1290 * bairitu - image_pixel_size / 2, 627 * bairitu, 1290 * bairitu + image_pixel_size / 2, image_option[IMG_OPTION_PIXEL_720].size_y + 627 * bairitu, image_option[flag_full_hd_now == FALSE ? IMG_OPTION_PIXEL_720 : IMG_OPTION_PIXEL_1080].Handle, TRUE);
	//DrawExtendGraphF(config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, config_coordinate_screen_resolution_switch_1920_x + image_dialog[0].size_x, config_coordinate_screen_resolution_switch_y + image_dialog[0].size_y, image_dialog[flag_dialog_appear == FALSE ? 0 : 1].Handle, TRUE);
	#pragma region ver0.0043制作時コメント化コード
	//DrawStringFToHandle(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, "TITLE", DrawTitleStringColor(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL), g_font3);
#pragma endregion
	#pragma region ver0.0042制作時コメント化コード
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_bgm_message_y, "ＢＧＭ音量", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, config_bgm_message_y, "←", DrawTitleStringColor(config_retu2_x, config_bgm_message_y, GetDrawStringWidthToHandle("←", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);

	//// （座標が合わない）
	////DrawFormatStringFToHandle(config_retu2_x + bairitu * 100 + GetDrawStringWidthToHandle("←", 2, g_font3) - GetDrawFormatStringWidthToHandle(g_font3, "%d％", bgm_volume) / 2, config_bgm_message_y, GetColor(255, 255, 255), g_font3, "%d％", bgm_volume);
	////（将伍Ｐ解決案）
	//DrawFormatStringFToHandle((config_retu2_x + config_bgm_volume_up_x + GetDrawStringWidthToHandle("→", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d％", bgm_volume) / 2, config_bgm_message_y, GetColor(255, 255, 255), g_font3, "%d％", bgm_volume);

	//DrawStringFToHandle(config_bgm_volume_up_x, config_bgm_message_y, "→", DrawTitleStringColor(config_bgm_volume_up_x, config_bgm_message_y, GetDrawStringWidthToHandle("→", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	//// ＳＥ
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_se_message_y, "ＳＥ音量", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, config_se_message_y, "←", DrawTitleStringColor(config_retu2_x, config_se_message_y, GetDrawStringWidthToHandle("←", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);

	//// （座標が合わない）
	////DrawFormatStringFToHandle(config_retu2_x + bairitu * 100 + GetDrawStringWidthToHandle("←", 2, g_font3) - GetDrawFormatStringWidthToHandle(g_font3, "%d％", se_volume) / 2, config_se_message_y, GetColor(255, 255, 255), g_font3, "%d％", se_volume);
	////（将伍Ｐ解決案）
	//DrawFormatStringFToHandle((config_retu2_x + config_bgm_volume_up_x + GetDrawStringWidthToHandle("→", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d％", se_volume) / 2, config_se_message_y, GetColor(255, 255, 255), g_font3, "%d％", se_volume);

	//DrawStringFToHandle(config_bgm_volume_up_x, config_se_message_y, "→", DrawTitleStringColor(config_bgm_volume_up_x, config_se_message_y, GetDrawStringWidthToHandle("→", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
#pragma endregion
	DrawExtendGraphF(config_coordinate_icon_back_x, config_coordinate_icon_back_y, config_coordinate_icon_back_x + size_icon_auto.x, config_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);

	DrawOptionArrow(bgm_volume, 5, config_bgm_message_y, FALSE);
	float number_x = bairitu * 1371;	// ＢＧＭ音量値等の中心x座標
	DrawFormatStringFToHandle(number_x - GetDrawFormatStringWidthToHandle(g_font3, "%d", bgm_volume) / 2, config_bgm_message_y + bairitu * 12, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::CONFIG_VOLUME)].GetHandle(), "%d", bgm_volume);
	DrawOptionArrow(bgm_volume, 5, config_bgm_message_y, TRUE);
	// ＳＥ
	DrawOptionArrow(se_volume, 5, config_se_message_y, FALSE);
	DrawFormatStringFToHandle(number_x - GetDrawFormatStringWidthToHandle(g_font3, "%d", se_volume) / 2, config_se_message_y + bairitu * 12, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::CONFIG_VOLUME)].GetHandle(), "%d", se_volume);
	DrawOptionArrow(se_volume, 5, config_se_message_y, TRUE);
	// メッセージウィンドウ透過度
	DrawOptionArrow(text_window_clear_percentage, 20, config_text_window_clear_y, FALSE);
	DrawFormatStringFToHandle(number_x - GetDrawFormatStringWidthToHandle(g_font3, "%d", text_window_clear_percentage) / 2, config_text_window_clear_y + bairitu * 12, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::CONFIG_VOLUME)].GetHandle(), "%d", text_window_clear_percentage);
	DrawOptionArrow(text_window_clear_percentage, 20, config_text_window_clear_y, TRUE);
	// メッセージ速度
	#pragma region ver0.0042制作時コメント化コード
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_message_speed_y, "メッセージ速度", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, config_message_speed_y, "←", DrawTitleStringColor(config_retu2_x, config_message_speed_y, GetDrawStringWidthToHandle("←", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	//DrawFormatStringFToHandle(config_retu2_x + GetDrawStringWidthToHandle("←", 2, g_font3) + (config_bgm_volume_up_x - config_retu2_x - GetDrawStringWidthToHandle("←", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%s", config_message_message_speed[g_commumessagespeed]) / 2, config_message_speed_y, GetColor(255, 255, 255), g_font3, "%s", config_message_message_speed[g_commumessagespeed]);
	//DrawStringFToHandle(config_bgm_volume_up_x, config_message_speed_y, "→", DrawTitleStringColor(config_bgm_volume_up_x, config_message_speed_y, GetDrawStringWidthToHandle("→", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
#pragma endregion
	//for (int i = 0; i < CONFIG_MESSAGE_SPEED_NUMBER; i++) { DrawExtendGraphF(config_coordinate_message_speed_x[i], config_message_speed_y, config_coordinate_message_speed_x[i] + image_option_message_speed[i].size_x, config_message_speed_y + image_option_message_speed[0].size_y, image_option_message_speed[i].Handle, TRUE); }
	image_icon_config_text_speed[0][g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW ? 1 : 0].DrawImage();
	image_icon_config_text_speed[1][g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL ? 1 : 0].DrawImage();
	image_icon_config_text_speed[2][g_commumessagespeed == COMMU_MESSAGE_SPEED_FAST ? 1 : 0].DrawImage();
	// 画面モード選択肢
	for (int i = 0; i < 2; i++) { DrawExtendGraphF(config_coordinate_full_screen_switch_x[i], config_coordinate_full_screen_switch_y, config_coordinate_full_screen_switch_x[i] + image_option_window_type[i].size_x, config_coordinate_full_screen_switch_y + image_option_window_type[i].size_y, image_option_window_type[i].Handle, TRUE); }
	// 起動時ダイアログボックス表示
	image_icon_config_dialog[0][flag_dialog_appear].DrawImage();
	image_icon_config_dialog[1][flag_dialog_appear == FALSE ? 1 : 0].DrawImage();
}
// 設定モードの矢印を描画する際の共通処理
void DrawOptionArrow(int x, int y, float z, BOOL a)	// 現在数値、矢印を表示するために必要な限界値との数値差、y座標、矢印は右向きか、
{
	if(a == FALSE && x >= y){ DrawExtendGraphF(config_coordinate_arrow_down_x, z, config_coordinate_arrow_down_x + image_option_arrow[0].size_x, z + image_option_arrow[0].size_y, image_option_arrow[0].Handle, TRUE); }
	else if(x + y <= 100){ DrawExtendGraphF(config_bgm_volume_up_x, z, config_bgm_volume_up_x + image_option_arrow[0].size_x, z + image_option_arrow[0].size_y, image_option_arrow[1].Handle, TRUE); }
}

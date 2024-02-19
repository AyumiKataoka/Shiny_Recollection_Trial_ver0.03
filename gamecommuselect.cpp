#include "gamecommuselect.h"

CommuUpperState g_commuupperstate = CPS_COMMON;	// 表示されるコミュの種類

// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfcs=click_flag_commu_select）
BOOL cfcs_move_title = FALSE;										// タイトル画面へ移動
BOOL cfcs_commu_type_change[COMMU_SELECT_C_TYPE_NUMBER];			// 表示するコミュの種類の切り替えを
BOOL cfcs_commu_character_change[COMMU_SELECT_CHARACTER_NUMBER];	// 表示するコミュの種類の切り替えを

int commu_select_display = 0	;// 表示させられるコミュの個数

float commu_select_coordinate_title_x;										// 『TITLE』アイコン左端x座標
float commu_select_coordinate_title_y;										// 『TITLE』アイコン上端y座標
float commu_select_coordinate_c_type_x[COMMU_SELECT_C_TYPE_NUMBER];			// コミュ種類選択肢左端x座標
float commu_select_coordinate_c_type_y;										// コミュ種類選択肢上端y座標
float commu_select_coordinate_alternative_x;								// コミュ選択肢左端x座標（Y座標はmain.h）
float commu_select_coordinate_character_x;									// キャラアイコン左端x座標
float commu_select_coordinate_character_y[COMMU_SELECT_CHARACTER_NUMBER];	// キャラアイコン上端y座標
// コミュセレクト画面移行処理
void GameCommuSelectNext()
{
	if (g_gamestate != GAME_TITLE) { MusicPlay(BN_TITLE); }			// タイトルＢＧＭを再生する
	g_gamestate = GAME_COMMU_SELECT;
	GameCommuSelectAlternativeCheck();
	// 初期化処理
	commu_before_cs = FALSE;	// コミュの閲覧を始める前はコミュセレクトモードだったか判別するフラグ
}
// GameCommuSelect状態のメイン処理
void GameCommuSelect()
{
	GameCommuSelectControl();
	DrawGameCommuSelect();
}
// コミュセレクト画面操作処理
void GameCommuSelectControl()
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
				if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_title_x, commu_select_coordinate_title_y, size_icon_auto.x * bairitu, size_icon_auto.y * bairitu, TRUE, FALSE) == TRUE) { cfcs_move_title = TRUE; }
				else if (GameMapControlCTYPECheck(TRUE)){}
				else if(GameMapControlCCharacterCheck(TRUE)){}
				else if (GameMapControlCAlternativeCheck(TRUE)) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				// タイトルに戻る
				if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_title_x, commu_select_coordinate_title_y, size_icon_auto.x * bairitu, size_icon_auto.y * bairitu, FALSE, cfcs_move_title) == TRUE) { g_gamestate = GAME_TITLE; }
				// 表示させるコミュを再確認、表示させる
				else if (GameMapControlCTYPECheck(FALSE)) {}
				else if (GameMapControlCCharacterCheck(FALSE)) {}
				else if (GameMapControlCAlternativeCheck(FALSE)) {}
				// 全てのフラグを戻す
				cfcs_move_title = FALSE;																			// タイトル画面へ移動
				for (int i = 0; i < 2; i++) { cfcs_commu_type_change[i] = FALSE; }									// 表示するコミュの種類の切り替え
				for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { cfcs_commu_character_change[i] = FALSE; }	// 表示するコミュのキャラの切り替え
				for (int i = 0; i < CS_COMMU_LIMIT; i++) { cfcs_move_commu[i] = FALSE; }							// 選択されたコミュを閲覧する
			}
		}
	}
}
// 表示させるコミュを検索する
void GameCommuSelectAlternativeCheck()
{
	commu_select_display = 0;
	// 代入前に一度要素をリセットする
	for (int i = 0; i < CS_COMMU_LIMIT; i++) { cs_displat_commu[i].StateReset(); }
	// 現在表示させたいコミュの列挙定数と一致しているものを全コミュの中から検索し、一致していたら構造体に加える
	for (int i = 0; i < GlobalStaticVariable::GetCommuNumber(); i++)
	{
		if(g_commuupperstate == commu_data[i].character_icon)
		{
			cs_displat_commu[commu_select_display].StateChange(&commu_data[i]);
			commu_select_display++;
		}
	}
}
// コミュセレクト画面で使う様々な座標を（再）定義する
void GameCommuSelectCoordinateSetting()
{
	commu_select_coordinate_title_x = 48 * bairitu;																										// 『TITLE』アイコン左端x座標
	commu_select_coordinate_title_y = 48 * bairitu;																										// 『TITLE』アイコン上端y座標
	// コミュ種類選択肢左端x座標（間隔が狭いので少しスペースをあけている）
	for (int i = 0; i < COMMU_SELECT_C_TYPE_NUMBER; i++) { commu_select_coordinate_c_type_x[i] = (float)(screen_size_x * (i + 1) / (COMMU_SELECT_C_TYPE_NUMBER + 1)) - size_ui_cs_alternative_type.x / 2 + (i - 1) * 99 * bairitu; }	

	commu_select_coordinate_c_type_y = bairitu * 99;
	commu_select_coordinate_alternative_x = bairitu * 300;																								// コミュ選択肢左端x座標
	for (int i = 0; i < CS_COMMU_LIMIT; i++) { commu_select_coordinate_alternative_y[i] = i * size_ui_cs_alternative.y * 1.5f + bairitu * 240; };		// コミュ選択肢上端y座標
	commu_select_coordinate_character_x = bairitu * 99;																									// キャラアイコン左端x座標
	for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { commu_select_coordinate_character_y[i] = i * size_ui_map_icon2.y * 1.5f + bairitu * 240; }	// キャラアイコン上端y座標
}
// コミュセレクト時の描画処理
void DrawGameCommuSelect()
{
	// 『TITLE』
	DrawExtendGraphF(commu_select_coordinate_title_x, commu_select_coordinate_title_y, commu_select_coordinate_title_x + size_icon_auto.x * bairitu, commu_select_coordinate_title_y + size_icon_auto.y * bairitu, g_imghandles.icon_title, TRUE);
	// キャラ立ち絵
	if (g_commuupperstate >= CPS_MEGURU && g_commuupperstate < CPS_TEST)
	{
		float x = bairitu * 330;	// キャラ立ち絵素材を右にずらす値
		float y = bairitu * 132;	// キャラ立ち絵素材を下にずらす値
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_body[g_commuupperstate - 1][0][0], TRUE);
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_face[g_commuupperstate - 1][0][0][1][2], TRUE);
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_eyebrow[g_commuupperstate - 1][0][0][1][2], TRUE);	// 眉毛（テスト）
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_face[g_commuupperstate - 1][0][0][1][6], TRUE);
	}

	#pragma region ver0.00399制作時コメント化コード
	//for (int i = 0; i < 2; i++)
#pragma endregion
	for (int i = 0; i < COMMU_SELECT_C_TYPE_NUMBER; i++)
	{
		DrawExtendGraphF(commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, commu_select_coordinate_c_type_x[i] + size_ui_cs_alternative_type.x, commu_select_coordinate_c_type_y + size_ui_cs_alternative_type.y, g_imghandles.commu_select_type, TRUE); 
		char c[256];
		const char* s = "";
		switch (i)
		{
		case 0: s = "MAIN COMMU";	break;
		case 1: s = "CHARACTER";	break;
		case 2: s = "TEST";			break;
		default:					break;
		}
		sprintf_s(c, 256, "%s", s);
		DrawStringFToHandle(commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, "", DrawTitleStringColor(config_bgm_volume_up_x, config_message_speed_y, GetDrawStringWidthToHandle("→", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
		DrawFormatStringFToHandle(commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, GetColor(0, 0, 0), g_font3, "%s", c);
	}
	// コミュ選択肢
	for (int i = 0; i < CS_COMMU_LIMIT; i++) 
	{
		// コミュＩＤが1以上（コミュが存在している）ならＵＩを表示させる
		if (cs_displat_commu[i].id >= 1)
		{
			DrawExtendGraphF(commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], commu_select_coordinate_alternative_x + size_ui_cs_alternative.x, commu_select_coordinate_alternative_y[i] + size_ui_cs_alternative.y, g_imghandles.commu_select, TRUE);
			DrawFormatStringFToHandle(commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], GetColor(0, 0, 0), g_font3, "%s", cs_displat_commu[i].name);
		}
	}
	// キャラアイコン（表示コミュがキャラクターのものなら）
	if (g_commuupperstate >= CPS_MEGURU && g_commuupperstate < CPS_TEST)
	{
		for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { DrawExtendGraphF(commu_select_coordinate_character_x, commu_select_coordinate_character_y[i], commu_select_coordinate_character_x + size_ui_map_icon2.x, commu_select_coordinate_character_y[i] + size_ui_map_icon2.y, g_imghandles.ui_map_icon[i], TRUE); }
	}
}
// コミュ種類選択肢クリック確認用関数
BOOL GameMapControlCTYPECheck(BOOL x)
{
	for (int i = 0; i < COMMU_SELECT_C_TYPE_NUMBER; i++)
	{
		if (x == TRUE)
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, size_ui_cs_alternative_type.x, size_ui_cs_alternative_type.y, TRUE, FALSE) == TRUE)
			{
				cfcs_commu_type_change[i] = TRUE;
				return TRUE;
			}
		}
		else
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, size_ui_cs_alternative_type.x, size_ui_cs_alternative_type.y, FALSE, cfcs_commu_type_change[i]) == TRUE)
			{
				// 表示させるコミュを再確認、表示させる
				switch (i)
				{
				case 0: g_commuupperstate = CPS_COMMON; break;
				case 1: g_commuupperstate = CPS_MEGURU; break;
				case 2: g_commuupperstate = CPS_TEST;	break;
				default:								break;
				}
				GameCommuSelectAlternativeCheck();
				return TRUE;
			}
		}
	}
	return FALSE;
}
// コミュキャラ選択肢クリック確認用関数
BOOL GameMapControlCCharacterCheck(BOOL x)
{
	for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++)
	{
		if (x == TRUE)
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_character_x, commu_select_coordinate_character_y[i], size_ui_map_icon2.x, size_ui_map_icon2.y, TRUE, FALSE) == TRUE)
			{
				cfcs_commu_character_change[i] = TRUE;
				return TRUE;
			}
		}
		else
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_character_x, commu_select_coordinate_character_y[i], size_ui_map_icon2.x, size_ui_map_icon2.y, FALSE, cfcs_commu_character_change[i]) == TRUE && g_commuupperstate >= CPS_MEGURU && g_commuupperstate < CPS_TEST)
			{
				// 表示させるコミュを再確認、表示させる
				g_commuupperstate = static_cast<CommuUpperState>(i + 1);
				GameCommuSelectAlternativeCheck();
				return TRUE;
			}
		}
	}
	return FALSE;
}
// コミュ選択肢クリック確認用関数
BOOL GameMapControlCAlternativeCheck(BOOL x)
{
	for (int i = 0; i < CS_COMMU_LIMIT; i++)
	{
		if (x == TRUE)
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], size_ui_cs_alternative.x, size_ui_cs_alternative.y, TRUE, FALSE) == TRUE)
			{
				cfcs_move_commu[i] = TRUE;
				return TRUE;
			}
		}
		else
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], size_ui_cs_alternative.x, size_ui_cs_alternative.y, FALSE, cfcs_move_commu[i]) == TRUE)
			{
				// （存在していれば）コミュを閲覧する
				if (cs_displat_commu[i].id >= 1) { GameMainCommunicationNext(cs_displat_commu[i].id - 1, TRUE, 0); }
				return TRUE;
			}
		}
	}
	return FALSE;
}
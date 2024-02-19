#include "gamemap.h"

MapDestinationType g_map_destination = MAP_DESTINATION_LEFT;								// 移動先マップの状態

TipsStringData tips_string[2];
/* TipsDataクラス ---------*/
int TipsData::number = 0;
#pragma region ver0.00708制作時コメント化コード
//TipsData tips_data[TIPS_NUMBER];		// tips関係の構造体
#pragma endregion
TipsData tips_data[TipsData::LOAD_LIMIT];	// tips関係の構造体
/*-------------------------*/
BOOL GlobalStaticMap::trial_commu_viewed[COMMU_CHARACTER_NUMBER] = { FALSE, FALSE, FALSE , FALSE , FALSE };
void GlobalStaticMap::TrialCommuViewedReset()
{
	for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++) { trial_commu_viewed[i] = FALSE; }
}
#pragma region ver0.00704制作時コメント化コード
//CommuData commu_data[COMMU_NUMBER], commu_data_map[COMMU_MAP_LIMIT], commu_data_map_choice;	// コミュのステータス
#pragma endregion
/* CommuDataクラス ---------*/
CommuData::MapUpperType CommuData::g_mapuppertype = CommuData::MapUpperType::DEFAULT;
CommuData commu_data[COMMU_NUMBER_MAX], commu_data_map[COMMU_MAP_LIMIT], commu_data_map_choice;	// コミュのステータス
// 様々なデータをセットする
void CommuData::SetData(int x, int y) // 代入先マップデータＩＤ、代入元コミュＩＤ
{
	commu_data_map[x].id = commu_data[y].id;
	sprintf_s(commu_data_map[x].path, 256, "%s", commu_data[y].path);
	sprintf_s(commu_data_map[x].title, 256, "%s", commu_data[y].title);
	commu_data_map[x].appear_timing = commu_data[y].appear_timing;
	commu_data_map[x].character_icon = commu_data[y].character_icon;
	commu_data_map[x].map_zone = commu_data[y].map_zone;
	commu_data_map[x].map_coordinate_x = commu_data[y].map_coordinate_x;
	commu_data_map[x].map_coordinate_y = commu_data[y].map_coordinate_y;
}
/*--------------------------*/
BOOL map_move_commu_check = FALSE; // 選択したコミュを閲覧するか確認するフラグ
BOOL map_commu_upper[3][2];	// マップ画面にコミュアイコンが出現するか
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfgm=click_flag_game_map）
//BOOL cfgm_move_left = FALSE;			// 左マップへ移動
//BOOL cfgm_move_right = FALSE;			// 右マップへ移動
#pragma region ver0.0038制作時コメント化コード
//BOOL cfgm_commu_check = FALSE;		// 選択コミュ閲覧画面を表示する
#pragma endregion
BOOL cfgm_commu_check[COMMU_MAP_LIMIT];	// 選択コミュ閲覧画面を表示する
BOOL cfgm_commu_check_ok = FALSE;		// 選択コミュへ移行する
BOOL cfgm_commu_check_no = FALSE;		// 選択コミュ閲覧画面を解除する

int game_week_number = GlobalStaticMap::WEEK_INITIAL_VALUE;	// ゲーム中の月、週を参照する変数（11＝３月４週）
int commu_look_count[COMMU_CHARACTER_NUMBER];	// マップ画面からアイコンを選択し、（フレンドコミュ以外の）各キャラのコミュを見た回数
//int select_map_number = 1;	// 選ばれているマップＵＩ
int map_font_arrow;								// マップ画面矢印のフォントサイズ

float draw_map_plus_x;				// マップＵＩに加算するx座標値
//float map_arrow_left_x;				// 左側に行く矢印のx座標値
//float map_arrow_right_x;			// 右側に行く矢印のx座標値
float draw_map_space;				// 各マップ間の隙間
#pragma region ver0.0038制作時コメント化コード
//float draw_map_character_icon_x;	// キャラアイコンx座標始点
//float draw_map_character_icon_y;	// キャラアイコンy座標始点
#pragma endregion
//float draw_map_character_icon_x[COMMU_MAP_LIMIT];		// キャラアイコンx座標始点
float draw_map_character_icon_x[COMMU_MAP_LIMIT] = { -300, -300, -300 , -300 , -300 , -300 , -300 , -300 , -300 , -300 };		// キャラアイコンx座標始点
float draw_map_character_icon_y[COMMU_MAP_LIMIT];		// キャラアイコンy座標始点
float draw_map_coordinate_hukidasi_x[COMMU_MAP_LIMIT];	// 吹き出しx座標始点
float draw_map_coordinate_hukidasi_y[COMMU_MAP_LIMIT];	// 吹き出しy座標始点
float draw_map_commu_choice_x[2];						// コミュ移動選択肢x座標始点
float draw_map_commu_choice_y;							// コミュ移動選択肢y座標始点
// マップ画面移行処理
void GameMapNext()
{
	MusicPlay(BN_MAP);
	SEPlay(-2);	//	コミュ終了というよりはループＳＥを停止させるための処理
	g_gamestate = GAME_MAP;
	//select_map_number = 1;
	g_map_destination = MAP_DESTINATION_LEFT;
	map_move_commu_check = FALSE;
	//draw_map_plus_x = 0;	// マップＵＩに加算するx座標値
	draw_map_plus_x = size_ui_map.x * bairitu + draw_map_space;	// マップＵＩに加算するx座標値
	game_week_number++;	// １週進める
	// マップのコミュデータを初期化する
	for (int i = 0; i < COMMU_MAP_LIMIT; i++)
	{
		commu_data_map[i].id = 0;
		sprintf_s(commu_data_map[i].path, 256, "");
		commu_data_map[i].SetTitle((char*)"");
		commu_data_map[i].appear_timing = 0;
		commu_data_map[i].character_icon = 0;
		commu_data_map[i].map_zone = 0;
		commu_data_map[i].map_coordinate_x = 0;
		commu_data_map[i].map_coordinate_y = bairitu * -255;
		// マップ上にアイコンの当たり判定が残り続けるバグを回避するための処理
		draw_map_coordinate_hukidasi_y[i] = commu_data_map[i].map_coordinate_y;
	}
	// 全てのコミュから現在の月、週と出現時期が一致するコミュを探す（該当しているものを専用の構造体に代入する？）
	// 体験版の場合、まだ見ていない特定のコミュを表示させる
	int x = 0;
	if (GlobalStaticVariable::GetModeTrial() == FALSE)
	{
		#pragma region ver0.0039制作時コメント化コード
		//int c[3] = {};	// コミュ確認用変数
#pragma endregion
		int c[COMMU_CHARACTER_NUMBER] = {};	// コミュ確認用変数
		#pragma region ver0.00704制作時コメント化コード
//for (int i = 0; i < COMMU_NUMBER; i++)
#pragma endregion
		for (int i = 0; i < GlobalStaticVariable::GetCommuNumber(); i++)
		{
			// コミュがめぐる～千雪専用のコミュなら
			#pragma region ver0.00706制作時コメント化コード
//if (commu_data[i].character_icon != 0 && commu_data[i].character_icon < 6)	// （アプリが停止しない代わりに吹き出しはあるがアイコンが表示されない）
#pragma endregion
			if (GameMapUpperCheck(commu_data[i].character_icon, i) == TRUE)
			{
				//	キャラ毎のこのループを通った回数		キャラ毎のコミュを見た回数																						
				if (c[commu_data[i].character_icon - 1] == commu_look_count[commu_data[i].character_icon - 1])
				{
					commu_data_map[x].id = commu_data[i].id;
					#pragma region ver0.00706制作時コメント化コード
					//sprintf_s(commu_data_map[i].path, 256, "%s", commu_data[i].path);
#pragma endregion
					sprintf_s(commu_data_map[x].path, 256, "%s", commu_data[i].path);
					sprintf_s(commu_data_map[x].title, 256, "%s", commu_data[i].title);
					commu_data_map[x].appear_timing = commu_data[i].appear_timing;
					commu_data_map[x].character_icon = commu_data[i].character_icon;
					commu_data_map[x].map_zone = commu_data[i].map_zone;
					commu_data_map[x].map_coordinate_x = commu_data[i].map_coordinate_x;
					commu_data_map[x].map_coordinate_y = commu_data[i].map_coordinate_y;
					x++;
				}
				c[commu_data[i].character_icon - 1]++;
			}
			// フレンドＣＧコミュ出現状態なら
			else if (CommuData::GetGMapUpperType() == CommuData::MapUpperType::FRIEND_CG_MEGURU && i == static_cast<int>(CommuType::FRIEND))
			{
				commu_data_map[x].id = commu_data[i].id;
				sprintf_s(commu_data_map[x].path, 256, "%s", commu_data[i].path);
				sprintf_s(commu_data_map[x].title, 256, "%s", commu_data[i].title);
				commu_data_map[x].appear_timing = commu_data[i].appear_timing;
				// なぜかCommuData::MapUpperTypeに数値が初期化されている
				commu_data_map[x].character_icon = static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 4;

				commu_data_map[x].map_zone = commu_data[i].map_zone;
				commu_data_map[x].map_coordinate_x = commu_data[i].map_coordinate_x;
				commu_data_map[x].map_coordinate_y = commu_data[i].map_coordinate_y;
				x++;
			}
		}
	}
	else
	{
		for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++)
		{
			if (GlobalStaticMap::GetTrialCommuViewed(i) == FALSE)
			{
				// iの値に応じたＩＤのコミュデータを代入する
				int y = 0;
				switch (i)
				{
				case 0: y = static_cast<int>(CommuType::MEGURU5);		break;
				case 1: y = static_cast<int>(CommuType::KOGANE_STILL);	break;
				case 2: y = static_cast<int>(CommuType::JURI_STILL);	break;
				case 3: y = static_cast<int>(CommuType::RINZE0);		break;
				case 4: y = static_cast<int>(CommuType::CHIYUKI_STILL);	break;
				default:												break;
				}
				CommuData::SetData(x, y);
				x++;
			}
		}
	}
	commu_number = -1;	// ロードしたらマップに移動するデータを不具合なくセーブできるようコミュＩＤを初期化する
}
// GAME_MAP状態のメイン処理
void GameMap()
{
	GameMapControl();
	GameMapFlame();
	DrawGameMap();
}
// マップ画面操作処理
void GameMapControl()
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
				#pragma region ver0.0053制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, map_arrow_left_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("←", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, TRUE, FALSE) == TRUE){ cfgm_move_left = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, map_arrow_right_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("→", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, TRUE, FALSE) == TRUE){ cfgm_move_right = TRUE; }
#pragma endregion
				if(hjimage_map[0].JudgementClickCheck() == TRUE){}
				else if(hjimage_map[1].JudgementClickCheck() == TRUE){}
				else if (hjimage_map[2].JudgementClickCheck() == TRUE) {}
				else if (hjimage_map[3].JudgementClickCheck() == TRUE) {}
				#pragma region ver0.0038制作時コメント化コード
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x, draw_map_character_icon_y, size_ui_map_icon.x * bairitu, size_ui_map_icon.y * bairitu, TRUE, FALSE) == TRUE){ cfgm_commu_check = TRUE; }
#pragma endregion
				else if (GameMapControlCommuCheck(TRUE)){}
				#pragma region ver0.00393制作時コメント化コード
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE){ cfgm_commu_check_ok = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[1], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE){ cfgm_commu_check_no = TRUE; }
#pragma endregion
				#pragma region ver0.0081制作時コメント化コード
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE && map_move_commu_check == TRUE) { cfgm_commu_check_ok = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[1], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE && map_move_commu_check == TRUE) { cfgm_commu_check_no = TRUE; }
#pragma endregion
				else if (image_icon_check[0].JudgementClickCheck() == TRUE && map_move_commu_check == TRUE) {}
				else if (image_icon_check[1].JudgementClickCheck() == TRUE && map_move_commu_check == TRUE) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				// マップを移動する
				#pragma region ver0.0053制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, map_arrow_left_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("←", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, FALSE, cfgm_move_left) == TRUE)
				//{
				//	if (map_move_commu_check == FALSE)
				//	{
				//		if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_LEFT; }
				//		else if (g_map_destination == MAP_DESTINATION_RIGHT){ g_map_destination = MAP_DESTINATION_CENTER; }
				//	}
				//}
				//else if (ClickFlagCheckF(ClickX, ClickY, map_arrow_right_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("→", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, FALSE, cfgm_move_right) == TRUE)
				//{ 
				//	if (map_move_commu_check == FALSE)
				//	{
				//		if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_RIGHT; }
				//		else if (g_map_destination == MAP_DESTINATION_LEFT){ g_map_destination = MAP_DESTINATION_CENTER; }
				//	}
				//}
#pragma endregion
				if (hjimage_map[0].JudgementReleaseCheck() == TRUE)
				{
					if (map_move_commu_check == FALSE)
					{
						if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_LEFT; }
						else if (g_map_destination == MAP_DESTINATION_RIGHT){ g_map_destination = MAP_DESTINATION_CENTER; }
					}
				}
				else if (hjimage_map[1].JudgementReleaseCheck() == TRUE)
				{
					if (map_move_commu_check == FALSE)
					{
						if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_RIGHT; }
						else if (g_map_destination == MAP_DESTINATION_LEFT){ g_map_destination = MAP_DESTINATION_CENTER; }
					}
				}
				else if (hjimage_map[2].JudgementReleaseCheck() == TRUE) 
				{ 
					GameSaveLoadNext(TRUE, SL_BEFORE_MAP); 
					SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
				}
				else if (hjimage_map[3].JudgementReleaseCheck() == TRUE) 
				{ 
					GameSaveLoadNext(FALSE, SL_BEFORE_MAP);
					SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
				}
				#pragma region ver0.0038制作時コメント化コード
				// コミュ移動確認状態にする
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x, draw_map_character_icon_y, size_ui_map_icon.x, size_ui_map_icon.y, FALSE, cfgm_commu_check) == TRUE){ map_move_commu_check = TRUE; }
				// 選択したコミュを閲覧する
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, FALSE, cfgm_commu_check_ok) == TRUE){ GameMainCommunicationNext(2); }
#pragma endregion
				// コミュ移動確認状態にする
				else if (GameMapControlCommuCheck(FALSE)) {}
				// 選択したコミュを閲覧する
				else if (image_icon_check[0].JudgementReleaseCheck() == TRUE && map_move_commu_check == TRUE)
				#pragma region ver0.0081制作時コメント化コード
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, FALSE, cfgm_commu_check_ok) == TRUE)
#pragma endregion
				{
					// （デバッグ：コミュが存在してなかったら強制終了させる）
					if (commu_data_map[0].id == 0) { quit_game = TRUE; }
					#pragma region ver0.00607制作時コメント化コード
					//else { GameMainCommunicationNext(commu_data_map_choice.id - 1, FALSE); }
#pragma endregion
					else 
					{ 
						SEPlay(static_cast<int>(SEData::IDName::COMMU_START));	// ＳＥを鳴らす
						SEData::SetCommuStartTime();
						GameMainCommunicationNext(commu_data_map_choice.id - 1, FALSE, 0);
					}

					commu_look_count[commu_data_map_choice.character_icon - 1]++;	// キャラ別コミュ視聴回数をカウントする
				}
				// コミュ移動確認画面を消す
				#pragma region ver0.0081制作時コメント化コード
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[1], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, FALSE, cfgm_commu_check_no) == TRUE){ map_move_commu_check = FALSE; }
#pragma endregion
				else if (image_icon_check[1].JudgementReleaseCheck() == TRUE && map_move_commu_check == TRUE) { map_move_commu_check = FALSE; }
				// 全てのフラグを戻す
				#pragma region ver0.0053制作時コメント化コード
				//cfgm_move_left = FALSE;														// 左マップへ移動
				//cfgm_move_right = FALSE;													// 右マップへ移動
#pragma endregion
				for (int i = 0; i < HIT_JUDGEMENT_IMAGE_NUMBER_MAP; i++) { hjimage_map[i].CJChange(FALSE); }
				#pragma region ver0.0038制作時コメント化コード
				//cfgm_commu_check = FALSE;		// 選択コミュ閲覧画面を表示する
#pragma endregion
				for (int i = 0; i < COMMU_MAP_LIMIT; i++) { cfgm_commu_check[i] = FALSE; }	// 選択コミュ閲覧画面を表示する
				cfgm_commu_check_ok = FALSE;												// 選択コミュへ移行する
				cfgm_commu_check_no = FALSE;												// 選択コミュ閲覧画面を解除する
				for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].CJChange(FALSE); }
			}
		}
	}
}
// マップモード時１フレーム毎に行われる処理
void GameMapFlame()
{
	// tips文字列のX座標を動かす
	for (int i = 0; i < 2; i++)
	{ 
		#pragma region ver0.021制作時コメント化コード
		//if (i == 0 || tips_string[0].x < screen_size_x - GetDrawFormatStringWidthToHandle(g_font_tips, tips_string[0].string) - bairitu * 256){ tips_string[i].x -= 3; }
#pragma endregion
		if (i == 0 || tips_string[0].x < screen_size_x - GetDrawFormatStringWidthToHandle(g_font_tips, tips_string[0].string) - bairitu * 256) { tips_string[i].x -= 2; }
	}
	// tips文字列[0]が一定位置まで来たらGameMapTipsSubstitution関数を呼び出す
	if (tips_string[0].x < screen_size_x - GetDrawFormatStringWidthToHandle(g_font_tips, tips_string[0].string) - screen_size_x * 2 / 3){ GameMapTipsSubstitution(); }

	float s = bairitu * 120;	// 移動速度ローカル変数
	// 行き過ぎた座標を修正する（目的地中）
	if (g_map_destination == MAP_DESTINATION_CENTER && draw_map_plus_x >= (-s) && draw_map_plus_x <= s){ draw_map_plus_x = 0; }
	// ターゲットのマップとdraw_map_plus_xの値に応じてdraw_map_plus_xに数値を加減し、座標を再定義する
	if ((g_map_destination == MAP_DESTINATION_LEFT && draw_map_plus_x < size_ui_map.x * bairitu + draw_map_space) || (g_map_destination == MAP_DESTINATION_CENTER && draw_map_plus_x < 0)){ draw_map_plus_x += s; }
	if ((g_map_destination == MAP_DESTINATION_RIGHT && draw_map_plus_x > (size_ui_map.x * bairitu + draw_map_space) * (-1)) || (g_map_destination == MAP_DESTINATION_CENTER && draw_map_plus_x > 0)){ draw_map_plus_x -= s; }
	// 行き過ぎた座標を修正する（目的地左右）
	if (g_map_destination == MAP_DESTINATION_LEFT && draw_map_plus_x > size_ui_map.x * bairitu + draw_map_space){ draw_map_plus_x = size_ui_map.x * bairitu + draw_map_space; }
	if (g_map_destination == MAP_DESTINATION_RIGHT && draw_map_plus_x < (size_ui_map.x * bairitu + draw_map_space) * (-1)){ draw_map_plus_x = (size_ui_map.x * bairitu + draw_map_space) * (-1); }
	// draw_map_plus_xによって変化する座標を再定義する
	#pragma region ver0.0038制作時コメント化コード
	//draw_map_character_icon_x = screen_size_x / 2 - size_ui_map_icon.x * bairitu / 2 + draw_map_plus_x + (commu_data_map[0].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[0].map_coordinate_x;	// キャラアイコンx座標始点
	//draw_map_character_icon_y = screen_size_y / 2 - size_ui_map_icon.y * bairitu / 2 + commu_data_map[0].map_coordinate_y;																										// キャラアイコンy座標始点
#pragma endregion
	for (int i = 0; i < COMMU_MAP_LIMIT; i++)
	{
		if (commu_data_map[i].id != 0)
		{
			draw_map_character_icon_x[i] =		screen_size_x / 2 - size_ui_map_icon2.x * bairitu / 2 + draw_map_plus_x + (commu_data_map[i].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[i].map_coordinate_x + bairitu * 82;				// キャラアイコンx座標始点
			draw_map_character_icon_y[i] = screen_size_y / 2 - size_ui_map_icon2.y * bairitu / 2 + commu_data_map[i].map_coordinate_y - bairitu * 45;																												// キャラアイコンy座標始点
			#pragma region ver0.0081制作時コメント化コード
			//draw_map_coordinate_hukidasi_x[i] = screen_size_x / 2 - size_ui_map_hukidasi[0].x * bairitu / 2 + draw_map_plus_x + (commu_data_map[i].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[i].map_coordinate_x + bairitu * 82;	// 吹き出しx座標始点
			//draw_map_coordinate_hukidasi_y[i] = screen_size_y / 2 - size_ui_map_hukidasi[0].y * bairitu * 2 / 5 + commu_data_map[i].map_coordinate_y - bairitu * 45;																									// 吹き出しy座標始点
#pragma endregion
			// 
			const float X = (commu_data_map[i].id == static_cast<int>(CommuType::FRIEND) + 1 ? image_icon_map_character[static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 5].GetSizeX() / 2 : image_icon_map_character[0].GetSizeX() / 2);

			draw_map_coordinate_hukidasi_x[i] = screen_size_x / 2 - X + draw_map_plus_x + (commu_data_map[i].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[i].map_coordinate_x + bairitu * 82;	// 吹き出しx座標始点
			draw_map_coordinate_hukidasi_y[i] = screen_size_y / 2 - image_icon_map_character[0].GetSizeY() * 2 / 5 + commu_data_map[i].map_coordinate_y - bairitu * 45;																									// 吹き出しy座標始点
		}
	}
	// マップ移動矢印の座標を（再）定義する
	float x = screen_size_x * 0.54f;
	float y = bairitu * 705;														// 両矢印の中心からのずれ
	float z = (22.5f - (progress_frame % 45)) * bairitu;
	hjimage_map[0].CoordinateSetting(x - y - hjimage_map[0].size_x / 2 - abs(z), screen_size_y / 2.0f);
	hjimage_map[1].CoordinateSetting(x + y - hjimage_map[1].size_x / 2 + abs(z), screen_size_y / 2.0f);
}
// tips文字列データを代入する
void GameMapTipsSubstitution()
{
	// [1]のデータを[0]に代入する
	tips_string[0].string = tips_string[1].string;
	tips_string[0].x = tips_string[1].x;
	// 存在する全てのtipsの中からまだ出現していないものを調べる（全て出現済みの場合はフラグをリセットし、[0]の次のＩＤのものを[1]に代入させる？）
	for (int j = (tips_string[0].string == NULL ? 0 : 1); j < 2; j++)
	{
		int x = 0;	// 未出現tipsカウント用変数
		#pragma region ver0.00706制作時コメント化コード
		//int y[TIPS_NUMBER];
		//char* c[TIPS_NUMBER];
#pragma endregion
		#pragma region ver0.00708制作時コメント化コード
		//int y[TIPS_NUMBER] = {0, 0, 0};
		//char* c[TIPS_NUMBER] = {};
		//do
		//{
		//	for (int i = 0; i < TIPS_NUMBER; i++)
		//	{
		//		if (tips_data[i].appear == FALSE)
		//		{
		//			c[x] = tips_data[i].tips;
		//			y[x] = tips_data[i].id;
		//			x++;
		//		}
		//	}
		//	if (x == 0)
		//	{
		//		for (int i = 0; i < TIPS_NUMBER; i++){ tips_data[i].appear = FALSE; }
		//	}
		//} while (x == 0);	// xが0の限りループ
#pragma endregion
		int y[TipsData::LOAD_LIMIT];
		char* c[TipsData::LOAD_LIMIT];
		//int y[3];
		//char* c[3];
		do
		{
			for (int i = 0; i < TipsData::GetNumber(); i++)
			{
				if (tips_data[i].appear == FALSE)
				{
					c[x] = tips_data[i].tips;
					y[x] = tips_data[i].id;
					x++;
				}
			}
			if (x == 0)
			{
				for (int i = 0; i < TipsData::GetNumber(); i++) { tips_data[i].appear = FALSE; }
			}
		} while (x == 0);	// xが0の限りループ
		// 出現していないものからランダムに１つ選び、初期位置含めた情報を[1]（初回なら[0]）に代入する
		//（１周の終わりと２周の最初で被る可能性もあるので、[1]を選ぶ際、[0]と被ったらやり直す、という処理も入れておきたい）
		int z = GetRand(x - 1);	// 乱数用変数
		tips_string[j].string = c[z];

		tips_string[j].x = (float)screen_size_x;
		// （yの値がMinusになり不具合が起きている）
		tips_data[y[z]].appear = TRUE;
	}
}
// マップ画面で使う様々な座標を（再）定義する
void GameMapCoordinateSetting()
{
	// フォントも定義する
	map_font_arrow = g_font_commu_name;	// マップ画面矢印のフォントサイズ

	#pragma region ver0.0051制作時コメント化コード
	//float x = screen_size_x / 2.0f;
	//float y = bairitu * 600;														// 両矢印の中心からのずれ
	//map_arrow_left_x = x - y - GetDrawStringWidthToHandle("←", 2, g_font3);		// 左側に行く矢印のx座標値
#pragma endregion

	draw_map_space = bairitu * 360;													// 各マップ間の隙間
	// コミュ移動選択肢x座標始点
	float z = size_ui_map_check_choice.x * bairitu / 2 + 90;	// 両選択肢で扱われる数値のローカル変数
	draw_map_commu_choice_x[0] = (screen_size_x - size_ui_map_check_choice.x * bairitu) / 2 - z;
	draw_map_commu_choice_x[1] = (screen_size_x - size_ui_map_check_choice.x * bairitu) / 2 + z;

	draw_map_commu_choice_y = (screen_size_y + size_ui_map_check.y * bairitu) / 2 - size_ui_map_check_choice.y * bairitu - 120;	// コミュ移動選択肢y座標始点（未完了）
	// セーブ、ロードアイコン
	float x = 24 * bairitu;
	hjimage_map[2].CoordinateSetting(x, screen_size_y - hjimage_map[2].GetSizeY() * 4);
	hjimage_map[3].CoordinateSetting(x, screen_size_y - hjimage_map[3].GetSizeY() * 2);
	// コミュ移動選択肢
	for (int i = 0; i < 2; i++)
	{
		image_icon_map_move_alternative[i].CoordinateSetting2(
			image_icon_map_move_alternative[i].GetOriginalSizeX() * (i - 1) + 19 * (i == 0 ? 1 : -1) + 1034.0f,
			675.0f);
	}
	// コミュ移動確認時等の選択肢の『いいえ』当たり判定用
	image_icon_map_collision_detection.CoordinateSetting2(
	1008, 861.0f - image_icon_map_collision_detection.GetOriginalSizeY());
}
// マップモード時描画処理
void DrawGameMap()
{
	// マップ背景
	image_map_background.DrawImage();
	// マップ
	DrawExtendGraphF(screen_size_x / 2 - size_ui_map.x * bairitu * 1.5f - draw_map_space + draw_map_plus_x, screen_size_y / 2 - size_ui_map.y * bairitu / 2, (screen_size_x - size_ui_map.x * bairitu) / 2 - draw_map_space + draw_map_plus_x, (screen_size_y + size_ui_map.y * bairitu) / 2, g_imghandles.ui_map[0], TRUE);
	DrawExtendGraphF(screen_size_x / 2 - size_ui_map.x * bairitu / 2 + draw_map_plus_x, screen_size_y / 2 - size_ui_map.y * bairitu / 2, (screen_size_x + size_ui_map.x * bairitu) / 2 + draw_map_plus_x, (screen_size_y + size_ui_map.y * bairitu) / 2, g_imghandles.ui_map[1], TRUE);
	DrawExtendGraphF(screen_size_x / 2 + size_ui_map.x * bairitu / 2 + draw_map_space + draw_map_plus_x, screen_size_y / 2 - size_ui_map.y * bairitu / 2, screen_size_x / 2 + size_ui_map.x * bairitu * 1.5f + draw_map_space + draw_map_plus_x, (screen_size_y + size_ui_map.y * bairitu) / 2, g_imghandles.ui_map[2], TRUE);
	// キャラアイコン
	for (int i = 0; i < COMMU_MAP_LIMIT; i++)
	{
		if (commu_data_map[i].id != 0)
		{
			// 吹き出し（現在は１人用で固定、後々コミュに応じた大きさのアイコンに変化させる必要がある）
			#pragma region ver0.0081制作時コメント化コード
//			DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i],draw_map_coordinate_hukidasi_x[i] + size_ui_map_hukidasi[0].x * bairitu, draw_map_coordinate_hukidasi_y[i] + size_ui_map_hukidasi[0].y * bairitu, g_imghandles.ui_map_hukidasi[0], TRUE);
//			#pragma region ver0.0042制作時コメント化コード
//			//DrawExtendGraphF(draw_map_character_icon_x[i], draw_map_character_icon_y[i], draw_map_character_icon_x[i] + size_ui_map_icon.x * bairitu, draw_map_character_icon_y[i] + size_ui_map_icon.y * bairitu, g_imghandles.ui_map_icon[commu_data_map[i].character_icon - 1], TRUE);
//#pragma endregion
//			DrawExtendGraphF(draw_map_character_icon_x[i], draw_map_character_icon_y[i],draw_map_character_icon_x[i] + size_ui_map_icon2.x * bairitu, draw_map_character_icon_y[i] + size_ui_map_icon2.y * bairitu, g_imghandles.ui_map_icon[commu_data_map[i].character_icon - 1], TRUE);
#pragma endregion
			#pragma region ver0.0081制作時コメント化コード
			//DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], draw_map_coordinate_hukidasi_x[i] + size_ui_map_hukidasi[0].x, draw_map_coordinate_hukidasi_y[i] + size_ui_map_hukidasi[0].y, g_imghandles.ui_map_hukidasi[0], TRUE);
			//DrawExtendGraphF(draw_map_character_icon_x[i], draw_map_character_icon_y[i], draw_map_character_icon_x[i] + size_ui_map_icon2.x, draw_map_character_icon_y[i] + size_ui_map_icon2.y, g_imghandles.ui_map_icon[commu_data_map[i].character_icon - 1], TRUE);
#pragma endregion
			#pragma region ver0.00904制作時コメント化コード
			//DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], draw_map_coordinate_hukidasi_x[i] + image_icon_map_character[0].GetSizeX(), draw_map_coordinate_hukidasi_y[i] + image_icon_map_character[0].GetSizeY(), image_icon_map_character[commu_data_map[i].character_icon - 1].GetHandle(), TRUE);
#pragma endregion
			DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], draw_map_coordinate_hukidasi_x[i] + image_icon_map_character[(commu_data_map[i].GetID() == static_cast<int>(CommuType::FRIEND) + 1) ? static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 5 : 0].GetSizeX(), draw_map_coordinate_hukidasi_y[i] + image_icon_map_character[0].GetSizeY(), image_icon_map_character[commu_data_map[i].character_icon - 1].GetHandle(), TRUE);
		}
	}

	#pragma region ver0.0039制作時コメント化コード
	//DrawExtendGraphF(screen_size_x - size_ui_tips.x * bairitu, 0, WINDOW_SIZE_X * bairitu, size_ui_tips.y * bairitu, g_imghandles.ui_tips, TRUE);	// tipsＵＩ

	//// 動作テスト
	//for (int i = 0; i < 2; i++){ DrawFormatStringFToHandle(tips_string[i].x, 50, GetColor(0, 0, 0), g_font_tips, tips_string[i].string); }

	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.ui_month, TRUE);	// 月ＵＩ
#pragma endregion
	DrawExtendGraphF(screen_size_x - size_ui_tips.x * bairitu, 0, WINDOW_SIZE_X * bairitu, size_ui_tips.y * bairitu, g_imghandles.ui_tips, TRUE);	// tipsＵＩ
	#pragma region ver0.00391制作時コメント化コード

	//for (int i = 0; i < 2; i++) { DrawFormatStringFToHandle(tips_string[i].x, 50, GetColor(0, 0, 0), g_font_tips, tips_string[i].string); }

#pragma endregion
	for (int i = 0; i < 2; i++) { DrawFormatStringFToHandle(tips_string[i].x, bairitu * 24, GetColor(0, 0, 0), g_font_tips, tips_string[i].string); }
	#pragma region ver0.00706制作時コメント化コード
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.ui_month, TRUE);	// 月ＵＩ
#pragma endregion
	// 現在月ＵＩ
	if (GlobalStaticVariable::GetModeTrial() == FALSE) { ui_map_month[game_week_number - 12].DrawImage(); }
	else { bgimage_non_month.DrawImage(); }
	// 矢印
	//DrawStringFToHandle(map_arrow_left_x, screen_size_y / 2.0f, "←", DrawTitleStringColor(map_arrow_left_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("←", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	if (map_move_commu_check == FALSE)
	{
		#pragma region ver0.0038制作時コメント化コード
		//if (g_map_destination != MAP_DESTINATION_LEFT){ DrawStringFToHandle(map_arrow_left_x, screen_size_y / 2.0f, "←", DrawTitleStringColor(map_arrow_left_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("←", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
		//if (g_map_destination != MAP_DESTINATION_RIGHT){ DrawStringFToHandle(map_arrow_right_x, screen_size_y / 2.0f, "→", DrawTitleStringColor(map_arrow_right_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("→", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
#pragma endregion
		// 矢印を動かすために必要な絶対数？
		#pragma region ver0.0051制作時コメント化コード
		//float x = 22.5f - (progress_frame % 45) * bairitu;
#pragma endregion
		#pragma region ver0.0053制作時コメント化コード
		//float x = (22.5f - (progress_frame % 45)) * bairitu;

		//if (g_map_destination != MAP_DESTINATION_LEFT) { DrawStringFToHandle(map_arrow_left_x - abs(x), screen_size_y / 2.0f, "←", DrawTitleStringColor(map_arrow_left_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("←", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
		//if (g_map_destination != MAP_DESTINATION_RIGHT) { DrawStringFToHandle(map_arrow_right_x + abs(x), screen_size_y / 2.0f, "→", DrawTitleStringColor(map_arrow_right_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("→", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
#pragma endregion
		if (g_map_destination != MAP_DESTINATION_LEFT) { hjimage_map[0].DrawImage(); }
		if (g_map_destination != MAP_DESTINATION_RIGHT) { hjimage_map[1].DrawImage(); }
	}
	// コミュ移動確認ＵＩ
	if (map_move_commu_check == TRUE)
	{ 
		#pragma region ver0.013制作時コメント化コード
		const float X = (screen_size_x - bairitu * size_ui_map_check.x) / 2;
		const float Y = (screen_size_y - bairitu * size_ui_map_check.y) / 2;
		DrawExtendGraphF(X, Y, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, g_imghandles.ui_map_check, TRUE); 
#pragma endregion
		// 影
		//const float Z = bairitu * 495;
		//const float A = bairitu * 270;
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		//DrawFormatStringFToHandle(Z + bairitu * 3, A + bairitu * 3, GetColor(20, 20, 20), font[static_cast<int>(FontData::Type::MAP_TITLE)].GetHandle(), commu_data_map_choice.GetTitle());
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// サブタイトル
		//DrawFormatStringFToHandle(Z, A, GetColor(255, 255, 255), font[static_cast<int>(FontData::Type::MAP_TITLE)].GetHandle(), commu_data_map_choice.GetTitle());

		#pragma region ver0.0042制作時コメント化コード
		//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_icon.x) / 2, (screen_size_y - bairitu * size_ui_map_icon.y) / 2 - bairitu * 150, (screen_size_x + bairitu * size_ui_map_icon.x) / 2, (screen_size_y + bairitu * size_ui_map_icon.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[commu_data_map_choice.character_icon - 1], TRUE);	// アイコン（仮）
#pragma endregion
		#pragma region ver0.0081制作時コメント化コード
		//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_icon2.x) / 2, (screen_size_y - bairitu * size_ui_map_icon2.y) / 2 - bairitu * 150, (screen_size_x + bairitu * size_ui_map_icon2.x) / 2, (screen_size_y + bairitu * size_ui_map_icon2.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[commu_data_map_choice.character_icon - 1], TRUE);	// アイコン（仮）
#pragma endregion
		// フレンドめぐるコミュの場合５人のアイコンを表示させる
		#pragma region ver0.013制作時コメント化コード
		if (commu_data_map_choice.GetID() != static_cast<int>(CommuType::FRIEND) + 1)
		{
			DrawExtendGraphF((screen_size_x - size_ui_map_icon2.x) / 2, (screen_size_y - size_ui_map_icon2.y) / 2 - bairitu * 150, (screen_size_x + size_ui_map_icon2.x) / 2, (screen_size_y + size_ui_map_icon2.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[commu_data_map_choice.character_icon - 1], TRUE);	// アイコン（仮）
		}
		else
		{
			// ５人全員のアイコンを表示させる
			for (int i = 0; i < 5; i++)
			{
				// アイコンのずれ
				const float X = (i - 2) * bairitu * 108;

				DrawExtendGraphF((screen_size_x - size_ui_map_icon2.x) / 2 + X,
					(screen_size_y - size_ui_map_icon2.y) / 2 - bairitu * 150,
					(screen_size_x + size_ui_map_icon2.x) / 2 + X, (screen_size_y + size_ui_map_icon2.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[i], TRUE);	// アイコン（仮）
			}
		}
#pragma endregion
		//if (commu_data_map_choice.GetID() != static_cast<int>(CommuType::FRIEND) + 1) { image_map_question[commu_data_map_choice.character_icon - 1].DrawImage(); }
		//else { image_map_question[static_cast<int>(ImgDataMapQuestion::Type::FRIEND_ALL)].DrawImage(); }
		#pragma region ver0.0081制作時コメント化コード
		//for (int i = 0; i < 2; i++){ DrawExtendGraphF(draw_map_commu_choice_x[i], draw_map_commu_choice_y, draw_map_commu_choice_x[i] + size_ui_map_check_choice.x * bairitu, draw_map_commu_choice_y + size_ui_map_check_choice.y * bairitu, g_imghandles.ui_map_check_choice[i], TRUE); }
#pragma endregion
		// 選択肢アイコン
		for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].DrawImage(); }
		//for (int i = 0; i < 2; i++) { image_icon_map_move_alternative[i].DrawImage(); }
		// デバッグ用当たり判定
		//image_icon_map_collision_detection.DrawImage();
	}
	// セーブ・ロードアイコン
	for(int i = 2; i < 4; i++){hjimage_map[i].DrawImage(); }
}
// 対応するキャラコミュが出現するかチェックする
BOOL GameMapUpperCheck(int x, int y)	// キャラクター,コミュＩＤ
{
	// フレンドＣＧコミュ
	//if (game_week_number == 17)
	//{
	//	if (y == COMMU_TYPE_FRIEND) { return TRUE; }
	//}
	//// 個別コミュ
	//else if (x != 0 && x < 6)
	if (x != 0 && x < 6)
	{
		// タイミング次第で表示するコミュ
		switch (CommuData::GetGMapUpperType())
		{
		case CommuData::MapUpperType::MEGURU0:	if (x == 1) { return TRUE; }	break;
		case CommuData::MapUpperType::KOGANE0:	if (x == 2) { return TRUE; }	break;
		case CommuData::MapUpperType::JURI0:	if (x == 3) { return TRUE; }	break;
		case CommuData::MapUpperType::RINZE0:	if (x == 4) { return TRUE; }	break;
		case CommuData::MapUpperType::CHIYUKI0:	if (x == 5) { return TRUE; }	break;
		case CommuData::MapUpperType::FRIEND_CG_MEGURU:							break;
		default:								return TRUE;					break;
		}
	}
	return FALSE;
}
// マップアイコンクリック確認用関数
BOOL GameMapControlCommuCheck(BOOL x)	// 処理タイミング（TRUEなら押した時）
{
	if (map_move_commu_check == FALSE)
	{
		for (int i = 0; i < COMMU_MAP_LIMIT; i++)
		{
			const int Y = (commu_data_map[i].GetID() == static_cast<int>(CommuType::FRIEND) + 1) ? static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 5 : 0;
			if (x == TRUE)
			{
				#pragma region ver0.0081制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x[i], draw_map_character_icon_y[i], size_ui_map_icon2.x * bairitu, size_ui_map_icon2.y * bairitu, TRUE, FALSE) == TRUE)
#pragma endregion
				#pragma region ver0.00904制作時コメント化コード
//if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[0].GetSizeX(), image_icon_map_character[0].GetSizeY(), TRUE, FALSE) == TRUE)
#pragma endregion
				if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[Y].GetSizeX(), image_icon_map_character[0].GetSizeY(), TRUE, FALSE) == TRUE)
				{
					cfgm_commu_check[i] = TRUE;
					return TRUE;
				}
			}
			else
			{
				#pragma region ver0.00393制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x[i], draw_map_character_icon_y[i], size_ui_map_icon.x, size_ui_map_icon.y, FALSE, cfgm_commu_check[i]) == TRUE)
#pragma endregion
				#pragma region ver0.0081制作時コメント化コード
//if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x[i], draw_map_character_icon_y[i], size_ui_map_icon2.x, size_ui_map_icon2.y, FALSE, cfgm_commu_check[i]) == TRUE && map_move_commu_check == FALSE)
#pragma endregion
				#pragma region ver0.00904制作時コメント化コード
//if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[0].GetSizeX(), image_icon_map_character[0].GetSizeY(), FALSE, cfgm_commu_check[i]) == TRUE && map_move_commu_check == FALSE)
#pragma endregion
				if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[Y].GetSizeX(), image_icon_map_character[0].GetSizeY(), FALSE, cfgm_commu_check[i]) == TRUE && map_move_commu_check == FALSE)
				{
					map_move_commu_check = TRUE;
					// 選択用コミュステータスに必要な要素を代入する
					commu_data_map_choice.id = commu_data_map[i].id;
					commu_data_map_choice.SetTitle(commu_data_map[i].GetTitle());
					commu_data_map_choice.character_icon = commu_data_map[i].character_icon;
					// ＳＥを鳴らす
					SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));

					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

#include "soundroom.h"

// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfsr=click_flag_sound_room）
BOOL cfsr_play_music[SR_BGM_ALTERNATIVE_NUMBER];	// ＢＧＭを再生する
BOOL cfsr_play_se[SE_NUMBER + 1];	// ＳＥを再生する（バグが起きないか要確認）
BOOL cfsr_move_title = FALSE;		// タイトル画面へ移動
BOOL cfsr_bgm_down = FALSE;			// ＢＧＭ音量を下げる
BOOL cfsr_bgm_up = FALSE;			// ＢＧＭ音量を上げる
BOOL cfsr_se_down = FALSE;			// ＳＥ音量を下げる
BOOL cfsr_se_up = FALSE;			// ＳＥ音量を上げる

float sound_room_coordinate_alternative_x[SR_BGM_ALTERNATIVE_NUMBER];	// BGM選択肢基本x座標
float sound_room_coordinate_alternative_y[SR_BGM_ALTERNATIVE_NUMBER];	// BGM選択肢基本y座標
float sound_room_coordinate_alternative_se_x[SE_NUMBER + 1];	// ＳＥ選択肢基本x座標
float sound_room_coordinate_alternative_se_y[SE_NUMBER + 1];	// ＳＥ選択肢基本y座標（バグが起きないか要確認）
float sound_room_size_alternative_x = 0;						// BGM選択肢基本x幅
float sound_room_size_alternative_y = 0;						// BGM選択肢基本y幅
float sound_room_coordinate_string_title_x = 0;					// 『TITLE』x座標
float sound_room_coordinate_string_title_y = 0;					// 『TITLE』y座標
float sound_room_coordinate_bgm_message_y = 0;					// BGM音量関係Y座標
float sound_room_coordinate_bgm_volume_up_x = 0;				// BGM『→』文字X座標
float sound_room_coordinate_bgm_volume_up_y = 0;				// BGM『→』文字Y座標
float sound_room_coordinate_se_message_y = 0;					// SE音量関係Y座標
float sound_room_coordinate_se_volume_up_x = 0;					// SE『→』文字X座標
float sound_room_coordinate_se_volume_up_y = 0;					// SE『→』文字Y座標
// SoundRoom状態のメイン処理
void SoundRoom()
{
	SoundRoomControl();
	DrawSoundRoom();
}
// コミュ画面操作処理
void SoundRoomControl()
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
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_bgm_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_bgm_up = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_se_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_se_up = TRUE; }
				// ＢＧＭ選択肢
				for (int i = 0; i < SR_BGM_ALTERNATIVE_NUMBER; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_x[i], sound_room_coordinate_alternative_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, TRUE, FALSE) == TRUE) { cfsr_play_music[i] = TRUE; }
				}
				// ＳＥ選択肢
				for (int i = 0; i < SEData::GetNumber() + 1; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, TRUE, FALSE) == TRUE){ cfsr_play_se[i] = TRUE; }
				}
				// 『TITLE』文字列
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfsr_move_title = TRUE; }
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				// 音量を下げる
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_bgm_down) == TRUE)
				{
					bgm_volume -= 5;
					ChangeBGMVolume();
				}
				// 音量を上げる
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_bgm_up) == TRUE)
				{
					bgm_volume += 5;
					ChangeBGMVolume();
				}
				// ＳＥ音量を下げる
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("←", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_se_down) == TRUE) 
				{
					se_volume -= 5;
					ChangeSEVolume();
				}
				// ＳＥ音量を上げる
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("→", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_se_up) == TRUE) 
				{
					se_volume += 5;
					ChangeSEVolume();
				}
				// 音量変動によって下（上）限値を過ぎた場合、修正する
				if (bgm_volume < 0) { bgm_volume = 0; }
				else if (bgm_volume > 100) { bgm_volume = 100; }
				if (se_volume < 0) { se_volume = 0; }
				else if (se_volume > 100) { se_volume = 100; }
				// ＢＧＭを再生する（プロトタイプ）
				#pragma region ver0.0051制作時コメント化コード
				for (int i = 0; i < SR_BGM_ALTERNATIVE_NUMBER; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_x[i], sound_room_coordinate_alternative_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, FALSE, cfsr_play_music[i]) == TRUE){ MusicPlay(i - 1); }
				}
				// ＳＥを再生（、停止）する（プロトタイプ）
				for (int i = 0; i < SEData::GetNumber() + 1; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, FALSE, cfsr_play_se[i]) == TRUE)
					{ 
						if(i == 0){ SEPlay(-2); }
						else{ SEPlay(i - 1); }
					}
				}
				// タイトル画面に戻る
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_move_title) == TRUE){ GameTitleNext(); }
				// 全てのフラグを戻す
				for (int i = 0; i < BGM_NUMBER; i++){ cfsr_play_music[i] = FALSE; }	// ＢＧＭを再生する
				for (int i = 0; i < SEData::GetNumber() + 1; i++){ cfsr_play_se[i] = FALSE; }	// ＳＥを再生する
				cfsr_move_title = FALSE;											// タイトル画面へ移動
				cfsr_bgm_down = FALSE;												// ＢＧＭ音量を下げる
				cfsr_bgm_up = FALSE;												// ＢＧＭ音量を上げる
				cfsr_se_down = FALSE;												// ＳＥ音量を下げる
				cfsr_se_up = FALSE;													// ＳＥ音量を上げる
			}
		}
	}
	/* マウスホイール関係 ---------*/
}
// サウンドルーム画面で使う様々な座標を（再）定義する
void SoundRoomCoordinateSetting()
{
	// 文字代入テスト
	for (int i = -1; i < BGM_NUMBER; i++) { i == -1 ? music_string_stop.NameChange(i) : music_string[i].NameChange(i); }
	// BGM関係選択肢座標
	sound_room_size_alternative_x = 330 * bairitu;																						// BGM選択肢基本x幅
	sound_room_size_alternative_y = 35 * bairitu;																						// BGM選択肢基本y幅
	// ＢＧＭ関係選択肢座標
	for (int i = 0; i < SR_BGM_ALTERNATIVE_NUMBER; i++)
	{
		sound_room_coordinate_alternative_x[i] = sound_room_size_alternative_x * (i % 2 == 0 ? 0 : 1.0f) + 400 * bairitu;	// BGM選択肢基本x座標
		sound_room_coordinate_alternative_y[i] = 100 * bairitu + sound_room_size_alternative_y * (i / 2);// BGM選択肢基本y座標
	}
	// ＳＥ関係選択肢座標
	for (int i = 0; i < SEData::GetNumber() + 1; i++)
	{
		sound_room_coordinate_alternative_se_x[i] = sound_room_coordinate_alternative_x[0] + sound_room_size_alternative_x * (i % 2 == 0 ? 2.5f : 3.5f);
		sound_room_coordinate_alternative_se_y[i] = 100 * bairitu + sound_room_size_alternative_y * (i / 2); // SE選択肢基本y座標
	}
	// 『TITLE』文字列
	sound_room_coordinate_string_title_x = 90 * bairitu;
	sound_room_coordinate_string_title_y = 180 * bairitu;
	// 『BGM音量』文字列
	sound_room_coordinate_bgm_message_y = 250 * bairitu;
	sound_room_coordinate_bgm_volume_up_x = sound_room_coordinate_string_title_x + bairitu * 130;
	sound_room_coordinate_bgm_volume_up_y = 40 * bairitu + sound_room_coordinate_bgm_message_y;
	// 『SE音量』文字列
	sound_room_coordinate_se_message_y = 330 * bairitu;
	sound_room_coordinate_se_volume_up_x = sound_room_coordinate_string_title_x + bairitu * 130;
	sound_room_coordinate_se_volume_up_y = 40 * bairitu + sound_room_coordinate_se_message_y;
}
// サウンドルームの描画処理
void DrawSoundRoom()
{
	DrawStringFToHandle(90 * bairitu, 100 * bairitu, "SoundRoom", GetColor(255, 255, 255), g_font3);
	// BGMボタン（プロトタイプ）
	for (int i = -1; i < BGM_NUMBER; i++)
	{
		int color_x = (i + 2) / 2 % 2 == 1 ? GetColor(128, 128, 128) : GetColor(0, 225, 225);	// 奇数個目は灰色、偶数個目は水色
		DrawBoxAA(sound_room_coordinate_alternative_x[i + 1], sound_room_coordinate_alternative_y[i + 1], sound_room_coordinate_alternative_x[i + 1] + sound_room_size_alternative_x - 1, sound_room_coordinate_alternative_y[i + 1] + sound_room_size_alternative_y - 1, color_x, TRUE);
		if(i == -1)
		{ 
			DrawFormatStringFToHandle(sound_room_coordinate_alternative_x[i + 1], sound_room_coordinate_alternative_y[i + 1] + bairitu * 10, GetColor(255, 255, 255), g_font3, music_string_stop.name);	// 文字
		}
		else
		{
			DrawFormatStringFToHandle(sound_room_coordinate_alternative_x[i + 1], sound_room_coordinate_alternative_y[i + 1] + bairitu * 10, GetColor(255, 255, 255), g_font3, music_string[i].name);	// 文字
		}
	}
	// ＳＥボタン（プロトタイプ）
	for (int i = 0; i < SEData::GetNumber() + 1; i++)
	{
		int color_x = (i + 1) / 2 % 2 == 1 ? GetColor(128, 128, 128) : GetColor(0, 225, 225);	// 奇数個目は灰色、偶数個目は水色（偶数行目は入れ替わる）
		DrawBoxAA(sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i], sound_room_coordinate_alternative_se_x[i] + sound_room_size_alternative_x - 1, sound_room_coordinate_alternative_se_y[i] + sound_room_size_alternative_y - 1, color_x, TRUE);
		DrawFormatStringFToHandle(sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i] + bairitu * 10, GetColor(255, 255, 255), g_font3, i == 0 ? "SE停止" : se[i - 1].GetName());	// 文字
	}
	// 『TITLE』
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, "TITLE", DrawTitleStringColor(sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, GetDrawStringWidthToHandle("TITLE", 5, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	// 『ＢＧＭ』
	DrawStringFToHandle(sound_room_coordinate_alternative_x[0], sound_room_coordinate_alternative_y[0] - bairitu * 30, "ＢＧＭ", GetColor(255, 255, 255), g_font3);
	// 『ＳＥ』
	DrawStringFToHandle(sound_room_coordinate_alternative_se_x[0], sound_room_coordinate_alternative_y[0] - bairitu * 30, "ＳＥ", GetColor(255, 255, 255), g_font3);
	// 『BGM音量』
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_message_y, "BGM音量", GetColor(255, 255, 255), g_font3);
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, "←", DrawTitleStringColor(sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, GetDrawStringWidthToHandle("←", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	DrawFormatStringFToHandle((sound_room_coordinate_string_title_x + sound_room_coordinate_bgm_volume_up_x + GetDrawStringWidthToHandle("→", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d％", bgm_volume) / 2, sound_room_coordinate_bgm_volume_up_y, GetColor(255, 255, 255), g_font3, "%d％", bgm_volume);
	DrawStringFToHandle(sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, "→", DrawTitleStringColor(sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, GetDrawStringWidthToHandle("→", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	// 『SE音量』
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_se_message_y, "SE音量", GetColor(255, 255, 255), g_font3);
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, "←", DrawTitleStringColor(sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, GetDrawStringWidthToHandle("←", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	DrawFormatStringFToHandle((sound_room_coordinate_string_title_x + sound_room_coordinate_se_volume_up_x + GetDrawStringWidthToHandle("→", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d％", se_volume) / 2, sound_room_coordinate_se_volume_up_y, GetColor(255, 255, 255), g_font3, "%d％", se_volume);
	DrawStringFToHandle(sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, "→", DrawTitleStringColor(sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, GetDrawStringWidthToHandle("→", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
}

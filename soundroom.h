#ifndef __SOUNDROOM_H__
#define __SOUNDROOM_H__

#include <DxLib.h>
#include "main.h"

#define SR_BGM_ALTERNATIVE_NUMBER 34 + 1	// サウンドルーム内でのＢＧＭ選択肢数（『BGM_NUMBER + 1』）

// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfsr=click_flag_sound_room）
extern BOOL cfsr_play_music[];	// ＢＧＭを再生する（バグが起きないか要確認）
extern BOOL cfsr_play_se[];		// ＢＧＭを再生する（バグが起きないか要確認）
extern BOOL cfsr_move_title;	// タイトル画面へ移動
extern BOOL cfsr_bgm_down;		// ＢＧＭ音量を下げる
extern BOOL cfsr_bgm_up;		// ＢＧＭ音量を上げる
extern BOOL cfsr_se_down;		// ＳＥ音量を下げる
extern BOOL cfsr_se_up;			// ＳＥ音量を上げる

extern float sound_room_coordinate_alternative_x[];		// BGM選択肢基本x座標
extern float sound_room_coordinate_alternative_y[];		// BGM選択肢基本y座標（バグが起きないか要確認）
extern float sound_room_coordinate_alternative_se_x[];	// ＳＥ選択肢基本x座標
extern float sound_room_coordinate_alternative_se_y[];	// ＳＥ選択肢基本y座標（バグが起きないか要確認）
extern float sound_room_size_alternative_x;				// BGM選択肢基本x幅
extern float sound_room_size_alternative_y;				// BGM選択肢基本y幅
extern float sound_room_coordinate_string_title_x;		// 『TITLE』x座標
extern float sound_room_coordinate_string_title_y;		// 『TITLE』y座標
extern float sound_room_coordinate_bgm_message_y;		// BGM音量関係Y座標
extern float sound_room_coordinate_bgm_volume_up_x;		// BGM『→』文字X座標
extern float sound_room_coordinate_bgm_volume_up_y;		// BGM『→』文字Y座標
extern float sound_room_coordinate_se_message_y;		// SE音量関係Y座標
extern float sound_room_coordinate_se_volume_up_x;		// SE『→』文字X座標
extern float sound_room_coordinate_se_volume_up_y;		// SE『→』文字Y座標

void SoundRoom();					// SoundRoom状態のメイン処理
void SoundRoomControl();			// サウンドルーム画面操作処理
void SoundRoomCoordinateSetting();	// サウンドルーム画面で使う様々な座標を（再）定義する
void DrawSoundRoom();				// サウンドルームの描画処理

#endif

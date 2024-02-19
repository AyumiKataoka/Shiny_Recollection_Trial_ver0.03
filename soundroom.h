#ifndef __SOUNDROOM_H__
#define __SOUNDROOM_H__

#include <DxLib.h>
#include "main.h"

#define SR_BGM_ALTERNATIVE_NUMBER 34 + 1	// サウンドルーム内でのＢＧＭ選択肢数（『BGM_NUMBER + 1』）

// ＳＥタイトルデータ
#pragma region ver0.00607制作時コメント化コード
//class SEStringData
//{
//public:
//	char* name;
//	void NameChange(int x)
//	{
//		switch (x)
//		{
//		#pragma region ver0.0026制作時コメント化コード
//		//case 0:		name = "（ループ）ＳＥ停止";					break;
//		//case 1:		name = "ウィンドチャイム";						break;
//		//case 2:		name = "拍手（一人）";							break;
//		//case 3:		name = "拍手（大勢）";							break;
//		//case 4:		name = "チャイム";								break;
//		//case 5:		name = "ドリブル";								break;
//		//case 6:		name = "足音";									break;
//		//case 7:		name = "カーテンを開ける";						break;
//		//case 8:		name = "店のドアを開ける";						break;
//		//case 9:		name = "引き戸を開ける";						break;
//		//case 10:	name = "ノック";								break;
//		//case 11:	name = "鳥のさえずり";							break;
//		//case 12:	name = "風";									break;
//		//case 13:	name = "選択肢を決定する";						break;
//		//case 14:	name = "川の水の流れの音";						break;
//		//case 15:	name = "川の流れの音 Long Ver";					break;
//		//case 16:	name = "布が擦れる";							break;
//		//case 17:	name = "バスケットボールゴール";				break;
//		//case 18:	name = "人と人とがぶつかる";					break;
//		//case 19:	name = "猫の鳴き声";							break;
//		//case 20:	name = "マップを移動するＳＥ";					break;
//		//case 21:	name = "ハイタッチ";							break;
//		//case 22:	name = "手を叩く音";							break;
//		//case 23:	name = "部活動中の生徒たちの声";				break;
//		//case 24:	name = "部活動中の声Long  Ver";					break;
//		//case 25:	name = "シューズの音";							break;
//		//case 26:	name = "キーボード";							break;
//		//case 27:	name = "紙が散らばる音";						break;
//		//case 28:	name = "携帯　通知";							break;
//		//case 29:	name = "椅子を立つ音";							break;
//		//case 30:	name = "ガタガタとした物音";					break;
//		//case 31:	name = "携帯　着信音";							break;
//		//default:	name = "";										break;
//#pragma endregion
//		case 0:		name = (char*)"（ループ）ＳＥ停止";		break;
//		case 1:		name = (char*)"ウィンドチャイム";		break;
//		case 2:		name = (char*)"拍手（一人）";			break;
//		case 3:		name = (char*)"拍手（大勢）";			break;
//		case 4:		name = (char*)"チャイム";				break;
//		case 5:		name = (char*)"ドリブル";				break;
//		case 6:		name = (char*)"足音";					break;
//		case 7:		name = (char*)"足音（ループ）";			break;
//		case 8:		name = (char*)"カーテンを開ける";		break;
//		case 9:		name = (char*)"店のドアを開ける";		break;
//		case 10:	name = (char*)"引き戸を開ける";			break;
//		case 11:	name = (char*)"ノック";					break;
//		case 12:	name = (char*)"鳥のさえずり";			break;
//		case 13:	name = (char*)"風";						break;
//		case 14:	name = (char*)"選択肢を決定する";		break;
//		case 15:	name = (char*)"川の水の流れの音";		break;
//		case 16:	name = (char*)"川の流れの音 Long Ver";	break;
//		case 17:	name = (char*)"布が擦れる";				break;
//		case 18:	name = (char*)"バスケットボールゴール";	break;
//		case 19:	name = (char*)"人と人とがぶつかる";		break;
//		case 20:	name = (char*)"猫の鳴き声";				break;
//		case 21:	name = (char*)"マップを移動するＳＥ";	break;
//		case 22:	name = (char*)"ハイタッチ";				break;
//		case 23:	name = (char*)"手を叩く音";				break;
//		case 24:	name = (char*)"部活動中の生徒たちの声";	break;
//		case 25:	name = (char*)"部活動中の声Long  Ver";	break;
//		case 26:	name = (char*)"シューズの音";			break;
//		case 27:	name = (char*)"キーボード";				break;
//		case 28:	name = (char*)"紙が散らばる音";			break;
//		case 29:	name = (char*)"携帯　通知";				break;
//		case 30:	name = (char*)"椅子を立つ音";			break;
//		case 31:	name = (char*)"ガタガタとした物音";		break;
//		case 32:	name = (char*)"携帯　着信音";			break;
//		case 33:	name = (char*)"アイコンを押した音";		break;
//		case 34:	name = (char*)"揚げ物をする音";			break;
//		case 35:	name = (char*)"フラッシュバック";		break;
//		case 36:	name = (char*)"思い出す音";				break;
//		case 37:	name = (char*)"開き戸の音";				break;
//		case 38:	name = (char*)"ガサガサ";				break;
//		case 39:	name = (char*)"駆ける足音";				break;
//		case 40:	name = (char*)"窓を開ける音";			break;
//		case 41:	name = (char*)"文字を書く";				break;
//		case 42:	name = (char*)"文字を書く(LOOP)";		break;
//		case 43:	name = (char*)"静かに戸を開く";			break;
//		case 44:	name = (char*)"椅子に座る";				break;
//		case 45:	name = (char*)"セミの声";				break;
//		case 46:	name = (char*)"セミの声(LOOP)";			break;
//		case 47:	name = (char*)"水道を開く";				break;
//		case 48:	name = (char*)"水道を止める音";			break;
//		case 49:	name = (char*)"場面転換IN";				break;
//		case 50:	name = (char*)"場面転換OUT";			break;
//		case 51:	name = (char*)"スタート画面選択";		break;
//		case 52:	name = (char*)"Start";					break;
//		case 53:	name = (char*)"水道の音";				break;
//		case 54:	name = (char*)"水道の音(LOOP)";			break;
//		default:	name = (char*)"";						break;
//		}
//	}
//};
//extern SEStringData se_string[];
#pragma endregion

// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfsr=click_flag_sound_room）
extern BOOL cfsr_play_music[];	// ＢＧＭを再生する（バグが起きないか要確認）
extern BOOL cfsr_play_se[];		// ＢＧＭを再生する（バグが起きないか要確認）
extern BOOL cfsr_move_title;	// タイトル画面へ移動
extern BOOL cfsr_bgm_down;		// ＢＧＭ音量を下げる
extern BOOL cfsr_bgm_up;		// ＢＧＭ音量を上げる
extern BOOL cfsr_se_down;		// ＳＥ音量を下げる
extern BOOL cfsr_se_up;			// ＳＥ音量を上げる

#pragma region ver0.00391制作時コメント化コード
//extern float sound_room_coordinate_alternative_x;		// BGM選択肢基本x座標
#pragma endregion
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

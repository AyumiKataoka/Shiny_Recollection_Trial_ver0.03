/*
●デバッグはよほど特別な事がない限り（Ｂキー＋特定のキー）で自由に発動できるようにした方が楽なのでは？
*/

#include "debugprogram.h"
BOOL GlobalStaticDebug::log = FALSE;

int debug_local_int[2];	// ローカル変数代入用変数（int）

double debug_local_double_1 = 0;	// ローカル変数代入用変数（double）
//フラグ
BOOL debug_load = FALSE;				// セーブデータロードとは別の情報をロード（上書き）する
BOOL debug_window = FALSE;				// ウィンドウ解像度を変更する
BOOL debug_bgm_load_cut = FALSE;		// ＢＧＭのロードを行わないようにする
BOOL debug_character_load_cut = FALSE;	// 立ち絵のロードを行わないようにする
BOOL debug_escape_check = TRUE;			// エスケープキーの入力で強制終了させる
BOOL debug_keyboard = FALSE;			// キーボードに応じたデバッグ処理を行う
BOOL debug_message = FALSE;				// 状態に応じたメッセージを出力する
BOOL debug_not_production = FALSE;		// 餃子の生産力を０にする
BOOL debug_hit_judge = FALSE;			// 当たり判定を表示する
BOOL debug_entrance_before = FALSE;		// 入学前コミュ撮影モードにする
BOOL debug_dialog_through = TRUE;		// 解像度ダイアログボックス処理を無視して指定した解像度にする
// デバッグプログラム共通処理
void DebugProgram(DebugType x)
{
	// デバッグモードでないなら何も起きない 
	if (mode_debug == TRUE)
	{
		switch (x)
		{
		case DEBUG_MAIN:
			DebugEscapeCheck();
			DebugProgramControl();
			DebugMessage();
			break;
		case DEBUG_LOAD:
			DebugLoad();
			//DebugWindowChange();
			break;
		default:
			break;
		}
	}
}
// セーブデータとは別の情報をロード（上書き）する
void DebugLoad()
{
	if (debug_load == TRUE)
	{
	}
}
// ウィンドウ解像度を変更する
void DebugWindowChange()
{
	#pragma region ver0.0041制作時コメント化コード
	//if(debug_window == TRUE)
	//{ 
	//	screen_size_x = 1280;
	//	screen_size_y = 720;
	//	bairitu = (float)screen_size_y / WINDOW_SIZE_Y;	// 文字や画像の倍率を再定義する
	//}
#pragma endregion
	if (debug_dialog_through == TRUE) { flag_full_hd_now = FALSE; }	// 指定した方のウィンドウサイズにする
}
// E＋Xキーの入力で強制終了させる
void DebugEscapeCheck()
{
	if (debug_escape_check == TRUE)
	{
		#pragma region ver0.0042制作時コメント化コード
		//if (CheckHitKey(KEY_INPUT_E) == 1) { quit_game = TRUE; }
#pragma endregion
		if (CheckHitKey(KEY_INPUT_E) == 1 && CheckHitKey(KEY_INPUT_X) == 1) { quit_game = TRUE; }
	}
}
// デバッグモード中の操作処理
void DebugProgramControl()
{
	// オンオフ
	if (CheckHitKey(KEY_INPUT_D) == TRUE && CheckHitKey(KEY_INPUT_B) == TRUE)
	{ 
		debug_keyboard = TRUE; 
		for (int i = 0; i < 3; i++)
		{
			//GameMainCommunicationNext(COMMU_TYPE_CHIYUKI1, FALSE, 0);
			commu_character[i] = 0;
		}
	}
	if (CheckHitKey(KEY_INPUT_0) == TRUE)
	{
		debug_keyboard = FALSE;
	}
	if (debug_keyboard == TRUE)
	{
		if (CheckHitKey(KEY_INPUT_1) == TRUE){ GameMapNext(); }
		// 入学前コミュ撮影モードオンオフ
		if (CheckHitKey(KEY_INPUT_2) == TRUE && CheckHitKey(KEY_INPUT_O) == TRUE)
		{
			debug_entrance_before = TRUE;	// 特定のＵＩが非表示になる
			GameMainCommunicationAuto();
			// ＯＰ画面のＢＧＭを止める
			if(g_gamestate == GAME_TITLE){g_bgmstate[BN_TITLE].state = BGM_STOP; }
		}
		else if (CheckHitKey(KEY_INPUT_2) == TRUE && CheckHitKey(KEY_INPUT_N) == TRUE)
		{ 
			debug_entrance_before = FALSE;
			g_commuauto = COMMU_AUTO_NORMAL;
		}
		// セーブテスト
		if (CheckHitKey(KEY_INPUT_S) == TRUE) { GameSave(0); }
		// ロードテスト
		if (CheckHitKey(KEY_INPUT_L) == TRUE) { GameLoad(0); }
		
		if (g_gamestate == GAME_MAIN_COMMUNICATION)
		{
			// コミュ終了（COMMU END）
			if(CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_E) == 1){commu_before_cs == FALSE ? GameMainCommunicationEnd() : GameCommuSelectNext();}
			// 体験版終了コミュへ移動
			else if (CheckHitKey(KEY_INPUT_Q) == 1) { GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL_END), FALSE, 0); }
		}
	}
	// デバッグログのページ数変更
	if (TextLog::GetMode() == TRUE)
	{
		int key = GetJoypadInputState(DX_INPUT_KEY);
	}
	// デバッグメッセージオンオフ
	if((CheckHitKey(KEY_INPUT_M) == TRUE || CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) && CheckHitKey(KEY_INPUT_O) == TRUE){ debug_message = TRUE; }
	else if ((CheckHitKey(KEY_INPUT_M) == TRUE || CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) && CheckHitKey(KEY_INPUT_N) == TRUE){ debug_message = FALSE; }
}
// ログ関係の処理
void DebugLog(LogOutputType x)
{
	if (GlobalStaticDebug::GetLog() == TRUE)
	{
		char c[256];
		switch (x)
		{
		case LogOutputType::LOAD_FLAG:
			sprintf_s(c, 256, "キャラを読み込まないデバッグフラグ：%d、デバッグフラグ：%d\n", debug_character_load_cut, mode_debug);
			break;
		case LogOutputType::LOAD_CHECK:		sprintf_s(c, 256, "キャラ画像数：%d、ポーズ数：%d、衣装画像数：%d\n", CharacterImage::CHARACTER_NUMBER, CharacterImage::PAUSE_NUMBER, CharacterImage::CLOTHES_NUMBER);	break;
		case LogOutputType::CELL_CHARACTER:
			sprintf_s(c, 256, "%d行目、コマンド：%s、キャラ左ID：%d、キャラ中ID：%d、キャラ右ID：%d\n", cell_number + 2, HM[commu_number][cell_number].GetCommand(), commu_character[0], commu_character[1], commu_character[2]);				
			break;
		case LogOutputType::LOG_MESSAGE:
			sprintf_s(c, 256, "%s\n", text_log[1].GetLine());
			break;
		case LogOutputType::NOT_USE_BACKGROUND:
			LogFileAdd("使ってない背景\n");
			for (int i = 0; i < bgimage[0].GetNumber(); i++)
			{
				if (bgimage[i].GetUse() == FALSE)
				{
					char c2[256];
					sprintf_s(c2, 256, "%d：%s\n", i + 1, bgimage[i].GetName());
					LogFileAdd(c2);
				}
			}
			break;
		default:
			break;
		}

		LogFileAdd(c);
	}
}
// 状態に応じたメッセージを出力する
void DebugMessage()
{
	clsDx();
	// （入学前）コミュ撮影モードなら全てのデバッグメッセージを非表示にする
	if (debug_entrance_before == FALSE)
	{
		if (debug_message == TRUE)
		{
			printfDx("shift or M＋N：デバッグメッセージ非表示\n");
			printfDx("立ち絵読み込みタイミング時にC：立ち絵読み込みスキップ\n");
			printfDx("画面解像度・%d：%d\n", monitor_resolution_x, monitor_resolution_y);
			printfDx("最近クリック座標・%d：%d\n", ClickX, ClickY);	// 前回クリックした際の座標
			printfDx("マウス座標：%d・%d\n", MouseX, MouseY);
			printfDx("現在のフルＨＤフラグ：%d\n", flag_full_hd_now);
			printfDx("E+X：強制終了\n");
			printfDx("progress_frame_time：%d\n", progress_frame_time);
			printfDx("progress_frame_need_time：%d\n", progress_frame_need_time);
			printfDx("GetNowCount()：%d\n", GetNowCount());
			printfDx("GetNowCount() - progress_frame_time：%d\n", GetNowCount() - progress_frame_time);
			if (debug_keyboard == FALSE){ printfDx("D+B：デバッグ操作可能\n"); }
			else
			{
				printfDx("デバッグ操作（");
				if (g_gamestate == GAME_TITLE){ printfDx("1：マップ画面へ移動、"); }
				if (g_gamestate == GAME_MAIN_COMMUNICATION) { printfDx("C+E：コミュ終了、"); }
				if (debug_entrance_before == FALSE){ printfDx("2+O：入学前コミュ撮影モードON、"); }
				else{ printfDx("2+N：入学前コミュ撮影モードOFF、"); }
				printfDx("0：デバッグ操作状態解除）\n");
			}
			//printfDx("サイズ変換倍率：%f\n", bairitu);
			printfDx("現在の状態：");

			BOOL jump = FALSE;
			BOOL jump_save[6] = {};
			// マップ中心からのマウス座標差
			float m_x = MouseX - 1038 * bairitu;
			float m_y = MouseY - 600 * bairitu;

			switch (g_gamestate)
			{
			case GAME_TITLE:
				printfDx("タイトル\n");
				printfDx("ボーダー画像：%d\n", ImgDataHJTitle::GetCountFrame() % ImaDataName::GetTitleBorderNumber());
				printfDx("●エディットキャラ読み込みフラグ（対応数字キー＋shiftでON、ctrlでOFF）\n");
				for (int i = 0; i < CharacterImage::GetCharacterMember(); i++)
				{
					char c[256] = "";
					switch (i)
					{
					case 0:	sprintf_s(c, 256, "・1:めぐる");	break;
					case 1:	sprintf_s(c, 256, "・2:恋鐘　");	break;
					case 2:	sprintf_s(c, 256, "・3:樹里　");	break;
					case 3:	sprintf_s(c, 256, "・4:凛世　");	break;
					case 4:	sprintf_s(c, 256, "・5:千雪　");	break;
					case 5:	sprintf_s(c, 256, "・6:はづき");	break;
					case 6:	sprintf_s(c, 256, "・7:校長　");	break;
					default:									break;
					}
					printfDx("%s：%s\n", c, CharacterImage::GetLoadEdit(i) == TRUE ? "ON" : "OFF");
				}
				break;
			case GAME_MAIN_COMMUNICATION:
				printfDx("メイン（コミュ）\n");
				printfDx("プレイ時間：%f\n", commu_play_time);
				//printfDx("『AUTO』x幅：%f\n", size_icon_auto.x);
				//printfDx("『AUTO』x座標：%f\n", commu_coordinate_icon_auto_x);
				printfDx("コミュタイトル：%s\n", commu_data[commu_number].GetTitle());
				printfDx("エディット時の行：%d\n", cell_number + 2);
				printfDx("左キャラクターＩＤ：%d\n", commu_character[0]);
				printfDx("中央キャラクターＩＤ：%d\n", commu_character[1]);
				printfDx("右キャラクターＩＤ：%d\n", commu_character[2]);
				printfDx("キャラ均等化フラグ：%d\n", commu_mode_distance);
				printfDx("キャラクター切り替えフレーム数：%d\n", commu_character_visibility_count[1]);
				// 行ジャンプ履歴
				printfDx("●行ジャンプ履歴\n");
				for (int i = 0; i < GlobalStaticVariable::GetCellLimit(); i++)
				{
					if (state::GetAlternativeMoveNumber(i) != 0)
					{
						jump = TRUE;
						printfDx("・%d行目：%d行へジャンプ\n", i + 2, state::GetAlternativeMoveNumber(i) + 2);
					}
				}
				if (jump == FALSE) { printfDx("・なし\n"); }
				printfDx("読み込み背景ＩＤ：%d\n", HM[commu_number][cell_number].background - 1);
				if (TextLog::GetMode() == FALSE) { printfDx("バックログ表示オフ\n"); }
				else
				{
					printfDx("○バックログ現在ページ：%d\n", TextLog::GetPage());
					for (int i = 0; i < TextLog::GetPagesLineNumber(); i++)
					{
						printfDx("・セリフ%d：%s\n", i + 1, text_log[(TextLog::GetPage() - 1) * 4 + i].GetLine());
					}
				}
				break;
			case GAME_MAP:
				printfDx("メイン（マップ）\n");				
				printfDx("マップ中心からのマウス座標差：%f・%f\n", m_x, m_y);
				printfDx("現在年月日：%d月%d週\n", game_week_number / 4 + 1, game_week_number % 4 + 1);
				for (int i = 0; i < 3; i++)
				{
					printfDx("コミュ%dデータ：ＩＤ・%d：タイトル・%s：出現タイミング・%d：アイコン左端x座標・%f：アイコン上端y座標・%f\n", i, commu_data[i].id, commu_data[i].path, commu_data[i].appear_timing, draw_map_character_icon_x[i], draw_map_character_icon_y[i]);
				}
				for (int i = 0; i < 10; i++)
				{
					printfDx("表示コミュ%dデータ：ＩＤ・%d：タイトル・%s：出現タイミング・%d：x座標・%f：y座標・%f\n",
						i, commu_data_map[i].id, commu_data_map[i].path, commu_data_map[i].appear_timing, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i]);
				}
				printfDx("『いいえ』選択肢x座標：%d\n", draw_map_commu_choice_x[1]);
				printfDx("前方tips文字列：%s\n", tips_string[0].string);
				printfDx("後方tips文字列：%s\n", tips_string[1].string);
				for (int i = 0; i < 3; i++) { printfDx("tips%dＩＤ：%d\n", i, tips_data[i].id); }
				printfDx("アイコン１タイトル：%s\n", commu_data_map[0].GetTitle());
				printfDx("選択中タイトル：%s\n", commu_data_map_choice.GetTitle());
				// 一時的に確認するもの
				printfDx("キャラアイコン横幅：%f\n", size_ui_map_icon2.x);
				printfDx("吹き出し：%f\n", size_ui_map_hukidasi[0].x);
				// マップ画面移動確認用画像X座標
				//for (int i = 0; i < ImgDataMapQuestion::GetNumber(); i++){printfDx("マップ画面移動確認用画像X座標：%f、Y座標：%f\n", image_map_question[i].GetCoordinateX(), image_map_question[i].GetCoordinateY());}
				// 『いいえ』当たり判定
				printfDx("『いいえ』当たり判定X座標：%f、Y座標：%f\n",
					image_icon_map_collision_detection.GetCoordinateX(),
					image_icon_map_collision_detection.GetCoordinateY());
				break;
			case GAME_SAVELOAD:
				if (mode_save == TRUE) { printfDx("セーブ\n"); }
				else { printfDx("ロード\n"); }
				break;
			case GAME_CONFIG:
				printfDx("設定\n");
				break;
			case GAME_COMMU_SELECT:
				printfDx("選択肢１：左端x座標・%f、上端y座標・%f、横幅・%f、縦幅・%f\n", commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[0], size_ui_cs_alternative.x, size_ui_cs_alternative.y);
				break;
			case GAME_COMMU_EDIT:
				printfDx("コミュ作成\n");
				printfDx("入力中のコマンド系文字列%d\n", g_commandinputstring);
				for(int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						printfDx("%d行目%d列目ＩＤ：%d\n", i + 1, j + 1, edit_character_id[i][j]);
					}
				}
				break;
			default:
				printfDx("不明\n");
				break;
			}

		}
		else
		{
			clsDx();
			if (g_gamestate == GAME_FIRST_LOAD)
			{
				printfDx("C：立ち絵ロードをしない\nB：ＢＧＭロードをしない\n");
				//printfDx("素材読み込みカウント：%d\n", GetNowCount() - ImgData2::GetNoticeCount());
			}
			printfDx("(shift or M)＋O：デバッグメッセージ表示\n");
		}
	}
}
// クリック判定用描画関数
void DebugDrawClickJudge(int x1, int y1, int x2, int y2, int r, int g, int b)	// 左端,上端,幅,高さ,赤,緑,青
{
	DrawBox(x1, y1, x1 + x2, y1 + y2, GetColor(r, g, b), FALSE);
}
// 立ち絵ロードを行うか確認する
BOOL DebugLoadCheckCharacter()
{
	if (CheckHitKey(KEY_INPUT_C) == TRUE) { debug_character_load_cut = TRUE; }
	else { debug_character_load_cut = FALSE; }
	return debug_character_load_cut;
}
// ＢＧＭロードを行うか確認する
BOOL DebugLoadCheckBGM()
{
	if (CheckHitKey(KEY_INPUT_B) == TRUE) { debug_bgm_load_cut = TRUE; }
	return debug_bgm_load_cut;
}

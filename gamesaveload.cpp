#include "gamesaveload.h"
#include <string>
#include <vector> 

SaveLoadBeforeMode g_sl_bm_status = SL_BEFORE_TITLE;

using namespace std;//名前空間を指定

int GlobalStaticSaveLoad::samune_background_id = 0;	// サムネ背景保存のために必要なＩＤ変数

float sl_coordinate_mode_icon_x = 0;						// 格モード移動系アイコンx座標
float sl_coordinate_icon_save_y = 0;						// 『SAVE』アイコンy座標
float sl_coordinate_icon_load_y = 0;						// 『LOAD』アイコンy座標
float sl_coordinate_icon_back_y = 0;						// 『BACK』アイコンy座標
float sl_coordinate_icon_title_y = 0;						// 『TITLE』アイコンy座標
float sl_coordinate_icon_exit_y = 0;						// 『EXIT』アイコンy座標
#pragma region ver0.0072制作時コメント化コード
//float sl_coordinate_icon_sf_page_x[SL_FILE_PAGE_NUMBER];	// 各セーブファイルページの左端x座標
//float sl_coordinate_icon_sf_page_y = 0;						// セーブファイルページの上端y座標
#pragma endregion
float sl_coordinate_icon_sf_x[6];							// 各セーブファイルの左端x座標
float sl_coordinate_icon_sf_y[6];							// 各セーブファイルの上端y座標

//将伍P変数-------------------------------------------------------------------------------
bool cft_save = FALSE;                                      //セーブモード切り替え
bool cft_load = FALSE;                                      //ロードモード切り替え
bool exit_switch = FALSE;                                   //EXITモード判定
bool CallCheckMsg;                                          //確認メッセージ呼び出し
bool cft_checkmsgYes = FALSE;                               //確認メッセージ「はい」
bool cft_checkmsgNo = FALSE;                                //確認メッセージ「いいえ」
bool checkmsg = FALSE;		                                //確認メッセージ判定
bool cft_savefile_page[SL_FILE_PAGE_NUMBER];                //セーブファイルページを変更する
#pragma region ver0.0072制作時コメント化コード
//bool cft_savefile_sl[6];                                    //『SAVE』or『LOAD』を行う
#pragma endregion

float chk_coordinate_yes_x = 0;	                            //確認メッセージ『はい』選択肢x座標
float chk_coordinate_yes_y = 0;	                            //確認メッセージ選択肢y座標
float chk_coordinate_no_x = 0;	                            //確認メッセージ『いいえ』選択肢x座標
int temp_font3 = 0;                                         //仮フォント
int savefile_page =0;                                       //現在のセーブファイルページ
int savefile_sl = 0;                                        //選択中のセーブファイル
std::string msg_text = "〇〇しますか?";                     //確認メッセージテキスト
char *display_time;											//セーブファイルのプレイ時間表示
//-------------------------------------------------------------------------------

//デバック用-----------------
int temp = 0;
extern std::string debug_var;
bool DrawClickFlag = FALSE;
int p_count;
vector<vector<string>> xy(3, vector<string>(3, "abc"));

//---------------------------

BOOL mode_save = TRUE;	// セーブorロード状態を判別する
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfsl=click_flag_save_load）
//BOOL cfsl_;		// 
// セーブ・ロード画面移行処理
void GameSaveLoadNext(BOOL x, SaveLoadBeforeMode y)	// セーブorロードのフラグ,セーブorロード状態移行前の状態
{
	g_gamestate = GAME_SAVELOAD;
	mode_save = x;
	g_sl_bm_status = y;
	// サムネのハンドルを読み込む
	for (int i = 0; i < SL_FILE_PAGE_NUMBER * SL_FILE_NUMBER; i++){ save_data_image[i].LoadHandel(i);}
}
// GAME_SAVELOAD状態のメイン処理
void GameSaveLoad()
{
	if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE;}
	//GameMainCommunicationControl();
	
	if (CallCheckMsg == FALSE) { GameSaveLoadControl(); }
	DrawGameSaveLoad();
    //CallCheckMs==TRUEで確認メッセージを表示する
	if (CallCheckMsg == TRUE) 
	{
		CheckMessage();		//確認メッセージ処理
		if (checkmsg == TRUE)	//確認メッセージ「はい」を選択した場合
		{
			if (exit_switch == TRUE)	//EXITモード時処理
			{
				quit_game = TRUE;	//ゲーム終了
				mode_save = FALSE;	//フラグを戻す
			}
			else if (mode_save == TRUE) { GameSave(savefile_sl); }	//SAVEモード時処理
			else { GameLoad(savefile_sl); }		//LOADモード時処理

			//全てのフラグを戻す
			exit_switch = FALSE;
			checkmsg = FALSE;
			CallCheckMsg = FALSE; //確認メッセージ表示フラグを戻す
		}


	}
	//dbClickgamesaveload(CallCheckMsg);	//デバック用

}
// セーブロード画面操作処理
void GameSaveLoadControl()
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
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , TRUE, FALSE) == TRUE) { cfsl_ = TRUE; }
				//「SAVE」アイコン判定
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }//タイトルからの場合
				#pragma region ver0.017制作時コメント化コード
				//else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_save = TRUE; }
				////「LOAD」アイコン判定
				//if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_load = TRUE; }
				////「BACK」アイコン判定
				//if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }//タイトルからの場合
				//else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_exit_main_commu = TRUE; }
				////「TITLE」アイコン判定
				//if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y,size_icon_auto.x ,size_icon_auto.y , TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
				////「EXIT」アイコン判定
				//if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_quit_game = TRUE; }
#pragma endregion
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::SAVE)].JudgementClickCheck() == TRUE) {}
				//「LOAD」アイコン判定
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::LOAD)].JudgementClickCheck() == TRUE) {}
				//「BACK」アイコン判定
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }//タイトルからの場合
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::BACK)].JudgementClickCheck() == TRUE) {}
				//「TITLE」アイコン判定
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::TITLE)].JudgementClickCheck() == TRUE) {}
				//「EXIT」アイコン判定
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::EXIT)].JudgementClickCheck() == TRUE) {}
				// セーブファイルページアイコン判定
				#pragma region ver0.0072制作時コメント化コード
				//for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++)
				//{ 
				//	if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y,  size_icon_sl_file_page.x, size_icon_sl_file_page.y, TRUE, FALSE) == TRUE){ cft_savefile_page[i] = TRUE; }
				//}
#pragma endregion
				for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++)
				{
					if(image_icon_sl_page[i].JudgementClickCheck() == TRUE){}
				}
				// セーブファイル判定
				#pragma region ver0.0072制作時コメント化コード
				//for (int i = 0; i < SL_FILE_NUMBER; i++)
				//{
				//	if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], size_icon_sl_file.x, size_icon_sl_file.y, TRUE, FALSE) == TRUE){ cft_savefile_sl[i] = TRUE; }
				//}
#pragma endregion
				for (int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
				{
					if (image_icon_save_file[i][0].JudgementClickCheck() == TRUE) {}
				}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				//「SAVE」アイコン判定
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }//タイトルからの場合
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::SAVE)].JudgementReleaseCheck() == TRUE)
				{ 
					// ロードモードなら効果音を鳴らす
					if (mode_save == FALSE) { SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE)); }

					mode_save = TRUE;
				}
				//「LOAD」アイコン判定
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::LOAD)].JudgementReleaseCheck() == TRUE)
				{ 
					// セーブモードなら効果音を鳴らす
					if (mode_save == TRUE) { SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE)); }

					mode_save = FALSE; 
				}
				//「BACK」アイコン判定
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }//タイトルからの場合
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::BACK)].JudgementReleaseCheck() == TRUE)
				{ 
					if(g_sl_bm_status == SL_BEFORE_COMMU){g_gamestate = GAME_MAIN_COMMUNICATION; }	//コミュに戻る
					else if (g_sl_bm_status == SL_BEFORE_MAP) { g_gamestate = GAME_MAP; }			// マップに戻る
					SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					//フラグを戻す
					mode_save = FALSE;
					exit_switch = FALSE;
				}
				//「TITLE」アイコン判定
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::TITLE)].JudgementReleaseCheck() == TRUE) { GameTitleNext(); }
				//「EXIT」アイコン判定
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::EXIT)].JudgementReleaseCheck() == TRUE)
				{
					CallCheckMsg=TRUE;	//確認メッセージ呼び出しフラグ
					exit_switch = TRUE;	//「EXIT」モードフラグ
				}
				#pragma region ver0.0072制作時コメント化コード
				//// セーブファイルページアイコン判定
				//for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++)
				//{
				//	if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, size_icon_sl_file_page.x, size_icon_sl_file_page.y, FALSE, cft_savefile_page[i]) == TRUE)
				//	{
				//		savefile_page = i;	//選択したページ数を格納
				//	}
				//}
				// セーブファイル判定
				//for (int i = 0; i < SL_FILE_NUMBER; i++)
				//{
				//	if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], size_icon_sl_file.x, size_icon_sl_file.y, FALSE, cft_savefile_sl[i]) == TRUE)
				//	{
				//		CallCheckMsg = TRUE;	//確認メッセージ呼び出しフラグ
				//		exit_switch = FALSE;	//「EXIT」モードのフラグを戻す
				//		savefile_sl = i + (savefile_page * SL_FILE_NUMBER);	//選択したセーブファイル"1～6"+(ページ数*1ページ内の表示セーブデータ数"6")
				//			if (commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second < 1)  //セーブするデータのプレイ時間が1秒未満の場合
				//			{
				//				if (mode_save == FALSE) { CallCheckMsg = FALSE; }	//フラグを戻しセーブ処理を発生させない
				//			}
				//	}
				//}
#pragma endregion
				// セーブファイルページアイコン判定
				for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++)
				{
					//選択したページ数を格納
					if (image_icon_sl_page[i].JudgementReleaseCheck() == TRUE) { savefile_page = i; }
				}
				// セーブファイル判定
				for (int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
				{
					if (image_icon_save_file[i][0].JudgementReleaseCheck() == TRUE)
					{
						CallCheckMsg = TRUE;	//確認メッセージ呼び出しフラグ
						exit_switch = FALSE;	//「EXIT」モードのフラグを戻す
						#pragma region ver0.0081制作時コメント化コード
						//savefile_sl = i + (savefile_page * SL_FILE_NUMBER);	//選択したセーブファイル"1～6"+(ページ数*1ページ内の表示セーブデータ数"6")
						//if (commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second < 1)  //セーブするデータのプレイ時間が1秒未満の場合
#pragma endregion
						savefile_sl = i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber());	//選択したセーブファイル"1～6"+(ページ数*1ページ内の表示セーブデータ数"6")
						if (commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second < 1)  //セーブするデータのプレイ時間が1秒未満の場合
						{
							if (mode_save == FALSE) { CallCheckMsg = FALSE; }	//フラグを戻しセーブ処理を発生させない
						}
						// ロードモード時に存在しないファイルをクリックした場合でなければ効果音を鳴らす
						if (commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second > 1 || mode_save == TRUE) { SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE)); }
					}
				}
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , FALSE, cfsl_) == TRUE) { }
				// 全てのフラグを戻す
				//cfsl_ = FALSE;
				cft_save = FALSE;               //セーブモード切り替え
				cft_load = FALSE;               //ロードモード切り替え
				cft_exit_main_commu = FALSE;	// コミュ画面に移動
				cfc_move_title = FALSE;			// タイトル画面へ移動
				cft_quit_game = FALSE;			// ゲームを終了
				#pragma region ver0.0072制作時コメント化コード
				//for (int i = 0; i < SL_FILE_NUMBER; i++) { cft_savefile_page[i] = FALSE; }     //セーブファイルページを変更する
				//『SAVE』or『LOAD』を行う
				//for (int i = 0; i < SL_FILE_NUMBER; i++) { cft_savefile_sl[i] = FALSE; }    //『SAVE』or『LOAD』を行う
#pragma endregion
				for (int i = 0; i < SL_FILE_NUMBER; i++) { cft_savefile_page[i] = FALSE; }     //セーブファイルページを変更する
				//『SAVE』or『LOAD』を行う
				for (int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++) {image_icon_save_file[i][0].CJChange(FALSE); }
				for (int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++) { image_icon_new_option[i].CJChange(FALSE); }	// 各コマンドを実行する
				for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++) { image_icon_sl_page[i].CJChange(FALSE); }
			}
		}
	}
}
// 引数に応じた番号のデータにセーブする
void GameSave(int x)	// セーブデータ番号
{
	FILE* fp;
	errno_t err;
	char c[256];
	sprintf_s(c, 256, "sr_commusave%02d.dat", x);	// １桁の場合は『0x』となる
	commu_save_data[x].play_second = commu_play_time;
	commu_save_data[x].ChangeTimeString();
	commu_save_data[x].ChangeSaveData(game_week_number, commu_number + 1, cell_number, static_cast<int>(CommuData::GetGMapUpperType()));
	for (int i = 0; i < CommuSaveData::GetCharacterNumber(); i++) { commu_save_data[x].SetNumberMet(i, commu_look_count[i]); }
	commu_save_data[x].SetLineJump();
	for (int i = 0; i < CommuSaveData::GetCharacterNumber(); i++) { commu_save_data[x].SetTrialStillViewed(i, GlobalStaticMap::GetTrialCommuViewed(i)); }
	err = fopen_s(&fp, c, "wb");
	//このコードで警告文が消える
	//if (fp != NULL)
	//{
		fwrite(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);
		fclose(fp);
	//}

	// 画像保存テスト（ここに異常があってマップに戻った際左マップが残っている）
	save_data_image[x].Blend(x, commu_save_data[x].GetCommuID() != 0 ? FALSE : TRUE);
}
// 引数に応じた番号のデータをロードする
void GameLoad(int x)	// 
{
	FILE* fp;
	errno_t err;
	char c[256];
	sprintf_s(c, 256, "sr_commusave%02d.dat", x);	// １桁の場合は『0x』となる
	err = fopen_s(&fp, c, "rb");
	//このコードで警告文が消える
	//if (fp != NULL)
	//{
	fread(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);
	fclose(fp);
	//}
	commu_play_time = commu_save_data[x].play_second;
	game_week_number = commu_save_data[x].GetWeek();
	commu_number = commu_save_data[x].GetCommuID();
	for(int i = 0; i < CommuSaveData::GetCharacterNumber(); i++)
	{
		commu_look_count[i] = commu_save_data[x].GetNumberMet(i);
		GlobalStaticMap::SetTrialCommuViewed(i, commu_save_data[x].GetTrialStillViewed(i));
	}
	// マップ出現タイミングの数値は変換して使う
	CommuData::SetGMapUpperType(static_cast<CommuData::MapUpperType>(commu_save_data[x].GetMapAppearID()));

	// 指定のコミュを始める（0ならマップ画面）
	#pragma region ver0.00396制作時コメント化コード
	//GameMainCommunicationNext(0);
#pragma endregion
	if (commu_number > 0)
	{
		GameMainCommunicationNext(commu_number - 1, FALSE, 0); 
		// コミュ履歴をセーブデータから読み込む
		for (int i = 0; i < GlobalStaticVariable::GetCellLimit(); i++){state::SetAlternativeMoveNumber(i, commu_save_data[x].GetLineJump(i));}

		int loop_limit = commu_save_data[x].GetCell();
		// 目的の行に選択肢がある場合、『目的の行』を1減らす
		if (std::strcmp(HM[commu_number][loop_limit].GetCommand(), "altenative_2") == 0 || std::strcmp(HM[commu_number][loop_limit].GetCommand(), "altenative_3") == 0) { loop_limit--; }
		// ロード中フラグを立てる
		GlobalStaticMusic::SetNowLoading(TRUE);
		// 目的の行まで行送りを繰り返す
		for (int i = 0; i < loop_limit; i++) 
		{
			// 行を跳ぶ
			if (state::GetAlternativeMoveNumber(i) != 0)
			{
				int y = state::GetAlternativeMoveNumber(i) - 1;
				i = y;
				cell_number = y;
			}

			GameMainCommunicationNextLine();
			// 該当行以前のＳＥを鳴らさない
			if (i < loop_limit - 1) { SEPlay(-2); }
		}
		// 透明度入れ替えの数値を0にする
		for (int i = 0; i < 3; i++) { commu_character_visibility_count[i] = 0; }
		commu_background_visibility_count = 0;
		commu_mode_background = FALSE;
		// 選択肢、指定フレーム後自動進行状態を発生させない
		if (g_commustatus == COMMU_STATUS_ALTENATIVE || g_commustatus == COMMU_STATUS_AUTO || 
			(g_commustatus == COMMU_STATUS_SE && strcmp(HM[commu_number][cell_number].command, "auto_se") != 0)) { g_commustatus = COMMU_STATUS_NORMAL; }
		//	if (strcmp(HM[commu_number][cell_number].command, "auto_se") == 0){ g_commustatus = COMMU_STATUS_SE; }	// 次行セルコマンドが『auto_se』なら次行ＳＥ再生が終わるまで操作が自動になるフラグを立てる
		// ロード中フラグをおろす
		GlobalStaticMusic::SetNowLoading(FALSE);
	}
	else 
	{ 
		// 週を進めないようにしてマップ画面へ移行
		game_week_number--;
		GameMapNext(); 
	}
}
// セーブ・ロード画面で使う様々な座標を（再）定義する
void GameSaveLoadCoordinateSetting()
{
	sl_coordinate_mode_icon_x = bairitu * 1800;					// 格モード移動系アイコンx座標
	sl_coordinate_icon_save_y = bairitu * 596;					// 『SAVE』アイコンy座標
	float x = size_icon_auto.y * 2.0f;							// 各アイコンの間隔
	sl_coordinate_icon_load_y = sl_coordinate_icon_save_y + x;	// 『LOAD』アイコンy座標
	sl_coordinate_icon_back_y = sl_coordinate_icon_load_y + x;	// 『BACK』アイコンy座標
	sl_coordinate_icon_title_y = sl_coordinate_icon_back_y + x;	// 『TITLE』アイコンy座標
	sl_coordinate_icon_exit_y = sl_coordinate_icon_title_y + x;	// 『EXIT』アイコンy座標

	chk_coordinate_yes_x = bairitu * 600;	                      //確認メッセージ『はい』選択肢x座標
	chk_coordinate_yes_y = bairitu * 600;	                      //確認メッセージ『はい』選択肢y座標
	chk_coordinate_no_x = chk_coordinate_yes_x * 1.75f;	          //確認メッセージ『いいえ』選択肢x座標
	for(int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++)
	{
		const float X = 200.0f * (i == 0 ? -1 : 1);	// 可読性向上のため代入
		image_icon_check[i].CoordinateSetting2(X - image_icon_check[i].GetOriginalSizeX() / 2 + GlobalStaticVariable::GetRSOriginalX() / 2,600);
	}

	temp_font3 = CreateFontToHandle("メイリオ", FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y*5, -1, DX_FONTTYPE_ANTIALIASING);
	#pragma region ver0.0072制作時コメント化コード
	//// 各セーブファイルページの左端x座標
	//for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { sl_coordinate_icon_sf_page_x[i] = i * (size_icon_sl_file_page.x * 1.25f) + bairitu * 600; }

	//sl_coordinate_icon_sf_page_y = bairitu * 60;	// セーブファイルページの上端y座標
#pragma endregion
	// セーブロードページ
	for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++) { image_icon_sl_page[i].CoordinateSetting2(i % GlobalStaticSaveLoad::GetFilePageNumber() * image_icon_sl_page[i].GetOriginalSizeX() * 1.25f + 1440, 951); }
	// セーブデータ
	#pragma region ver0.0072制作時コメント化コード
	//for(int i = 0; i < SL_FILE_NUMBER; i++)
	//{
	//	//debug_var= std::to_string(screen_size_x - bairitu * ((i % 2 == 0 ? size_icon_sl_file.x + 100 : 0) + size_icon_sl_file.x + 100));
	//	//sl_coordinate_icon_sf_x[i] = screen_size_x - bairitu * ((i % 2 == 0 ? size_icon_sl_file.x + 100 : 0) + size_icon_sl_file.x + 100);							// 各セーブファイルの左端x座標
	//	//将伍Ｐにより修正済
	//	sl_coordinate_icon_sf_x[i] = screen_size_x - ((i % 2 == 0 ? size_icon_sl_file.x + bairitu * 100 : 0) + size_icon_sl_file.x + bairitu * 100);				// 各セーブファイルの左端x座標
	//	//sl_coordinate_icon_sf_y[i] = bairitu * ((int)(i / 2) * (size_icon_sl_file.y + 50) + 100);																	// 各セーブファイルの上端y座標
	//	sl_coordinate_icon_sf_y[i] = (int)(i / 2) * (size_icon_sl_file.y + bairitu * 50) + sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y + bairitu * 90;	// 各セーブファイルの上端y座標
	//}
#pragma endregion
	for(int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
	{
		// static_castにしておけばコンパイル時にエラーチェックを行ってくれる
		image_icon_save_file[i][0].CoordinateSetting2(i % 5 * (image_icon_save_file[i][0].GetOriginalSizeX() * 1.1f) + 102.0f, static_cast<int>(i / 5) * (image_icon_save_file[i][0].GetOriginalSizeY() * 1.25f) + 186);
		image_icon_save_file[i][1].CoordinateSetting2(i % 5 * (image_icon_save_file[i][1].GetOriginalSizeX() * 1.1f) + 102.0f, static_cast<int>(i / 5) * (image_icon_save_file[i][1].GetOriginalSizeY() * 1.25f) + 186);
	}
	// （新しい）アイコン（CoordinateSetting2で倍率をかけるのでオリジナルサイズを定義する）
	const float X = 1800;
	const float Y = 783;
	for(int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++)
	{ 
		image_icon_new_option[i].CoordinateSetting2(X, i * image_icon_new_option[i].GetOriginalSizeY() * 1.2f + Y);
	}
}
// セーブ・ロード画面の描画処理
void DrawGameSaveLoad()
{
	// 背景
	#pragma region ver0.00907制作時コメント化コード
	//bgimage[static_cast<int>(ImgDataBG::EnumConstant::OFFICE)].DrawImage();
#pragma endregion
	if (mode_save == TRUE){bgimage[static_cast<int>(ImgDataBG::EnumConstant::STAFF_ROOM)].DrawImage();}
	else { bgimage_room_teacher.DrawImage(); }
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// モード表示
	image_saveload_mode[mode_save].DrawImage();

	if (mode_save == TRUE) 
	{
		#pragma region ver0.017制作時コメント化コード
		////『SAVE』モードならオレンジ
		//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[1], TRUE);
		//// 『LOAD』アイコン
		//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[0], TRUE);
#pragma endregion
		// 『LOAD』アイコン
		image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::LOAD)].DrawImage();
	}
	// ロード状態
	else	
	{
		// （直前の状態がタイトル画面だったら）グレー『SAVE』アイコン
		if (g_sl_bm_status == SL_BEFORE_TITLE) 
		{ 
			//素材未入手
			//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE); 
		}
		else
		{
			//『SAVE』アイコン
			#pragma region ver0.017制作時コメント化コード
			//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE);
#pragma endregion
			image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::SAVE)].DrawImage();
		}
		#pragma region ver0.017制作時コメント化コード

		//// 『LOAD』モードならオレンジ
		//	DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[1], TRUE);
#pragma endregion
	}		
	// （直前の状態がタイトル画面だったら）グレー『BACK』アイコン
	if (g_sl_bm_status == SL_BEFORE_TITLE)
	{
		//素材未入手
		//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);
	}
	else
	{
		//『BACK』アイコン
		#pragma region ver0.017制作時コメント化コード
		//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);
#pragma endregion
		image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::BACK)].DrawImage();
	}
	#pragma region ver0.017制作時コメント化コード
	//// 『TITLE』アイコン
	//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_title_y + size_icon_auto.y, g_imghandles.icon_title, TRUE);
	//// 『EXIT』アイコン
	//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_exit_y + size_icon_auto.y, g_imghandles.icon_exit, TRUE);
#pragma endregion
	// 『TITLE』アイコン
	image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::TITLE)].DrawImage();
	// 『EXIT』アイコン
	image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::EXIT)].DrawImage();
	// （新しい）アイコン（テストで問題なければ消す）
	//for (int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++) { image_icon_new_option[i].DrawImage(); }
	// セーブファイルページアイコン
	#pragma region ver0.0072制作時コメント化コード
	//for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { DrawExtendGraphF(sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[i] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, g_imghandles.icon_save_file_page[0], TRUE); }
 //   DrawExtendGraphF(sl_coordinate_icon_sf_page_x[savefile_page], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[savefile_page] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, g_imghandles.icon_save_file_page[1], TRUE); 
#pragma endregion
	for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++) { image_icon_sl_page[i].DrawImage(); }

	#pragma region ver0.0072制作時コメント化コード
//	// セーブファイル
//	for(int i = 0; i < SL_FILE_NUMBER; i++){ DrawExtendGraphF(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, g_imghandles.icon_save_file, TRUE); }
//	// セーブファイルページ
//	for (int i = 0; i < SL_FILE_NUMBER; i++) 
//	{ 
//		DrawExtendGraphF(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second <= 0 ? g_imghandles.icon_save_file : save_data_image[i + (savefile_page * SL_FILE_NUMBER)].GetHandle(), TRUE);
//		//DrawExtendGraphF(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, g_imghandles.icon_save_file, TRUE);
//		#pragma region ver0.0035制作時コメント化コード
//		//DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], GetColor(255, 0, 0), temp_font3, "%02d", i + 1+(savefile_page* SL_FILE_NUMBER));
//#pragma endregion
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70 * 255 / 100);
//		DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], GetColor(255, 0, 0), temp_font3, "%02d", i + 1 + (savefile_page * SL_FILE_NUMBER));
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//		if (commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second >= 1) //セーブするデータのプレイ時間が1秒以上の場合描画
//		{
//			DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, GetColor(255, 0, 0), g_font3, "%02d:%02d:%02d", int((commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second) / 3600), int(fmod( (commu_save_data[i+(savefile_page* SL_FILE_NUMBER)].play_second)/60,60)), int(fmod((commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second), 60)));
//			DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], GetColor(255, 0, 0), g_font3, commu_save_data[i + savefile_page * SL_FILE_NUMBER].GetTimeString());
//			DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i] + bairitu * 30, GetColor(0, 0, 0), g_font3, "%d月%d週", commu_save_data[i + savefile_page * SL_FILE_NUMBER].GetWeek() / 4 + 1, commu_save_data[i + savefile_page * SL_FILE_NUMBER].GetWeek() % 4 + 1);
//		}
//	}
#pragma endregion
	for(int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
	{
		int x = i + savefile_page * GlobalStaticSaveLoad::GetFileNumber();
		// 空のセーブファイルorサムネを描画
		if (commu_save_data[x].play_second > 0)
		{
			image_icon_save_file[i][1].DrawImage();
			const float X = bairitu * 42;
			DrawExtendGraphF(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + X, image_icon_save_file[i][0].GetCoordinateX() + image_icon_save_file[i][0].GetSizeX(), image_icon_save_file[i][0].GetCoordinateY() + X + image_icon_save_file[i][0].GetSizeX() / 16 * 9, save_data_image[x].GetHandle(), TRUE);
		}
		else{ image_icon_save_file[i][0].DrawImage(); }

		#pragma region ver0.0081制作時コメント化コード
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70 * 255 / 100);
		//DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() - bairitu * 30, GetColor(255, 0, 0), g_font3, "%02d", 1 + x);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#pragma endregion
		DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + bairitu * 9, GetColor(0, 0, 0), g_font3, "No.%02d", 1 + x);
		#pragma region ver0.0081制作時コメント化コード
		//if (commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second >= 1) //セーブするデータのプレイ時間が1秒以上の場合描画
#pragma endregion
		if (commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second >= 1) //セーブするデータのプレイ時間が1秒以上の場合描画
		{
			// スチル体験版では表示させない
			if (GlobalStaticVariable::GetModeTrial() == FALSE){DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX() + bairitu * 210, image_icon_save_file[i][0].GetCoordinateY() + bairitu * 9, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::SAVE_DATA)].GetHandle(), "%d月%d週", commu_save_data[x].GetWeek() / 4 + 1, commu_save_data[x].GetWeek() % 4 + 1);}
			// サブタイトル
			if (commu_save_data[x].GetCommuID() > 0)
			{
				// 文字列比較を行う
				if(strlen(commu_data[commu_save_data[x].GetCommuID() - 1].GetTitle()) > 18)
				{
					char c[22];	// ヌル終点用に+1バイト
					sprintf_s(c, 22, "%.18s...", commu_data[commu_save_data[x].GetCommuID() - 1].GetTitle());
					DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].GetSizeX() / 16 * 9 + bairitu * 45, GetColor(0, 0, 0), g_font3, c);
				}
				else{DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].GetSizeX() / 16 * 9 + bairitu * 45, GetColor(0, 0, 0), g_font3, commu_data[commu_save_data[x].GetCommuID() - 1].GetTitle());}
			}
			const float X = image_icon_save_file[i][0].GetCoordinateX();
			const float Y_PLAY_TIME = image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * (60 + 3);
			const float Y_SAVE_TIME = image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * (30 + 3);
			const float Z = bairitu * 15;
			DrawLineAA(X + Z, Y_PLAY_TIME, X + image_icon_save_file[i][0].GetSizeX() - Z, Y_PLAY_TIME, GetColor(0, 0, 0));
			#pragma region ver0.0081制作時コメント化コード
			//DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX() + Z, image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * 60, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::SAVE_DATA)].GetHandle(), "Play time―%02d:%02d:%02d", int((commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second) / 3600), int(fmod((commu_save_data[x].play_second) / 60, 60)), int(fmod((commu_save_data[i + (savefile_page * SL_FILE_NUMBER)].play_second), 60)));
#pragma endregion
			DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX() + Z, image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * 60, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::SAVE_DATA)].GetHandle(), "Play time―%02d:%02d:%02d", int((commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second) / 3600), int(fmod((commu_save_data[x].play_second) / 60, 60)), int(fmod((commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second), 60)));
			DrawLineAA(X + Z, Y_SAVE_TIME, X + image_icon_save_file[i][0].GetSizeX() - Z, Y_SAVE_TIME, GetColor(0, 0, 0));
			DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX() + Z, image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * 30, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::SAVE_DATA)].GetHandle(), commu_save_data[x].GetTimeString());
		}
	}
}
// 確認メッセージ状態のメイン処理
void CheckMessage() 
{
	CheckMessageControl();
		DrawCheckMessage();
}
// 確認メッセージ操作処理
void CheckMessageControl()
{
	// マウスのボタンが押されたり離されたりしたかどうかの情報を取得する
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		// 左ボタンが押されていたら
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
				#pragma region ver0.0081制作時コメント化コード
				//BOOL x = FALSE;	// 以降の処理から抜け出す変数
				////「はい」判定
				//if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y,  size_icon_auto.x*3 ,  size_icon_auto.y*3 , TRUE, FALSE) == TRUE) { cft_checkmsgYes = TRUE; }
				////「いいえ」判定
				//if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y,  size_icon_auto.x *3,  size_icon_auto.y*3 , TRUE, FALSE) == TRUE) { cft_checkmsgNo = TRUE; }
#pragma endregion
				if (image_icon_check[0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_check[1].JudgementClickCheck() == TRUE) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				//「はい」判定
				#pragma region ver0.0081制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, FALSE, cft_checkmsgYes) == TRUE)
#pragma endregion
				if (image_icon_check[0].JudgementReleaseCheck() == TRUE)
				{
					checkmsg= TRUE;		//「はい」フラグ
					CallCheckMsg = FALSE;	//確認メッセージを閉じる
					SEPlay(static_cast<int>(SEData::IDName::SENTAKUSHI));
				}
				//「いいえ」判定
				#pragma region ver0.0081制作時コメント化コード
				//if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, FALSE, cft_checkmsgNo) == TRUE)
#pragma endregion
				else if (image_icon_check[1].JudgementReleaseCheck() == TRUE)
				{
						checkmsg= FALSE;	//「いいえ」フラグ
						CallCheckMsg = FALSE;	//確認メッセージを閉じる
						SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));
				}
				// 全てのフラグを戻す
				cft_checkmsgYes = FALSE;                               //確認メッセージ「はい」
				cft_checkmsgNo = FALSE;                                //確認メッセージ「いいえ」
				for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].CJChange(FALSE); }								
			}
		}
	}
}
// 確認メッセージの描画処理
void DrawCheckMessage()
{
	//確認メッセージ内容(各モードの判定)
	#pragma region ver0.0081制作時コメント化コード
	//if (exit_switch == TRUE) { msg_text = "終了しますか?"; }
	//else
	//{
	//	if (mode_save == TRUE) { msg_text = "セーブしますか?"; }
	//	if (mode_save == FALSE) { msg_text = "ロードしますか?"; }
	//}
#pragma endregion

	//仮素材のため配置適当アイコンサイズは3倍
	//確認メッセージウィンドウ
	//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_check.x) / 2, (screen_size_y - bairitu * size_ui_map_check.y) / 2, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, g_imghandles.ui_map_check, TRUE);
	// 文字列
	if (exit_switch == TRUE)
	{ 
		#pragma region ver0.0081制作時コメント化コード
		//DrawBoxAA((screen_size_x - bairitu * size_ui_map_check.x) / 2, (screen_size_y - bairitu * size_ui_map_check.y) / 2, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, GetColor(0, 223, 223), TRUE);
		//DrawStringFToHandle(float(screen_size_x) / 2 - (GetDrawFormatStringWidthToHandle(temp_font3, "%s", msg_text.c_str()) / 2), ((screen_size_y - bairitu * size_ui_map_check.y) / 2 + (screen_size_y / 2 - GetDrawFormatStringWidthToHandle(temp_font3, "%c", msg_text.c_str())) / 2), msg_text.c_str(), GetColor(0, 0, 0), temp_font3);
#pragma endregion
		image_finish_check.DrawImage();
	}
	else
	{
		if (mode_save == TRUE) { image_sl_check_message[static_cast<int>(ImgDataSLCheck::Type::SAVE)].DrawImage(); }
		if (mode_save == FALSE) { image_sl_check_message[static_cast<int>(ImgDataSLCheck::Type::LOAD)].DrawImage(); }
	}
	#pragma region ver0.0081制作時コメント化コード
	////『はい』アイコン
	//DrawExtendGraphF(chk_coordinate_yes_x, chk_coordinate_yes_y, chk_coordinate_yes_x + size_icon_auto.x * 3, chk_coordinate_yes_y + size_icon_auto.y * 3, g_imghandles.ui_map_check_choice[0], TRUE);
	////『いいえ』アイコン
	//DrawExtendGraphF(chk_coordinate_no_x, chk_coordinate_yes_y, chk_coordinate_no_x + size_icon_auto.x * 3, chk_coordinate_yes_y + size_icon_auto.y * 3, g_imghandles.ui_map_check_choice[1], TRUE);
#pragma endregion
	// 選択肢アイコン
	for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].DrawImage(); }
}


//以下デバック用--------------------------------------------------------------------------------------------------------------------

bool dbClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, std::string massage)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBoxAA(Jx, Jy, Jx + breadth, Jy + length, GetColor(255, 0, 255), TRUE);
	//if (ClickFlagCheckF(ClickX, ClickY, Jx, Jy, breadth, length, TRUE, FALSE)) { debug_var = flag; }
	//else { debug_var = "フラグなし"; }
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 150);
	return FALSE;
}

void dbClickgamesaveload(bool p1, bool p2, bool p3) 
{

	if (p1 == TRUE) { p_count = 1; }
	if (p2 == TRUE) { p_count = 2; }
	if (p3 == TRUE) { p_count = 3; }
	switch(p_count) 
	{
	case 1:

			//if (ClickFlagCheckF(ClickX, ClickY, , , , , TRUE, FALSE) == TRUE) { cfsl_ = TRUE; }


			if (dbClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, TRUE, FALSE) == TRUE) { cft_checkmsgYes = TRUE; }
			if (dbClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, TRUE, FALSE) == TRUE) { cft_checkmsgNo = TRUE; }

		break;
	default:

		if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }
		else if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_save = TRUE; }
		if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_load = TRUE; }
		if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }
		else if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_exit_main_commu = TRUE; }
		if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
		if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_quit_game = TRUE; }

		// セーブファイルページアイコン
		for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) 
		{
			// 再び必要になったら修正する
			#pragma region ver0.0072制作時コメント化コード
			//if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, size_icon_sl_file_page.x, size_icon_sl_file_page.y, TRUE, FALSE) == TRUE)
			//{
			//	cft_savefile_page[i] = TRUE;

			//}
#pragma endregion
		}
		for (int i = 0; i < SL_FILE_NUMBER; i++) 
		{
			// 再び必要になったら修正する
			#pragma region ver0.0072制作時コメント化コード
			//if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], size_icon_sl_file.x, size_icon_sl_file.y, TRUE, FALSE) == TRUE)
			//{
			//	cft_savefile_sl[i] = TRUE;
			//}
#pragma endregion
		}
		break;
	}
	p_count = 0;
}

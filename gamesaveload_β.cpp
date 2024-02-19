#include "gamesaveload.h"
#include <string>


SaveLoadBeforeMode g_sl_bm_status = SL_BEFORE_TITLE;



float sl_coordinate_mode_icon_x = 0;						// 格モード移動系アイコンx座標
float sl_coordinate_icon_save_y = 0;						// 『SAVE』アイコンy座標
float sl_coordinate_icon_load_y = 0;						// 『LOAD』アイコンy座標
float sl_coordinate_icon_back_y = 0;						// 『BACK』アイコンy座標
float sl_coordinate_icon_title_y = 0;						// 『TITLE』アイコンy座標
float sl_coordinate_icon_exit_y = 0;						// 『EXIT』アイコンy座標
float sl_coordinate_icon_sf_page_x[SL_FILE_PAGE_NUMBER];	// 各セーブファイルページの左端x座標
float sl_coordinate_icon_sf_page_y = 0;						// セーブファイルページの上端y座標
float sl_coordinate_icon_sf_x[6];							// 各セーブファイルの左端x座標
float sl_coordinate_icon_sf_y[6];							// 各セーブファイルの上端y座標

//将伍P変数
bool cft_save = FALSE;                                   //セーブモード切り替え
bool cft_load = FALSE;                                   //ロードモード切り替え
bool exit_switch = FALSE;                                   //EXITモード判定
bool CallCheckMsg;                                          //確認メッセージ呼び出し
bool cft_checkmsgYes = FALSE;                               //確認メッセージ「はい」
bool cft_checkmsgNo = FALSE;                                //確認メッセージ「いいえ」
bool checkmsg = FALSE;		                                //確認メッセージ判定
bool cft_savefile_page = FALSE;                             //セーブファイルページを変更する
bool cft_savefile_sl = FALSE;                               //『SAVE』or『LOAD』を行う

float chk_coordinate_yes_x = 0;	                        //確認メッセージ『はい』選択肢x座標
float chk_coordinate_yes_y = 0;	                        //確認メッセージ選択肢y座標
float chk_coordinate_no_x = 0;	                        //確認メッセージ『いいえ』選択肢x座標
int temp_font3 = 0;                                     //仮フォント
int savefile_page =0;                                   //現在のセーブファイルページ
int savefile_sl = 0;                                    //選択中のセーブファイル
int savefile_page_check = 0;                            //クリックを離した座標でページが変わってしまう現象の対策
int savefile_sl_check = 0;
int temp = 0;
int  savedata_time[2];
std::string msg_text = "〇〇しますか?";
char *display_time;

BOOL mode_save = TRUE;	// セーブorロード状態を判別する
// 同じ範囲でマウスを押し、離されたら○○するフラグ（cfsl=click_flag_save_load）
//BOOL cfsl_;		// 
// セーブ・ロード画面移行処理
void GameSaveLoadNext(BOOL x, SaveLoadBeforeMode y)	// セーブorロードのフラグ,セーブorロード状態移行前の状態
{
	g_gamestate = GAME_SAVELOAD;
	mode_save = x;
	g_sl_bm_status = y;
}
// GAME_SAVELOAD状態のメイン処理
void GameSaveLoad()
{
	if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE;}
	//GameMainCommunicationControl();
	

	
	if (CallCheckMsg == FALSE) { GameSaveLoadControl(); }
		DrawGameSaveLoad();
	if (CallCheckMsg == TRUE) {
		CheckMessage();
		if (checkmsg == TRUE) {
			if (exit_switch == TRUE) { quit_game = TRUE; }
			if (mode_save == TRUE) { GameSave(savefile_sl); }
			if (mode_save == FALSE) { GameLoad(savefile_sl); }
			checkmsg = FALSE;
			CallCheckMsg = FALSE;
		}


	}
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
				
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_save = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_load = TRUE; }
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_exit_main_commu = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y,size_icon_auto.x ,size_icon_auto.y , TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_quit_game = TRUE; }
				// セーブファイルページアイコン(高さ方向当たり判定おかしい)
				for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { 
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[i] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, TRUE, FALSE) == TRUE)
					{
						cft_savefile_page = TRUE;
						savefile_page_check = i;
					}
				}
				for (int i = 0; i < SL_FILE_NUMBER; i++) {
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y,  TRUE, FALSE) == TRUE)
					{
						cft_savefile_sl = TRUE;
						savefile_sl_check = i;

					}
				}

			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_save) == TRUE) {  mode_save = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_load) == TRUE) { mode_save = FALSE; }
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_exit_main_commu) == TRUE) { GameMainCommunicationNext(0); }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfc_move_title) == TRUE) { GameTitleNext(); }
				if ((ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_quit_game) == TRUE)){
					CallCheckMsg=TRUE; 
					exit_switch = TRUE;
				}
				for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) {
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[i] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, FALSE, cft_savefile_page) == TRUE)
					{
						if (i == savefile_page_check) {
							cft_savefile_page = TRUE;
							savefile_page = i;
						}
					}
				}
				for (int i = 0; i < SL_FILE_NUMBER; i++) {
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, FALSE, cft_savefile_sl) == TRUE)
					{
						cft_savefile_sl = TRUE;
						CallCheckMsg = TRUE;
						exit_switch = FALSE;
						savefile_sl = i;
						if (commu_save_data[i+(savefile_page*5)].play_second <1){
							if (mode_save == FALSE) { CallCheckMsg = FALSE; }
							
							}
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
				cft_savefile_page = FALSE;      //セーブファイルページを変更する
				cft_savefile_sl = FALSE;        //『SAVE』or『LOAD』を行う
									// 
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
	err = fopen_s(&fp, c, "wb");
	fwrite(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);

	fclose(fp);
}
// 引数に応じた番号のデータをロードする
void GameLoad(int x)	// 
{
	FILE* fp;
	errno_t err;
	char c[256];
	sprintf_s(c, 256, "sr_commusave%02d.dat", x);	// １桁の場合は『0x』となる
	err = fopen_s(&fp, c, "rb");
	fread(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);
	fclose(fp);
	commu_play_time = commu_save_data[x].play_second;
	// 指定のコミュを始める動作テスト
	GameMainCommunicationNext(0);
}
// セーブ・ロード画面で使う様々な座標を（再）定義する
void GameSaveLoadCoordinateSetting()
{
	sl_coordinate_mode_icon_x = bairitu * 200;					// 格モード移動系アイコンx座標
	sl_coordinate_icon_save_y = bairitu * 200;					// 『SAVE』アイコンy座標
	float x = size_icon_auto.y * 2.0f;							// 各アイコンの間隔
	sl_coordinate_icon_load_y = sl_coordinate_icon_save_y + x;	// 『LOAD』アイコンy座標
	sl_coordinate_icon_back_y = sl_coordinate_icon_load_y + x;	// 『BACK』アイコンy座標
	sl_coordinate_icon_title_y = sl_coordinate_icon_back_y + x;	// 『TITLE』アイコンy座標
	sl_coordinate_icon_exit_y = sl_coordinate_icon_title_y + x;	// 『EXIT』アイコンy座標

	chk_coordinate_yes_x = bairitu * 600;	                      //確認メッセージ『はい』選択肢x座標
	chk_coordinate_yes_y = bairitu * 600;	                      //確認メッセージ『はい』選択肢y座標
	chk_coordinate_no_x = chk_coordinate_yes_x * 1.75;	          //確認メッセージ『いいえ』選択肢x座標
	temp_font3 = CreateFontToHandle("メイリオ", FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y*5, -1, DX_FONTTYPE_ANTIALIASING);


	// 各セーブファイルページの左端x座標
	for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { sl_coordinate_icon_sf_page_x[i] = i * (size_icon_sl_file_page.x * 1.25f) + bairitu * 600; }

	sl_coordinate_icon_sf_page_y = bairitu * 60;	// セーブファイルページの上端y座標
	// セーブデータ
	for(int i = 0; i < SL_FILE_NUMBER; i++)
	{
		sl_coordinate_icon_sf_x[i] = screen_size_x - bairitu * ((i % 2 == 0 ? size_icon_sl_file.x + 100 : 0) + size_icon_sl_file.x + 100);							// 各セーブファイルの左端x座標
		//sl_coordinate_icon_sf_y[i] = bairitu * ((int)(i / 2) * (size_icon_sl_file.y + 50) + 100);																	// 各セーブファイルの上端y座標
		sl_coordinate_icon_sf_y[i] = (int)(i / 2) * (size_icon_sl_file.y + bairitu * 50) + sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y + bairitu * 90;	// 各セーブファイルの上端y座標
	}
}
// セーブ・ロード画面の描画処理
void DrawGameSaveLoad()
{

	

	if (mode_save == TRUE) {
		//『SAVE』モードならオレンジ
		DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[1], TRUE);
		// 『LOAD』アイコン
		DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[0], TRUE);
	}
	   else	
	{
		// （直前の状態がタイトル画面だったら）グレー『SAVE』アイコン
		if (g_sl_bm_status == SL_BEFORE_TITLE) { 
			//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE); 
		}
		else
		{
			DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE);
		}
		
		// 『LOAD』モードならオレンジ
			DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[1], TRUE);
		
	}
		
	// 『BACK』アイコン
	if (g_sl_bm_status == SL_BEFORE_TITLE) {
		//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);
	}
	else {
		DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);

	}
	// 『TITLE』アイコン
	DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_title_y + size_icon_auto.y, g_imghandles.icon_title, TRUE);
	// 『EXIT』アイコン
	DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_exit_y + size_icon_auto.y, g_imghandles.icon_exit, TRUE);
	// セーブファイルページアイコン
	for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { DrawExtendGraphF(sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[i] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, g_imghandles.icon_save_file_page[0], TRUE); }
    DrawExtendGraphF(sl_coordinate_icon_sf_page_x[savefile_page], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[savefile_page] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, g_imghandles.icon_save_file_page[1], TRUE); 
	// セーブファイル
	for(int i = 0; i < SL_FILE_NUMBER; i++){ DrawExtendGraphF(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, g_imghandles.icon_save_file, TRUE); }
	for (int i = 0; i < SL_FILE_NUMBER; i++) { 
		DrawExtendGraphF(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, g_imghandles.icon_save_file, TRUE); 
		DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], GetColor(255, 0, 0), temp_font3, "%02d", i + 1+(savefile_page*5));
		if (commu_save_data[i + (savefile_page * 5)].play_second > 1) {
			temp = commu_save_data[i].play_second;
			//display_time = std::to_string(int(commu_save_data[i].play_second / 360)) + ":" + std::to_string(int(commu_save_data[i].play_second/60)) + ":" +std::to_string(int(commu_save_data[i].play_second))+":";
			DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i] - 30, GetColor(255, 0, 0), g_font3, "%02d:%02d:%02d", int(commu_save_data[i + (savefile_page * 5)].play_second / 360), int(commu_save_data[i+(savefile_page*5)].play_second / 60), int(commu_save_data[i + (savefile_page * 5)].play_second));
		}
	}
}

void CheckMessage() {
	CheckMessageControl();
		DrawCheckMessage();
}
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
				BOOL x = FALSE;	// 以降の処理から抜け出す変数
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , TRUE, FALSE) == TRUE) { cfsl_ = TRUE; }


				if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y,  size_icon_auto.x*3 ,  size_icon_auto.y*3 , TRUE, FALSE) == TRUE) { cft_checkmsgYes = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y,  size_icon_auto.x *3,  size_icon_auto.y*3 , TRUE, FALSE) == TRUE) { cft_checkmsgNo = TRUE; }
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// 以降の処理から抜け出す変数

				if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, FALSE, cft_checkmsgYes) == TRUE) {
					checkmsg= TRUE; 
					CallCheckMsg = FALSE;
				}
					if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, FALSE, cft_checkmsgNo) == TRUE) {
						checkmsg= FALSE;
						CallCheckMsg = FALSE;
					}
			
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , FALSE, cfsl_) == TRUE) { }
				// 全てのフラグを戻す
				//cfsl_ = FALSE;
				cft_checkmsgYes = FALSE;                               //確認メッセージ「はい」
				cft_checkmsgNo = FALSE;                                //確認メッセージ「いいえ」
								
			}
		}
	}
}
// 確認メッセージの描画処理
void DrawCheckMessage()
{
	if (exit_switch == TRUE) { msg_text = "終了しますか?"; }
	else {
		if (mode_save == TRUE) { msg_text = "セーブしますか?"; }
		if (mode_save == FALSE) { msg_text = "ロードしますか?"; }
	}

	//仮素材のため配置適当アイコンサイズは3倍
	//確認メッセージウィンドウ
	//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_check.x) / 2, (screen_size_y - bairitu * size_ui_map_check.y) / 2, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, g_imghandles.ui_map_check, TRUE);
	DrawBox((screen_size_x - bairitu * size_ui_map_check.x) / 2, (screen_size_y - bairitu * size_ui_map_check.y) / 2, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, GetColor(0, 255, 0), TRUE);

	//『はい』アイコン
	DrawExtendGraphF(chk_coordinate_yes_x, chk_coordinate_yes_y, chk_coordinate_yes_x + size_icon_auto.x*3, chk_coordinate_yes_y + size_icon_auto.y*3, g_imghandles.ui_map_check_choice[0], TRUE);
	//『いいえ』アイコン
	DrawExtendGraphF(chk_coordinate_no_x, chk_coordinate_yes_y, chk_coordinate_no_x + size_icon_auto.x * 3, chk_coordinate_yes_y + size_icon_auto.y * 3, g_imghandles.ui_map_check_choice[1], TRUE);
	DrawStringFToHandle(screen_size_x / 2 - bairitu * GetDrawFormatStringWidthToHandle(temp_font3, "%s", msg_text.c_str())/2,( (screen_size_y - bairitu * size_ui_map_check.y) / 2+( screen_size_y  / 2- GetDrawFormatStringWidthToHandle(temp_font3, "%c", msg_text.c_str()))/2), msg_text.c_str(), GetColor(0, 0, 0), temp_font3);
}
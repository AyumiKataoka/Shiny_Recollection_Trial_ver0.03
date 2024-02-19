/*
●必要処理
●推奨処理
●要修正
*/
#pragma region 固有メモ
/*
*/
#pragma endregion
#pragma region
#pragma endregion
//●永続保存メモ
/*
○ヘッダファイルの変数等の並びに規則性を持たせた方がいい
・（構造体内の変数宣言にenumを使うことがあるので下記の順番にする）
・インクルード宣言
・定数宣言
・enum
・struct
・class
・char
・int
・float
・double
・BOOL
・void関数（操作系と処理系の順番は問題ないか？）
　・ゲーム起動時に行われる読み込み
　・メイン関数
　・操作系
　・処理系
　・描画系
・その他の関数
○定数の式を使う定数は括弧で囲んだ方がいい？
・『定数x y + z』は『y + z』を格納しているだけで『y + z』の値ではないので、『100 - x』は『100 - y + z』となりzの値が加算されてしまう
○IDなどで順番に定数をつける場合（、そして後々その順番がずれる可能性がある場合）に、列挙体（enum）を付けるのが適している
○コメント化したコード整理の際は以下の要点に気をつける
・同バージョン作業内でコメント文にしたコード（ただのミス）は消してもよい
・修正としてコメントにした以前のバージョンのコードは残しておき、作業が本格的に一段落した際に消すかどうか決める
　・今現在、コメントで囲んで折りたたみできる機能、および『region』機能があるので、そのまま残しておいてもいい
・メディア、コード整理版アプリフォルダの作成は、上記の校正コメントを消した際かいずれかのメディアを消した、または場所を変えた際に行うのがいいのかもしれない
○多い行数のコメントは、囲んでコメント文にすれば関数のように開閉することができる
・『#pragma region』でも可能
○ゲームのタイトルを変更する場合
・『14歳からはじめる（中略）』のＰ132～134参照
・ピンステータスが初期化されてしまうので、行う場合はバージョンアップ作業のはじめに行ったほうがいい
○終わりの方からコメントで囲めば、折りたたんでるコードが開かれない
○関数に引数を増やすだけの作業でもregionによるバックアップを作成する
・引数を増やす前の処理を確認しようとした時、コメント化の解除ではなく一々引数を消さなければいけない事態に陥るのを防ぐため
○エラーが起きてしまうので、struct、enumを扱う変数もcppファイルの方で定義する
○40行を超える要素のコードはregionで囲んでもいい
○変数を返す関数によって変数を変える場合、関数を単独で記入し実質何も起きないミスがよくあるので、必ず計算式になっているか確認する
○定数宣言や構造体などは、順序や入力するヘッダファイルの違いによってエラーが起こるので注意すること
・例１：Ａのヘッダファイルで宣言した構造体はＢのヘッダファイルで宣言した関数の引数に使おうとしてもでも定義されていない扱いになりエラーが起きる
　・この場合、先に宣言した関数などを修正のため移動させなければいけないので手間になる
・例２：構造体の変数に配列を使おうとし、その数字を定数（等？）にする場合、上部で先に宣言しておかないと定義されていない扱いになりエラーが起きる
・解決方としてはmain.hなど、予め『上記のようなことが起こる構造体等を格納するための場所』を用意しておけばいい？
○charは読み込みの際によくエラーが起きるので、（配列ならfor文を使って）必ず初期化する
○コードを読んだ際にenumの目的をすぐ理解できるよう、enum classは関係するクラスの
　中に入れた方が良い
○if文は『if(x == TRUE)』とせずif(x)だけでも問題ない。xはintでもいいし、0なら
　FALSE、0以外なら２以上でも－１以下でもTRUEになる
○テンプレメッセージ
// ver0.021制作時校正コメント
#pragma region ver0.031制作時コメント化コード
#pragma endregion
・regionは『ver0.001beta_b』のように『.』の後に先頭に数字がある英字を用いるとエラーが起きる（『ver0.001(beta)』なら問題ない）
○ver0.021校正コメント存在ファイル
*/
//○コメント中くくり
/* （ここにメッセージ） ---------*/
/*-------------------------------*/

#pragma region リリース作業手順
/*
１：（テストプレイヤー用でなければ）『debug_mode』をFALSEにする
２：リリース版アプリをビルドする（体験版の動作も確認したい場合は、その分もビルドする）
３：（mediaフォルダの内容が変わったなら）media.datファイルを作成する
４：動作を確認する（最適化するが故にdebug版では起こらなかったバグが起こる可能性がある）
●リリース版デバッグプレイ確認要項
○本来ならクリックしても意味のない場所をクリックしてみる
●すぐ忘れてしまうので、不具合等を確認した際は即座に記載しておく
●録画機能があるWindows10で確認することを推奨する
５：削除コード、メディアを消去し、sitagaki、newprojectのコードを適当なファイルに移す
６：（削除したものがあったか、コードを上記のファイルから移動させたなら）リリース版アプリを再びビルドする
６Ａ：動作を確認する
７：次回作業内容を記入する（最長でも20分以内で完了する可能性が高い『スモールゴール』を意識したタスクを沢山作る）
８：作業フォルダをコピペし、作業していたバージョン数値を記入する
●visualstudioの作業環境内容もあるので、『.vs』フォルダ以外のデータを（Ｄドライブに？）コピーする、という方法が一番適当である
９：タブとして出ている全てのコードをできるだけ折りたたみ、main.cpp、debugprogram.cpp、sitagaki、newproject
　　以外の作業ファイルのピンを外し、ブックマークを削除する
10：アプリタイトル、コメント、レギオン用コメントコードのバージョン数値を変更する
●いつ公開、出典することになってもいいように、アプリタイトル等目視できる部分は公開する際の数字に繰り上げる
11：ビルド環境を『Debug』に戻す
*/
#pragma endregion
//●現在の不具合（緊急度順）
/*
*/
//アップデートメモ--------
/*
●新しいアップデート内容を思いついても、現在作業中のバージョンに組み込まないようにする
○現在バージョンに搭載しようとしてまだしてないアップデート内容を次のバージョンで搭載しようとするのはいい
○小数点第３位の数値は、第三者にアプリを見せる（見せた）際に切り替える
*/
#pragma region 以降目的作業計画
/*
*/
#pragma endregion
#pragma region 宣言系統
#include "main.h"
// グローバル変数
// 時間計測用変数
int g_lasttime = 0;
float g_frametime = 0;
int g_timerstart;
// 乱数
int Ransu = 0;

GameState g_gamestate = GAME_FIRST_LOAD;
SaveFileID g_saveid = SAVE_ID_001;
CommuMessageSpeedType g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; // メッセ―ジ速度の種類

//ConfigData Data;
SystemData system_data;
CSDisplayCommuState cs_displat_commu[CS_COMMU_LIMIT];
/* CommuSaveDataクラス ---------*/
CommuSaveData commu_save_data[SAVE_DATA_NUMBER], commu_save_data_memory;	// コミュセーブデータ構造体（仮）
void CommuSaveData::SetLineJump()
{
	for (int i = 0; i < CELL_LIMIT; i++) { line_jump[i] = state::GetAlternativeMoveNumber(i); }
}
/*------------------------------*/
/* KeyTriggerクラス ---------*/
BOOL KeyTrigger::key_prev[KeyTrigger::KEY_NUMBER] = {};
BOOL KeyTrigger::Trigger(int key, KeyTrigger::Type y)
{
	int z = 0;
	switch (y)
	{
	case KeyTrigger::Type::LEFT:	z = KEY_INPUT_LEFT;		break;
	case KeyTrigger::Type::RIGHT:	z = KEY_INPUT_RIGHT;	break;
	default:												break;
	}
	if (key & z)
	{
		if (key_prev[static_cast<int>(y)] == FALSE)
		{
			key_prev[static_cast<int>(y)] = TRUE;
			return TRUE;
		}
	}
	else { key_prev[static_cast<int>(y)] = FALSE; }
	return FALSE;
}
/*---------------------------*/
/* GlobalStaticVariableクラス ---------*/
int GlobalStaticVariable::commu_number = 0;
const BOOL GlobalStaticVariable::mode_trial = TRUE;
const int GlobalStaticVariable::RESOLUTION_SIZE_ORIGINAL_X = 1920;
/*-------------------------------------*/
#pragma region BOOL変数
BOOL g_upkey_prev[2];		// 直前のＡボタンの状態
BOOL g_downkey_prev[2];		// 直前の下キーの状態
BOOL g_leftkey_prev[2];		// 直前の左キーの状態
BOOL g_rightkey_prev[2];	// 直前の右キーの状態
BOOL g_enterkey_prev[2];	// 直前のエンターキーの状態
BOOL quit_game = FALSE;			// ゲームを終了させるか判別するフラグ
BOOL flag_full_hd_ok = TRUE;	// フルＨＤによるプレイが可能か判別する
BOOL flag_full_hd_now = TRUE;	// 現在の解像度がフルＨＤか判別する
BOOL flag_mode_window = TRUE;	// フルスクリーン、ウィンドウの状態を判別するフラグ
BOOL flag_dialog_appear = TRUE;	// ダイアログボックスを出現させるフラグ
// コミュセレクト用
BOOL cfcs_move_commu[CS_COMMU_LIMIT];	// 選択されたコミュを閲覧するフラグ
// 体験版モード専用
//BOOL mode_trial = FALSE;	// 現在トライアルモードか判別する
// デバッグモード専用
BOOL mode_debug = TRUE;	// 現在デバッグモードか判別する
#pragma endregion

char OneMojiBuf[3];	// １文字分一時記憶配列

char StringBuf[STRBUF_HEIGHT][STRBUF_WIDTH + 2];	// 仮想テキストバッファ
// カーソル
int select_cursor = 0;
int mode_cursor = 2;

int title_wait_time = 0;		// タイトル画面に切り替わった時間
int now_title_wait_time = 0;	// タイトル画面に切り替わってから経過した時間
int demo_count = 0;				// デモ画面に切り替わった回数
int InputHandle;			// 文字を入力する際に必要なハンドル
int monitor_resolution_x = 0;	// メインモニターX座標
int monitor_resolution_y = 0;	// メインモニターY座標

int MouseX, MouseY;						// マウス座標取得に必要な変数
int StringSizeX, StringSizeY, StringLine;		// 文字サイズ取得に必要な変数（GetDrawStringSizeToHandle関係で高さが想定の２倍になるのは、改行を考慮している？（下から上に上げる場合、２分の１でちょうどよくなる））
int DrawPointX, DrawPointY;	// 文字列描画の位置
int SP, CP;									// 参照する文字列番号と文字列中の文字ポインタ
int EndFlag = 0;							// 文字を１文字ずつ描画する処理の終了フラグ

int screen_size_x = 1920;	// ゲームの横解像度
int screen_size_y = 1080;	// ゲームの縦解像度

float bairitu = 1.00f;	// 現在解像度に応じた各要素の倍率
// コミュセレクトモード関係
float commu_select_coordinate_alternative_y[CS_COMMU_LIMIT];	// コミュ選択肢左端y座標
/*---------------------------
共通ソース用変数
---------------------------*/
int progress_frame = 0 ;					// ゲーム開始から経過したフレーム数（１／60秒）
int progress_frame_time = GetNowCount();	// 前回の経過フレームをカウントした時間
int progress_frame_need_time = 16;			// 前回の経過フレームをカウントするのに必要な時間
#pragma endregion

#pragma region 関数
int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC)
{
	if (GlobalStaticDebug::GetLog() == FALSE) { SetOutApplicationLogValidFlag(FALSE); }	// デバッグモードでなければログが作成されないようにする
	char cpp_title[256] = "";
	char cpp_title_a[256] = "";
	sprintf_s(cpp_title, 256, "%s%s",	GlobalStaticDebug::GetLog() == TRUE ? " デバッグログ出力モード" : "", mode_debug == TRUE ? " デバッグモード" : "");
	if (GlobalStaticVariable::GetModeTrial() == FALSE){ sprintf_s(cpp_title_a, 256, "Shiny_Recollection_Trial_ver0.02%s", cpp_title); }
	else{ sprintf_s(cpp_title_a, 256, "Shiny_Recollection_StillTrial_ver0.03a%s", cpp_title); }	// 体験版用タイトル
	SetWindowText(cpp_title_a);																				// アプリケーションのタイトルを元々の『DxLib』から変更する
	// config_dataの内容を読み込む（原理不明）
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "sr_system.dat", "rb");
	if (fp == NULL){}	// 初期状態ではTRUEが適当なダイアログ表示フラグに代入する
	else
	{
		fread(&system_data, sizeof(system_data), 1, fp);
		fclose(fp);
		// 読み込んだセーブデータのＩＤが今バージョンもしくは古いバージョンか
		//if (score_data.id <= g_saveid)
		{
			flag_mode_window = system_data.full_screen;						// フルスクリーンのフラグ
			flag_full_hd_now = system_data.screen_resolution;				// 解像度のフラグ（TRUEなら1080px）
			bgm_volume = system_data.vol_bgm;								// ＢＧＭ音量
			se_volume = system_data.vol_se;									// ＳＥ音量
			text_window_clear_percentage = system_data.text_window_clear;	// テキストウィンドウ透明度
			g_commumessagespeed = system_data.string_speed;					// 文字スピード
			flag_dialog_appear = system_data.dialog_appear;					// ダイアログボックス表示フラグ
			// エディットモードでの個別読み込みフラグ
			for (int i = 0; i < CharacterImage::GetCharacterMember(); i++){CharacterImage::SetLoadEdit(i, system_data.GetECL(i));}
		}
	}
	// コミュセーブデータを読み込む
	for (int i = 0; i < SAVE_DATA_NUMBER; i++)
	{
		char c[256];
		sprintf_s(c, 256, "sr_commusave%02d.dat", i);
		err = fopen_s(&fp, c, "rb");
		if (fp == NULL) {}
		else
		{
			fread(&commu_save_data_memory, sizeof(commu_save_data_memory), 1, fp);
			fclose(fp);
			// 読み込んだセーブデータのＩＤが今バージョンもしくは古いバージョンか
			//if (score_data.id <= g_saveid)
			{
				commu_save_data[i].play_second = commu_save_data_memory.play_second;
				commu_save_data[i].ChangeTimeString(commu_save_data_memory.GetTimeString());
				commu_save_data[i].ChangeSaveData(commu_save_data_memory.GetWeek(), commu_save_data_memory.GetCommuID(), commu_save_data_memory.GetCell(), commu_save_data_memory.GetMapAppearID());
				// 行ジャンプ履歴
				for (int j = 0; j < GlobalStaticVariable::GetCellLimit(); j++){commu_save_data[i].SetLineJumpSave(j, commu_save_data_memory.GetLineJump(j));}				
				// スチル体験版で使うキャラ別のコミュを見終えたフラグ
				for (int j = 0; j < CommuSaveData::GetCharacterNumber(); j++) { commu_save_data[i].SetTrialStillViewed(j, commu_save_data_memory.GetTrialStillViewed(j)); }
			}
		}
	}
	// メインモニター解像度を取得する
	monitor_resolution_x = GetSystemMetrics(SM_CXSCREEN);
	monitor_resolution_y = GetSystemMetrics(SM_CYSCREEN);
	// モニター解像度がフルＨＤを表示できないなら、フルＨＤ表示可能フラグを降ろし、ＨＤサイズの解像度にする
	if (monitor_resolution_x < 1920 || monitor_resolution_y < 1080)
	{
		flag_full_hd_ok = FALSE;
		flag_full_hd_now = FALSE;
		flag_dialog_appear = FALSE;	// ダイアログボックスを表示させない
	}
	// 解像度選択ダイアログボックス
	if ((mode_debug == FALSE || debug_dialog_through == FALSE) && flag_dialog_appear == TRUE)
	{
		#pragma region ver0.0111制作時コメント化コード
		DialogBox(h1, TEXT("DLG1"), 0, (DLGPROC)DlgProc1);
#pragma endregion
		if (dialog_not_push == TRUE)return 0;	// 『×』ボタン等の非正規の方法でダイアログボックスを終了した場合、アプリも終了させる
	}
	else { DebugWindowChange(); }

	if (DxLib_Init() == -1) return -1;	// DXライブラリ初期化
	SetAlwaysRunFlag(TRUE);				// メインウインドウが非アクティブ状態でも処理を実行するかどうかを設定する( TRUE:実行する  FALSE:停止する( デフォルト ) )	SetMouseDispFlag(TRUE);				// マウスを表示状態にする
	ScreenResolutionChange();
	DebugProgram(DEBUG_LOAD);
	if(flag_mode_window == TRUE)
	{
		if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK) { return -1; };
	}
	SetMouseDispFlag(TRUE);										// マウスを表示状態にする
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);	// フルスクリーンモード時の解像度モードを設定する
	SetWindowIconID(283);										// ウィンドウ左上のアイコンをオリジナルのものに変更する
	if (mode_debug == FALSE){ SetDXArchiveExtension("dat"); }	// デバッグモードでなければ、datファイルをフォルダとして読み込む
	SetDXArchiveKeyString("46399292");							// ロックされたデータファイルのパスワード

	// 画像、ＢＧＭ、ＳＥ読み込み
	if (LoadGameImage() == FALSE){ return -1; }					
	LoadFont();
	BGMData::LoadFirst();
	SetDrawScreen(DX_SCREEN_BACK);				// 描画先を裏画面にする
	g_lasttime = GetNowCount();					// 現在時刻の記録
	// フルスクリーン切り替えを行っても重くならないようにする処理（仕様詳細は不明）
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);	// 画面モード変更時( とウインドウモード変更時 )にグラフィックスシステムの設定やグラフィックハンドルをリセットするかどうかを設定する( TRUE:リセットする( デフォルト )  FALSE:リセットしない )

	SetSysCommandOffFlag(1);					// タスクスイッチを有効にするかどうかを設定する（1にするとAltキーが無効化される）
	SetKeyInputCursorBrinkFlag(TRUE);			// キー入力ハンドルのキー入力時のカーソルを点滅させるかどうかをセットする
	GameMapTipsSubstitution();					// tips代入テスト
	g_time_first_load_start = GetNowCount();	// FIRST_LOADモードを開始したミリ秒を記録する

	// 専用csvファイルがあるならその内容を読み込む
	char csv_name[256] = "media\\edit_import.csv";
	struct stat st;

	if (stat(csv_name, &st) == 0)	// ファイルが存在していれば0を返す
	{ 
		char gomi[1][256];
		int FileHandle = FileRead_open("media\\edit_import.csv");
		if (FileHandle == NULL) { return FALSE; }	// エラー時の処理
		for (int i = 0; i < 1; i++) { FileRead_gets(gomi[0], 1024, FileHandle); }	// 最初の二行を読み飛ばす（何故かエラーが起きたため修正）
		for (int i = 2; i < COMMU_LINE_MAX; i++) {	// 二行目から1+n行目まで読みとる
			// 読み込み（タブスペースを空けて不具合が起きないかは不明）
			FileRead_scanf(FileHandle,
				//																																																			キャラクター・左、																				（特殊表情）											キャラクター・中、																				（特殊表情）											キャラクター・右、																				（特殊表情）											キャラクター変更タイプ、							キャラクター距離均一化のオンオフ、																		背景変更タイプ、（ＩＤ、）																	ＢＧＭ切り替えタイプ
				"%[^,],							%d[^,],									%[^,],						%[^,],						%[^,],						%[^,],		%d[^,],								%[^,],		%[^,],	%[^,],	%[^,],		%[^,],	%[^,],		%d[^,],							%[^,],			%d[^,],										%[^,],		%[^,],	%[^,],		%[^,],		%[^,],	%[^,],	%d[^,],					%[^,],					%d[^,],										%[^,],		%[^,],		%[^,],	%[^,],	%[^,],		%[^,],	%d[^,],					%[^,],					%d[^,],										%[^,],		%d[^,],									%[^,],		%d[^,],											%[^,],		%d[^,],							%[^,],		%d[^,],									%[^,],		%d[^,],			%[^,],					%d[^,],					%[^,],				%d[^,],						%[^,],										%d[^,],										%[^,],										%d[^,],										%[^,],										%d",
				&commu_state_edit[i].command,	&commu_state_edit[i].move_commu_number, &commu_state_edit[i].name,	&commu_state_edit[i].name2, &commu_state_edit[i].line,	&gomi[0],	&commu_state_edit[i].line_mouse,	&gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0],	&commu_state_edit[i].character[0], &gomi[0],	&commu_state_edit[i].character_face_etc[0],	&gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0],	&commu_state_edit[i].character[1], &gomi[0],	&commu_state_edit[i].character_face_etc[1],	&gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0],	&commu_state_edit[i].character[2], &gomi[0],	&commu_state_edit[i].character_face_etc[2], &gomi[0], &commu_state_edit[i].character_change,	&gomi[0],	&commu_state_edit[i].character_even_distance,	&gomi[0], &commu_state_edit[i].background,	&gomi[0],	&commu_state_edit[i].background_change,	&gomi[0],	&commu_state_edit[i].bgm,	&gomi[0],	&commu_state_edit[i].bgm_change, &gomi[0],	&commu_state_edit[i].se,	&commu_state_edit[i].altenative_message[0], &commu_state_edit[i].altenative_jump[0],	&commu_state_edit[i].altenative_message[1], &commu_state_edit[i].altenative_jump[1],	&commu_state_edit[i].altenative_message[2], &commu_state_edit[i].altenative_jump[2]);
		}
		FileRead_close(FileHandle);	// ファイルを閉じる
	}
	// テキストファイル読み込みテスト---
	else
	{
		// ファイルを開く（テスト）
		int FileHandle = FileRead_open("media\\めぐる出会いコミュ.txt");
		const int txt_line = 2048;	// 格納できるtxtファイルの行数（１行したの配列を変数として宣言できないため、定数にするしかない）
		char c[txt_line][256];	// 一時的にメモ帳の内容を記憶する変数
		for (int i = 0; i < txt_line; i++) { sprintf_s(c[i], 256, ""); }	// 初期化処理
		for (int i = 0; i < txt_line; i++) { FileRead_gets(c[i], 256, FileHandle); }	// 一時的な変数にメモ帳の内容を記録する
		int x = 2;
		BOOL line_output_mode = FALSE;	// 台詞編集モードフラグ
		int line_output_count = 0;		// 台詞編集モード時のカウント用変数
		for (int i = 0; i < txt_line; i++)
		{
			char c2[3] = { c[i + 1][0] , c[i + 1][1] };	// 次の行の1、2バイト目を取得し、一文字にする
			char c6[3] = { c[i][0] , c[i][1] };			// 現在の行の1、2バイト目を取得し、一文字にする
			if (strcmp(c2, "「") != 0 && strcmp(c2, "（") != 0 && line_output_mode == FALSE)
			{
				// ＢＧＭ、ＳＥを読み込む処理
				if (strcmp(c6, "△") == 0)
				{
					// 先頭5バイトが『△BGM』なら『△BGM:』を削除した文字列を比較して一致した文字列のIDを代入する
					//char c3[6] = { c[i + 1][0], c[i + 1][1], c[i + 1][2] , c[i + 1][3] , c[i + 1][4] };
					char c3[6] = { c[i][0], c[i][1], c[i][2] , c[i][3] , c[i][4] };
					if (strcmp(c3, "△BGM") == 0)
					{
						// 一致してる文字列があれば、BGMを指定する
						for (int j = 0; j < BGM_NUMBER; j++)
						{
							char c5[256];
							sprintf_s(c5, 256, "△BGM:%s", music_string[j].name);
							if (strcmp(c[i], c5) == 0) { commu_state_edit[x].BGMChange(j + 1); }
						}
					}
					// 先頭4バイトが『△SE』なら『△SE:』を削除した文字列を比較して一致した文字列のIDを代入する
					char c4[5] = { c[i][0], c[i][1], c[i][2] , c[i][3] };
					if (strcmp(c4, "△SE") == 0)
					{
						// 一致してる文字列があれば、SEを指定する
						for (int j = 0; j < SEData::GetNumber(); j++)
						{
							char c5[256];
							sprintf_s(c5, 256, "△SE:%s", se[j].GetName());
							if (strcmp(c[i], c5) == 0)
							{
								commu_state_edit[x].SEChange(j + 1);
								x++;
							}
						}
					}
				}
				else if (strcmp(c[i], "") != 0)
				{
					// line_output_countが1なら@マークをつけつ
					if (line_output_count == 0)
					{
						sprintf_s(commu_state_edit[x].line, 256, "%s", c[i]); // 文字があるならそれを構造体に代入する
						line_output_count++;
					}
					else
					{
						commu_state_edit[x].LineConnection(c[i]);
						line_output_count = 0;
						x++;
					}
				}
				else
				{
					if (line_output_count >= 1)
					{
						line_output_count = 0;
						x++;
					}
				}
			}
			else
			{
				line_output_mode = TRUE;	// 台詞編集モードにする
				// 現在の文字列を台詞主にする
				if (line_output_count == 0)
				{
					commu_state_edit[x].LineCharacterChange(0, c[i]);
					line_output_count++;
				}
				// 文字列があれば台詞を入力する
				else
				{
					if (strcmp(c[i], "") != 0)
					{
						// 先頭１文字目が『「』なら行を変える
						if (strcmp(c6, "「") == 0 && line_output_count == 2)
						{
							line_output_count = 1;
							x++;
							commu_state_edit[x].LineCharacterChange(0, commu_state_edit[x - 1].GetLineCharacterName());
						}

						if (line_output_count == 1)
						{
							// 台詞主が見つからなければ前行の台詞主を代入する
							if (strcmp(commu_state_edit[x].GetLineCharacterName(), "") == 0) { commu_state_edit[x].LineCharacterChange(0, commu_state_edit[x - 1].GetLineCharacterName()); }

							commu_state_edit[x].LineChange(c[i]);
						}
						else
						{
							commu_state_edit[x].LineConnection(c[i]);
							line_output_count = 0;
							x++;
						}
						line_output_count++;
					}
					// 台詞編集フラグをResetする
					else
					{
						line_output_count = 0;
						line_output_mode = FALSE;
						x++;
					}
				}
			}
		}

		// 最後に『end』コマンドをつける
		commu_state_edit[x].CommandChange((char*)"end");

		FileRead_close(FileHandle);
	}
	//----------------------------------

	// ムービー再生テスト
	//int MovieGraphHandle;
	//MovieGraphHandle = LoadGraph("media\\test.mp4");
	//PlayMovieToGraph(MovieGraphHandle);

	// （ウィンドウ右上の『×』やAlt+F4は、それによってProcessMessageに-1を返す処理が行われているのでウィンドウが強制的に閉じられると同時にコード通りシステムファイル保存も行われる）
	while ((ProcessMessage() == 0/* && CheckHitKey(KEY_INPUT_E) == 0*/) && quit_game == FALSE)
	{
		if (GetNowCount() - progress_frame_time >= progress_frame_need_time)	// 60ヘルツを超えるＰＣでも60フレーム毎秒で動作するようにしている
		{
			progress_frame_time = GetNowCount();
			progress_frame++;
			// 16（ミリ秒） * 20（フレーム） + 17 * 40 = 1000（ミリ秒）
			if (progress_frame % 3 == 0){ progress_frame_need_time = 16; }
			else{ progress_frame_need_time = 17; }
			// 1ループにかかった時間を計測
			int curtime = GetNowCount();
			g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
			g_lasttime = curtime;

			ClearDrawScreen();
			GetMousePoint(&MouseX, &MouseY);	// マウスの位置を取得
			GameMusic();	// ＢＧＭのフレーム処理
			switch (g_gamestate)
			{
			//case GAME_OPENING:
			//	DrawGameOpening();
			//	break;
			case GAME_FIRST_LOAD:
				g_time_load_start = GetNowCount();	// 読み込み開始時間を記録する
				DrawLoading();						// 読み込みアイコン表示
				if (LoadSE() == FALSE){ return -1; }
				// 規定ミリ秒経過していなければ強引にロード状態を続ける（テスト）
				//if (GetNowCount() <= load_test + 5000){ g_gamestate = GAME_FIRST_LOAD; }	
				break;
			case GAME_TITLE:
				GameTitle();
				break;
			case GAME_MENU:
				DrawGameMenu();
				break;
			case GAME_MAIN_COMMUNICATION:
				GameMainCommunication();
				break;
			case GAME_MAP:
				GameMap();
				break;
			case GAME_SAVELOAD:
				GameSaveLoad();
				break;
			case GAME_TUTORIAL_END:	GameTutorialEnd();	break;
			case GAME_SOUNDROOM:
				SoundRoom();
				break;
			case GAME_COMMU_SELECT:	GameCommuSelect();	break;
			case GAME_COMMU_EDIT:	GameCommuEdit();	break;
			case GAME_CLEAR:
				DrawGameClear();
				break;
			case GAME_CONFIG:
				GameConfig();
				break;
			case GAME_TUTORIAL:
				DrawGameTutorial();
				break;
			case GAME_CONTINUE:
				DrawGameContinue();
				break;
			case GAME_ENDING:
				DrawGameEnding();
				break;
			default:
				break;
			}
			DebugProgram(DEBUG_MAIN);

			// テスト
			//DrawGraph(0, 0, MovieGraphHandle, FALSE);
			//WaitTimer(10);

			ScreenFlip();
		}
	}
	// セーブ処理
	system_data.full_screen = flag_mode_window;						// フルスクリーンのフラグ
	system_data.screen_resolution = flag_full_hd_now;				// 解像度のフラグ（TRUEなら1080px）
	system_data.vol_bgm = bgm_volume;								// ＢＧＭ音量
	system_data.vol_se = se_volume;									// ＳＥ音量
	system_data.text_window_clear = text_window_clear_percentage;	// テキストウィンドウ透明度
	system_data.string_speed = g_commumessagespeed;					// 文字スピード
	system_data.dialog_appear = flag_dialog_appear;					// ダイアログボックス表示フラグ
	// エディットモードでの個別読み込みフラグ
	for (int i = 0; i < CharacterImage::GetCharacterMember(); i++){ system_data.SetECL(i, CharacterImage::GetLoadEdit(i)); }	

	err = fopen_s(&fp, "sr_system.dat", "wb");
	fwrite(&system_data, sizeof(system_data), 1, fp);

	fclose(fp);

	// コミュエディットcsvファイル作成
	if (mode_debug == TRUE)
	{
		for (int j = 0; j < 2; j++)
		{
			std::ofstream myfile;
			char csv_export_name[256] = "";
			sprintf_s(csv_export_name, 256, "");
			if (j == 0) { sprintf_s(csv_export_name, 256, "media\\commu\\edit.csv"); }
			// エクスポート用（現在年月日時刻を得る）
			else
			{
				DATEDATA Date;		// DXライブラリ独自の構造体
				GetDateTime(&Date);	// 現在時刻を得る
				sprintf_s(csv_export_name, 256, "media\\export\\edit_%04d%02d%02d_%02d%02d%02d.csv", Date.Year, Date.Mon, Date.Day, Date.Hour, Date.Min, Date.Sec);
			}

			myfile.open(csv_export_name);
			myfile << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,終点\n";
			//myfile << "a,b,c,\n";
			//myfile << "c,s,v,\n";
			for (int i = 2; i < COMMU_LINE_MAX; i++)
			{
				char c_csv[512];
				sprintf_s(c_csv, 512, "%s,%d,%s,%s,%s,,%d,,,,,,,%d,,%d,,,,,,,%d,,%d,,,,,,,%d,,%d,,%d,,%d,,%d,,%d,,%d,,%d,,%d,%s,%d,%s,%d,%s,%d\n",
					commu_state_edit[i].GetCommand(),
					commu_state_edit[i].GetCommandNumber(),
					commu_state_edit[i].GetLineCharacterName(),
					commu_state_edit[i].GetLineCharacterName2(),
					commu_state_edit[i].GetLine(),
					commu_state_edit[i].GetLineMouse(),
					commu_state_edit[i].GetCharacter(0),
					commu_state_edit[i].GetCFE(0),
					commu_state_edit[i].GetCharacter(1),
					commu_state_edit[i].GetCFE(1),
					commu_state_edit[i].GetCharacter(2),
					commu_state_edit[i].GetCFE(2),
					commu_state_edit[i].GetCC(),
					commu_state_edit[i].GetCDU(),
					commu_state_edit[i].GetBackground(),
					commu_state_edit[i].GetBackgroundChangeType(),
					commu_state_edit[i].GetBGM(),
					commu_state_edit[i].GetBGMCT(),
					commu_state_edit[i].GetSE(),
					commu_state_edit[i].GetAlternativeString(0),
					commu_state_edit[i].GetAlternativeJump(0),
					commu_state_edit[i].GetAlternativeString(1),
					commu_state_edit[i].GetAlternativeJump(1),
					commu_state_edit[i].GetAlternativeString(2),
					commu_state_edit[i].GetAlternativeJump(2)
				);
				myfile << c_csv;
			}
			myfile.close();
		}
	}

	// （デバッグ用）使われてない背景のデータをログに出力
	DebugLog(LogOutputType::NOT_USE_BACKGROUND);
	// DXライブラリの終了処理
	DxLib_End();

	return 0;
}
// 画面解像度を定義する
void ScreenResolutionChange()
{
	// 解像度定義に必要な変数を代入する
	if (flag_full_hd_now == TRUE)
	{
		screen_size_x = 1920;
		screen_size_y = 1080;
	}
	else
	{
		screen_size_x = 1280;
		screen_size_y = 720;
	}
	bairitu = (float)screen_size_y / WINDOW_SIZE_Y;	// 文字や画像の倍率を再定義する
	font[0].ChangeMagnification(bairitu);
	SetGraphMode(screen_size_x, screen_size_y, 32);	// ウィンドウサイズを変更する（ここが画面を点滅させてる）
	SetDrawScreen(DX_SCREEN_BACK);				// 描画先を裏画面にする
}
// タイトルデモ画面描画
void DrawGameOpening()
{
}
// メニュー画面描画
void DrawGameMenu()
{
}
// ゲームクリア画面描画
void DrawGameClear()
{
}
// 説明モード
void DrawGameTutorial()
{
}
// コンテニュー画面
void DrawGameContinue()
{
}
// エンディング
void DrawGameEnding()
{
}
// キートリガー処理（上キー）
BOOL IsUPKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_UP)
	{
		if (g_upkey_prev[y] == FALSE)
		{
			g_upkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_upkey_prev[y] = FALSE; }

	return FALSE;
}
// キートリガー処理（下キー）
BOOL IsDOWNKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_DOWN)
	{
		if (g_downkey_prev[y] == FALSE)
		{
			g_downkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_downkey_prev[y] = FALSE; }

	return FALSE;
}
// キートリガー処理（左キー）
BOOL IsLEFTKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_LEFT)
	{
		if (g_leftkey_prev[y] == FALSE)
		{
			g_leftkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_leftkey_prev[y] = FALSE; }

	return FALSE;
}
// キートリガー処理（右キー）
BOOL IsRIGHTKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_RIGHT)
	{
		if (g_rightkey_prev[y] == FALSE)
		{
			g_rightkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_rightkey_prev[y] = FALSE; }

	return FALSE;
}
// キートリガー処理（エンターキー）
BOOL IsENTERKeyTrigger(int key, int y)
{
	// （チェックヒットキー？）
	if (CheckHitKey(KEY_INPUT_NUMPADENTER) == TRUE)
	{
		if (g_enterkey_prev[y] == FALSE)
		{
			g_enterkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else { g_enterkey_prev[y] = FALSE; }

	return FALSE;
}
// クリックされたタイミングや状況に応じたフラグを返す
BOOL ClickFlagCheck(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a)	// クリックx座標,クリックy座標,判定左端x座標,判定上端y座標,座標横幅,座標縦幅,左ボタンが押されたか離されたか判別するフラグ,条件として使用する変数（zがTRUEなら『FALSE』でいい）
{
	if (z == TRUE)
	{	
		// クリックの座標が判定の範囲内ならTRUEを返す
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1){  return TRUE; }
	}
	else
	{
		// クリックの座標が判定の範囲内であり、押した時のフラグも立っているならTRUEを返す
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1 && a == TRUE){ return TRUE; }
	}
	return FALSE;
}
// クリックされたタイミングや状況に応じたフラグを返す（float変数『bairitu』をかける）
BOOL ClickFlagCheck2(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a)	// クリックx座標,クリックy座標,判定左端x座標,判定上端y座標,座標横幅,座標縦幅,左ボタンが押されたか離されたか判別するフラグ,条件として使用する変数（zがTRUEなら『FALSE』でいい）
{
	if (z == TRUE)
	{
		// クリックの座標が判定の範囲内ならTRUEを返す
		if (Cx >= Jx * bairitu && Cx <= (Jx - 1) * bairitu + breadth && Cy >= Jy * bairitu && Cy <= (Jy + length - 1) * bairitu){ return TRUE; }
	}
	else
	{
		// クリックの座標が判定の範囲内であり、押した時のフラグも立っているならTRUEを返す
		if (Cx >= Jx * bairitu && Cx <= (Jx - 1) * bairitu + breadth && Cy >= Jy * bairitu && Cy <= (Jy + length - 1) * bairitu && a == TRUE){ return TRUE; }
	}
	return FALSE;
}
// クリックされたタイミングや状況に応じたフラグを返す（列挙定数に応じて条件のフラグが追加される）
BOOL ClickFlagCheckF2(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, ClickFlagCheckType type)	// クリックx座標,クリックy座標,判定左端x座標,判定上端y座標,座標横幅,座標縦幅,左ボタンが押されたか離されたか判別するフラグ,条件として使用する変数（zがTRUEなら『FALSE』でいい）,呼び出しタイミング（判定の有無を判別する列挙定数）
{
	if (z == TRUE)
	{
		// クリックの座標が判定の範囲内であり、『type』毎の条件を満たしている（当たり判定が存在している）ならTRUEを返す
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1)
		{ 
			switch(type)
			{
			case CFC_COMMU_MENU:	if (commu_mode_menu == TRUE && commu_mode_text_off == FALSE) { return TRUE; }	break;
			case CFC_COMMU_TEXT:	if (commu_mode_text_off == FALSE) { return TRUE; }								break;
			default:				return TRUE;																	break;
			}
		}
	}
	else
	{
		// クリックの座標が判定の範囲内であり、押した時のフラグも立っているならTRUEを返す
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1 && a == TRUE) { return TRUE; }
	}
	return FALSE;
}

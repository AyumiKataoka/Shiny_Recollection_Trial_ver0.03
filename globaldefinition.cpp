#include "globaldefinition.h"

BackgroundChangeType g_backgroundchange;	// 背景変更方法の種類
/* stateクラス ---------*/
int state::alternative_move_number[COMMU_LINE_MAX] = {};
state HM[512][COMMU_LINE_MAX], commu_state_edit[COMMU_LINE_MAX + 1];
/*----------------------*/
//							オプションでアイコンでもなく変動しないもの（机、紙、文字、タイトル、解像度×２）、	オプション選択肢用矢印、	メッセージ速度、				画面モードの種類
ImgData image_dialog[2],	image_option[6],																	image_option_arrow[2],		image_option_message_speed[3],	image_option_window_type[2],
//													注意文												マップ選択時背景
		image_text_window[2][4], image_icon_option,	image_cautionary_message, image_icon_commu_edit,	image_map_background;
//			タイトル画面用、マップ画面用、									選択肢
ImgDataHJ	hjimage_title,	hjimage_map[HIT_JUDGEMENT_IMAGE_NUMBER_MAP],	hjimage_alternative[ALTENATIVE_MAX_NUMBER];
/* ImgDataBGクラス ---------*/
#pragma region ver0.00704制作時コメント化コード
//ImgDataBG bgimage[BACKGROUND_NUMBER] = {
#pragma endregion
ImgDataBG bgimage[] = {
	{(char*)"めぐるの部屋"},				{(char*)"家庭科室"},					{(char*)"河川敷"},						{(char*)"通学路"},						{(char*)"カフェテラス"},
	{(char*)"1F西棟廊下"},					{(char*)"掲示板前"},					{(char*)"千雪の前任校"} ,				{(char*)"教室"} ,						{(char*)"職員室"} ,
	{(char*)"バスケストリートコート"},		{ (char*)"大等部教室" },				{(char*)"空き教室"},					{ (char*)"2F西棟廊下" },				{ (char*)"1F東棟廊下" },
	{ (char*)"2F東棟廊下" } ,				{(char*)"学校階段"},					{ (char*)"旧校舎廊下" },				{ (char*)"食堂" },						{ (char*)"食堂・夕" },
	{ (char*)"食堂・夜" } ,					{(char*)"校長室"},						{ (char*)"図書室" },					{ (char*)"音楽室" },					{ (char*)"事務室" },
	{ (char*)"天文部部室" } ,				{ (char*)"校舎裏、校内ベンチ" },		{ (char*)"校舎裏、校内ベンチ・夕" },	{ (char*)"屋上" },						{ (char*)"屋上・夕" } ,
	{(char*)"屋上・夜"},					{ (char*)"噴水広場" },					{ (char*)"グラウンド" },				{ (char*)"講堂" },						{ (char*)"講堂・夜" } ,
	{ (char*)"講堂・壇上" } ,				{ (char*)"天翔の鐘" } ,					{(char*)"校舎が見える校舎裏"},			{ (char*)"ショッピングモール" },		{ (char*)"街中" },
	{ (char*)"星空" },						{ (char*)"めぐる空き教室" },			{(char*)"白背景"},						{(char*)"説明コミュ用事務室"},			{(char*)"説明コミュ用事務室・電気OFF"}, 
	{ (char*)"めぐるＦスチル" },			{ (char*)"教室・セピア" },				{ (char*)"空き教室・セピア" },			{ (char*)"2F西棟廊下・セピア" },		{ (char*)"学校階段・セピア" },
	{ (char*)"（仮）生徒会室" },			{ (char*)"（仮）生徒会室・夕" },		{ (char*)"（仮）生徒会室・点灯" },		{ (char*)"（仮）生徒会室・消灯" },		{ (char*)"校舎裏、校内ベンチ・夜" }, 
	{(char*)"（仮）商店街" },				{ (char*)"（仮）商店街・夕" },			{ (char*)"（仮）商店街・夜" },			{ (char*)"（仮）放送室・１" },			{ (char*)"（仮）放送室・２" },
	{ (char*)"（仮）放送室・３" },			{ (char*)"（仮）放送室・４" },			{ (char*)"（仮）放送室・５" },			{ (char*)"（仮）放送室・６" },			{ (char*)"（仮）Ｆスチル・紅葉" }, 
	{ (char*)"（仮）めぐるスチル・１" },	{ (char*)"（仮）めぐるスチル・２" },	{ (char*)"（仮）めぐるスチル・４" },	{ (char*)"（仮）恋鐘スチル・１" },		{ (char*)"（仮）樹里スチル・１" },
	{ (char*)"（仮）樹里スチル・２" },		{ (char*)"（仮）樹里スチル・３" },		{ (char*)"（仮）樹里スチル・４" },		{ (char*)"（仮）凛世スチル・１" },		{ (char*)"（仮）凛世スチル・２" },
	{ (char*)"（仮）千雪スチル・１" },		{ (char*)"（仮）千雪スチル・３" },		{ (char*)"噴水広場・夜" },				{ (char*)"噴水広場・停電" },			{ (char*)"2F東棟廊下・夕" },
	{ (char*)"校門前・夕" },				{ (char*)"教室・夕" },					{ (char*)"教室・夜" },					{ (char*)"教室・停電" },				{ (char*)"1F西棟廊下・夕" },
	{ (char*)"1F西棟廊下・夜" },			{ (char*)"1F西棟廊下・停電" },			{ (char*)"2F西棟廊下・夕" },			{ (char*)"2F西棟廊下・夜" },			{ (char*)"2F東棟廊下・夕" },
	{ (char*)"2F東棟廊下・夜" },			{ (char*)"学校階段・夕" },				{ (char*)"学校階段・停電" },			{ (char*)"ブティック" },				{ (char*)"第二体育館出入口側" } ,
	{ (char*)"第二体育館出入口側・雨" } ,	{ (char*)"第二体育館出入口側・夕" } ,	{ (char*)"第二体育館出入口側・夜" } ,	{ (char*)"第二体育館出入口側・停電" } ,	{ (char*)"第二体育館出入口側・ゆがみ" },
	{ (char*)"家庭科室・セピア" } };
int ImgDataBG::number = 0;
ImgDataBG::ImgDataBG(char* c)
{
	sprintf_s(name, 256, c);
	number++;
	// エディットモードで使われる背景選択肢の最大行数を変更する
	GlobalStaticEdit::SetBackgroundAlternativeLineLimit(number / GlobalStaticEdit::GetBackgroundAlternativeLineNumber() + 1);
}
/*--------------------------*/
float MagnificationData::magnification = 1.00f;
int ImgDataBGTutorial::number = 0;
int ImgDataBGTutorial::draw_image_number = 0;
float ImgDataBGTutorial::screen_y = 0;
const int ImgDataBGTutorial::SCREEN_Y_INITIAL = -1080;
ImgDataBGTutorial tutorial_image[] = {
	{(char*)"media\\background\\tutorial\\info_screen.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map1.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map2.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map3.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map4.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map5.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map6.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map7.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map8.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map9.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map10.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map11.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map12.png"},
	{(char*)"media\\background\\tutorial\\info_screen_map13.png"},
	{(char*)"media\\background\\tutorial\\info_screen_system1.png"},
	{(char*)"media\\background\\tutorial\\info_screen_system2.png"},
	{(char*)"media\\background\\tutorial\\info_screen_system3.png"}};
// スクリーンのＹ座標をずらす
void ImgDataBGTutorial::ScreenYMove()
{
	float y = SCREEN_Y_INITIAL * magnification;
	float x = y / -138;	// １フレームに移動する値
	if(cell_number + 2 >= 27 && cell_number + 2 <= 122)
	{ 
		if ((screen_y += x) > 0) { screen_y = 0; }
	}
	else
	{
		if ((screen_y -= x) <= y) { screen_y = y; }
	}
}
// 要素をリセットする
void ImgDataBGTutorial::Reset()
{
	draw_image_number = 0;
	screen_y = SCREEN_Y_INITIAL;
}
/* ImaDataNameクラス ---------*/
ImaDataName image_title_border[ImaDataName::TITLE_BORDER_NUMBER];
// 倍率を見込んだ上で座標値を定義する
void ImaDataName::CoordinateSettingName(float x, float y)
{
	coordinate_x = x * magnification;
	coordinate_y = y * magnification;
}
/*----------------------------*/
/* ImgData2クラス ---------*/
int ImgData2::notice_count = 0;							// 警告文背景の透明度調整用数値
const int ImgData2::NOTICE_COUNT_MILLI_SECOND = 1000;	// 警告文背景の透明度調整に必要なミリ秒
ImgData2 bgimage_notice = {(char*)"media\\background\\notice.png"} ;
ImgData2 bgimage_title = { (char*)"media\\background\\title\\title_base.png" };
ImgData2 image_title_logo = { (char*)"media\\background\\title\\title_logo.png" };
ImgData2 image_title_logo_stilltrial = { (char*)"media\\background\\title\\title_stilltrial.png" };
ImgData2 bgimage_sukashi = { (char*)"media\\background\\sukasi.png" };
ImgData2 image_finish_check = { (char*)"media\\UI\\save_load\\finish_.png" };
ImgData2 bgimage_room_teacher = { (char*)"media\\background\\board_pr001_00.png" };
ImgData2 image_saveload_mode[2] = {
	{(char*)"media\\UI\\save_load\\mode_load.png"},
	{(char*)"media\\UI\\save_load\\mode_save.png"} };
ImgData2 image_bl_background[ImgData2::LOG_BACKGROUND_NUMBER] = {
	{(char*)"media\\UI\\back_log\\background.png" },
	{(char*)"media\\UI\\back_log\\logo.png" }};
ImgData2 image_map_character[ImgData2::IMC_NUMBER] = {
	{(char*)"media\\UI\\map_player.png"},
	{(char*)"media\\UI\\map_meguru.png"},
	{(char*)"media\\UI\\map_kogane.png"},
	{(char*)"media\\UI\\map_juri.png"},
	{(char*)"media\\UI\\map_rinze.png"},
	{(char*)"media\\UI\\map_chiyuki.png"},
	{(char*)"media\\UI\\map_hazuki.png"},
	{(char*)"media\\UI\\map_tsutomu.png"},
	{(char*)"media\\UI\\map_mob.png"} };
ImgData2 image_log_text_window[ImgData2::LOG_TEXT_WINDOW_NUMBER] = {
	{(char*)"media\\UI\\back_log\\text_window_default.png"},
	{(char*)"media\\UI\\back_log\\text_window_blue.png"},
	{(char*)"media\\UI\\back_log\\text_window_pink.png"},
	{(char*)"media\\UI\\back_log\\text_window_green.png"},
	{(char*)"media\\UI\\back_log\\text_window_gray.png"}};
ImgData2 bgimage_non_month = { (char*)"media\\UI\\map_frame\\frame_non_0.png" };
// 倍率を見込んだ上で座標値を定義する
void ImgData2::CoordinateSetting2(float x, float y)
{
	coordinate_x = x * magnification;
	coordinate_y = y * magnification;
}
void ImgData2::DrawImageNotice()
{
	// 1000ミリ秒かけて描画させる
	if (notice_count == 0) { notice_count = GetNowCount(); }
	int x = (GetNowCount() - notice_count > NOTICE_COUNT_MILLI_SECOND) ? NOTICE_COUNT_MILLI_SECOND : GetNowCount() - notice_count;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, x * 255 / NOTICE_COUNT_MILLI_SECOND);
	DrawExtendGraphF(coordinate_x, coordinate_y, (float)screen_size_x, (float)screen_size_y, Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
/*-------------------------*/
/* ImgDataHJ2クラス ---------*/
ImgDataHJ2 image_icon_save_file[GlobalStaticSaveLoad::FILE_NUMBER][2] = {
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} ,
	{{ (char*)"media\\UI\\icon\\save_no_deta.png" }, { (char*)"media\\UI\\icon\\save_file_frame.png" }} };
ImgDataHJ2 image_icon_sl_page[GlobalStaticSaveLoad::FILE_PAGE_NUMBER] = {
	{(char*)"media\\UI\\save_load\\page1.png"},
	{(char*)"media\\UI\\save_load\\page2.png"},
	{(char*)"media\\UI\\save_load\\page3.png"},
	{(char*)"media\\UI\\save_load\\page4.png"},
	{(char*)"media\\UI\\save_load\\page5.png"},
	{(char*)"media\\UI\\save_load\\page6.png"} };
ImgDataHJ2 image_icon_new_option[ImgDataHJ2::OPTION_ICON_NUMBER] = {
	{(char*)"media\\UI\\icon\\option\\save.png"},
	{(char*)"media\\UI\\icon\\option\\load.png"},
	{(char*)"media\\UI\\icon\\option\\back.png"},
	{(char*)"media\\UI\\icon\\option\\title.png"},
	{(char*)"media\\UI\\icon\\option\\exit.png"}};
ImgDataHJ2 image_icon_config_dialog[2][2] = {
	{{ (char*)"media\\UI\\icon\\option\\option_on.png" }, { (char*)"media\\UI\\icon\\option\\orangeon.png" }} ,
	{{ (char*)"media\\UI\\icon\\option\\option_off.png" }, { (char*)"media\\UI\\icon\\option\\orangeoff.png" }} };
ImgDataHJ2 image_icon_config_text_speed[3][2] = {
	{{ (char*)"media\\UI\\icon\\option\\slow.png" }, { (char*)"media\\UI\\icon\\option\\orange slow.png" }} ,
	{{ (char*)"media\\UI\\icon\\option\\normal.png" }, { (char*)"media\\UI\\icon\\option\\orange normal.png" }} ,
	{{ (char*)"media\\UI\\icon\\option\\fast.png" }, { (char*)"media\\UI\\icon\\option\\orangefast.png" }} };
ImgDataHJ2 image_icon_map_move_alternative[2] = {
	{(char*)"media\\UI\\icon\\map\\yes.png"},
	{(char*)"media\\UI\\icon\\map\\no.png"} };
ImgDataHJ2 image_icon_map_collision_detection = {(char*)"media\\UI\\icon\\map\\collision_detection.png"} ;
ImgDataHJ2 image_icon_log = { (char*)"media\\UI\\icon\\menu_log.png" };
ImgDataHJ2 image_icon_log_back = { (char*)"media\\UI\\icon\\text_log\\log_close.png" };
ImgDataHJ2 image_icon_text_log[ImgDataHJ2::TEXT_LOG_ARROW_NUMBER] = {
	{(char*)"media\\UI\\icon\\text_log\\left_end.png"},
	{(char*)"media\\UI\\icon\\text_log\\prev.png"},
	{(char*)"media\\UI\\icon\\text_log\\next.png"},
	{(char*)"media\\UI\\icon\\text_log\\right_end.png"}};
// 条件付きクリック判定処理を行う
BOOL ImgDataHJ2::JudgementClickCheckFlag(BOOL x)
{
	if (ClickFlagCheckF(ClickX, ClickY, coordinate_x, coordinate_y, size_x, size_y, TRUE, FALSE) == TRUE && x == TRUE)
	{
		click_judgement = TRUE;
		return TRUE;
	}
	return FALSE;
}
/*---------------------------*/
/* ImgDataTutorialEndクラス ---------*/
BOOL ImgDataTutorialEnd::white_out = FALSE;
int ImgDataTutorialEnd::count = 0;					// 体験版アンケート背景の透明度調整用数値 
int ImgDataTutorialEnd::count_wait = 0;				// 体験版終了モードで操作可能になるのに必要なカウント数値
const int ImgDataTutorialEnd::COUNT_LIMIT = 180;	// 体験版アンケート背景の透明度調整用の限界数値
ImgDataTutorialEnd bgimage_tutorial_end = { (char*)"media\\background\\questionnaire_haduki.png" };
// 体験版終了背景専用の描画処理
void ImgDataTutorialEnd::DrawImageTutorialEnd()
{
	// カウント処理
	if (white_out == FALSE && count < COUNT_LIMIT) { count++; }
	else if (white_out == TRUE && count > 0) { count--; }
	if (count >= COUNT_LIMIT) { count_wait++; }
	else if (white_out == TRUE && count <= 0)
	{ 
		count_wait++;
		// とりあえず３秒
		if (count_wait >= COUNT_LIMIT) 
		{ 
			ImgDataHJTitle::SetCountFrame(0);
			GameTitleNext();
			SEPlay(static_cast<int>(SEData::IDName::START_EFFECT));	// 専用のＳＥを再生
		}	
	}
	// 描画
	DrawExtendGraphF(coordinate_x, coordinate_y, (float)screen_size_x, (float)screen_size_y, Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COUNT_LIMIT - count) * 255 / COUNT_LIMIT);
	DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
// 体験版終了に必要な要素をリセットする
void ImgDataTutorialEnd::CountReset()
{
	white_out = FALSE;
	count = 0;	// 念のため
	count_wait = 0;
}
/*-----------------------------------*/
/* ImgDataMapFrameクラス ---------*/
ImgDataMapFrame ui_map_month[] = {
	{(char*)"media\\UI\\map_frame\\frame_April_1.png"},
	{(char*)"media\\UI\\map_frame\\frame_April_2.png"},
	{(char*)"media\\UI\\map_frame\\frame_April_3.png"},
	{(char*)"media\\UI\\map_frame\\frame_April_4.png"},
	{(char*)"media\\UI\\map_frame\\frame_May_1.png"},
	{(char*)"media\\UI\\map_frame\\frame_May_2.png"} };
int ImgDataMapFrame::frame_number = 0;
/*--------------------------------*/
/* ImgDataMapQuestionクラス ---------*/
ImgDataMapQuestion image_map_question[] = {
	{(char*)"media\\UI\\map_question\\meguru_heroine.png"},
	{(char*)"media\\UI\\map_question\\kogane_heroine.png"},
	{(char*)"media\\UI\\map_question\\juri_heroine.png"},
	{(char*)"media\\UI\\map_question\\rinze_heroine.png"},
	{(char*)"media\\UI\\map_question\\chiyuki_heroine.png"},
	{(char*)"media\\UI\\map_question\\all_friend.png"} };
int ImgDataMapQuestion::number = 0;
/*-----------------------------------*/
/* ImgDataTitleCharacterクラス ---------*/
ImgDataTitleCharacter image_title_character[] = {
	{(char*)"media\\character\\title\\title_kogane.png"},
	{(char*)"media\\character\\title\\title_chiyuki.png"},
	{(char*)"media\\character\\title\\title_rinze.png"},
	{(char*)"media\\character\\title\\title_juri.png"},
	{(char*)"media\\character\\title\\title_meguru.png"},
};
int ImgDataTitleCharacter::character_number = 0;
/*--------------------------------------*/
/* ImgDataSLCheckクラス ---------*/
ImgDataSLCheck image_sl_check_message[] = {
	{(char*)"media\\UI\\save_load\\save_ok.png"},
	{(char*)"media\\UI\\save_load\\load_ok.png"}};
int ImgDataSLCheck::image_number = 0;
/*-------------------------------*/
/* ImgDataHJTitleクラス ---------*/
BOOL ImgDataHJTitle::flag_count = FALSE;
int ImgDataHJTitle::menu_number = 0;
int ImgDataHJTitle::count_frame = 0;				// タイトル画面での経過フレーム数
ImgDataHJTitle image_title_menu[][2] = {
	{{(char*)"media\\UI\\icon\\title_select_start.png", TRUE} ,{(char*)"media\\UI\\icon\\title_select_start_on.png", FALSE}},
	{ {(char*)"media\\UI\\icon\\title_select_load.png", TRUE} ,{(char*)"media\\UI\\icon\\title_select_load_on.png", FALSE}},
	{ {(char*)"media\\UI\\icon\\title_select_continue.png", TRUE} ,{(char*)"media\\UI\\icon\\title_select_continue_on.png", FALSE}},
	{ {(char*)"media\\UI\\icon\\title_select_option.png", TRUE} ,{(char*)"media\\UI\\icon\\title_select_option_on.png", FALSE}},
	{ {(char*)"media\\UI\\icon\\title_select_extra.png", TRUE} ,{(char*)"media\\UI\\icon\\title_select_extra_on.png", FALSE}},
	{ {(char*)"media\\UI\\icon\\title_select_exit.png", TRUE} ,{(char*)"media\\UI\\icon\\title_select_exit_on.png", FALSE}}
};
void ImgDataHJTitle::DrawTitleImage()
{
	// ベース背景
	//if(mode_debug == FALSE){ image_title_border[0].DrawImage(); }
	//else {image_title_border[count_frame % ImaDataName::GetTitleBorderNumber()].DrawImage();}
	image_title_border[count_frame % ImaDataName::GetTitleBorderNumber()].DrawImage();
	//image_title_border[count_frame / 9 % ImaDataName::GetTitleBorderNumber()].DrawImage();
	DrawExtendGraphF(bgimage_title.GetCoordinateX(), bgimage_title.GetCoordinateY(), (float)screen_size_x, (float)screen_size_y, bgimage_title.GetHandle(), TRUE);
	// キャラ画像
	const int X = 60;			// １人のキャラを出現させきるのに必要なフレーム数
	const int X_DISTANCE = 36;	// 次のキャラが出るまでの間隔
	for(int i = 0; i < ImgDataTitleCharacter::GetTitleCharacterNumber(); i++)
	{ 
		// 規定経過フレーム数を満たしていなければそもそも描画されない
		if (count_frame > i * X_DISTANCE)
		{
			int y = (count_frame < i * X_DISTANCE + X) ? count_frame - i * X_DISTANCE : X;	// 透過度用カウント
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, y * 255 / X);
			DrawExtendGraphF(image_title_character[i].GetCoordinateX(), image_title_character[i].GetCoordinateY(), (float)screen_size_x, (float)screen_size_y, image_title_character[i].GetHandle(), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	// タイトルロゴ
	int x = (ImgDataTitleCharacter::GetTitleCharacterNumber() - 1) * X_DISTANCE + X;
	const int Y = 60;	// タイトルロゴを出現させきるのに必要なフレーム数
	if(count_frame > x)
	{
		int y = (count_frame < x + Y ? count_frame - x : Y);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, y * 255 / Y);
		image_title_logo.DrawImage();
		image_title_logo_stilltrial.DrawImage();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// メニューアイコン
	int f = x + Y;
	const int Z = 20;	// １つのアイコンを出現させきるのに必要なフレーム数
	for(int i = 0; i < ImgDataHJTitle::GetMenuNumber(); i++)
	{
		if (count_frame > f + i * (Z / 2))
		{
			int y = (count_frame < f + Z + i * (Z / 2)) ? count_frame - (f + i * (Z / 2)): Z;
			// 表示させる際に備えて２種類座標を定義しておく
			for (int j = 0; j < 2; j++){image_title_menu[i][j].CoordinateSetting(screen_size_x - y * image_title_menu[i][j].GetSizeX() / Z, screen_size_y - (ImgDataHJTitle::GetMenuNumber() - i - 1) * image_title_menu[0][0].GetSizeY() * 1.25f - image_title_menu[0][0].GetSizeY() * 2);}
			// マウスカーソルがアイコンの範囲内だったら専用の画像を描画するようにする変数
			BOOL b = (MouseX >= image_title_menu[i][0].GetCoordinateX() && MouseX < screen_size_x && MouseY >= image_title_menu[i][0].GetCoordinateY() && MouseY < image_title_menu[i][0].GetCoordinateY() + image_title_menu[i][0].GetSizeY()) ? TRUE : FALSE;
			// 『EXTRA』だったら
			image_title_menu[i][b].DrawImage();
		}
		// 左上or見えないけど本来アイコンが置かれる場所をクリックするとまだ見えていなくても判定が行われる不具合の予防処理
		else 
		{
			for (int j = 0; j < 2; j++) { image_title_menu[i][j].CoordinateSetting((float)screen_size_x, 0); }
		}
	}
	// 全ての要素が表示されきっていて、かつスタートを押してなければBGMを流す
	#pragma region ver0.017制作時コメント化コード
	//if (count_frame >= f + Z + Z / 2 * ImgDataHJTitle::GetMenuNumber() - 1 && CheckSoundMem(g_sndhandles.BGM[BN_TITLE]) == 0 && flag_next_start == FALSE) { MusicPlay(BN_TITLE); }
#pragma endregion
	if (count_frame >= f + Z + Z / 2 * ImgDataHJTitle::GetMenuNumber() - 1 && CheckSoundMem(bgm[BN_TITLE].GetHandle()) == 0 && flag_next_start == FALSE) { MusicPlay(BN_TITLE); }
	count_frame++;	// 経過フレームカウント	
}
/*-------------------------------*/
/* ImgDataIconCheckクラス ---------*/
ImgDataIconCheck image_icon_check[2] = {
	{(char*)"media\\UI\\move_comu_check_ok.png"},
	{(char*)"media\\UI\\move_comu_check_no.png"} };
const int ImgDataIconCheck::IMAGE_NUMBER = 2;
/*---------------------------------*/
/* ImgDataIconMapCharacterクラス ---------*/
ImgDataIconMapCharacter image_icon_map_character[] = {
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_mg.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_kg.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_jr.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_rn.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_cy.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_all.png"} };
#pragma region ver0.00904制作時コメント化コード
//const int ImgDataIconMapCharacter::NUMBER = 5;
#pragma endregion
int ImgDataIconMapCharacter::number = 0;
/*----------------------------------------*/
/* FontDataクラス ---------*/
int FontData::font_number = 0;
// ＭＳ系フォント、メイリオ以外のWindows搭載フォントはライセンス許諾の必要がある
FontData font[] = {
	{(char*)"メイリオ",	27},
	{(char*)"メイリオ", 48},
	{(char*)"メイリオ", 40},
	{(char*)"メイリオ", 36},
	{(char*)"ＭＳ ゴシック", 45},
	{(char*)"メイリオ", 24} ,
	{(char*)"メイリオ", 33} };
void FontData::Create()
{
	handle = CreateFontToHandle(name, (int)(size * magnification), -1, DX_FONTTYPE_ANTIALIASING);
	// 定義フォントに『あ』がない場合、フォントをメイリオにする
	if (GetFontCharInfo(handle, "あ", NULL, NULL, NULL, NULL, NULL) < 0)
	{
		// 文字がない
		handle = CreateFontToHandle("メイリオ", (int)(size * magnification), -1, DX_FONTTYPE_ANTIALIASING);
		quit_game = TRUE;	// フォントがきちんと追加されたか確認するコード
	}
	else
	{
		// 文字がある
	}
}
/*-------------------------*/

StringData line_character = { GetColor(20, 20, 20), 1};
/* SaveDataImageクラス ---------*/
SaveDataImage save_data_image[SaveDataImage::LIMIT_NUMBER];
void SaveDataImage::SetCoordinate(float x, float y)
{
	coordinate_x = x * magnification;
	coordinate_y = y * magnification;
}
// 画像を合成する
void SaveDataImage::Blend(int x, BOOL y)	// コミュ背景でなく全体マップを描画するか
{
	namespace fs = std::filesystem;			// 『fs』という単語に『std::filesystem』という意味を持たせている？
	std::string folder_path = "savedata";	// 確認するフォルダのパス
	// フォルダが存在しなければ
	if (!fs::exists(folder_path))
	{
		// 例外処理tryを開始し、例外が発生すればcaych内の処理を実行する
		try{fs::create_directories(folder_path);}
		catch(const std::exception& ex)
		{
			std::cerr << ex.what() << '\n';	// エラーメッセージを表示する
			quit_game = TRUE;
		}
	}
	else{}

	// コミュ背景（ここを変えればコミュ時のサムネバグが修正できると思うが背景用
	// のＩＤは後々配列定数に変える予定なのでまだ修正しない）
	int h;
	if (y == FALSE)
	#pragma region ver0.016制作時コメント化コード
		//{h = commu_background;}
#pragma endregion
	{
		if (GlobalStaticSaveLoad::GetSamuneBackgroundID() > 0)
		{
			char c[256];
			sprintf_s(c, 256, "media\\background\\board_%03d.png", GlobalStaticSaveLoad::GetSamuneBackgroundID());	// 100未満でも必ず３桁にする
			h = LoadGraph(c);
			if (h == -1)
			{
				quit_game = TRUE;
				return;
			}
		}
	}
	// マップ背景
	else
	{
		//h = image_map_background.GetHandle();
		h = LoadGraph("media\\background\\map_BG.png");
		if (h == -1) 
		{
			quit_game = TRUE;
			return; 
		}
		// 		h = image_map_background.GetHandle();
		// 画像ハンドル
		int z = GlobalStaticVariable::GetModeTrial() == FALSE ? ui_map_month[game_week_number - 12].GetHandle() : bgimage_non_month.GetHandle();	

		GraphBlend(h, g_imghandles.ui_tips, 255, DX_GRAPH_BLEND_NORMAL);	// tipsＵＩをブレンド
		#pragma region ver0.021制作時コメント化コード
		//GraphBlend(h, ui_map_month[game_week_number - 12].GetHandle(), 255, DX_GRAPH_BLEND_NORMAL);	// フレームをブレンド
#pragma endregion
		GraphBlend(h, z, 255, DX_GRAPH_BLEND_NORMAL);	// フレームをブレンド
		// ここを後でなおす（選択しているマップに応じて描画）
		GraphBlend(h, g_imghandles.ui_map[0], 255, DX_GRAPH_BLEND_NORMAL);	// マップをブレンド
	}
	handle = h;
	char path[256];
	sprintf_s(path, 256, "savedata\\test_image%02d.bmp", x);
	SaveDrawValidGraphToBMP(h, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, path);
}
// フォルダ内にあるサムネ画像を読み込む
void SaveDataImage::LoadHandel(int x)
{
	namespace fs = std::filesystem;			// 『fs』という単語に『std::filesystem』という意味を持たせている？
	char path[256];
	sprintf_s(path, 256, "savedata\\test_image%02d.bmp", x);
	std::string file_path = path;	// 確認するファイルのパス
	if (fs::exists(file_path)){handle = LoadGraph(path);}
}
/*------------------------------*/
char StringBufAltenative[ALTENATIVE_MAX_NUMBER][STRBUF_ALTENATIVE_HEIGHT][STRBUF_ALTENATIVE_WIDTH + 2];	// 選択肢用仮想テキストバッファ（横サイズ（３番目）の数字は適当）

int ClickX, ClickY, Button, LogType;	//	クリック処理に必要な変数

// クリックされたタイミングや状況に応じたフラグを返す（範囲座標がfloat）
BOOL ClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a)	// クリックx座標,クリックy座標,判定左端x座標,判定上端y座標,座標横幅,座標縦幅,左ボタンが押されたか離されたか判別するフラグ,条件として使用する変数（zがTRUEなら『FALSE』でいい）
{
	if (z == TRUE)
	{
		// クリックの座標が判定の範囲内ならTRUEを返す
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1) { return TRUE; }
	}
	else
	{
		// クリックの座標が判定の範囲内であり、押した時のフラグも立っているならTRUEを返す
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1 && a == TRUE) { return TRUE; }
	}
	return FALSE;
}

#include "globaldefinition.h"

BackgroundChangeType g_backgroundchange;	// �w�i�ύX���@�̎��
/* state�N���X ---------*/
int state::alternative_move_number[COMMU_LINE_MAX] = {};
state HM[512][COMMU_LINE_MAX], commu_state_edit[COMMU_LINE_MAX + 1];
/*----------------------*/
//							�I�v�V�����ŃA�C�R���ł��Ȃ��ϓ����Ȃ����́i���A���A�����A�^�C�g���A�𑜓x�~�Q�j�A	�I�v�V�����I�����p���A	���b�Z�[�W���x�A				��ʃ��[�h�̎��
ImgData image_dialog[2],	image_option[6],																	image_option_arrow[2],		image_option_message_speed[3],	image_option_window_type[2],
//													���ӕ�												�}�b�v�I�����w�i
		image_text_window[2][4], image_icon_option,	image_cautionary_message, image_icon_commu_edit,	image_map_background;
//			�^�C�g����ʗp�A�}�b�v��ʗp�A									�I����
ImgDataHJ	hjimage_title,	hjimage_map[HIT_JUDGEMENT_IMAGE_NUMBER_MAP],	hjimage_alternative[ALTENATIVE_MAX_NUMBER];
/* ImgDataBG�N���X ---------*/
#pragma region ver0.00704���쎞�R�����g���R�[�h
//ImgDataBG bgimage[BACKGROUND_NUMBER] = {
#pragma endregion
ImgDataBG bgimage[] = {
	{(char*)"�߂���̕���"},				{(char*)"�ƒ�Ȏ�"},					{(char*)"�͐�~"},						{(char*)"�ʊw�H"},						{(char*)"�J�t�F�e���X"},
	{(char*)"1F�����L��"},					{(char*)"�f���O"},					{(char*)"���̑O�C�Z"} ,				{(char*)"����"} ,						{(char*)"�E����"} ,
	{(char*)"�o�X�P�X�g���[�g�R�[�g"},		{ (char*)"�哙������" },				{(char*)"�󂫋���"},					{ (char*)"2F�����L��" },				{ (char*)"1F�����L��" },
	{ (char*)"2F�����L��" } ,				{(char*)"�w�Z�K�i"},					{ (char*)"���Z�ɘL��" },				{ (char*)"�H��" },						{ (char*)"�H���E�[" },
	{ (char*)"�H���E��" } ,					{(char*)"�Z����"},						{ (char*)"�}����" },					{ (char*)"���y��" },					{ (char*)"������" },
	{ (char*)"�V��������" } ,				{ (char*)"�Z�ɗ��A�Z���x���`" },		{ (char*)"�Z�ɗ��A�Z���x���`�E�[" },	{ (char*)"����" },						{ (char*)"����E�[" } ,
	{(char*)"����E��"},					{ (char*)"�����L��" },					{ (char*)"�O���E���h" },				{ (char*)"�u��" },						{ (char*)"�u���E��" } ,
	{ (char*)"�u���E�d��" } ,				{ (char*)"�V�Ă̏�" } ,					{(char*)"�Z�ɂ�������Z�ɗ�"},			{ (char*)"�V���b�s���O���[��" },		{ (char*)"�X��" },
	{ (char*)"����" },						{ (char*)"�߂���󂫋���" },			{(char*)"���w�i"},						{(char*)"�����R�~���p������"},			{(char*)"�����R�~���p�������E�d�COFF"}, 
	{ (char*)"�߂���e�X�`��" },			{ (char*)"�����E�Z�s�A" },				{ (char*)"�󂫋����E�Z�s�A" },			{ (char*)"2F�����L���E�Z�s�A" },		{ (char*)"�w�Z�K�i�E�Z�s�A" },
	{ (char*)"�i���j���k�" },			{ (char*)"�i���j���k��E�[" },		{ (char*)"�i���j���k��E�_��" },		{ (char*)"�i���j���k��E����" },		{ (char*)"�Z�ɗ��A�Z���x���`�E��" }, 
	{(char*)"�i���j���X�X" },				{ (char*)"�i���j���X�X�E�[" },			{ (char*)"�i���j���X�X�E��" },			{ (char*)"�i���j�������E�P" },			{ (char*)"�i���j�������E�Q" },
	{ (char*)"�i���j�������E�R" },			{ (char*)"�i���j�������E�S" },			{ (char*)"�i���j�������E�T" },			{ (char*)"�i���j�������E�U" },			{ (char*)"�i���j�e�X�`���E�g�t" }, 
	{ (char*)"�i���j�߂���X�`���E�P" },	{ (char*)"�i���j�߂���X�`���E�Q" },	{ (char*)"�i���j�߂���X�`���E�S" },	{ (char*)"�i���j�����X�`���E�P" },		{ (char*)"�i���j�����X�`���E�P" },
	{ (char*)"�i���j�����X�`���E�Q" },		{ (char*)"�i���j�����X�`���E�R" },		{ (char*)"�i���j�����X�`���E�S" },		{ (char*)"�i���j�z���X�`���E�P" },		{ (char*)"�i���j�z���X�`���E�Q" },
	{ (char*)"�i���j���X�`���E�P" },		{ (char*)"�i���j���X�`���E�R" },		{ (char*)"�����L��E��" },				{ (char*)"�����L��E��d" },			{ (char*)"2F�����L���E�[" },
	{ (char*)"�Z��O�E�[" },				{ (char*)"�����E�[" },					{ (char*)"�����E��" },					{ (char*)"�����E��d" },				{ (char*)"1F�����L���E�[" },
	{ (char*)"1F�����L���E��" },			{ (char*)"1F�����L���E��d" },			{ (char*)"2F�����L���E�[" },			{ (char*)"2F�����L���E��" },			{ (char*)"2F�����L���E�[" },
	{ (char*)"2F�����L���E��" },			{ (char*)"�w�Z�K�i�E�[" },				{ (char*)"�w�Z�K�i�E��d" },			{ (char*)"�u�e�B�b�N" },				{ (char*)"���̈�ُo������" } ,
	{ (char*)"���̈�ُo�������E�J" } ,	{ (char*)"���̈�ُo�������E�[" } ,	{ (char*)"���̈�ُo�������E��" } ,	{ (char*)"���̈�ُo�������E��d" } ,	{ (char*)"���̈�ُo�������E�䂪��" },
	{ (char*)"�ƒ�Ȏ��E�Z�s�A" } };
int ImgDataBG::number = 0;
ImgDataBG::ImgDataBG(char* c)
{
	sprintf_s(name, 256, c);
	number++;
	// �G�f�B�b�g���[�h�Ŏg����w�i�I�����̍ő�s����ύX����
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
// �X�N���[���̂x���W�����炷
void ImgDataBGTutorial::ScreenYMove()
{
	float y = SCREEN_Y_INITIAL * magnification;
	float x = y / -138;	// �P�t���[���Ɉړ�����l
	if(cell_number + 2 >= 27 && cell_number + 2 <= 122)
	{ 
		if ((screen_y += x) > 0) { screen_y = 0; }
	}
	else
	{
		if ((screen_y -= x) <= y) { screen_y = y; }
	}
}
// �v�f�����Z�b�g����
void ImgDataBGTutorial::Reset()
{
	draw_image_number = 0;
	screen_y = SCREEN_Y_INITIAL;
}
/* ImaDataName�N���X ---------*/
ImaDataName image_title_border[ImaDataName::TITLE_BORDER_NUMBER];
// �{���������񂾏�ō��W�l���`����
void ImaDataName::CoordinateSettingName(float x, float y)
{
	coordinate_x = x * magnification;
	coordinate_y = y * magnification;
}
/*----------------------------*/
/* ImgData2�N���X ---------*/
int ImgData2::notice_count = 0;							// �x�����w�i�̓����x�����p���l
const int ImgData2::NOTICE_COUNT_MILLI_SECOND = 1000;	// �x�����w�i�̓����x�����ɕK�v�ȃ~���b
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
// �{���������񂾏�ō��W�l���`����
void ImgData2::CoordinateSetting2(float x, float y)
{
	coordinate_x = x * magnification;
	coordinate_y = y * magnification;
}
void ImgData2::DrawImageNotice()
{
	// 1000�~���b�����ĕ`�悳����
	if (notice_count == 0) { notice_count = GetNowCount(); }
	int x = (GetNowCount() - notice_count > NOTICE_COUNT_MILLI_SECOND) ? NOTICE_COUNT_MILLI_SECOND : GetNowCount() - notice_count;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, x * 255 / NOTICE_COUNT_MILLI_SECOND);
	DrawExtendGraphF(coordinate_x, coordinate_y, (float)screen_size_x, (float)screen_size_y, Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
/*-------------------------*/
/* ImgDataHJ2�N���X ---------*/
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
// �����t���N���b�N���菈�����s��
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
/* ImgDataTutorialEnd�N���X ---------*/
BOOL ImgDataTutorialEnd::white_out = FALSE;
int ImgDataTutorialEnd::count = 0;					// �̌��ŃA���P�[�g�w�i�̓����x�����p���l 
int ImgDataTutorialEnd::count_wait = 0;				// �̌��ŏI�����[�h�ő���\�ɂȂ�̂ɕK�v�ȃJ�E���g���l
const int ImgDataTutorialEnd::COUNT_LIMIT = 180;	// �̌��ŃA���P�[�g�w�i�̓����x�����p�̌��E���l
ImgDataTutorialEnd bgimage_tutorial_end = { (char*)"media\\background\\questionnaire_haduki.png" };
// �̌��ŏI���w�i��p�̕`�揈��
void ImgDataTutorialEnd::DrawImageTutorialEnd()
{
	// �J�E���g����
	if (white_out == FALSE && count < COUNT_LIMIT) { count++; }
	else if (white_out == TRUE && count > 0) { count--; }
	if (count >= COUNT_LIMIT) { count_wait++; }
	else if (white_out == TRUE && count <= 0)
	{ 
		count_wait++;
		// �Ƃ肠�����R�b
		if (count_wait >= COUNT_LIMIT) 
		{ 
			ImgDataHJTitle::SetCountFrame(0);
			GameTitleNext();
			SEPlay(static_cast<int>(SEData::IDName::START_EFFECT));	// ��p�̂r�d���Đ�
		}	
	}
	// �`��
	DrawExtendGraphF(coordinate_x, coordinate_y, (float)screen_size_x, (float)screen_size_y, Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COUNT_LIMIT - count) * 255 / COUNT_LIMIT);
	DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
// �̌��ŏI���ɕK�v�ȗv�f�����Z�b�g����
void ImgDataTutorialEnd::CountReset()
{
	white_out = FALSE;
	count = 0;	// �O�̂���
	count_wait = 0;
}
/*-----------------------------------*/
/* ImgDataMapFrame�N���X ---------*/
ImgDataMapFrame ui_map_month[] = {
	{(char*)"media\\UI\\map_frame\\frame_April_1.png"},
	{(char*)"media\\UI\\map_frame\\frame_April_2.png"},
	{(char*)"media\\UI\\map_frame\\frame_April_3.png"},
	{(char*)"media\\UI\\map_frame\\frame_April_4.png"},
	{(char*)"media\\UI\\map_frame\\frame_May_1.png"},
	{(char*)"media\\UI\\map_frame\\frame_May_2.png"} };
int ImgDataMapFrame::frame_number = 0;
/*--------------------------------*/
/* ImgDataMapQuestion�N���X ---------*/
ImgDataMapQuestion image_map_question[] = {
	{(char*)"media\\UI\\map_question\\meguru_heroine.png"},
	{(char*)"media\\UI\\map_question\\kogane_heroine.png"},
	{(char*)"media\\UI\\map_question\\juri_heroine.png"},
	{(char*)"media\\UI\\map_question\\rinze_heroine.png"},
	{(char*)"media\\UI\\map_question\\chiyuki_heroine.png"},
	{(char*)"media\\UI\\map_question\\all_friend.png"} };
int ImgDataMapQuestion::number = 0;
/*-----------------------------------*/
/* ImgDataTitleCharacter�N���X ---------*/
ImgDataTitleCharacter image_title_character[] = {
	{(char*)"media\\character\\title\\title_kogane.png"},
	{(char*)"media\\character\\title\\title_chiyuki.png"},
	{(char*)"media\\character\\title\\title_rinze.png"},
	{(char*)"media\\character\\title\\title_juri.png"},
	{(char*)"media\\character\\title\\title_meguru.png"},
};
int ImgDataTitleCharacter::character_number = 0;
/*--------------------------------------*/
/* ImgDataSLCheck�N���X ---------*/
ImgDataSLCheck image_sl_check_message[] = {
	{(char*)"media\\UI\\save_load\\save_ok.png"},
	{(char*)"media\\UI\\save_load\\load_ok.png"}};
int ImgDataSLCheck::image_number = 0;
/*-------------------------------*/
/* ImgDataHJTitle�N���X ---------*/
BOOL ImgDataHJTitle::flag_count = FALSE;
int ImgDataHJTitle::menu_number = 0;
int ImgDataHJTitle::count_frame = 0;				// �^�C�g����ʂł̌o�߃t���[����
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
	// �x�[�X�w�i
	//if(mode_debug == FALSE){ image_title_border[0].DrawImage(); }
	//else {image_title_border[count_frame % ImaDataName::GetTitleBorderNumber()].DrawImage();}
	image_title_border[count_frame % ImaDataName::GetTitleBorderNumber()].DrawImage();
	//image_title_border[count_frame / 9 % ImaDataName::GetTitleBorderNumber()].DrawImage();
	DrawExtendGraphF(bgimage_title.GetCoordinateX(), bgimage_title.GetCoordinateY(), (float)screen_size_x, (float)screen_size_y, bgimage_title.GetHandle(), TRUE);
	// �L�����摜
	const int X = 60;			// �P�l�̃L�������o����������̂ɕK�v�ȃt���[����
	const int X_DISTANCE = 36;	// ���̃L�������o��܂ł̊Ԋu
	for(int i = 0; i < ImgDataTitleCharacter::GetTitleCharacterNumber(); i++)
	{ 
		// �K��o�߃t���[�����𖞂����Ă��Ȃ���΂��������`�悳��Ȃ�
		if (count_frame > i * X_DISTANCE)
		{
			int y = (count_frame < i * X_DISTANCE + X) ? count_frame - i * X_DISTANCE : X;	// ���ߓx�p�J�E���g
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, y * 255 / X);
			DrawExtendGraphF(image_title_character[i].GetCoordinateX(), image_title_character[i].GetCoordinateY(), (float)screen_size_x, (float)screen_size_y, image_title_character[i].GetHandle(), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	// �^�C�g�����S
	int x = (ImgDataTitleCharacter::GetTitleCharacterNumber() - 1) * X_DISTANCE + X;
	const int Y = 60;	// �^�C�g�����S���o����������̂ɕK�v�ȃt���[����
	if(count_frame > x)
	{
		int y = (count_frame < x + Y ? count_frame - x : Y);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, y * 255 / Y);
		image_title_logo.DrawImage();
		image_title_logo_stilltrial.DrawImage();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// ���j���[�A�C�R��
	int f = x + Y;
	const int Z = 20;	// �P�̃A�C�R�����o����������̂ɕK�v�ȃt���[����
	for(int i = 0; i < ImgDataHJTitle::GetMenuNumber(); i++)
	{
		if (count_frame > f + i * (Z / 2))
		{
			int y = (count_frame < f + Z + i * (Z / 2)) ? count_frame - (f + i * (Z / 2)): Z;
			// �\��������ۂɔ����ĂQ��ލ��W���`���Ă���
			for (int j = 0; j < 2; j++){image_title_menu[i][j].CoordinateSetting(screen_size_x - y * image_title_menu[i][j].GetSizeX() / Z, screen_size_y - (ImgDataHJTitle::GetMenuNumber() - i - 1) * image_title_menu[0][0].GetSizeY() * 1.25f - image_title_menu[0][0].GetSizeY() * 2);}
			// �}�E�X�J�[�\�����A�C�R���͈͓̔����������p�̉摜��`�悷��悤�ɂ���ϐ�
			BOOL b = (MouseX >= image_title_menu[i][0].GetCoordinateX() && MouseX < screen_size_x && MouseY >= image_title_menu[i][0].GetCoordinateY() && MouseY < image_title_menu[i][0].GetCoordinateY() + image_title_menu[i][0].GetSizeY()) ? TRUE : FALSE;
			// �wEXTRA�x��������
			image_title_menu[i][b].DrawImage();
		}
		// ����or�����Ȃ����ǖ{���A�C�R�����u�����ꏊ���N���b�N����Ƃ܂������Ă��Ȃ��Ă����肪�s����s��̗\�h����
		else 
		{
			for (int j = 0; j < 2; j++) { image_title_menu[i][j].CoordinateSetting((float)screen_size_x, 0); }
		}
	}
	// �S�Ă̗v�f���\�����ꂫ���Ă��āA���X�^�[�g�������ĂȂ����BGM�𗬂�
	#pragma region ver0.017���쎞�R�����g���R�[�h
	//if (count_frame >= f + Z + Z / 2 * ImgDataHJTitle::GetMenuNumber() - 1 && CheckSoundMem(g_sndhandles.BGM[BN_TITLE]) == 0 && flag_next_start == FALSE) { MusicPlay(BN_TITLE); }
#pragma endregion
	if (count_frame >= f + Z + Z / 2 * ImgDataHJTitle::GetMenuNumber() - 1 && CheckSoundMem(bgm[BN_TITLE].GetHandle()) == 0 && flag_next_start == FALSE) { MusicPlay(BN_TITLE); }
	count_frame++;	// �o�߃t���[���J�E���g	
}
/*-------------------------------*/
/* ImgDataIconCheck�N���X ---------*/
ImgDataIconCheck image_icon_check[2] = {
	{(char*)"media\\UI\\move_comu_check_ok.png"},
	{(char*)"media\\UI\\move_comu_check_no.png"} };
const int ImgDataIconCheck::IMAGE_NUMBER = 2;
/*---------------------------------*/
/* ImgDataIconMapCharacter�N���X ---------*/
ImgDataIconMapCharacter image_icon_map_character[] = {
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_mg.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_kg.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_jr.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_rn.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_one_cy.png"},
	{(char*)"media\\UI\\icon\\map\\map_hukidasi_all.png"} };
#pragma region ver0.00904���쎞�R�����g���R�[�h
//const int ImgDataIconMapCharacter::NUMBER = 5;
#pragma endregion
int ImgDataIconMapCharacter::number = 0;
/*----------------------------------------*/
/* FontData�N���X ---------*/
int FontData::font_number = 0;
// �l�r�n�t�H���g�A���C���I�ȊO��Windows���ڃt�H���g�̓��C�Z���X�����̕K�v������
FontData font[] = {
	{(char*)"���C���I",	27},
	{(char*)"���C���I", 48},
	{(char*)"���C���I", 40},
	{(char*)"���C���I", 36},
	{(char*)"�l�r �S�V�b�N", 45},
	{(char*)"���C���I", 24} ,
	{(char*)"���C���I", 33} };
void FontData::Create()
{
	handle = CreateFontToHandle(name, (int)(size * magnification), -1, DX_FONTTYPE_ANTIALIASING);
	// ��`�t�H���g�Ɂw���x���Ȃ��ꍇ�A�t�H���g�����C���I�ɂ���
	if (GetFontCharInfo(handle, "��", NULL, NULL, NULL, NULL, NULL) < 0)
	{
		// �������Ȃ�
		handle = CreateFontToHandle("���C���I", (int)(size * magnification), -1, DX_FONTTYPE_ANTIALIASING);
		quit_game = TRUE;	// �t�H���g��������ƒǉ����ꂽ���m�F����R�[�h
	}
	else
	{
		// ����������
	}
}
/*-------------------------*/

StringData line_character = { GetColor(20, 20, 20), 1};
/* SaveDataImage�N���X ---------*/
SaveDataImage save_data_image[SaveDataImage::LIMIT_NUMBER];
void SaveDataImage::SetCoordinate(float x, float y)
{
	coordinate_x = x * magnification;
	coordinate_y = y * magnification;
}
// �摜����������
void SaveDataImage::Blend(int x, BOOL y)	// �R�~���w�i�łȂ��S�̃}�b�v��`�悷�邩
{
	namespace fs = std::filesystem;			// �wfs�x�Ƃ����P��Ɂwstd::filesystem�x�Ƃ����Ӗ����������Ă���H
	std::string folder_path = "savedata";	// �m�F����t�H���_�̃p�X
	// �t�H���_�����݂��Ȃ����
	if (!fs::exists(folder_path))
	{
		// ��O����try���J�n���A��O�����������caych���̏��������s����
		try{fs::create_directories(folder_path);}
		catch(const std::exception& ex)
		{
			std::cerr << ex.what() << '\n';	// �G���[���b�Z�[�W��\������
			quit_game = TRUE;
		}
	}
	else{}

	// �R�~���w�i�i������ς���΃R�~�����̃T���l�o�O���C���ł���Ǝv�����w�i�p
	// �̂h�c�͌�X�z��萔�ɕς���\��Ȃ̂ł܂��C�����Ȃ��j
	int h;
	if (y == FALSE)
	#pragma region ver0.016���쎞�R�����g���R�[�h
		//{h = commu_background;}
#pragma endregion
	{
		if (GlobalStaticSaveLoad::GetSamuneBackgroundID() > 0)
		{
			char c[256];
			sprintf_s(c, 256, "media\\background\\board_%03d.png", GlobalStaticSaveLoad::GetSamuneBackgroundID());	// 100�����ł��K���R���ɂ���
			h = LoadGraph(c);
			if (h == -1)
			{
				quit_game = TRUE;
				return;
			}
		}
	}
	// �}�b�v�w�i
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
		// �摜�n���h��
		int z = GlobalStaticVariable::GetModeTrial() == FALSE ? ui_map_month[game_week_number - 12].GetHandle() : bgimage_non_month.GetHandle();	

		GraphBlend(h, g_imghandles.ui_tips, 255, DX_GRAPH_BLEND_NORMAL);	// tips�t�h���u�����h
		#pragma region ver0.021���쎞�R�����g���R�[�h
		//GraphBlend(h, ui_map_month[game_week_number - 12].GetHandle(), 255, DX_GRAPH_BLEND_NORMAL);	// �t���[�����u�����h
#pragma endregion
		GraphBlend(h, z, 255, DX_GRAPH_BLEND_NORMAL);	// �t���[�����u�����h
		// ��������łȂ����i�I�����Ă���}�b�v�ɉ����ĕ`��j
		GraphBlend(h, g_imghandles.ui_map[0], 255, DX_GRAPH_BLEND_NORMAL);	// �}�b�v���u�����h
	}
	handle = h;
	char path[256];
	sprintf_s(path, 256, "savedata\\test_image%02d.bmp", x);
	SaveDrawValidGraphToBMP(h, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, path);
}
// �t�H���_���ɂ���T���l�摜��ǂݍ���
void SaveDataImage::LoadHandel(int x)
{
	namespace fs = std::filesystem;			// �wfs�x�Ƃ����P��Ɂwstd::filesystem�x�Ƃ����Ӗ����������Ă���H
	char path[256];
	sprintf_s(path, 256, "savedata\\test_image%02d.bmp", x);
	std::string file_path = path;	// �m�F����t�@�C���̃p�X
	if (fs::exists(file_path)){handle = LoadGraph(path);}
}
/*------------------------------*/
char StringBufAltenative[ALTENATIVE_MAX_NUMBER][STRBUF_ALTENATIVE_HEIGHT][STRBUF_ALTENATIVE_WIDTH + 2];	// �I�����p���z�e�L�X�g�o�b�t�@�i���T�C�Y�i�R�Ԗځj�̐����͓K���j

int ClickX, ClickY, Button, LogType;	//	�N���b�N�����ɕK�v�ȕϐ�

// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ��i�͈͍��W��float�j
BOOL ClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a)	// �N���b�Nx���W,�N���b�Ny���W,���荶�[x���W,�����[y���W,���W����,���W�c��,���{�^���������ꂽ�������ꂽ�����ʂ���t���O,�����Ƃ��Ďg�p����ϐ��iz��TRUE�Ȃ�wFALSE�x�ł����j
{
	if (z == TRUE)
	{
		// �N���b�N�̍��W������͈͓̔��Ȃ�TRUE��Ԃ�
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1) { return TRUE; }
	}
	else
	{
		// �N���b�N�̍��W������͈͓̔��ł���A���������̃t���O�������Ă���Ȃ�TRUE��Ԃ�
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1 && a == TRUE) { return TRUE; }
	}
	return FALSE;
}

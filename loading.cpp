#include "loading.h"

const char* load_name[CHARACTER_GRAPH_NUMBER] = { "meguru", "kogane", "juri", "rinze", "chiyuki", "hazuki", "tsutomu" };	// �L�����N�^�[�����G�ǂݍ��݂̍ۂɎg���閼�O���

ImageHandles g_imghandles;
/* CharacterImage�N���X ---------*/
const char* CharacterImage::LOAD_NAME[CharacterImage::CHARACTER_NUMBER] = { "meguru", "kogane", "juri", "rinze", "chiyuki", "hazuki", "tsutomu" };	// �ǂݍ��݂̍ۂɎg���閼�O���
// �G�f�B�b�g���[�h�ł̌ʓǂݍ��݃t���O
BOOL CharacterImage::load_edit[CharacterImage::CHARACTER_NUMBER] = {FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE};

//const int CharacterImage::CHARACTER_NUMBER = 7;	// �l��
//const int CharacterImage::PAUSE_NUMBER = 10;	// �|�[�Y�ő吔
//const int CharacterImage::CLOTHES_NUMBER = 6;	// �ߑ��ő吔
CharacterImage image_character[CharacterImage::CHARACTER_NUMBER][CharacterImage::PAUSE_NUMBER][CharacterImage::CLOTHES_NUMBER];
void CharacterImage::SetFlagAll(BOOL b)
{
	for (int i = 0; i < CHARACTER_NUMBER; i++)
	{
		// �G�f�B�b�g���[�h�ڍs���Ƀt���O���I�t�ɂȂ��Ă���L�����͓ǂݍ��݂��X�L�b�v������悤�ɂ���
		if (g_gamestate != GAME_COMMU_EDIT || load_edit[i] != FALSE)
		{
			for (int j = 0; j < PAUSE_NUMBER; j++)
			{
				for (int k = 0; k < CLOTHES_NUMBER; k++)
				{
					for (int l = 0; l < FACE_NUMBER; l++) { image_character[i][j][k].load_flag[l] = b; }
				}
			}
		}
	}
}
// �ǂݍ��މ摜�̎�ނ��`�F�b�N����
void CharacterImage::LoadFlagCheck()
{
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		for(int j = 0; j < COMMU_LINE_MAX; j++)
		{
			int x = HM[commu_number][j].character[i];
			//�o�b�t�@�I�[�o�[���������p�ϐ��H
			int y = x / 1000 - 1;
			int z = x / 100 % 10;
			int a = x / 10 % 10;
			int b = x % 10;
			
			if (x > 0) 
			{ 
				// �o�b�t�@�[�I�[�o�[�������������邽�߂ɕK�v��if��
				if (y >= 0 && y < CharacterImage::CHARACTER_NUMBER &&z >= 0 && z < CharacterImage::PAUSE_NUMBER &&a >= 0 && a < CharacterImage::CLOTHES_NUMBER &&b >= 0 && b < CharacterImage::FACE_NUMBER)
				{
					image_character[y][z][a].SetLoadFlag(b);
				}
			}
		}
	}
}
// �S�Ă̗����G������������폜����
void CharacterImage::DeleteAll()
{
	for (int i = 0; i < CHARACTER_NUMBER; i++)
	{
		for (int j = 0; j < PAUSE_NUMBER; j++)
		{
			for (int k = 0; k < CLOTHES_NUMBER; k++)
			{
				DeleteGraph(g_imghandles.character_body[i][j][k]);
				for (int l = 0; l < FACE_NUMBER; l++) 
				{ 
					// �t���O���������܂܂Ȃ�摜�������Ȃ�
					if (image_character[i][j][k].load_flag[l] == FALSE)
					{
						for (int m = 0; m < EYE_NUMBER + MOUSE_NUMBER; m++) { DeleteGraph(g_imghandles.character_face[i][j][k][l][m]); }
						for (int m = 0; m < EYE_BLOW_NUMBER; m++) { DeleteGraph(g_imghandles.character_eyebrow[i][j][k][l][m]); }
						image_character[i][j][k].load_flag_finished[l] = FALSE;	// �ǂݍ��݊����t���O�����Z�b�g
					}
				}
			}
		}
	}
}
// �ǂݍ��ݏ���
BOOL CharacterImage::Load()
{
	if (DebugLoadCheckCharacter() == FALSE || mode_debug == FALSE)
	{
		// �G�f�B�b�g���̃L�����I���Ɋւ���ϐ�
		int edit_c_x = 0;
		int edit_c_y = 0;

		for (int j = 0; j < CHARACTER_NUMBER; j++)
		{
			for (int i = 0; i < PAUSE_NUMBER; i++)
			{
				for (int l = 0; l < CLOTHES_NUMBER; l++)
				{
					char c[256];
					sprintf_s(c, 256, "%s_pause%d%d\\%s_pause%d%d.png", load_name[j], i, l, load_name[j], i, l);
					char d[256];	// �R�~���e�X�g�v���C���[�h���̃p�X
					sprintf_s(d, 256, "media\\%s_pause%d%d\\%s_pause%d%d.png", load_name[j], i, l, load_name[j], i, l);
					//sprintf_s(c, 256, "media.dat\\%s_pause%d%d\\%s_pause%d%d.png", load_name[j], i, l, load_name[j], i, l);
					struct stat st;
					if (DXArchiveCheckFile("media.dat", c) == 1 || stat(d, &st) == 0)	// stat�֐���c++�̃v���O�����Ȃ̂�DX�A�[�J�C�u�̂��Ƃ��l���ł��Ȃ�
					{
						// ���O
						//DebugLog(LogOutputType::LOAD_CHECK);
						if (GlobalStaticDebug::GetLog() == TRUE)
						{
							char c[256];
							sprintf_s(c, 256, "�L�����F%d�A�|�[�Y�F%d�A�ߑ��F%d\n", j, i, l);
							LogFileAdd(c);
						}
						LoadGameImageCharacterBody(i, &g_imghandles.character_body[j][i][l], load_name[j], l);
						if (g_imghandles.character_body[j][i][l] == -1) { return FALSE; }

						for (int m = 0; m < CHARACTER_GRAPH_FACE_NUMBER; m++)
						{
							char c3[256];	// �\��ǂݍ��ݏ����m�F�p������
							sprintf_s(c3, 256, "%s_pause%d%d\\%s_pause%d%d_eye%d0.png", load_name[j], i, l, load_name[j], i, l, m);
							char d3[256];
							sprintf_s(d3, 256, "media\\%s_pause%d%d\\%s_pause%d%d_eye%d0.png", load_name[j], i, l, load_name[j], i, l, m);
							// stat�֐���c++�̃v���O�����Ȃ̂�DX�A�[�J�C�u�̂��Ƃ��l���ł��Ȃ�
							if ((DXArchiveCheckFile("media.dat", c3) == 1 || stat(d3, &st) == 0) && image_character[j][i][l].load_flag[m] == TRUE && image_character[j][i][l].load_flag_finished[m] == FALSE)
							{

								for (int k = 0; k < CHARACTER_GRAPH_EYE_NUMBER + CHARACTER_GRAPH_MOUSE_NUMBER; k++)
								{
									char c2[256];
									char* face_parts = k < CHARACTER_GRAPH_EYE_NUMBER ? (char*)"eye" : (char*)"mouth";
									sprintf_s(c2, 256, "%s_pause%d%d\\%s_pause%d%d_%s%d%d.png", load_name[j], i, l, load_name[j], i, l, face_parts, m, k < CHARACTER_GRAPH_EYE_NUMBER ? k : k - CHARACTER_GRAPH_EYE_NUMBER);
									char d2[256];
									sprintf_s(d2, 256, "media\\%s_pause%d%d\\%s_pause%d%d_%s%d%d.png", load_name[j], i, l, load_name[j], i, l, face_parts, m, k < CHARACTER_GRAPH_EYE_NUMBER ? k : k - CHARACTER_GRAPH_EYE_NUMBER);
									// ����Ȗڃp�[�c�͂��̃^�C�~���O�Ńt�@�C�������݂��邩�ǂ����m�F���A���݂��ĂȂ���Γǂݍ��ݏ������X�L�b�v����
									//struct stat st;
									if (k <= 2 || k >= CHARACTER_GRAPH_EYE_NUMBER || DXArchiveCheckFile("media.dat", c2) == 1 || stat(d2, &st) == 0)	// ���݂��Ă����0��Ԃ�
									{
										char c4[256] = "";
										sprintf_s(c4, 256, "media\\%s", c2);
										g_imghandles.character_face[j][i][l][m][k] = LoadGraph(c4);
										if (g_imghandles.character_face[j][i][l][m][k] == -1) { return FALSE; }
									}
								}
								for (int k = 0; k < CHARACTER_GRAPH_EYE_BLOW_NUMBER; k++)
								{
									char c2[256];
									sprintf_s(c2, 256, "media\\%s_pause%d%d\\%s_pause%d%d_eyebrow%d%d.png", load_name[j], i, l, load_name[j], i, l, m, k);
									g_imghandles.character_eyebrow[j][i][l][m][k] = LoadGraph(c2);
									if (g_imghandles.character_eyebrow[j][i][l][m][k] == -1) { return FALSE; }
								}
								// �L�����G�f�B�b�g�̗����G�I���ɕK�v�Ȑ��l��������
								edit_character_id[edit_c_y][edit_c_x] = (j + 1) * 1000 + i * 100 + l * 10 + m;
								// �I�����p���l�����Z���ĕK�v�Ȃ�J��グ��
								if (edit_c_x >= EDIT_CHARACTER_ALTERNATIVE_X_LIMIT - 1)
								{
									edit_c_x = 0;
									edit_c_y++;
								}
								else { edit_c_x++; }
								// �ǂݍ��݊����t���O�𗧂Ă�
								image_character[j][i][l].load_flag_finished[m] = TRUE;
							}
						}
					}
				}
				// �����ɉ��̈Ӗ����Ȃ��N���b�N����������
				if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
				{
					if ((Button & MOUSE_INPUT_LEFT) != 0)
					{
						if (LogType == MOUSE_INPUT_LOG_DOWN){}
						else if (LogType != MOUSE_INPUT_LOG_DOWN){}
					}
				}
			}
		}
		// �G�f�B�b�g���[�h�Ŏg�������G�I�����̍s���𑝉�������
		if(mode_debug == TRUE && edit_character_alternative_line_limit < edit_c_y + 1){edit_character_alternative_line_limit = edit_c_y + 1;}
		// �i���ꉽ�H�j
		//if (edit_c_x == 0) { edit_character_alternative_line_limit--; }
	}
	return TRUE;
}
/*-------------------------------*/
//SoundHandles g_sndhandles;
/* BGMData�N���X ---------*/
// �i�����̕����̓��͂��I����j
BGMData bgm[BGM_NUMBER] = {
	{ (char*)"001_Wind_Chime",			FALSE,	0,		0},
	{ (char*)"101_NJ01",				FALSE,	0,		0},
	{ (char*)"102_NJ02",				FALSE,	0,		0},
	{ (char*)"103_NJ03",				FALSE,	0,		0},
	{ (char*)"104_NJ104",				FALSE,	0,		0},
	{ (char*)"105_NJ105",				FALSE,	0,		0},
	{ (char*)"106_NJ106",				FALSE,	0,		0},
	{ (char*)"201_SC_Happening",		FALSE,	0,		0},
	{ (char*)"202_SC_ Disquiet",		FALSE,	0,		0},
	{ (char*)"203_SC_Sad",				FALSE,	0,		0},
	{ (char*)"204_SC_AfterSchool",		FALSE,	0,		0},
	{ (char*)"205_SC_Determination",	FALSE,	0,		0},
	{ (char*)"206_SC_Night",			FALSE,	0,		0},
	{ (char*)"207_SC_Music_Room",		FALSE,	0,		0},
	{ (char*)"208_SC_dotabata",			FALSE,	0,		0},
	{ (char*)"209_SC_Night_Sky",		FALSE,	0,		0},
	{ (char*)"210_SC_Confession",		FALSE,	0,		0},
	{ (char*)"211_SC_Kaidan",			FALSE,	0,		0},
	{ (char*)"212_SC_Mystery",			FALSE,	0,		0},
	{ (char*)"213_SC_Uneasiness",		FALSE,	0,		0},
	{ (char*)"214_SC_Recollection",		FALSE,	0,		0},
	{ (char*)"215_SC_Battle",			FALSE,	0,		0},
	{ (char*)"216_Will",				FALSE,	0,		0},
	{ (char*)"217_Chaser",				FALSE,	0,		0},
	{ (char*)"301_CH_Amai_01",			FALSE,	0,		0},
	{ (char*)"302_CH_Juri_01",			FALSE,	26727,	61636},
	{ (char*)"303_CH_Haduki_01",		FALSE,	0,		0},
	{ (char*)"304_CH_Meguru_01",		FALSE,	0,		0},
	{ (char*)"305_CH_Rinze_01",			FALSE,	0,		0},
	{ (char*)"306_CH_Chiyuki_01",		FALSE,	0,		0},
	{ (char*)"307_CH_Kogane_01",		FALSE,	0,		0},
	{ (char*)"401_Main Theme",			TRUE,	0,		0},
	{ (char*)"402_Map",					TRUE,	0,		0},
	{ (char*)"403_OP_MusicBoxVer",		TRUE,	0,		0},
	{ (char*)"404_Sentakushi",			TRUE,	0,		0}
};
// ���[�v�֌W�̈ʒu��ݒ肷��
void BGMData::SetLoop()
{
	if (LOOP_POS > 0) { SetLoopPosSoundMem(LOOP_POS, handle); }
	if (LOOP_START > 0) { SetLoopStartTimePosSoundMem(LOOP_START, handle); }
}
// �������������Ȃ���ނ̂a�f�l��ǂݍ���
void BGMData::LoadFirst()
{
	for (int i = 0; i < NUMBER; i++)
	{
		// �폜����Ȃ��a�f�l�Ȃ�ǂݍ���
		if (bgm[i].not_release == TRUE)
		{
			bgm[i].handle = LoadSoundMem(bgm[i].path);
			if (bgm[i].handle == -1)
			{
				quit_game = TRUE;
				return;
			}
			bgm[i].SetLoop();	// ���[�v�֌W�̈ʒu��ݒ肷��
			// �ǂݍ��݊����t���O�𗧂Ă�
			bgm[i].load_finished = TRUE;
		}
	}
	ChangeBGMVolume();	// �ǂݍ��܂ꂽ�΂���̂a�f�l�͉��ʂ�100���Ȃ̂ōĒ�������
}
// �S�Ă�load�ϐ���ύX����
void BGMData::SetLoadAll(BOOL x)
{
	for (int i = 0; i < NUMBER; i++) { bgm[i].load = x; }
}
// �ǂݍ��ނa�f�l���`�F�b�N����
void BGMData::LoadFlagCheck()
{
	for (int i = 0; i < COMMU_LINE_MAX; i++)
	{
		if (HM[commu_number][i].GetBGM() > 0)
		{
			bgm[HM[commu_number][i].GetBGM() - 1].SetLoad(TRUE);
			// �ǂ̋Ȃ��g���Ă��邩�`�F�b�N����
			//char c[256];
			//sprintf_s(c, 256, "%d�F%s\n", HM[commu_number][i].GetBGM(), music_string[HM[commu_number][i].GetBGM() - 1].GetName());
			//LogFileAdd(c);
		}
	}
}
// �S�Ă̂a�f�l������������폜����
void BGMData::DeleteAll()
{
	for (int i = 0; i < BGM_NUMBER; i++)
	{
		// �����a�f�l�ł͂Ȃ�and�ǂݍ��݃t���O���~��Ă���Ȃ�a�f�l������
		if (bgm[i].GetNotRelease() == FALSE && bgm[i].load == FALSE)
		{ 
			DeleteSoundMem(bgm[i].handle);
			bgm[i].load_finished = FALSE;	// �ǂݍ��݊����t���O�����Z�b�g
		}
	}
}
// ���[�h����
void BGMData::Load()
{
	for (int i = 0; i < BGM_NUMBER; i++)
	{
		// �t���O�������Ă��Ȃ�or���ɓǂݍ���ł���Ȃ�ǂݍ���Ńt���O�𗧂Ă�
		if (bgm[i].GetLoad() == TRUE && bgm[i].load_finished == FALSE)
		{
			bgm[i].handle = LoadSoundMem(bgm[i].path);
			if(bgm[i].handle == -1)
			{
				quit_game = TRUE;
				return;
			}
			bgm[i].SetLoop();	// ���[�v�֌W�̈ʒu��ݒ肷��
			// �ǂݍ��݊����t���O�𗧂Ă�
			bgm[i].load_finished = TRUE;
		}
	}
	ChangeBGMVolume();	// �ǂݍ��܂ꂽ�΂���̂a�f�l�͉��ʂ�100���Ȃ̂ōĒ�������
}
/*------------------------*/

int SEData::number = 0;				// ����
int SEData::commu_start_time = 0;	// �R�~���X�^�[�g�r�d�Đ����~���b
SEData se[] = {
	{ (char*)"001_Wind_Chime",			(char*)"�E�B���h�`���C��",		FALSE},
	{ (char*)"002_Clap_Single",			(char*)"����i��l�j",			FALSE},
	{ (char*)"003_Clap_Multi",			(char*)"����i�吨�j",			FALSE},
	{ (char*)"004_Chime",				(char*)"�`���C��",				FALSE},
	{ (char*)"005_BasketBall Dribble",	(char*)"�h���u��",				TRUE},
	{ (char*)"006_Foot_Step_01",		(char*)"����",					FALSE},
	{ (char*)"006-2_Foot_Step_01_LOOP",	(char*)"�����i���[�v�j",		TRUE},
	{ (char*)"007_Curtain rail",		(char*)"�J�[�e�����J���鉹",	FALSE},
	{ (char*)"008_Callan colon",		(char*)"�X�̃h�A���J���鉹",	FALSE},
	{ (char*)"009_Door_open",			(char*)"�����˂��J���鉹",		FALSE},

	{ (char*)"010_Door Knock",		(char*)"�m�b�N�̉�",						FALSE},
	{ (char*)"011_Bird_cry",		(char*)"���̂�������",						FALSE},
	{ (char*)"012_Wind note",		(char*)"���̉�",							FALSE},
	{ (char*)"013_Decision sound",	(char*)"�I���������肷��",					FALSE},
	{ (char*)"014_River",			(char*)"��̐��̗���̉�",					FALSE},
	{ (char*)"014-2_River_LOOP",	(char*)"��̐��̗���̉�(LOOP)",			TRUE},
	{ (char*)"015_Cloth rubbing",	(char*)"�z���C��鉹",						FALSE},
	{ (char*)"016_Basket Goal",		(char*)"�o�X�P�b�g�{�[�����S�[���ɓ��鉹",	FALSE},
	{ (char*)"017_Collosion",		(char*)"�Ԃ��鉹",						FALSE},
	{ (char*)"018_Cat",				(char*)"�L�̖���",						FALSE},

	{ (char*)"019_Paper_Map_Move", (char*)"�����߂��鉹",					FALSE},
	{ (char*)"020_Clap_1Tap", (char*)"�n�C�^�b�`",							FALSE},
	{ (char*)"020-2_Clap_2Tap_01", (char*)"���@����",						FALSE},
	{ (char*)"021_Crowed_Students", (char*)"�K��-1",						FALSE},
	{ (char*)"021-2_Crowed_Students_LOOP", (char*)"�K��-1(LOOP)",			TRUE},
	{ (char*)"022_Shoes", (char*)"�V���[�Y�̉�",							FALSE},
	{ (char*)"023_keybord_typing", (char*)"�L�[�{�[�h��@��",				FALSE},
	{ (char*)"023-2_keybord_typing(LOOP)", (char*)"�L�[�{�[�h��@��(LOOP)",	TRUE},
	{ (char*)"024_Paper_Flying", (char*)"�����U��΂鉹",					FALSE},
	{ (char*)"025_Phone_notice_note", (char*)"�g�с@�ʒm",					FALSE},

	{ (char*)"026_Tumble",			(char*)"�����[(�]��)",			FALSE},
	{ (char*)"027_Chair_standup",	(char*)"�֎q�𗧂�",			FALSE},
	{ (char*)"028_Gatagata",		(char*)"�K�^�K�^�Ƃ�������",	FALSE},
	{ (char*)"029_Phone_call",		(char*)"�g�с@���M��",			FALSE},
	{ (char*)"030_Icon_Tap",		(char*)"�A�C�R������������",	FALSE},
	{ (char*)"031_agemono",			(char*)"�g���������鉹",		FALSE},
	{ (char*)"032_Flash_Back",		(char*)"�t���b�V���o�b�N",		FALSE},
	{ (char*)"033_howanx4",			(char*)"�v���o����",			FALSE},
	{ (char*)"034_Door_Open_gatya",	(char*)"�J���˂̉�",			FALSE},
	{ (char*)"035_gasagasa_01",		(char*)"�K�T�K�T",				FALSE},

	{ (char*)"036_Dash_01",				(char*)"�삯�鑫��",		FALSE},
	{ (char*)"037_open_window",			(char*)"�����J���鉹",		FALSE},
	{ (char*)"038-1_pen_write",			(char*)"����������",		FALSE},
	{ (char*)"038-2_pen_write(LOOP)",	(char*)"����������(LOOP)",	TRUE},
	{ (char*)"039_Door_open_silent",	(char*)"�Â��Ɍ˂��J��",	FALSE},
	{ (char*)"040_Chair_sitdown",		(char*)"�֎q�ɍ���",		FALSE},
	{ (char*)"041-1_semi",				(char*)"�Z�~�̐�",			FALSE},
	{ (char*)"042_jaguti_open",			(char*)"�������J��",		FALSE},
	{ (char*)"043_jaguti_cloase",		(char*)"�������~�߂鉹",	FALSE},
	{ (char*)"044-1_Scean_change_IN",	(char*)"��ʓ]��IN",		FALSE},

	{ (char*)"044-2_Scean_change_OUT",	(char*)"��ʓ]��OUT",		FALSE},
	{ (char*)"045_StartScean_note",		(char*)"�X�^�[�g��ʑI��",	FALSE},
	{ (char*)"046_Start",				(char*)"Start",				FALSE},
	{ (char*)"047-1_Fluid_water",		(char*)"�����̉�",			FALSE},
	{ (char*)"047-2_Fluid_water(LOOP)", (char*)"�����̉�(LOOP)",	TRUE},
	{ (char*)"048_Gaan",				(char*)"���[��",			FALSE},
	{ (char*)"049_Hug",					(char*)"��������",		FALSE},
	{ (char*)"051_Ping_Pong",			(char*)"�s���|��",			FALSE},
	{ (char*)"052_Horror",				(char*)"�z���[",			FALSE},
	{ (char*)"053_Sentakushi",			(char*)"�R�~���I����",		FALSE},

	{ (char*)"054_START_EFFECT",		(char*)"�^�C�g�����",		FALSE},
	{ (char*)"036-2_Dash_Room",			(char*)"�삯�鑫��(����)",	FALSE},
	{ (char*)"055_Comu_Start",			(char*)"�R�~���X�^�[�g",	FALSE},
	{ (char*)"056_Dog",					(char*)"���̖���",		FALSE},
	{ (char*)"057_pin_pon_pan_pon",		(char*)"�s���|���p���|��",	FALSE},
	{ (char*)"058_Mic_Noise",			(char*)"�}�C�N�m�C�Y",		FALSE},
	{ (char*)"059-1_Thunder_S",			(char*)"����(��)",			FALSE},
	{ (char*)"059-2_Thunder_L",			(char*)"����(��)",			FALSE},
	{ (char*)"060_LittleCat",			(char*)"�q�L�̖���",		FALSE},
	{ (char*)"061-1_huni",				(char*)"�ӂ�",				FALSE},

	{ (char*)"061-2_hunix2",		(char*)"�ӂɂӂ�",				FALSE},
	{ (char*)"062_Gatagata_02",		(char*)"�K�^�K�^�Ƃ�������-2",	FALSE},
	{ (char*)"063_StandUp_Slow",	(char*)"������藧���オ��",	FALSE},
	{ (char*)"064_Switch",			(char*)"�X�C�b�`�����鉹",	FALSE},
	{ (char*)"065_itamemono",		(char*)"�u�ߕ�",				FALSE},
	{ (char*)"066_Heavy_Door",		(char*)"�d���h�A",				FALSE},
	{ (char*)"067_Ohirome",			(char*)"����I��",				FALSE},
	{ (char*)"068_Crash_Collision",	(char*)"�ǂ���",				FALSE},
	{ (char*)"069_Scatter",			(char*)"�����ǂ��ǂ�������",	FALSE},
	{ (char*)"070_lie down",		(char*)"�d���h�A",				FALSE},

	{ (char*)"071_metal_noise",		(char*)"�������a�މ�",	FALSE},
	{ (char*)"072_howan_reverse",	(char*)"�����ɖ߂鉹",	FALSE},
};
GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check;
//								�wCommu List�x												�wTEXT OFF�x�A�C�R���A	�Z�[�u�t�@�C���y�[�W�A						�}�b�v�ړ��m�F�p�I����		�}�b�v�L�����A�C�R���A	�����o���A									�R�~���Z���N�g���R�~����ޑI�����A	�R�~���Z���N�g���R�~���I����
GraphSize2 size_icon_loading, size_icon_commu_list, size_text_loading, size_icon_auto, size_icon_text_off, size_icon_sl_file_page,			size_ui_map_check_choice, size_ui_map_icon2, size_ui_map_hukidasi[MAP_HUKIDASI_NUMBER], size_ui_cs_alternative_type, size_ui_cs_alternative;
BGMState g_bgmstate[BGM_NUMBER];
MusicStringData music_string[BGM_NUMBER], music_string_stop;

char* bgm_name[BGM_NUMBER];

int loading_icon_flame = 0;			// ���[�f�B���O�A�C�R���`��p�o�߃t���[��
int g_time_first_load_start = 0;	// FIRST_LOAD���[�h���n�܂����~���b
// �t�H���g
int g_font1;				// ����������
//int g_font2;				// ����������蕶��
int g_font3;				// �e�𑜓x�Ή�����
int g_font_commu_name;		// �R�~����ԑ䎌��p����
int g_font_commu_line;		// �R�~����ԑ䎌�p����
int g_font_tips;			// tips�p����
int g_time_load_start = 0;	// ���t���[���Ń��[�h���J�n�����~���b

BOOL debug_mute = FALSE;																														// �a�f�l��ǂݍ��ނ����ʂ���f�o�b�O�@�\
BOOL load_bgm_finished[BGM_NUMBER];																												// �a�f�l�����ɓǂݍ��܂�Ă邩���ʂ���
// ���[�h�Ɋ֌W����`�揈��
void DrawLoading()
{
	bgimage_notice.DrawImageNotice();	// �x�����`��

	// �T�b�o�߂����烍�[�f�B���O�A�C�R����`�悷��
	if(g_time_first_load_start <= GetNowCount() - 3000)
	{
		loading_icon_flame++;
		if (loading_icon_flame >= LOADING_ICON_FLAME_MAX) { loading_icon_flame = 0; }
	}
	ScreenFlip();
}
// �Q��ȏ�ǂݍ��܂��\��������t�H���g���`����
void LoadFont()
{
	g_font3 = CreateFontToHandle("���C���I", FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);							// �e�𑜓x�Ή��t�H���g�i�e�X�g�j
	g_font_commu_name = CreateFontToHandle("���C���I", FONT_SIZE_ORIGINAL_COMMU_NAME * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);	// �e�𑜓x�Ή��t�H���g�i�R�~�����䎌��j
	g_font_commu_line = CreateFontToHandle("���C���I", FONT_SIZE_ORIGINAL_COMMU_LINE * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);	// �e�𑜓x�Ή��t�H���g�i�R�~�����䎌�j
	g_font_tips = CreateFontToHandle("���C���I", FONT_SIZE_ORIGINAL_TIPS * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);				// �e�𑜓x�Ή��t�H���g�itips�j
	for (int i = 0; i < font[0].GetFontNumber(); i++) { font[i].Create(); }
	// ���łɉ摜���̃f�[�^���Ē�`����
	GraphSizeChange(&size_icon_loading, g_imghandles.icon_loading);
	GraphSizeChange(&size_text_loading, g_imghandles.text_loading);
	GraphSizeChange(&size_icon_commu_list, g_imghandles.commu_list);
	GraphSizeChange(&size_icon_auto, g_imghandles.icon_auto[0]);
	GraphSizeChange(&size_icon_text_off, g_imghandles.icon_text_off);
	GraphSizeChange(&size_ui_map_check_choice, g_imghandles.ui_map_check_choice[0]);												// �}�b�v�ړ��m�F�p�I����
	GraphSizeChange(&size_ui_map_icon2, g_imghandles.ui_map_icon[0]);												// �}�b�v�L�����A�C�R���A
	for (int i = 0; i < MAP_HUKIDASI_NUMBER; i++) { GraphSizeChange(&size_ui_map_hukidasi[i], g_imghandles.ui_map_hukidasi[i]); }	// �}�b�v�L�����A�C�R�����͂ސ����o��
	GraphSizeChange(&size_ui_cs_alternative_type, g_imghandles.commu_select_type);													// �R�~���Z���N�g���R�~����ޑI����
	GraphSizeChange(&size_ui_cs_alternative, g_imghandles.commu_select);// �R�~���Z���N�g���R�~���I����

	CoordinateSetting();	// ��ʃT�C�Y�A��`������p�t�H���g����l�X�ȍ��W���`����
}
// ������ꂽ�摜�T�C�Y�l���X�N���[���{���ɉ������l�ɂ���
void GraphSizeChange(GraphSize2 *pgs, int x)	// �\���̃A�h���X,�摜
{
	// �X�N���[���T�C�Y�����x�؂�ւ��Ă����v�Ȃ悤�ɁA���X����l�̑��ɕʂ̕ϐ���p�ӂ��Ă����K�v������
	GetGraphSize(x, &pgs->ox, &pgs->oy);
	pgs->x = pgs->ox * bairitu;
	pgs->y = pgs->oy * bairitu;
}
// �L�����N�^�[�̐g�̕�����ǂݍ���
void LoadGameImageCharacterBody(int x, int* y, const char* z, int a)	// �ǂݍ��݂ɕK�v�ȕϐ�,�L�����N�^�[�����G�̑����,�ǂݍ��ރL�����t�H���_�̖��O,�i�L���������ɕK�v�ȕϐ��j
{
	char c[256];
	//const char* character = ("character_%s", z);
	sprintf_s(c, 256, "media\\%s_pause%d%d\\%s_pause%d%d.png", z, x, a, z, x, a);
	// �A�h���X�ɂ���K�v������̂ł́H
	*y = LoadGraph(c);
}
// �摜����ǂݍ���
BOOL LoadGameImage()
{
	// �t�H���g��`
	g_font1 = CreateFontToHandle("���C���I", 12, -1, DX_FONTTYPE_ANTIALIASING);

	if (image_cautionary_message.Load((char*)"media\\etc\\cautionary_message.png", FALSE, bairitu) == FALSE) { return FALSE; }	// �^�C�g���O���ӕ�

	g_imghandles.icon_commu_option = LoadGraph("media\\commu_option.png");
	if (g_imghandles.icon_commu_option == -1){ return FALSE; }
	GetGraphSizeF(g_imghandles.icon_commu_option, &size_commu_option.x, &size_commu_option.y);	// �摜�T�C�Y�𓾂�
	g_imghandles.icon_loading = LoadGraph("media\\UI\\loading_icon.png");
	if (g_imghandles.icon_loading == -1){ return FALSE; }
	g_imghandles.text_loading = LoadGraph("media\\UI\\loading_text.png");
	if (g_imghandles.text_loading == -1){ return FALSE; }
	// �wCommu List�x
	g_imghandles.commu_list = LoadGraph("media\\UI\\icon_commu_list.png");
	if (g_imghandles.commu_list == -1) { return FALSE; }
	// �wCommu Edit�x
	//if (image_icon_commu_edit.Load((char*)"media\\UI\\icon_commu_edit.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (hjimage_title.Load((char*)"media\\UI\\icon_commu_edit.png", TRUE, bairitu) == FALSE) { return FALSE; }
	//	�wAUTO�x�A�C�R��
	g_imghandles.icon_auto[0] = LoadGraph("media\\UI\\icon_auto.png");
	if (g_imghandles.icon_auto[0] == -1){ return FALSE; }
	g_imghandles.icon_auto[1] = LoadGraph("media\\UI\\icon_auto_ON.png");
	if (g_imghandles.icon_auto[1] == -1){ return FALSE; }
	//	�wSKIP�x�A�C�R��
	g_imghandles.icon_skip[0] = LoadGraph("media\\UI\\icon_skip_off.png");
	if (g_imghandles.icon_skip[0] == -1){ return FALSE; }
	g_imghandles.icon_skip[1] = LoadGraph("media\\UI\\icon_skip_on.png");
	if (g_imghandles.icon_skip[1] == -1){ return FALSE; }
	//	�wSAVE�x�A�C�R��
	g_imghandles.icon_save[0] = LoadGraph("media\\UI\\icon_save.png");
	if (g_imghandles.icon_save[0] == -1) { return FALSE; }
	g_imghandles.icon_save[1] = LoadGraph("media\\UI\\icon_save_now.png");
	if (g_imghandles.icon_save[1] == -1) { return FALSE; }
	//	�wLOAD�x�A�C�R��
	g_imghandles.icon_load[0] = LoadGraph("media\\UI\\icon_load.png");
	if (g_imghandles.icon_load[0] == -1) { return FALSE; }
	g_imghandles.icon_load[1] = LoadGraph("media\\UI\\icon_load_now.png");
	if (g_imghandles.icon_load[1] == -1) { return FALSE; }
	//	�wMENU�x�A�C�R���i[1]�́��}�[�N�j
	g_imghandles.icon_menu[0] = LoadGraph("media\\UI\\icon_menu.png");
	if (g_imghandles.icon_menu[0] == -1) { return FALSE; }
	g_imghandles.icon_menu[1] = LoadGraph("media\\UI\\icon_menu_close.png");
	if (g_imghandles.icon_menu[1] == -1) { return FALSE; }
	//	�wTEXT_OFF�x�A�C�R��
	g_imghandles.icon_text_off = LoadGraph("media\\UI\\icon_text_off.png");
	if (g_imghandles.icon_text_off == -1) { return FALSE; }
	//	�wBACK�x�A�C�R��
	g_imghandles.icon_back = LoadGraph("media\\UI\\icon_back.png");
	if (g_imghandles.icon_back == -1) { return FALSE; }
	// �o�b�N���O�p�wBACK�x
	if (image_icon_log_back.Load2(TRUE) == FALSE) { return FALSE; }
	//	�wTITLE�x�A�C�R��
	g_imghandles.icon_title = LoadGraph("media\\UI\\icon_title.png");
	if (g_imghandles.icon_title == -1) { return FALSE; }
	//	�wEXIT�x�A�C�R��
	g_imghandles.icon_exit = LoadGraph("media\\UI\\icon_exit.png");
	if (g_imghandles.icon_exit == -1) { return FALSE; }
	// �wOPTION�x�A�C�R��
	if (image_icon_option.Load((char*)"media\\UI\\icon_option.png", TRUE, bairitu) == FALSE) { return FALSE; }
	/* �o�b�N���O�p ---------*/
	if (image_icon_log.Load2(TRUE) == FALSE) { return FALSE; }
	// �w�i
	for (int i = 0; i < ImgDataHJ2::LOG_BACKGROUND_NUMBER; i++)
	{
		if (image_bl_background[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// ���A�C�R��
	for(int i = 0; i < ImgDataHJ2::TEXT_LOG_ARROW_NUMBER; i++)
	{
		if (image_icon_text_log[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �e�L�X�g�E�B���h�E
	for (int i = 0; i < ImgData2::LOG_TEXT_WINDOW_NUMBER; i++)
	{ 
		if (image_log_text_window[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	/*-----------------------*/
	// �Z�[�u�A���[�h��ʂŎg����e�A�C�R��
	for (int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++)
	{
		if (image_icon_new_option[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �Z�[�u�t�@�C��
	for(int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
	{ 
		if (image_icon_save_file[i][0].Load2(TRUE) == FALSE) { return FALSE; }
		if (image_icon_save_file[i][1].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �Z�[�u�t�@�C���̃y�[�W
	for(int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++)
	{
		if (image_icon_sl_page[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �摜�T�C�Y�𓾂�
	// ���̂t�h
	for (int i = 0; i < ImgDataMapFrame::GetMapFrameNumber(); i++) { if (ui_map_month[i].Load2(TRUE) == FALSE) { return FALSE; } }
	if (bgimage_non_month.Load2(TRUE) == FALSE) { return FALSE; }	// �̌��ŗp
	// tips�t�h
	g_imghandles.ui_tips = LoadGraph("media\\ui_tips.png");
	if (g_imghandles.ui_tips == -1){ return FALSE; }
	GetGraphSizeF(g_imghandles.ui_tips, &size_ui_tips.x, &size_ui_tips.y);	// �摜�T�C�Y�𓾂�
	// �}�b�v
	for (int i = 0; i < 3; i++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\UI\\map_%d.png", i + 1);
		g_imghandles.ui_map[i] = LoadGraph(c);
		if (g_imghandles.ui_map[i] == -1){ return FALSE; }
	}
	GetGraphSizeF(g_imghandles.ui_map[0], &size_ui_map.x, &size_ui_map.y);	// �摜�T�C�Y�𓾂�

	if (image_map_background.Load((char*)"media\\background\\map_BG.png", TRUE, bairitu) == FALSE) { return FALSE; }	// �}�b�v�I�����w�i
	// �}�b�v�ړ��p���
	if (hjimage_map[0].Load((char*)"media\\UI\\arrow_Left.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (hjimage_map[1].Load((char*)"media\\UI\\arrow_Right.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// �Z�[�u�E���[�h�A�C�R��
	if (hjimage_map[2].Load((char*)"media\\UI\\icon_save.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (hjimage_map[3].Load((char*)"media\\UI\\icon_load.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// �i�}�b�v�A�j�R�~���Z���N�g���[�h���Ŏg���A�C�R��
	g_imghandles.ui_map_icon[0] = LoadGraph("media\\UI\\map_meguru.png");
	if (g_imghandles.ui_map_icon[0] == -1){ return FALSE; }
	g_imghandles.ui_map_icon[1] = LoadGraph("media\\UI\\map_kogane.png");
	if (g_imghandles.ui_map_icon[1] == -1) { return FALSE; }
	g_imghandles.ui_map_icon[2] = LoadGraph("media\\UI\\map_juri.png");
	if (g_imghandles.ui_map_icon[2] == -1) { return FALSE; }
	g_imghandles.ui_map_icon[3] = LoadGraph("media\\UI\\map_rinze.png");
	if (g_imghandles.ui_map_icon[3] == -1) { return FALSE; }
	g_imghandles.ui_map_icon[4] = LoadGraph("media\\UI\\map_chiyuki.png");
	if (g_imghandles.ui_map_icon[4] == -1) { return FALSE; }
	// �e�L�X�g���O���[�h���Ŏg���L�����t�h
	for (int i = 0; i < ImgData2::IMC_NUMBER; i++)
	{
		if (image_map_character[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �����o��
	g_imghandles.ui_map_hukidasi[0] = LoadGraph("media\\UI\\map_hukidasi_one.png");
	if (g_imghandles.ui_map_hukidasi[0] == -1) { return FALSE; }
	g_imghandles.ui_map_hukidasi[1] = LoadGraph("media\\UI\\map_hukidasi_Two.png");
	if (g_imghandles.ui_map_hukidasi[1] == -1) { return FALSE; }
	g_imghandles.ui_map_hukidasi[2] = LoadGraph("media\\UI\\map_hukidasi_all.png");
	if (g_imghandles.ui_map_hukidasi[2] == -1) { return FALSE; }
	// �L���������o���A�C�R��
	for(int i = 0; i < ImgDataIconMapCharacter::GetNumber(); i++)
	{
		if (image_icon_map_character[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �R�~���ړ��m�F�t�h
	g_imghandles.ui_map_check = LoadGraph("media\\UI\\move_comu_check.png");
	if (g_imghandles.ui_map_check == -1){ return FALSE; }
	GetGraphSizeF(g_imghandles.ui_map_check, &size_ui_map_check.x, &size_ui_map_check.y);	// �摜�T�C�Y�𓾂�
	// �R�~���ړ��m�F�t�h�i�V�j
	for (int i = 0; i < ImgDataMapQuestion::GetNumber(); i++)
	{
		if (image_map_question[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �R�~���ړ��m�F�����̑I����
	g_imghandles.ui_map_check_choice[0] = LoadGraph("media\\UI\\move_comu_check_ok.png");
	if (g_imghandles.ui_map_check_choice[0] == -1){ return FALSE; }
	g_imghandles.ui_map_check_choice[1] = LoadGraph("media\\UI\\move_comu_check_no.png");
	if (g_imghandles.ui_map_check_choice[1] == -1){ return FALSE; }
	for (int i = 0; i < 2; i++)
	{
		if (image_icon_map_move_alternative[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �R�~���ړ��m�F�����̑I�����́w�������x�����蔻��p
	if (image_icon_map_collision_detection.Load2(TRUE) == FALSE) { return FALSE; }


	for(int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++)
	{
		if (image_icon_check[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// �Z�[�u���[�h���[�h�m�F�p�t�h
	for (int i = 0; i < ImgDataSLCheck::GetSLCImageNumber(); i++)
	{
		if (image_sl_check_message[i].Load2(TRUE) == FALSE) { return FALSE; } 
	}
	// �Q�[���I���m�F�t�h
	if (image_finish_check.Load2(TRUE) == FALSE) { return FALSE; }
	// �^�C�g���p�A�C�R��
	for (int i = 0; i < ImgDataHJTitle::GetMenuNumber(); i++)
	{
		for(int j = 0; j < 2; j++){if (image_title_menu[i][j].Load2(TRUE) == FALSE) { return FALSE; }}
	}
	// �I����
	for (int i = 0; i < ALTENATIVE_MAX_NUMBER; i++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\altenative_%d.png", i + 1);
		if (hjimage_alternative[i].Load(c, TRUE, bairitu) == FALSE) { return FALSE; }
	}
	// �w�i
	for (int i = 0; i < bgimage[0].GetNumber(); i++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\background\\board_%03d.png", i + 1);	// 100�����ł��K���R���ɂ���
		if (bgimage[i].Load(c, TRUE, bairitu) == FALSE) { return FALSE; }
	}
	// ���[�h�w�i�p����
	if (bgimage_room_teacher.Load2(TRUE) == FALSE) { return FALSE; }
	// �Z�[�u���[�h���[�h�摜
	for (int i = 0; i < 2; i++)
	{
		if (image_saveload_mode[i].Load2(TRUE) == FALSE) { return FALSE; }
	}

	for (int i = 0; i < ImgDataBGTutorial::GetNumber(); i++) { if (tutorial_image[i].Load(tutorial_image[i].GetPath(), TRUE, bairitu) == FALSE) { return FALSE; } }
	if (bgimage_notice.Load2(TRUE) == FALSE) { return FALSE; } 
	if (bgimage_title.Load2(TRUE) == FALSE) { return FALSE; }
	if (image_title_logo.Load2(TRUE) == FALSE) { return FALSE; }
	if (image_title_logo_stilltrial.Load2(TRUE) == FALSE) { return FALSE; }
	if (bgimage_tutorial_end.Load2(TRUE) == FALSE) { return FALSE; }	// �̌��ŏI���w�i
	// �^�C�g���{�[�_�[
	for(int i = 0; i < ImaDataName::GetTitleBorderNumber(); i++)
	{ 
		char c[256];
		sprintf_s(c, 256, "media\\background\\title\\border\\border_%d.png", i + 1);
		if (image_title_border[i].LoadName(c, TRUE) == FALSE) { return FALSE; }
	}
	// �������t�h
	if (bgimage_sukashi.Load2(TRUE) == FALSE) { return FALSE; }
	// �^�C�g���p�L���������G
	for (int i = 0; i < ImgDataTitleCharacter::GetTitleCharacterNumber(); i++) { if (image_title_character[i].Load2(TRUE) == FALSE) { return FALSE; } }
	// �_�C�A���O�\���t���O
	if (image_dialog[0].Load((char*)"media\\UI\\icon_dialog_off.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_dialog[1].Load((char*)"media\\UI\\icon_dialog_on.png", FALSE, bairitu) == FALSE) { return FALSE; }
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (image_icon_config_dialog[i][j].Load2(TRUE) == FALSE) { return FALSE; }
		}
	}
	// �A�C�R���ł��Ȃ��ϓ����Ȃ��I�v�V�����p�摜�i���A���A�����A�^�C�g���A�𑜓x�~�Q�j
	if (image_option[0].Load((char*)"media\\UI\\option_background.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[1].Load((char*)"media\\UI\\option_paper.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[2].Load((char*)"media\\UI\\option_menu.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[3].Load((char*)"media\\UI\\option_title.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[IMG_OPTION_PIXEL_720].Load((char*)"media\\UI\\option_pixel_720p.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option[IMG_OPTION_PIXEL_1080].Load((char*)"media\\UI\\option_pixel_1080p.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// �I�v�V�����I�����p���
	if (image_option_arrow[0].Load((char*)"media\\UI\\option_arrow_left.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option_arrow[1].Load((char*)"media\\UI\\option_arrow_right.png", FALSE, bairitu) == FALSE) { return FALSE; }
	// ���b�Z�[�W���x�I����
	if (image_option_message_speed[0].Load((char*)"media\\UI\\icon_message_speed_slow.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option_message_speed[1].Load((char*)"media\\UI\\icon_message_speed_normal.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option_message_speed[2].Load((char*)"media\\UI\\icon_message_speed_fast.png", TRUE, bairitu) == FALSE) { return FALSE; }
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (image_icon_config_text_speed[i][j].Load2(TRUE) == FALSE) { return FALSE; }
		}
	}
	// ��ʃ��[�h�I����
	if (image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].Load((char*)"media\\UI\\icon_option_fullscreen.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option_window_type[IO_WINDOW_TYPE_WINDOW].Load((char*)"media\\UI\\icon_option_window.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// �e�L�X�g�E�B���h�E�n
	for (int i = 0; i < 2; i++)
	{
		char c[256] = "";
		if (i == 0) { sprintf_s(c, 256, "namewindow"); }
		else{ sprintf_s(c, 256, "textwindow"); }
		for (int j = 0; j < 4; j++)
		{
			// sprintf_s�֐��̑�P�����A��S�ȍ~�̈����𗼕�c�ɂ���ƁAc�̏��߂̐��̕ϐ����폜����Ă��܂����ۂ��N����
			char c2[256] = "";
			switch (j)
			{
			case 0:		sprintf_s(c2, 256, "media\\UI\\%s_gray.png", c);		break;
			case 1:		sprintf_s(c2, 256, "media\\UI\\%s_bule.png", c);		break;
			case 2:		sprintf_s(c2, 256, "media\\UI\\%s_pink.png", c);		break;
			case 3:		sprintf_s(c2, 256, "media\\UI\\%s_green.png", c);		break;
			default:															break;
			}
			if (image_text_window[i][j].Load(c2, TRUE, bairitu) == FALSE) { return FALSE; }
		}
	}
	// �R�~����ޑI����
	g_imghandles.commu_select_type = LoadGraph("media\\UI\\cs_commu_type.png");
	if (g_imghandles.commu_select_type == -1) { return FALSE; }
	g_imghandles.commu_select = LoadGraph("media\\UI\\cs_commu.png");
	if (g_imghandles.commu_select == -1) { return FALSE; }

	/*�t�@�C���ǂݍ��݃e�X�g---------*/
	int FileHandle;
	// �\������x���W��y���W
	int x = 10;
	int y = 10;
	char gomi[8][256];

	/*�t�@�C����ǂݍ���---------*/
	// �e�R�~���̃X�e�[�^�X
	FileHandle = FileRead_open("media\\commu_status.csv");
	if (FileHandle == NULL) return FALSE;	// �G���[���̏���
	for (int i = 0; i < 1; i++) { FileRead_gets(gomi[0], 512, FileHandle); }	// �ŏ��̈�s��ǂݔ�΂�
	for (int i = 0; i < GlobalStaticVariable::GetCellLimit(); i++) {	// ��s�ڂ���1+x�s�ڂ܂œǂ݂Ƃ�
		FileRead_scanf(FileHandle,
			// �R�~���h�c�A		�t�@�C�����A			�^�C�g���A				�o���t�F�[�Y�A	�o�������A						�R�~���A�C�R���A				�o���]�[���A				���S����̏o���w���W����A			���S����̏o���x���W����
			"%d[^,],			%[^,],					%[^,],					%d[^,],			%d[^,],							%d[^,],							%d[^,],						%f[^,],								%f",
			&commu_data[i].id,	&commu_data[i].path,	&commu_data[i].title,	&gomi[0],		&commu_data[i].appear_timing,	&commu_data[i].character_icon,	&commu_data[i].map_zone,	&commu_data[i].map_coordinate_x,	&commu_data[i].map_coordinate_y);
		// �ǂݍ��܂ꂽ���W����̒l�ɔ{����������
		commu_data[i].map_coordinate_x *= bairitu;
		commu_data[i].map_coordinate_y *= bairitu;
		// �ǂݍ��܂ꂽ�s�ԍ���-1�Ȃ烋�[�v���I�����A����Ă�����R�~�������𑝂₷
		if (commu_data[i].id == -1) { i = GlobalStaticVariable::GetCellLimit(); }
		else { GlobalStaticVariable::CommuNumberCount(); }
	}
	FileRead_close(FileHandle);	// �t�@�C�������
	// �R�~���o���^�C�~���O
	FileHandle = FileRead_open("media\\upper_timing.csv");
	if (FileHandle == NULL) return FALSE;	// �G���[���̏���
	for (int i = 0; i < 1; i++) { FileRead_gets(gomi[0], 512, FileHandle); }	// �ŏ��̈�s��ǂݔ�΂�
	for (int i = 0; i < GAME_ALL_WEAK; i++) {	// ��s�ڂ���1+x�s�ڂ܂œǂ݂Ƃ�
		FileRead_scanf(FileHandle,
			// ���T�A	�V�X�e�����l�ł̌��T�i�K�v�Ȃ��H�j�A	�߂���A				�����A�@				����
			"%[^,],		%d[^,],									%d[^,],					%d[^,],					%d[^,]",
			&gomi[0],	&gomi[0],								&map_commu_upper[0][i],	&map_commu_upper[1][i],	&map_commu_upper[2][i]);
	}
	FileRead_close(FileHandle);	// �t�@�C�������
	// �R�~���t�@�C��
	for (int j = 0; j < GlobalStaticVariable::GetCommuNumber(); j++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\commu\\%s.csv", commu_data[j].path);
		FileHandle = FileRead_open(c);
		// �G���[���̏���
		if (FileHandle == NULL) { return FALSE; }

		for (int i = 0; i < 1; i++){ FileRead_gets(gomi[0], 1024, FileHandle); }	// �ŏ��̓�s��ǂݔ�΂��i���̂��G���[���N�������ߏC���j
		y = 10;
		for (int i = 0; i < COMMU_LINE_MAX; i++) {	// ��s�ڂ���1+n�s�ڂ܂œǂ݂Ƃ�
			// �ǂݍ��݁i�^�u�X�y�[�X���󂯂ĕs����N���Ȃ����͕s���j
			FileRead_scanf(FileHandle,
				//																																			�L�����N�^�[�E���A																				�i����\��j									�L�����N�^�[�E���A																				�i����\��j									�L�����N�^�[�E�E�A																				�i����\��j									�L�����N�^�[�ύX�^�C�v�A				�L�����N�^�[�����ψꉻ�̃I���I�t�A													�w�i�ύX�^�C�v�A�i�h�c�A�j												�a�f�l�؂�ւ��^�C�v
				"%[^,],				%d[^,],							%[^,],			%[^,],				%[^,],			%[^,],		%d[^,],					%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%d[^,],					%[^,],		%d[^,],								%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%d[^,],					%[^,],		%d[^,],								%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%d[^,],					%[^,],		%d[^,],								%[^,],		%d[^,],						%[^,],		%d[^,],								%[^,],		%d[^,],					%[^,],		%d[^,],							%[^,],		%d[^,],			%[^,],		%d[^,],					%[^,],		%d[^,],			%[^,],								%d[^,],							%[^,],								%d[^,],							%[^,],								%d",
				&HM[j][i].command,	&HM[j][i].move_commu_number,	&HM[j][i].name,	&HM[j][i].name2,	&HM[j][i].line,	&gomi[0],	&HM[j][i].line_mouse,	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&HM[j][i].character[0],	&gomi[0],	&HM[j][i].character_face_etc[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&HM[j][i].character[1], &gomi[0],	&HM[j][i].character_face_etc[1],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&HM[j][i].character[2], &gomi[0],	&HM[j][i].character_face_etc[2],	&gomi[0],	&HM[j][i].character_change,	&gomi[0],	&HM[j][i].character_even_distance,	&gomi[0],	&HM[j][i].background,	&gomi[0],	&HM[j][i].background_change,	&gomi[0],	&HM[j][i].bgm,	&gomi[0],	&HM[j][i].bgm_change,	&gomi[0],	&HM[j][i].se,	&HM[j][i].altenative_message[0],	&HM[j][i].altenative_jump[0],	&HM[j][i].altenative_message[1],	&HM[j][i].altenative_jump[1],	&HM[j][i].altenative_message[2],	&HM[j][i].altenative_jump[2]);
		}
		//WaitKey();	// �L�[���͑҂�
		// �t�@�C�������
		FileRead_close(FileHandle);
	}
	//WaitKey();	// �L�[���͑҂�

	// tips�t�@�C��
	FileHandle = FileRead_open("media\\tips.csv");
	if (FileHandle == NULL) return FALSE;	// �G���[���̏���
	for (int i = 0; i < 1; i++){ FileRead_gets(gomi[0], 256, FileHandle); }	// �ŏ��̈�s��ǂݔ�΂�
	int n = TipsData::LOAD_LIMIT;	// �f�[�^�̐�
	y = 10;
	for (int i = 0; i < n; i++){	// ��s�ڂ���1+n�s�ڂ܂œǂ݂Ƃ�
		FileRead_scanf(FileHandle, "%s", &tips_data[i].tips);		// �ǂݍ���
		tips_data[i].id = i;	// ID����
		//DrawFormatString(x, y, 0xFFFFFF, "%2d %10s", tips_data[i].id,tips_data[i].tips);	// �o��
		y += 20;
		// ����������Ă��Ȃ������烋�[�v���I��������
		if (strcmp(tips_data[i].tips, "") == 0) { i = n; }
		else { TipsData::NumberCount(); }
	}
	//WaitKey();	// �L�[���͑҂�
	// �t�@�C�������

	FileRead_close(FileHandle);
	/*---------------------------*/

	/*-------------------------------*/

	return TRUE;
}
// �r�d��ǂݍ���
BOOL LoadSE()
{
	// �^�C�g����ʈȑO�̃^�C�~���O�ŃN���b�N���ꂽ�ꍇ�^�C�g����ʂŃN���b�N��
	// �Ă��Ȃ��Ă��^�C�g���A�j���[�V�������J�b�g����Ă��܂��s����C�����邽
	// �߂̏���
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN){}
			else if (LogType != MOUSE_INPUT_LOG_DOWN){}
		}
	}

	for (int i = 0; i < SEData::GetNumber(); i++)
	{
		// �Y������h�c�̂r�d���܂��ǂݍ���ł��Ȃ��Ȃ�
		if (se[i].GetLoadFinished() == FALSE)
		{
			se[i].Load();	// �r�d��ǂݍ���
			if (se[i].GetHandle() == -1) { return FALSE; }
			// main.cpp�̃��[�v�J�n���Ԃ���P�^60�b���o�߂��Ă�����LoadBGM�֐��𔲂��o�����߂��o��
			if (g_time_load_start + (1000 / 60) <= GetNowCount()){ return TRUE; }
		}
	}
	ChangeSEVolume();										// �ǂݍ��܂ꂽ�΂���̂r�d�͉��ʂ�100���Ȃ̂ōĒ�������
	GameTitleNext();										// �r�d��S�ēǂݍ��߂���^�C�g����ʂֈڍs����
	SEPlay(static_cast<int>(SEData::IDName::START_EFFECT));	// ��p�̂r�d���Đ�
	return TRUE;
}

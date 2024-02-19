#include "loading.h"

const char* load_name[CHARACTER_GRAPH_NUMBER] = { "meguru", "kogane", "juri", "rinze", "chiyuki", "hazuki", "tsutomu" };	// キャラクター立ち絵読み込みの際に使われる名前情報

ImageHandles g_imghandles;
/* CharacterImageクラス ---------*/
const char* CharacterImage::LOAD_NAME[CharacterImage::CHARACTER_NUMBER] = { "meguru", "kogane", "juri", "rinze", "chiyuki", "hazuki", "tsutomu" };	// 読み込みの際に使われる名前情報
// エディットモードでの個別読み込みフラグ
BOOL CharacterImage::load_edit[CharacterImage::CHARACTER_NUMBER] = {FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE};

//const int CharacterImage::CHARACTER_NUMBER = 7;	// 人数
//const int CharacterImage::PAUSE_NUMBER = 10;	// ポーズ最大数
//const int CharacterImage::CLOTHES_NUMBER = 6;	// 衣装最大数
CharacterImage image_character[CharacterImage::CHARACTER_NUMBER][CharacterImage::PAUSE_NUMBER][CharacterImage::CLOTHES_NUMBER];
void CharacterImage::SetFlagAll(BOOL b)
{
	for (int i = 0; i < CHARACTER_NUMBER; i++)
	{
		// エディットモード移行時にフラグがオフになっているキャラは読み込みをスキップさせるようにする
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
// 読み込む画像の種類をチェックする
void CharacterImage::LoadFlagCheck()
{
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		for(int j = 0; j < COMMU_LINE_MAX; j++)
		{
			int x = HM[commu_number][j].character[i];
			//バッファオーバーラン解決用変数？
			int y = x / 1000 - 1;
			int z = x / 100 % 10;
			int a = x / 10 % 10;
			int b = x % 10;
			
			if (x > 0) 
			{ 
				// バッファーオーバーランを解決するために必要なif文
				if (y >= 0 && y < CharacterImage::CHARACTER_NUMBER &&z >= 0 && z < CharacterImage::PAUSE_NUMBER &&a >= 0 && a < CharacterImage::CLOTHES_NUMBER &&b >= 0 && b < CharacterImage::FACE_NUMBER)
				{
					image_character[y][z][a].SetLoadFlag(b);
				}
			}
		}
	}
}
// 全ての立ち絵をメモリから削除する
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
					// フラグが立ったままなら画像を消さない
					if (image_character[i][j][k].load_flag[l] == FALSE)
					{
						for (int m = 0; m < EYE_NUMBER + MOUSE_NUMBER; m++) { DeleteGraph(g_imghandles.character_face[i][j][k][l][m]); }
						for (int m = 0; m < EYE_BLOW_NUMBER; m++) { DeleteGraph(g_imghandles.character_eyebrow[i][j][k][l][m]); }
						image_character[i][j][k].load_flag_finished[l] = FALSE;	// 読み込み完了フラグもリセット
					}
				}
			}
		}
	}
}
// 読み込み処理
BOOL CharacterImage::Load()
{
	if (DebugLoadCheckCharacter() == FALSE || mode_debug == FALSE)
	{
		// エディット自のキャラ選択に関する変数
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
					char d[256];	// コミュテストプレイモード時のパス
					sprintf_s(d, 256, "media\\%s_pause%d%d\\%s_pause%d%d.png", load_name[j], i, l, load_name[j], i, l);
					//sprintf_s(c, 256, "media.dat\\%s_pause%d%d\\%s_pause%d%d.png", load_name[j], i, l, load_name[j], i, l);
					struct stat st;
					if (DXArchiveCheckFile("media.dat", c) == 1 || stat(d, &st) == 0)	// stat関数はc++のプログラムなのでDXアーカイブのことを考慮できない
					{
						// ログ
						//DebugLog(LogOutputType::LOAD_CHECK);
						if (GlobalStaticDebug::GetLog() == TRUE)
						{
							char c[256];
							sprintf_s(c, 256, "キャラ：%d、ポーズ：%d、衣装：%d\n", j, i, l);
							LogFileAdd(c);
						}
						LoadGameImageCharacterBody(i, &g_imghandles.character_body[j][i][l], load_name[j], l);
						if (g_imghandles.character_body[j][i][l] == -1) { return FALSE; }

						for (int m = 0; m < CHARACTER_GRAPH_FACE_NUMBER; m++)
						{
							char c3[256];	// 表情読み込み条件確認用文字列
							sprintf_s(c3, 256, "%s_pause%d%d\\%s_pause%d%d_eye%d0.png", load_name[j], i, l, load_name[j], i, l, m);
							char d3[256];
							sprintf_s(d3, 256, "media\\%s_pause%d%d\\%s_pause%d%d_eye%d0.png", load_name[j], i, l, load_name[j], i, l, m);
							// stat関数はc++のプログラムなのでDXアーカイブのことを考慮できない
							if ((DXArchiveCheckFile("media.dat", c3) == 1 || stat(d3, &st) == 0) && image_character[j][i][l].load_flag[m] == TRUE && image_character[j][i][l].load_flag_finished[m] == FALSE)
							{

								for (int k = 0; k < CHARACTER_GRAPH_EYE_NUMBER + CHARACTER_GRAPH_MOUSE_NUMBER; k++)
								{
									char c2[256];
									char* face_parts = k < CHARACTER_GRAPH_EYE_NUMBER ? (char*)"eye" : (char*)"mouth";
									sprintf_s(c2, 256, "%s_pause%d%d\\%s_pause%d%d_%s%d%d.png", load_name[j], i, l, load_name[j], i, l, face_parts, m, k < CHARACTER_GRAPH_EYE_NUMBER ? k : k - CHARACTER_GRAPH_EYE_NUMBER);
									char d2[256];
									sprintf_s(d2, 256, "media\\%s_pause%d%d\\%s_pause%d%d_%s%d%d.png", load_name[j], i, l, load_name[j], i, l, face_parts, m, k < CHARACTER_GRAPH_EYE_NUMBER ? k : k - CHARACTER_GRAPH_EYE_NUMBER);
									// 特殊な目パーツはこのタイミングでファイルが存在するかどうか確認し、存在してなければ読み込み処理をスキップする
									//struct stat st;
									if (k <= 2 || k >= CHARACTER_GRAPH_EYE_NUMBER || DXArchiveCheckFile("media.dat", c2) == 1 || stat(d2, &st) == 0)	// 存在していれば0を返す
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
								// キャラエディットの立ち絵選択に必要な数値を代入する
								edit_character_id[edit_c_y][edit_c_x] = (j + 1) * 1000 + i * 100 + l * 10 + m;
								// 選択肢用数値を加算して必要なら繰り上げる
								if (edit_c_x >= EDIT_CHARACTER_ALTERNATIVE_X_LIMIT - 1)
								{
									edit_c_x = 0;
									edit_c_y++;
								}
								else { edit_c_x++; }
								// 読み込み完了フラグを立てる
								image_character[j][i][l].load_flag_finished[m] = TRUE;
							}
						}
					}
				}
				// ここに何の意味もないクリック処理を挟む
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
		// エディットモードで使う立ち絵選択肢の行数を増加させる
		if(mode_debug == TRUE && edit_character_alternative_line_limit < edit_c_y + 1){edit_character_alternative_line_limit = edit_c_y + 1;}
		// （これ何？）
		//if (edit_c_x == 0) { edit_character_alternative_line_limit--; }
	}
	return TRUE;
}
/*-------------------------------*/
//SoundHandles g_sndhandles;
/* BGMDataクラス ---------*/
// （ここの部分の入力を終える）
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
// ループ関係の位置を設定する
void BGMData::SetLoop()
{
	if (LOOP_POS > 0) { SetLoopPosSoundMem(LOOP_POS, handle); }
	if (LOOP_START > 0) { SetLoopStartTimePosSoundMem(LOOP_START, handle); }
}
// メモリ解放されない種類のＢＧＭを読み込む
void BGMData::LoadFirst()
{
	for (int i = 0; i < NUMBER; i++)
	{
		// 削除されないＢＧＭなら読み込む
		if (bgm[i].not_release == TRUE)
		{
			bgm[i].handle = LoadSoundMem(bgm[i].path);
			if (bgm[i].handle == -1)
			{
				quit_game = TRUE;
				return;
			}
			bgm[i].SetLoop();	// ループ関係の位置を設定する
			// 読み込み完了フラグを立てる
			bgm[i].load_finished = TRUE;
		}
	}
	ChangeBGMVolume();	// 読み込まれたばかりのＢＧＭは音量が100％なので再調整する
}
// 全てのload変数を変更する
void BGMData::SetLoadAll(BOOL x)
{
	for (int i = 0; i < NUMBER; i++) { bgm[i].load = x; }
}
// 読み込むＢＧＭをチェックする
void BGMData::LoadFlagCheck()
{
	for (int i = 0; i < COMMU_LINE_MAX; i++)
	{
		if (HM[commu_number][i].GetBGM() > 0)
		{
			bgm[HM[commu_number][i].GetBGM() - 1].SetLoad(TRUE);
			// どの曲が使われているかチェックする
			//char c[256];
			//sprintf_s(c, 256, "%d：%s\n", HM[commu_number][i].GetBGM(), music_string[HM[commu_number][i].GetBGM() - 1].GetName());
			//LogFileAdd(c);
		}
	}
}
// 全てのＢＧＭをメモリから削除する
void BGMData::DeleteAll()
{
	for (int i = 0; i < BGM_NUMBER; i++)
	{
		// 消すＢＧＭではないand読み込みフラグが降りているならＢＧＭを消す
		if (bgm[i].GetNotRelease() == FALSE && bgm[i].load == FALSE)
		{ 
			DeleteSoundMem(bgm[i].handle);
			bgm[i].load_finished = FALSE;	// 読み込み完了フラグもリセット
		}
	}
}
// ロード処理
void BGMData::Load()
{
	for (int i = 0; i < BGM_NUMBER; i++)
	{
		// フラグが立っていないor既に読み込んでいるなら読み込んでフラグを立てる
		if (bgm[i].GetLoad() == TRUE && bgm[i].load_finished == FALSE)
		{
			bgm[i].handle = LoadSoundMem(bgm[i].path);
			if(bgm[i].handle == -1)
			{
				quit_game = TRUE;
				return;
			}
			bgm[i].SetLoop();	// ループ関係の位置を設定する
			// 読み込み完了フラグを立てる
			bgm[i].load_finished = TRUE;
		}
	}
	ChangeBGMVolume();	// 読み込まれたばかりのＢＧＭは音量が100％なので再調整する
}
/*------------------------*/

int SEData::number = 0;				// 総個数
int SEData::commu_start_time = 0;	// コミュスタートＳＥ再生時ミリ秒
SEData se[] = {
	{ (char*)"001_Wind_Chime",			(char*)"ウィンドチャイム",		FALSE},
	{ (char*)"002_Clap_Single",			(char*)"拍手（一人）",			FALSE},
	{ (char*)"003_Clap_Multi",			(char*)"拍手（大勢）",			FALSE},
	{ (char*)"004_Chime",				(char*)"チャイム",				FALSE},
	{ (char*)"005_BasketBall Dribble",	(char*)"ドリブル",				TRUE},
	{ (char*)"006_Foot_Step_01",		(char*)"足音",					FALSE},
	{ (char*)"006-2_Foot_Step_01_LOOP",	(char*)"足音（ループ）",		TRUE},
	{ (char*)"007_Curtain rail",		(char*)"カーテンを開ける音",	FALSE},
	{ (char*)"008_Callan colon",		(char*)"店のドアを開ける音",	FALSE},
	{ (char*)"009_Door_open",			(char*)"引き戸を開ける音",		FALSE},

	{ (char*)"010_Door Knock",		(char*)"ノックの音",						FALSE},
	{ (char*)"011_Bird_cry",		(char*)"鳥のさえずり",						FALSE},
	{ (char*)"012_Wind note",		(char*)"風の音",							FALSE},
	{ (char*)"013_Decision sound",	(char*)"選択肢を決定する",					FALSE},
	{ (char*)"014_River",			(char*)"川の水の流れの音",					FALSE},
	{ (char*)"014-2_River_LOOP",	(char*)"川の水の流れの音(LOOP)",			TRUE},
	{ (char*)"015_Cloth rubbing",	(char*)"布が擦れる音",						FALSE},
	{ (char*)"016_Basket Goal",		(char*)"バスケットボールがゴールに入る音",	FALSE},
	{ (char*)"017_Collosion",		(char*)"ぶつかる音",						FALSE},
	{ (char*)"018_Cat",				(char*)"猫の鳴き声",						FALSE},

	{ (char*)"019_Paper_Map_Move", (char*)"紙をめくる音",					FALSE},
	{ (char*)"020_Clap_1Tap", (char*)"ハイタッチ",							FALSE},
	{ (char*)"020-2_Clap_2Tap_01", (char*)"手を叩く音",						FALSE},
	{ (char*)"021_Crowed_Students", (char*)"ガヤ-1",						FALSE},
	{ (char*)"021-2_Crowed_Students_LOOP", (char*)"ガヤ-1(LOOP)",			TRUE},
	{ (char*)"022_Shoes", (char*)"シューズの音",							FALSE},
	{ (char*)"023_keybord_typing", (char*)"キーボードを叩く",				FALSE},
	{ (char*)"023-2_keybord_typing(LOOP)", (char*)"キーボードを叩く(LOOP)",	TRUE},
	{ (char*)"024_Paper_Flying", (char*)"紙が散らばる音",					FALSE},
	{ (char*)"025_Phone_notice_note", (char*)"携帯　通知",					FALSE},

	{ (char*)"026_Tumble",			(char*)"ずさー(転ぶ)",			FALSE},
	{ (char*)"027_Chair_standup",	(char*)"椅子を立つ音",			FALSE},
	{ (char*)"028_Gatagata",		(char*)"ガタガタとした物音",	FALSE},
	{ (char*)"029_Phone_call",		(char*)"携帯　着信音",			FALSE},
	{ (char*)"030_Icon_Tap",		(char*)"アイコンを押した音",	FALSE},
	{ (char*)"031_agemono",			(char*)"揚げ物をする音",		FALSE},
	{ (char*)"032_Flash_Back",		(char*)"フラッシュバック",		FALSE},
	{ (char*)"033_howanx4",			(char*)"思い出す音",			FALSE},
	{ (char*)"034_Door_Open_gatya",	(char*)"開き戸の音",			FALSE},
	{ (char*)"035_gasagasa_01",		(char*)"ガサガサ",				FALSE},

	{ (char*)"036_Dash_01",				(char*)"駆ける足音",		FALSE},
	{ (char*)"037_open_window",			(char*)"窓を開ける音",		FALSE},
	{ (char*)"038-1_pen_write",			(char*)"文字を書く",		FALSE},
	{ (char*)"038-2_pen_write(LOOP)",	(char*)"文字を書く(LOOP)",	TRUE},
	{ (char*)"039_Door_open_silent",	(char*)"静かに戸を開く",	FALSE},
	{ (char*)"040_Chair_sitdown",		(char*)"椅子に座る",		FALSE},
	{ (char*)"041-1_semi",				(char*)"セミの声",			FALSE},
	{ (char*)"042_jaguti_open",			(char*)"水道を開く",		FALSE},
	{ (char*)"043_jaguti_cloase",		(char*)"水道を止める音",	FALSE},
	{ (char*)"044-1_Scean_change_IN",	(char*)"場面転換IN",		FALSE},

	{ (char*)"044-2_Scean_change_OUT",	(char*)"場面転換OUT",		FALSE},
	{ (char*)"045_StartScean_note",		(char*)"スタート画面選択",	FALSE},
	{ (char*)"046_Start",				(char*)"Start",				FALSE},
	{ (char*)"047-1_Fluid_water",		(char*)"水道の音",			FALSE},
	{ (char*)"047-2_Fluid_water(LOOP)", (char*)"水道の音(LOOP)",	TRUE},
	{ (char*)"048_Gaan",				(char*)"がーん",			FALSE},
	{ (char*)"049_Hug",					(char*)"抱きつく音",		FALSE},
	{ (char*)"051_Ping_Pong",			(char*)"ピンポン",			FALSE},
	{ (char*)"052_Horror",				(char*)"ホラー",			FALSE},
	{ (char*)"053_Sentakushi",			(char*)"コミュ選択肢",		FALSE},

	{ (char*)"054_START_EFFECT",		(char*)"タイトル画面",		FALSE},
	{ (char*)"036-2_Dash_Room",			(char*)"駆ける足音(室内)",	FALSE},
	{ (char*)"055_Comu_Start",			(char*)"コミュスタート",	FALSE},
	{ (char*)"056_Dog",					(char*)"犬の鳴き声",		FALSE},
	{ (char*)"057_pin_pon_pan_pon",		(char*)"ピンポンパンポン",	FALSE},
	{ (char*)"058_Mic_Noise",			(char*)"マイクノイズ",		FALSE},
	{ (char*)"059-1_Thunder_S",			(char*)"雷鳴(小)",			FALSE},
	{ (char*)"059-2_Thunder_L",			(char*)"雷鳴(大)",			FALSE},
	{ (char*)"060_LittleCat",			(char*)"子猫の鳴き声",		FALSE},
	{ (char*)"061-1_huni",				(char*)"ふに",				FALSE},

	{ (char*)"061-2_hunix2",		(char*)"ふにふに",				FALSE},
	{ (char*)"062_Gatagata_02",		(char*)"ガタガタとした物音-2",	FALSE},
	{ (char*)"063_StandUp_Slow",	(char*)"ゆっくり立ち上がる",	FALSE},
	{ (char*)"064_Switch",			(char*)"スイッチを入れる音",	FALSE},
	{ (char*)"065_itamemono",		(char*)"炒め物",				FALSE},
	{ (char*)"066_Heavy_Door",		(char*)"重いドア",				FALSE},
	{ (char*)"067_Ohirome",			(char*)"お披露目",				FALSE},
	{ (char*)"068_Crash_Collision",	(char*)"どさっ",				FALSE},
	{ (char*)"069_Scatter",			(char*)"物がどさどさ落ちる",	FALSE},
	{ (char*)"070_lie down",		(char*)"重いドア",				FALSE},

	{ (char*)"071_metal_noise",		(char*)"金属が軋む音",	FALSE},
	{ (char*)"072_howan_reverse",	(char*)"現実に戻る音",	FALSE},
};
GraphSize size_commu_option, size_ui_tips, size_ui_map, size_ui_map_icon, size_ui_map_check;
//								『Commu List』												『TEXT OFF』アイコン、	セーブファイルページ、						マップ移動確認用選択肢		マップキャラアイコン、	吹き出し、									コミュセレクト時コミュ種類選択肢、	コミュセレクト時コミュ選択肢
GraphSize2 size_icon_loading, size_icon_commu_list, size_text_loading, size_icon_auto, size_icon_text_off, size_icon_sl_file_page,			size_ui_map_check_choice, size_ui_map_icon2, size_ui_map_hukidasi[MAP_HUKIDASI_NUMBER], size_ui_cs_alternative_type, size_ui_cs_alternative;
BGMState g_bgmstate[BGM_NUMBER];
MusicStringData music_string[BGM_NUMBER], music_string_stop;

char* bgm_name[BGM_NUMBER];

int loading_icon_flame = 0;			// ローディングアイコン描画用経過フレーム
int g_time_first_load_start = 0;	// FIRST_LOADモードが始まったミリ秒
// フォント
int g_font1;				// 小さい文字
//int g_font2;				// 小さい縁取り文字
int g_font3;				// 各解像度対応文字
int g_font_commu_name;		// コミュ状態台詞主用文字
int g_font_commu_line;		// コミュ状態台詞用文字
int g_font_tips;			// tips用文字
int g_time_load_start = 0;	// 現フレームでロードを開始したミリ秒

BOOL debug_mute = FALSE;																														// ＢＧＭを読み込むか判別するデバッグ機能
BOOL load_bgm_finished[BGM_NUMBER];																												// ＢＧＭが既に読み込まれてるか判別する
// ロードに関係する描画処理
void DrawLoading()
{
	bgimage_notice.DrawImageNotice();	// 警告文描画

	// ５秒経過したらローディングアイコンを描画する
	if(g_time_first_load_start <= GetNowCount() - 3000)
	{
		loading_icon_flame++;
		if (loading_icon_flame >= LOADING_ICON_FLAME_MAX) { loading_icon_flame = 0; }
	}
	ScreenFlip();
}
// ２回以上読み込まれる可能性があるフォントを定義する
void LoadFont()
{
	g_font3 = CreateFontToHandle("メイリオ", FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);							// 各解像度対応フォント（テスト）
	g_font_commu_name = CreateFontToHandle("メイリオ", FONT_SIZE_ORIGINAL_COMMU_NAME * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);	// 各解像度対応フォント（コミュ中台詞主）
	g_font_commu_line = CreateFontToHandle("メイリオ", FONT_SIZE_ORIGINAL_COMMU_LINE * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);	// 各解像度対応フォント（コミュ中台詞）
	g_font_tips = CreateFontToHandle("メイリオ", FONT_SIZE_ORIGINAL_TIPS * screen_size_y / WINDOW_SIZE_Y, -1, DX_FONTTYPE_ANTIALIASING);				// 各解像度対応フォント（tips）
	for (int i = 0; i < font[0].GetFontNumber(); i++) { font[i].Create(); }
	// ついでに画像幅のデータを再定義する
	GraphSizeChange(&size_icon_loading, g_imghandles.icon_loading);
	GraphSizeChange(&size_text_loading, g_imghandles.text_loading);
	GraphSizeChange(&size_icon_commu_list, g_imghandles.commu_list);
	GraphSizeChange(&size_icon_auto, g_imghandles.icon_auto[0]);
	GraphSizeChange(&size_icon_text_off, g_imghandles.icon_text_off);
	GraphSizeChange(&size_ui_map_check_choice, g_imghandles.ui_map_check_choice[0]);												// マップ移動確認用選択肢
	GraphSizeChange(&size_ui_map_icon2, g_imghandles.ui_map_icon[0]);												// マップキャラアイコン、
	for (int i = 0; i < MAP_HUKIDASI_NUMBER; i++) { GraphSizeChange(&size_ui_map_hukidasi[i], g_imghandles.ui_map_hukidasi[i]); }	// マップキャラアイコンを囲む吹き出し
	GraphSizeChange(&size_ui_cs_alternative_type, g_imghandles.commu_select_type);													// コミュセレクト時コミュ種類選択肢
	GraphSizeChange(&size_ui_cs_alternative, g_imghandles.commu_select);// コミュセレクト時コミュ選択肢

	CoordinateSetting();	// 画面サイズ、定義した専用フォントから様々な座標を定義する
}
// 代入された画像サイズ値をスクリーン倍率に応じた値にする
void GraphSizeChange(GraphSize2 *pgs, int x)	// 構造体アドレス,画像
{
	// スクリーンサイズを何度切り替えても大丈夫なように、元々ある値の他に別の変数を用意しておく必要がある
	GetGraphSize(x, &pgs->ox, &pgs->oy);
	pgs->x = pgs->ox * bairitu;
	pgs->y = pgs->oy * bairitu;
}
// キャラクターの身体部分を読み込む
void LoadGameImageCharacterBody(int x, int* y, const char* z, int a)	// 読み込みに必要な変数,キャラクター立ち絵の代入先,読み込むキャラフォルダの名前,（キャラ服装に必要な変数）
{
	char c[256];
	//const char* character = ("character_%s", z);
	sprintf_s(c, 256, "media\\%s_pause%d%d\\%s_pause%d%d.png", z, x, a, z, x, a);
	// アドレスにする必要があるのでは？
	*y = LoadGraph(c);
}
// 画像等を読み込む
BOOL LoadGameImage()
{
	// フォント定義
	g_font1 = CreateFontToHandle("メイリオ", 12, -1, DX_FONTTYPE_ANTIALIASING);

	if (image_cautionary_message.Load((char*)"media\\etc\\cautionary_message.png", FALSE, bairitu) == FALSE) { return FALSE; }	// タイトル前注意文

	g_imghandles.icon_commu_option = LoadGraph("media\\commu_option.png");
	if (g_imghandles.icon_commu_option == -1){ return FALSE; }
	GetGraphSizeF(g_imghandles.icon_commu_option, &size_commu_option.x, &size_commu_option.y);	// 画像サイズを得る
	g_imghandles.icon_loading = LoadGraph("media\\UI\\loading_icon.png");
	if (g_imghandles.icon_loading == -1){ return FALSE; }
	g_imghandles.text_loading = LoadGraph("media\\UI\\loading_text.png");
	if (g_imghandles.text_loading == -1){ return FALSE; }
	// 『Commu List』
	g_imghandles.commu_list = LoadGraph("media\\UI\\icon_commu_list.png");
	if (g_imghandles.commu_list == -1) { return FALSE; }
	// 『Commu Edit』
	//if (image_icon_commu_edit.Load((char*)"media\\UI\\icon_commu_edit.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (hjimage_title.Load((char*)"media\\UI\\icon_commu_edit.png", TRUE, bairitu) == FALSE) { return FALSE; }
	//	『AUTO』アイコン
	g_imghandles.icon_auto[0] = LoadGraph("media\\UI\\icon_auto.png");
	if (g_imghandles.icon_auto[0] == -1){ return FALSE; }
	g_imghandles.icon_auto[1] = LoadGraph("media\\UI\\icon_auto_ON.png");
	if (g_imghandles.icon_auto[1] == -1){ return FALSE; }
	//	『SKIP』アイコン
	g_imghandles.icon_skip[0] = LoadGraph("media\\UI\\icon_skip_off.png");
	if (g_imghandles.icon_skip[0] == -1){ return FALSE; }
	g_imghandles.icon_skip[1] = LoadGraph("media\\UI\\icon_skip_on.png");
	if (g_imghandles.icon_skip[1] == -1){ return FALSE; }
	//	『SAVE』アイコン
	g_imghandles.icon_save[0] = LoadGraph("media\\UI\\icon_save.png");
	if (g_imghandles.icon_save[0] == -1) { return FALSE; }
	g_imghandles.icon_save[1] = LoadGraph("media\\UI\\icon_save_now.png");
	if (g_imghandles.icon_save[1] == -1) { return FALSE; }
	//	『LOAD』アイコン
	g_imghandles.icon_load[0] = LoadGraph("media\\UI\\icon_load.png");
	if (g_imghandles.icon_load[0] == -1) { return FALSE; }
	g_imghandles.icon_load[1] = LoadGraph("media\\UI\\icon_load_now.png");
	if (g_imghandles.icon_load[1] == -1) { return FALSE; }
	//	『MENU』アイコン（[1]は▼マーク）
	g_imghandles.icon_menu[0] = LoadGraph("media\\UI\\icon_menu.png");
	if (g_imghandles.icon_menu[0] == -1) { return FALSE; }
	g_imghandles.icon_menu[1] = LoadGraph("media\\UI\\icon_menu_close.png");
	if (g_imghandles.icon_menu[1] == -1) { return FALSE; }
	//	『TEXT_OFF』アイコン
	g_imghandles.icon_text_off = LoadGraph("media\\UI\\icon_text_off.png");
	if (g_imghandles.icon_text_off == -1) { return FALSE; }
	//	『BACK』アイコン
	g_imghandles.icon_back = LoadGraph("media\\UI\\icon_back.png");
	if (g_imghandles.icon_back == -1) { return FALSE; }
	// バックログ用『BACK』
	if (image_icon_log_back.Load2(TRUE) == FALSE) { return FALSE; }
	//	『TITLE』アイコン
	g_imghandles.icon_title = LoadGraph("media\\UI\\icon_title.png");
	if (g_imghandles.icon_title == -1) { return FALSE; }
	//	『EXIT』アイコン
	g_imghandles.icon_exit = LoadGraph("media\\UI\\icon_exit.png");
	if (g_imghandles.icon_exit == -1) { return FALSE; }
	// 『OPTION』アイコン
	if (image_icon_option.Load((char*)"media\\UI\\icon_option.png", TRUE, bairitu) == FALSE) { return FALSE; }
	/* バックログ用 ---------*/
	if (image_icon_log.Load2(TRUE) == FALSE) { return FALSE; }
	// 背景
	for (int i = 0; i < ImgDataHJ2::LOG_BACKGROUND_NUMBER; i++)
	{
		if (image_bl_background[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// 矢印アイコン
	for(int i = 0; i < ImgDataHJ2::TEXT_LOG_ARROW_NUMBER; i++)
	{
		if (image_icon_text_log[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// テキストウィンドウ
	for (int i = 0; i < ImgData2::LOG_TEXT_WINDOW_NUMBER; i++)
	{ 
		if (image_log_text_window[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	/*-----------------------*/
	// セーブ、ロード画面で使われる各アイコン
	for (int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++)
	{
		if (image_icon_new_option[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// セーブファイル
	for(int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
	{ 
		if (image_icon_save_file[i][0].Load2(TRUE) == FALSE) { return FALSE; }
		if (image_icon_save_file[i][1].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// セーブファイルのページ
	for(int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++)
	{
		if (image_icon_sl_page[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// 画像サイズを得る
	// 月のＵＩ
	for (int i = 0; i < ImgDataMapFrame::GetMapFrameNumber(); i++) { if (ui_map_month[i].Load2(TRUE) == FALSE) { return FALSE; } }
	if (bgimage_non_month.Load2(TRUE) == FALSE) { return FALSE; }	// 体験版用
	// tipsＵＩ
	g_imghandles.ui_tips = LoadGraph("media\\ui_tips.png");
	if (g_imghandles.ui_tips == -1){ return FALSE; }
	GetGraphSizeF(g_imghandles.ui_tips, &size_ui_tips.x, &size_ui_tips.y);	// 画像サイズを得る
	// マップ
	for (int i = 0; i < 3; i++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\UI\\map_%d.png", i + 1);
		g_imghandles.ui_map[i] = LoadGraph(c);
		if (g_imghandles.ui_map[i] == -1){ return FALSE; }
	}
	GetGraphSizeF(g_imghandles.ui_map[0], &size_ui_map.x, &size_ui_map.y);	// 画像サイズを得る

	if (image_map_background.Load((char*)"media\\background\\map_BG.png", TRUE, bairitu) == FALSE) { return FALSE; }	// マップ選択時背景
	// マップ移動用矢印
	if (hjimage_map[0].Load((char*)"media\\UI\\arrow_Left.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (hjimage_map[1].Load((char*)"media\\UI\\arrow_Right.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// セーブ・ロードアイコン
	if (hjimage_map[2].Load((char*)"media\\UI\\icon_save.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (hjimage_map[3].Load((char*)"media\\UI\\icon_load.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// （マップ、）コミュセレクトモード等で使うアイコン
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
	// テキストログモード等で使うキャラＵＩ
	for (int i = 0; i < ImgData2::IMC_NUMBER; i++)
	{
		if (image_map_character[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// 吹き出し
	g_imghandles.ui_map_hukidasi[0] = LoadGraph("media\\UI\\map_hukidasi_one.png");
	if (g_imghandles.ui_map_hukidasi[0] == -1) { return FALSE; }
	g_imghandles.ui_map_hukidasi[1] = LoadGraph("media\\UI\\map_hukidasi_Two.png");
	if (g_imghandles.ui_map_hukidasi[1] == -1) { return FALSE; }
	g_imghandles.ui_map_hukidasi[2] = LoadGraph("media\\UI\\map_hukidasi_all.png");
	if (g_imghandles.ui_map_hukidasi[2] == -1) { return FALSE; }
	// キャラ吹き出しアイコン
	for(int i = 0; i < ImgDataIconMapCharacter::GetNumber(); i++)
	{
		if (image_icon_map_character[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// コミュ移動確認ＵＩ
	g_imghandles.ui_map_check = LoadGraph("media\\UI\\move_comu_check.png");
	if (g_imghandles.ui_map_check == -1){ return FALSE; }
	GetGraphSizeF(g_imghandles.ui_map_check, &size_ui_map_check.x, &size_ui_map_check.y);	// 画像サイズを得る
	// コミュ移動確認ＵＩ（新）
	for (int i = 0; i < ImgDataMapQuestion::GetNumber(); i++)
	{
		if (image_map_question[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// コミュ移動確認時等の選択肢
	g_imghandles.ui_map_check_choice[0] = LoadGraph("media\\UI\\move_comu_check_ok.png");
	if (g_imghandles.ui_map_check_choice[0] == -1){ return FALSE; }
	g_imghandles.ui_map_check_choice[1] = LoadGraph("media\\UI\\move_comu_check_no.png");
	if (g_imghandles.ui_map_check_choice[1] == -1){ return FALSE; }
	for (int i = 0; i < 2; i++)
	{
		if (image_icon_map_move_alternative[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// コミュ移動確認時等の選択肢の『いいえ』当たり判定用
	if (image_icon_map_collision_detection.Load2(TRUE) == FALSE) { return FALSE; }


	for(int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++)
	{
		if (image_icon_check[i].Load2(TRUE) == FALSE) { return FALSE; }
	}
	// セーブロードモード確認用ＵＩ
	for (int i = 0; i < ImgDataSLCheck::GetSLCImageNumber(); i++)
	{
		if (image_sl_check_message[i].Load2(TRUE) == FALSE) { return FALSE; } 
	}
	// ゲーム終了確認ＵＩ
	if (image_finish_check.Load2(TRUE) == FALSE) { return FALSE; }
	// タイトル用アイコン
	for (int i = 0; i < ImgDataHJTitle::GetMenuNumber(); i++)
	{
		for(int j = 0; j < 2; j++){if (image_title_menu[i][j].Load2(TRUE) == FALSE) { return FALSE; }}
	}
	// 選択肢
	for (int i = 0; i < ALTENATIVE_MAX_NUMBER; i++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\altenative_%d.png", i + 1);
		if (hjimage_alternative[i].Load(c, TRUE, bairitu) == FALSE) { return FALSE; }
	}
	// 背景
	for (int i = 0; i < bgimage[0].GetNumber(); i++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\background\\board_%03d.png", i + 1);	// 100未満でも必ず３桁にする
		if (bgimage[i].Load(c, TRUE, bairitu) == FALSE) { return FALSE; }
	}
	// ロード背景用自室
	if (bgimage_room_teacher.Load2(TRUE) == FALSE) { return FALSE; }
	// セーブロードモード画像
	for (int i = 0; i < 2; i++)
	{
		if (image_saveload_mode[i].Load2(TRUE) == FALSE) { return FALSE; }
	}

	for (int i = 0; i < ImgDataBGTutorial::GetNumber(); i++) { if (tutorial_image[i].Load(tutorial_image[i].GetPath(), TRUE, bairitu) == FALSE) { return FALSE; } }
	if (bgimage_notice.Load2(TRUE) == FALSE) { return FALSE; } 
	if (bgimage_title.Load2(TRUE) == FALSE) { return FALSE; }
	if (image_title_logo.Load2(TRUE) == FALSE) { return FALSE; }
	if (image_title_logo_stilltrial.Load2(TRUE) == FALSE) { return FALSE; }
	if (bgimage_tutorial_end.Load2(TRUE) == FALSE) { return FALSE; }	// 体験版終了背景
	// タイトルボーダー
	for(int i = 0; i < ImaDataName::GetTitleBorderNumber(); i++)
	{ 
		char c[256];
		sprintf_s(c, 256, "media\\background\\title\\border\\border_%d.png", i + 1);
		if (image_title_border[i].LoadName(c, TRUE) == FALSE) { return FALSE; }
	}
	// 透かしＵＩ
	if (bgimage_sukashi.Load2(TRUE) == FALSE) { return FALSE; }
	// タイトル用キャラ立ち絵
	for (int i = 0; i < ImgDataTitleCharacter::GetTitleCharacterNumber(); i++) { if (image_title_character[i].Load2(TRUE) == FALSE) { return FALSE; } }
	// ダイアログ表示フラグ
	if (image_dialog[0].Load((char*)"media\\UI\\icon_dialog_off.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_dialog[1].Load((char*)"media\\UI\\icon_dialog_on.png", FALSE, bairitu) == FALSE) { return FALSE; }
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (image_icon_config_dialog[i][j].Load2(TRUE) == FALSE) { return FALSE; }
		}
	}
	// アイコンでもなく変動しないオプション用画像（机、紙、文字、タイトル、解像度×２）
	if (image_option[0].Load((char*)"media\\UI\\option_background.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[1].Load((char*)"media\\UI\\option_paper.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[2].Load((char*)"media\\UI\\option_menu.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[3].Load((char*)"media\\UI\\option_title.png", FALSE, bairitu) == FALSE) { return FALSE; }
	if (image_option[IMG_OPTION_PIXEL_720].Load((char*)"media\\UI\\option_pixel_720p.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option[IMG_OPTION_PIXEL_1080].Load((char*)"media\\UI\\option_pixel_1080p.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// オプション選択肢用矢印
	if (image_option_arrow[0].Load((char*)"media\\UI\\option_arrow_left.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option_arrow[1].Load((char*)"media\\UI\\option_arrow_right.png", FALSE, bairitu) == FALSE) { return FALSE; }
	// メッセージ速度選択肢
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
	// 画面モード選択肢
	if (image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].Load((char*)"media\\UI\\icon_option_fullscreen.png", TRUE, bairitu) == FALSE) { return FALSE; }
	if (image_option_window_type[IO_WINDOW_TYPE_WINDOW].Load((char*)"media\\UI\\icon_option_window.png", TRUE, bairitu) == FALSE) { return FALSE; }
	// テキストウィンドウ系
	for (int i = 0; i < 2; i++)
	{
		char c[256] = "";
		if (i == 0) { sprintf_s(c, 256, "namewindow"); }
		else{ sprintf_s(c, 256, "textwindow"); }
		for (int j = 0; j < 4; j++)
		{
			// sprintf_s関数の第１引数、第４以降の引数を両方cにすると、cの初めの数個の変数が削除されてしまう現象が起きる
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
	// コミュ種類選択肢
	g_imghandles.commu_select_type = LoadGraph("media\\UI\\cs_commu_type.png");
	if (g_imghandles.commu_select_type == -1) { return FALSE; }
	g_imghandles.commu_select = LoadGraph("media\\UI\\cs_commu.png");
	if (g_imghandles.commu_select == -1) { return FALSE; }

	/*ファイル読み込みテスト---------*/
	int FileHandle;
	// 表示するx座標とy座標
	int x = 10;
	int y = 10;
	char gomi[8][256];

	/*ファイルを読み込む---------*/
	// 各コミュのステータス
	FileHandle = FileRead_open("media\\commu_status.csv");
	if (FileHandle == NULL) return FALSE;	// エラー時の処理
	for (int i = 0; i < 1; i++) { FileRead_gets(gomi[0], 512, FileHandle); }	// 最初の一行を読み飛ばす
	for (int i = 0; i < GlobalStaticVariable::GetCellLimit(); i++) {	// 二行目から1+x行目まで読みとる
		FileRead_scanf(FileHandle,
			// コミュＩＤ、		ファイル名、			タイトル、				出現フェーズ、	出現時期、						コミュアイコン、				出現ゾーン、				中心からの出現Ｘ座標ずれ、			中心からの出現Ｙ座標ずれ
			"%d[^,],			%[^,],					%[^,],					%d[^,],			%d[^,],							%d[^,],							%d[^,],						%f[^,],								%f",
			&commu_data[i].id,	&commu_data[i].path,	&commu_data[i].title,	&gomi[0],		&commu_data[i].appear_timing,	&commu_data[i].character_icon,	&commu_data[i].map_zone,	&commu_data[i].map_coordinate_x,	&commu_data[i].map_coordinate_y);
		// 読み込まれた座標ずれの値に倍率をかける
		commu_data[i].map_coordinate_x *= bairitu;
		commu_data[i].map_coordinate_y *= bairitu;
		// 読み込まれた行番号が-1ならループを終了し、違っていたらコミュ総数を増やす
		if (commu_data[i].id == -1) { i = GlobalStaticVariable::GetCellLimit(); }
		else { GlobalStaticVariable::CommuNumberCount(); }
	}
	FileRead_close(FileHandle);	// ファイルを閉じる
	// コミュ出現タイミング
	FileHandle = FileRead_open("media\\upper_timing.csv");
	if (FileHandle == NULL) return FALSE;	// エラー時の処理
	for (int i = 0; i < 1; i++) { FileRead_gets(gomi[0], 512, FileHandle); }	// 最初の一行を読み飛ばす
	for (int i = 0; i < GAME_ALL_WEAK; i++) {	// 二行目から1+x行目まで読みとる
		FileRead_scanf(FileHandle,
			// 月週、	システム数値での月週（必要ない？）、	めぐる、				恋鐘、　				樹里
			"%[^,],		%d[^,],									%d[^,],					%d[^,],					%d[^,]",
			&gomi[0],	&gomi[0],								&map_commu_upper[0][i],	&map_commu_upper[1][i],	&map_commu_upper[2][i]);
	}
	FileRead_close(FileHandle);	// ファイルを閉じる
	// コミュファイル
	for (int j = 0; j < GlobalStaticVariable::GetCommuNumber(); j++)
	{
		char c[256];
		sprintf_s(c, 256, "media\\commu\\%s.csv", commu_data[j].path);
		FileHandle = FileRead_open(c);
		// エラー時の処理
		if (FileHandle == NULL) { return FALSE; }

		for (int i = 0; i < 1; i++){ FileRead_gets(gomi[0], 1024, FileHandle); }	// 最初の二行を読み飛ばす（何故かエラーが起きたため修正）
		y = 10;
		for (int i = 0; i < COMMU_LINE_MAX; i++) {	// 二行目から1+n行目まで読みとる
			// 読み込み（タブスペースを空けて不具合が起きないかは不明）
			FileRead_scanf(FileHandle,
				//																																			キャラクター・左、																				（特殊表情）									キャラクター・中、																				（特殊表情）									キャラクター・右、																				（特殊表情）									キャラクター変更タイプ、				キャラクター距離均一化のオンオフ、													背景変更タイプ、（ＩＤ、）												ＢＧＭ切り替えタイプ
				"%[^,],				%d[^,],							%[^,],			%[^,],				%[^,],			%[^,],		%d[^,],					%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%d[^,],					%[^,],		%d[^,],								%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%d[^,],					%[^,],		%d[^,],								%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%[^,],		%d[^,],					%[^,],		%d[^,],								%[^,],		%d[^,],						%[^,],		%d[^,],								%[^,],		%d[^,],					%[^,],		%d[^,],							%[^,],		%d[^,],			%[^,],		%d[^,],					%[^,],		%d[^,],			%[^,],								%d[^,],							%[^,],								%d[^,],							%[^,],								%d",
				&HM[j][i].command,	&HM[j][i].move_commu_number,	&HM[j][i].name,	&HM[j][i].name2,	&HM[j][i].line,	&gomi[0],	&HM[j][i].line_mouse,	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&HM[j][i].character[0],	&gomi[0],	&HM[j][i].character_face_etc[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&HM[j][i].character[1], &gomi[0],	&HM[j][i].character_face_etc[1],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&gomi[0],	&HM[j][i].character[2], &gomi[0],	&HM[j][i].character_face_etc[2],	&gomi[0],	&HM[j][i].character_change,	&gomi[0],	&HM[j][i].character_even_distance,	&gomi[0],	&HM[j][i].background,	&gomi[0],	&HM[j][i].background_change,	&gomi[0],	&HM[j][i].bgm,	&gomi[0],	&HM[j][i].bgm_change,	&gomi[0],	&HM[j][i].se,	&HM[j][i].altenative_message[0],	&HM[j][i].altenative_jump[0],	&HM[j][i].altenative_message[1],	&HM[j][i].altenative_jump[1],	&HM[j][i].altenative_message[2],	&HM[j][i].altenative_jump[2]);
		}
		//WaitKey();	// キー入力待ち
		// ファイルを閉じる
		FileRead_close(FileHandle);
	}
	//WaitKey();	// キー入力待ち

	// tipsファイル
	FileHandle = FileRead_open("media\\tips.csv");
	if (FileHandle == NULL) return FALSE;	// エラー時の処理
	for (int i = 0; i < 1; i++){ FileRead_gets(gomi[0], 256, FileHandle); }	// 最初の一行を読み飛ばす
	int n = TipsData::LOAD_LIMIT;	// データの数
	y = 10;
	for (int i = 0; i < n; i++){	// 二行目から1+n行目まで読みとる
		FileRead_scanf(FileHandle, "%s", &tips_data[i].tips);		// 読み込み
		tips_data[i].id = i;	// IDを代入
		//DrawFormatString(x, y, 0xFFFFFF, "%2d %10s", tips_data[i].id,tips_data[i].tips);	// 出力
		y += 20;
		// 何も書かれていなかったらループを終了させる
		if (strcmp(tips_data[i].tips, "") == 0) { i = n; }
		else { TipsData::NumberCount(); }
	}
	//WaitKey();	// キー入力待ち
	// ファイルを閉じる

	FileRead_close(FileHandle);
	/*---------------------------*/

	/*-------------------------------*/

	return TRUE;
}
// ＳＥを読み込む
BOOL LoadSE()
{
	// タイトル画面以前のタイミングでクリックされた場合タイトル画面でクリックし
	// ていなくてもタイトルアニメーションがカットされてしまう不具合を修正するた
	// めの処理
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
		// 該当するＩＤのＳＥをまだ読み込んでいないなら
		if (se[i].GetLoadFinished() == FALSE)
		{
			se[i].Load();	// ＳＥを読み込む
			if (se[i].GetHandle() == -1) { return FALSE; }
			// main.cppのループ開始時間から１／60秒が経過していたらLoadBGM関数を抜け出す命令を出す
			if (g_time_load_start + (1000 / 60) <= GetNowCount()){ return TRUE; }
		}
	}
	ChangeSEVolume();										// 読み込まれたばかりのＳＥは音量が100％なので再調整する
	GameTitleNext();										// ＳＥを全て読み込めたらタイトル画面へ移行する
	SEPlay(static_cast<int>(SEData::IDName::START_EFFECT));	// 専用のＳＥを再生
	return TRUE;
}

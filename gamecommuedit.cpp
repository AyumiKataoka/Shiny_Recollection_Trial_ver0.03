#include "gamecommuedit.h"

EditType g_edittype;											// 現在何の機能を編集しているか
EditCharacterType g_editcharactertype = EDIT_CHARACTER_BODY;	// キャラクターのどの部分を編集しているか
CommandInputStringType g_commandinputstring = CIS_NULL;		// 今現在入力しているコマンド系文字列

//BackgroundName background_name[BACKGROUND_NUMBER] = { 
//	{(char*)"めぐるの部屋"},{(char*)"家庭科室"},		{(char*)"土手"},		{(char*)"校門前"},	{(char*)"テラス"},
//	{(char*)"廊下"},		{(char*)"屋外・掲示板前"},	{(char*)"前の学校"} ,	{(char*)"教室"} ,	{(char*)"職員室"} };


/* GlobalStaticEditクラス ---------*/
// 背景選択肢用
int GlobalStaticEdit::background_alternative_row = 0;
int GlobalStaticEdit::background_alternative_line = 0;				// 行カーソル
int GlobalStaticEdit::background_alternative_line_limit = 1;		// 行の最大数
int GlobalStaticEdit::background_alternative_line_draw = 0;			// １段目に描画する行
const int GlobalStaticEdit::BACKGROUND_ALTERNATIVE_LINE_NUMBER = 2;	// １行に並ぶ背景数
void GlobalStaticEdit::SetBackgroundAlternativeRow(int x)
{
	background_alternative_row += x;
	// 上下限を超えたカーソルを修正する
	if (background_alternative_row < 0) { background_alternative_row = 0; }
	else if (background_alternative_row >= BACKGROUND_ALTERNATIVE_LINE_NUMBER) { background_alternative_row = BACKGROUND_ALTERNATIVE_LINE_NUMBER - 1; }
}
void GlobalStaticEdit::SetBackgroundAlternativeLine(int x)
{
	background_alternative_line += x;
	// 上下限を超えたカーソルを修正する
	if (background_alternative_line < 0) { background_alternative_line = 0; }
	else if (background_alternative_line >= background_alternative_line_limit) { background_alternative_line = background_alternative_line_limit - 1; }
	// 描画行を変える処理
	if (background_alternative_line < background_alternative_line_draw) { background_alternative_line_draw = background_alternative_line; }
	else if (background_alternative_line >= background_alternative_line_draw + BACKGROUND_ALTERNATIVE_LINE_NUMBER) { background_alternative_line_draw = background_alternative_line - BACKGROUND_ALTERNATIVE_LINE_NUMBER + 1; }
}
/*---------------------------------*/
char c_global_function[256] = "";	// char関数の返り値として使う変数（ローカル配列変数をreturnで扱えないのでグローバル変数にする必要がある）

BOOL commu_edit_input_string;	// （台詞主編集時に）文字の入力を行っている状態か
BOOL g_inputbkey_prev;			// 直前のキーボードＢキーの状態
BOOL g_1key_prev;				// 直前のキーボード1キーの状態
BOOL g_2key_prev;				// 直前のキーボード2キーの状態
BOOL g_3key_prev;				// 直前のキーボード3キーの状態
BOOL g_4key_prev;				// 直前のキーボード4キーの状態
BOOL g_5key_prev;				// 直前のキーボード5キーの状態
BOOL g_6key_prev;				// 直前のキーボード6キーの状態
BOOL g_7key_prev;				// 直前のキーボード7キーの状態
BOOL g_8key_prev;				// 直前のキーボード8キーの状態
BOOL g_9key_prev;				// 直前のキーボード9キーの状態
BOOL g_0key_prev;				// 直前のキーボード0キーの状態
BOOL edit_insert_prev;			// 直前の挿入操作判定の状態
BOOL edit_copy_paste_prev;		// 直前のコピペ操作判定の状態
BOOL edit_delete_prev;			// 直前の行削除の状態

int edit_row = 0;												// 現在編集しようとしているもの
int edit_row_background = 1;									// 現在編集しようとしている背景のページ
int edit_row_bgm = 0;											// 現在編集しようとしているＢＧＭのページ
int edit_row_se = 0;											// 現在編集しようとしているＳＥのページ
int edit_line = 2;												// 現在編集している行数
int edit_play_bgm = 0;											// エディットモードで現在流れているＢＧＭＩＤ
int edit_character_id[256][EDIT_CHARACTER_ALTERNATIVE_X_LIMIT];	// 立ち絵選択時に必要なキャラＩＤ
int edit_character_alternative_row = 0;							// キャラ選択肢用の列カーソル
int edit_character_alternative_line = 0;						// キャラ選択肢用の行カーソル
int edit_character_alternative_line_limit = 1;					// キャラ選択肢用の行の最大数

// GAME_COMMU_EDIT状態のメイン処理
void GameCommuEdit()
{
	GameCommuEditControl();
	DrawGameCommuEdit();
}
// コミュエディット画面操作処理
void GameCommuEditControl()
{
	int key = GetJoypadInputState(DX_INPUT_KEY);
	// 文字入力時
	if(g_edittype == EDIT_LINES || commu_edit_input_string == TRUE)
	{ 
		// 台詞の入力が完了したら
		if (CheckKeyInput(InputHandle) != 0)
		{
			// エスケープキーによる終了でなければ入力された文字列を取得
			if (CheckHitKey(KEY_INPUT_ESCAPE) == FALSE) 
			{
				switch (g_edittype)
				{
				case EDIT_LINES_CHARACTER:	commu_state_edit[edit_line].LineCharacterChange(0, InputHandle);	break;
				case EDIT_LINES_CHARACTER2:	commu_state_edit[edit_line].LineCharacterChange(1, InputHandle);	break;
				case EDIT_LINES:			commu_state_edit[edit_line].LineChange(InputHandle);				break;
				default:																						break;
				}
				// コマンド系
				if (g_commandinputstring == CIS_FRAME_AUTO || g_commandinputstring == CIS_MOVE_SELL || g_commandinputstring == CIS_MOVE_COMMU) { commu_state_edit[edit_line].CommandNumberChange(GetKeyInputNumber(InputHandle)); }
				if (g_commandinputstring >= CIS_ALTERNATIVE2_1 && g_commandinputstring <= CIS_ALTERNATIVE3_3){commu_state_edit[edit_line].AlternativeChange(g_commandinputstring <= CIS_ALTERNATIVE2_2 ? g_commandinputstring - CIS_ALTERNATIVE2_1 : g_commandinputstring - CIS_ALTERNATIVE3_1, InputHandle); }
				// （適当な数値を入れる）
				//if (g_commandinputstring >= CIS_ALTERNATIVE2_1 && g_commandinputstring <= CIS_ALTERNATIVE3_3) { commu_state_edit[edit_line].AlternativeJumpChange
				//( , GetKeyInputNumber(InputHandle)); }
				switch (g_commandinputstring)
				{
				case CIS_FRAME_AUTO:			
					commu_state_edit[edit_line].CommandChange((char*)"frame_auto");		
					g_commandinputstring = CIS_NULL;
					break;
				case CIS_MOVE_SELL:
					commu_state_edit[edit_line].CommandChange((char*)"move_sell");
					g_commandinputstring = CIS_NULL;
					break;
				case CIS_MOVE_COMMU:			
					commu_state_edit[edit_line].CommandChange((char*)"move_commu");		
					g_commandinputstring = CIS_NULL;
					break;
				case CIS_ALTERNATIVE2_1:		commu_state_edit[edit_line].AlternativeChange(0 ,InputHandle);		break;
				case CIS_ALTERNATIVE2_2:		commu_state_edit[edit_line].AlternativeChange(1, InputHandle);		break;
				case CIS_ALTERNATIVE3_1:		commu_state_edit[edit_line].AlternativeChange(0, InputHandle);		break;
				case CIS_ALTERNATIVE3_2:		commu_state_edit[edit_line].AlternativeChange(1, InputHandle);		break;
				case CIS_ALTERNATIVE3_3:		commu_state_edit[edit_line].AlternativeChange(2, InputHandle);		break;
				case CIS_ALTERNATIVE_JUMP2_1:	commu_state_edit[edit_line].AlternativeJumpChange(0, GetKeyInputNumber(InputHandle));	break;
				case CIS_ALTERNATIVE_JUMP2_2:
					commu_state_edit[edit_line].CommandChange((char*)"altenative_2");	
					g_commandinputstring = CIS_NULL;
					commu_state_edit[edit_line].AlternativeJumpChange(1, GetKeyInputNumber(InputHandle));
					break;
				case CIS_ALTERNATIVE_JUMP3_1:	commu_state_edit[edit_line].AlternativeJumpChange(0, GetKeyInputNumber(InputHandle));	break;
				case CIS_ALTERNATIVE_JUMP3_2:	commu_state_edit[edit_line].AlternativeJumpChange(1, GetKeyInputNumber(InputHandle));	break;
				case CIS_ALTERNATIVE_JUMP3_3:
					commu_state_edit[edit_line].CommandChange((char*)"altenative_3");	
					g_commandinputstring = CIS_NULL;
					commu_state_edit[edit_line].AlternativeJumpChange(2, GetKeyInputNumber(InputHandle));
					break;
				default:																							
					break;
				}
			}
			else
			{
				g_commandinputstring = CIS_NULL;
			}
			DeleteKeyInput(InputHandle);
			g_edittype = EDIT_DEFAULT;
			commu_edit_input_string = FALSE;			// EDIT_LINES状態の時についでにこの処理をしても恐らく問題ない
			// 条件に応じて再び文字を入力する状態にする
			if (CheckHitKey(KEY_INPUT_ESCAPE) == FALSE)
			{
				switch (g_commandinputstring)
				{
				case CIS_ALTERNATIVE2_1:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP2_1);	break;
				case CIS_ALTERNATIVE2_2:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP2_2);	break;
				case CIS_ALTERNATIVE3_1:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP3_1);	break;
				case CIS_ALTERNATIVE3_2:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP3_2);	break;
				case CIS_ALTERNATIVE3_3:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP3_3);	break;
				case CIS_ALTERNATIVE_JUMP2_1:	GameCommuEditAlternativeInput(CIS_ALTERNATIVE2_2);		break;
				case CIS_ALTERNATIVE_JUMP3_1:	GameCommuEditAlternativeInput(CIS_ALTERNATIVE3_2);		break;
				case CIS_ALTERNATIVE_JUMP3_2:	GameCommuEditAlternativeInput(CIS_ALTERNATIVE3_3);		break;
				default:																				break;
				}
			}
			if (IsENTERKeyTrigger(key, 0) == TRUE) {}	// 文字入力確定→デフォルト状態で即座に項目確定の誤作動を防ぐためのチェックだけの処理
		}
	}
	else
	{
		// 左右キーに応じて編集内容候補を変化させる
		if (IsLEFTKeyTrigger(key, 0) == TRUE)
		{
			switch (g_edittype)
			{
			case EDIT_DEFAULT:
				if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) { edit_row = 0; }
				else if (edit_row > 0) { edit_row--; }						
				break;
			case EDIT_CHARACTER_LEFT:	
			case EDIT_CHARACTER_CENTER:
			case EDIT_CHARACTER_RIGHT:
				if (edit_character_alternative_row > 0) { edit_character_alternative_row--; }
				break;
			case EDIT_BACKGROUND:
				if (edit_row_background > 0) { edit_row_background--; }
				GlobalStaticEdit::SetBackgroundAlternativeRow(-1);
				break;
			case EDIT_BGM:			if (edit_row_bgm > 0) { edit_row_bgm--; }				break;
			case EDIT_SE:			if (edit_row_se > 0) { edit_row_se--; }					break;
			default:																		break;
			}
		}
		if (IsRIGHTKeyTrigger(key, 0) == TRUE)
		{
			switch (g_edittype)
			{
			case EDIT_DEFAULT:
				if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) { edit_row = EDIT_SELECT_PAGE_MAX; }
				else if (edit_row < EDIT_SELECT_PAGE_MAX) { edit_row++; }
				break;
			case EDIT_CHARACTER_LEFT:
			case EDIT_CHARACTER_CENTER:
			case EDIT_CHARACTER_RIGHT:
				if (edit_character_alternative_row < EDIT_CHARACTER_ALTERNATIVE_X_LIMIT - 1) { edit_character_alternative_row++; }
				break;
			#pragma region ver0.00704制作時コメント化コード
			//case EDIT_BACKGROUND:	if (edit_row_background < (BACKGROUND_NUMBER - 1) / 10 + 1) { edit_row_background++; }	break;
#pragma endregion
			case EDIT_BACKGROUND:
				if (edit_row_background < (bgimage[0].GetNumber() - 1) / 10 + 1) { edit_row_background++; }
				GlobalStaticEdit::SetBackgroundAlternativeRow(1);
				break;
			case EDIT_BGM:			if (edit_row_bgm < (BGMData::GetNumber() - 1) / 10 + 1) { edit_row_bgm++; }												break;
			#pragma region ver0.00707制作時コメント化コード
			//case EDIT_SE:			if (edit_row_se < SE_NUMBER / 10 + 1) { edit_row_se++; }								break;
#pragma endregion
			case EDIT_SE:			if (edit_row_se < SEData::GetNumber() / 10 + 1) { edit_row_se++; }								break;
			default:																										break;
			}
		}
		// 押しっぱなしのキーに応じて動く行の桁数を変える
		int move_line_times = 1;
		if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) { move_line_times = 100; }
		else if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) { move_line_times = 10; }
		// 上下キーに応じて編集行を変化させる
		//if (IsUPKeyTrigger(key, 0) == TRUE && edit_line > 2)
		if (IsUPKeyTrigger(key, 0) == TRUE)
		{
			//if (g_edittype == EDIT_DEFAULT) { edit_line--; }
			if (g_edittype == EDIT_DEFAULT) 
			{ 
				edit_line -= move_line_times;
				if (edit_line < 2) { edit_line = 2; }
			}
			// キャラクター選択肢
			else if (g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT && edit_character_alternative_line > 0) { edit_character_alternative_line--; }
			// 背景選択肢
			else if (g_edittype == EDIT_BACKGROUND) { GlobalStaticEdit::SetBackgroundAlternativeLine(-1); }
		}
		//if (IsDOWNKeyTrigger(key, 0) == TRUE && edit_line < COMMU_LINE_MAX_EDIT - 1)
		if (IsDOWNKeyTrigger(key, 0) == TRUE)
		{
			//if (g_edittype == EDIT_DEFAULT) { edit_line++; }
			if (g_edittype == EDIT_DEFAULT)
			{
				edit_line += move_line_times;
				if (edit_line > COMMU_LINE_MAX_EDIT - 1) { edit_line = COMMU_LINE_MAX_EDIT - 1; }
			}
			// キャラクター選択肢
			else if (g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT && edit_character_alternative_line < edit_character_alternative_line_limit - 1) { edit_character_alternative_line++; }
			// 背景選択肢（なぜかできない）
			else if (g_edittype == EDIT_BACKGROUND) { GlobalStaticEdit::SetBackgroundAlternativeLine(1); }
		}

		if (IsINPUTBKeyTrigger() == TRUE)
		{
			int edit_commu_number = static_cast<int>(CommuType::EDIT);
			switch (g_edittype)
			{
			// コミュセレクト用エディットコミュにエディット内容をコピペしてタイトルへ戻る
			case EDIT_DEFAULT:
				for (int i = 2; i < COMMU_LINE_MAX; i++)
				{
					//HM[edit_commu_number][i - 2](commu_state_edit[i]());	// 
					HM[edit_commu_number][i - 2].CommandChange(commu_state_edit[i].GetCommand());						// コマンド
					HM[edit_commu_number][i - 2].CommandNumberChange(commu_state_edit[i].GetCommandNumber());			// 各特定コマンド用数値
					HM[edit_commu_number][i - 2].LineCharacterChange(0, commu_state_edit[i].GetLineCharacterName());	// 台詞主
					HM[edit_commu_number][i - 2].LineCharacterChange(1, commu_state_edit[i].GetLineCharacterName2());	// 台詞主２
					HM[edit_commu_number][i - 2].LineChange(commu_state_edit[i].GetLine());								// 台詞
					HM[edit_commu_number][i - 2].LineMouseChange(commu_state_edit[i].GetLineMouse());					// 台詞口パクタイプ
					for(int j = 0; j < 3; j++)
					{
						HM[edit_commu_number][i - 2].CharacterIDChange(j, commu_state_edit[i].GetCharacter(j));				// キャラクターＩＤ
						HM[edit_commu_number][i - 2].CFECHANGE(j, commu_state_edit[i].GetCFE(j));							// キャラクター特殊表情
						HM[edit_commu_number][i - 2].AlternativeChange(j, commu_state_edit[i].GetAlternativeString(j));		// 選択肢文字列
						HM[edit_commu_number][i - 2].AlternativeJumpChange(j, commu_state_edit[i].GetAlternativeJump(j));	// 選択肢ジャンプ先行
					}
					HM[edit_commu_number][i - 2].CCCHANGE(commu_state_edit[i].GetCC());										// キャラクター変更タイプ
					HM[edit_commu_number][i - 2].CDUCHANGE(commu_state_edit[i].GetCDU());									// キャラ間距離均一化
					HM[edit_commu_number][i - 2].BackgroundChange(commu_state_edit[i].GetBackground());						// 背景
					HM[edit_commu_number][i - 2].BackgroundChangeTypeChange(commu_state_edit[i].GetBackgroundChangeType());	// 背景変更タイプ
					HM[edit_commu_number][i - 2].BGMChange(commu_state_edit[i].GetBGM());	// ＢＧＭ
					HM[edit_commu_number][i - 2].BCTChange(commu_state_edit[i].GetBGMCT());	// ＢＧＭ変更タイプ
					HM[edit_commu_number][i - 2].SEChange(commu_state_edit[i].GetSE());		// ＳＥ

				}
				GameTitleNext();
				break;	

				//case EDIT_COMMAND_NUMBER:						break;
			default:					g_edittype = EDIT_DEFAULT;	break;
			}
		}
		// Dキーを押したタイミングに応じて様々なものを決定する		
		if (CheckHitKey(KEY_INPUT_D) == TRUE) 
		{ 
			if (g_edittype == EDIT_DEFAULT)
			{
				if (edit_row == EDIT_SELECT_LINES) { commu_state_edit[edit_line].LineChange((char*)""); }					// 台詞を全削除する
				// キャラ変数を初期化する
				else if (edit_row == EDIT_SELECT_CHARACTER_LEFT) { commu_state_edit[edit_line].CharacterIDChange(0, 0); }
				else if (edit_row == EDIT_SELECT_CHARACTER_CENTER) { commu_state_edit[edit_line].CharacterIDChange(1, 0); }
				else if (edit_row == EDIT_SELECT_CHARACTER_RIGHT) { commu_state_edit[edit_line].CharacterIDChange(2, 0); }
			}
		}
		// エンターを押したタイミングに応じて様々なものを決定する
		if (IsENTERKeyTrigger(key, 0) == TRUE)
		{
			char* c_line = commu_state_edit[edit_line].line;	// キー入力をする際、前回の台詞内容を表示させるための変数
			switch (g_edittype)
			{
			case EDIT_DEFAULT:
				// edit_rowが位置していた場所に応じて編集するものが変わる
				switch (edit_row)
				{
				case EDIT_SELECT_COMMAND:			g_edittype = EDIT_COMMAND;			break;
				case EDIT_SELECT_LINES_CHARACTER:	g_edittype = EDIT_LINES_CHARACTER;	break;
				case EDIT_SELECT_LINES_CHARACTER2:	g_edittype = EDIT_LINES_CHARACTER2;	break;
				case EDIT_SELECT_LINES:
					GameCommuEditInputString(105, FALSE,c_line);	// 「」が余分に出てしまうので101のところ先の数字にしている
					g_edittype = EDIT_LINES;
					break;
				case EDIT_SELECT_LINES_MOUSE:		g_edittype = EDIT_LINES_MOUSE;		break;
				case EDIT_SELECT_CHARACTER_LEFT:	
					g_edittype = EDIT_CHARACTER_LEFT;	
					g_editcharactertype = EDIT_CHARACTER_BODY;
					break;
				case EDIT_SELECT_CHARACTER_CENTER:
					g_edittype = EDIT_CHARACTER_CENTER;
					g_editcharactertype = EDIT_CHARACTER_BODY;
					break;
				case EDIT_SELECT_CHARACTER_RIGHT:
					g_edittype = EDIT_CHARACTER_RIGHT;
					g_editcharactertype = EDIT_CHARACTER_BODY;
					break;
				case EDIT_SELECT_BACKGROUND:
					g_edittype = EDIT_BACKGROUND;
					edit_row_background = 1;
					break;
				case EDIT_SELECT_BGM:
					g_edittype = EDIT_BGM;
					edit_row_bgm = 1;
					break;
				case EDIT_SELECT_SE:
					g_edittype = EDIT_SE;
					edit_row_se = 1;
					break;
				default:																break;
				}
				break;
			case EDIT_CHARACTER_LEFT:
			case EDIT_CHARACTER_CENTER:
			case EDIT_CHARACTER_RIGHT:
				commu_state_edit[edit_line].CharacterIDChange(g_edittype - EDIT_CHARACTER_LEFT, edit_character_id[edit_character_alternative_line][edit_character_alternative_row]);
				g_edittype = EDIT_DEFAULT;
				break;
			default:																	break;
			}

		}
		if (g_edittype == EDIT_DEFAULT)
		{
			// 空白行挿入
			if (IsInsertTrigger() == TRUE)
			{
				for (int i = COMMU_LINE_MAX_EDIT - 1; i >= edit_line; i--)
				{
					GameCommuEditLineErase(i);								// 行の内容を消去する
					if (i > edit_line) { GameCommuEditLineCopy(i, i - 1, 1); }	// 編集中の行でなければi行目にi-1行目の内容をコピーする
				}
			}
			// 行コピー挿入
			if (IsCopyPasteTrigger() == TRUE)
			{
				for (int i = COMMU_LINE_MAX_EDIT - 1; i >= edit_line; i--)
				{
					GameCommuEditLineErase(i);								// 行の内容を消去する
					if (i > edit_line) { GameCommuEditLineCopy(i, i - 1, 1); }	// 編集中の行でなければi行目にi-1行目の内容をコピーする
				}
				GameCommuEditLineCopy(edit_line, edit_line + 1, 0);	// 選択行に『選択行+1』行目の内容をコピーする
			}
			// 行削除
			if (IsDeleteTrigger() == TRUE)
			{
				for (int i = edit_line; i < COMMU_LINE_MAX_EDIT - 1; i++) { GameCommuEditLineCopy(i, i + 1, -1); }
				GameCommuEditLineErase(COMMU_LINE_MAX_EDIT - 1);	// 最後の行は削除する
			}
		}
		// コマンド選択時の処理
		if (g_edittype == EDIT_COMMAND && g_commandinputstring == CIS_NULL)
		{
			if (CheckHitKey(KEY_INPUT_2) == TRUE || CheckHitKey(KEY_INPUT_5) == TRUE || CheckHitKey(KEY_INPUT_7) == TRUE) { GameCommuEditInputString(3, TRUE, (char*)""); }
			else if (CheckHitKey(KEY_INPUT_3) == TRUE || CheckHitKey(KEY_INPUT_4) == TRUE) { GameCommuEditInputString(33, FALSE, (char*)""); }

			if (Is1KeyTrigger() == TRUE) 
			{ 
				commu_state_edit[edit_line].CommandChange((char*)"auto_se");
				g_edittype = EDIT_DEFAULT;
			}
			else if (Is2KeyTrigger() == TRUE) { g_commandinputstring = CIS_FRAME_AUTO; }
			else if (Is3KeyTrigger() == TRUE) { g_commandinputstring = CIS_ALTERNATIVE2_1; }
			else if (Is4KeyTrigger() == TRUE) { g_commandinputstring = CIS_ALTERNATIVE3_1; }
			else if (Is5KeyTrigger() == TRUE) { g_commandinputstring = CIS_MOVE_SELL; }
			else if (Is6KeyTrigger() == TRUE) 
			{ 
				sprintf_s(commu_state_edit[edit_line].command, 256, "end");
				g_edittype = EDIT_DEFAULT;
			}
			else if (Is7KeyTrigger() == TRUE) { g_commandinputstring = CIS_MOVE_COMMU; }
			else if (Is8KeyTrigger() == TRUE) { g_edittype = EDIT_TEXT_WINDOW; }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE)
			{
				sprintf_s(commu_state_edit[edit_line].command, 256, "");
				commu_state_edit[edit_line].CommandNumberChange(0);	// ついでにコマンド用数値も初期化
				g_edittype = EDIT_DEFAULT;
			}
		}
		// テキストウィンドウ色選択時の処理
		if (g_edittype == EDIT_TEXT_WINDOW)
		{
			if (Is1KeyTrigger() == TRUE) { GameCommuEditTextWindow(1); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditTextWindow(2); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditTextWindow(3); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditTextWindow(4); }
		}
		// 台詞主選択時の処理
		if (g_edittype >= EDIT_LINES_CHARACTER && g_edittype <= EDIT_LINES_CHARACTER2)
		{
			if (Is1KeyTrigger() == TRUE)		{ GameCommuEditLinesCharacter((char*)"主人公"); }
			else if (Is2KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"めぐる"); }
			else if (Is3KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"恋鐘"); }
			else if (Is4KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"樹里"); }
			else if (Is5KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"凛世"); }
			else if (Is6KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"千雪"); }
			else if (Is7KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"はづき"); }
			else if (Is8KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"校長"); }
			else if (Is9KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"一同"); }
			// 台詞主自由入力モードに移行
			else if (Is0KeyTrigger() == TRUE) {	GameCommuEditInputString(16, FALSE,(char*)"");}
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditLinesCharacter((char*)""); }
		}
		// 口パクタイプ選択時の処理
		if (g_edittype == EDIT_LINES_MOUSE)
		{
			if (Is1KeyTrigger() == TRUE) { GameCommuEditLinesMouse(-1); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditLinesMouse(1); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditLinesMouse(2); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditLinesMouse(3); }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditLinesMouse(0); }
		}
		// キャラクター選択時の処理
		if (g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT)
		{
			//int x = g_edittype - EDIT_CHARACTER_LEFT;
			//// HM[j][i].character[x]の1000の位を消して、入力された数×1000を追加する
			//if (g_editcharactertype == EDIT_CHARACTER_BODY)
			//{
			//	if (Is0KeyTrigger() == TRUE)
			//	{ 
			//		commu_state_edit[edit_line].CharacterIDChange(x, -1000);
			//		g_edittype = EDIT_DEFAULT;
			//	}
			//	else if (Is1KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 1); }
			//	else if (Is2KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 2); }
			//	else if (Is3KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 3); }
			//	else if (Is4KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 4); }
			//	else if (Is5KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 5); }
			//	else if (Is6KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 6); }
			//	else if (Is7KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 7); }
			//	else if (CheckHitKey(KEY_INPUT_D) == TRUE) 
			//	{ 
			//		commu_state_edit[edit_line].CharacterIDChange(x, 0);
			//		g_edittype = EDIT_DEFAULT;
			//	}
			//}
			//// ポーズ、衣装、表情用
			//else
			//{
			//	if (Is0KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 0); }
			//	else if (Is1KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 1); }
			//	else if (Is2KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 2); }
			//	else if (Is3KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 3); }
			//	else if (Is4KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 4); }
			//	else if (Is5KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 5); }
			//	else if (Is6KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 6); }
			//	else if (Is7KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 7); }
			//	else if (Is8KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 8); }
			//	else if (Is9KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 9); }
			//}

			// 削除用立ち絵ＩＤを代入する
			if (Is0KeyTrigger() == TRUE)
			{
				commu_state_edit[edit_line].CharacterIDChange(g_edittype - EDIT_CHARACTER_LEFT, -1000);
				g_edittype = EDIT_DEFAULT;
			}
			// 押された数字キーに応じてカーソルが瞬時移動する
			if (Is1KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(1); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(2); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(3); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(4); }
			else if (Is5KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(5); }
			else if (Is6KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(6); }
			else if (Is7KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(7); }
		}
		// 『キャラ変更タイプ』選択時の処理
		if(edit_row == EDIT_CHARACTER_CHANGE_TYPE)
		{
			#pragma region ver0.007制作時コメント化コード
			//if (CheckHitKey(KEY_INPUT_0) == TRUE)
			//{ 
			//	if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
			//	{
			//		for (int i = edit_line; i <= COMMU_LINE_MAX; i++) { commu_state_edit[i].CCCHANGE(0); }
			//	}
			//	else { commu_state_edit[edit_line].CCCHANGE(0); }
			//}
			//else if (CheckHitKey(KEY_INPUT_1) == TRUE)
			//{
			//	if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
			//	{
			//		for(int i = edit_line; i <= COMMU_LINE_MAX; i++){ commu_state_edit[i].CCCHANGE(1); }
			//	}
			//	else{ commu_state_edit[edit_line].CCCHANGE(1); }
			//}
#pragma endregion
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { GameCommuEditCharacterChange(0); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { GameCommuEditCharacterChange(1); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { GameCommuEditCharacterChange(2); }
		}
		// 『特殊表情』選択時の処理
		if(edit_row == EDIT_SELECT_FE_LEFT || edit_row == EDIT_SELECT_FE_CENTER || edit_row == EDIT_SELECT_FE_RIGHT)
		{
			int x = 0;
			switch (edit_row)
			{
			case EDIT_SELECT_FE_CENTER:	x = 1;	break;
			case EDIT_SELECT_FE_RIGHT:	x = 2;	break;
			default:							break;
			}
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, -1); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, 1); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, 2); }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, 0); }
		}
		// 『キャラ間距離均一化』選択時の処理
		if (edit_row == EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM)
		{
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].CDUCHANGE(-1); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].CDUCHANGE(1); }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { commu_state_edit[edit_line].CDUCHANGE(0); }
		}
		// 背景選択時の処理
		if (g_edittype == EDIT_BACKGROUND)
		{
			int x = (edit_row_background - 1) * 10;
			if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditBackground(0); }
			else if (edit_row_background == 0)
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditBackground(-1); }
			}
			else if (Is0KeyTrigger() == TRUE) { GameCommuEditBackground(x + 1); }
			else if (Is1KeyTrigger() == TRUE) { GameCommuEditBackground(x + 2); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditBackground(x + 3); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditBackground(x + 4); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditBackground(x + 5); }
			else if (Is5KeyTrigger() == TRUE) { GameCommuEditBackground(x + 6); }
			else if (Is6KeyTrigger() == TRUE) { GameCommuEditBackground(x + 7); }
			else if (Is7KeyTrigger() == TRUE) { GameCommuEditBackground(x + 8); }
			else if (Is8KeyTrigger() == TRUE) { GameCommuEditBackground(x + 9); }
			else if (Is9KeyTrigger() == TRUE) { GameCommuEditBackground(x + 10); }
		}
		// 『キャラ変更タイプ』選択時の処理
		if (edit_row == EDIT_SELECT_BACKGROUND_CHANGE_TYPE)
		{
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].BackgroundChangeTypeChange(BACKGROUND_CHANGE_VISIBILITY); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].BackgroundChangeTypeChange(BACKGROUND_CHANGE_BLACKOUT); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { commu_state_edit[edit_line].BackgroundChangeTypeChange(BACKGROUND_CHANGE_WHITEOUT); }
		}
		// ＢＧＭ選択時の処理
		if (g_edittype == EDIT_BGM)
		{
			if(CheckHitKey(KEY_INPUT_D) == TRUE){ GameCommuEditBGM(0); }
			else if(edit_row_bgm == 0)
			{ 
				if (Is0KeyTrigger() == TRUE) { GameCommuEditBGM(-1); }
			}
			else
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 1); }
				else if (Is1KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 2); }
				else if (Is2KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 3); }
				else if (Is3KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 4); }
				else if (Is4KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 5); }
				else if (Is5KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 6); }
				else if (Is6KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 7); }
				else if (Is7KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 8); }
				else if (Is8KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 9); }
				else if (Is9KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 10); }
			}
		}
		// 『ＢＧＭ変更タイプ』選択時の処理
		if (edit_row == EDIT_SELECT_BGM_CHANGE_TYPE)
		{
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_FO_P); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_FO_FI); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_S_P); }
			else if (CheckHitKey(KEY_INPUT_3) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_S_FI); }
		}
		// ＳＥ選択時の処理
		if (g_edittype == EDIT_SE)
		{
			if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditSE(0); }
			else if (edit_row_se == 0)
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditSE(-1); }
			}
			else
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 1); }
				else if (Is1KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 2); }
				else if (Is2KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 3); }
				else if (Is3KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 4); }
				else if (Is4KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 5); }
				else if (Is5KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 6); }
				else if (Is6KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 7); }
				else if (Is7KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 8); }
				else if (Is8KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 9); }
				else if (Is9KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 10); }
			}
		}
	}
}
// テキストウィンドウ色変更の際の共通処理
void GameCommuEditTextWindow(int x)	// ウィンドウの色
{
	g_edittype = EDIT_DEFAULT;
	commu_state_edit[edit_line].CommandChange((char*)"text_window_color");
	commu_state_edit[edit_line].CommandNumberChange(x);
}
// 選択肢文字列入力の際の共通処理
void GameCommuEditAlternativeInput(CommandInputStringType x)	// 次に入力する選択肢系文字列
{
	g_commandinputstring = x;
	if (x >= CIS_ALTERNATIVE_JUMP2_1 && x <= CIS_ALTERNATIVE_JUMP3_3) { GameCommuEditInputString(3, TRUE, (char*)""); }
	else { GameCommuEditInputString(33, FALSE, (char*)""); }
	g_edittype = EDIT_COMMAND;
	commu_edit_input_string = TRUE;
}
// 文字入力状態移行の共通処理
void GameCommuEditInputString(int x, BOOL y, char* c)	// 入力できる半角文字数上限,半角数字限定のフラグ,入力開始時文字列
{
	InputHandle = MakeKeyInput(x, TRUE, FALSE, y);		// キー入力ハンドルを作る
	SetKeyInputString(c, InputHandle);					// キー入力ハンドルに指定の文字列をセットする
	SetActiveKeyInput(InputHandle);						// 作成したキー入力ハンドルをアクティブにする
	commu_edit_input_string = TRUE;						// 文字入力モードオン
}
// 行内容全削除の共通処理
void GameCommuEditLineErase(int x)	// 削除行
{
	char c_null[256] = "";
	commu_state_edit[x].CommandChange(c_null);			// コマンド
	commu_state_edit[x].CommandNumberChange(0);			// 各特定コマンド用数値
	commu_state_edit[x].LineCharacterChange(0, c_null);	// 台詞主
	commu_state_edit[x].LineCharacterChange(1, c_null);	// 台詞主２
	commu_state_edit[x].LineChange(c_null);				// 台詞
	commu_state_edit[x].LineMouseChange(0);				// 台詞口パクタイプ
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j <= 4; j++) { commu_state_edit[x].CharacterIDChange(i, j, 0); }	// キャラクター
		commu_state_edit[x].CFECHANGE(i, 0);												// キャラクター特殊表情
	}
	commu_state_edit[x].CCCHANGE(0);												// キャラクター変更タイプ
	commu_state_edit[x].CDUCHANGE(0);												// キャラ間距離均一化
	commu_state_edit[x].BackgroundChange(0);										// 背景
	commu_state_edit[x].BackgroundChangeTypeChange(BACKGROUND_CHANGE_VISIBILITY);	// 背景変更タイプ
	commu_state_edit[x].BGMChange(0);												// ＢＧＭ
	commu_state_edit[x].BCTChange(BGM_CHANGE_FO_P);									// ＢＧＭ変更タイプ
	commu_state_edit[x].SEChange(0);												// ＳＥ
	for (int i = 0; i < 3; i++)
	{
		commu_state_edit[x].AlternativeChange(i, 0);		// 選択肢文字列（第２引数が適当ではない可能性がある）
		commu_state_edit[x].AlternativeJumpChange(i, 0);	// 選択肢ジャンプ先行
	}
}
// 行内容コピーの共通処理
#pragma region ver0.00704制作時コメント化コード
//void GameCommuEditLineCopy(int x, int y)	// コピー先行,コピー元行
#pragma endregion
void GameCommuEditLineCopy(int x, int y, int z)	// コピー先行,コピー元行,特定の条件時に加算される数値
{
	commu_state_edit[x].CommandChange(commu_state_edit[y].GetCommand());						// コマンド
	// 各特定コマンド用数値（『move_cell』を指定されている際は特定の数値が加算される）
	commu_state_edit[x].CommandNumberChange(commu_state_edit[y].GetCommandNumber() + (strcmp(commu_state_edit[y].GetCommand(), "move_sell") == 0 ? z : 0));

	commu_state_edit[x].LineCharacterChange(0, commu_state_edit[y].GetLineCharacterName());		// 台詞主
	commu_state_edit[x].LineCharacterChange(1, commu_state_edit[y].GetLineCharacterName2());	// 台詞主２
	commu_state_edit[x].LineChange(commu_state_edit[y].GetLine());								// 台詞
	commu_state_edit[x].LineMouseChange(commu_state_edit[y].GetLineMouse());					// 台詞口パクタイプ
	for (int i = 0; i < 3; i++)
	{
		commu_state_edit[x].CharacterIDChange(i, commu_state_edit[y].GetCharacter(i));	// キャラクター
		commu_state_edit[x].CFECHANGE(i, commu_state_edit[y].GetCFE(i));				// キャラクター特殊表情
	}
	commu_state_edit[x].CCCHANGE(commu_state_edit[y].GetCC());										// キャラクター変更タイプ
	commu_state_edit[x].CDUCHANGE(commu_state_edit[y].GetCDU());									// キャラ間距離均一化
	commu_state_edit[x].BackgroundChange(commu_state_edit[y].GetBackground());						// 背景
	commu_state_edit[x].BackgroundChangeTypeChange(commu_state_edit[y].GetBackgroundChangeType());	// 背景変更タイプ
	commu_state_edit[x].BGMChange(commu_state_edit[y].GetBGM());									// ＢＧＭ
	commu_state_edit[x].BCTChange(commu_state_edit[y].GetBGMCT());									// ＢＧＭ変更タイプ
	commu_state_edit[x].SEChange(commu_state_edit[y].GetSE());										// ＳＥ
	for (int i = 0; i < 3; i++)
	{
		commu_state_edit[x].AlternativeChange(i, commu_state_edit[y].GetAlternativeString(i));		// 選択肢文字列（第２引数が適当ではない可能性がある）
		// 選択肢ジャンプ先行（コマンドで実際に選択肢が使われる場合、特定の数値が加算される）
		int a = 0;
		if (strcmp(commu_state_edit[y].GetCommand(), "altenative_2") || (strcmp(commu_state_edit[y].GetCommand(), "altenative_3") && i == 2)) { a = z; }
		{commu_state_edit[x].AlternativeJumpChange(i, commu_state_edit[y].GetAlternativeJump(i) + a);}
	}
}
// 口パクタイプ変数代入の共通処理
void GameCommuEditLinesMouse(int x)	// 口パクタイプ用変数
{
	commu_state_edit[edit_line].LineMouseChange(x);
	g_edittype = EDIT_DEFAULT;
}
// 台詞主変数代入処理の際の共通処理
void GameCommuEditLinesCharacter(char* c)	// 文字列
{
	commu_state_edit[edit_line].LineCharacterChange(g_edittype - EDIT_SELECT_LINES_CHARACTER, c);
	g_edittype = EDIT_DEFAULT;
}
// キャラクター用変数代入処理の際の共通処理
void GameCommuEditCharacter(int x, int y, int z) // 変更するキャラクター,変更するID数値の桁の位,変更後の数字
{
	commu_state_edit[edit_line].CharacterIDChange(x, y, z);
	switch (g_editcharactertype)
	{
	case EDIT_CHARACTER_EXPRESSION:	
		g_edittype = EDIT_DEFAULT;
		g_editcharactertype = EDIT_CHARACTER_BODY;
		break;
	case EDIT_CHARACTER_COSTUME:	g_editcharactertype = EDIT_CHARACTER_EXPRESSION;	break;
	case EDIT_CHARACTER_PAUSE:		g_editcharactertype = EDIT_CHARACTER_COSTUME;		break;
	case EDIT_CHARACTER_BODY:		g_editcharactertype = EDIT_CHARACTER_PAUSE;			break;
	default:																			break;
	}
}
// キャラ立ち絵選択時瞬時移動するキャラを検索し移動する際の共通処理
void GameCommuEditCharacterCursorMove(int x)	// 検索するキャラの千の位
{
	// 検索する
	for (int i = 0; i < edit_character_alternative_line_limit; i++)
	{
		for (int j = 0; j < EDIT_CHARACTER_ALTERNATIVE_X_LIMIT; j++)
		{
			// 千の位が一致していたらカーソルを移動させ関数を抜け出す
			if (edit_character_id[i][j] / 1000 == x)
			{
				edit_character_alternative_row = j;
				edit_character_alternative_line = i;
				return;
			}
		}
	}
}
// キャラ変更タイプを変更する際の共通処理
void GameCommuEditCharacterChange(int x)	// キャラ変更タイプＩＤ
{
	if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
	{
		for (int i = edit_line; i <= COMMU_LINE_MAX; i++) { commu_state_edit[i].CCCHANGE(x); }
	}
	else { commu_state_edit[edit_line].CCCHANGE(x); }
}
// 背景変数代入の共通処理
void GameCommuEditBackground(int x)	// 背景
{
	#pragma region ver0.00704制作時コメント化コード
	//if (x <= BACKGROUND_NUMBER)
#pragma endregion
	if (x <= bgimage[0].GetNumber())
	{
		commu_state_edit[edit_line].BackgroundChange(x);
		g_edittype = EDIT_DEFAULT;
	}
}
// ＢＧＭ変数代入の共通処理
void GameCommuEditBGM(int x)	// ＢＧＭ
{
	commu_state_edit[edit_line].BGMChange(x);
	g_edittype = EDIT_DEFAULT;
}
// ＳＥ変数代入の共通処理
void GameCommuEditSE(int x)	// ＳＥ
{
	// 存在するＳＥのＩＤならＳＥを編集してEDIT_DEFAULT状態にする
	#pragma region ver0.00707制作時コメント化コード
	//if (x <= SE_NUMBER)
#pragma endregion
	if (x <= SEData::GetNumber())
	{
		commu_state_edit[edit_line].SEChange(x);
		g_edittype = EDIT_DEFAULT;
		//if(x > 0){ PlaySoundMem(g_sndhandles.SE[x - 1], DX_PLAYTYPE_BACK); }	// 編集したＳＥを鳴らす
		if (x > 0) { se[x - 1].PlayBack(); }	// 編集したＳＥを鳴らす
	}
}
// コミュエディット画面の描画処理（プレイヤー向けにアップロードする際はここの内容を一時消去してビルドする）
void DrawGameCommuEdit()
{
	// キャラ立ち絵選択肢用描画
	if(g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT)
	{
		float b_x = screen_size_x * edit_character_alternative_row / 7.0f - screen_size_x / 10;
		float b_y = screen_size_y / 3.0f;
		// 16：９サイズのキャラ立ち絵と同じサイズだと両隣にぶつかるので横幅を狭くしている
		DrawBoxAA(b_x + screen_size_x * 0.25f, b_y, b_x + (WINDOW_SIZE_X * bairitu) / 3 - screen_size_x * 0.25f, b_y + screen_size_y / 3, GetColor(100, 150, 255), TRUE);

		for (int i = -1; i < 2; i++)
		{
			for(int j = 0; j < EDIT_CHARACTER_ALTERNATIVE_X_LIMIT; j++)
			{
				if (edit_character_id[edit_character_alternative_line + i][j] >= 1000)
				{
					float x = screen_size_x * j / 7.0f - screen_size_x / 10;	// キャラの配置場所によって変わるx座標
					float cy = screen_size_y / 3.0f + i * screen_size_y / 2.5f;	// キャラの配置場所によって変わるy座標
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_body[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10], TRUE);
					int y = 2;	// 目パーツに使う変数（まばたきをし終えるまでのフレーム数が1以上且つ、18（6×3）以下なら、残りフレーム数に5を足した数値を6で割った後、2で割った際の余りを返す、違っていれば2を返す（フレーム数19以上なら開きっぱなし））
					//if (g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE && y == 0) { y = 3; }																																					// 特殊表情が『笑顔閉じ目』なら通常の閉じ目の時に差し替える
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_face[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10][edit_character_id[edit_character_alternative_line + i][j] % 10][y], TRUE);
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_eyebrow[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10][edit_character_id[edit_character_alternative_line + i][j] % 10][2], TRUE);	// 眉毛
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_face[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10][edit_character_id[edit_character_alternative_line + i][j] % 10][8], TRUE);
					DrawFormatStringFToHandle(x + (WINDOW_SIZE_X * bairitu) / 6.1f - bairitu * 30, cy + screen_size_y / 3, GetColor(255, 255, 255), g_font3, "%d", edit_character_id[edit_character_alternative_line + i][j]);
				}
			}
		}
		// ヘルプメッセージ
		char h_c[256] = "";
		sprintf_s(h_c, 256, "十字キー：移動\nEnter：決定\n0：削除（-1000）\n●瞬時移動\n○1：めぐる\n○2：恋鐘\n○3：樹里\n○4：凛世\n○5：千雪\n○6：はづき\n○7：校長\n\nB：キャンセル");
		DrawFormatStringFToHandle(bairitu * 1662, screen_size_y / 4.0f - bairitu * 198, GetColor(255, 255, 255), g_font3, h_c);
	}
	// 背景選択肢用描画（存在しない背景を描画させない）
	else if (g_edittype == EDIT_BACKGROUND)
	{
		const float CURSOR_X = GlobalStaticEdit::GetBackgroundAlternativeRow() * static_cast<float>(screen_size_x) / GlobalStaticEdit::GetBackgroundAlternativeLineNumber();
		//const float CURSOR_Y = GlobalStaticEdit::GetBackgroundAlternativeRow() * screen_size_x / GlobalStaticEdit::GetBackgroundAlternativeLineNumber();
		DrawBoxAA(CURSOR_X, 0, CURSOR_X + screen_size_x / GlobalStaticEdit::GetBackgroundAlternativeLineNumber(), static_cast<float>(screen_size_y) / GlobalStaticEdit::GetBackgroundAlternativeLineNumber(), GetColor(100, 150, 255), TRUE);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				const int B = (i + GlobalStaticEdit::GetBackgroundAlternativeLine()) * 2 + j;
				if (B < bgimage[0].GetNumber())
				{
					const float X = j * screen_size_x / 2.0f;
					const float Y = i * screen_size_y / 2.0f;
					const float Z = bairitu * 30;	// 縮小ピクセル数横
					const float A = Z * 2 * 9 / 16;	// 縮小ピクセル数縦（下方向のみ）
					DrawExtendGraphF(X + Z, Y, X + screen_size_x / 2 - Z, Y + screen_size_y / 2 - A, bgimage[B].GetHandle(), TRUE);
					DrawFormatStringFToHandle(X + Z, Y + screen_size_y / 2 - A, GetColor(255, 255, 255), g_font3, "%d：%s", B + 1, bgimage[B].GetName());
				}
			}
		}
	}

	else
	{
		char c[512];	// 説明文
		// 選択編集内容の文字列を定義させる
		char e_string[256];
		switch (edit_row)
		{
		case EDIT_SELECT_COMMAND:
			sprintf_s(e_string, 256, "コマンド");
			// 選択肢２が選ばれてるなら選択肢２つの内容を
			if (strcmp(commu_state_edit[edit_line].command, "altenative_2") == 0 || strcmp(commu_state_edit[edit_line].command, "altenative_3") == 0) { sprintf_s(e_string, 256, "%s\n選択肢１：\n%s\n移動先の行：%d\n選択肢２：\n%s\n移動先の行：%d\n", e_string, commu_state_edit[edit_line].altenative_message[0], commu_state_edit[edit_line].altenative_jump[0], commu_state_edit[edit_line].altenative_message[1], commu_state_edit[edit_line].altenative_jump[1]); }
			if (strcmp(commu_state_edit[edit_line].command, "altenative_3") == 0) { sprintf_s(e_string, 256, "%s選択肢３：\n%s\n移動先の行：%d\n", e_string, commu_state_edit[edit_line].altenative_message[2], commu_state_edit[edit_line].altenative_jump[2]); }
			break;
		case EDIT_SELECT_LINES_CHARACTER:				sprintf_s(e_string, 256, "台詞主");						break;
		case EDIT_SELECT_LINES_CHARACTER2:				sprintf_s(e_string, 256, "台詞主・２");					break;
		case EDIT_SELECT_LINES:							sprintf_s(e_string, 256, "台詞");						break;
		case EDIT_SELECT_LINES_MOUSE:					sprintf_s(e_string, 256, "台詞口パクタイプ");			break;
		case EDIT_SELECT_CHARACTER_LEFT:				sprintf_s(e_string, 256, "左キャラクター");				break;
		case EDIT_SELECT_FE_LEFT:						sprintf_s(e_string, 256, "左キャラクター特殊表情");		break;
		case EDIT_SELECT_CHARACTER_CENTER:				sprintf_s(e_string, 256, "中央キャラクター");			break;
		case EDIT_SELECT_FE_CENTER:						sprintf_s(e_string, 256, "中央キャラクター特殊表情");	break;
		case EDIT_SELECT_CHARACTER_RIGHT:				sprintf_s(e_string, 256, "右キャラクター");				break;
		case EDIT_SELECT_FE_RIGHT:						sprintf_s(e_string, 256, "右キャラクター特殊表情");		break;
		case EDIT_CHARACTER_CHANGE_TYPE:				sprintf_s(e_string, 256, "キャラクター変更タイプ");		break;
		case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(e_string, 256, "キャラ間距離均一化");			break;
		case EDIT_SELECT_BACKGROUND:					sprintf_s(e_string, 256, "背景");						break;
		case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(e_string, 256, "背景変更タイプ");				break;
		case EDIT_SELECT_BGM:							sprintf_s(e_string, 256, "ＢＧＭ");						break;
		case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(e_string, 256, "ＢＧＭ変更タイプ");			break;
		case EDIT_SELECT_SE:							sprintf_s(e_string, 256, "ＳＥ");						break;
		default:										sprintf_s(e_string, 256, "（未設定の項目）");			break;
		}
		// 状態に応じて説明文を変更する
		char c_x[10][256] = { "", "", "" , "" , "" , "" , "" , "" , "" , "" };	// エラーが起きそうなので初期値代入
		switch (g_edittype)
		{
		case EDIT_DEFAULT:
			char c_line_control[256];
			sprintf_s(c_line_control, 256, "B：タイトルへ戻る\nI：空白行挿入\nC+E or Ctrl+E：編集行コピー挿入\nD+L or Ctrl+L：行削除");
			// 編集行移動についての説明文
			char c_line_move[256];
			sprintf_s(c_line_move, 256, "編集行：%d\nCtrl＋左右キー：左右端へ移動\n\n(↑↓キー：移動\nShiftキー押しながら：移動量100倍、ctrlキー押しながら：移動量10倍)", edit_line);

			switch (edit_row)
			{
			case EDIT_SELECT_LINES:							sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\nD：台詞を削除\nEnter：台詞を編集\n%s", e_string, c_line_move, c_line_control);									break;
			case EDIT_SELECT_CHARACTER_LEFT:
			case EDIT_SELECT_CHARACTER_CENTER:
			case EDIT_SELECT_CHARACTER_RIGHT:
				sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\nEnter：立ち絵編集\nD：削除\n%s", e_string, c_line_move, c_line_control);
				break;
			case EDIT_SELECT_FE_LEFT:
			case EDIT_SELECT_FE_CENTER:
			case EDIT_SELECT_FE_RIGHT:
				sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\nD：削除\n0：通常に戻す\n1：閉じ目\n2：笑顔閉じ目\n%s", e_string, c_line_move, c_line_control);
				break;
			case EDIT_CHARACTER_CHANGE_TYPE:				sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\n\nShiftを押しながら：この行から最終行まで\n0：削除\n1：瞬時表示・入れ替え\n2：透明度高速入れ替え\n\n%s", e_string, c_line_move, c_line_control);								break;
			case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\nD：削除\n0：オフ\n1：オン\n%s", e_string, c_line_move, c_line_control);									break;
			case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\n0：不透明度入れ替え\n1：ブラックアウト\n2：ホワイトアウト\n%s", e_string, c_line_move, c_line_control);	break;
				//case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c, 256, "編集内容候補（←→キー）：%s\n編集行（↑↓キー）：%d\n0：ＦＯ→Ｐ\n1：ＦＯ→ＦＩ\n2：Ｓ→Ｐ\n3：Ｓ→ＦＩ\n※\nＦＯ（fade out）：60フレームかけて音量が小さくなり停止します\nＳ（stop）：10フレームかけて音量が小さくなり停止します\n○Ｐ(play)：即再生します\nＦＩ(fade in)：再生し、240フレームかけて設定音量になります\n\nB：タイトルへ戻る", e_string, edit_line);	break;
			case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\n0：ＦＯ→Ｐ\n1：ＦＯ→ＦＩ\n2：Ｓ→Ｐ\n3：Ｓ→ＦＩ\n%s", e_string, c_line_move, c_line_control);			break;
			default:										sprintf_s(c, 512, "編集内容候補（←→キー）：%s\n%s\nEnter：指定コマンドを編集\n%s", e_string, c_line_move, c_line_control);									break;
			}
			break;
		case EDIT_COMMAND:
			switch (g_commandinputstring)
			{
			case CIS_NULL:
				sprintf_s(c, 256, "1：ＳＥ終了で次行処理\n2：指定フレーム数後次行処理\n3：２択選択肢\n4：３択選択肢\n5：指定行へジャンプ\n6：コミュ終了\n7：指定ＩＤコミュへ移動\n8：テキストウィンドウ色変更\nB：キャンセル\nD：削除");
				break;
			case CIS_FRAME_AUTO:
			case CIS_MOVE_SELL:
			case CIS_MOVE_COMMU:
				sprintf_s(c, 256, "数値を入力\nEsc：キャンセル\nEnter：決定");
				break;
			case CIS_ALTERNATIVE2_1:
			case CIS_ALTERNATIVE3_1:
				sprintf_s(c, 256, "選択肢１を入力\nEsc：キャンセル\nEnter：決定");
				break;
			case CIS_ALTERNATIVE2_2:
			case CIS_ALTERNATIVE3_2:
				sprintf_s(c, 256, "選択肢２を入力\nEsc：キャンセル\nEnter：決定");
				break;
			case CIS_ALTERNATIVE3_3:
				sprintf_s(c, 256, "選択肢３を入力\nEsc：キャンセル\nEnter：決定");
				break;
			case CIS_ALTERNATIVE_JUMP2_1:
			case CIS_ALTERNATIVE_JUMP3_1:
				sprintf_s(c, 256, "選択肢１決定時ジャンプ先行を入力\nEsc：キャンセル\nEnter：決定");
				break;
			case CIS_ALTERNATIVE_JUMP2_2:
			case CIS_ALTERNATIVE_JUMP3_2:
				sprintf_s(c, 256, "選択肢２決定時ジャンプ先行を入力\nEsc：キャンセル\nEnter：決定");
				break;
			case CIS_ALTERNATIVE_JUMP3_3:
				sprintf_s(c, 256, "選択肢３決定時ジャンプ先行を入力\nEsc：キャンセル\nEnter：決定");
				break;
			default:
				sprintf_s(c, 256, "1：ＳＥ終了で次行処理\n2：指定フレーム数後次行処理\n3：２択選択肢\n4：３択選択肢\n5：指定行へジャンプ\n6：コミュ終了\n7：指定ＩＤコミュへ移動\n8：テキストウィンドウ色変更\nB：キャンセル\nD：削除");
				break;
			}
			break;
		case EDIT_TEXT_WINDOW:		sprintf_s(c, 256, "1：灰\n2：水\n3：桃\n4：緑\nB：キャンセル");																														break;
		case EDIT_LINES_CHARACTER:
		case EDIT_LINES_CHARACTER2:
			if (commu_edit_input_string == FALSE) { sprintf_s(c, 256, "1：主人公\n2：めぐる\n3：恋鐘\n4：樹里\n5：凛世\n6：千雪\n7：はづき\n8：校長\n9：一同\n0：自由入力\nB：キャンセル\nD：削除"); }
			else { sprintf_s(c, 256, "Enter：入力名を決定\nEsc：キャンセル："); }
			break;
		case EDIT_LINES:		sprintf_s(c, 256, "Enter：入力台詞を決定\nEsc：キャンセル：");												break;
		case EDIT_LINES_MOUSE:	sprintf_s(c, 256, "1：開かない\n2：台詞が終わるまで開く\n3：開きっぱなし\n4：全員喋らせる\nB：キャンセル\nD：通常に戻す");	break;
		case EDIT_CHARACTER_LEFT:
		case EDIT_CHARACTER_CENTER:
		case EDIT_CHARACTER_RIGHT:
			char c_character[256];	// キャラＩＤ選択時の共通メッセージ
			sprintf_s(c_character, 256, "B：キャンセル\nD：削除");
			switch (g_editcharactertype)
			{
			case EDIT_CHARACTER_EXPRESSION:	sprintf_s(c, 256, "0～9：指定表情を決定\n%s", c_character);													break;
			case EDIT_CHARACTER_COSTUME:	sprintf_s(c, 256, "0～9：指定衣装を決定\n%s", c_character);													break;
			case EDIT_CHARACTER_PAUSE:		sprintf_s(c, 256, "0～9：指定ポーズを決定\n%s", c_character);												break;
			case EDIT_CHARACTER_BODY:		sprintf_s(c, 256, "0：出現キャラを消す\n1：めぐる\n2：恋鐘\n3：樹里\n4：凛世\n5：千雪\n6：はづき\n7：校長\n%s", c_character);	break;
			default:																																	break;
			}
			break;
		case EDIT_BACKGROUND:
			#pragma region ver0.00704制作時コメント化コード
			//if (edit_row_background == 0) { sprintf_s(c, 256, "ページ1/%d\n←→キー：ページ切り替え\n0：背景を削除\nB：キャンセル\nD：削除", (BACKGROUND_NUMBER - 1) / 10 + 2); }
#pragma endregion
			if (edit_row_background == 0) { sprintf_s(c, 256, "ページ1/%d\n←→キー：ページ切り替え\n0：背景を削除\nB：キャンセル\nD：削除", (bgimage[0].GetNumber() - 1) / 10 + 2); }
			else
			{
				int x = (edit_row_background - 1) * 10;
				// 40番目の背景名は存在しないが、不具合を確認できず、プレイヤーが使うモードでもないので放置中
				#pragma region ver0.00704制作時コメント化コード
				//sprintf_s(c, 256, "ページ%d/%d\n←→キー：ページ切り替え\n0：%s\n1：%s\n2：%s\n3：%s\n4：%s\n5：%s\n6：%s\n7：%s\n8：%s\n9：%s\nB：キャンセル\nD：削除", edit_row_background + 1, (BACKGROUND_NUMBER - 1) / 10 + 2, bgimage[x + 0].GetName(), bgimage[x + 1].GetName(), bgimage[x + 2].GetName(), bgimage[x + 3].GetName(), bgimage[x + 4].GetName(), bgimage[x + 5].GetName(), bgimage[x + 6].GetName(), bgimage[x + 7].GetName(), bgimage[x + 8].GetName(), bgimage[x + 9].GetName());
#pragma endregion
				//sprintf_s(c, 256, "ページ%d/%d\n←→キー：ページ切り替え\n0：%s\n1：%s\n2：%s\n3：%s\n4：%s\n5：%s\n6：%s\n7：%s\n8：%s\n9：%s\nB：キャンセル\nD：削除", edit_row_background + 1, (bgimage[0].GetNumber() - 1) / 10 + 2, bgimage[x + 0].GetName(), bgimage[x + 1].GetName(), bgimage[x + 2].GetName(), bgimage[x + 3].GetName(), bgimage[x + 4].GetName(), bgimage[x + 5].GetName(), bgimage[x + 6].GetName(), bgimage[x + 7].GetName(), bgimage[x + 8].GetName(), bgimage[x + 9].GetName());
				sprintf_s(c, 512, "ページ%d/%d\n←→キー：ページ切り替え\n0：%s\n1：%s\n2：%s\n3：%s\n4：%s\n5：%s\n6：%s\n7：%s\n8：%s\n9：%s\nB：キャンセル\nD：削除", edit_row_background + 1, (bgimage[0].GetNumber() - 1) / 10 + 2, bgimage[x + 0].GetName(), bgimage[x + 1].GetName(), bgimage[x + 2].GetName(), bgimage[x + 3].GetName(), bgimage[x + 4].GetName(), bgimage[x + 5].GetName(), bgimage[x + 6].GetName(), bgimage[x + 7].GetName(), bgimage[x + 8].GetName(), bgimage[x + 9].GetName());
			}
			break;
		case EDIT_BGM:
			// 10個の変数を代入
			for (int i = 0; i < 10; i++)
			{
				int x = (edit_row_bgm - 1) * 10 + i;	// 比較用
				if (x >= 0 && x < BGM_NUMBER) { sprintf_s(c_x[i], 256, "%s", music_string[(edit_row_bgm - 1) * 10 + i].name); }
			}
			if (edit_row_bgm == 0) { sprintf_s(c, 256, "ページ1/4\n←→キー：ページ切り替え\n0：ＢＧＭ停止"); }
			else { sprintf_s(c, 256, "ページ%d/%d\n←→キー：ページ切り替え\n0：%s\n1：%s\n2：%s\n3：%s\n4：%s\n5：%s\n6：%s\n7：%s\n8：%s\n9：%s\nB：キャンセル\nD：削除\n", edit_row_bgm + 1, (BGMData::GetNumber() - 1) / 10 + 2, c_x[0], c_x[1], c_x[2], c_x[3], c_x[4], c_x[5], c_x[6], c_x[7], c_x[8], c_x[9]); }
			break;
		case EDIT_SE:
			// 10個の変数を代入
			for (int i = 0; i < 10; i++)
			{
				int x = (edit_row_se - 1) * 10 + i;	// 比較用
				#pragma region ver0.00707制作時コメント化コード
				//if (x >= 0 && x < SE_NUMBER) { sprintf_s(c_x[i], 256, se[(edit_row_se - 1) * 10 + i].GetName()); }
#pragma endregion
				if (x >= 0 && x < SEData::GetNumber()) { sprintf_s(c_x[i], 256, se[(edit_row_se - 1) * 10 + i].GetName()); }
			}
			// 文字列と文字列をくっつける
			#pragma region ver0.00707制作時コメント化コード
			//if (edit_row_se == 0) { sprintf_s(c, 256, "ページ1/%d\n←→キー：ページ切り替え\n0：SE停止", SE_NUMBER / 10 + 2); }
			//else { sprintf_s(c, 256, "ページ%d/%d\n←→キー：ページ切り替え\n0：%s\n1：%s\n2：%s\n3：%s\n4：%s\n5：%s\n6：%s\n7：%s\n8：%s\n9：%s\nB：キャンセル\nD：削除\n", edit_row_se + 1, SE_NUMBER / 10 + 2, c_x[0], c_x[1], c_x[2], c_x[3], c_x[4], c_x[5], c_x[6], c_x[7], c_x[8], c_x[9]); }
#pragma endregion
			if (edit_row_se == 0) { sprintf_s(c, 256, "ページ1/%d\n←→キー：ページ切り替え\n0：SE停止", SEData::GetNumber() / 10 + 2); }
			else { sprintf_s(c, 256, "ページ%d/%d\n←→キー：ページ切り替え\n0：%s\n1：%s\n2：%s\n3：%s\n4：%s\n5：%s\n6：%s\n7：%s\n8：%s\n9：%s\nB：キャンセル\nD：削除\n", edit_row_se + 1, SEData::GetNumber() / 10 + 2, c_x[0], c_x[1], c_x[2], c_x[3], c_x[4], c_x[5], c_x[6], c_x[7], c_x[8], c_x[9]); }
			break;
		default:	sprintf_s(c, 256, "（未設定の項目）\n%s", c_character);																				break;
		}
		DrawFormatStringFToHandle(screen_size_x / 2.0f, screen_size_y / 4.0f - bairitu * 198, GetColor(255, 255, 255), g_font3, c);
		// サムネ代わりの文---------
		int samune_character[] = { GetEditSamuneNumber(ESS_CHARACTER_LEFT), GetEditSamuneNumber(ESS_CHARACTER_CENTER), GetEditSamuneNumber(ESS_CHARACTER_RIGHT) };
		int samune_distance = GetEditSamuneNumber(ESS_CHARACTER_DISTANCE);
		int samune_background = GetEditSamuneNumber(ESS_BACKGROUND);
		int samune_bgm = GetEditSamuneNumber(ESS_BGM);
		DrawFormatStringFToHandle(0.0f, screen_size_y / 2.0f, GetColor(255, 255, 255), g_font3,
			//"編集行：%d\n台詞――%s：%s\n/*キャラクター左：%s\nキャラクター中：%s\nキャラクター右：%s\n*/背景：%s\nＢＧＭ：%s\nＳＥ：%s",
			"編集行：%d\n台詞――%s%s%s\nキャラ均一：%s\nＢＧＭ：%s\nＳＥ：%s",
			edit_line,
			commu_state_edit[edit_line].GetLineCharacterName(),
			commu_state_edit[edit_line].GetLineCharacterName() != "" ? "" : "：",
			commu_state_edit[edit_line].GetLine(),
			samune_distance == 0 ? "オフ" : (commu_state_edit[samune_distance].GetCDU() < 1 ? "オフ" : "オン"),
			samune_bgm == 0 ? "" : music_string[commu_state_edit[samune_bgm].GetBGM() - 1].GetName(),
			GetSEString(commu_state_edit[edit_line].GetSE())
		);
		// -------------------------
		// サムネ画像
		//if(commu_state_edit[samune_background].GetBackground() - 1 >= 0)DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.background[commu_state_edit[samune_background].GetBackground() - 1], TRUE);	// 背景
		if (commu_state_edit[samune_background].GetBackground() - 1 >= 0) { bgimage[commu_state_edit[samune_background].GetBackground() - 1].DrawImageSamune(); }	// 背景

		// キャラクター
		for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
		{
			if (samune_character[i] > 0)
			{
				float x = (i * COMMU_CHARACTER_SPACE - COMMU_CHARACTER_SPACE) * bairitu;	// キャラの配置場所によって変わるx座標
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_body[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10], TRUE);
				int y = 2;	// 目パーツに使う変数（まばたきをし終えるまでのフレーム数が1以上且つ、18（6×3）以下なら、残りフレーム数に5を足した数値を6で割った後、2で割った際の余りを返す、違っていれば2を返す（フレーム数19以上なら開きっぱなし））
				//if (g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE && y == 0) { y = 3; }																																					// 特殊表情が『笑顔閉じ目』なら通常の閉じ目の時に差し替える
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_face[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) % 10][y], TRUE);
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_eyebrow[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) % 10][2], TRUE);	// 眉毛
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_face[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) % 10][8], TRUE);
			}
		}

		// 真ん中の行を四角で囲む
		DrawBoxAA(0, bairitu * 855, screen_size_x * 1.0f, bairitu * 930, GetColor(100, 150, 255), TRUE);
		// 編集行とその±１行の内容
		for (int i = -1; i < 2; i++)
		{
			char c_mouse[256];	// 口パクタイプ用変数
			switch (commu_state_edit[edit_line + i].line_mouse)
			{
			case -1:	sprintf_s(c_mouse, 256, "開かない");				break;
			case 0:		sprintf_s(c_mouse, 256, "通常");					break;
			case 1:		sprintf_s(c_mouse, 256, "台詞が終わるまで開く");	break;
			case 2:		sprintf_s(c_mouse, 256, "開きっぱなし");			break;
			case 3:		sprintf_s(c_mouse, 256, "全員喋らせる");			break;
			default:														break;
			}
			char c_face_etc[3][256];	// 特殊表情文字列用変数
			for (int j = 0; j < 3; j++)
			{
				switch (commu_state_edit[edit_line + i].GetCFE(j))
				{
				case -1:	sprintf_s(c_face_etc[j], 256, "通常に戻す");	break;
				case 0:		sprintf_s(c_face_etc[j], 256, "");				break;
				case 1:		sprintf_s(c_face_etc[j], 256, "閉じ目");		break;
				case 2:		sprintf_s(c_face_etc[j], 256, "笑顔閉じ目");	break;
				default:	sprintf_s(c_face_etc[j], 256, "");				break;
				}
			}
			char c_cdu[256];	// キャラクター距離均一化用変数
			switch (commu_state_edit[edit_line + i].GetCDU())
			{
			case -1:	sprintf_s(c_cdu, 256, "オフ");	break;
			case 1:		sprintf_s(c_cdu, 256, "オン");	break;
			default:	sprintf_s(c_cdu, 256, "");		break;
			}
			char c_bct[256];	// 背景変更タイプ用変数
			switch (commu_state_edit[edit_line + i].GetBackgroundChangeType())
			{
			case BACKGROUND_CHANGE_BLACKOUT:	sprintf_s(c_bct, 256, "ブラックアウト");	break;
			case BACKGROUND_CHANGE_WHITEOUT:	sprintf_s(c_bct, 256, "ホワイトアウト");	break;
			default:							sprintf_s(c_bct, 256, "不透明度入れ替え");	break;
			}
			char c_bgmct[256];	// 背景変更タイプ用変数
			switch (commu_state_edit[edit_line + i].GetBGMCT())
			{
			case BGM_CHANGE_FO_FI:	sprintf_s(c_bgmct, 256, "ＦＯ→ＦＩ");	break;
			case BGM_CHANGE_S_P:	sprintf_s(c_bgmct, 256, "Ｓ→Ｐ");		break;
			case BGM_CHANGE_S_FI:	sprintf_s(c_bgmct, 256, "Ｓ→ＦＩ");	break;
			default:				sprintf_s(c_bgmct, 256, "ＦＯ→Ｐ");	break;
			}
			int row_x = 570;	// 各列の固定間隔
			if (edit_line + i >= 2 && edit_line + i <= COMMU_LINE_MAX)
			{
				DrawFormatStringFToHandle(bairitu * 99, screen_size_y + i * bairitu * 99 - bairitu * 198, GetColor(255, 255, 255), g_font3, "%d：",
					//		%16s・%d・%s%s%s%s%64s：%d：%d：%d", 
					edit_line + i
					//		//commu_state_edit[edit_line + i].command == "" ? "　　　" : commu_state_edit[edit_line + i].command,
					//		commu_state_edit[edit_line + i].command,
					//		commu_state_edit[edit_line + i].move_commu_number,
					//		commu_state_edit[edit_line + i].name,
					//		strcmp(commu_state_edit[edit_line + i].name, "") != 0 && strcmp(commu_state_edit[edit_line + i].name2, "") != 0 ? "・" : "",
					//		commu_state_edit[edit_line + i].name2,
					//		c_mouse,
					//		commu_state_edit[edit_line + i].line,
					//		commu_state_edit[edit_line + i].character[0],
					//		commu_state_edit[edit_line + i].character[1],
					//		commu_state_edit[edit_line + i].character[2]
				);
				// 現在指定中のedit_rowに応じて表示するものを変える
				for (int j = -1; j < 2; j++)
				{
					if (edit_row + j >= EDIT_SELECT_COMMAND && edit_row + j <= EDIT_SELECT_PAGE_MAX)
					{
						char c_edit[256];
						switch (edit_row + j)
						{
						case EDIT_SELECT_COMMAND:						sprintf_s(c_edit, 256, "%s：%d", commu_state_edit[edit_line + i].command, commu_state_edit[edit_line + i].move_commu_number);	break;
						case EDIT_SELECT_LINES_CHARACTER:				sprintf_s(c_edit, 256, "%s", commu_state_edit[edit_line + i].name);																break;
						case EDIT_SELECT_LINES_CHARACTER2:				sprintf_s(c_edit, 256, "%s", commu_state_edit[edit_line + i].name2);															break;
						case EDIT_SELECT_LINES:							sprintf_s(c_edit, 256, "%s", commu_state_edit[edit_line + i].line);																break;
						case EDIT_SELECT_LINES_MOUSE:					sprintf_s(c_edit, 256, c_mouse);																								break;
						case EDIT_SELECT_CHARACTER_LEFT:				sprintf_s(c_edit, 256, "%d", commu_state_edit[edit_line + i].character[0]);														break;
						case EDIT_SELECT_FE_LEFT:						sprintf_s(c_edit, 256, c_face_etc[0]);																							break;
						case EDIT_SELECT_CHARACTER_CENTER:				sprintf_s(c_edit, 256, "%d", commu_state_edit[edit_line + i].character[1]);														break;
						case EDIT_SELECT_FE_CENTER:						sprintf_s(c_edit, 256, c_face_etc[1]);																							break;
						case EDIT_SELECT_CHARACTER_RIGHT:				sprintf_s(c_edit, 256, "%d", commu_state_edit[edit_line + i].character[2]);														break;
						case EDIT_SELECT_FE_RIGHT:						sprintf_s(c_edit, 256, c_face_etc[2]);																							break;
						case EDIT_CHARACTER_CHANGE_TYPE:
							if (commu_state_edit[edit_line + i].GetCC() == CCC_INSTANT) { sprintf_s(c_edit, 256, "瞬時表示・入れ替え"); }
							else if(commu_state_edit[edit_line + i].GetCC() == CCC_TRANSPARENCY_FAST){sprintf_s(c_edit, 256, "透明度高速入れ替え");}
							else { sprintf_s(c_edit, 256, ""); }
							break;
						case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(c_edit, 256, c_cdu);																									break;
						case EDIT_SELECT_BACKGROUND:
							if (commu_state_edit[edit_line + i].GetBackground() == -1) { sprintf_s(c_edit, 256, "背景を削除"); }
							else if (commu_state_edit[edit_line + i].GetBackground() > 0) { sprintf_s(c_edit, 256, bgimage[commu_state_edit[edit_line + i].GetBackground() - 1].GetName()); }
							else { sprintf_s(c_edit, 256, ""); }
							break;
						case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(c_edit, 256, c_bct);																									break;
						case EDIT_SELECT_BGM:
							if (commu_state_edit[edit_line + i].bgm == -1) { sprintf_s(c_edit, 256, music_string_stop.name); }
							else if (commu_state_edit[edit_line + i].bgm > 0) { sprintf_s(c_edit, 256, music_string[commu_state_edit[edit_line + i].bgm - 1].name); }
							else { sprintf_s(c_edit, 256, ""); }
							break;
						case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c_edit, 256, c_bgmct);																								break;
							//case EDIT_SELECT_SE:
							//	if (commu_state_edit[edit_line + i].se == -1) { sprintf_s(c_edit, 256, se_string[0].name); }
							//	else if (commu_state_edit[edit_line + i].se > 0) { sprintf_s(c_edit, 256, se_string[commu_state_edit[edit_line + i].se - 0].name); }
							//	else { sprintf_s(c_edit, 256, ""); }
							//	break;
						case EDIT_SELECT_SE:	sprintf_s(c_edit, 256, "%s", GetSEString(commu_state_edit[edit_line + i].se));																				break;
						default:																																										break;
						}
						DrawFormatStringFToHandle(bairitu * (750 + j * row_x), screen_size_y + i * bairitu * 99 - bairitu * 198, GetColor(255, 255, 255), g_font3, "%s", c_edit);
					}
				}
			}
			if (i == -1)
			{
				for (int j = -1; j < 2; j++)
				{
					if (edit_row + j >= EDIT_SELECT_COMMAND && edit_row + j <= EDIT_SELECT_PAGE_MAX)
					{
						char c_edit_title[256];
						switch (edit_row + j)
						{
						case EDIT_SELECT_COMMAND:						sprintf_s(c_edit_title, 256, "コマンド：コマンド関係数値");	break;
						case EDIT_SELECT_LINES_CHARACTER:				sprintf_s(c_edit_title, 256, "台詞主");						break;
						case EDIT_SELECT_LINES_CHARACTER2:				sprintf_s(c_edit_title, 256, "台詞主２");					break;
						case EDIT_SELECT_LINES:							sprintf_s(c_edit_title, 256, "台詞");						break;
						case EDIT_SELECT_LINES_MOUSE:					sprintf_s(c_edit_title, 256, "台詞口パクタイプ");			break;
						case EDIT_SELECT_CHARACTER_LEFT:				sprintf_s(c_edit_title, 256, "キャラクター左");				break;
						case EDIT_SELECT_FE_LEFT:						sprintf_s(c_edit_title, 256, "キャラクター左特殊表情");		break;
						case EDIT_SELECT_CHARACTER_CENTER:				sprintf_s(c_edit_title, 256, "キャラクター中央");			break;
						case EDIT_SELECT_FE_CENTER:						sprintf_s(c_edit_title, 256, "キャラクター中央特殊表情");	break;
						case EDIT_SELECT_CHARACTER_RIGHT:				sprintf_s(c_edit_title, 256, "キャラクター右");				break;
						case EDIT_SELECT_FE_RIGHT:						sprintf_s(c_edit_title, 256, "キャラクター右特殊表情");		break;
						case EDIT_CHARACTER_CHANGE_TYPE:				sprintf_s(c_edit_title, 256, "キャラクター変更タイプ");		break;
						case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(c_edit_title, 256, "キャラ間距離均一化");			break;
						case EDIT_SELECT_BACKGROUND:					sprintf_s(c_edit_title, 256, "背景");						break;
						case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(c_edit_title, 256, "背景変更タイプ");				break;
						case EDIT_SELECT_BGM:							sprintf_s(c_edit_title, 256, "ＢＧＭ");						break;
						case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c_edit_title, 256, "ＢＧＭ変更タイプ");			break;
						case EDIT_SELECT_SE:							sprintf_s(c_edit_title, 256, "ＳＥ");						break;
						default:										sprintf_s(c_edit_title, 256, "（未設定の項目）");			break;
							break;
						}
						DrawFormatStringFToHandle(bairitu * (750 + j * row_x), screen_size_y + i * bairitu * 99 - bairitu * 297, GetColor(255, 255, 255), g_font3, "%s", c_edit_title);
					}
				}
			}
		}
		// 入力途中の文字列を描画
		DrawKeyInputString(screen_size_x / 2, (int)(bairitu * 345), InputHandle);
	}
}
// seの引数から文字列を取得する
char* GetSEString(int x)	// seの変数
{
	sprintf_s(c_global_function, 256, "");
	if (x == -1) { sprintf_s(c_global_function, 256, "SE停止"); }
	else if (x > 0) { sprintf_s(c_global_function, 256, se[x - 1].GetName()); }
	return c_global_function;
}
#pragma region キートリガー処理
// キーボードBキー
BOOL IsINPUTBKeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_B) == TRUE)
	{
		if (g_inputbkey_prev == FALSE)
		{
			g_inputbkey_prev = TRUE;
			return TRUE;
		}
	}
	else { g_inputbkey_prev = FALSE; }
	return FALSE;
}
// 1キー
BOOL Is1KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_1) == TRUE)
	{
		if (g_1key_prev == FALSE)
		{
			g_1key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_1key_prev = FALSE; }
	return FALSE;
}
// 2キー
BOOL Is2KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_2) == TRUE)
	{
		if (g_2key_prev == FALSE)
		{
			g_2key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_2key_prev = FALSE; }
	return FALSE;
}
// 3キー
BOOL Is3KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_3) == TRUE)
	{
		if (g_3key_prev == FALSE)
		{
			g_3key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_3key_prev = FALSE; }
	return FALSE;
}
// 4キー
BOOL Is4KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_4) == TRUE)
	{
		if (g_4key_prev == FALSE)
		{
			g_4key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_4key_prev = FALSE; }
	return FALSE;
}
// 5キー
BOOL Is5KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_5) == TRUE)
	{
		if (g_5key_prev == FALSE)
		{
			g_5key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_5key_prev = FALSE; }
	return FALSE;
}
// 6キー
BOOL Is6KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_6) == TRUE)
	{
		if (g_6key_prev == FALSE)
		{
			g_6key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_6key_prev = FALSE; }
	return FALSE;
}
// 1キー
BOOL Is7KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_7) == TRUE)
	{
		if (g_7key_prev == FALSE)
		{
			g_7key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_7key_prev = FALSE; }
	return FALSE;
}
// 8キー
BOOL Is8KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_8) == TRUE)
	{
		if (g_8key_prev == FALSE)
		{
			g_8key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_8key_prev = FALSE; }
	return FALSE;
}
// 9キー
BOOL Is9KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_9) == TRUE)
	{
		if (g_9key_prev == FALSE)
		{
			g_9key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_9key_prev = FALSE; }
	return FALSE;
}
// 0キー
BOOL Is0KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_0) == TRUE)
	{
		if (g_0key_prev == FALSE)
		{
			g_0key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_0key_prev = FALSE; }
	return FALSE;
}
// 挿入操作
BOOL IsInsertTrigger()
{
	if (CheckHitKey(KEY_INPUT_I) == TRUE)
	{
		if (edit_insert_prev == FALSE)
		{
			edit_insert_prev = TRUE;
			return TRUE;
		}
	}
	else { edit_insert_prev = FALSE; }
	return FALSE;
}
// コピペ操作
BOOL IsCopyPasteTrigger()
{
	BOOL input_control = (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) ? TRUE : FALSE;
	if ((CheckHitKey(KEY_INPUT_C) == TRUE || input_control == TRUE) && CheckHitKey(KEY_INPUT_E) == TRUE)
	{
		if (edit_copy_paste_prev == FALSE)
		{
			edit_copy_paste_prev = TRUE;
			return TRUE;
		}
	}
	else { edit_copy_paste_prev = FALSE; }
	return FALSE;
}
// 行削除操作
BOOL IsDeleteTrigger()
{
	BOOL input_control = (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) ? TRUE : FALSE;
	if ((CheckHitKey(KEY_INPUT_D) == TRUE || input_control == TRUE) && CheckHitKey(KEY_INPUT_L) == TRUE)
	{
		if (edit_delete_prev == FALSE)
		{
			edit_delete_prev = TRUE;
			return TRUE;
		}
	}
	else { edit_delete_prev = FALSE; }
	return FALSE;
}
// 遡って検索するタイプのサムネ文の要素に関わる数値を探す際の共通処理
int GetEditSamuneNumber(EditSamuneSearchType x)	// 数値のアドレス,検索するサムネ用数値の種類
{
	int y = 0;
	// 数値を探す
	if (x == ESS_CHARACTER_DISTANCE)
	{
		for (int i = edit_line; i >= 2; i--)
		{
			y = commu_state_edit[i].GetCDU();
			if (y > 0 || y < 0) { return i; }
		}
	}
	for (int i = edit_line; i >= 2; i--)
	{
		// 比較用数値の定義
		switch (x)
		{
		case ESS_CHARACTER_LEFT:	y = commu_state_edit[i].GetCharacter(0);	break;
		case ESS_CHARACTER_CENTER:	y = commu_state_edit[i].GetCharacter(1);	break;
		case ESS_CHARACTER_RIGHT:	y = commu_state_edit[i].GetCharacter(2);	break;
		case ESS_BACKGROUND:		y = commu_state_edit[i].GetBackground();	break;
		case ESS_BGM:
			y = commu_state_edit[i].GetBGM();
			if (edit_play_bgm != y && y != 0)
			{
				if (y < 0) 
				{
					edit_play_bgm = -1;
					MusicPlay(-1);
				}
				else
				{
					edit_play_bgm = y;
					MusicPlay(y - 1);
				}
			}
			break;
		default:																break;
		}
		if (y > 0){return i;}
		else if (y < 0) { return 0; }
	}
	// 曲が見つからなかった場合、現在のＢＧＭを停止させる
	if(x == ESS_BGM)
	{
		edit_play_bgm = 0;
		MusicPlay(-1);
	}	
	return 0;
}

#pragma endregion

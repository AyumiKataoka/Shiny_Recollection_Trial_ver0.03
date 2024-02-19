#include "gametutorialend.h"
// GAME_MAP状態のメイン処理
void GameTutorialEnd()
{
	GameTutorialEndControl();
	DrawGameTutorialEnd();
}
// マップ画面操作処理
void GameTutorialEndControl()
{
	// マウスのボタンが押されたり離されたりしたかどうかの情報を取得する
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		// 左ボタンが押されていたら
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				// 左クリックが放された時、背景が表示されきってから３秒経過していた場合、背景を消すようにする
				if (ImgDataTutorialEnd::GetCountWait() >= 180)
				{
					ImgDataTutorialEnd::SetWhiteOut(TRUE);
					ImgDataTutorialEnd::SetCountWait(0);
				}
			}
		}
	}

}
// マップモード時描画処理
void DrawGameTutorialEnd()
{
	bgimage_tutorial_end.DrawImageTutorialEnd();
}

#include "gametutorialend.h"
// GAME_MAP��Ԃ̃��C������
void GameTutorialEnd()
{
	GameTutorialEndControl();
	DrawGameTutorialEnd();
}
// �}�b�v��ʑ��쏈��
void GameTutorialEndControl()
{
	// �}�E�X�̃{�^���������ꂽ�藣���ꂽ�肵�����ǂ����̏����擾����
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		// ���{�^����������Ă�����
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				// ���N���b�N�������ꂽ���A�w�i���\�����ꂫ���Ă���R�b�o�߂��Ă����ꍇ�A�w�i�������悤�ɂ���
				if (ImgDataTutorialEnd::GetCountWait() >= 180)
				{
					ImgDataTutorialEnd::SetWhiteOut(TRUE);
					ImgDataTutorialEnd::SetCountWait(0);
				}
			}
		}
	}

}
// �}�b�v���[�h���`�揈��
void DrawGameTutorialEnd()
{
	bgimage_tutorial_end.DrawImageTutorialEnd();
}

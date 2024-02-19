#include "functionprogram.h"

int moji_retu_count = 0;	// �`��ɕK�v�ȗ�
int moji_gyou_count = 0;	// �`��ɕK�v�ȍs��
// �t���O��؂�ւ���
void FlagChange(BOOL *pf)
{
	if (*pf == FALSE){ *pf = TRUE; }
	else{ *pf = FALSE; }
}
// �Q�[�W��`�悷��i�F���ύX�\�Ȋ֐��ɂ��Ă��������j
void DrawGauge(DrawGaugeEnd x, int y, int z, int a, int b, int c, int d, int e)	// �Q�[�W��������n�_�A���͌���I���I�_,�Ή����鐔�l�̍ő�l,�Ή����鐔�l�̌��ݒl,������Wx,������Wy,�E�����Wx,�E�����Wy,�F��RGB���l
{
	switch (x)
	{
	case GAUGE_END_LEFT:
		DrawBox(a, b, ((c - a) * z / y) + a + 1, d + 1, e, TRUE);
		break;
	case GAUGE_END_RIGHT:
		DrawBox(a + ((c - a) - (c - a) * z / y), b, c + 1, d + 1, e, TRUE);
		break;
	default:
		break;
	}
}
// ���b�Z�[�W�E�B���h�E��\������
void DrawMessageWindow(int a, int b, int c, int d)	// ����x���W,����y���W,�E��x���W,�E��y���W
{
	DrawBox(a - 5, b - 5, c + 5, d + 5, GetColor(255, 255, 255), TRUE);	// �O���̔��g
	DrawBox(a, b, c, d, GetColor(0, 0, 255), TRUE);	// �����̐g
}
// ���b�Z�[�W�E�B���h�E��F�A�g�̑������w�肵�ĕ\������
void DrawMessageWindow2(int a, int b, int c, int d, int x, int co1, int co2)	// ����x���W,����y���W,�E��x���W,�E��y���W,�g�̑���,�����̐F,�O���̐F
{
	DrawBox(a, b, c, d, co2, TRUE);	// �O���̘g
	DrawBox(a + x, b + x, c - x, d - x, co1, TRUE);	// �����̘g
}
// String�֐��������Đ�����`�悷��
void DrawStringNumber(int x, int y, int number, int absolute_figure, int color, int font)	// x���W�Ay���W�A�����A�O��`�悷���ΓI�Ȍ���,�F,�t�H���g
{
	int figure = 1;					// �����̌���
	int figure_checker = number;	// �����̌����𒲂ׂ邽�߂ɐ���ǂݍ���
	// �����𒲂ׂ�
	for (int z = 0; z < 1;)
	{
		figure_checker /= 10;
		if (figure_checker == 0){ z++; }	// 10�����������ꍇ�A�������m�肵���[�v����o��
		else{ figure++; }					// �������グ�A�J��Ԃ�
	}

	if (figure > absolute_figure){ absolute_figure = figure; }	// �������傫����������
	// ������`�悷��
	for (int z = 0; z < absolute_figure; z++)
	{
		int a = 1;
		int b = 0;
		if (figure >= absolute_figure - z)
		{
			// �ł������傫����������`�悷��悤�ɂ���
			for (int c = 1; c < absolute_figure - z; c++){ a *= 10; }
			// �`�悷�鐔�������߂�
			b = number / a % 10;
		}
		// ������`�悷��
		if (figure == 1)	// �P���̏ꍇ�A�S�p�����ɂ���
		{
			switch (b)
			{
			case 0:	DrawStringToHandle(x + z * 8, y, "�O", color, font);	break;
			case 1:	DrawStringToHandle(x + z * 8, y, "�P", color, font);	break;
			case 2:	DrawStringToHandle(x + z * 8, y, "�Q", color, font);	break;
			case 3:	DrawStringToHandle(x + z * 8, y, "�R", color, font);	break;
			case 4:	DrawStringToHandle(x + z * 8, y, "�S", color, font);	break;
			case 5:	DrawStringToHandle(x + z * 8, y, "�T", color, font);	break;
			case 6:	DrawStringToHandle(x + z * 8, y, "�U", color, font);	break;
			case 7:	DrawStringToHandle(x + z * 8, y, "�V", color, font);	break;
			case 8:	DrawStringToHandle(x + z * 8, y, "�W", color, font);	break;
			case 9:	DrawStringToHandle(x + z * 8, y, "�X", color, font);	break;
			default:														break;
			}
		}
		else
		{
			switch (b)
			{
			case 0:	DrawStringToHandle(x + z * 10, y, "0", color, font);	break;
			case 1:	DrawStringToHandle(x + z * 10, y, "1", color, font);	break;
			case 2:	DrawStringToHandle(x + z * 10, y, "2", color, font);	break;
			case 3:	DrawStringToHandle(x + z * 10, y, "3", color, font);	break;
			case 4:	DrawStringToHandle(x + z * 10, y, "4", color, font);	break;
			case 5:	DrawStringToHandle(x + z * 10, y, "5", color, font);	break;
			case 6:	DrawStringToHandle(x + z * 10, y, "6", color, font);	break;
			case 7:	DrawStringToHandle(x + z * 10, y, "7", color, font);	break;
			case 8:	DrawStringToHandle(x + z * 10, y, "8", color, font);	break;
			case 9:	DrawStringToHandle(x + z * 10, y, "9", color, font);	break;
			default:														break;
			}
		}
	}
}
// �������P�������`�悷��O�ɍs������
void NextDrawCharString()
{
	// �`��ʒu�̏����ʒu�Z�b�g
	DrawPointX = 0;
	DrawPointY = 0;
	// �Q�ƕ����ʒu���Z�b�g
	SP = 0;	// �P�s�ڂ�
	CP = 0;	// �O����
	// �I���t���O��|��
	EndFlag = 0;
}
// ������`�悷��̂ɉ��񉽍s�K�v�����ׂ�O�ɍs������
void NextNDCNumberCheck()
{
	moji_retu_count = 0;
	moji_gyou_count = 0;
}

// �e�L�X�g�o�b�t�@�̉��s�����֐�
void Kaigyou2(void)
{
	// �`��s�ʒu���������
	CursorY++;
	// �`�����ŏ��ɖ߂�
	CursorX = 0;
	// �����e�L�X�g�o�b�t�@�c������͂ݏo��Ȃ�e�L�X�g�o�b�t�@���c�X�N���[��������
	if (CursorY >= STRBUF_HEIGHT)
	{
		int i, j;
		for (i = 1; i < STRBUF_HEIGHT; i++)
		{
			for (j = 1; j < STRBUF_WIDTH; j++)
			{
				StringBuf[i - 1][j] = String[i][j];
			}
		}
		// �`��s�ʒu���������
		CursorY--;
	}
}

// �J�[�\���𓮂���
int CursorMove(int a, int b, int c) // �ړ��O�̐��l�A�ړ��ʁA�ړ����E�l
{
	// �J�[�\���𓮂���
	a += b;
	// �J�[�\�����O�������΁i����ȏ�ɂȂ�΁j�w����|�P�x�Ɂi�O�Ɂj�C������
	if (a < 0){ a = c - 1; }
	else if (a >= c){ a = 0; }

	//if (g_gamestate == GAME_CHARACTERSELECT){ SEPlay(1); }	// �L�����N�^�[�Z���N�g���Ȃ���ʉ���炷
	// �ړ���̐��l��Ԃ�
	return a;
}
// �Q�l�ΐ��ʂŁA���Ώ̂ɕ`�悷����̂�x���W�����߂�
int CallDrawX(int a, int b, int c, int d, int e)	// ��ʑS�̂̑傫��,�摜�̉��T�C�Y,�v���C���[,��������̂��炵�l,�v���C���[�֌W�Ȃ����炷�l
{
	if (c == 0){ d = d * (-1); }
	int x = a / 2 - b / 2 + d + e;
	return x;
}
// �������P�������`�悷��i���̕��@�͑S�p������`�悷�邱�Ƃɂ̂ݓK���Ă��邽�߁A���p��������͂����ꍇ�A�ň��t���[�Y����
// �B���������͂��ꂽ���p�������������Ȃ瓖�Ă͂܂�Ȃ��j
int DrawCharString(int x, int y, int xl, char c, char c2, char c3, int color, int ms)	// �J�n�w���W,�J�n�x���W,�܂�Ԃ�����w���W,����,1�o�C�g��̕���,2�o�C�g��̕���,�F,�����T�C�Y
{
	switch (c)
	{
	case '@':	// ���s����
		// ���s��������юQ�ƕ����ʒu����i�߂�
		Kaigyou();
		CP++;
		break;
	case '�a':	// �{�^�������҂������i�ȗ��j
		break;
	case 'E':	// �I������
		// �I���t���O�𗧂Ă邨��юQ�ƕ����ʒu����i�߂�
		EndFlag = 1;
		CP++;
		break;
	case '�b':	// �N���A�����i�ȗ��j
		break;
	default:	// ���̑��̕���
		// �P�����������o��
		OneMojiBuf[0] = c;
		OneMojiBuf[1] = c2;
		OneMojiBuf[2] = '\0';
		// �P�����`��
		DrawFormatStringToHandle(DrawPointX * ms + x, DrawPointY * ms + y, color, g_font1, OneMojiBuf);
		// �Q�ƕ����ʒu���Q�o�C�g�i�߂�
		CP += 2;
		// �J�[�\�����ꕶ�����i�߂�
		DrawPointX++;
		// ��ʂ���͂ݏo����i���̕����`����W���݂͂ł�Ȃ�H�j���s����
		if (DrawPointX * ms + ms + x > xl){ Kaigyou(); }
		break;
	}
	// �I���t���O���P��������I������
	//if (EndFlag == 1)return 1;
	if (EndFlag == 1 || CP > 255)return 1;
	// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
	if ((c == '@' || c == 'E') ? c2 == '\0' : c3 == '\0')
	{
		SP++;
		CP = 0;
	}
	return 0;
}
int Kaigyou(void)
{
	//int TempGraph;
	// �`��s�ʒu���������
	DrawPointY++;
	// �`�����ŏ��ɖ߂�
	DrawPointX = 0;
	// ������ʂ���͂ݏo��Ȃ��ʂ��X�N���[��������
	//�i�K�v�Ȃ��Ɣ��f�������ߏȗ��j

	// �I��
	return 0;
}
// �������P�������`�悷��̂ɉ��񉽍s�K�v�����ׂ�
int DCSNumberCheck(int x, int y, int xl, char c, char c2, char c3, int ms, int *retu, int *gyou)	// �J�n�w���W,�J�n�x���W�i�g��Ȃ��j,�܂�Ԃ�����w���W,����,1�o�C�g��̕���,2�o�C�g��̕���,�����T�C�Y,��,�s��
{
	switch (c)
	{
	case '@':	// ���s����
		// ���s��������юQ�ƕ����ʒu����i�߂�
		Kaigyou();
		CP++;
		break;
	case '�a':	// �{�^�������҂������i�ȗ��j
		break;
	case 'E':	// �I������
		// �I���t���O�𗧂Ă邨��юQ�ƕ����ʒu����i�߂�
		EndFlag = 1;
		CP++;
		break;
	case '�b':	// �N���A�����i�ȗ��j
		break;
	default:	// ���̑��̕���
		// �P�����������o��
		OneMojiBuf[0] = c;
		OneMojiBuf[1] = c2;
		OneMojiBuf[2] = '\0';
		// �Q�ƕ����ʒu���Q�o�C�g�i�߂�
		CP += 2;
		// �J�[�\�����ꕶ�����i�߂�
		DrawPointX++;
		// ��ʂ���͂ݏo����i���̕����`����W���݂͂ł�Ȃ�H�j���s����
		if (DrawPointX * ms + ms + x > xl)
		{
			*retu = DrawPointX;
			Kaigyou();
		}
		break;
	}
	// �I���t���O���P��������I������
	if (EndFlag == 1 || CP > 255)
	{
		if (DrawPointX > *retu){ *retu = DrawPointX; }
		*gyou = DrawPointY;
		return 1;
	}
	// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
	if ((c == '@' || c == 'E') ? c2 == '\0' : c3 == '\0')
	{
		SP++;
		CP = 0;
	}
	return 0;
}

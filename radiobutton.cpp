//	���W�I�{�^���T���v��
//	Visual C++ 2013 32/64bit

#include <windows.h>
#include <commctrl.h> 
#include <tchar.h>
#include "resource.h"
#include "main.h"

BOOL dialog_not_push = TRUE;	// �_�C�A���O�{�b�N�X�ł�����Ɓw�Q�[���N���x�������ꂽ���m�F����t���O

/*
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
	TCHAR* lpszCmdLine, int nCmdShow){
	DialogBox(hInstance, TEXT("DLG1"), 0, (DLGPROC)DlgProc1);

	return (int)0;
}
*/

//	�_�C�A���O�{�b�N�X�v���V�[�W���[
LRESULT CALLBACK DlgProc1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam){
	TCHAR buf[32];
	switch (msg) {
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_RADIOBUTTON101), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hDlg, IDC_RADIOBUTTON111), BM_SETCHECK, BST_CHECKED, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIOBUTTON101:
			if(HIWORD(wParam) == BN_CLICKED){
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL103), _TEXT("�j"));
			}
			return FALSE;
		case IDC_RADIOBUTTON102:
			if (HIWORD(wParam) == BN_CLICKED){
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL103), _TEXT("��"));
			}
			return FALSE;
		case IDC_RADIOBUTTON111:
			if (HIWORD(wParam) == BN_CLICKED){
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL113), _TEXT("�q��"));
			}
			return FALSE;
		case IDC_RADIOBUTTON112:
			if (HIWORD(wParam) == BN_CLICKED){
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL113), _TEXT("��l"));
			}
			return FALSE;
		case IDOK:
			if (SendMessage(GetDlgItem(hDlg, IDC_RADIOBUTTON101), BM_GETCHECK, 0, 0) == BST_CHECKED)
				//_tcscpy_s(buf,sizeof(buf)/sizeof(TCHAR), _TEXT("�j "));
			{
				flag_full_hd_now = FALSE;
			}
			else
				//_tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _TEXT("�� "));
			{
				flag_full_hd_now = TRUE;
			}

			if (SendMessage(GetDlgItem(hDlg, IDC_RADIOBUTTON111), BM_GETCHECK, 0, 0) == BST_CHECKED)
				_tcscat_s(buf, sizeof(buf) / sizeof(TCHAR), _TEXT("�q��"));
			else
				_tcscat_s(buf, sizeof(buf) / sizeof(TCHAR), _TEXT("��l"));
			//MessageBox(hDlg, buf, _TEXT("���W�I�{�^���̏��"), MB_OK);
			EndDialog(hDlg, TRUE);
			dialog_not_push = FALSE;	// �Q�[�����I�������t���O�����낷
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return FALSE;
		default:
			return FALSE;
		}
	default:
		return FALSE;
	}
	return TRUE;
}

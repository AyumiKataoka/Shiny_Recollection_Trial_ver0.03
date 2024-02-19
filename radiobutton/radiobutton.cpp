//	ラジオボタンサンプル
//	Visual C++ 2013 32/64bit

#include <windows.h>
#include <commctrl.h> 
#include <tchar.h>
#include "resource.h"

//	ダイアログボックスプロシージャー
LRESULT CALLBACK DlgProc1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
	TCHAR* lpszCmdLine, int nCmdShow){
	DialogBox(hInstance, TEXT("DLG1"), 0, (DLGPROC)DlgProc1);

	return (int)0;
}

//	ダイアログボックスプロシージャー

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
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL103), _TEXT("男"));
			}
			return FALSE;
		case IDC_RADIOBUTTON102:
			if (HIWORD(wParam) == BN_CLICKED){
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL103), _TEXT("女"));
			}
			return FALSE;
		case IDC_RADIOBUTTON111:
			if (HIWORD(wParam) == BN_CLICKED){
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL113), _TEXT("子供"));
			}
			return FALSE;
		case IDC_RADIOBUTTON112:
			if (HIWORD(wParam) == BN_CLICKED){
				SetWindowText(GetDlgItem(hDlg, IDC_LABEL113), _TEXT("大人"));
			}
			return FALSE;
		case IDOK:
			if (SendMessage(GetDlgItem(hDlg, IDC_RADIOBUTTON101), BM_GETCHECK, 0, 0) == BST_CHECKED)
				_tcscpy_s(buf,sizeof(buf)/sizeof(TCHAR), _TEXT("男 "));
			else
				_tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _TEXT("女 "));

			if (SendMessage(GetDlgItem(hDlg, IDC_RADIOBUTTON111), BM_GETCHECK, 0, 0) == BST_CHECKED)
				_tcscat_s(buf, sizeof(buf) / sizeof(TCHAR), _TEXT("子供"));
			else
				_tcscat_s(buf, sizeof(buf) / sizeof(TCHAR), _TEXT("大人"));
			MessageBox(hDlg, buf, _TEXT("ラジオボタンの状態"), MB_OK);
			EndDialog(hDlg, TRUE);
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

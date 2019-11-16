#include "../include/stdafx.h"
#include "../include/PwdMaker.h"
#include "../include/MD5lib.h"

HINSTANCE hInst;

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DiagProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR lpCmdLine,
                       int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
		hInst = hInstance;
	
		InitCommonControls();

		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, DiagProc);

    return 1;
}


INT_PTR CALLBACK DiagProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent, resLen = 8;

	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		SetDlgItemInt(hDlg, IDC_EDIT_BITS, resLen, false);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId) {
		case IDCANCEL:
			EndDialog(hDlg, wmId);
			break;
		case IDC_BUTTON_DO:
			char cSource[100], cKey[100], cRes[32];
			int cNum = 0;
			HWND hSource = GetDlgItem(hDlg, IDC_EDIT_SOURCE);
			HWND hKey = GetDlgItem(hDlg, IDC_EDIT_KEYS);

			SetDlgItemText(hDlg, IDC_EDIT_RESULT, "");
			if (GetWindowTextLength(hSource) > 100) {
				MessageBox(hDlg, " ", "", MB_OK);
				SendMessage(hSource, EN_SETFOCUS, 1, 0);
				return 0;
			}
			else if (GetWindowTextLength(hSource) < 1) {
				MessageBox(hDlg, "", "", MB_OK);
				SendMessage(hSource, EN_SETFOCUS, 1, 0);
				return 0;
			}

			if (GetWindowTextLength(hKey) > 100) {
				MessageBox(hDlg, "", "", MB_OK);
				return 0;
			}


			GetDlgItemText(hDlg, IDC_EDIT_SOURCE, cSource, 100);
			GetDlgItemText(hDlg, IDC_EDIT_KEYS, cKey, 100);

			BOOL flag;
			resLen = GetDlgItemInt(hDlg, IDC_EDIT_BITS, &flag, false);

			if (!flag || resLen > 32 || resLen <= 0) {
				MessageBox(hDlg, "", "", MB_OK);
				return 0;
			}

			if (strcmp(cKey, "")) {
				strncpy(cRes, hmac_md5(cSource, cKey), resLen);
				cRes[resLen] = 0;
				SetDlgItemText(hDlg, IDC_EDIT_RESULT, cRes);
			}
			else {
				strncpy(cRes, MDString(cSource), resLen);
				cRes[resLen] = 0;
				SetDlgItemText(hDlg, IDC_EDIT_RESULT, cRes);
			}

			break;
		}
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}

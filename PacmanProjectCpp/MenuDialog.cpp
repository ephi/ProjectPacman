// MenuDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PacmanProjectCpp.h"
#include "MenuDialog.h"
#include "afxdialogex.h"


// MenuDialog dialog

IMPLEMENT_DYNAMIC(MenuDialog, CDialogEx)

	MenuDialog::MenuDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MenuDialog::IDD, pParent)
{

}

MenuDialog::~MenuDialog()
{
}

void MenuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MenuDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RESUME, &MenuDialog::OnBnClickedBtnResume)
	ON_BN_CLICKED(IDC_BTN_RESTART, &MenuDialog::OnBnClickedBtnRestart)
//	ON_WM_INITMENU()
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BTN_REDO, &MenuDialog::OnBnClickedBtnRedo)
ON_BN_CLICKED(IDC_BTN_UNDO, &MenuDialog::OnBnClickedBtnUndo)
ON_BN_CLICKED(IDC_BTN_LOAD, &MenuDialog::OnBnClickedBtnLoad)
ON_BN_CLICKED(IDC_BTN_SAVE, &MenuDialog::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// MenuDialog message handlers


void MenuDialog::OnBnClickedBtnResume()
{
	GameLevel::resume(gameDlg->getGameThread(),this);
}


void MenuDialog::OnBnClickedBtnRestart()
{
	GameLevel *gameLvl =gameDlg->getGameLevel();
	bool isGameOver = gameLvl->isGameOver();
	gameLvl->restart(true);
	if(!isGameOver)
	{
		ResumeThread(*gameDlg->getGameThread());
	}
	else
	{
		gameDlg->restartGameThread();
	}
	ShowWindow(SW_HIDE);
}


//void MenuDialog::OnInitMenu(CMenu* pMenu)
//{
//	
//	CDialogEx::OnInitMenu(pMenu);
//
//	
//}


void MenuDialog::OnClose()
{
	
	if(gameDlg->getGameLevel()->isGameOver())
		OnBnClickedBtnRestart();
	else
		OnBnClickedBtnResume();
	CDialogEx::OnClose();
}


void MenuDialog::OnBnClickedBtnRedo()
{
	gameDlg->getGameLevel()->redo();
}


void MenuDialog::OnBnClickedBtnUndo()
{
	gameDlg->getGameLevel()->undo();
}


void MenuDialog::OnBnClickedBtnLoad()
{
	gameDlg->getGameLevel()->load();
	MessageBoxW(L"Your Game has been loaded",L"load Successfull");
}


void MenuDialog::OnBnClickedBtnSave()
{
	gameDlg->getGameLevel()->save();
	MessageBoxW(L"Your Game has been saved",L"Save Successfull");
}

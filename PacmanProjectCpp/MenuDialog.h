#pragma once


// MenuDialog dialog
#include "GameLevel.h"
#include "PacmanProjectCppDlg.h"
class CPacmanProjectCppDlg;
class MenuDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MenuDialog)

public:
	MenuDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MenuDialog();
	void setGameDialog(CPacmanProjectCppDlg *dialog){ this->gameDlg = dialog;}

// Dialog Data
	enum { IDD = IDD_MNU };
private:
	CPacmanProjectCppDlg *gameDlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnResume();
	afx_msg void OnBnClickedBtnRestart();
//	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnRedo();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
};

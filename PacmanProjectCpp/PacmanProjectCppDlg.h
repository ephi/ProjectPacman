
// PacmanProjectCppDlg.h : header file
//

#pragma once

#include "GameLevel.h"
#include "MenuDialog.h"
class MenuDialog;
// CPacmanProjectCppDlg dialog
class CPacmanProjectCppDlg : public CDialogEx
{
// Construction
public:
	CPacmanProjectCppDlg(CWnd* pParent = NULL);	// standard constructor
	~CPacmanProjectCppDlg(){
		//gamelevel.releaseUndosRedos();
		delete menuDialog;
	};
	GameLevel* getGameLevel();
	HANDLE* getGameThread(){ return &gamethreadHandle;}
	void restartGameThread();
	BOOL PreTranslateMessage(MSG* pMsg);

// Dialog Data
	enum { IDD = IDD_PACMANPROJECTCPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	HANDLE gamethreadHandle; 
	GameLevel *gamelevel;
	MenuDialog* menuDialog;
	//MenuDialog menuDialog;
public:
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	CButton m_mnu_grp;
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnCancel();
};

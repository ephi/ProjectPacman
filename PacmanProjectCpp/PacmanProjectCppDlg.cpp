
// PacmanProjectCppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PacmanProjectCpp.h"
#include "PacmanProjectCppDlg.h"
#include "afxdialogex.h"
#include "Levelwall.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPacmanProjectCppDlg dialog




CPacmanProjectCppDlg::CPacmanProjectCppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPacmanProjectCppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	menuDialog = new MenuDialog(NULL);
	menuDialog->setGameDialog(this);
	gamelevel = NULL;
}

void CPacmanProjectCppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_MNU_GRP, m_mnu_grp);

}

BEGIN_MESSAGE_MAP(CPacmanProjectCppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//	ON_WM_KEYUP()
	//ON_WM_KEYDOWN()

	//	ON_WM_CTLCOLOR()
//	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


DWORD WINAPI GameThread( LPVOID lpParam ) 
{

	CPacmanProjectCppDlg*     Data;
	int     count = 0;
	HANDLE  hStdout = NULL;

	// Get Handle To screen.
	// Else how will we print?
	if( (hStdout = 
		GetStdHandle(STD_OUTPUT_HANDLE)) 
		== INVALID_HANDLE_VALUE )  
		return 1;

	// Cast the parameter to the correct
	// data type passed by callee i.e main() in our case.
	Data = ((CPacmanProjectCppDlg*)lpParam); 
	//bool notOver = true;
	while(	Data->getGameLevel()->update()){
		//Data->getGameLevel()->update();
		//Data->Invalidate();
		//Data->Invalidate();
		//Data->ValidateRect(Data->getGameLevel()->getPacman()->getBindingRect());
		//Data->UpdateWindow();
		Sleep(100);
	}
	//
	//Data->getGameLevel()->clearLevel();
	//Data->Invalidate();
	//for (count = 0; count <= 4; count++ )
	//{
	//  DisplayMessage (hStdout, "Thread_no_1", Data, count);
	//}
	return 0; 
} 

// CPacmanProjectCppDlg message handlers

BOOL CPacmanProjectCppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
//	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	this->SetBackgroundColor(RGB(0,0,0));
	//m_btn_load.SetParent(&m_mnu_grp);
	//m_btn_save.SetParent(&m_mnu_grp);
	//m_btn_redo.SetParent(&m_mnu_grp);
	//m_btn_undo.SetParent(&m_mnu_grp);
	//m_btn_restart.SetParent(&m_mnu_grp);
	//m_btn_resume.SetParent(&m_mnu_grp);
	//m_btn_quit.SetParent(&m_mnu_grp);
	//m_mnu_grp.setwin

	menuDialog->Create(IDD_MNU ,this);
	// Create game thread
	
	restartGameThread();
	//menuDialog.setGameThreadHandle(&gamethreadHandle);
	//menuDialog.setGameLevel(&(this->gamelevel));
	HICON hIcon= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PACMAN));
	SetIcon(hIcon,true);
	SetIcon(hIcon,false);
	return TRUE;  // return TRUE  unless you set the focus to a control

}

void CPacmanProjectCppDlg::restartGameThread(){
	if(gamelevel != NULL)
		delete gamelevel;
	gamelevel = new GameLevel(this);
	gamethreadHandle = CreateThread( NULL, 0, 
		GameThread, this, 0, NULL);  
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPacmanProjectCppDlg::OnPaint()
{
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // device context for painting

	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	//	// Center icon in client rectangle
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;

	//	// Draw the icon
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{
	//	CDialogEx::OnPaint();
	//}
	CPaintDC dc(this); // device context for painting
	gamelevel->draw(&dc);
	//CDialogEx::OnPaint();
	//Levelwall lw(90,10,0,0);
	//lw.Draw(&dc);

}
GameLevel* CPacmanProjectCppDlg::getGameLevel(){
	return gamelevel;
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPacmanProjectCppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CPacmanProjectCppDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//
//	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
//}


//void CPacmanProjectCppDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	TRACE("test");
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}
BOOL CPacmanProjectCppDlg::PreTranslateMessage(MSG* pMsg){
	if(pMsg->message == WM_KEYUP){
		switch(pMsg->wParam){
		case VK_DOWN:
			TRACE("DOWN");
			gamelevel->getPacman()->changeDirection(DIRECTION::Down);
			break;
		case VK_UP:
			TRACE("UP");
			gamelevel->getPacman()->changeDirection(DIRECTION::Up);
			break;
		case VK_LEFT:
			TRACE("LEFT");
			gamelevel->getPacman()->changeDirection(DIRECTION::Left);
			break;
		case VK_RIGHT:
			TRACE("RIGHT");
			gamelevel->getPacman()->changeDirection(DIRECTION::Right);
			break;
		case 80://P button presseed
			GameLevel::pause(&gamethreadHandle,menuDialog);
			break;

		}
	}
	return CDialogEx::PreTranslateMessage(pMsg); 
}


//HBRUSH CPacmanProjectCppDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//
//	if(pWnd->GetDlgCtrlID() == IDC_MNU_GRP)
//	{
//		pDC->SetBkColor(RGB(255,255,255));
//	}
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//	// TODO:  Change any attributes of the DC here
//
//	// TODO:  Return a different brush if the default is not desired
//	return hbr;
//}


//void CPacmanProjectCppDlg::OnShowWindow(BOOL bShow, UINT nStatus)
//{
//	CDialogEx::OnShowWindow(bShow, nStatus);
//
//	// TODO: Add your message handler code here
//}


void CPacmanProjectCppDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	gamelevel->finishGame();
	Sleep(150);
	delete gamelevel;
	CDialogEx::OnCancel();
}

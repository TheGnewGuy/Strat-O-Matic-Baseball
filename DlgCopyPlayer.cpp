// DlgCopyPlayer.cpp : implementation file
//

//#include "pch.h"
#include "stdafx.h"
#include "Baseball.h"
#include "afxdialogex.h"
#include "DlgCopyPlayer.h"


// DlgCopyPlayer dialog

IMPLEMENT_DYNAMIC(DlgCopyPlayer, CDialog)

DlgCopyPlayer::DlgCopyPlayer(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SELPLAYER1, pParent)

{

}

DlgCopyPlayer::~DlgCopyPlayer()
{
}

void DlgCopyPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELPLAYERLISTBOX1, m_playerListBox);
}


BEGIN_MESSAGE_MAP(DlgCopyPlayer, CDialog)
END_MESSAGE_MAP()


// DlgCopyPlayer message handlers


BOOL DlgCopyPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_playerListBox.ResetContent();
	for (int i = 0; i < m_arrayPlayers.GetSize(); i++)
	{
		m_playerListBox.AddString(m_arrayPlayers[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void DlgCopyPlayer::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	int count;

	m_Index = m_playerListBox.GetCurSel();
	
	count = m_playerListBox.GetTextLen(m_Index);
	m_playerListBox.GetText(m_Index, m_selection.GetBuffer(count));
	m_selection.ReleaseBuffer();

	CDialog::OnOK();
}

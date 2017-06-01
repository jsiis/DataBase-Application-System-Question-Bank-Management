// PasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "PasswordDlg.h"
#include "ManageAllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg dialog


CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPasswordDlg)
	m_strNew = _T("");
	m_strNewagain = _T("");
	m_strOld = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	strUsername = "";
}


void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordDlg)
	DDX_Text(pDX, IDC_EDIT_NEW, m_strNew);
	DDX_Text(pDX, IDC_EDIT_NEWAGAIN, m_strNewagain);
	DDX_Text(pDX, IDC_EDIT_OLD, m_strOld);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CPasswordDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg message handlers

BOOL CPasswordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;
	strUsername = parent->GetUsername();
	m_strTitle = "�û�";
	m_strTitle += strUsername;
	m_strTitle += "��";
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPasswordDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_strOld.IsEmpty())
	{
		AfxMessageBox("������ԭ����!");
		return;
	}
	if(m_strNew.IsEmpty())
	{
		AfxMessageBox("������������!");
		return;
	}
	CADORecordset *pRs = new CADORecordset(pDB);
	CString sql;
	sql.Format("select * from tbLogin where Username='%s'",strUsername);
	pRs->Open(sql,CADORecordset.openQuery);
	if(!pRs->IsOpen())
	    return;
	if(pRs->GetRecordCount() <= 0)
		return;
	CString strPassword;
	pRs->GetFieldValue("Password",strPassword);
	if(strPassword != m_strOld)
	{
		AfxMessageBox("ԭ�����������!");
		return;
	}
	if(m_strNewagain != m_strNew)
	{
		AfxMessageBox("��������ȷ�����벻һ��!");
		return;
	}
	pRs->SetFieldValue("Password",m_strNew);
	pRs->Update();
	pRs->Close();
	delete(pRs);
	AfxMessageBox("�����޸ĳɹ�!");
	CDialog::OnOK();
}

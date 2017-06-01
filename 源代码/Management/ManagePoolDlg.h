#if !defined(AFX_MANAGEPOOLDLG_H__D5047930_1587_43A3_86F1_4CF48C8D4FFC__INCLUDED_)
#define AFX_MANAGEPOOLDLG_H__D5047930_1587_43A3_86F1_4CF48C8D4FFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManagePoolDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManagePoolDlg dialog

class CManagePoolDlg : public CDialog
{
// Construction
public:
	CManagePoolDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase *pDB;

// Dialog Data
	//{{AFX_DATA(CManagePoolDlg)
	enum { IDD = IDD_DIALOG_MANAGEPOOL };
	CListCtrl	m_listPool;
	CString	m_strSubject;      //Ҫ��ӵĿ�Ŀ����
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagePoolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitPoolList();           //��ʼ������б�
	BOOL CreateNewTable(CString tablename,CString papername,CString existname);  //�½���Ӧ�ı�
	BOOL TableIsEmpty(CString tablename);         //�жϱ��Ƿ�Ϊ��
//	void UpdateOthers(CString old_id);            //ɾ����Ŀ����º����Ŀ��id

	// Generated message map functions
	//{{AFX_MSG(CManagePoolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();            //��ӿ�Ŀ
	afx_msg void OnButtonDelete();         //ɾ����Ŀ
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEPOOLDLG_H__D5047930_1587_43A3_86F1_4CF48C8D4FFC__INCLUDED_)

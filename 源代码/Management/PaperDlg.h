#if !defined(AFX_PAPERDLG_H__027A1889_5D95_442D_9432_E5BADC076BC7__INCLUDED_)
#define AFX_PAPERDLG_H__027A1889_5D95_442D_9432_E5BADC076BC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaperDlg dialog

class CPaperDlg : public CDialog
{
// Construction
	CString strUsername;     //�û���(�����Ծ���)
	BOOL Purview;       //�Ƿ���ϵͳ����Ա
	CString ExistTable_name;   //��ǰ�����Ծ���������
	CString Exist_ID;         //��ǰ�����Ծ�ID
	CString Now_ID;           //��ǰѡ���Ծ�ID
public:
	CPaperDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase *pDB;
	CString GetUsername(){return strUsername;};

// Dialog Data
	//{{AFX_DATA(CPaperDlg)
	enum { IDD = IDD_DIALOG_PAPER };
	CListCtrl	m_listPaper;        //�Ծ��б�
	CDateTimeCtrl	m_DateTo;       //����ʱ��ؼ�
	CListCtrl	m_listQuestion;     //�����б�
	CDateTimeCtrl	m_DateFrom;     //��ʼʱ��ؼ�
	CComboBox	m_comboSubject;     //ѡ���ĿCombo
	CComboBox	m_comboCreateperson;  //ѡ�񴴽���Combo
	CTreeCtrl	m_paperTree;        //�Ծ����οؼ�
	CButton	m_buttonAnswer;         //����𰸰�ť
	BOOL	m_checkDate;            //�Ƿ�ʱ���ѯ
	CString	m_strCreateperson;      //������
	CString	m_strSubject;           //�Ծ��Ŀ
	CString	m_strID;                //��ȷ��ѯID
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CImageList m_ImgList;          //���νṹ(m_ImgLst.Create(IDB_TREE,16,1,RGB(0,255,255));  m_wndTree.SetImageList(&m_ImgLst,TVSIL_NORMAL);��ͼ��)
	BOOL InitComboSubject();       //��ʼ����ĿCombo   
	BOOL InitComboCreate();        //ѡ����Ŀ���ʼ��������Combo
	BOOL InitPaperList();          //�仯ʱ��ʼ���Ծ��б�
	BOOL InitPaperTree();          //�仯ʱ��ʼ���Ծ����οؼ�
	CString FindtbPaper(CString strChineseName);    //ͨ����Ŀ���Ʒ��������Ծ����
	CString FindtbExist(CString strChineseName);    //ͨ����Ŀ���Ʒ��س����Ծ����
	BOOL InsertPaperItem(HTREEITEM hItem,CString strPaperName);  //�������Ծ�������οؼ�
	BOOL InsertExistItem(HTREEITEM hItem,CString strExistName);  //�������Ծ�������οؼ�
	void RefreshList(BOOL PaperOrExist,CADORecordset &recordset); //�����Ծ��б�
	void UpdateQuestionList(CADORecordset &recordset);           //���������б�
	CString FindType(CString Type);                 //ͨ�����ͱ��뷵����Ŀ��������
	CString FindDifficulty(CString Difficulty);     //ͨ���Ѷȱ��뷵����Ŀ�Ѷ�����
	CString FindChapter(CString Chapter);           //ͨ���½ڱ��뷵����Ŀ�½�����
	BOOL SaveExist(CString strContent);             //�ж��Ƿ񱣴���׵�����Ծ�     
	// Generated message map functions
	//{{AFX_MSG(CPaperDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonIn();                  //��������Ծ�
	afx_msg void OnButtonInanswer();            //���������
	afx_msg void OnButtonBrowse();              //����Ծ���
	afx_msg void OnSelchangeComboSubject();      //��Ŀѡ�����仯
	afx_msg void OnClickTreePaper(NMHDR* pNMHDR, LRESULT* pResult);   //������οؼ�
	afx_msg void OnSelchangedTreePaper(NMHDR* pNMHDR, LRESULT* pResult);  //���οؼ�ѡ�����仯
	afx_msg void OnClickListPaper(NMHDR* pNMHDR, LRESULT* pResult);   //����Ծ��б�
	afx_msg void OnCheckDate();          //ѡ���Ƿ�ʱ���ѯ
	afx_msg void OnButtonQuery();       //������ѯ
	afx_msg void OnButtonOnlyquery();   //��ȷ��ѯ
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAPERDLG_H__027A1889_5D95_442D_9432_E5BADC076BC7__INCLUDED_)

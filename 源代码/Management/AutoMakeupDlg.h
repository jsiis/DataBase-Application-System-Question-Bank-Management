#if !defined(AFX_AUTOMAKEUPDLG_H__59648BBC_1686_4B23_8B5B_8FD96E59EA8C__INCLUDED_)
#define AFX_AUTOMAKEUPDLG_H__59648BBC_1686_4B23_8B5B_8FD96E59EA8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoMakeupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAutoMakeupDlg dialog
typedef struct Item      //�Ծ�
{  
	CString FanganID;    
	CString ID;
	CString QuestionID;
	CString QuestionScore;
	CString QuestionAnswer;
	CString Content;
	CString Answer;
	CString Date;
	CString Username;
}PaperNode;

class CAutoMakeupDlg : public CDialog
{
// Construction
	BOOL Purview;                    //Ȩ���Ƿ�Ϊ����Ա
	PaperNode newPaper;              //���Ծ���
public:
	CAutoMakeupDlg(CWnd* pParent = NULL);   // standard constructor
	~CAutoMakeupDlg();
	CADODatabase * pDB;
    CADORecordset* pRs;
	int     m_nCount[10];            //��Ÿ�������
	int     m_nScore[10];            //��Ÿ����ֵ
	CString m_str[10];               //��Ÿ�����������
	CComboBox   m_combo[10];         //ѡ������
	CButton     m_buttonOther[10];   //ѡ���½ڡ��Ѷ�
	CEdit       m_editCount[10];     //����
	CEdit       m_editScore[10];     //��ֵ
	int nButtonOther_index;
	//�������ƣ��´��ٰ���ButtonOther��ʼ����,���������
	CString strSelChap[10];
	CString strSelDiff[10];
	//�ж��ܷ�����ã���ѡ�½ں��Ѷ����������뵱ǰѡ����Ŀ�Ƿ�һ��,����������
	int nSelChap[10];
	int nSelDiff[10];
	//ȡ�ñ������͵��½ں��Ѷȸ�Sel��
	CString Chapter_all[30];
    CString Difficulty_all[5];
	//ȡ�������ÿ��ÿ���Ѷȵ���Ŀ����ѡ��ʱ�ж������Ƿ������
	int EveryChapNum[30];
	int EveryDiffNum[5];
	//��¼��OnButtonOther��ÿ������ÿ�¡�ÿ���Ѷȵ���Ŀ�����ʱ��,����������
	int Chapter_num[10][30];
	int Difficulty_num[10][5];
	CString GetTableName();
	

// Dialog Data
	//{{AFX_DATA(CAutoMakeupDlg)
	enum { IDD = IDD_DIALOG_AUTO };
	CDateTimeCtrl	m_DateTimeCreate;      //�Ծ���ʱ��
	CEdit	m_editAllscore;                //��д�ֿܷؼ�
	CEdit	m_editAnswer;
	CButton	m_buttonOutAnswer;
	CButton	m_buttonOut;
	CButton	m_buttonStart;
	CButton	m_buttonSelect;
	CButton	m_buttonReset;
	CEdit	m_editPaper;
	CComboBox	m_comboSubject;
	CComboBox	m_comboNumber;
	int		m_nNumber;             //��������
	CString	m_strSubject;          //��Ŀ����
	CString	m_strPaper;	           //����Ծ�����
	CString	m_strAnswer;           //����Ծ��
	int		m_nAllscore;           //�ܷ�ֵ
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoMakeupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitCombo();         //ÿ��ѡ�п�Ŀ֮���ʼ������ѡ������Combo Box��Dataֵ
	BOOL InitComboSubject();  //��ʼ��ѡ���ĿCombo Box��Dataֵ
	BOOL FindAllItems();      //�ҵ�����������������������
	BOOL IsExist(int No[],int x);  //�жϵ�ǰ�����ȡ�������Ƿ���ѡ�й�
	BOOL InsertNewItems();         //��������Ծ���ӵ��Ծ��
	CString FindTable();           //����жϵ�ǰѡ�еĿ�Ŀ����Ƿ���ڣ�����ֵΪ�������
	CString FindID(CString fangan_ID);  //ͨ���βη���ID�����ص�ǰ����Ծ�Ҫ����������е�ID
	CString FindType(CString strType);  //ͨ���β��������ƣ��������ʹ���
	int FindDifficulty(CString strDifficulty);  //ͨ���β��Ѷ����ƣ���������
	CString IntToString(int index);     //����������ת��Ϊ2λ���ַ���
	CString SetTitle();              //���þ�ͷ

	CString Table_name;              //��¼��ǰѡ�п�Ŀ�������
	CString strPaperName;            //��¼��ǰѡ��Ŀ�Ŀ�Ծ����


	// Generated message map functions
	//{{AFX_MSG(CAutoMakeupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonOut();
	afx_msg void OnSelchangeComboNumber();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonOutanswer();
	//}}AFX_MSG
	void OnButtonOther(UINT nID); 
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOMAKEUPDLG_H__59648BBC_1686_4B23_8B5B_8FD96E59EA8C__INCLUDED_)

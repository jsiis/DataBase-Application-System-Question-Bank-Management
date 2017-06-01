#if !defined(AFX_QUESTIONDLG_H__79AC77B2_D68B_430E_886D_260F00E7CE97__INCLUDED_)
#define AFX_QUESTIONDLG_H__79AC77B2_D68B_430E_886D_260F00E7CE97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuestionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuestionDlg dialog
typedef struct question
{
	char type[20];
	char difficulty[10];
	char chapter[10];
	char content[10000];
	char answer[10000];
	struct question * next;
}Node,*pNode;

class CQuestionDlg : public CDialog
{
// Construction
	bool Purview;          //�ж�Ȩ���Ƿ��ǹ���Ա
public:
	CQuestionDlg(CWnd* pParent = NULL);   // standard constructor
	~CQuestionDlg();
	CADODatabase * pDB;
    CADORecordset* pRs;
	//��ӻ��޸ļ�¼
	bool m_AddorEdit;      //CAddandeditDlg�л�ȡ��ֵ���ж�����ӻ����޸�

// Dialog Data
	//{{AFX_DATA(CQuestionDlg)
	enum { IDD = IDD_DIALOG_QUESTION };
	CButton	m_buttonClear;
	CEdit	m_editQueryid;
	CButton	m_buttonQueryOnly;
	CButton	m_buttonQuery;
	CButton	m_buttonPre;
	CButton	m_buttonOut;
	CButton	m_buttonNext;
	CButton	m_buttonLast;
	CButton	m_buttonIn;
	CButton	m_buttonFirst;
	CButton	m_buttonEdit;
	CButton	m_buttonDelete;
	CButton	m_buttonConfirm;
	CButton	m_buttonClose;
	CButton	m_buttonAdd;
	CComboBox	m_comboType;
	CComboBox	m_comboDifficulty;
	CComboBox	m_comboChapter;
	CEdit	m_editAnswer;
	CEdit	m_editType;
	CEdit	m_editID;
	CEdit	m_editDifficulty;
	CEdit	m_editContent;
	CEdit	m_editChapter;
	CListCtrl	m_questionList;
	CComboBox	m_comboSubject;
	CString	m_chapter;             //��¼�½�(��ǰ����)
	CString	m_content;             //��¼����
	CString	m_difficulty;          //��¼�Ѷ�
	CString	m_id;                  //��¼id
	CString	m_type;                //��¼����
	CString	m_answer;              //��¼��
	CString	m_subject;             //��¼��ǰ�����Ŀ�Ŀ����
	CString	m_selectChapter;       //������ѯѡ���½�
	CString	m_selectDifficulty;    //������ѯѡ���Ѷ�
	CString	m_selectType;          //������ѯѡ������
	CString	m_queryid;             //��ȷ��ѯid
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuestionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//�򿪵������
	CString Table_name;

	//�����Ƿ����ѡ�п�Ŀ�����
	CString FindTable();
	//������ϸ��Ϣ
	void SetAllControls();
	//���������б�
	void RefreshList(CADORecordset& recordset);
	//�õ����ʹ���
	CString FindType(CString type);
	//�õ��Ѷȴ���
	CString FindDifficulty(CString difficulty);
	//�õ��½ڴ���
	CString FindChapter(CString chapter);
	//�õ���4λ(�����͡��½ڡ��Ѷ��еĵڼ���)
	CString FindNum(CString type,CString difficulty,CString chapter);
	//ĳ���ⱻɾ�����޸ĺ��޸�ԭ������֮���������ĿID
	void UpdateOthers(CString old_id,CString old_type,CString old_difficulty,CString old_chapter);
	//��ʼ�����͡��ѶȺ��½�combo
	BOOL InitCombo();
	//��ʼ����Ŀcombo
	BOOL InitComboSubject();
	//����������������
	BOOL InsertNewItem(CString type,CString difficulty,CString chapter,CString content,CString answer); 
	//������������ʱ�ж��ļ��Ƿ���Դ�
	CString CanOpen(CString in_filename);
	//������������
	BOOL ImportQuestiones(CString strChapter,CString strSel);
	//������ѯʱ�ж�
	int State();
	//ֹͣ��������
	bool IsStop(int index,int len);


	// Generated message map functions
	//{{AFX_MSG(CQuestionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListQuestion(NMHDR* pNMHDR, LRESULT* pResult);   //��������б���Ӧ����
	afx_msg void OnButtonConfirm();          //�������
	afx_msg void OnButtonClose();            //�رյ�ǰ�򿪿�Ŀ�����
	afx_msg void OnButtonFirst();            //��һ��
	afx_msg void OnButtonLast();             //���һ��
	afx_msg void OnButtonPre();              //��һ��
	afx_msg void OnButtonNext();             //��һ��
	afx_msg void OnButtonAdd();              //�������
	afx_msg void OnButtonEdit();             //�޸�����
	afx_msg void OnButtonDelete();           //ɾ������
	afx_msg void OnButtonClear();            //�������
    afx_msg void OnButtonQuery();            //������ѯ����
    afx_msg void OnButtonQueryonly();        //��ȷ��ѯ����
    afx_msg void OnButtonIn();               //���������������
	afx_msg void OnButtonOut();              //��������鿴
	afx_msg void OnKeydownListQuestion(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUESTIONDLG_H__79AC77B2_D68B_430E_886D_260F00E7CE97__INCLUDED_)

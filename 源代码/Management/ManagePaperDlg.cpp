// ManagePaperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "ManagePaperDlg.h"
#include "ManageAllDlg.h"
#include "BrowsePaperDlg.h"
#include "EditAnswerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManagePaperDlg dialog
CString paperDifficulty_Chinese[5] = {"��","����","�е�","����","��"};
//CString paperChapter_Chinese[30] = {"��01��","��02��","��03��","��04��","��05��","��06��","��07��","��08��","��09��","��10��",
//"��11��","��12��","��13��","��14��","��15��","��16��","��17��","��18��","��19��","��20��",
//"��21��","��22��","��23��","��24��","��25��","��26��","��27��","��28��","��29��","��30��"};


CManagePaperDlg::CManagePaperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManagePaperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManagePaperDlg)
	m_strCreateperson = _T("");
	m_strSubject = _T("");
	m_strID = _T("");
	m_checkDate = FALSE;
	//}}AFX_DATA_INIT
	Purview = FALSE;
	strUsername = "";
	Now_ID = "";
}


void CManagePaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManagePaperDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_DateTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_DateFrom);
	DDX_Control(pDX, IDC_TREE_PAPER, m_paperTree);
	DDX_Control(pDX, IDC_LIST_QUESTION, m_listQuestion);
	DDX_Control(pDX, IDC_LIST_PAPER, m_listPaper);
	DDX_Control(pDX, IDC_COMBO_SUBJECT, m_comboSubject);
	DDX_Control(pDX, IDC_COMBO_CREATEPERSON, m_comboCreateperson);
	DDX_CBString(pDX, IDC_COMBO_CREATEPERSON, m_strCreateperson);
	DDX_CBString(pDX, IDC_COMBO_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Check(pDX, IDC_CHECK_DATE, m_checkDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManagePaperDlg, CDialog)
	//{{AFX_MSG_MAP(CManagePaperDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBJECT, OnSelchangeComboSubject)
	ON_BN_CLICKED(IDC_CHECK_DATE, OnCheckDate)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERYONLY, OnButtonQueryonly)
	ON_NOTIFY(NM_CLICK, IDC_TREE_PAPER, OnClickTreePaper)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PAPER, OnSelchangedTreePaper)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_EDITANSWER, OnButtonEditanswer)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PAPER, OnClickListPaper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagePaperDlg message handlers

BOOL CManagePaperDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;
	CString strPurview = parent->GetPurview();
	strUsername = parent->GetUsername();
	if(strPurview == "ϵͳ����Ա")
	{
		Purview = TRUE;
	}
	else
		Purview = FALSE;

	//��ʼ��List�ؼ�����Ŀ
	m_listPaper.InsertColumn(0,"�Ծ�ID",LVCFMT_LEFT,177,-1);
	m_listPaper.InsertColumn(1,"�Ծ���ʱ��",LVCFMT_LEFT,120,-1);
	m_listPaper.InsertColumn(2,"�Ծ�����",LVCFMT_LEFT,100,-1);
	m_listPaper.InsertColumn(3,"�Ծ�����",LVCFMT_LEFT,100,-1);
	m_listPaper.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_listQuestion.InsertColumn(0,"�Ծ�ID",LVCFMT_LEFT,167,-1);
	m_listQuestion.InsertColumn(1,"ID",LVCFMT_LEFT,100,-1);
	m_listQuestion.InsertColumn(2,"����",LVCFMT_LEFT,100,-1);
	m_listQuestion.InsertColumn(3,"�Ѷ�",LVCFMT_LEFT,60,-1);
	m_listQuestion.InsertColumn(4,"�����½�",LVCFMT_LEFT,70,-1);	
	m_listQuestion.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	InitComboSubject();
	
	//����Date Time Picker�ؼ���������ʾ��ʽ
	m_DateFrom.SetFormat("yyyyMMdd");
	m_DateTo.SetFormat("yyyyMMdd");
	//���ڲ�ѯ��ʼ��ʱ�ǲ�ѡ�еģ�������ʼ���ڵĿؼ�������
	m_checkDate = FALSE;
	m_DateFrom.EnableWindow(FALSE);
	m_DateTo.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//��ʼ��ѡ���Ŀcombo
BOOL CManagePaperDlg::InitComboSubject()
{
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;
	if(Purview)
	{
		CADORecordset* pTableRs;
		pTableRs = new CADORecordset(pDB); 
		CString strSQL = "select * from tbTableName order by ID";
		pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
		{
			CString strName;
			while(!(pTableRs->IsEOF()))
			{
				pTableRs->GetFieldValue("ChineseName",strName);
				int count = m_comboSubject.GetCount();
				m_comboSubject.InsertString(count,strName);
				pTableRs->MoveNext();
			}
			pTableRs->Close();
		}
		if(pTableRs)
			delete(pTableRs);
	}
	else
	{
		CString strSubject = parent->GetSubject();
		if(strSubject.IsEmpty())
			return FALSE;
		int len = strSubject.GetLength();
		int i = 0;
		while(i < len)
		{
			char c = strSubject.GetAt(i);
			char sub[20];
			int j = 0;
			while(c != ',' && i < len)
			{
				sub[j] = c;
				i++;
				j++;
				if(i < len)
					c = strSubject.GetAt(i);			
			}
			i++;
			sub[j] = '\0';
			CString strsub = sub;
			m_comboSubject.AddString(strsub);			
		}
	}
	return TRUE;
}

//��ʼ��������combo
BOOL CManagePaperDlg::InitComboCreate()
{
	int count = m_comboCreateperson.GetCount();
	for(int i = 0 ; i < count ; i++)
		m_comboCreateperson.DeleteString(0);
	m_comboCreateperson.AddString("");
	CString strChineseName = m_strSubject;
	CString Username;
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	CString strPurview = parent->GetPurview();
	if(Purview)
	{
		CString strPaperName = FindtbPaper(strChineseName);
		CADORecordset *pPaperRs = new CADORecordset(pDB);
		CString strSql;
		strSql.Format("select * from %s order by ID",strPaperName);
		pPaperRs->Open(strSql,CADORecordset.openQuery);
		if(pPaperRs->IsOpen() && pPaperRs->GetRecordCount() >=0)
		{
			while(!pPaperRs->IsEOF())
			{
				pPaperRs->GetFieldValue("������",Username);
				int n = m_comboCreateperson.FindString(0,Username);
				if(n == -1)
					m_comboCreateperson.AddString(Username);
				pPaperRs->MoveNext();				
			}
			pPaperRs->Close();
		}
		delete pPaperRs;

		CString strExistName = FindtbExist(strChineseName);
		CADORecordset *pExistRs = new CADORecordset(pDB);
		strSql.Format("select * from %s order by ������",strExistName);
		pExistRs->Open(strSql,CADORecordset.openQuery);
		if(pExistRs->IsOpen() && pExistRs->GetRecordCount() >=0)
		{
			while(!pExistRs->IsEOF())
			{
				pExistRs->GetFieldValue("������",Username);
				int n = m_comboCreateperson.FindString(0,Username);
				if(n == -1)
					m_comboCreateperson.AddString(Username);
				pExistRs->MoveNext();				
			}
			pExistRs->Close();
		}
		delete pExistRs;	
	}
	else
	{
		m_comboCreateperson.EnableWindow(FALSE);
	}
	return TRUE;
}


//�ҵ���������Ծ��tb��
CString CManagePaperDlg::FindtbPaper(CString strChineseName)
{
	CString strPaperName = "";
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s' order by ID",strChineseName);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{		
		pTableRs->GetFieldValue("PaperName",strPaperName);	
		pTableRs->Close();
	}
	if(pTableRs)
		delete(pTableRs);
	return strPaperName;
}

//�ҵ���ų����Ծ��tb��
CString CManagePaperDlg::FindtbExist(CString strChineseName)
{
	CString strExistName = "";
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s' order by ID",strChineseName);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{		
		pTableRs->GetFieldValue("ExistName",strExistName);	
		pTableRs->Close();
	}
	if(pTableRs)
		delete(pTableRs);
	return strExistName;
}

//��ʼ���Ծ��б�
BOOL CManagePaperDlg::InitPaperList()
{
	m_listPaper.DeleteAllItems();
	int indexofList = 0;
	CString strChineseName = m_strSubject;
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	//���������Ծ�
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	if(Purview)
		strSQL.Format("select * from %s order by ����ID",strPaperName);
	else
		strSQL.Format("select * from %s where ������='%s' order by ����ID",strPaperName,strUsername);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pPaperRs->IsOpen() && pPaperRs->GetRecordCount() > 0)
	{
		CString strID,strCreatetime,strCreateperson;
		while(!pPaperRs->IsEOF())
		{
			pPaperRs->GetFieldValue("ID",strID);
			pPaperRs->GetFieldValue("����ʱ��",strCreatetime);
			pPaperRs->GetFieldValue("������",strCreateperson);

			m_listPaper.InsertItem(indexofList,strID);
			m_listPaper.SetItemText(indexofList,1,strCreatetime);
			m_listPaper.SetItemText(indexofList,2,strCreateperson);
			m_listPaper.SetItemText(indexofList,3,"�����Ծ�");
			indexofList+=1;

			pPaperRs->MoveNext();
		}
		//��Ŀlist
		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);
		pPaperRs->Close();
	}
	else
		m_listQuestion.DeleteAllItems();
	if(pPaperRs)
		delete pPaperRs;

	//������׵�����Ծ�
	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	if(Purview)
		strSQL.Format("select * from %s order by ID",strExistName);
	else
		strSQL.Format("select * from %s where ������='%s' order by ID",strExistName,strUsername);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pExistRs->IsOpen() && pExistRs->GetRecordCount() > 0)
	{
		CString strID,strCreatetime,strCreateperson;
		while(!pExistRs->IsEOF())
		{
			pExistRs->GetFieldValue("ID",strID);
			pExistRs->GetFieldValue("����ʱ��",strCreatetime);
			pExistRs->GetFieldValue("������",strCreateperson);

			m_listPaper.InsertItem(indexofList,strID);
			m_listPaper.SetItemText(indexofList,1,strCreatetime);
			m_listPaper.SetItemText(indexofList,2,strCreateperson);
			m_listPaper.SetItemText(indexofList,3,"�����Ծ�");
			indexofList+=1;

			pExistRs->MoveNext();
		}
		pExistRs->Close();
	}
	if(pExistRs)
		delete pExistRs;

	//��ǰѡ�е��Ծ�
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
	}
	else
		Now_ID = "";

	m_listPaper.SetFocus();
	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
	return TRUE;
}

//��ʼ�������б�
BOOL CManagePaperDlg::InitPaperTree()
{
	m_paperTree.DeleteAllItems();
	CString strChineseName = m_strSubject;
	m_paperTree.ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|WS_BORDER);
	HTREEITEM hRoot = m_paperTree.InsertItem(_T(strChineseName),0,1);

	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s' order by ID",strChineseName);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{
		CString strEnglishName = "";
		CString strPaperName = "";
		CString strExistName = "";
		
		pTableRs->GetFieldValue("PaperName",strPaperName);
		pTableRs->GetFieldValue("ExistName",strExistName);
		
		HTREEITEM hItem1 = m_paperTree.InsertItem(_T("�����Ծ�"),0,1,hRoot,TVI_LAST);
		InsertPaperItem(hItem1,strPaperName);

		HTREEITEM hItem2 = m_paperTree.InsertItem(_T("�����Ծ�"),0,1,hRoot,TVI_LAST);
		InsertExistItem(hItem2,strExistName);
		
		m_paperTree.Expand(hItem1, TVE_EXPAND);
		m_paperTree.Expand(hItem2, TVE_EXPAND);
		
		
		m_paperTree.Expand(hRoot, TVE_EXPAND);
		pTableRs->Close();
		delete pTableRs;
		return TRUE;
	}
	if(pTableRs)
		delete pTableRs;
	return FALSE;
}

//�������б��в��������Ծ�
BOOL CManagePaperDlg::InsertPaperItem(HTREEITEM hItem,CString strPaperName)
{
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	if(Purview)
		strSQL.Format("select * from %s order by ����ID",strPaperName);
	else
		strSQL.Format("select * from %s where ������='%s' order by ����ID",strPaperName,strUsername);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pPaperRs->IsOpen() && pPaperRs->GetRecordCount() > 0)
	{
		CString last_ID = "";
		HTREEITEM hItem_child;
		CString strID,strfangID;
		while(!pPaperRs->IsEOF())
		{
			pPaperRs->GetFieldValue("����ID",strfangID);
			if(strfangID != last_ID)
			{ 
				hItem_child = m_paperTree.InsertItem(_T(strfangID),0,1,hItem,TVI_LAST);
			}
			last_ID = strfangID;
			pPaperRs->GetFieldValue("ID",strID);
			m_paperTree.InsertItem(_T(strID),0,1,hItem_child,TVI_LAST);
			pPaperRs->MoveNext();
		}
		pPaperRs->Close();
		delete pPaperRs;
		return TRUE;
	}
	if(pPaperRs)
		delete pPaperRs;
	return FALSE;
}

//�������б��в�������Ծ�
BOOL CManagePaperDlg::InsertExistItem(HTREEITEM hItem,CString strExistName)
{
	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	CString strSQL;
	if(Purview)
		strSQL.Format("select * from %s order by ID",strExistName);
	else
		strSQL.Format("select * from %s where ������='%s' order by ID",strExistName,strUsername);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pExistRs->IsOpen() && pExistRs->GetRecordCount() > 0)
	{
		CString strID;
		while(!pExistRs->IsEOF())
		{
			pExistRs->GetFieldValue("ID",strID);
			m_paperTree.InsertItem(_T(strID),0,1,hItem,TVI_LAST);
			pExistRs->MoveNext();
		}
		pExistRs->Close();
		delete pExistRs;	
		return TRUE;
	}
	if(pExistRs)
		delete pExistRs;
	return FALSE;
}

//ѡ���Ŀ�����仯
void CManagePaperDlg::OnSelchangeComboSubject() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_listPaper.DeleteAllItems();
	m_listQuestion.DeleteAllItems();
	InitPaperList();
	InitPaperTree();
	InitComboCreate();
}

//����List�ؼ�,����¼�Ƶ���һ��  +++++++++++�����������б�����++++++++++
void CManagePaperDlg::RefreshList(BOOL PaperOrExist,CADORecordset& recordset) 
{	
	CString strType;
	if(PaperOrExist)
		strType = "�����Ծ�";
	else
		strType = "�����Ծ�";
	if(!recordset.IsOpen())
	{
		Now_ID = "";
		return;
	}
	if(recordset.GetRecordCount() <= 0)
	{
		Now_ID = "";
		return;
	}
	recordset.MoveFirst();
	CString strID,strCreatetime,strCreateperson;
	int indexofList=0;
	
	while(!(recordset.IsEOF()))
	{
		recordset.GetFieldValue("ID",strID);
		recordset.GetFieldValue("����ʱ��",strCreatetime);
		recordset.GetFieldValue("������",strCreateperson);

		m_listPaper.InsertItem(indexofList,strID);
		m_listPaper.SetItemText(indexofList,1,strCreatetime);
		m_listPaper.SetItemText(indexofList,2,strCreateperson);
		m_listPaper.SetItemText(indexofList,3,strType);
		indexofList+=1;
		recordset.MoveNext();
	}
	recordset.MoveFirst();

	//��ǰѡ�е��Ծ�
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
	}
	else
		Now_ID = "";
}

//����ѡ��仯
void CManagePaperDlg::OnSelchangedTreePaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString strChineseName = m_strSubject;
	HTREEITEM hItem = m_paperTree.GetSelectedItem();
	if(m_paperTree.GetItemText(hItem) == strChineseName)
	{
		InitPaperList();
		return;
	}
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	
	m_listPaper.DeleteAllItems();

	if(m_paperTree.GetItemText(hItem) == "�����Ծ�")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s order by ����ID",strPaperName);
		else
			strSQL.Format("select * from %s where ������='%s' order by ����ID",strPaperName,strUsername);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hItem) == "�����Ծ�")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s order by ID",strExistName);
		else
			strSQL.Format("select * from %s where ������='%s' order by ID",strExistName,strUsername);
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();
		
		*pResult = 0;
		return;
	}
	HTREEITEM hParent = m_paperTree.GetParentItem(hItem);
	if(m_paperTree.GetItemText(hParent) == "�����Ծ�")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strExistName,m_paperTree.GetItemText(hItem));
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();

		*pResult = 0;
		return;
	}
	HTREEITEM hpParent = m_paperTree.GetParentItem(hParent);
	if(m_paperTree.GetItemText(hpParent) == strChineseName)
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s where ����ID='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem));
		else
			strSQL.Format("select * from %s where ����ID='%s' and ������='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem),strUsername);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hpParent) == "�����Ծ�")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strPaperName,m_paperTree.GetItemText(hItem));
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	*pResult = 0;
}

void CManagePaperDlg::OnCheckDate() 
{
	// TODO: Add your control notification handler code here
	if(m_checkDate == FALSE)
	{
		m_checkDate = TRUE;
		m_DateFrom.EnableWindow(TRUE);
		m_DateTo.EnableWindow(TRUE);
	}
	else
	{
		m_checkDate = FALSE;
		m_DateFrom.EnableWindow(FALSE);
		m_DateTo.EnableWindow(FALSE);
	}	
}

//������ѯ
void CManagePaperDlg::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strChineseName = m_strSubject;
	if(strChineseName.IsEmpty())
		return;
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	CString strDateFrom,strDateTo;
	CString strSQL1,strSQL2,temp;
	//��û��ѡ���κβ�ѯ���������ѯ���м�¼
	if((!m_checkDate) && (m_strCreateperson.IsEmpty()))
	{
		strSQL1.Format("select * from %s",strPaperName);
		strSQL2.Format("select * from %s",strExistName);
	}
	else 
	{
		strSQL1.Format("select * from %s where",strPaperName);
		strSQL2.Format("select * from %s where",strExistName);
	}

	//���ѡ�����ڲ�ѯ���������ڿؼ����ַ�����������Ϣ
	if(m_checkDate)
	{
		CTime timeFrom,timeTo;
		m_DateFrom.GetTime(timeFrom);
		m_DateTo.GetTime(timeTo);
		m_DateFrom.GetWindowText(strDateFrom);
		m_DateTo.GetWindowText(strDateTo);
		//�ж�ʱ��ֵ����Ч��
		if(timeFrom.GetYear() > timeTo.GetYear())
		{
			MessageBox("Date set is wrong!");
			return;
		}
		else if(timeFrom.GetYear() == timeTo.GetYear())
		{
			if(timeFrom.GetMonth() > timeTo.GetMonth())
			{
				MessageBox("Date set is wrong!");
				return;
			}
			else if(timeFrom.GetMonth() == timeTo.GetMonth())
			{
				if(timeFrom.GetDay() > timeTo.GetDay())
				{
					MessageBox("Date set is wrong!");
					return;
				}
			}
		}
		temp.Format(" ����ʱ��>='%s' and ����ʱ��<='%s'",strDateFrom,strDateTo);
		strSQL1 += temp;
		strSQL2 += temp;
	}
	//����û������˴������˵���������Ҫ��SQL�м��������
	if(!m_strCreateperson.IsEmpty())
	{
		if(m_checkDate)
			temp.Format(" and ������='%s'",m_strCreateperson);
		else
			temp.Format(" ������='%s'",m_strCreateperson);
		strSQL1 += temp;
		strSQL2 += temp;
	}
	else
	{
		if(!Purview)
		{
			if(m_checkDate)
				temp.Format(" and ������='%s'",strUsername);
			else
				temp.Format(" ������='%s'",strUsername);
			strSQL1 += temp;
		    strSQL2 += temp;
		}
	}
	m_listPaper.DeleteAllItems();

	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	pExistRs->Open(_bstr_t(strSQL2),CADORecordset.openQuery);
	RefreshList(FALSE,*pExistRs);
	pExistRs->Close();
	delete pExistRs;

	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	pPaperRs->Open(_bstr_t(strSQL1),CADORecordset.openQuery);
	RefreshList(TRUE,*pPaperRs);

	m_listQuestion.DeleteAllItems();
	UpdateQuestionList(*pPaperRs);

	pPaperRs->Close();
	delete pPaperRs;

	//��ǰѡ�е��Ծ�
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
		if(Now_ID.GetLength() % 2)
			m_listQuestion.DeleteAllItems();
	}
	else
	{
		m_listQuestion.DeleteAllItems();
		Now_ID = "";
	}

	m_listPaper.SetFocus();
	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
}

//��ȷ��ѯ
void CManagePaperDlg::OnButtonQueryonly() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strChineseName = m_strSubject;
	if(strChineseName.IsEmpty())
		return;
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	m_listPaper.DeleteAllItems();
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	if(Purview)
		strSQL.Format("select * from %s where ID='%s'",strPaperName,m_strID);
	else
		strSQL.Format("select * from %s where ID='%s'and ������='%s'",strPaperName,m_strID,strUsername);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	RefreshList(TRUE,*pPaperRs);

	m_listQuestion.DeleteAllItems();
	UpdateQuestionList(*pPaperRs);

	pPaperRs->Close();
	delete pPaperRs;

	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	if(Purview)
		strSQL.Format("select * from %s where ID='%s'",strExistName,m_strID);
	else
		strSQL.Format("select * from %s where ID='%s' and ������='%s'",strExistName,m_strID,strUsername);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	RefreshList(FALSE,*pExistRs);
	pExistRs->Close();
	delete pExistRs;

	//��ǰѡ�е��Ծ�
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
		if(Now_ID.GetLength() % 2)
			m_listQuestion.DeleteAllItems();
	}
	else
	{
		m_listQuestion.DeleteAllItems();
		Now_ID = "";
	}
	m_listPaper.SetFocus();
	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
}

//ѡ�����οؼ�
void CManagePaperDlg::OnClickTreePaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
/*	CString strChineseName = m_strSubject;
	HTREEITEM hItem = m_paperTree.GetSelectedItem();
	if(!hItem)
	{
		Now_ID = "";
		return;
	}
	if(m_paperTree.GetItemText(hItem) == strChineseName)
	{
		InitPaperList();
		return;
	}
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);

	m_listPaper.DeleteAllItems();

	if(m_paperTree.GetItemText(hItem) == "�����Ծ�")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s order by ����ID",strPaperName);
		else
			strSQL.Format("select * from %s where ������='%s' order by ����ID",strPaperName,strUsername);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hItem) == "�����Ծ�")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s order by ID",strExistName);
		else
			strSQL.Format("select * from %s where ������='%s' order by ID",strExistName,strUsername);
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;
		*pResult = 0;
		return;
	}
	HTREEITEM hParent = m_paperTree.GetParentItem(hItem);
	if(m_paperTree.GetItemText(hParent) == "�����Ծ�")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strExistName,m_paperTree.GetItemText(hItem));
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;
		*pResult = 0;
		return;
	}
	HTREEITEM hpParent = m_paperTree.GetParentItem(hParent);
	if(m_paperTree.GetItemText(hpParent) == strChineseName)
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s where ����ID='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem));
		else
			strSQL.Format("select * from %s where ����ID='%s' and ������='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem),strUsername);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
     	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hpParent) == "�����Ծ�")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strPaperName,m_paperTree.GetItemText(hItem));
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
    	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}*/
    CString strChineseName = m_strSubject;
	if(strChineseName.IsEmpty())
		return;
	HTREEITEM hItem = m_paperTree.GetSelectedItem();
	if(m_paperTree.GetItemText(hItem) == strChineseName)
	{
		InitPaperList();
		return;
	}
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	
	m_listPaper.DeleteAllItems();

	if(m_paperTree.GetItemText(hItem) == "�����Ծ�")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s order by ����ID",strPaperName);
		else
			strSQL.Format("select * from %s where ������='%s' order by ����ID",strPaperName,strUsername);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hItem) == "�����Ծ�")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s order by ID",strExistName);
		else
			strSQL.Format("select * from %s where ������='%s' order by ID",strExistName,strUsername);
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();
		
		*pResult = 0;
		return;
	}
	HTREEITEM hParent = m_paperTree.GetParentItem(hItem);
	if(m_paperTree.GetItemText(hParent) == "�����Ծ�")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strExistName,m_paperTree.GetItemText(hItem));
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();

		*pResult = 0;
		return;
	}
	HTREEITEM hpParent = m_paperTree.GetParentItem(hParent);
	if(m_paperTree.GetItemText(hpParent) == strChineseName)
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		if(Purview)
			strSQL.Format("select * from %s where ����ID='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem));
		else
			strSQL.Format("select * from %s where ����ID='%s' and ������='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem),strUsername);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hpParent) == "�����Ծ�")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strPaperName,m_paperTree.GetItemText(hItem));
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	*pResult = 0;
}

void CManagePaperDlg::UpdateOthers(BOOL PaperOrExist,CString old_id)
{
	CString strChineseName = m_strSubject;
	if(PaperOrExist)
	{
		int len = old_id.GetLength();
		char fanganID[50]; 
		for(int i = 0 ; i < len-4 ; i++)
		{
			fanganID[i] = old_id.GetAt(i);
		}
		fanganID[i] = '\0';
		char no[5];
		int j = 0;
		for(i = len-4 ; i < len ; i++)
		{
			no[j] = old_id.GetAt(i);
			j++;
		}
		no[j] = '\0';
		CString old_no = no;
		int id_no = atoi(old_no);

		CString strfanganID = fanganID;
		CString strPaperName = FindtbPaper(strChineseName);
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ����ID='%s' order by ID",strPaperName,strfanganID);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		
			
		CString strID;
		if(pPaperRs->IsOpen() && pPaperRs->GetRecordCount() > 0)
		{	
			pPaperRs->MoveFirst();
			while(!(pPaperRs->IsEOF()))
			{	
				pPaperRs->GetFieldValue("ID",strID);
				len = strID.GetLength();
				j = 0;
				for(i = len-4 ; i < len ; i++)
				{
					no[j] = strID.GetAt(i);
					j++;
				}
				no[j] = '\0';
				CString new_no = no;
				int r_id = atol(new_no);
				
				if(r_id > id_no)
				{	
					r_id--;
					strID.Format(_T("%ld"),r_id);
					len = strID.GetLength();
					CString temp = "";
					for(i = 0 ; i < 4-len ; i++)
						temp += "0";
					temp += strID;
					strID = strfanganID;
					strID += temp;
					pPaperRs->SetFieldValue("ID",strID);
					pPaperRs->Update();
				}
				pPaperRs->MoveNext();
			}
			pPaperRs->Close();
		}
		delete pPaperRs;	
	}
	else
	{
		CString strExistName = FindtbExist(strChineseName);
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB);
		CString strSQL;
		strSQL.Format("select * from %s order by ID",strExistName);
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		
		long id = atol(old_id);	
		CString strID;
		if(pExistRs->IsOpen() && pExistRs->GetRecordCount() > 0)
		{	
			pExistRs->MoveFirst();
			while(!(pExistRs->IsEOF()))
			{			
				pExistRs->GetFieldValue("ID",strID);
				long r_id = atol(strID);
				
				if(r_id > id)
				{	
					r_id--;
					strID.Format(_T("%ld"),r_id);
					int len = strID.GetLength();
					CString temp = "";
					for(int i = 0 ; i < 5-len ; i++)
					{
						temp += "0";
					}
					temp += strID;
					strID = temp;
					pExistRs->SetFieldValue("ID",strID);
					pExistRs->Update();
				}
				pExistRs->MoveNext();
			}
			pExistRs->Close();
		}
		delete pExistRs;
	}
}

void CManagePaperDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
/*	int sel=m_listPaper.GetSelectionMark();
	if(sel<0)
	{
		MessageBox("û��ѡ��ɾ�����Ծ�!");
		return;
	}
	CString strID = m_listPaper.GetItemText(sel,0);
	CString strType = m_listPaper.GetItemText(sel,3);*/
	CString strID = Now_ID;
	if(strID.IsEmpty())
		return;
	CString strType;
	if(strID.GetLength() % 2)
		strType = "�����Ծ�";
	else
		strType = "�����Ծ�";
	
	CString strChineseName = m_strSubject;
	CString strTableName;
	BOOL PaperOrExist;
	if(strType == "�����Ծ�")
	{
		strTableName = FindtbPaper(strChineseName);
		PaperOrExist = TRUE;
	}
	else
	{
		strTableName = FindtbExist(strChineseName);
		PaperOrExist = FALSE;
	}

	CString strdelete = "Ҫɾ��No.";
	strdelete += strID;
	strdelete += "�Ծ�?";
	if(MessageBox(strdelete,"ȷ��ɾ��",MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
		return;	
	try
	{
		pDB->BeginTransaction();
		CString strSQL;
		strSQL.Format("delete from %s where ID='%s'",strTableName,strID);
		pDB->Execute(strSQL);
		UpdateOthers(PaperOrExist,strID);
		pDB->CommitTransaction();
		InitPaperTree();
		InitPaperList();
	}
	catch(_com_error e)
	{
		pDB->RollbackTransaction();
		AfxMessageBox(e.ErrorMessage());
	}
}

void CManagePaperDlg::OnButtonBrowse() 
{
	// TODO: Add your control notification handler code here
	CBrowsePaperDlg browsepaperDlg;
/*	int sel = m_listPaper.GetSelectionMark();
	if(sel < 0)
		return;
	CString strID = m_listPaper.GetItemText(sel,0);
	CString strType = m_listPaper.GetItemText(sel,3);*/
	CString strID = Now_ID;
	if(strID.IsEmpty())
		return;
	CString strType;
	if(strID.GetLength() % 2)
		strType = "�����Ծ�";
	else
		strType = "�����Ծ�";
	CString strContent;
	
	CString strChineseName = m_strSubject;
	CString strTableName;
	if(strType == "�����Ծ�")
		strTableName = FindtbPaper(strChineseName);
	else
		strTableName = FindtbExist(strChineseName);
	
	CADORecordset *pRs = new CADORecordset(pDB);
	CString strSql;
	strSql.Format("select * from %s where ID='%s'",strTableName,strID);
	pRs->Open(_bstr_t(strSql),CADORecordset.openQuery);
	if(pRs->IsOpen())
	{
		pRs->GetFieldValue("����",strContent);
		browsepaperDlg.m_strTitle = "�Ծ�ID��";
		browsepaperDlg.m_strTitle += strID;
		browsepaperDlg.m_strPaper = strContent;
		browsepaperDlg.strID = strID;

		browsepaperDlg.DoModal();
		pRs->Close();
	}
	delete pRs;
}

void CManagePaperDlg::OnButtonEditanswer() 
{
	// TODO: Add your control notification handler code here
	CEditAnswerDlg editanswerDlg;
/*	int sel = m_listPaper.GetSelectionMark();
	if(sel < 0)
		return;
	CString strID = m_listPaper.GetItemText(sel,0);
	CString strType = m_listPaper.GetItemText(sel,3);*/
	CString strID = Now_ID;
	if(strID.IsEmpty())
		return;
	CString strType;
	if(strID.GetLength() % 2)
		strType = "�����Ծ�";
	else
		strType = "�����Ծ�";

	CString strAnswer,strPaper;
	
	CString strChineseName = m_strSubject;
	CString strTableName;
	if(strType == "�����Ծ�")
		strTableName = FindtbPaper(strChineseName);
	else
		strTableName = FindtbExist(strChineseName);
	
	CADORecordset *pRs = new CADORecordset(pDB);
	CString strSql;
	strSql.Format("select * from %s where ID='%s'",strTableName,strID);
	pRs->Open(_bstr_t(strSql),CADORecordset.openQuery);
	if(pRs->IsOpen())
	{
		pRs->GetFieldValue("��",strAnswer);
		pRs->GetFieldValue("����",strPaper);
		editanswerDlg.m_strTitle = "�Ծ�ID��";
		editanswerDlg.m_strTitle += strID;
		editanswerDlg.m_strTitle += "��";
		editanswerDlg.m_strTitilePaper = "�Ծ�ID��";
		editanswerDlg.m_strTitilePaper += strID;
		editanswerDlg.m_strTitilePaper += "��������";
		editanswerDlg.m_strAnswer = strAnswer;
		editanswerDlg.m_strPaper = strPaper;
		editanswerDlg.strID = strID;
		
		if(editanswerDlg.DoModal() == IDOK)
		{
			pRs->SetFieldValue("��",editanswerDlg.m_strAnswer);
			pRs->Update();
		}		
		pRs->Close();
	}
	delete pRs;	
}

//��������
CString CManagePaperDlg::FindType(CString type)
{
	CString strType = "";
	CADORecordset* pTypeRs;
	pTypeRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbType where ID='%s'",type);
	pTypeRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTypeRs->IsOpen() && pTypeRs->GetRecordCount() > 0)
	{
		pTypeRs->GetFieldValue("Name",strType);
		pTypeRs->Close();
	}
	if(pTypeRs)
		delete(pTypeRs);
	return strType;
}

//�����Ѷ�
CString CManagePaperDlg::FindDifficulty(CString Difficulty)
{
	CString strDifficulty = "";
	if(Difficulty == "00")
		return strDifficulty;
	else
	{
		int i = atoi(Difficulty);
		strDifficulty = paperDifficulty_Chinese[i-1];
		return strDifficulty;
	}
}

//�����½�
CString CManagePaperDlg::FindChapter(CString Chapter)
{
	CString strChapter = "";
	if(Chapter == "00")
		return strChapter;
	else
	{
		strChapter = "��";
		strChapter += Chapter;
		strChapter += "��";
		return strChapter;
	}
}

void CManagePaperDlg::UpdateQuestionList(CADORecordset &recordset)
{
	if(!recordset.IsOpen())
		return;
	if(recordset.GetRecordCount() <= 0)
		return;
	recordset.MoveFirst();
	CString strID,strQuesID;
	int indexofList=0;
	
	recordset.GetFieldValue("ID",strID);
	recordset.GetFieldValue("��ĿID",strQuesID);

	int len = strQuesID.GetLength();
	int i = 0;
	while(i < len)
	{
		char quesID[12];
		int j = 0;
		char c;
		do
		{
			c = strQuesID.GetAt(i);
			if(c != ',')
				quesID[j] = c;
			i++;
			j++;
		}while(i < len && c != ',');
		quesID[j] = '\0';
	//	i++;

		CString strNowID = quesID;
		char type[3];
		type[0] = quesID[0];
		type[1] = quesID[1];
		type[2] = '\0';
		CString Type = type;
		CString strType = FindType(Type);

		char difficulty[3];
		difficulty[0] = quesID[2];
		difficulty[1] = quesID[3];
		difficulty[2] = '\0';
		CString Difficulty = difficulty;
		CString strDifficulty = FindDifficulty(Difficulty);

		char chapter[3];
		chapter[0] = quesID[4];
		chapter[1] = quesID[5];
		chapter[2] = '\0';
		CString Chapter = chapter;
		CString strChapter = FindChapter(Chapter);

		m_listQuestion.InsertItem(indexofList,strID);
		m_listQuestion.SetItemText(indexofList,1,strNowID);
		m_listQuestion.SetItemText(indexofList,2,strType);
        m_listQuestion.SetItemText(indexofList,3,strDifficulty);
		m_listQuestion.SetItemText(indexofList,4,strChapter);
		indexofList+=1;
	}
}
/*
void CManagePaperDlg::OnSetfocusListPaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_listQuestion.DeleteAllItems();
	int nItem = m_listPaper.GetSelectedCount();
	char ID[100],Type[10];
	m_listPaper.GetItemText(nItem,0,ID,100);
	m_listPaper.GetItemText(nItem,3,Type,10);
	CString strID = ID;
	CString strType = Type;
	Now_ID = strID;
	if(strType == "�����Ծ�")
	{
		CString strChineseName = m_strSubject;
		CString strPaperName = FindtbPaper(strChineseName);

		CADORecordset *pPaperRs = new CADORecordset(pDB);
		CString strSql;
		strSql.Format("select * from %s where ID='%s'",strPaperName,strID);
		pPaperRs->Open(_bstr_t(strSql),CADORecordset.openQuery);
		if(pPaperRs->IsOpen())
		{
			UpdateQuestionList(*pPaperRs);
			pPaperRs->Close();
		}
		delete pPaperRs;
	}
	*pResult = 0;
}*/

void CManagePaperDlg::OnClickListPaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_listQuestion.DeleteAllItems();
	int sel = m_listPaper.GetSelectionMark();
	if(sel<0)
	{
		Now_ID = "";
		return;
	}
	CString strID = m_listPaper.GetItemText(sel,0);
	CString strType = m_listPaper.GetItemText(sel,3);
	//��ǰѡ�е��Ծ�
	Now_ID = strID;

	if(strType == "�����Ծ�")
	{
		CString strChineseName = m_strSubject;
		CString strPaperName = FindtbPaper(strChineseName);

		CADORecordset *pPaperRs = new CADORecordset(pDB);
		CString strSql;
		strSql.Format("select * from %s where ID='%s'",strPaperName,strID);
		pPaperRs->Open(_bstr_t(strSql),CADORecordset.openQuery);
		if(pPaperRs->IsOpen())
		{
			UpdateQuestionList(*pPaperRs);
			pPaperRs->Close();
		}
		delete pPaperRs;
	}
	*pResult = 0;
}

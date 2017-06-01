// AutoMakeupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "AutoMakeupDlg.h"
#include "ManageAllDlg.h"
#include "SelChapAndDiffDlg.h"
#include "time.h"
#include "msword.h"
#include <AtlBase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoMakeupDlg dialog
CString Number_Chinese[10] = {"һ","��","��","��","��","��","��","��","��","ʮ"};
//����ȫ�ֱ���
CString autoDifficulty_Chinese[5] = {"��","����","�е�","����","��"};
CString autoChapter_Chinese[30] = {"��01��","��02��","��03��","��04��","��05��","��06��","��07��","��08��","��09��","��10��",
"��11��","��12��","��13��","��14��","��15��","��16��","��17��","��18��","��19��","��20��",
"��21��","��22��","��23��","��24��","��25��","��26��","��27��","��28��","��29��","��30��"};

CAutoMakeupDlg::CAutoMakeupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoMakeupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoMakeupDlg)
	m_nNumber = -1;
	m_strSubject = _T("");
	m_strPaper = _T("");
	m_strAnswer = _T("");
	m_nAllscore = 0;
	//}}AFX_DATA_INIT
	//��ֵ��Ϊ0���
	for(int i = 0 ; i < 10 ; i++)
	{
		m_str[i] = _T("");
		m_nCount[i] = 0;
        m_nScore[i] = 0;
		strSelChap[i] = _T("");
		strSelDiff[i] = _T("");
		nSelChap[i] = 0;
	    nSelDiff[i] = 0;
	}
	for(i = 0 ; i < 30 ; i++)
	{
		Chapter_all[i] = "";
		EveryChapNum[i] = 0;
	}
	for(i = 0 ; i < 5 ; i++)
	{
		Difficulty_all[i] = "";
	    EveryDiffNum[i] = 0;
	}
	for(i = 0 ; i < 10 ; i++)
	{
		for(int j = 0 ; j < 30 ; j++)
			Chapter_num[i][j] = 0;

		for(j = 0 ; j < 5 ; j++)
			Difficulty_num[i][j]= 0;
	}
	strPaperName = "";
	nButtonOther_index = -1;

	newPaper.FanganID = "";
	newPaper.ID = "";
	newPaper.QuestionID = "";
	newPaper.QuestionScore = "";
	newPaper.QuestionAnswer = "";
	newPaper.Content = "";
	newPaper.Answer = "";
	newPaper.Username = "";
	newPaper.Date = "";

	Purview = FALSE;
}

CAutoMakeupDlg::~CAutoMakeupDlg()
{
	//�رռ�¼��
	if(pRs && pRs->IsOpen())
		pRs->Close();
	if(pRs)
		delete(pRs);
}

void CAutoMakeupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoMakeupDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER_CREATE, m_DateTimeCreate);
	DDX_Control(pDX, IDC_EDIT_SCORE, m_editAllscore);
	DDX_Control(pDX, IDC_EDIT_ANSWER, m_editAnswer);
	DDX_Control(pDX, IDC_BUTTON_OUTANSWER, m_buttonOutAnswer);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_buttonOut);
	DDX_Control(pDX, IDC_BUTTON_START, m_buttonStart);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_buttonSelect);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_buttonReset);
	DDX_Control(pDX, IDC_EDIT_PAPER, m_editPaper);
	DDX_Control(pDX, IDC_COMBO_SUBJECT, m_comboSubject);
	DDX_Control(pDX, IDC_COMBO_NUMBER, m_comboNumber);
	DDX_CBIndex(pDX, IDC_COMBO_NUMBER, m_nNumber);
	DDX_CBString(pDX, IDC_COMBO_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_PAPER, m_strPaper);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_strAnswer);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_nAllscore);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_COUNT1, m_nCount[0]);
	DDX_Text(pDX, IDC_EDIT_COUNT10, m_nCount[9]);
	DDX_Text(pDX, IDC_EDIT_COUNT2, m_nCount[1]);
	DDX_Text(pDX, IDC_EDIT_COUNT3, m_nCount[2]);
	DDX_Text(pDX, IDC_EDIT_COUNT4, m_nCount[3]);
	DDX_Text(pDX, IDC_EDIT_COUNT5, m_nCount[4]);
	DDX_Text(pDX, IDC_EDIT_COUNT6, m_nCount[5]);
	DDX_Text(pDX, IDC_EDIT_COUNT7, m_nCount[6]);
	DDX_Text(pDX, IDC_EDIT_COUNT8, m_nCount[7]);
	DDX_Text(pDX, IDC_EDIT_COUNT9, m_nCount[8]);
	DDX_Text(pDX, IDC_EDIT_SCORE1, m_nScore[0]);
	DDX_Text(pDX, IDC_EDIT_SCORE10, m_nScore[9]);
	DDX_Text(pDX, IDC_EDIT_SCORE2, m_nScore[1]);
	DDX_Text(pDX, IDC_EDIT_SCORE3, m_nScore[2]);
	DDX_Text(pDX, IDC_EDIT_SCORE4, m_nScore[3]);
	DDX_Text(pDX, IDC_EDIT_SCORE5, m_nScore[4]);
	DDX_Text(pDX, IDC_EDIT_SCORE6, m_nScore[5]);
	DDX_Text(pDX, IDC_EDIT_SCORE7, m_nScore[6]);
	DDX_Text(pDX, IDC_EDIT_SCORE8, m_nScore[7]);
	DDX_Text(pDX, IDC_EDIT_SCORE9, m_nScore[8]);
	DDX_CBString(pDX, IDC_COMBO_NO1, m_str[0]);
	DDX_CBString(pDX, IDC_COMBO_NO10, m_str[9]);
	DDX_CBString(pDX, IDC_COMBO_NO2, m_str[1]);
	DDX_CBString(pDX, IDC_COMBO_NO3, m_str[2]);
	DDX_CBString(pDX, IDC_COMBO_NO4, m_str[3]);
	DDX_CBString(pDX, IDC_COMBO_NO5, m_str[4]);
	DDX_CBString(pDX, IDC_COMBO_NO6, m_str[5]);
	DDX_CBString(pDX, IDC_COMBO_NO7, m_str[6]);
	DDX_CBString(pDX, IDC_COMBO_NO8, m_str[7]);
	DDX_CBString(pDX, IDC_COMBO_NO9, m_str[8]);
	DDX_Control(pDX, IDC_COMBO_NO9, m_combo[8]);
	DDX_Control(pDX, IDC_COMBO_NO8, m_combo[7]);
	DDX_Control(pDX, IDC_COMBO_NO7, m_combo[6]);
	DDX_Control(pDX, IDC_COMBO_NO6, m_combo[5]);
	DDX_Control(pDX, IDC_COMBO_NO5, m_combo[4]);
	DDX_Control(pDX, IDC_COMBO_NO4, m_combo[3]);
	DDX_Control(pDX, IDC_COMBO_NO3, m_combo[2]);
	DDX_Control(pDX, IDC_COMBO_NO2, m_combo[1]);
	DDX_Control(pDX, IDC_COMBO_NO10, m_combo[9]);
	DDX_Control(pDX, IDC_COMBO_NO1, m_combo[0]);
	DDX_Control(pDX, IDC_BUTTON_OTHER9, m_buttonOther[8]);
	DDX_Control(pDX, IDC_BUTTON_OTHER8, m_buttonOther[7]);
	DDX_Control(pDX, IDC_BUTTON_OTHER7, m_buttonOther[6]);
	DDX_Control(pDX, IDC_BUTTON_OTHER6, m_buttonOther[5]);
	DDX_Control(pDX, IDC_BUTTON_OTHER5, m_buttonOther[4]);
	DDX_Control(pDX, IDC_BUTTON_OTHER4, m_buttonOther[3]);
	DDX_Control(pDX, IDC_BUTTON_OTHER3, m_buttonOther[2]);
	DDX_Control(pDX, IDC_BUTTON_OTHER2, m_buttonOther[1]);
	DDX_Control(pDX, IDC_BUTTON_OTHER10, m_buttonOther[9]);
	DDX_Control(pDX, IDC_BUTTON_OTHER1, m_buttonOther[0]);	
	DDX_Control(pDX, IDC_EDIT_COUNT1, m_editCount[0]);
	DDX_Control(pDX, IDC_EDIT_COUNT10, m_editCount[9]);
	DDX_Control(pDX, IDC_EDIT_COUNT2, m_editCount[1]);
	DDX_Control(pDX, IDC_EDIT_COUNT3, m_editCount[2]);
	DDX_Control(pDX, IDC_EDIT_COUNT4, m_editCount[3]);
	DDX_Control(pDX, IDC_EDIT_COUNT5, m_editCount[4]);
	DDX_Control(pDX, IDC_EDIT_COUNT6, m_editCount[5]);
	DDX_Control(pDX, IDC_EDIT_COUNT7, m_editCount[6]);
    DDX_Control(pDX, IDC_EDIT_COUNT8, m_editCount[7]);
	DDX_Control(pDX, IDC_EDIT_COUNT9, m_editCount[8]);
	DDX_Control(pDX, IDC_EDIT_SCORE1, m_editScore[0]);
	DDX_Control(pDX, IDC_EDIT_SCORE10, m_editScore[9]);
	DDX_Control(pDX, IDC_EDIT_SCORE2, m_editScore[1]);
	DDX_Control(pDX, IDC_EDIT_SCORE3, m_editScore[2]);
	DDX_Control(pDX, IDC_EDIT_SCORE4, m_editScore[3]);
	DDX_Control(pDX, IDC_EDIT_SCORE5, m_editScore[4]);
	DDX_Control(pDX, IDC_EDIT_SCORE6, m_editScore[5]);
	DDX_Control(pDX, IDC_EDIT_SCORE7, m_editScore[6]);
	DDX_Control(pDX, IDC_EDIT_SCORE8, m_editScore[7]);
	DDX_Control(pDX, IDC_EDIT_SCORE9, m_editScore[8]);
}


BEGIN_MESSAGE_MAP(CAutoMakeupDlg, CDialog)
	//{{AFX_MSG_MAP(CAutoMakeupDlg)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnButtonOut)
	ON_CBN_SELCHANGE(IDC_COMBO_NUMBER, OnSelchangeComboNumber)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_OUTANSWER, OnButtonOutanswer)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_OTHER1, IDC_BUTTON_OTHER10, OnButtonOther)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoMakeupDlg message handlers

BOOL CAutoMakeupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;
	pRs = new CADORecordset(pDB);
	CString strPurview = parent->GetPurview();
	if(strPurview == "ϵͳ����Ա")
	{
		Purview = TRUE;
	}
	else
		Purview = FALSE;

	//��ʼ��Combo�ؼ�
	InitComboSubject();

	//��ʼ��״̬
	for(int i = 0 ; i < 10 ; i++)
	{
		m_buttonOther[i].EnableWindow(FALSE);
		m_editCount[i].EnableWindow(FALSE);
		m_editScore[i].EnableWindow(FALSE);
		m_combo[i].EnableWindow(FALSE);
	}
	m_buttonReset.EnableWindow(FALSE);
	m_comboNumber.EnableWindow(FALSE);
	m_editAllscore.EnableWindow(FALSE);
	m_DateTimeCreate.EnableWindow(FALSE);
	m_buttonStart.EnableWindow(FALSE);
	m_buttonOut.EnableWindow(FALSE);
	m_buttonOutAnswer.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CAutoMakeupDlg::GetTableName()
{
	return Table_name;
}

//ÿ��ѡ�п�Ŀ֮���ʼ�����Ϳؼ�
BOOL CAutoMakeupDlg::InitCombo()
{
	if(pRs->IsOpen() && pRs->GetRecordCount() > 0)
	{
		CString strType = "";
		CString oldType = "";
		while(!pRs->IsEOF())
		{			
			pRs->GetFieldValue("Type",strType);
			if(strType != oldType)
			{
				for(int i = 0 ; i < 10 ; i++)
					m_combo[i].AddString(strType);
			}
			oldType = strType;
			pRs->MoveNext();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CAutoMakeupDlg::InitComboSubject()
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

//���ұ�(������Ƿ����)
CString CAutoMakeupDlg::FindTable()
{
	UpdateData(TRUE);
	
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where Chinesename='%s'",m_strSubject);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	
	CString strEnglishName = "";
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{
		pTableRs->GetFieldValue("EnglishName",strEnglishName);
		pTableRs->GetFieldValue("PaperName",strPaperName);
		pTableRs->Close();
	}
	if(pTableRs)
		delete(pTableRs);
	return strEnglishName;
}

//+++++++++++++++++++��ʼ���+++++++++++++++++++
void CAutoMakeupDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	newPaper.FanganID = "";
	newPaper.ID = "";
	newPaper.QuestionID = "";
	newPaper.QuestionScore = "";
	newPaper.QuestionAnswer = "";
	newPaper.Content = "";
	newPaper.Answer = "";
	newPaper.Username = "";
	newPaper.Date = "";

	UpdateData(TRUE);
		
	//�ж��Ƿ��Ѿ�������
	if(!pRs->IsOpen())
	{
		AfxMessageBox("��ѡ��Ŀ������ݶ�ȡʧ��!");
		return;
	}

//++++++++++��Ŀѡ��+++++++++++
	UpdateData(TRUE);
	m_strPaper = "";
	UpdateData(FALSE);
	if(m_nNumber == -1)
	{
		AfxMessageBox("��ѡ�񹲼�������!");
		return;
	}

	int full_score = 0;
	for(int i = 0 ; i < m_nNumber+1 ; i++)
	{
		if(m_str[i].IsEmpty() || m_nCount[i] <= 0 || m_nScore[i] <= 0)
		{
			AfxMessageBox("��Ŀ��Ϣѡ�������޷����!");
			return;
		}
	}
	for(i = 0 ; i < m_nNumber+1 ; i++)
	{
		for(int j = 1 ; j < m_nNumber + 1 - i ; j++)
			if(m_str[i] == m_str[i+j])
			{
				AfxMessageBox("���Ͳ������ظ�!");
				return;
			}
	}
	for(i = 0 ; i < m_nNumber+1 ; i++)
		full_score += m_nScore[i];
	if(full_score != m_nAllscore)
	{
		AfxMessageBox("�����ֵ֮�����ܷ�ֵ���ȣ������·���!");
		return;
	}
	
	if(!FindAllItems())
	{
		AfxMessageBox("���ʧ��!");
	}
	//�������ƣ��´��ٰ���ButtonOther��ʼ����,����������
	for(i = 0 ; i < 10 ; i++)
	{
		strSelChap[i] = "";
		strSelDiff[i] = "";
		//�ж��ܷ�����ã���ѡ�½ں��Ѷ����������뵱ǰѡ����Ŀ�Ƿ�һ��,����������
		nSelChap[i] = 0;
		nSelDiff[i] = 0;
		//��¼��OnButtonOther��ÿ������ÿ�¡�ÿ���Ѷȵ���Ŀ�����ʱ��,����������
		for(int j = 0 ; j < 30 ; j++)
			Chapter_num[i][j] = 0;
		for(j = 0 ; j < 5 ; j++)
			Difficulty_num[i][j] = 0;
	}
	
	if(pRs->IsOpen())
		pRs->Close();
	m_comboSubject.EnableWindow(TRUE);
	m_strSubject = "";
	m_nAllscore = 0;
	UpdateData(FALSE);
	m_buttonSelect.EnableWindow(TRUE);
	m_buttonReset.EnableWindow(FALSE);
	m_comboNumber.EnableWindow(FALSE);
	m_editAllscore.EnableWindow(FALSE);
	m_DateTimeCreate.EnableWindow(FALSE);
	m_buttonStart.EnableWindow(FALSE);
	for(i = 0 ; i < 10 ; i++)
	{
		int count = m_combo[i].GetCount();
		for(int j = 0 ; j < count ; j++)	
			m_combo[i].DeleteString(0);
	}
	UpdateData(TRUE);
	int num = m_comboNumber.GetCurSel() + 1;
	for(i = 0 ; i < num ; i++)
	{
		m_nCount[i] = 0;
		m_nScore[i] = 0;
		m_buttonOther[i].EnableWindow(FALSE);
		m_editCount[i].EnableWindow(FALSE);
		m_editScore[i].EnableWindow(FALSE);
		m_combo[i].EnableWindow(FALSE);
	}
	m_nNumber = 0;
	UpdateData(FALSE);
}

BOOL CAutoMakeupDlg::IsExist(int No[],int x)
{
	int i = 0;
	while(No[i] != -1)
	{
		if(x == No[i])
			return TRUE;
		i++;
	}
	return FALSE;
}


CString CAutoMakeupDlg::IntToString(int index)
{
	CString str;
	CString strNo = "";
	str.Format(_T("%d"),index);
	if(str.GetLength() == 1)
	{
		strNo += "0";
		strNo += str;
	}
	else
		strNo += str;
	return strNo;
}

//��������
int CAutoMakeupDlg::FindDifficulty(CString strDifficulty)
{
	for(int i = 0 ; i < 5 ; i++)
		if(strDifficulty == autoDifficulty_Chinese[i])
			return i;
	return -1;
}

CString CAutoMakeupDlg::SetTitle()
{
	UpdateData(TRUE);
	m_strPaper = "                 �׶�ʦ����ѧ    -    ѧ���  ѧ��\r\n";
	m_strPaper += "                           ��  �����Ծ�\r\n\r\n";
	m_strPaper += "���Կ�Ŀ��                        �Ծ����           ����ʱ�䣺_____ ����\r\n";
	m_strPaper += "___________________________Ժ_________________ϵ_____________��__________��\r\n";
    m_strPaper += "����_______________________         ѧ��_______________________________\r\n\r\n";
	CString strAnswer = "                 �׶�ʦ����ѧ    -    ѧ���  ѧ��\r\n";
	strAnswer += "                         ��  �����Ծ��\r\n\r\n";
	return strAnswer;
}

//++++++++++++++++�ҵ���������������Ŀ+++++++++++++++++
BOOL CAutoMakeupDlg::FindAllItems()
{
//	UpdateData(TRUE);
//	SetTitle();
	CString question_ID = "";            //Ҫ��ӵ��Ծ���Ϣ
	CString question_score ="";
	CString question_answer = "";
	CString fangan_ID = "";
	CString content_answer = SetTitle();
	for(int i = 0 ; i < m_nNumber+1 ; i++)
	{
		//����ID
		CString str;
		m_combo[i].GetLBText(m_combo[i].GetCurSel(),str);	
		fangan_ID += FindType(str);
		fangan_ID += IntToString(m_nCount[i]);
		
		CString temp;
		//����
		m_strPaper += Number_Chinese[i];
		m_strPaper += "��";
		m_strPaper += m_str[i];
		m_strPaper += "(��";
		content_answer += Number_Chinese[i];
		content_answer += "��";
		content_answer += m_str[i];
		content_answer += "(��";		
		temp.Format(_T("%d"),m_nCount[i]);
		m_strPaper += temp;
		content_answer += temp;
		m_strPaper += "С��,��";
		content_answer += "С��,��";
		temp.Format(_T("%d"),m_nScore[i]);
		m_strPaper += temp;
		m_strPaper += "��)\r\n";
		content_answer += temp;
		content_answer += "��)\r\n";
		
		
		question_score += temp;
		if(i != m_nNumber)
			question_score += "��";
//++++++++++++++++++û�ж��½ں��Ѷ�����++++++++++++++++++++++
		if(nSelChap[i] == 0 && nSelDiff[i] ==0)
		{
			//�ж��Ƿ��Ѿ�������
			if(pRs->IsOpen())
				pRs->Close();
			//�����ַ����洢SQL���
			CString strSql;
			//��ʼ��SQL����ַ����������ѡ��������
			strSql.Format("select * from %s where Type='%s' order by ID",Table_name,m_str[i]);	
			//�򿪵�ǰѡ�е����
			pRs->Open(strSql,CADORecordset.openQuery);
			int Question_num = pRs->GetRecordCount();
			if(Question_num < m_nCount[i])
			{
				AfxMessageBox("�������Ŀ��������!");
				return FALSE;
			}
			
			//�漴ѡ������
			int No[100];
			for(int now = 0 ; now < 100 ; now++)
				No[now] = -1;
			int j = 0;
			
			srand((unsigned)time(NULL));
			//С��
			while(j < m_nCount[i])
			{
				
				int x = rand()%(Question_num);
				if(IsExist(No,x))
				{
					continue;
				}
				
				No[j] = x;
				if(!pRs->MoveTo(x))
					continue;
				CString strNo;
				strNo.Format(_T("%d"),j+1);
				m_strPaper += strNo;
				m_strPaper += ".";
				
				content_answer += strNo;
				content_answer += ".";
				
				CString strContent;
				pRs->GetFieldValue("Content",strContent);
				m_strPaper += strContent;
				m_strPaper += "\r\n\r\n";
				CString strID;
				pRs->GetFieldValue("ID",strID);
				question_ID += strID;
				
				CString strAnswer;
				pRs->GetFieldValue("Answer",strAnswer);
				if(strAnswer.IsEmpty())
					strAnswer = "��";
				question_answer += strAnswer;
				
				content_answer += strAnswer;
				content_answer += "\r\n\r\n";
				j++;
				if(!(j == m_nCount[i] && i == m_nNumber))
				{
					question_ID += ",";
					question_answer +="��";
				}
			}//endwhile
		}//endif
//++++++++++++++++++�������½ڻ��Ѷ�++++++++++++++++++++++
		else
		{
			//+++++++++++ֻ�������½�++++++++++++
			if(nSelDiff[i] == 0)
			{	
				CString strSql;
				strSql.Format("select * from %s where Type='%s'",Table_name,m_str[i]);
				int nNo = 1;
				bool IsFirst = TRUE;
				for(int j = 0 ; j < 30 ; j++)
				{
					if(Chapter_num[i][j] == 1)
					{						
						CString temp;
						if(IsFirst)
						{
							temp.Format(" and (Chapter='%s'",autoChapter_Chinese[j]);
							strSql += temp;
						}
						else
						{
							temp.Format(" or Chapter='%s'",autoChapter_Chinese[j]);
							strSql += temp;
						}
						IsFirst = FALSE;
					}
				}
				strSql += ")";
				//�ж��Ƿ��Ѿ�������
				if(pRs->IsOpen())
					pRs->Close();
				//�򿪵�ǰѡ�е����
				pRs->Open(strSql,CADORecordset.openQuery);
				int Question_num = pRs->GetRecordCount();
				if(Question_num < m_nCount[i])
				{
					AfxMessageBox("�������Ŀ��������!");
					return FALSE;
				}
				
				//�漴ѡ������
				int No[100];
				for(int now = 0 ; now < 100 ; now++)
					No[now] = -1;
				j = 0;
				
				srand((unsigned)time(NULL));
				//С��
				while(j < m_nCount[i])
				{
					
					int x = rand()%(Question_num);
					if(IsExist(No,x))
					{
						continue;
					}
					
					No[j] = x;
					if(!pRs->MoveTo(x))
						continue;
					CString strNo;
					strNo.Format(_T("%d"),j+1);
					m_strPaper += strNo;
					m_strPaper += ".";
					
					content_answer += strNo;
					content_answer += ".";
					
					CString strContent;
					pRs->GetFieldValue("Content",strContent);
					m_strPaper += strContent;
					m_strPaper += "\r\n\r\n";
					CString strID;
					pRs->GetFieldValue("ID",strID);
					question_ID += strID;
					
					CString strAnswer;
					pRs->GetFieldValue("Answer",strAnswer);
					if(strAnswer.IsEmpty())
						strAnswer = "��";
					question_answer += strAnswer;
					
					content_answer += strAnswer;
					content_answer += "\r\n\r\n";
					j++;
					if(!(j == m_nCount[i] && i == m_nNumber))
					{
						question_ID += ",";
						question_answer +="��";
					}
				}//endwhile
			}//endif
//+++++++++++ֻ�������Ѷ�++++++++++++
			else
				if(nSelChap[i] == 0)
				{
					int nNo = 1;
					for(int j = 0 ; j < 5 ; j++)
					{
						if(Difficulty_num[i][j] > 0)
						{
							//�ж��Ƿ��Ѿ�������
							if(pRs->IsOpen())
								pRs->Close();
							//�����ַ����洢SQL���
							CString strSql;
							//��ʼ��SQL����ַ����������ѡ��������
							strSql.Format("select * from %s where Type='%s' and Difficulty='%s' order by ID",Table_name,m_str[i],autoDifficulty_Chinese[j]);	
							//�򿪵�ǰѡ�е����
							pRs->Open(strSql,CADORecordset.openQuery);
							int Question_num = pRs->GetRecordCount();
							
							//�漴ѡ������
							int No[100];
							for(int now = 0 ; now < 100 ; now++)
								No[now] = -1;
							int k = 0;
							
							srand((unsigned)time(NULL));
							//С��
							while(k < Difficulty_num[i][j])
							{
								
								int x = rand()%(Question_num);
								if(IsExist(No,x))
								{
									continue;
								}
								
								No[k] = x;
								if(!pRs->MoveTo(x))
									continue;
								CString strNo;
								strNo.Format(_T("%d"),nNo);
								m_strPaper += strNo;
								m_strPaper += ".";
								
								content_answer += strNo;
								content_answer += ".";
								
								CString strContent;
								pRs->GetFieldValue("Content",strContent);
								m_strPaper += strContent;
								m_strPaper += "\r\n\r\n";
								CString strID;
								pRs->GetFieldValue("ID",strID);
								question_ID += strID;
								
								CString strAnswer;
								pRs->GetFieldValue("Answer",strAnswer);
								if(strAnswer.IsEmpty())
									strAnswer = "��";
								question_answer += strAnswer;
								
								content_answer += strAnswer;
								content_answer += "\r\n\r\n";
								k++;
								nNo++;
								if(!(nNo == m_nCount[i] && i == m_nNumber))
								{
									question_ID += ",";
									question_answer +="��";
								}
							}//endwhile
						}//endif
					}//endfor		
				}//endif
//+++++++++++���������½����������Ѷ�++++++++++++
				else
				{
					CString strSql;
					strSql.Format("select * from %s where Type='%s'",Table_name,m_str[i]);
					bool IsFirst = TRUE;
					for(int j = 0 ; j < 30 ; j++)
					{
						if(Chapter_num[i][j] == 1)
						{						
							CString temp;
							if(IsFirst)
							{
								temp.Format(" and (Chapter='%s'",autoChapter_Chinese[j]);
								strSql += temp;
							}
							else
							{
								temp.Format(" or Chapter='%s'",autoChapter_Chinese[j]);
								strSql += temp;
							}
							IsFirst = FALSE;
						}
					}
					strSql += ")";
					int nNo = 1;
					for(j = 0 ; j < 5 ; j++)
					{
						if(Difficulty_num[i][j] > 0)
						{
							//�ж��Ƿ��Ѿ�������
							if(pRs->IsOpen())
								pRs->Close();
							//�����ַ����洢SQL���
							temp.Format(" and Difficulty='%s'",autoDifficulty_Chinese[j]);
							strSql += temp;
							//�򿪵�ǰѡ�е����
							pRs->Open(strSql,CADORecordset.openQuery);
							int Question_num = pRs->GetRecordCount();
							
							//�漴ѡ������
							int No[100];
							for(int now = 0 ; now < 100 ; now++)
								No[now] = -1;
							int k = 0;
							
							srand((unsigned)time(NULL));
							//С��
							while(k < Difficulty_num[i][j])
							{
								
								int x = rand()%(Question_num);
								if(IsExist(No,x))
								{
									continue;
								}
								
								No[k] = x;
								if(!pRs->MoveTo(x))
									continue;
								CString strNo;
								strNo.Format(_T("%d"),nNo);
								m_strPaper += strNo;
								m_strPaper += ".";
								
								content_answer += strNo;
								content_answer += ".";
								
								CString strContent;
								pRs->GetFieldValue("Content",strContent);
								m_strPaper += strContent;
								m_strPaper += "\r\n\r\n";
								CString strID;
								pRs->GetFieldValue("ID",strID);
								question_ID += strID;
								
								CString strAnswer;
								pRs->GetFieldValue("Answer",strAnswer);
								if(strAnswer.IsEmpty())
									strAnswer = "��";
								question_answer += strAnswer;
								
								content_answer += strAnswer;
								content_answer += "\r\n\r\n";
								k++;
								nNo++;
								if(!(nNo == m_nCount[i] && i == m_nNumber))
								{
									question_ID += ",";
									question_answer +="��";
								}
							}//endwhile
						}//endif
					}//endfor(�Ѷ�ѭ��)										
				}//endif(ѡ�����ѶȺ��½�)
		}//endif
	}//endfor
	CString question_content = m_strPaper;
    m_strAnswer = content_answer;


	CString ID = FindID(fangan_ID);
 
	CString strDate;	
	GetDlgItem(IDC_DATETIMEPICKER_CREATE)->GetWindowText(strDate);
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
    CString	strUsername = parent->GetUsername();

	newPaper.FanganID = fangan_ID;
	newPaper.ID = ID;
	newPaper.QuestionID = question_ID;
	newPaper.QuestionScore = question_score;
	newPaper.QuestionAnswer = question_answer;
	newPaper.Content = question_content;
	newPaper.Answer = content_answer;
	newPaper.Username = strUsername;
	newPaper.Date = strDate;

	if(fangan_ID == "" || ID == ""
		|| question_ID == "" || question_score == ""
		|| question_answer == "" || question_content == ""
		|| content_answer == "" || strUsername == ""
		|| strDate == "")
		return FALSE;
	UpdateData(FALSE);

	CString strSave = "ȷ�Ͻ����Ծ��뵽��";
	strSave += m_strSubject;
	strSave += "�Ծ��";
	if(MessageBox(strSave,"ȷ�ϱ��������Ծ�",MB_ICONQUESTION|MB_OKCANCEL) == IDOK)
	{
		if(InsertNewItems())	
		{
			CString afx = "�Ծ��ţ�";
			afx += newPaper.ID;
			afx += "����ӵ�";
			afx += m_strSubject;
			afx += "�����";
			MessageBox(afx,"��ʾ",MB_ICONINFORMATION|MB_OK);
			m_buttonOut.EnableWindow(TRUE);
			m_buttonOutAnswer.EnableWindow(TRUE);
			return TRUE;
		}
	}
	else
	{
		m_strPaper = "";
		m_strAnswer = "";
		UpdateData(FALSE);
	}
	return FALSE;
}

//�õ����ʹ���
CString CAutoMakeupDlg::FindType(CString type)
{
	CString strType = "";
	CADORecordset* pTypeRs;
	pTypeRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbType where Name='%s'",type);
	pTypeRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTypeRs->IsOpen() && pTypeRs->GetRecordCount() > 0)
	{
		CString strID;
		pTypeRs->GetFieldValue("ID",strID);
		if(strID.GetLength() == 1)
		{
			strType += "0";
			strType += strID;
		}
		else
			strType += strID;
		pTypeRs->Close();
	}
	if(pTypeRs)
		delete(pTypeRs);
	return strType;
}

//ͨ������ID��ѯ�Ծ��õ������Ծ�ID
CString CAutoMakeupDlg::FindID(CString fangan_ID)
{
	CString ID = "";
	if(fangan_ID.IsEmpty() || strPaperName.IsEmpty())
		return ID;
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s where ����ID='%s' order by ID",strPaperName,fangan_ID);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pPaperRs->IsOpen())
	{
		ID += fangan_ID;
		int nNumber = pPaperRs->GetRecordCount();
		
		CString strNum;
		strNum.Format(_T("%d"),nNumber+1);
		int n = strNum.GetLength();	
		for(int i = 0 ; i < 4-n ; i++)
		{
			ID += "0";
		}
		ID += strNum;

		pPaperRs->Close();
		delete pPaperRs;
		return ID;
	}
	if(pPaperRs)
		delete pPaperRs;
    return ID;
}

//�����µ��Ծ�
BOOL CAutoMakeupDlg::InsertNewItems()
{
	if(strPaperName.IsEmpty())
		return FALSE;
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s order by ����ID",strPaperName);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pPaperRs->IsOpen())
	{
		//�����¼����¼��
		pPaperRs->AddNew();
		pPaperRs->SetFieldValue("ID",newPaper.ID);
		pPaperRs->SetFieldValue("����ID",newPaper.FanganID);
		pPaperRs->SetFieldValue("��ĿID",newPaper.QuestionID);
		pPaperRs->SetFieldValue("��Ŀ��ֵ",newPaper.QuestionScore);
		pPaperRs->SetFieldValue("��Ŀ��",newPaper.QuestionAnswer);
		pPaperRs->SetFieldValue("����",newPaper.Content);
		pPaperRs->SetFieldValue("��",newPaper.Answer);
		pPaperRs->SetFieldValue("����ʱ��",newPaper.Date);
		pPaperRs->SetFieldValue("������",newPaper.Username);
		pPaperRs->Update();
		pPaperRs->Close();
		delete pPaperRs;
		return TRUE;
	}
	if(pPaperRs)
		delete pPaperRs;
	return FALSE;
}

void CAutoMakeupDlg::OnButtonOut() 
{
	// TODO: Add your control notification handler code here
	if(m_strPaper.IsEmpty())
		return;
	CString strFilter;
	strFilter.LoadString(IDS_FILE_FILTER);
	CString Filename = "�Ծ�";
	Filename += newPaper.ID;
	CFileDialog fileDlg(FALSE, NULL, Filename, OFN_HIDEREADONLY, strFilter, NULL);
	if(fileDlg.DoModal() != IDOK)
		return;
	CString strFilename = fileDlg.GetPathName();
	strFilename += ".doc";
	
	_Application app;
	app.CreateDispatch(_T("Word.Application"));
	app.SetVisible(TRUE);
	
	Documents docs=app.GetDocuments();
	CComVariant Template(_T(""));
	CComVariant NewTemplate(false),DocumentType(0),Visible;
	docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
	
	Selection sel=app.GetSelection();
	
	sel.TypeText(_T(m_strPaper));
	
	CString strSave = "�Ƿ񱣴��ĵ�1��";
	strSave += strFilename;
	if(MessageBox(strSave,"ȷ�ϱ���",MB_ICONQUESTION|MB_OKCANCEL) == IDOK)
	{
		_Document doc=app.GetActiveDocument();		//�õ�ActiveDocument
		CComVariant FileName(_T(strFilename));	//�ļ���
		CComVariant FileFormat(0);
		CComVariant LockComments(false),Password(_T(""));
		CComVariant AddToRecentFiles(true),WritePassword(_T(""));
		CComVariant ReadOnlyRecommended(false),EmbedTrueTypeFonts(false);
		CComVariant SaveNativePictureFormat(false),SaveFormsData(false);
		CComVariant SaveAsAOCELetter(false);
		
		doc.SaveAs(&FileName,&FileFormat,&LockComments,&Password,
			&AddToRecentFiles,&WritePassword,&ReadOnlyRecommended,
			&EmbedTrueTypeFonts,&SaveNativePictureFormat,&SaveFormsData,
			&SaveAsAOCELetter);
		doc.ReleaseDispatch();
	}
	sel.ReleaseDispatch();	
	docs.ReleaseDispatch();
	
	CComVariant SaveChanges(false),OriginalFormat,RouteDocument;
	app.Quit(&SaveChanges,&OriginalFormat,&RouteDocument);
	app.ReleaseDispatch();	
}

void CAutoMakeupDlg::OnButtonOther(UINT nID) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	for(int i = 0 ; i < 30 ; i++)
	{
		Chapter_all[i] = "";
		EveryChapNum[i] = 0;
	}
	for(i = 0 ; i < 5 ; i++)
	{
		Difficulty_all[i] = "";
	    EveryDiffNum[i] = 0;
	}

	nButtonOther_index = nID - IDC_BUTTON_OTHER1;
	if(m_str[nButtonOther_index].IsEmpty() || m_nCount[nButtonOther_index] <= 0)
	{
		AfxMessageBox("����ѡ����Ŀ���ͺ�����!");
		return;
	}
	//�����ַ����洢SQL���
	CString strSql;
	//��ʼ��SQL����ַ����������ѡ��������
	strSql.Format("select * from %s where Type='%s' order by Chapter",Table_name,m_str[nButtonOther_index]);	
	//�򿪵�ǰѡ�е����
	pRs->Open(strSql,CADORecordset.openQuery);
	if(!pRs->IsOpen())
		return;
	if(pRs->GetRecordCount() <= 0)
		return;
	int QuesCountType = pRs->GetRecordCount();
	if(m_nCount[nButtonOther_index] > QuesCountType)
	{
		AfxMessageBox("��ѡ������������и���������!");
		return;
	}
	CString strChapter = "";
	CString lastChapter = "";
	i = 0;
	while(!pRs->IsEOF())
	{		
		pRs->GetFieldValue("Chapter",strChapter);
		if(strChapter != lastChapter)
		{
			Chapter_all[i] = strChapter;
			lastChapter = strChapter;
			i++;
		}
		EveryChapNum[i-1]++;	
		pRs->MoveNext();
	}
	pRs->Close();

	//��ʼ��SQL����ַ����������ѡ��������
	strSql.Format("select * from %s where Type='%s' order by Difficulty",Table_name,m_str[nButtonOther_index]);	
	//�򿪵�ǰѡ�е����
	pRs->Open(strSql,CADORecordset.openQuery);
	if(!pRs->IsOpen())
		return;
	if(pRs->GetRecordCount() <= 0)
		return;
	CString strDifficulty = "";
	CString lastDifficulty = "";
	while(!pRs->IsEOF())
	{		
		pRs->GetFieldValue("Difficulty",strDifficulty);
		if(strDifficulty != lastDifficulty)
		{
			i = FindDifficulty(strDifficulty);
			if(i >= 0)
				Difficulty_all[i] = strDifficulty;
			lastDifficulty = strDifficulty;
		}
		EveryDiffNum[i]++;
		pRs->MoveNext();
	}

	CSelChapAndDiffDlg selchapanddiffDlg;
	if(selchapanddiffDlg.DoModal() == IDOK)
	{
		strSelChap[nButtonOther_index] = selchapanddiffDlg.strSelChapter;
		strSelDiff[nButtonOther_index] = selchapanddiffDlg.strSelDifficulty;
        nSelChap[nButtonOther_index] = selchapanddiffDlg.nChapnum;
	    nSelDiff[nButtonOther_index] = selchapanddiffDlg.nDiffnum;
		//�Ƿ���ĳ�½���ѡ��
		for(i = 0 ; i < 30 ; i++)
			Chapter_num[nButtonOther_index][i] = selchapanddiffDlg.Chapter_num[i];
		//ĳ�Ѷȹ��������
		for(i = 0 ; i < 5 ; i++)
			Difficulty_num[nButtonOther_index][i] = selchapanddiffDlg.Difficulty_num[i];
		m_editCount[nButtonOther_index].EnableWindow(FALSE);
	}
	else
	{
		strSelChap[nButtonOther_index] = "";
		strSelDiff[nButtonOther_index] = "";
		nSelChap[nButtonOther_index] = 0;
	    nSelDiff[nButtonOther_index] = 0;
		for(i = 0 ; i < 30 ; i++)
			Chapter_num[nButtonOther_index][i] = 0;
		for(i = 0 ; i < 5 ; i++)
			Difficulty_num[nButtonOther_index][i] = 0;
		m_editCount[nButtonOther_index].EnableWindow(TRUE);
	}
}

void CAutoMakeupDlg::OnSelchangeComboNumber() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int num = m_comboNumber.GetCurSel() + 1;
	for(int i = 0 ; i < num ; i++)
	{
		m_buttonOther[i].EnableWindow(TRUE);
		m_editCount[i].EnableWindow(TRUE);
		m_editScore[i].EnableWindow(TRUE);
		m_combo[i].EnableWindow(TRUE);
	}
	for(i = num ; i < 10 ; i++)
	{
		m_nCount[i] = 0;
		m_nScore[i] = 0;
		m_buttonOther[i].EnableWindow(FALSE);
		m_editCount[i].EnableWindow(FALSE);
		m_editScore[i].EnableWindow(FALSE);
		m_combo[i].EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CAutoMakeupDlg::OnButtonSelect() 
{
	// TODO: Add your control notification handler code here
	//���ҵ�ǰҪ�򿪵�����Ƿ����
	Table_name = FindTable();
	if(Table_name.IsEmpty())
	{
		AfxMessageBox("��ѡ���Ŀ!");
		return;
	}
	//�����ַ����洢SQL���
	CString strSql;
	//��ʼ��SQL����ַ����������ѡ��������
	strSql.Format("select * from %s order by ID",Table_name);	
	//�򿪵�ǰѡ�е����
	pRs->Open(strSql,CADORecordset.openQuery);
	if(pRs->IsOpen())
	{
		m_comboSubject.EnableWindow(FALSE);
		m_buttonSelect.EnableWindow(FALSE);
		m_buttonReset.EnableWindow(TRUE);
		m_comboNumber.EnableWindow(TRUE);
		m_editAllscore.EnableWindow(TRUE);
		m_DateTimeCreate.EnableWindow(TRUE);
	    m_buttonStart.EnableWindow(TRUE);
		m_buttonOut.EnableWindow(FALSE);
		m_buttonOutAnswer.EnableWindow(FALSE);
	}
	InitCombo();
	UpdateData(TRUE);
	int num = m_comboNumber.GetCurSel() + 1;
	for(int i = 0 ; i < num ; i++)
	{
		m_buttonOther[i].EnableWindow(TRUE);
		m_editCount[i].EnableWindow(TRUE);
		m_editScore[i].EnableWindow(TRUE);
		m_combo[i].EnableWindow(TRUE);
	}
	m_strPaper = "";
	m_strAnswer = "";
	UpdateData(FALSE);
}

void CAutoMakeupDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	if(pRs->IsOpen())
		pRs->Close();
	m_comboSubject.EnableWindow(TRUE);
    m_strSubject = "";
	m_nAllscore = 0;
	UpdateData(FALSE);
	m_buttonSelect.EnableWindow(TRUE);
	m_buttonReset.EnableWindow(FALSE);
	m_comboNumber.EnableWindow(FALSE);
	m_editAllscore.EnableWindow(FALSE);
	m_DateTimeCreate.EnableWindow(FALSE);
	m_buttonStart.EnableWindow(FALSE);
	for(int i = 0 ; i < 10 ; i++)
	{
		int count = m_combo[i].GetCount();
		for(int j = 0 ; j < count ; j++)	
			m_combo[i].DeleteString(0);
	}
	UpdateData(TRUE);
	int num = m_comboNumber.GetCurSel() + 1;
	for(i = 0 ; i < num ; i++)
	{
		m_nCount[i] = 0;
		m_nScore[i] = 0;
		m_buttonOther[i].EnableWindow(FALSE);
		m_editCount[i].EnableWindow(FALSE);
		m_editScore[i].EnableWindow(FALSE);
		m_combo[i].EnableWindow(FALSE);
	}
	m_nNumber = 0;
	UpdateData(FALSE);
}

void CAutoMakeupDlg::OnButtonOutanswer() 
{
	// TODO: Add your control notification handler code here
	if(m_strAnswer.IsEmpty())
		return;
	CString strFilter;
	strFilter.LoadString(IDS_FILE_FILTER);
	CString Filename = "�Ծ�";
	Filename += newPaper.ID;
	Filename += "��";
	CFileDialog fileDlg(FALSE, NULL, Filename, OFN_HIDEREADONLY, strFilter, NULL);
	if(fileDlg.DoModal() != IDOK)
		return;
	CString strFilename = fileDlg.GetPathName();
	strFilename += ".doc";
	
	_Application app;
	app.CreateDispatch(_T("Word.Application"));
	app.SetVisible(TRUE);
	
	Documents docs=app.GetDocuments();
	CComVariant Template(_T(""));
	CComVariant NewTemplate(false),DocumentType(0),Visible;
	docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
	
	Selection sel=app.GetSelection();
	
	sel.TypeText(_T(m_strAnswer));
	
	CString strSave = "�Ƿ񱣴��ĵ�1��";
	strSave += strFilename;
	if(MessageBox(strSave,"ȷ�ϱ���",MB_ICONQUESTION|MB_OKCANCEL) == IDOK)
	{
		_Document doc=app.GetActiveDocument();		//�õ�ActiveDocument
		CComVariant FileName(_T(strFilename));	//�ļ���
		CComVariant FileFormat(0);
		CComVariant LockComments(false),Password(_T(""));
		CComVariant AddToRecentFiles(true),WritePassword(_T(""));
		CComVariant ReadOnlyRecommended(false),EmbedTrueTypeFonts(false);
		CComVariant SaveNativePictureFormat(false),SaveFormsData(false);
		CComVariant SaveAsAOCELetter(false);
		
		doc.SaveAs(&FileName,&FileFormat,&LockComments,&Password,
			&AddToRecentFiles,&WritePassword,&ReadOnlyRecommended,
			&EmbedTrueTypeFonts,&SaveNativePictureFormat,&SaveFormsData,
			&SaveAsAOCELetter);
		doc.ReleaseDispatch();
	}
	sel.ReleaseDispatch();	
	docs.ReleaseDispatch();
	
	CComVariant SaveChanges(false),OriginalFormat,RouteDocument;
	app.Quit(&SaveChanges,&OriginalFormat,&RouteDocument);
	app.ReleaseDispatch();	
}

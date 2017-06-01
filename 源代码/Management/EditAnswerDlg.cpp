// EditAnswerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "EditAnswerDlg.h"
#include "msword.h"
#include <AtlBase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditAnswerDlg dialog


CEditAnswerDlg::CEditAnswerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditAnswerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditAnswerDlg)
	m_strAnswer = _T("");
	m_strTitle = _T("");
	m_strPaper = _T("");
	m_strTitilePaper = _T("");
	//}}AFX_DATA_INIT
	strID = "";
}


void CEditAnswerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditAnswerDlg)
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_strAnswer);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_PAPER, m_strPaper);
	DDX_Text(pDX, IDC_STATIC_TITLEPAPER, m_strTitilePaper);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditAnswerDlg, CDialog)
	//{{AFX_MSG_MAP(CEditAnswerDlg)
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnButtonOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditAnswerDlg message handlers

void CEditAnswerDlg::OnButtonOut() 
{
	// TODO: Add your control notification handler code here
	if(m_strAnswer.IsEmpty())
		return;

	CString strFilter;
	strFilter.LoadString(IDS_FILE_FILTER);
	CString Filename = "�Ծ�";
	Filename += strID;
	Filename += "��";
	CFileDialog fileDlg(FALSE, NULL, Filename, NULL, strFilter, NULL);
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

void CEditAnswerDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);	

	CDialog::OnOK();
}

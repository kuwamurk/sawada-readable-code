
// TestApplicationDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "TestApplication.h"
#include "TestApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestApplicationDlg ダイアログ



CTestApplicationDlg::CTestApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTAPPLICATION_DIALOG, pParent)
    , m_titleWords()
    , m_prePos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MESSAGE, m_stMessage);
    DDX_Control(pDX, IDC_LIST1, m_messageList);
}

BEGIN_MESSAGE_MAP(CTestApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_ACTION, &CTestApplicationDlg::OnBnClickedAction)
    ON_BN_CLICKED(IDC_SAVE, &CTestApplicationDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// CTestApplicationDlg メッセージ ハンドラー

BOOL CTestApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CTestApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CTestApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CTestApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestApplicationDlg::OnBnClickedAction()
{
    m_stMessage.SetWindowTextW(L"上手");
}


void CTestApplicationDlg::OnBnClickedLoad()
{
    CString strDicFile;
    getDictionaryFilePath(strDicFile);

    BYTE byRead[READ_SIZE];
    ZeroMemory(byRead, READ_SIZE);

    HANDLE hFile = CreateFile(strDicFile, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD dwReaded = 0;
    ReadFile(hFile, byRead, READ_SIZE, &dwReaded, NULL);

    m_titleWords = reinterpret_cast<LPCTSTR>(byRead);
//    m_stMessage.SetWindowTextW(m_titleWords);

    // ListBoxに単語を追加する
    bool bNext = false;
    do{
        CString nextWord;
        bNext = getNextTitleWord(nextWord);
        if (nextWord.IsEmpty()) {
            break;
        }
        m_messageList.AddString(nextWord);
    } while (bNext);

    CloseHandle(hFile); // ファイルの後始末
}

void CTestApplicationDlg::getDictionaryFilePath(CString& strDicFile)
{
    strDicFile = _T("C:\\readablecode\\test3\\sawada-readable-code\\proj\\TestApplication\\dictionary-data.txt");
}

bool CTestApplicationDlg::getNextTitleWord(CString &titleWord)
{
    int pos = m_titleWords.Find(_T("\n"), m_prePos+1);
    if ( pos == -1 ){
        titleWord = m_titleWords.Right(pos);
        return false;
    }
    titleWord = m_titleWords.Mid(m_prePos, pos - m_prePos);
    m_prePos = pos;
    return true;
}
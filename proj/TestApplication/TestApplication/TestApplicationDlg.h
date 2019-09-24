
// TestApplicationDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#define READ_SIZE   (1024)

// CTestApplicationDlg ダイアログ
class CTestApplicationDlg : public CDialogEx
{
// コンストラクション
public:
	CTestApplicationDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
    CStatic m_stMessage;
    
    //!< 次の単語を取得する
    bool getNextTitleWord(CString &titleWord);

    CString m_titleWords;   //!< 単語ファイルから読み出した単語文字列
    int m_prePos;     //!< 今、読み込んでいる単語位置
public:

    afx_msg void OnBnClickedAction();
    afx_msg void OnBnClickedLoad();

    void getDictionaryFilePath(CString& strDicFile);
    CListBox m_messageList;
};


// 2017212151Demo1Dlg.h: 头文件
//

#pragma once


// CMy2017212151Demo1Dlg 对话框
class CMy2017212151Demo1Dlg : public CDialogEx
{
// 构造
public:
	CMy2017212151Demo1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2017212151DEMO1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedCancel();
	CListCtrl m_list;
	void ShowData();
	CEdit m_edtsno;
	CEdit m_edtsname;
	CEdit m_edtssex;
	CEdit m_edtsage;
	CEdit m_edtsdept;
	afx_msg void OnNMClickListShow(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonDelete();
	CButton m_btnCourse1;
	CButton m_btnCourse2;
	CButton m_btnCourse3;
	CButton m_btnCourse4;
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonReset();
};

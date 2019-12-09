
// 2017212151Demo1Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2017212151Demo1.h"
#include "2017212151Demo1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

extern MYSQL m_mysql;
extern CString char2CSt(char * szBuf);
extern char * CSt2char(CString str);

CString mstrsno, mstrsname, mstrssex, mstrsage, mstrsdept;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
bool check1, check2, check3, check4;
int grade1, grade2, grade3, grade4;

int Chartoint(char* c) {
	if (c == NULL) {
		return -1;
	}
	int s = 0;
	int value = 10;
	for (int i = 0; i < strlen(c); i++) {
		s *= value;
		s += int(c[i]) - 48;
	}
	return s;
}


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy2017212151Demo1Dlg 对话框

CMy2017212151Demo1Dlg::CMy2017212151Demo1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY2017212151DEMO1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2017212151Demo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW, m_list);
	DDX_Control(pDX, IDC_EDIT_SNO, m_edtsno);
	DDX_Control(pDX, IDC_EDIT_SNAME, m_edtsname);
	DDX_Control(pDX, IDC_EDIT_SSEX, m_edtssex);
	DDX_Control(pDX, IDC_EDIT_SAGE, m_edtsage);
	DDX_Control(pDX, IDC_EDIT_SDEPT, m_edtsdept);
	DDX_Control(pDX, IDC_CHECK_C1, m_btnCourse1);
	DDX_Control(pDX, IDC_CHECK_C2, m_btnCourse2);
	DDX_Control(pDX, IDC_CHECKC3, m_btnCourse3);
	DDX_Control(pDX, IDC_CHECK_C4, m_btnCourse4);
}

BEGIN_MESSAGE_MAP(CMy2017212151Demo1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMy2017212151Demo1Dlg::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SHOW, &CMy2017212151Demo1Dlg::OnNMClickListShow)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMy2017212151Demo1Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CMy2017212151Demo1Dlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMy2017212151Demo1Dlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CMy2017212151Demo1Dlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMy2017212151Demo1Dlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CMy2017212151Demo1Dlg 消息处理程序

BOOL CMy2017212151Demo1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//list的初始化
	m_list.InsertColumn(0, _T("学号"), LVCFMT_LEFT, 70);
	m_list.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 70);
	m_list.InsertColumn(2, _T("性别"), LVCFMT_LEFT, 70);
	m_list.InsertColumn(3, _T("年龄"), LVCFMT_LEFT, 70);
	m_list.InsertColumn(4, _T("所在系"), LVCFMT_LEFT, 70);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//选择节点的时候选中整行
	ShowData();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy2017212151Demo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2017212151Demo1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy2017212151Demo1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy2017212151Demo1Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	mysql_close(&m_mysql);
	CDialogEx::OnCancel();
}


void CMy2017212151Demo1Dlg::ShowData()
{
	// TODO: 在此处添加实现代码.
	m_list.DeleteAllItems();//清空原有数据
	char sql[100];
	sprintf_s(sql, "select * from student");//设计sql语言
	if (mysql_real_query(&m_mysql, sql, (unsigned long)strlen(sql)))//执行sql语言
	{
		MessageBoxW(_T("读取表格失败")); return;
	}
	MYSQL_RES *result;
	MYSQL_ROW row;
	if (!(result = mysql_use_result(&m_mysql)))//获取数据
	{
		MessageBoxW(_T("读取数据集失败"));
		return;
	}
	int i = 0;
	while (row = mysql_fetch_row(result)) {//第一步是取数据，第二步是判断是否为空
		m_list.InsertItem(i, char2CSt(row[0]));
		if (row[1] == NULL)
			m_list.SetItemText(i, 1, _T("NULL"));
		else
			m_list.SetItemText(i, 1, char2CSt(row[1]));
		if (row[2] == NULL)
			m_list.SetItemText(i, 2, _T("NULL"));
		else
			m_list.SetItemText(i, 2, char2CSt(row[2]));
		if (row[3] == NULL)
			m_list.SetItemText(i, 3, _T("NULL"));
		else
			m_list.SetItemText(i, 3, char2CSt(row[3]));
		if (row[4] == NULL)
			m_list.SetItemText(i, 4, _T("NULL"));
		else
			m_list.SetItemText(i, 4, char2CSt(row[4]));
		i++;
	}
	mysql_free_result(result);//释放资源
}


void CMy2017212151Demo1Dlg::OnNMClickListShow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString strsno, strsname, strssex, strsage, strsdept;
	if (pNMItemActivate->iItem != -1)//pNMItemActivate->iItem为鼠标焦点处对应的行号
	{
		mstrsno = m_list.GetItemText(pNMItemActivate->iItem, 0);
		m_edtsno.SetWindowText(mstrsno);
		mstrsname = m_list.GetItemText(pNMItemActivate->iItem, 1);
		m_edtsname.SetWindowText(mstrsname);
		mstrssex = m_list.GetItemText(pNMItemActivate->iItem, 2);
		m_edtssex.SetWindowText(mstrssex);
		mstrsage = m_list.GetItemText(pNMItemActivate->iItem, 3);
		m_edtsage.SetWindowText(mstrsage);
		mstrsdept = m_list.GetItemText(pNMItemActivate->iItem, 4);
		m_edtsdept.SetWindowText(mstrsdept);

		m_btnCourse1.SetCheck(FALSE);
		m_btnCourse2.SetCheck(FALSE);
		m_btnCourse3.SetCheck(FALSE);
		m_btnCourse4.SetCheck(FALSE);

		check1 = FALSE;
		check2 = FALSE;
		check3 = FALSE;
		check4 = FALSE;

		MYSQL_RES *result;
		MYSQL_ROW row;
		CString mstrsql;
		mstrsql.Format(_T("select cno, grade from sc where sno='%s'"), mstrsno);
		char* sql = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql, strlen(sql))) {
			MessageBoxW(_T("读取课程信息失败！"));
			return;
		}
		if (!(result = mysql_use_result(&m_mysql))) {	//获取数据
			MessageBoxW(_T("读取数据集失败"));
			return;
		}
		while (row = mysql_fetch_row(result)) {
			if (char2CSt(row[0]) == char2CSt("1")) {
				m_btnCourse1.SetCheck(TRUE);
				check1 = TRUE;
				grade1 = Chartoint(row[1]);
			}
			else if (char2CSt(row[0]) == char2CSt("2")) {
				m_btnCourse2.SetCheck(TRUE);
				check2 = TRUE;
				grade2 = Chartoint(row[1]);
			}
			else if (char2CSt(row[0]) == char2CSt("3")) {
				m_btnCourse3.SetCheck(TRUE);
				check3 = TRUE;
				grade3 = Chartoint(row[1]);
			}
			else if (char2CSt(row[0]) == char2CSt("4")) {
				m_btnCourse4.SetCheck(TRUE);
				check4 = TRUE;
				grade4 = Chartoint(row[1]);
			}
		}
		//mysql_free_result(result);//释放资源
		UpdateData(FALSE);//将底层代码的数据传递给上层的界面
	}
	*pResult = 0;
}


void CMy2017212151Demo1Dlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//把界面上的数据传递给底层代码
	CString strsno, strsname, strssex, strsage, strsdept;
	m_edtsno.GetWindowText(strsno);
	m_edtsname.GetWindowText(strsname);
	m_edtssex.GetWindowText(strssex);
	m_edtsage.GetWindowText(strsage);
	m_edtsdept.GetWindowText(strsdept);
	if (strsno == _T(""))
	{
		MessageBoxW(_T("学号为主码，取值不能为空！ "));
		return;
	}
	else
	{
		if (strsname == _T(""))
			strsname = _T("NULL");
		else
			strsname = _T("'") + strsname + _T("'");
		if (strssex == _T(""))
			strssex = _T("NULL");
		else
			strssex = _T("'") + strssex + _T("'");
		if (strsage == _T(""))
			strsage = _T("NULL"); if (strsdept == _T(""))
			strsdept = _T("NULL");
			else
			strsdept = _T("'") + strsdept + _T("'");
		CString mstrsql;
		mstrsql.Format(_T("insert into student values('%s',%s,%s,%s,%s)"), strsno, strsname, strssex,
			strsage, strsdept);
		//MessageBoxW(mstrsql);//测试生成的sql语言
		char *sql = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql, strlen(sql)))
		{
			MessageBoxW(_T("添加失败！请检查学号是否重复？ "));
		}
		else
			ShowData();
	}
}


void CMy2017212151Demo1Dlg::OnBnClickedButtonUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//把界面上的数据传递给底层代码
	CString strsno, strsname, strssex, strsage, strsdept;
	m_edtsno.GetWindowText(strsno);
	m_edtsname.GetWindowText(strsname);
	m_edtssex.GetWindowText(strssex);
	m_edtsage.GetWindowText(strsage);
	m_edtsdept.GetWindowText(strsdept);
	if (strsno == _T(""))
		strsno = mstrsno;	//如果学号为空使用原学号
	else
		strsno = _T("'") + strsno + _T("'");
	if (strsname == _T(""))
		strsname = _T("NULL");
	else
		strsname = _T("'") + strsname + _T("'");
	if (strssex == _T(""))
		strssex = _T("NULL");
	else
		strssex = _T("'") + strssex + _T("'");
	if (strsage == _T(""))
		strsage = _T("NULL"); if (strsdept == _T(""))
		strsdept = _T("NULL");
		else
		strsdept = _T("'") + strsdept + _T("'");
	CString mstrsql;
	mstrsql.Format(_T("alter table sc drop foreign key `sc_ibfk_1`"));	//删除外键约束
	char *sql1 = CSt2char(mstrsql);
	if (mysql_real_query(&m_mysql, sql1, strlen(sql1))) {
		MessageBoxW(_T("删除外键约束失败"));
		return;
	}
	mstrsql.Format(_T("alter table sc add constraint `sc_ibfk_1` foreign key sc(`Sno`) references student(`Sno`) on update cascade on delete cascade"));
	//新增级联型外加约束
	char *sql2 = CSt2char(mstrsql);
	if (mysql_real_query(&m_mysql, sql2, strlen(sql2))) {
		MessageBoxW(_T("新增级联外键约束失败"));
		return;
	}
	mstrsql.Format(_T("update student set sno=%s, sname=%s, ssex=%s, sage=%s, sdept=%s where sno='%s'"),
		strsno, strsname, strssex, strsage, strsdept, mstrsno);
	//修改信息
	//MessageBoxW(mstrsql);//测试生成的sql语言
	char *sql = CSt2char(mstrsql);
	if (mysql_real_query(&m_mysql, sql, strlen(sql)))
	{
		MessageBoxW(_T("修改失败！请检查学号是否重复？ "));
	}
	else {
		MessageBoxW(_T("修改成功！"));
		ShowData();
	}
}


void CMy2017212151Demo1Dlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//把界面上的数据传递给底层代码
	CString strsno;
	m_edtsno.GetWindowText(strsno);
	if (strsno == _T(""))
	{
		MessageBoxW(_T("请输入删除学号"));
		return;
	}
	else
	{
		CString mstrsql;
		mstrsql.Format(_T("alter table sc drop foreign key `sc_ibfk_1`"));	//删除外键约束
		char *sql1 = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql1, strlen(sql1))) {
			MessageBoxW(_T("删除外键约束失败"));
			return;
		}
		mstrsql.Format(_T("alter table sc add constraint `sc_ibfk_1` foreign key sc(`Sno`) references student(`Sno`) on update cascade on delete cascade"));
		//新增级联型外加约束
		char *sql2 = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql2, strlen(sql2))) {
			MessageBoxW(_T("新增级联外键约束失败"));
			return;
		}
		mstrsql.Format(_T("delete from student where sno = '%s'"), strsno);
		//按学号删除数据
		//MessageBoxW(mstrsql);//测试生成的sql语言
		char *sql = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql, strlen(sql)))
		{
			MessageBoxW(_T("删除失败！请检查学号是否正确？ "));
		}
		else {
			MessageBoxW(_T("删除成功！"));
			ShowData();
		}
	}

}


void CMy2017212151Demo1Dlg::OnBnClickedButtonCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strsno;
	m_edtsno.GetWindowText(strsno);
	if (strsno == _T(""))
	{
		MessageBoxW(_T("请输入学号！"));
		return;
	}
	CString mstrsql;

	if (m_btnCourse1.GetCheck() == 1) {
		mstrsql.Format(_T("insert into sc values('%s','1',NULL)"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	else {
		mstrsql.Format(_T("delete from sc where sno='%s' and cno='1'"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	if (m_btnCourse2.GetCheck() == 1) {
		mstrsql.Format(_T("insert into sc values('%s','2',NULL)"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	else {
		mstrsql.Format(_T("delete from sc where sno='%s' and cno='2'"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	if (m_btnCourse3.GetCheck() == 1) {
		mstrsql.Format(_T("insert into sc values('%s','3',NULL)"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	else {
		mstrsql.Format(_T("delete from sc where sno='%s' and cno='3'"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	if (m_btnCourse4.GetCheck() == 1) {
		mstrsql.Format(_T("insert into sc values('%s','4',NULL)"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	else {
		mstrsql.Format(_T("delete from sc where sno='%s' and cno='4'"), strsno);
		char * sql = CSt2char(mstrsql);
		mysql_real_query(&m_mysql, sql, strlen(sql));
	}
	MessageBoxW(_T("修改成功！"));
}


void CMy2017212151Demo1Dlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strsno;
	m_edtsno.GetWindowText(strsno);
	if (strsno == _T(""))
	{
		MessageBoxW(_T("请输入学号！"));
		return;
	}

	m_btnCourse1.SetCheck(FALSE);
	m_btnCourse2.SetCheck(FALSE);
	m_btnCourse3.SetCheck(FALSE);
	m_btnCourse4.SetCheck(FALSE);

	CString mstrsql;
	mstrsql.Format(_T("delete from sc where sno='%s'"), strsno);
	char *sql = CSt2char(mstrsql);
	mysql_real_query(&m_mysql, sql, strlen(sql));
	if (check1) {
		if (grade1 >= 0)
			mstrsql.Format(_T("insert into sc values('%s', '1', %d)"), strsno, grade1);
		if (grade1 == -1)
			mstrsql.Format(_T("insert into sc values('%s', '1', NULL)"), strsno);
		char *sql1 = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql1, strlen(sql1))) {
			MessageBoxW(_T("重置失败！"));
			return;
		}
		m_btnCourse1.SetCheck(TRUE);
	}
	if (check2) {
		if (grade2 >= 0)
			mstrsql.Format(_T("insert into sc values('%s', '2', %d)"), strsno, grade2);
		if (grade2 == -1)
			mstrsql.Format(_T("insert into sc values('%s', '2', NULL)"), strsno);
		char *sql1 = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql1, strlen(sql1))) {
			MessageBoxW(_T("重置失败！"));
			return;
		}
		m_btnCourse2.SetCheck(TRUE);
	}
	if (check3) {
		if (grade3 >= 0)
			mstrsql.Format(_T("insert into sc values('%s', '3', %d)"), strsno, grade3);
		if (grade3 == -1)
			mstrsql.Format(_T("insert into sc values('%s', '3', NULL)"), strsno);
		char *sql1 = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql1, strlen(sql1))) {
			MessageBoxW(_T("重置失败！"));
			return;
		}
		m_btnCourse3.SetCheck(TRUE);
	}
	if (check4) {
		if (grade4 >= 0)
			mstrsql.Format(_T("insert into sc values('%s', '4', %d)"), strsno, grade4);
		if (grade4 == -1)
			mstrsql.Format(_T("insert into sc values('%s', '4', NULL)"), strsno);
		char *sql1 = CSt2char(mstrsql);
		if (mysql_real_query(&m_mysql, sql1, strlen(sql1))) {
			MessageBoxW(_T("重置失败！"));
			return;
		}
		m_btnCourse4.SetCheck(TRUE);
	}
	MessageBoxW(_T("重置成功！"));
}

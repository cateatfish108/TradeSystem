#include "TradeSystem.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "MdSpi.h"
#include "TdSpi.h"
#include <QMessageBox>
#include "tinystr.h"
#include "tinyxml.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <atlstr.h>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QtSql>
#include <QSqlTableModel>
#include <QMessageBox>


using namespace std;

extern QString hyarray[2000][4];

TradeSystem::TradeSystem(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	md = new MdSpi(this);
	td = new TdSpi(this);

	string filename = "config/config.xml";
	readxml(filename);
	//ReadTxt("data/cu1609.txt");

	SetHQUI();
	SetWTUI();
	SetCJUI();
	SetCCUI();
	SetZJUI();
	SetHYUI();
	SetCCUI();
	SetZJUI();
	SetHYUI();
	SetAutoUI();
	SetUI();
}

TradeSystem::~TradeSystem()
{
	WriteTxt("config/pz.txt", 0);
}

void TradeSystem::SetHQUI()
{
	//***************************行情表设置****************************************//
	//设置行情表格行列数量,行11行,10列
	ui.HQTable->setColumnCount(12);

	QStringList headerHQ;
	headerHQ.append(QString::fromLocal8Bit("合约代码"));
	headerHQ.append(QString::fromLocal8Bit("日期"));
	headerHQ.append(QString::fromLocal8Bit("更新时间"));
	headerHQ.append(QString::fromLocal8Bit("最新价"));
	headerHQ.append(QString::fromLocal8Bit("买一价"));
	headerHQ.append(QString::fromLocal8Bit("买一量"));
	headerHQ.append(QString::fromLocal8Bit("卖一价"));
	headerHQ.append(QString::fromLocal8Bit("卖一量"));
	headerHQ.append(QString::fromLocal8Bit("涨幅"));
	headerHQ.append(QString::fromLocal8Bit("成交量"));
	headerHQ.append(QString::fromLocal8Bit("涨停价"));
	headerHQ.append(QString::fromLocal8Bit("跌停价"));

	//填充表格信息
	ui.HQTable->setHorizontalHeaderLabels(headerHQ);
	//自动排列列的内容
	ui.HQTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.HQTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	//整行选中
	ui.HQTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.HQTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetWTUI()
{
	//***************************委托表设置****************************************//
	//设置委托表格行列数量,行11行,10列
	ui.WTTable->setColumnCount(9);
	//ui.WTTable->setRowCount(10);

	QStringList headerWT;
	headerWT.append(QString::fromLocal8Bit("委托时间"));
	headerWT.append(QString::fromLocal8Bit("合约代码"));
	headerWT.append(QString::fromLocal8Bit("买卖"));
	headerWT.append(QString::fromLocal8Bit("开平"));
	headerWT.append(QString::fromLocal8Bit("数量"));
	headerWT.append(QString::fromLocal8Bit("价格"));
	headerWT.append(QString::fromLocal8Bit("状态"));
	headerWT.append(QString::fromLocal8Bit("委托号"));
	headerWT.append(QString::fromLocal8Bit("交易所"));


	//填充表格信息
	ui.WTTable->setHorizontalHeaderLabels(headerWT);
	//自动排列列的内容
	ui.WTTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.WTTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.WTTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetCJUI()
{
	//***************************成交表设置****************************************//
	//设置成交表格行列数量,行11行,10列
	ui.CJTable->setColumnCount(8);
	//ui.CJTable->setRowCount(10);

	QStringList headerCJ;
	headerCJ.append(QString::fromLocal8Bit("成交时间"));
	headerCJ.append(QString::fromLocal8Bit("合约代码"));
	headerCJ.append(QString::fromLocal8Bit("买卖"));
	headerCJ.append(QString::fromLocal8Bit("开平"));
	headerCJ.append(QString::fromLocal8Bit("数量"));
	headerCJ.append(QString::fromLocal8Bit("价格"));
	headerCJ.append(QString::fromLocal8Bit("委托号"));
	headerCJ.append(QString::fromLocal8Bit("交易所"));


	//填充表格信息
	ui.CJTable->setHorizontalHeaderLabels(headerCJ);
	//自动排列列的内容
	ui.CJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.CJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.CJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetCCUI()
{
	//***************************持仓表设置****************************************//
	//设置持仓表格行列数量,行11行,10列
	ui.CCTable->setColumnCount(4);
	//ui.CCTable->setRowCount(6);

	QStringList headerCC;
	headerCC.append(QString::fromLocal8Bit("合约代码"));
	headerCC.append(QString::fromLocal8Bit("持仓类型"));
	headerCC.append(QString::fromLocal8Bit("持仓数量"));
	headerCC.append(QString::fromLocal8Bit("持仓成本"));

	//填充表格信息
	ui.CCTable->setHorizontalHeaderLabels(headerCC);
	//自动排列列的内容
	ui.CCTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.CCTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.CCTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetZJUI()
{
	//***************************资金表设置****************************************//
	//设置资金表格行列数量,行11行,10列
	ui.ZJTable->setColumnCount(5);

	QStringList headerZJ;
	headerZJ.append(QString::fromLocal8Bit("帐户"));
	headerZJ.append(QString::fromLocal8Bit("动态权益"));
	headerZJ.append(QString::fromLocal8Bit("占用保证金"));
	headerZJ.append(QString::fromLocal8Bit("可用资金"));
	headerZJ.append(QString::fromLocal8Bit("风险度"));


	//填充表格信息
	ui.ZJTable->setHorizontalHeaderLabels(headerZJ);
	//自动排列列的内容
	ui.ZJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.ZJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.ZJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetHYUI()
{
	//***************************合约表设置****************************************//
	//设置合约表格行列数量,
	ui.HYTable->setColumnCount(4);
	//ui.HYTable->setRowCount(200);

	QStringList headerHY;
	headerHY.append(QString::fromLocal8Bit("代码"));
	headerHY.append(QString::fromLocal8Bit("合约名称"));
	headerHY.append(QString::fromLocal8Bit("合约乘数"));
	headerHY.append(QString::fromLocal8Bit("合约点数"));

	//填充表格信息
	ui.HYTable->setHorizontalHeaderLabels(headerHY);
	//自动排列列的内容
	ui.HYTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.HYTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.HYTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetAutoUI()
{
	/////////////////////////////全自动交易模块开始/////////////////////////////////////////////
	//设置行情表格行列数量,行11行,10列
	ui.AutoTable->setColumnCount(13);
	QStringList DayHeaderHQ;
	DayHeaderHQ.append(QString::fromLocal8Bit("合约代码"));
	DayHeaderHQ.append(QString::fromLocal8Bit("更新时间"));
	DayHeaderHQ.append(QString::fromLocal8Bit("开仓价格"));
	DayHeaderHQ.append(QString::fromLocal8Bit("持仓类型"));
	DayHeaderHQ.append(QString::fromLocal8Bit("持仓数量"));
	DayHeaderHQ.append(QString::fromLocal8Bit("当前盈亏"));
	DayHeaderHQ.append(QString::fromLocal8Bit("平仓时间"));
	DayHeaderHQ.append(QString::fromLocal8Bit("保证金比例(%)"));
	DayHeaderHQ.append(QString::fromLocal8Bit("亏损比例(%)"));
	DayHeaderHQ.append(QString::fromLocal8Bit("开盘价"));
	DayHeaderHQ.append(QString::fromLocal8Bit("买一价"));
	DayHeaderHQ.append(QString::fromLocal8Bit("卖一价"));
	DayHeaderHQ.append(QString::fromLocal8Bit("最新价"));
	//填充表格信息
	ui.AutoTable->setHorizontalHeaderLabels(DayHeaderHQ);
	//自动排列列的内容
	//ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	//ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.AutoTable->horizontalHeader()->setSectionResizeMode(7, QHeaderView::ResizeToContents);
	ui.AutoTable->horizontalHeader()->setSectionResizeMode(8, QHeaderView::ResizeToContents);
	//整行选中
	ui.AutoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	//ui.AutoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ReadTxt("config/pz.txt", 0);
	ui.radiostop->setChecked(true);

	/////////////////////////////全自动交易模块结束/////////////////////////////////////////////
}

void TradeSystem::SetUI()
{
	connect(md, SIGNAL(sendData(QString)), this, SLOT(ReceiveHQ(QString)));
	connect(md, SIGNAL(sendData(QString)), this, SLOT(ReceiveAutoHQ(QString)));
	connect(td, SIGNAL(sendCJ(QString)), this, SLOT(ReceiveCJ(QString)));
	connect(td, SIGNAL(sendWT(QString)), this, SLOT(ReceiveWT(QString)));
	connect(td, SIGNAL(sendHY(QString)), this, SLOT(ReceiveHY(QString)));
	connect(td, SIGNAL(sendCC(QString)), this, SLOT(ReceiveCC(QString)));
	connect(td, SIGNAL(sendCC(QString)), this, SLOT(ReceiveAutoCC(QString)));
	connect(td, SIGNAL(sendZJ(QString)), this, SLOT(ReceiveZJ(QString)));
	connect(ui.BtnXd, SIGNAL(clicked()), this, SLOT(xd()));
	connect(ui.Btnxml, SIGNAL(clicked()), this, SLOT(Onxml()));
	/////////////////////********************************///////////////////////////
	//设置行情地址
// 	ui.MDEdit->setText("tcp://180.168.146.187:10010");
// 	ui.TDEdit->setText("tcp://180.168.146.187:10000");
// 	ui.BIDEdit->setText("9999");
// 	ui.USEREdit->setText("049252");
	//把认证码框和密码框设置为密文框
	ui.ACEdit->setEchoMode(QLineEdit::Password);
	ui.PWDEdit->setEchoMode(QLineEdit::Password);
	//设置下单选框提示信息
	//ui.Editdm->setText("ni1609");
	//ui.EditLots->setText("2");
	//设置平今仓/市价的radio为选中
	ui.radioSJ->setChecked(true);
	ui.radioPJ->setChecked(true);
	//////////////右键菜单
	ui.WTTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.WTTable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(OnWTMenu(const QPoint&)));
	connect(ui.actioncd, SIGNAL(triggered()), this, SLOT(cd()));
}

void TradeSystem::Login()
{
	/////////////行情

	//从EditLine传过来的参数为QString数据类型，在CTP API中为char数据类型，需做如下转化
	char* MD;
	char* TD;
	char* BID;
	char* AC;
	char* APP;
	char* USER;
	char* PWD;

	QByteArray baMD = ui.MDEdit->text().toLatin1();
	QByteArray baTD = ui.TDEdit->text().toLatin1();
	QByteArray baBID = ui.BIDEdit->text().toLatin1();
	QByteArray baAC = ui.ACEdit->text().toLatin1();
	QByteArray baAPP = ui.APPEdit->text().toLatin1();
	QByteArray baUSER = ui.USEREdit->text().toLatin1();
	QByteArray baPWD = ui.PWDEdit->text().toLatin1();

	MD = baMD.data();
	TD = baTD.data();
	BID = baBID.data();
	AC = baAC.data();
	APP = baAPP.data();
	USER = baUSER.data();
	PWD = baPWD.data();

	strcpy(md->hq.FRONT_ADDR, MD);
	strcpy(md->hq.BROKER_ID, BID);
	md->Init();

	///////交易登陆
	strcpy(td->jy.FRONT_ADDR, TD);
	strcpy(td->jy.BROKER_ID, BID);
	strcpy(td->jy.AUTHCODE, AC);
	strcpy(td->jy.APPID, APP);
	strcpy(td->jy.INVESTOR_ID, USER);
	strcpy(td->jy.PASSWORD, PWD);
	td->Init();
}

int hy(QString dm)
{
	int hycs;
	for (int i = 0; i < 500; i++)
	{
		if (dm == hyarray[i][0])
		{
			hycs = hyarray[i][2].toInt();
			break;
		}
	}
	return hycs;
}

void TradeSystem::ReceiveHQ(QString TICK)
{
	QStringList  strlist = TICK.split(",");	   //接收StringList数据
	WriteTxt("data/"+strlist.at(0) + ".txt", TICK);
	WriteDB(TICK);

	if (strlist.at(0) == ui.Editdm->text())
	{
		ui.labelAsk->setText(strlist.at(5));
		ui.labelLast->setText(strlist.at(2));
		ui.labelBid->setText(strlist.at(3));
		ui.labelUp->setText(strlist.at(9));
		ui.labelDown->setText(strlist.at(10));
	}

	//循环传入的数据
	for (int i = 0; i < ui.HQTable->rowCount(); i++)   //以 HQTable数量为边界
	{
		if (ui.HQTable->item(i, 0)->text() == strlist.at(0))
		{
			ui.HQTable->setItem(i, 0, new QTableWidgetItem(strlist.at(0)));	  //更新数据
			ui.HQTable->setItem(i, 1, new QTableWidgetItem(strlist.at(13)));	  //更新数据
			ui.HQTable->setItem(i, 2, new QTableWidgetItem(strlist.at(1)));	  //更新数据
			ui.HQTable->setItem(i, 3, new QTableWidgetItem(strlist.at(2)));	  //更新数据
			ui.HQTable->setItem(i, 4, new QTableWidgetItem(strlist.at(3)));	  //更新数据
			ui.HQTable->setItem(i, 5, new QTableWidgetItem(strlist.at(4)));	  //更新数据
			ui.HQTable->setItem(i, 6, new QTableWidgetItem(strlist.at(5)));	  //更新数据
			ui.HQTable->setItem(i, 7, new QTableWidgetItem(strlist.at(6)));	  //更新数据
			ui.HQTable->setItem(i, 8, new QTableWidgetItem(strlist.at(7)));	  //更新数据
			ui.HQTable->setItem(i, 9, new QTableWidgetItem(strlist.at(8)));	  //更新数据
			ui.HQTable->setItem(i, 10, new QTableWidgetItem(strlist.at(9)));	  //更新数据
			ui.HQTable->setItem(i, 11, new QTableWidgetItem(strlist.at(10)));	  //更新数据
			return;
		}
	}
	int row = ui.HQTable->rowCount();
	ui.HQTable->insertRow(row);
	ui.HQTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
	ui.HQTable->setItem(row, 1, new QTableWidgetItem(strlist.at(13)));
	ui.HQTable->setItem(row, 2, new QTableWidgetItem(strlist.at(1)));
	ui.HQTable->setItem(row, 3, new QTableWidgetItem(strlist.at(2)));
	ui.HQTable->setItem(row, 4, new QTableWidgetItem(strlist.at(3)));
	ui.HQTable->setItem(row, 5, new QTableWidgetItem(strlist.at(4)));
	ui.HQTable->setItem(row, 6, new QTableWidgetItem(strlist.at(5)));
	ui.HQTable->setItem(row, 7, new QTableWidgetItem(strlist.at(6)));
	ui.HQTable->setItem(row, 8, new QTableWidgetItem(strlist.at(7)));
	ui.HQTable->setItem(row, 9, new QTableWidgetItem(strlist.at(8)));
	ui.HQTable->setItem(row, 10, new QTableWidgetItem(strlist.at(9)));
	ui.HQTable->setItem(row, 11, new QTableWidgetItem(strlist.at(10)));

}

void TradeSystem::ReceiveCJ(QString CJData)
{

	QStringList strlist = CJData.split(",");

	QString buysell = "";
	QString openclose = "";
	if (strlist.at(2) == "0")
	{
		buysell = QString::fromLocal8Bit("买入");
	}
	else
	{
		buysell = QString::fromLocal8Bit("卖出");
	}
	if (strlist.at(3) == "0")
	{
		openclose = QString::fromLocal8Bit("开仓");
	}
	else if (strlist.at(3) == "4")
	{
		openclose = QString::fromLocal8Bit("平昨");
	}
	else
	{
		openclose = QString::fromLocal8Bit("平今");
	}
	//0是开仓,3是平今，4是平昨
	int row = ui.CJTable->rowCount();
	ui.CJTable->insertRow(row);
	ui.CJTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
	ui.CJTable->setItem(row, 1, new QTableWidgetItem(strlist.at(1)));
	ui.CJTable->setItem(row, 2, new QTableWidgetItem(buysell));
	ui.CJTable->setItem(row, 3, new QTableWidgetItem(openclose));
	ui.CJTable->setItem(row, 4, new QTableWidgetItem(strlist.at(4)));
	ui.CJTable->setItem(row, 5, new QTableWidgetItem(strlist.at(5)));
	ui.CJTable->setItem(row, 6, new QTableWidgetItem(strlist.at(6)));
	ui.CJTable->setItem(row, 7, new QTableWidgetItem(strlist.at(7)));


}

void TradeSystem::ReceiveWT(QString WTData)
{
	QStringList strlist = WTData.split(",");
	if (strlist.at(8) == "")return;

	QString buysell = "";
	QString openclose = "";
	if (strlist.at(2) == "0")
	{
		buysell = QString::fromLocal8Bit("买入");
	}
	else
	{
		buysell = QString::fromLocal8Bit("卖出");
	}
	if (strlist.at(3) == "0")
	{
		openclose = QString::fromLocal8Bit("开仓");
	}
	else if (strlist.at(3) == "4")
	{
		openclose = QString::fromLocal8Bit("平昨");
	}
	else
	{
		openclose = QString::fromLocal8Bit("平今");
	}
	//0是开仓,3是平今，4是平昨


	//循环传入的数据
	for (int i = 0; i < ui.WTTable->rowCount(); i++)   //以 WTTable数量为边界
	{
		if (ui.WTTable->item(i, 0)->text() == strlist.at(0))
		{

			ui.WTTable->setItem(i, 0, new QTableWidgetItem(strlist.at(0)));	  //更新数据
			ui.WTTable->setItem(i, 1, new QTableWidgetItem(strlist.at(1)));	  //更新数据
			ui.WTTable->setItem(i, 2, new QTableWidgetItem(buysell));	  //更新数据
			ui.WTTable->setItem(i, 3, new QTableWidgetItem(openclose));	  //更新数据
			ui.WTTable->setItem(i, 4, new QTableWidgetItem(strlist.at(4)));	  //更新数据
			ui.WTTable->setItem(i, 5, new QTableWidgetItem(strlist.at(6)));	  //更新数据
			ui.WTTable->setItem(i, 6, new QTableWidgetItem(strlist.at(7)));	  //更新数据
			ui.WTTable->setItem(i, 7, new QTableWidgetItem(strlist.at(8)));	  //更新数据
			ui.WTTable->setItem(i, 8, new QTableWidgetItem(strlist.at(9)));	  //更新数据

			return;
		}

	}

	int row = ui.WTTable->rowCount();
	ui.WTTable->insertRow(row);
	ui.WTTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
	ui.WTTable->setItem(row, 1, new QTableWidgetItem(strlist.at(1)));
	ui.WTTable->setItem(row, 2, new QTableWidgetItem(buysell));
	ui.WTTable->setItem(row, 3, new QTableWidgetItem(openclose));
	ui.WTTable->setItem(row, 4, new QTableWidgetItem(strlist.at(4)));
	ui.WTTable->setItem(row, 5, new QTableWidgetItem(strlist.at(6)));
	ui.WTTable->setItem(row, 6, new QTableWidgetItem(strlist.at(7)));
	ui.WTTable->setItem(row, 7, new QTableWidgetItem(strlist.at(8)));
	ui.WTTable->setItem(row, 8, new QTableWidgetItem(strlist.at(9)));

}

void TradeSystem::ReceiveCC(QString CCData)
{
	QString lx;
	QStringList strlist = CCData.split(",");
	if (strlist.at(1) == "2") { lx = QString::fromLocal8Bit("买"); }
	if (strlist.at(1) == "3") { lx = QString::fromLocal8Bit("卖"); }

	int row = ui.CCTable->rowCount();
	ui.CCTable->insertRow(row);
	ui.CCTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
	ui.CCTable->setItem(row, 1, new QTableWidgetItem(lx));
	ui.CCTable->setItem(row, 2, new QTableWidgetItem(strlist.at(2)));
	ui.CCTable->setItem(row, 3, new QTableWidgetItem(strlist.at(3)));
}

//资金数据接收方法,更新至资金表
void TradeSystem::ReceiveZJ(QString ZJData)
{
	QStringList  strlist = ZJData.split(",");	   //接收StringList数据
	//循环传入的数据
	int row = ui.ZJTable->rowCount();
	ui.ZJTable->insertRow(row);
	ui.ZJTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
	ui.ZJTable->setItem(row, 1, new QTableWidgetItem(strlist.at(1)));
	ui.ZJTable->setItem(row, 2, new QTableWidgetItem(strlist.at(2)));
	ui.ZJTable->setItem(row, 3, new QTableWidgetItem(strlist.at(3)));
	ui.ZJTable->setItem(row, 4, new QTableWidgetItem(strlist.at(4)));
}

void TradeSystem::ReceiveHY(QString HYData)
{
	QStringList  strlist = HYData.split(",");	   //接收StringList数据
	//循环传入的数据
	int row = ui.HYTable->rowCount();
	ui.HYTable->insertRow(row);
	ui.HYTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
	ui.HYTable->setItem(row, 1, new QTableWidgetItem(strlist.at(1)));
	ui.HYTable->setItem(row, 2, new QTableWidgetItem(strlist.at(2)));
	ui.HYTable->setItem(row, 3, new QTableWidgetItem(strlist.at(3)));
}

void TradeSystem::xd()
{
	QString dm = ui.Editdm->text();
	int lots = ui.EditLots->text().toInt();

	QString lx;
	double wtprice;
	double sjprice;
	double xjprice;

	int index = ui.comboXd->currentIndex();
	if (ui.radioSJ->isChecked())
	{
		if (index == 0)
		{
			lx = "kd";
			sjprice = ui.labelAsk->text().toDouble();
			wtprice = sjprice;

		}
		if (index == 1)
		{
			lx = "pd";
			sjprice = ui.labelBid->text().toDouble();
			wtprice = sjprice;
		}
		if (index == 2)
		{
			lx = "kk";
			sjprice = ui.labelBid->text().toDouble();
			wtprice = sjprice;
		}
		if (index == 3)
		{
			lx = "pk";
			sjprice = ui.labelAsk->text().toDouble();
			wtprice = sjprice;
		}
	}
	if (ui.radioXJ->isChecked())
	{
		if (index == 0)
		{
			lx = "kd";
			xjprice = ui.EditXj->text().toDouble();
			wtprice = xjprice;
		}
		if (index == 1)
		{
			lx = "pd";
			xjprice = ui.EditXj->text().toDouble();
			wtprice = xjprice;
		}
		if (index == 2)
		{
			lx = "kk";
			xjprice = ui.EditXj->text().toDouble();
			wtprice = xjprice;

		}
		if (index == 3)
		{
			lx = "pk";
			xjprice = ui.EditXj->text().toDouble();
			wtprice = xjprice;
		}
	}

	td->ReqOrderInsert(dm, lx, lots, wtprice);

}

//右键撤单（菜单）
void TradeSystem::OnWTMenu(const QPoint& pt)
{
	QMenu menu;
	menu.addAction(ui.actioncd);
	//menu.addAction(ui.actionAdd);
	menu.exec(ui.WTTable->mapToGlobal(pt));
}

void TradeSystem::cd()
{
	int i = ui.WTTable->currentIndex().row();
	QString wth = ui.WTTable->item(i, 7)->text(); //委托号
	QString jsy = ui.WTTable->item(i, 8)->text(); //交易所
	QString brokerid = ui.BIDEdit->text();


	td->ReqOrderAction(brokerid, wth, jsy);
	QMessageBox::information(this, "", QString::fromLocal8Bit("已撤单"));
}

bool TradeSystem::writexml(string& szFileName)
{
	try
	{
		TiXmlDocument* myDocument = new TiXmlDocument();  //创建一个XML的文档对象;
		TiXmlElement* RootElement = new TiXmlElement("Persons");	  //创建根元素
		myDocument->LinkEndChild(RootElement); //连接
		TiXmlElement* PersonElement = new TiXmlElement("Persons");
		RootElement->LinkEndChild(PersonElement);

		PersonElement->SetAttribute("ID", "1");	  //创建元素

		TiXmlElement* MDElement = new TiXmlElement("行情地址");
		TiXmlElement* TDElement = new TiXmlElement("交易地址");
		TiXmlElement* BIDElement = new TiXmlElement("BrokerID");
		TiXmlElement* APPElement = new TiXmlElement("APP编号");
		TiXmlElement* ACCOUNTElement = new TiXmlElement("帐号");

		PersonElement->LinkEndChild(MDElement);
		PersonElement->LinkEndChild(TDElement);
		PersonElement->LinkEndChild(BIDElement);
		PersonElement->LinkEndChild(APPElement);
		PersonElement->LinkEndChild(ACCOUNTElement);  //创建子元素并连接

		QByteArray xmlmd = ui.MDEdit->text().toLatin1();
		const char* md = xmlmd.data();	  //把QString 转化成char类型
		QByteArray xmltd = ui.TDEdit->text().toLatin1();
		const char* td = xmltd.data();
		QByteArray xmlbid = ui.BIDEdit->text().toLatin1();
		const char* bid = xmlbid.data();
		QByteArray xmlapp = ui.APPEdit->text().toLatin1();
		const char* app = xmlapp.data();
		QByteArray xmlaccount = ui.USEREdit->text().toLatin1();
		const char* account = xmlaccount.data();

		TiXmlText* MDContent = new TiXmlText(md);
		TiXmlText* TDContext = new TiXmlText(td);
		TiXmlText* BIDContext = new TiXmlText(bid);
		TiXmlText* APPContext = new TiXmlText(app);
		TiXmlText* ACCOUNTContext = new TiXmlText(account);

		MDElement->LinkEndChild(MDContent);
		TDElement->LinkEndChild(TDContext);
		BIDElement->LinkEndChild(BIDContext);
		APPElement->LinkEndChild(APPContext);
		ACCOUNTElement->LinkEndChild(ACCOUNTContext);


		CString appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = szFileName;
		myDocument->SaveFile(fullPath.c_str());	 //保存到文件
	}
	catch (string & e)
	{
		return false;
	}
	return true;
}

void TradeSystem::Onxml()
{
	string filename = "config/config.xml";
	writexml(filename);
	readxml(filename);
}

CString TradeSystem::GetAppPath()
{
	TCHAR modulePath[MAX_PATH];
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	CString strModulePath(modulePath);
	strModulePath = strModulePath.Left(strModulePath.ReverseFind(_T('\\')));
	return strModulePath;
}

bool TradeSystem::readxml(string& szFileName)
{
	try {
		CString 	appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = szFileName;

		TiXmlDocument* myDocument = new TiXmlDocument(fullPath.c_str()); //把string类型转化成char类型
		myDocument->LoadFile(); //创建一个文档对象

		TiXmlElement* RootElement = myDocument->RootElement(); //获取根元素
		TiXmlElement* FirstPerson = RootElement->FirstChildElement(); //获取第一个节点
		TiXmlElement* MDElement = FirstPerson->FirstChildElement();
		TiXmlElement* TDElement = MDElement->NextSiblingElement();
		TiXmlElement* BIDElement = TDElement->NextSiblingElement();	 //顺序获取下一个元素
		TiXmlElement* APPElement = BIDElement->NextSiblingElement();
		TiXmlElement* ACCOUNTElement = APPElement->NextSiblingElement();

		TiXmlAttribute* IDAttribute = FirstPerson->FirstAttribute();
		QString md, td, bid, app, account;
		md = MDElement->FirstChild()->Value();
		td = TDElement->FirstChild()->Value();
		bid = BIDElement->FirstChild()->Value();
		app = APPElement->FirstChild()->Value();
		account = ACCOUNTElement->FirstChild()->Value();

		ui.MDEdit->setText(md);
		ui.TDEdit->setText(td);
		ui.BIDEdit->setText(bid);
		ui.APPEdit->setText(app);
		ui.USEREdit->setText(account);
	}
	catch (string & e)
	{
		return false;
	}
	return true;
}

void TradeSystem::WriteDB(QString TICK)
{
	QStringList strlist = TICK.split(",");
	QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
	dbconn.setDatabaseName("data/TradeSystem.db");	 //在工程目录建立一个TradeSystem.db的数据库文件
	if (!dbconn.open())
	{
		QMessageBox::information(this, "", "conn error!");
	}
	else
	{
		QSqlQuery query(dbconn);
		QString creSql = "create table if not exists " + strlist.at(0) 
									+"(updateTime text primary key,"
									+"code varchar(20),"
									+"lastPrice float,"
									+"bidPrice float,"
									+"bidVolume int,"
									+"sellPrice float,"
									+"sellVolume int,"
									+"Volume int,"
									+"openPrice float,"
									+"preClosePrice float,"
									+"zf float,"
									+"ztPrice float,"
									+"dtPrice float)";
		bool creSuccess = query.exec(creSql);
		if (creSuccess)
		{
			QString insSql = "insert into " + strlist.at(0) +
				" values("
				+ "'" +strlist.at(15)+"'"+ ","
				+ "'" + strlist.at(0) + "'" + ","
				+ strlist.at(2) + ","
				+ strlist.at(3) + ","
				+ strlist.at(4) + ","
				+ strlist.at(5) + ","
				+ strlist.at(6) + ","
				+ strlist.at(8) + ","
				+ strlist.at(11) + ","
				+ strlist.at(12) + ","
				+ strlist.at(7) + ","
				+ strlist.at(9) + ","
				+ strlist.at(10)
				+ ")";
				bool insSuccess = query.exec(insSql);
		}
	}
}

void TradeSystem::WriteTxt(QString path, QString data)
{
	QFile mydata(path);
	if (mydata.open(QFile::WriteOnly | QIODevice::Append))
	{
		QTextStream out(&mydata);
		out << data + "\n";
	}
}

void TradeSystem::WriteTxt(QString path, int flag)
{
	QFile mydata(path);
	if (mydata.open(QFile::WriteOnly | QIODevice::Truncate)) //覆盖原有数据
	{
		QTextStream out(&mydata);
		for (int i = 0; i < ui.AutoTable->rowCount(); i++)
		{
			QString dm = ui.AutoTable->item(i, 0)->text();  //取代码的数据
			QString pctime = ui.AutoTable->item(i, 6)->text();
			QString bzj = ui.AutoTable->item(i, 7)->text();
			QString loss = ui.AutoTable->item(i, 8)->text();

			out << dm + "," + pctime + "," + bzj + "," + loss + "\r\n";


		}
		mydata.close();
	}
}
/* 数据显示面板
void TradeSystem::ReadTxt(QString path)
{
	QFile file(path);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!file.atEnd()) //没到最后一直读下去
		{
			QByteArray line = file.readLine();
			QString str(line);
			ui.textEdit->append(str);
		}
	}
}
*/

void TradeSystem::ReadTxt(QString path, int flag)
{
	QFile file(path);
	QStringList strdm;	 //代码list结构
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!file.atEnd())
		{
			QByteArray line = file.readLine();
			QString str(line);
			//过滤txt末尾为空
			if (str.trimmed() == "") continue;
			QStringList strlist = str.split(",");
			int row = ui.AutoTable->rowCount();
			ui.AutoTable->insertRow(row);
			ui.AutoTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
			ui.AutoTable->setItem(row, 6, new QTableWidgetItem(strlist.at(1)));
			ui.AutoTable->setItem(row, 7, new QTableWidgetItem(strlist.at(2)));
			ui.AutoTable->setItem(row, 8, new QTableWidgetItem(strlist.at(3)));
			strdm.append(strlist.at(0));
			md->dm = strdm.join(",");
		}
	}
}

void TradeSystem::OnExit()
{

}

bool pctime(QString fwqtime, QString sztime)
{
	QDateTime fwq = QDateTime::fromString(fwqtime, "hh:mm:ss");
	QDateTime sz = QDateTime::fromString(sztime, "hh:mm:ss");
	if (fwq > sz)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void TradeSystem::SubscribeHQ()
{
	QString dm;
	dm = ui.SubHQEdit->text().toLatin1();
	md->SubscribeMarketData(dm);
}

//自动交易
void TradeSystem::ReceiveAutoHQ(QString TICK)
{
	QStringList  strlist = TICK.split(",");	   //接收StringList数据

	//循环传入的数据
	for (int i = 0; i < ui.AutoTable->rowCount(); i++)   //以 HQTable数量为边界
	{
		//自动下单
		kc(i);
		pc(i);

		if (ui.AutoTable->item(i, 0)->text() == strlist.at(0))
		{

			ui.AutoTable->setItem(i, 1, new QTableWidgetItem(strlist.at(1)));	  //更新时间
			ui.AutoTable->setItem(i, 9, new QTableWidgetItem(strlist.at(11)));
			ui.AutoTable->setItem(i, 10, new QTableWidgetItem(strlist.at(3)));	  //买一价
			ui.AutoTable->setItem(i, 11, new QTableWidgetItem(strlist.at(5)));	  //卖一价
			ui.AutoTable->setItem(i, 12, new QTableWidgetItem(strlist.at(2)));	   //最新价显示

			if (ui.AutoTable->item(i, 2) == NULL)return;
			if (ui.AutoTable->item(i, 2)->text() == "") { ui.AutoTable->setItem(i, 5, new QTableWidgetItem("")); return; }

			double yk = (strlist.at(2).toDouble() - ui.AutoTable->item(i, 2)->text().toDouble()) * hy(strlist.at(0));
			ui.AutoTable->setItem(i, 5, new QTableWidgetItem(QString::number(yk)));

			return;
		}
	}
}

void TradeSystem::ReceiveAutoCC(QString CCData)
{

	QString lx;
	QStringList strlist = CCData.split(",");
	if (strlist.at(1) == "2") { lx = QString::fromLocal8Bit("买"); }
	if (strlist.at(1) == "3") { lx = QString::fromLocal8Bit("卖"); }

	for (int i = 0; i < ui.AutoTable->rowCount(); i++)
	{
		if (ui.AutoTable->item(i, 0)->text() == strlist.at(0))
		{

			ui.AutoTable->setItem(i, 2, new QTableWidgetItem(strlist.at(3)));	 //3是价格
			ui.AutoTable->setItem(i, 3, new QTableWidgetItem(lx));
			ui.AutoTable->setItem(i, 4, new QTableWidgetItem(strlist.at(2))); //2是数量 
			return;
		}
	}
}

void TradeSystem::ReceiveAutoZJ(QString ZJData)
{
	QStringList  strlist = ZJData.split(",");	   //接收StringList数据
	for (int i = 0; i < ui.AutoTable->rowCount(); i++)
	{
		if (ui.AutoTable->item(i, 0)->text() == strlist.at(0))
		{

			ui.AutoTable->setItem(i, 2, new QTableWidgetItem(strlist.at(2)));
			ui.AutoTable->setItem(i, 3, new QTableWidgetItem(strlist.at(3)));
			ui.AutoTable->setItem(i, 4, new QTableWidgetItem(strlist.at(4)));
		}
	}
}

void TradeSystem::OnAddHeyue()
{
	AddHeyue();
}

void TradeSystem::AddHeyue()
{
	int row = ui.AutoTable->rowCount();
	ui.AutoTable->insertRow(row);
	ui.AutoTable->setItem(row, 0, new QTableWidgetItem(ui.lineEditdm->text()));
	ui.AutoTable->setItem(row, 6, new QTableWidgetItem(ui.lineEditpctime->text()));
	ui.AutoTable->setItem(row, 7, new QTableWidgetItem(ui.lineEditbzj->text()));
	ui.AutoTable->setItem(row, 8, new QTableWidgetItem(ui.lineEditloss->text()));
	//订阅相关合约行情
	QString dm;
	dm = ui.lineEditdm->text().toLatin1();
	md->SubscribeMarketData(dm);
}

void TradeSystem::kc(int i)
{
	if (ui.radiorun->isChecked() == false)return;

	QString dm = ui.AutoTable->item(i, 0)->text();
	if (ui.AutoTable->item(i, 9) == NULL || ui.AutoTable->item(i, 12) == NULL)
	{
		return;
	}

	int vol = 0;
	if (ui.AutoTable->item(i, 4) != NULL)vol = ui.AutoTable->item(i, 4)->text().toInt();
	if (vol > 0)return;
	if (ui.labelzt->text() == QString::fromLocal8Bit("已开仓"))return;
	double openprice = ui.AutoTable->item(i, 9)->text().toDouble();
	double lastprice = ui.AutoTable->item(i, 12)->text().toDouble();
	double buyprice = ui.AutoTable->item(i, 10)->text().toDouble();
	double selltprice = ui.AutoTable->item(i, 11)->text().toDouble();

	if (lastprice > openprice)
	{
		td->ReqOrderInsert(dm, "kd", 1, selltprice);
		ui.labelzt->setText(QString::fromLocal8Bit("已开仓"));

	}
	if (lastprice < openprice)
	{
		td->ReqOrderInsert(dm, "kk", 1, buyprice);
		ui.labelzt->setText(QString::fromLocal8Bit("已开仓"));
	}


}

void TradeSystem::pc(int i)
{
	if (ui.radiorun->isChecked() == false)return;
	if (ui.AutoTable->item(i, 4) == NULL)return;
	QString dm = ui.AutoTable->item(i, 0)->text();
	int vol = 0;
	if (ui.AutoTable->item(i, 4) != NULL)vol = ui.AutoTable->item(i, 4)->text().toInt();
	if (vol == 0)return;
	//获取合约时间戳
	QString fwqtime = ui.AutoTable->item(i, 1)->text().trimmed();
	//获取设置平仓时间
	QString sztime = ui.AutoTable->item(i, 6)->text().trimmed();
	QString cclx = ui.AutoTable->item(i, 3)->text().trimmed();
	double openprice = ui.AutoTable->item(i, 9)->text().toDouble();
	double lastprice = ui.AutoTable->item(i, 12)->text().toDouble();
	double buyprice = ui.AutoTable->item(i, 10)->text().toDouble();
	double selltprice = ui.AutoTable->item(i, 11)->text().toDouble();

	//价格平仓
	if (vol >= 1 && cclx == "买" && lastprice < openprice)
	{
		td->ReqOrderInsert(dm, "pd", vol, buyprice);
	}
	if (vol >= 1 && cclx == "卖" && lastprice > openprice)
	{
		td->ReqOrderInsert(dm, "pk", vol, selltprice);
	}

	//时间平仓
	if (pctime(fwqtime, sztime) == true)
	{

		if (vol >= 1 && cclx == QString::fromLocal8Bit("买"))
		{
			td->ReqOrderInsert(dm, "pd", vol, buyprice);
		}
		if (vol >= 1 && cclx == QString::fromLocal8Bit("卖"))
		{
			td->ReqOrderInsert(dm, "pk", vol, selltprice);
		}

	}
}
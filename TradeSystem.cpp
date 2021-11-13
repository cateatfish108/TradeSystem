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
	//***************************���������****************************************//
	//������������������,��11��,10��
	ui.HQTable->setColumnCount(12);

	QStringList headerHQ;
	headerHQ.append(QString::fromLocal8Bit("��Լ����"));
	headerHQ.append(QString::fromLocal8Bit("����"));
	headerHQ.append(QString::fromLocal8Bit("����ʱ��"));
	headerHQ.append(QString::fromLocal8Bit("���¼�"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("�Ƿ�"));
	headerHQ.append(QString::fromLocal8Bit("�ɽ���"));
	headerHQ.append(QString::fromLocal8Bit("��ͣ��"));
	headerHQ.append(QString::fromLocal8Bit("��ͣ��"));

	//�������Ϣ
	ui.HQTable->setHorizontalHeaderLabels(headerHQ);
	//�Զ������е�����
	ui.HQTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.HQTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	//����ѡ��
	ui.HQTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.HQTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetWTUI()
{
	//***************************ί�б�����****************************************//
	//����ί�б����������,��11��,10��
	ui.WTTable->setColumnCount(9);
	//ui.WTTable->setRowCount(10);

	QStringList headerWT;
	headerWT.append(QString::fromLocal8Bit("ί��ʱ��"));
	headerWT.append(QString::fromLocal8Bit("��Լ����"));
	headerWT.append(QString::fromLocal8Bit("����"));
	headerWT.append(QString::fromLocal8Bit("��ƽ"));
	headerWT.append(QString::fromLocal8Bit("����"));
	headerWT.append(QString::fromLocal8Bit("�۸�"));
	headerWT.append(QString::fromLocal8Bit("״̬"));
	headerWT.append(QString::fromLocal8Bit("ί�к�"));
	headerWT.append(QString::fromLocal8Bit("������"));


	//�������Ϣ
	ui.WTTable->setHorizontalHeaderLabels(headerWT);
	//�Զ������е�����
	ui.WTTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.WTTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.WTTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetCJUI()
{
	//***************************�ɽ�������****************************************//
	//���óɽ������������,��11��,10��
	ui.CJTable->setColumnCount(8);
	//ui.CJTable->setRowCount(10);

	QStringList headerCJ;
	headerCJ.append(QString::fromLocal8Bit("�ɽ�ʱ��"));
	headerCJ.append(QString::fromLocal8Bit("��Լ����"));
	headerCJ.append(QString::fromLocal8Bit("����"));
	headerCJ.append(QString::fromLocal8Bit("��ƽ"));
	headerCJ.append(QString::fromLocal8Bit("����"));
	headerCJ.append(QString::fromLocal8Bit("�۸�"));
	headerCJ.append(QString::fromLocal8Bit("ί�к�"));
	headerCJ.append(QString::fromLocal8Bit("������"));


	//�������Ϣ
	ui.CJTable->setHorizontalHeaderLabels(headerCJ);
	//�Զ������е�����
	ui.CJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.CJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.CJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetCCUI()
{
	//***************************�ֱֲ�����****************************************//
	//���óֱֲ����������,��11��,10��
	ui.CCTable->setColumnCount(4);
	//ui.CCTable->setRowCount(6);

	QStringList headerCC;
	headerCC.append(QString::fromLocal8Bit("��Լ����"));
	headerCC.append(QString::fromLocal8Bit("�ֲ�����"));
	headerCC.append(QString::fromLocal8Bit("�ֲ�����"));
	headerCC.append(QString::fromLocal8Bit("�ֲֳɱ�"));

	//�������Ϣ
	ui.CCTable->setHorizontalHeaderLabels(headerCC);
	//�Զ������е�����
	ui.CCTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.CCTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.CCTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetZJUI()
{
	//***************************�ʽ������****************************************//
	//�����ʽ�����������,��11��,10��
	ui.ZJTable->setColumnCount(5);

	QStringList headerZJ;
	headerZJ.append(QString::fromLocal8Bit("�ʻ�"));
	headerZJ.append(QString::fromLocal8Bit("��̬Ȩ��"));
	headerZJ.append(QString::fromLocal8Bit("ռ�ñ�֤��"));
	headerZJ.append(QString::fromLocal8Bit("�����ʽ�"));
	headerZJ.append(QString::fromLocal8Bit("���ն�"));


	//�������Ϣ
	ui.ZJTable->setHorizontalHeaderLabels(headerZJ);
	//�Զ������е�����
	ui.ZJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.ZJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.ZJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetHYUI()
{
	//***************************��Լ������****************************************//
	//���ú�Լ�����������,
	ui.HYTable->setColumnCount(4);
	//ui.HYTable->setRowCount(200);

	QStringList headerHY;
	headerHY.append(QString::fromLocal8Bit("����"));
	headerHY.append(QString::fromLocal8Bit("��Լ����"));
	headerHY.append(QString::fromLocal8Bit("��Լ����"));
	headerHY.append(QString::fromLocal8Bit("��Լ����"));

	//�������Ϣ
	ui.HYTable->setHorizontalHeaderLabels(headerHY);
	//�Զ������е�����
	ui.HYTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.HYTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.HYTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TradeSystem::SetAutoUI()
{
	/////////////////////////////ȫ�Զ�����ģ�鿪ʼ/////////////////////////////////////////////
	//������������������,��11��,10��
	ui.AutoTable->setColumnCount(13);
	QStringList DayHeaderHQ;
	DayHeaderHQ.append(QString::fromLocal8Bit("��Լ����"));
	DayHeaderHQ.append(QString::fromLocal8Bit("����ʱ��"));
	DayHeaderHQ.append(QString::fromLocal8Bit("���ּ۸�"));
	DayHeaderHQ.append(QString::fromLocal8Bit("�ֲ�����"));
	DayHeaderHQ.append(QString::fromLocal8Bit("�ֲ�����"));
	DayHeaderHQ.append(QString::fromLocal8Bit("��ǰӯ��"));
	DayHeaderHQ.append(QString::fromLocal8Bit("ƽ��ʱ��"));
	DayHeaderHQ.append(QString::fromLocal8Bit("��֤�����(%)"));
	DayHeaderHQ.append(QString::fromLocal8Bit("�������(%)"));
	DayHeaderHQ.append(QString::fromLocal8Bit("���̼�"));
	DayHeaderHQ.append(QString::fromLocal8Bit("��һ��"));
	DayHeaderHQ.append(QString::fromLocal8Bit("��һ��"));
	DayHeaderHQ.append(QString::fromLocal8Bit("���¼�"));
	//�������Ϣ
	ui.AutoTable->setHorizontalHeaderLabels(DayHeaderHQ);
	//�Զ������е�����
	//ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	//ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui.AutoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.AutoTable->horizontalHeader()->setSectionResizeMode(7, QHeaderView::ResizeToContents);
	ui.AutoTable->horizontalHeader()->setSectionResizeMode(8, QHeaderView::ResizeToContents);
	//����ѡ��
	ui.AutoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	//ui.AutoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ReadTxt("config/pz.txt", 0);
	ui.radiostop->setChecked(true);

	/////////////////////////////ȫ�Զ�����ģ�����/////////////////////////////////////////////
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
	//���������ַ
// 	ui.MDEdit->setText("tcp://180.168.146.187:10010");
// 	ui.TDEdit->setText("tcp://180.168.146.187:10000");
// 	ui.BIDEdit->setText("9999");
// 	ui.USEREdit->setText("049252");
	//����֤�������������Ϊ���Ŀ�
	ui.ACEdit->setEchoMode(QLineEdit::Password);
	ui.PWDEdit->setEchoMode(QLineEdit::Password);
	//�����µ�ѡ����ʾ��Ϣ
	//ui.Editdm->setText("ni1609");
	//ui.EditLots->setText("2");
	//����ƽ���/�м۵�radioΪѡ��
	ui.radioSJ->setChecked(true);
	ui.radioPJ->setChecked(true);
	//////////////�Ҽ��˵�
	ui.WTTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.WTTable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(OnWTMenu(const QPoint&)));
	connect(ui.actioncd, SIGNAL(triggered()), this, SLOT(cd()));
}

void TradeSystem::Login()
{
	/////////////����

	//��EditLine�������Ĳ���ΪQString�������ͣ���CTP API��Ϊchar�������ͣ���������ת��
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

	///////���׵�½
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
	QStringList  strlist = TICK.split(",");	   //����StringList����
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

	//ѭ�����������
	for (int i = 0; i < ui.HQTable->rowCount(); i++)   //�� HQTable����Ϊ�߽�
	{
		if (ui.HQTable->item(i, 0)->text() == strlist.at(0))
		{
			ui.HQTable->setItem(i, 0, new QTableWidgetItem(strlist.at(0)));	  //��������
			ui.HQTable->setItem(i, 1, new QTableWidgetItem(strlist.at(13)));	  //��������
			ui.HQTable->setItem(i, 2, new QTableWidgetItem(strlist.at(1)));	  //��������
			ui.HQTable->setItem(i, 3, new QTableWidgetItem(strlist.at(2)));	  //��������
			ui.HQTable->setItem(i, 4, new QTableWidgetItem(strlist.at(3)));	  //��������
			ui.HQTable->setItem(i, 5, new QTableWidgetItem(strlist.at(4)));	  //��������
			ui.HQTable->setItem(i, 6, new QTableWidgetItem(strlist.at(5)));	  //��������
			ui.HQTable->setItem(i, 7, new QTableWidgetItem(strlist.at(6)));	  //��������
			ui.HQTable->setItem(i, 8, new QTableWidgetItem(strlist.at(7)));	  //��������
			ui.HQTable->setItem(i, 9, new QTableWidgetItem(strlist.at(8)));	  //��������
			ui.HQTable->setItem(i, 10, new QTableWidgetItem(strlist.at(9)));	  //��������
			ui.HQTable->setItem(i, 11, new QTableWidgetItem(strlist.at(10)));	  //��������
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
		buysell = QString::fromLocal8Bit("����");
	}
	else
	{
		buysell = QString::fromLocal8Bit("����");
	}
	if (strlist.at(3) == "0")
	{
		openclose = QString::fromLocal8Bit("����");
	}
	else if (strlist.at(3) == "4")
	{
		openclose = QString::fromLocal8Bit("ƽ��");
	}
	else
	{
		openclose = QString::fromLocal8Bit("ƽ��");
	}
	//0�ǿ���,3��ƽ��4��ƽ��
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
		buysell = QString::fromLocal8Bit("����");
	}
	else
	{
		buysell = QString::fromLocal8Bit("����");
	}
	if (strlist.at(3) == "0")
	{
		openclose = QString::fromLocal8Bit("����");
	}
	else if (strlist.at(3) == "4")
	{
		openclose = QString::fromLocal8Bit("ƽ��");
	}
	else
	{
		openclose = QString::fromLocal8Bit("ƽ��");
	}
	//0�ǿ���,3��ƽ��4��ƽ��


	//ѭ�����������
	for (int i = 0; i < ui.WTTable->rowCount(); i++)   //�� WTTable����Ϊ�߽�
	{
		if (ui.WTTable->item(i, 0)->text() == strlist.at(0))
		{

			ui.WTTable->setItem(i, 0, new QTableWidgetItem(strlist.at(0)));	  //��������
			ui.WTTable->setItem(i, 1, new QTableWidgetItem(strlist.at(1)));	  //��������
			ui.WTTable->setItem(i, 2, new QTableWidgetItem(buysell));	  //��������
			ui.WTTable->setItem(i, 3, new QTableWidgetItem(openclose));	  //��������
			ui.WTTable->setItem(i, 4, new QTableWidgetItem(strlist.at(4)));	  //��������
			ui.WTTable->setItem(i, 5, new QTableWidgetItem(strlist.at(6)));	  //��������
			ui.WTTable->setItem(i, 6, new QTableWidgetItem(strlist.at(7)));	  //��������
			ui.WTTable->setItem(i, 7, new QTableWidgetItem(strlist.at(8)));	  //��������
			ui.WTTable->setItem(i, 8, new QTableWidgetItem(strlist.at(9)));	  //��������

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
	if (strlist.at(1) == "2") { lx = QString::fromLocal8Bit("��"); }
	if (strlist.at(1) == "3") { lx = QString::fromLocal8Bit("��"); }

	int row = ui.CCTable->rowCount();
	ui.CCTable->insertRow(row);
	ui.CCTable->setItem(row, 0, new QTableWidgetItem(strlist.at(0)));
	ui.CCTable->setItem(row, 1, new QTableWidgetItem(lx));
	ui.CCTable->setItem(row, 2, new QTableWidgetItem(strlist.at(2)));
	ui.CCTable->setItem(row, 3, new QTableWidgetItem(strlist.at(3)));
}

//�ʽ����ݽ��շ���,�������ʽ��
void TradeSystem::ReceiveZJ(QString ZJData)
{
	QStringList  strlist = ZJData.split(",");	   //����StringList����
	//ѭ�����������
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
	QStringList  strlist = HYData.split(",");	   //����StringList����
	//ѭ�����������
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

//�Ҽ��������˵���
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
	QString wth = ui.WTTable->item(i, 7)->text(); //ί�к�
	QString jsy = ui.WTTable->item(i, 8)->text(); //������
	QString brokerid = ui.BIDEdit->text();


	td->ReqOrderAction(brokerid, wth, jsy);
	QMessageBox::information(this, "", QString::fromLocal8Bit("�ѳ���"));
}

bool TradeSystem::writexml(string& szFileName)
{
	try
	{
		TiXmlDocument* myDocument = new TiXmlDocument();  //����һ��XML���ĵ�����;
		TiXmlElement* RootElement = new TiXmlElement("Persons");	  //������Ԫ��
		myDocument->LinkEndChild(RootElement); //����
		TiXmlElement* PersonElement = new TiXmlElement("Persons");
		RootElement->LinkEndChild(PersonElement);

		PersonElement->SetAttribute("ID", "1");	  //����Ԫ��

		TiXmlElement* MDElement = new TiXmlElement("�����ַ");
		TiXmlElement* TDElement = new TiXmlElement("���׵�ַ");
		TiXmlElement* BIDElement = new TiXmlElement("BrokerID");
		TiXmlElement* APPElement = new TiXmlElement("APP���");
		TiXmlElement* ACCOUNTElement = new TiXmlElement("�ʺ�");

		PersonElement->LinkEndChild(MDElement);
		PersonElement->LinkEndChild(TDElement);
		PersonElement->LinkEndChild(BIDElement);
		PersonElement->LinkEndChild(APPElement);
		PersonElement->LinkEndChild(ACCOUNTElement);  //������Ԫ�ز�����

		QByteArray xmlmd = ui.MDEdit->text().toLatin1();
		const char* md = xmlmd.data();	  //��QString ת����char����
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
		myDocument->SaveFile(fullPath.c_str());	 //���浽�ļ�
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

		TiXmlDocument* myDocument = new TiXmlDocument(fullPath.c_str()); //��string����ת����char����
		myDocument->LoadFile(); //����һ���ĵ�����

		TiXmlElement* RootElement = myDocument->RootElement(); //��ȡ��Ԫ��
		TiXmlElement* FirstPerson = RootElement->FirstChildElement(); //��ȡ��һ���ڵ�
		TiXmlElement* MDElement = FirstPerson->FirstChildElement();
		TiXmlElement* TDElement = MDElement->NextSiblingElement();
		TiXmlElement* BIDElement = TDElement->NextSiblingElement();	 //˳���ȡ��һ��Ԫ��
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
	QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
	dbconn.setDatabaseName("data/TradeSystem.db");	 //�ڹ���Ŀ¼����һ��TradeSystem.db�����ݿ��ļ�
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
	if (mydata.open(QFile::WriteOnly | QIODevice::Truncate)) //����ԭ������
	{
		QTextStream out(&mydata);
		for (int i = 0; i < ui.AutoTable->rowCount(); i++)
		{
			QString dm = ui.AutoTable->item(i, 0)->text();  //ȡ���������
			QString pctime = ui.AutoTable->item(i, 6)->text();
			QString bzj = ui.AutoTable->item(i, 7)->text();
			QString loss = ui.AutoTable->item(i, 8)->text();

			out << dm + "," + pctime + "," + bzj + "," + loss + "\r\n";


		}
		mydata.close();
	}
}
/* ������ʾ���
void TradeSystem::ReadTxt(QString path)
{
	QFile file(path);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!file.atEnd()) //û�����һֱ����ȥ
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
	QStringList strdm;	 //����list�ṹ
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!file.atEnd())
		{
			QByteArray line = file.readLine();
			QString str(line);
			//����txtĩβΪ��
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

//�Զ�����
void TradeSystem::ReceiveAutoHQ(QString TICK)
{
	QStringList  strlist = TICK.split(",");	   //����StringList����

	//ѭ�����������
	for (int i = 0; i < ui.AutoTable->rowCount(); i++)   //�� HQTable����Ϊ�߽�
	{
		//�Զ��µ�
		kc(i);
		pc(i);

		if (ui.AutoTable->item(i, 0)->text() == strlist.at(0))
		{

			ui.AutoTable->setItem(i, 1, new QTableWidgetItem(strlist.at(1)));	  //����ʱ��
			ui.AutoTable->setItem(i, 9, new QTableWidgetItem(strlist.at(11)));
			ui.AutoTable->setItem(i, 10, new QTableWidgetItem(strlist.at(3)));	  //��һ��
			ui.AutoTable->setItem(i, 11, new QTableWidgetItem(strlist.at(5)));	  //��һ��
			ui.AutoTable->setItem(i, 12, new QTableWidgetItem(strlist.at(2)));	   //���¼���ʾ

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
	if (strlist.at(1) == "2") { lx = QString::fromLocal8Bit("��"); }
	if (strlist.at(1) == "3") { lx = QString::fromLocal8Bit("��"); }

	for (int i = 0; i < ui.AutoTable->rowCount(); i++)
	{
		if (ui.AutoTable->item(i, 0)->text() == strlist.at(0))
		{

			ui.AutoTable->setItem(i, 2, new QTableWidgetItem(strlist.at(3)));	 //3�Ǽ۸�
			ui.AutoTable->setItem(i, 3, new QTableWidgetItem(lx));
			ui.AutoTable->setItem(i, 4, new QTableWidgetItem(strlist.at(2))); //2������ 
			return;
		}
	}
}

void TradeSystem::ReceiveAutoZJ(QString ZJData)
{
	QStringList  strlist = ZJData.split(",");	   //����StringList����
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
	//������غ�Լ����
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
	if (ui.labelzt->text() == QString::fromLocal8Bit("�ѿ���"))return;
	double openprice = ui.AutoTable->item(i, 9)->text().toDouble();
	double lastprice = ui.AutoTable->item(i, 12)->text().toDouble();
	double buyprice = ui.AutoTable->item(i, 10)->text().toDouble();
	double selltprice = ui.AutoTable->item(i, 11)->text().toDouble();

	if (lastprice > openprice)
	{
		td->ReqOrderInsert(dm, "kd", 1, selltprice);
		ui.labelzt->setText(QString::fromLocal8Bit("�ѿ���"));

	}
	if (lastprice < openprice)
	{
		td->ReqOrderInsert(dm, "kk", 1, buyprice);
		ui.labelzt->setText(QString::fromLocal8Bit("�ѿ���"));
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
	//��ȡ��Լʱ���
	QString fwqtime = ui.AutoTable->item(i, 1)->text().trimmed();
	//��ȡ����ƽ��ʱ��
	QString sztime = ui.AutoTable->item(i, 6)->text().trimmed();
	QString cclx = ui.AutoTable->item(i, 3)->text().trimmed();
	double openprice = ui.AutoTable->item(i, 9)->text().toDouble();
	double lastprice = ui.AutoTable->item(i, 12)->text().toDouble();
	double buyprice = ui.AutoTable->item(i, 10)->text().toDouble();
	double selltprice = ui.AutoTable->item(i, 11)->text().toDouble();

	//�۸�ƽ��
	if (vol >= 1 && cclx == "��" && lastprice < openprice)
	{
		td->ReqOrderInsert(dm, "pd", vol, buyprice);
	}
	if (vol >= 1 && cclx == "��" && lastprice > openprice)
	{
		td->ReqOrderInsert(dm, "pk", vol, selltprice);
	}

	//ʱ��ƽ��
	if (pctime(fwqtime, sztime) == true)
	{

		if (vol >= 1 && cclx == QString::fromLocal8Bit("��"))
		{
			td->ReqOrderInsert(dm, "pd", vol, buyprice);
		}
		if (vol >= 1 && cclx == QString::fromLocal8Bit("��"))
		{
			td->ReqOrderInsert(dm, "pk", vol, selltprice);
		}

	}
}
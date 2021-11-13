#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TradeSystem.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "MdSpi.h"
#include "TdSpi.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <atlstr.h>	  //Cstring函数头文件
using namespace std;

class TradeSystem : public QMainWindow
{
	Q_OBJECT

public:
	TradeSystem(QWidget *parent = Q_NULLPTR);
	~TradeSystem();
	MdSpi* md;
	TdSpi* td;
private:
	void SetHQUI();
	void SetWTUI();
	void SetCJUI();
	void SetCCUI();
	void SetZJUI();
	void SetHYUI();
	void SetAutoUI();
	void SetUI();

private slots:
	void Login();
	void xd();
	void ReceiveHQ(QString);
	void ReceiveCJ(QString);
	void ReceiveWT(QString);
	void ReceiveCC(QString);
	void ReceiveZJ(QString);
	void ReceiveHY(QString);
	void OnWTMenu(const QPoint& pt);
	void cd();
	void Onxml();
	void OnExit();
	void SubscribeHQ();

	CString GetAppPath();
	bool writexml(string& szFileName); //xml写入
	bool readxml(string& szFileName);//xml读取
	//自动交易
	void ReceiveAutoHQ(QString);
	void ReceiveAutoCC(QString);
	void ReceiveAutoZJ(QString);
	void OnAddHeyue();  //自动交易合约添加

private:
	Ui::TradeSystemClass ui;
	void WriteDB(QString TICK);
	void WriteTxt(QString path, QString data);
	void WriteTxt(QString path, int flag);
	void ReadTxt(QString path);
	void ReadTxt(QString path, int flag);
	//自动交易
	void AddHeyue();
	void kc(int);
	void pc(int);
};

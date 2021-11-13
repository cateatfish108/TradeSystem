#include "MdSpi.h"
#include <iostream>
#include <QstringList>
using namespace std;
#include<typeinfo>

#pragma warning(disable: 4996)

char* ppInstrumentID []={"IF1609","ni1609","ru1609","SR609","cu1609","TA609"};	
int iInstrumentID=6;
// ������
int iRequestID;

MdSpi::MdSpi(QObject *parent)
	: QObject(parent)
{

}

MdSpi::~MdSpi()
{

}

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
						int nRequestID, bool bIsLast)
{
	cerr << "--->>> "<< __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

void MdSpi::OnFrontDisconnected(int nReason)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> Reason = " << nReason << endl;
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void MdSpi::OnFrontConnected()
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	///�û���¼����
	ReqUserLogin();
}


void MdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, hq.BROKER_ID);
	strcpy(req.UserID, "");
	strcpy(req.Password, "");
	int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> �����û���¼����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
							CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///��ȡ��ǰ������
		cerr << "--->>> ��ȡ��ǰ������ = " << pUserApi->GetTradingDay() << endl;
		// ����������
		SubscribeMarketData();
		SubscribeMarketData(dm);  //
	}
}
//
void MdSpi::SubscribeMarketData()
{
	int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> �������鶩������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}
//�Զ�����ģ�黯������벿��
void MdSpi::SubscribeMarketData(QString dm)
{
	QStringList strlist=dm.split(",");
	int iInstrumentID=strlist.length();
	for (int i=0;i<iInstrumentID;i++)
	{
		QString str=strlist.at(i);
		char *ch;
		QByteArray ba=str.toLatin1();
		ch=ba.data();
		char *myppInstrumentID[]={ch};
		int iRequestID=pUserApi->SubscribeMarketData(myppInstrumentID,1); //ÿ��ֻ����һ��
		
	}
	cerr<<"--->>>�������鶩������:"<<((iRequestID==0)?"�ɹ�":"ʧ��")<<endl;
}



void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}
//���غ�Լ���������Ϣ
void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//cerr << __FUNCTION__ << endl;
	QString dm = pDepthMarketData->InstrumentID;   //
	//char TDay[9];
	//memcpy(TDay, pDepthMarketData->TradingDay, sizeof(TDay));
	//QString tradeingday = TDay[0] + TDay[1] + TDay[2] + TDay[3] + "-" + TDay[4] + TDay[5] + TDay[6] + TDay[7];//������
	//cerr << "pDepthMarketData->TradingDay :" << typeid(pDepthMarketData->TradingDay).name() << endl;
	//cerr << "QString tradeingday :" << typeid(tradeingday).name() << endl;
	QString tradeingday = pDepthMarketData->TradingDay;
	tradeingday.insert(4, QString("-"));
	tradeingday.insert(7, QString("-"));
	QString updatetime = pDepthMarketData->UpdateTime; // ����ʱ��
	QString updatemillisec = pDepthMarketData->UpdateMillisec; //���º���
	QString datetime = tradeingday+" " + updatetime + "." + updatemillisec;
	QString lastprice = QString::number(pDepthMarketData->LastPrice);	  //���¼�
	QString buyprice = QString::number(pDepthMarketData->BidPrice1); //��һ��
	QString buyvol=QString::number(pDepthMarketData->BidVolume1);//��һ��
	QString sellprice =QString::number(pDepthMarketData->AskPrice1); //��һ��
	QString sellvol = QString::number(pDepthMarketData->AskVolume1); //��һ��
	QString preLastPrice = QString::number(pDepthMarketData->PreClosePrice); //�����̼�
	QString zf = QString::number(((pDepthMarketData->LastPrice-pDepthMarketData->PreClosePrice)*100/pDepthMarketData->PreClosePrice),'f',2);  //�Ƿ��ļ���
	QString vol = QString::number(pDepthMarketData->Volume); //�ɽ���
	QString zt = QString::number(pDepthMarketData->UpperLimitPrice); //��ͣ��
	QString dt = QString::number(pDepthMarketData->LowerLimitPrice); //��ͣ��
	QString openprice=QString::number(pDepthMarketData->OpenPrice);	 //���̼�

	QString HQTick = dm+","+ updatetime +","+lastprice+","+buyprice+","+buyvol+","+sellprice+","+sellvol+","+zf+","+vol+","+zt+","+dt+","+openprice + "," + preLastPrice + "," + tradeingday + "," + updatemillisec+ "," + datetime;	 //ʹ���źŴ�������
	emit sendData(HQTick); //ֻ�Ƿ��������ݣ���Ҫ���ն˽������� ��a,��ctp.hͷ�ļ�������շ��� b, ͨ��SLOT����
}

bool MdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}

void MdSpi::Init()
{
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
	pUserApi->RegisterSpi(this);
	pUserApi->RegisterFront(hq.FRONT_ADDR);
	pUserApi->Init();
}

#ifndef TDSPI_H
#define TDSPI_H

#include <QObject>
#include "ThostFtdcTraderApi.h"



class TdSpi : public QObject,public CThostFtdcTraderSpi
{
	Q_OBJECT

public:
	typedef struct TDStruct
	{
		 char FRONT_ADDR[100];
		 TThostFtdcBrokerIDType BROKER_ID;
		 TThostFtdcAuthCodeType AUTHCODE;
		 TThostFtdcAppIDType APPID;
		 TThostFtdcInvestorIDType INVESTOR_ID;
		 TThostFtdcPasswordKeyType PASSWORD;
	};
	TDStruct jy;
	//��Լ�ṹ
	typedef struct HYStruct
	{
		  int hycs;
		  double hyds;
	};

	HYStruct hy(QString);

	void Init();
	// USER_API����
	CThostFtdcTraderApi* pUserApi;
	
signals:
	void sendCJ(QString);
	void sendWT(QString);
	void sendCC(QString);
	void sendZJ(QString);
	void sendHY(QString);
	void xd();

public:
	TdSpi(QObject *parent);
	~TdSpi();
	TdSpi *td;

private:

public:
	///����¼������
	void ReqOrderInsert(QString dm,QString lx,int lots,double price);
	///������������
	void ReqOrderAction(QString brokerid,QString wth,QString jys);
	///������������
	//void ReqOrderAction(CThostFtdcOrderField *pOrder);

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///��֤����
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��Ӧ---��Լ��ѯ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ʽ��˻���Ӧ  --�ʽ��ѯ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���Ӧ--  �ֲֲ�ѯ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ���������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///����֪ͨ--------------/ί�лر�
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///�ɽ�֪ͨ--------------/�ɽ��ر�
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

private:
	void ReqAuthenticate();
	///�û���¼����
	void ReqUserLogin();
	///Ͷ���߽�����ȷ��
	void ReqSettlementInfoConfirm();
	///�����ѯ��Լ
	void ReqQryInstrument();
	///�����ѯ�ʽ��˻�
	void ReqQryTradingAccount();
	///�����ѯͶ���ֲ߳�
	void ReqQryInvestorPosition();

	// �Ƿ��յ��ɹ�����Ӧ
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
	// �Ƿ��ҵı����ر�
	bool IsMyOrder(CThostFtdcOrderField *pOrder);
	// �Ƿ����ڽ��׵ı���
	bool IsTradingOrder(CThostFtdcOrderField *pOrder);	
};

#endif // TDSPI_H
#ifndef _QP_CallbackWrap_
#define _QP_CallbackWrap_

#include "QP_Api.h"
#include <PTQuantBaseApi/PT_QuantApi.h>
using namespace PT_QuantPlatform;

class QP_CallbackWrap : public PT_QuantSpi
{
public:
	QP_CallbackWrap(QP_CallBack* fun, unsigned int sessionId, int model);
	~QP_CallbackWrap();
private:
	QP_CallBack* m_cb;
	unsigned int nSessionId;
	PT_QuantApi* m_session;
public:
	PT_QuantApi * GetSession();
public:
	virtual void onRspQueryAllUser(const PT_QuantUser* pUserInfo, bool isEnd) {};
	virtual void onRspPublicCode(const PT_QuantUserCodeControl* pPublicCode, int nNum) {};
	virtual void onRspUpdateUserAuthen(const TD_QuantUserAuthen* rsp, int error) {};
	virtual void onRspUpdateUserCodePool(const TD_QuantUserCodePool* rsp, int error) {};
	virtual void onRspDisablePublicCode(const TD_QuantUserDisablePublicCode* pUserDisablePublicCode, int error) {};
	virtual void onRspUpdateAccountPriority(const TD_RspUpdatePriority* rsp, int error) {};
	virtual void onRspQueryAccountPriority(const TD_RspQryPriority* rsp, int error, bool isEnd) {};
	virtual void onRtnProfit(const TD_RtnProfit *notice) {};

	virtual void OnConnect(int nSrvType);
	virtual void OnDisconnect(int nSrvType);
	virtual void onRtnUserInfo(const PT_QuantUserBase* pInfo);
public: //交易业务逻辑回调
	virtual void onRspOrderInsert(const TD_RspOrderInsert *rsp, int error);
	virtual void onRspOrderDelete(const TD_RspOrderDelete *rsp, int error);
	virtual void onRspQryOrder(const TD_RspQryOrder *rsp, int error, bool isEnd);
	virtual void onRspQryMatch(const TD_RspQryMatch *rsp, int error, bool isEnd);
	virtual void onRspQryPosition(const TD_RspQryPosition *rsp, int error, bool isEnd);
	virtual void onRspQryMaxEntrustCount(const TD_RspQryMaxEntrustCount* rsp, int error, bool isEnd);
	virtual void onRspQryAccountMaxEntrustCount(const TD_RspQryAccountMaxEntrustCount* rsp, int error, bool isEnd);
	virtual void onRtnOrderStatusChangeNotice(const TD_RtnOrderStatusChangeNotice *notice);
	virtual void onRtnOrderMatchNotice(const TD_RtnOrderMatchNotice *notice);
	virtual void onRtnUserAuthen(const TD_QuantUserAuthen* notice);
	virtual void onRtnMaxEntrustCount(const TD_RspQryMaxEntrustCount* notice);
	virtual void onRtnUpdateUserCodePool(const TD_QuantUserCodePool* notice);
	virtual void onRtnSimulationAccount(const TD_SimulationAccount* notice);
public://行情业务逻辑回调
	virtual void OnRtnMarket(MD_ReqID nReqID, MD_DATA_MARKET *pMarket);
	virtual void OnRtnKLine(MD_ReqID nReqID, MD_DATA_KLINE *pKLine);
	virtual void OnRtnIndex(MD_ReqID nReqID, MD_DATA_INDEX *pIndex);
	virtual void OnRtnTransaction(MD_ReqID nReqID, MD_DATA_TRANSACTION *pTrans);
	virtual void OnRtnOrderQueue(MD_ReqID nReqID, MD_DATA_ORDER_QUEUE *pQueue);
	virtual void OnRtnOrder(MD_ReqID nReqID, MD_DATA_ORDER *pOrder);
	virtual void OnRtnFuture(MD_ReqID nReqID, MD_DATA_FUTURE *pFuture);
	virtual void OnRtnFutureOption(MD_ReqID nReqID, MD_DATA_FUTURE *pFuture);
	virtual void OnRtnDayBegin(MD_ReqID nReqID, MD_ISODateTimeType pDate);
	virtual void OnRtnDayEnd(MD_ReqID nReqID, MD_ISODateTimeType pDate);
	virtual void OnRtnTimeless(MD_ReqID nReqID);

	virtual void OnRspTradingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg);
	virtual void OnRspHaltingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg);
	virtual void OnRspSubQuote(MD_ReqID nReqID, MD_SubType nSubType, MD_CycType nCycType, const MD_CodeType *pSubWindCode, long nSubWindCodeNum, MD_ISODateTimeType szBeginTime, MD_ISODateTimeType szEndTime, int nErrNo, const char *szErrMsg);
	virtual void OnRtnTradingCode(const MD_DATA_CODE *pWindCode, long nWindCodeNum, const MD_DATA_OPTION_CODE *pOptionCode, long nOptionCodeNum);
	virtual void OnRtnTradingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum);
	virtual void OnRtnHaltingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum);


private:
	// 临时变量
	// 行情
	QP_DATA_MARKET       m_market;
	QP_DATA_FUTURE       m_future;
	QP_DATA_INDEX        m_index;
	QP_DATA_TRANSACTION  m_transaction;
	QP_DATA_ORDER_QUEUE  m_queue;
	QP_DATA_ORDER        m_order;
	QP_DATA_KLINE        m_kline;

	QP_QryDayInfoRsp     m_rspDayInfo;
	QP_SubQuoteRsp       m_rspSubQuote;
	QP_DayInfoRtn        m_rtnDayInfo;

	// 交易
	QP_QuantUserBase     m_quantUserBase;

	QP_SimulationAccount        m_simulationAccount;
	QP_QuantUserCodePool        m_quantUserCodePool;
	QP_QuantUserAuthen          m_quantUserAuthen;

	QP_RtnOrderMatchNotice           m_rtnOrderMatchNotice;
	QP_RtnOrderStatusChangeNotice    m_rtnOrderStatusChangeNotice;
	QP_RspQryAccountMaxEntrustCount  m_rspQryAccountMaxEntrustCount;
	QP_RspQryMaxEntrustCount         m_rspQryMaxEntrustCount;
	QP_RspQryPosition                m_rspQryPosition;
	QP_RspQryMatch                   m_rspQryMatch;
	QP_RspOrderInsert                m_rspOrderInsert;
	QP_RspOrderDelete                m_rspOrderDelete;
	QP_RspQryOrder                   m_rspQryOrder;
};

#endif

#ifndef _QP_API_
#define _QP_API_

#ifdef WIN32
#define _QP_API_DllExport_ __declspec( dllexport )  //宏定义
#else
#define _QP_API_DllExport_  //宏定义
#endif // WIN32


#include "QP_Api_Struct.h"

typedef struct QP_CallBack
{
	//系统
	void(*cb_onConnect)(int, int);                      // sessionId, srvType
	void(*cb_onDisconnect)(int, int);                   // sessionId, srvType
	void(*cb_rtnUserInfo)(int, const QP_QuantUserBase*);

	//交易
	void(*cb_rspOrderInsert)(int, const QP_RspOrderInsert*, int);
	void(*cb_rspOrderDelete)(int, const QP_RspOrderDelete*, int);
	void(*cb_rspQryOrder)(int, const QP_RspQryOrder*, int, bool);
	void(*cb_rspQryMatch)(int, const QP_RspQryMatch*, int, bool);
	void(*cb_rspQryPosition)(int, const QP_RspQryPosition*, int, bool);
	void(*cb_rspQryMaxEntrustCount)(int, const QP_RspQryMaxEntrustCount*, int, bool);
	void(*cb_rspQryAccountMaxEntrustCount)(int, const QP_RspQryAccountMaxEntrustCount*, int, bool);
	void(*cb_rtnOrderStatusChangeNotice)(int, const QP_RtnOrderStatusChangeNotice*);
	void(*cb_rtnOrderMatchNotice)(int, const QP_RtnOrderMatchNotice*);
	void(*cb_rtnUserAuthen)(int, const QP_QuantUserAuthen*);
	void(*cb_rtnMaxEntrustCount)(int, const QP_RspQryMaxEntrustCount*);
	void(*cb_rtnUpdateUserCodePool)(int, const QP_QuantUserCodePool*);
	void(*cb_rtnSimulationAccount)(int, const QP_SimulationAccount*);

	//行情
	void(*cb_dataMarket)(int, const QP_DATA_MARKET*);         // sessionId, 行情结构体 函数指针
	void(*cb_dataKLine)(int, const QP_DATA_KLINE*);
	void(*cb_dataIndex)(int, const QP_DATA_INDEX*);
	void(*cb_dataTransaction)(int, const QP_DATA_TRANSACTION*);
	void(*cb_dataQueue)(int, const QP_DATA_ORDER_QUEUE*);
	void(*cb_dataOrder)(int, const QP_DATA_ORDER*);
	void(*cb_dataFuture)(int, const QP_DATA_FUTURE*);
	void(*cb_dataFutureOption)(int, const QP_DATA_FUTURE*);
	void(*cb_rtnDayBegin)(int, int, const char*);
	void(*cb_rtnDayEnd)(int, int, const char*);
	void(*cb_rtnTimeLess)(int, int);

	void(*cb_rspTradingDay)(int, const QP_QryDayInfoRsp*);
	void(*cb_rspHaltingDay)(int, const QP_QryDayInfoRsp*);
	void(*cb_rspSubQuote)(int, const QP_SubQuoteRsp*);
	void(*cb_dataTradingCode)(int, const QP_DATA_CODE*, int, const QP_DATA_OPTION_CODE*, int);
	void(*cb_dataTradingDay)(int, const QP_DayInfoRtn*);
	void(*cb_dataHaltingDay)(int, const QP_DayInfoRtn*);

} QP_CallBack;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

_QP_API_DllExport_ int QP_CreatSession(QP_CallBack* funObj, int model);
_QP_API_DllExport_ int QP_Login(int sessionId, const char* user, const char* pass);
_QP_API_DllExport_ int QP_GetCode(int sessionid);

// 行情接口
_QP_API_DllExport_ int QP_ReqSubQuote(int sessionId, QP_SubQuoteReq* req);
_QP_API_DllExport_ int QP_ReqHaltingDay(int sessionId, QP_QryDayInfoReq* req);
_QP_API_DllExport_ int QP_ReqTradingDay(int sessionId, QP_QryDayInfoReq* req);

// 交易接口
_QP_API_DllExport_ int QP_ReqOrderInsert(int sessionId, QP_OrderInsertReq* req);
_QP_API_DllExport_ int QP_ReqOrderDelete(int sessionId, QP_OrderDeleteReq* req);
_QP_API_DllExport_ int QP_ReqOrderQry(int sessionId, QP_OrderQryReq* req);
_QP_API_DllExport_ int QP_ReqMatchQry(int sessionId, QP_MatchQryReq* req);
_QP_API_DllExport_ int QP_ReqPositionQry(int sessionId, QP_PositionQryReq* req);
_QP_API_DllExport_ int QP_ReqMaxEntrustCount(int sessionId, QP_MaxEntrustCountQryReq* req);
_QP_API_DllExport_ int QP_ReqQryAccountMaxEntrustCount(int sessionId, QP_AccountMaxEntrustCountQryReq* req);
_QP_API_DllExport_ int QP_ReqSubscribeMaxEntrustCount(int sessionId);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif
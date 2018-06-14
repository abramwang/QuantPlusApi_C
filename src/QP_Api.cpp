// QP_Api.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <map>
#include "QP_Api.h"
#include "QP_CallbackWrap.h"
#include <PTQuantBaseApi/PT_QuantApi.h>

using namespace PT_QuantPlatform;

TD_ReqOrderInsert gReqOrderInsert;
TD_ReqOrderDelete gReqOrderDelete;
TD_ReqQryOrder    gReqQryOrder;
TD_ReqQryMatch    gReqQryMatch;
TD_ReqQryPosition gReqQryPosition;
TD_ReqQryMaxEntrustCount  gReqQryMaxEntrustCount;
TD_ReqQryAccountMaxEntrustCount gReqQryAccountMaxEntrustCount;

/*
    变量定义
*/
unsigned int g_sessionId = 0;
std::map<int, QP_CallbackWrap*> g_sessionMap;       //结构体

/*
    导出函数实现
*/

_QP_API_DllExport_ int QP_CreatSession(QP_CallBack* fun, int model)
{
	unsigned int sessionId = ++g_sessionId;
	QP_CallbackWrap* callBackWarp = new QP_CallbackWrap(fun, sessionId, model);
	g_sessionMap[sessionId] = callBackWarp;
	return sessionId;
}


_QP_API_DllExport_ int QP_Login(int sessionId, const char* user, const char* pass)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		return callBackWrap->GetSession()->Login((char*)user, (char*)pass);
	}

	return -1;
}

_QP_API_DllExport_ int QP_GetCode(int sessionid)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionid];

	if(callBackWrap)
	{
		return callBackWrap->GetSession()->GetCode();
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqSubQuote(int sessionId, QP_SubQuoteReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		MD_CodeType* pSubCode = new MD_CodeType[req->nSubCodeNum];
		memset(pSubCode, 0, sizeof(MD_CodeType)*req->nSubCodeNum);

		for(unsigned int i = 0; i < req->nSubCodeNum; ++i)
		{
			strcpy_s(*(pSubCode + i), *(req->pSubCode + i));
		}

		int err = callBackWrap->GetSession()->ReqSubQuote(req->nReqId,
				  req->nSubType, req->nCycType,
				  pSubCode, req->nSubCodeNum,
				  req->szBeginTime, req->szEndTime);

		delete[] pSubCode;
		return err;
	}

	return -1;
}


_QP_API_DllExport_ int QP_ReqHaltingDay(int sessionId, QP_QryDayInfoReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		MD_CodeType* pWindCode = new MD_CodeType[req->nWindCodeNum];
		memset(pWindCode, 0, sizeof(MD_CodeType)*req->nWindCodeNum);

		for(unsigned int i = 0; i < req->nWindCodeNum; ++i)
		{
			strcpy_s(*(pWindCode + i), *(req->pWindCode + i));
		}

		int result = callBackWrap->GetSession()->ReqHaltingDay(req->nReqId, pWindCode, req->nWindCodeNum, req->szBeginDay, req->szEndDay);

		delete[] pWindCode;
		return result;
	}

	return -1;
}


_QP_API_DllExport_ int QP_ReqTradingDay(int sessionId, QP_QryDayInfoReq*req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		MD_CodeType* pWindCode = new MD_CodeType[req->nWindCodeNum];
		memset(pWindCode, 0, sizeof(MD_CodeType)*req->nWindCodeNum);

		for(unsigned int i = 0; i < req->nWindCodeNum; ++i)
		{
			strcpy_s(*(pWindCode + i), *(req->pWindCode + i));
		}

		int result = callBackWrap->GetSession()->ReqTradingDay(req->nReqId, pWindCode, req->nWindCodeNum, req->szBeginDay, req->szEndDay);

		delete[] pWindCode;
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqOrderInsert(int sessionId, QP_OrderInsertReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		gReqOrderInsert.nReqId = req->nReqId;
		gReqOrderInsert.nStrategyId = req->nStrategyId;

		gReqOrderInsert.nUserDouble = req->nUserDouble;
		gReqOrderInsert.nUserInt = req->nUserInt;

		if(req->szUseStr)
		{
			memcpy_s(gReqOrderInsert.szUseStr, sizeof(gReqOrderInsert.szUseStr), req->szUseStr, strlen(req->szUseStr));
		}

		if(req->szContractCode)
		{
			memcpy_s(gReqOrderInsert.szContractCode, sizeof(gReqOrderInsert.szContractCode), req->szContractCode, strlen(req->szContractCode));
		}

		if(req->szContractName)
		{
			memcpy_s(gReqOrderInsert.szContractName, sizeof(gReqOrderInsert.szContractName), req->szContractName, strlen(req->szContractName));
		}

		gReqOrderInsert.nTradeType = (TD_TradeType)req->nTradeType;
		gReqOrderInsert.nOffsetType = (TD_OffsetType)req->nOffsetType;
		gReqOrderInsert.nOrderVol = req->nOrderVol;
		gReqOrderInsert.nOrderPrice = req->nOrderPrice;
		gReqOrderInsert.nCloseR = req->nCloseR;
		gReqOrderInsert.nOrderNum = req->nOrderNum;

		if(gReqOrderInsert.nOrderNum != 0)
		{
			gReqOrderInsert.pOrderDetail = (TD_OrderDetail*)malloc(sizeof(TD_OrderDetail) * gReqOrderInsert.nOrderNum);
			memset(gReqOrderInsert.pOrderDetail, 0, sizeof(TD_OrderDetail) * gReqOrderInsert.nOrderNum);

			for(int i = 0; i < gReqOrderInsert.nOrderNum; ++i)
			{
				gReqOrderInsert.pOrderDetail[i].nAccountId = req->pOrderDetail[i].nAccountId;
				gReqOrderInsert.pOrderDetail[i].nOrderVol = req->pOrderDetail[i].nOrderVol;
			}
		}

		int result = callBackWrap->GetSession()->reqOrderInsert(&gReqOrderInsert);

		if(gReqOrderInsert.pOrderDetail)
		{
			free(gReqOrderInsert.pOrderDetail);
		}

		memset(&gReqOrderInsert, 0, sizeof(TD_ReqOrderInsert));
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqOrderDelete(int sessionId, QP_OrderDeleteReq * req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		gReqOrderDelete.nReqId = req->nReqId;
		gReqOrderDelete.nStrategyId = req->nStrategyId;

		gReqOrderDelete.nUserDouble = req->nUserDouble;
		gReqOrderDelete.nUserInt = req->nUserInt;

		if(req->szUseStr)
		{
			memcpy_s(gReqOrderDelete.szUseStr, sizeof(gReqOrderDelete.szUseStr), req->szUseStr, strlen(req->szUseStr));
		}


		gReqOrderDelete.nOrderId = req->nOrderId;

		if(req->szOrderStreamId)
		{
			memcpy_s(gReqOrderDelete.szOrderStreamId, sizeof(gReqOrderDelete.szOrderStreamId), req->szOrderStreamId, strlen(req->szOrderStreamId));
		}

		int result = callBackWrap->GetSession()->reqOrderDelete(&gReqOrderDelete);

		memset(&gReqOrderDelete, 0, sizeof(TD_ReqOrderDelete));
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqOrderQry(int sessionId, QP_OrderQryReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		gReqQryOrder.nReqId = req->nReqId;
		gReqQryOrder.nStrategyId = req->nStrategyId;

		gReqQryOrder.nUserDouble = req->nUserDouble;
		gReqQryOrder.nUserInt = req->nUserInt;

		if(req->szUseStr)
		{
			memcpy_s(gReqQryOrder.szUseStr, sizeof(gReqQryOrder.szUseStr), req->szUseStr, strlen(req->szUseStr));
		}

		if(req->szContractCode)
		{
			memcpy_s(gReqQryOrder.szContractCode, sizeof(gReqQryOrder.szContractCode), req->szContractCode, strlen(req->szContractCode));
		}

		gReqQryOrder.nIndex = req->nIndex;
		gReqQryOrder.nNum = req->nNum;

		int result = callBackWrap->GetSession()->reqQryOrder(&gReqQryOrder);

		memset(&gReqQryOrder, 0, sizeof(TD_ReqQryOrder));
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqMatchQry(int sessionId, QP_MatchQryReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		gReqQryMatch.nReqId = req->nReqId;
		gReqQryMatch.nStrategyId = req->nStrategyId;

		gReqQryMatch.nUserDouble = req->nUserDouble;
		gReqQryMatch.nUserInt = req->nUserInt;

		if(req->szUseStr)
		{
			memcpy_s(gReqQryMatch.szUseStr, sizeof(gReqQryMatch.szUseStr), req->szUseStr, strlen(req->szUseStr));
		}

		if(req->szContractCode)
		{
			memcpy_s(gReqQryMatch.szContractCode, sizeof(gReqQryMatch.szContractCode), req->szContractCode, strlen(req->szContractCode));
		}

		gReqQryMatch.nIndex = req->nIndex;
		gReqQryMatch.nNum = req->nNum;

		int result = callBackWrap->GetSession()->reqQryMatch(&gReqQryMatch);

		memset(&gReqQryMatch, 0, sizeof(TD_ReqQryMatch));
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqPositionQry(int sessionId, QP_PositionQryReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		gReqQryPosition.nReqId = req->nReqId;
		gReqQryPosition.nStrategyId = req->nStrategyId;

		gReqQryPosition.nUserDouble = req->nUserDouble;
		gReqQryPosition.nUserInt = req->nUserInt;

		if(req->szUseStr)
		{
			memcpy_s(gReqQryPosition.szUseStr, sizeof(gReqQryPosition.szUseStr), req->szUseStr, strlen(req->szUseStr));
		}

		if(req->szContractCode)
		{
			memcpy_s(gReqQryPosition.szContractCode, sizeof(gReqQryPosition.szContractCode), req->szContractCode, strlen(req->szContractCode));
		}

		int result = callBackWrap->GetSession()->reqQryPosition(&gReqQryPosition);

		memset(&gReqQryPosition, 0, sizeof(TD_ReqQryPosition));
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqMaxEntrustCount(int sessionId, QP_MaxEntrustCountQryReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		gReqQryMaxEntrustCount.nReqId = req->nReqId;
		gReqQryMaxEntrustCount.nStrategyId = req->nStrategyId;

		gReqQryMaxEntrustCount.nUserDouble = req->nUserDouble;
		gReqQryMaxEntrustCount.nUserInt = req->nUserInt;

		if(req->szUseStr)
		{
			memcpy_s(gReqQryMaxEntrustCount.szUseStr, sizeof(gReqQryMaxEntrustCount.szUseStr), req->szUseStr, strlen(req->szUseStr));
		}

		if(req->szContractCode)
		{
			memcpy_s(gReqQryMaxEntrustCount.szContractCode, sizeof(gReqQryMaxEntrustCount.szContractCode), req->szContractCode, strlen(req->szContractCode));
		}

		int result = callBackWrap->GetSession()->reqQryMaxEntrustCount(&gReqQryMaxEntrustCount);

		memset(&gReqQryMaxEntrustCount, 0, sizeof(TD_ReqQryMaxEntrustCount));
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqQryAccountMaxEntrustCount(int sessionId, QP_AccountMaxEntrustCountQryReq* req)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		gReqQryAccountMaxEntrustCount.nReqId = req->nReqId;
		gReqQryAccountMaxEntrustCount.nStrategyId = req->nStrategyId;

		gReqQryAccountMaxEntrustCount.nUserDouble = req->nUserDouble;
		gReqQryAccountMaxEntrustCount.nUserInt = req->nUserInt;

		if(req->szUseStr)
		{
			memcpy_s(gReqQryAccountMaxEntrustCount.szUseStr, sizeof(gReqQryAccountMaxEntrustCount.szUseStr), req->szUseStr, strlen(req->szUseStr));
		}

		if(req->szContractCode)
		{
			memcpy_s(gReqQryAccountMaxEntrustCount.szContractCode, sizeof(gReqQryAccountMaxEntrustCount.szContractCode), req->szContractCode, strlen(req->szContractCode));
		}

		gReqQryAccountMaxEntrustCount.nAccountId = req->nAccountId;

		int result = callBackWrap->GetSession()->reqQryAccountMaxEntrustCount(&gReqQryAccountMaxEntrustCount);

		memset(&gReqQryAccountMaxEntrustCount, 0, sizeof(TD_ReqQryAccountMaxEntrustCount));
		return result;
	}

	return -1;
}

_QP_API_DllExport_ int QP_ReqSubscribeMaxEntrustCount(int sessionId)
{
	QP_CallbackWrap* callBackWrap = g_sessionMap[sessionId];

	if(callBackWrap)
	{
		return callBackWrap->GetSession()->reqSubscribeMaxEntrustCount();
	}

	return -1;
}

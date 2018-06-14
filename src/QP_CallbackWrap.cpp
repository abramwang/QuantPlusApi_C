#include "stdafx.h"
#include "QP_CallbackWrap.h"


QP_CallbackWrap::QP_CallbackWrap(QP_CallBack* fun, unsigned int sessionId, int model)
{
	m_cb = fun;
	nSessionId = sessionId;
	m_session = PT_QuantApi::createApi(this, true, (PT_QuantTdAppEType)model, PT_QuantMdAppEType_Real);

	//行情
	memset(&m_market, 0, sizeof(QP_DATA_MARKET));
	memset(&m_future, 0, sizeof(QP_DATA_FUTURE));
	memset(&m_index, 0, sizeof(QP_DATA_INDEX));
	memset(&m_transaction, 0, sizeof(QP_DATA_TRANSACTION));
	memset(&m_queue, 0, sizeof(QP_DATA_ORDER_QUEUE));
	memset(&m_order, 0, sizeof(QP_DATA_ORDER));
	memset(&m_kline, 0, sizeof(QP_DATA_KLINE));

	memset(&m_rspDayInfo, 0, sizeof(QP_QryDayInfoRsp));
	memset(&m_rspSubQuote, 0, sizeof(QP_SubQuoteRsp));
	memset(&m_rtnDayInfo, 0, sizeof(QP_DayInfoRtn));

	//交易
	memset(&m_quantUserBase, 0, sizeof(QP_QuantUserBase));

	memset(&m_simulationAccount, 0, sizeof(QP_SimulationAccount));
	memset(&m_quantUserCodePool, 0, sizeof(QP_QuantUserCodePool));
	memset(&m_quantUserAuthen, 0, sizeof(QP_QuantUserAuthen));

	memset(&m_rtnOrderMatchNotice, 0, sizeof(QP_RtnOrderMatchNotice));
	memset(&m_rtnOrderStatusChangeNotice, 0, sizeof(QP_RtnOrderStatusChangeNotice));
	memset(&m_rspQryAccountMaxEntrustCount, 0, sizeof(QP_RspQryAccountMaxEntrustCount));
	memset(&m_rspQryMaxEntrustCount, 0, sizeof(QP_RspQryMaxEntrustCount));
	memset(&m_rspQryPosition, 0, sizeof(QP_RspQryPosition));
	memset(&m_rspQryMatch, 0, sizeof(QP_RspQryMatch));
	memset(&m_rspOrderInsert, 0, sizeof(QP_RspOrderInsert));
	memset(&m_rspOrderDelete, 0, sizeof(QP_RspOrderDelete));
	memset(&m_rspQryOrder, 0, sizeof(QP_RspQryOrder));
}


QP_CallbackWrap::~QP_CallbackWrap()
{

}

PT_QuantApi * QP_CallbackWrap::GetSession()
{
	return m_session;
}

void QP_CallbackWrap::OnConnect(int nSrvType)
{
	if(m_cb->cb_onConnect)
	{
		m_cb->cb_onConnect(nSessionId, nSrvType);
	}
}
void QP_CallbackWrap::OnDisconnect(int nSrvType)
{
	if(m_cb->cb_onDisconnect)
	{
		m_cb->cb_onDisconnect(nSessionId, nSrvType);
	}
}
void QP_CallbackWrap::onRtnUserInfo(const PT_QuantUserBase* pInfo)
{
	m_quantUserBase.nId = pInfo->nId;
	m_quantUserBase.szUserName = (char*)pInfo->szUserName;
	m_quantUserBase.szNickName = (char*)pInfo->szNickName;
	m_quantUserBase.nGroupId = pInfo->nGroupId;
	m_quantUserBase.nUserRole = pInfo->nUserRole;

	m_quantUserBase.nStampTax = pInfo->nStampTax;
	m_quantUserBase.nTransferFees = pInfo->nTransferFees;
	m_quantUserBase.nCommissions = pInfo->nCommissions;

	if(m_cb->cb_rtnUserInfo)
	{
		m_cb->cb_rtnUserInfo(nSessionId, &m_quantUserBase);
	}
}

// ///////////////////////////
// 交易

void QP_CallbackWrap::onRspOrderInsert(const TD_RspOrderInsert *rsp, int error)
{
	// QP_BASEMSG_FIELDS
	m_rspOrderInsert.nReqId = rsp->nReqId;
	m_rspOrderInsert.nStrategyId = rsp->nStrategyId;

	m_rspOrderInsert.nUserInt = rsp->nUserInt;
	m_rspOrderInsert.nUserDouble = rsp->nUserDouble;
	m_rspOrderInsert.szUseStr = (char*)rsp->szUseStr;

	m_rspOrderInsert.szClientId = (char*)rsp->szClientId;
	m_rspOrderInsert.nUserId = rsp->nUserId;
	// QP_INSERTReq_FIELDS
	m_rspOrderInsert.szContractCode = (char*)rsp->szContractCode;
	m_rspOrderInsert.szContractName = (char*)rsp->szContractName;
	m_rspOrderInsert.nTradeType = (TD_TradeType)rsp->nTradeType;
	m_rspOrderInsert.nOffsetType = (TD_OffsetType)rsp->nOffsetType;
	m_rspOrderInsert.nOrderVol = rsp->nOrderVol;
	m_rspOrderInsert.nOrderPrice = rsp->nOrderPrice;
	m_rspOrderInsert.nCloseR = rsp->nCloseR;
	m_rspOrderInsert.nOrderNum = rsp->nOrderNum;

	if(m_rspOrderInsert.nOrderNum != 0)
	{
		m_rspOrderInsert.pOrderDetail = (QP_OrderDetail*)malloc(sizeof(QP_OrderDetail) * m_rspOrderInsert.nOrderNum);

		for(int i = 0; i < m_rspOrderInsert.nOrderNum; ++i)
		{
			m_rspOrderInsert.pOrderDetail[i].szOrderStreamId = rsp->pOrderDetail[i].szOrderStreamId;
			m_rspOrderInsert.pOrderDetail[i].nAccountId = rsp->pOrderDetail[i].nAccountId;
			m_rspOrderInsert.pOrderDetail[i].szAccountNickName = rsp->pOrderDetail[i].szAccountNickName;
			m_rspOrderInsert.pOrderDetail[i].nOrderVol = rsp->pOrderDetail[i].nOrderVol;
			m_rspOrderInsert.pOrderDetail[i].nDealedPrice = rsp->pOrderDetail[i].nDealedPrice;
			m_rspOrderInsert.pOrderDetail[i].nDealedVol = rsp->pOrderDetail[i].nDealedVol;
			m_rspOrderInsert.pOrderDetail[i].nWithDrawnVol = rsp->pOrderDetail[i].nWithDrawnVol;
			m_rspOrderInsert.pOrderDetail[i].szOrderTime = rsp->pOrderDetail[i].szOrderTime;
			m_rspOrderInsert.pOrderDetail[i].nStatus = rsp->pOrderDetail[i].nStatus;
			m_rspOrderInsert.pOrderDetail[i].szText = rsp->pOrderDetail[i].szText;
			m_rspOrderInsert.pOrderDetail[i].nFee = rsp->pOrderDetail[i].nFee;
		}
	}

	// QP_INSERTRsp_FIELDS
	m_rspOrderInsert.nOrderOwnerId = rsp->nOrderOwnerId;
	m_rspOrderInsert.nOrderId = rsp->nOrderId;
	m_rspOrderInsert.nSubmitVol = rsp->nSubmitVol;
	m_rspOrderInsert.nDealedPrice = rsp->nDealedPrice;
	m_rspOrderInsert.nDealedVol = rsp->nDealedVol;
	m_rspOrderInsert.nTotalWithDrawnVol = rsp->nTotalWithDrawnVol;
	m_rspOrderInsert.nInValid = rsp->nInValid;
	m_rspOrderInsert.nStatus = rsp->nStatus;
	m_rspOrderInsert.szInsertTime = (char*)rsp->szInsertTime;
	m_rspOrderInsert.nFee = rsp->nFee;

	if(m_cb->cb_rspOrderInsert)
	{
		m_cb->cb_rspOrderInsert(nSessionId, &m_rspOrderInsert, error);
	}

	if(m_rspOrderInsert.pOrderDetail)
	{
		free(m_rspOrderInsert.pOrderDetail);
	}

	memset(&m_rspOrderInsert, 0, sizeof(QP_RspOrderInsert));
}
void QP_CallbackWrap::onRspOrderDelete(const TD_RspOrderDelete *rsp, int error)
{
	return;
	// Base
	m_rspOrderDelete.nReqId = rsp->nReqId;
	m_rspOrderDelete.nStrategyId = rsp->nStrategyId;

	m_rspOrderDelete.nUserInt = rsp->nUserInt;
	m_rspOrderDelete.nUserDouble = rsp->nUserDouble;
	m_rspOrderDelete.szUseStr = (char*)rsp->szUseStr;

	m_rspOrderDelete.szClientId = (char*)rsp->szClientId;
	m_rspOrderDelete.nUserId = rsp->nUserId;
	// //////////////////////
	m_rspOrderDelete.nOrderId = rsp->nOrderId;
	m_rspOrderDelete.szOrderStreamId = (char*)rsp->szOrderStreamId;

	if(m_cb->cb_rspOrderDelete)
	{
		m_cb->cb_rspOrderDelete(nSessionId, &m_rspOrderDelete, error);
	}

	memset(&m_rspOrderDelete, 0, sizeof(QP_RspOrderDelete));
}
void QP_CallbackWrap::onRspQryOrder(const TD_RspQryOrder *rsp, int error, bool isEnd)
{
	// QP_BASEMSG_FIELDS
	m_rspQryOrder.nReqId = rsp->nReqId;
	m_rspQryOrder.nStrategyId = rsp->nStrategyId;

	m_rspQryOrder.nUserInt = rsp->nUserInt;
	m_rspQryOrder.nUserDouble = rsp->nUserDouble;
	m_rspQryOrder.szUseStr = (char*)rsp->szUseStr;

	m_rspQryOrder.szClientId = (char*)rsp->szClientId;
	m_rspQryOrder.nUserId = rsp->nUserId;
	// QP_INSERTReq_FIELDS
	m_rspQryOrder.szContractCode = (char*)rsp->szContractCode;
	m_rspQryOrder.szContractName = (char*)rsp->szContractName;
	m_rspQryOrder.nTradeType = (TD_TradeType)rsp->nTradeType;
	m_rspQryOrder.nOffsetType = (TD_OffsetType)rsp->nOffsetType;
	m_rspQryOrder.nOrderVol = rsp->nOrderVol;
	m_rspQryOrder.nOrderPrice = rsp->nOrderPrice;
	m_rspQryOrder.nCloseR = rsp->nCloseR;
	m_rspQryOrder.nOrderNum = rsp->nOrderNum;

	if(m_rspQryOrder.nOrderNum != 0)
	{
		m_rspQryOrder.pOrderDetail = (QP_OrderDetail*)malloc(sizeof(QP_OrderDetail) * m_rspQryOrder.nOrderNum);

		for(int i = 0; i < m_rspQryOrder.nOrderNum; ++i)
		{
			m_rspQryOrder.pOrderDetail[i].szOrderStreamId = rsp->pOrderDetail[i].szOrderStreamId;
			m_rspQryOrder.pOrderDetail[i].nAccountId = rsp->pOrderDetail[i].nAccountId;
			m_rspQryOrder.pOrderDetail[i].szAccountNickName = rsp->pOrderDetail[i].szAccountNickName;
			m_rspQryOrder.pOrderDetail[i].nOrderVol = rsp->pOrderDetail[i].nOrderVol;
			m_rspQryOrder.pOrderDetail[i].nDealedPrice = rsp->pOrderDetail[i].nDealedPrice;
			m_rspQryOrder.pOrderDetail[i].nDealedVol = rsp->pOrderDetail[i].nDealedVol;
			m_rspQryOrder.pOrderDetail[i].nWithDrawnVol = rsp->pOrderDetail[i].nWithDrawnVol;
			m_rspQryOrder.pOrderDetail[i].szOrderTime = rsp->pOrderDetail[i].szOrderTime;
			m_rspQryOrder.pOrderDetail[i].nStatus = rsp->pOrderDetail[i].nStatus;
			m_rspQryOrder.pOrderDetail[i].szText = rsp->pOrderDetail[i].szText;
			m_rspQryOrder.pOrderDetail[i].nFee = rsp->pOrderDetail[i].nFee;
		}
	}

	// QP_INSERTRsp_FIELDS
	m_rspQryOrder.nOrderOwnerId = rsp->nOrderOwnerId;
	m_rspQryOrder.nOrderId = rsp->nOrderId;
	m_rspQryOrder.nSubmitVol = rsp->nSubmitVol;
	m_rspQryOrder.nDealedPrice = rsp->nDealedPrice;
	m_rspQryOrder.nDealedVol = rsp->nDealedVol;
	m_rspQryOrder.nTotalWithDrawnVol = rsp->nTotalWithDrawnVol;
	m_rspQryOrder.nInValid = rsp->nInValid;
	m_rspQryOrder.nStatus = rsp->nStatus;
	m_rspQryOrder.szInsertTime = (char*)rsp->szInsertTime;
	m_rspQryOrder.nFee = rsp->nFee;
	// QP_RspQryOrder
	m_rspQryOrder.nIndex = rsp->nIndex;

	if(m_cb->cb_rspQryOrder)
	{
		m_cb->cb_rspQryOrder(nSessionId, &m_rspQryOrder, error, isEnd);
	}

	if(m_rspQryOrder.pOrderDetail)
	{
		free(m_rspQryOrder.pOrderDetail);
	}

	memset(&m_rspQryOrder, 0, sizeof(QP_RspQryOrder));
}


void QP_CallbackWrap::onRspQryMatch(const TD_RspQryMatch *rsp, int error, bool isEnd)
{
	// QP_BASEMSG_FIELDS
	m_rspQryMatch.nReqId = rsp->nReqId;
	m_rspQryMatch.nStrategyId = rsp->nStrategyId;

	m_rspQryMatch.nUserInt = rsp->nUserInt;
	m_rspQryMatch.nUserDouble = rsp->nUserDouble;
	m_rspQryMatch.szUseStr = (char*)rsp->szUseStr;

	m_rspQryMatch.szClientId = (char*)rsp->szClientId;
	m_rspQryMatch.nUserId = rsp->nUserId;
	// QP_RtnOrderMatchNotice_FIELDS
	m_rspQryMatch.nOrderId = rsp->nOrderId;
	m_rspQryMatch.szOrderStreamId = (char*)rsp->szOrderStreamId;
	m_rspQryMatch.nMatchStreamId = rsp->nMatchStreamId;
	m_rspQryMatch.nMatchPrice = rsp->nMatchPrice;
	m_rspQryMatch.nMatchVol = rsp->nMatchVol;
	m_rspQryMatch.szContractCode = (char*)rsp->szContractCode;
	m_rspQryMatch.szContractName = (char*)rsp->szContractName;
	m_rspQryMatch.szMatchTime = (char*)rsp->szMatchTime;
	m_rspQryMatch.nTradeType = rsp->nTradeType;
	m_rspQryMatch.nAccountId = rsp->nAccountId;
	m_rspQryMatch.szAccountNickName = (char*)rsp->szAccountNickName;
	// QP_RspQryMatch
	m_rspQryMatch.nIndex = rsp->nIndex;

	if(m_cb->cb_rspQryMatch)
	{
		m_cb->cb_rspQryMatch(nSessionId, &m_rspQryMatch, error, isEnd);
	}

	memset(&m_rspQryMatch, 0, sizeof(QP_RspQryMatch));
}


void QP_CallbackWrap::onRspQryPosition(const TD_RspQryPosition *rsp, int error, bool isEnd)
{
	// QP_BASEMSG_FIELDS
	m_rspQryPosition.nReqId = rsp->nReqId;
	m_rspQryPosition.nStrategyId = rsp->nStrategyId;

	m_rspQryPosition.nUserInt = rsp->nUserInt;
	m_rspQryPosition.nUserDouble = rsp->nUserDouble;
	m_rspQryPosition.szUseStr = (char*)rsp->szUseStr;

	m_rspQryPosition.szClientId = (char*)rsp->szClientId;
	m_rspQryPosition.nUserId = rsp->nUserId;
	// QP_RspQryPosition
	m_rspQryPosition.szContractCode = (char*)rsp->szContractCode;
	m_rspQryPosition.nPosition = rsp->nPosition;
	m_rspQryPosition.nPrice = rsp->nPrice;
	m_rspQryPosition.nProfit = rsp->nProfit;
	m_rspQryPosition.nSelltleProfit = rsp->nSelltleProfit;

	if(m_cb->cb_rspQryPosition)
	{
		m_cb->cb_rspQryPosition(nSessionId, &m_rspQryPosition, error, isEnd);
	}

	memset(&m_rspQryPosition, 0, sizeof(QP_RspQryPosition));
}


void QP_CallbackWrap::onRspQryMaxEntrustCount(const TD_RspQryMaxEntrustCount* rsp, int error, bool isEnd)
{
	// QP_BASEMSG_FIELDS
	m_rspQryMaxEntrustCount.nReqId = rsp->nReqId;
	m_rspQryMaxEntrustCount.nStrategyId = rsp->nStrategyId;

	m_rspQryMaxEntrustCount.nUserInt = rsp->nUserInt;
	m_rspQryMaxEntrustCount.nUserDouble = rsp->nUserDouble;
	m_rspQryMaxEntrustCount.szUseStr = (char*)rsp->szUseStr;

	m_rspQryMaxEntrustCount.szClientId = (char*)rsp->szClientId;
	m_rspQryMaxEntrustCount.nUserId = rsp->nUserId;
	// QP_RspQryMaxEntrustCount

	m_rspQryMaxEntrustCount.pStockMaxEntrustCount.szContractCode = (char*)rsp->pStockMaxEntrustCount.szContractCode;
	m_rspQryMaxEntrustCount.pStockMaxEntrustCount.nMaxBuyCaptial = rsp->pStockMaxEntrustCount.nMaxBuyCaptial;
	m_rspQryMaxEntrustCount.pStockMaxEntrustCount.nMaxSellVol = rsp->pStockMaxEntrustCount.nMaxSellVol;

	if(m_cb->cb_rspQryMaxEntrustCount)
	{
		m_cb->cb_rspQryMaxEntrustCount(nSessionId, &m_rspQryMaxEntrustCount, error, isEnd);
	}

	memset(&m_rspQryMaxEntrustCount, 0, sizeof(QP_RspQryMaxEntrustCount));
}


void QP_CallbackWrap::onRspQryAccountMaxEntrustCount(const TD_RspQryAccountMaxEntrustCount* rsp, int error, bool isEnd)
{
	// QP_BASEMSG_FIELDS
	m_rspQryAccountMaxEntrustCount.nReqId = rsp->nReqId;
	m_rspQryAccountMaxEntrustCount.nStrategyId = rsp->nStrategyId;

	m_rspQryAccountMaxEntrustCount.nUserInt = rsp->nUserInt;
	m_rspQryAccountMaxEntrustCount.nUserDouble = rsp->nUserDouble;
	m_rspQryAccountMaxEntrustCount.szUseStr = (char*)rsp->szUseStr;

	m_rspQryAccountMaxEntrustCount.szClientId = (char*)rsp->szClientId;
	m_rspQryAccountMaxEntrustCount.nUserId = rsp->nUserId;
	// QP_RspQryAccountMaxEntrustCount
	m_rspQryAccountMaxEntrustCount.nAccountId = rsp->nAccountId;
	m_rspQryAccountMaxEntrustCount.szAccountNickName = (char*)rsp->szAccountNickName;
	m_rspQryAccountMaxEntrustCount.nNum = rsp->nNum;
	m_rspQryAccountMaxEntrustCount.pStockMaxEntrustCount = NULL;

	if(m_rspQryAccountMaxEntrustCount.nNum != 0)
	{
		m_rspQryAccountMaxEntrustCount.pStockMaxEntrustCount = (QP_StockMaxEntrustCount*)malloc(sizeof(QP_StockMaxEntrustCount) * m_rspQryAccountMaxEntrustCount.nNum);

		for(int i = 0; i < m_rspQryAccountMaxEntrustCount.nNum; ++i)
		{
			m_rspQryAccountMaxEntrustCount.pStockMaxEntrustCount[i].szContractCode = rsp->pStockMaxEntrustCount[i].szContractCode;
			m_rspQryAccountMaxEntrustCount.pStockMaxEntrustCount[i].nMaxBuyCaptial = rsp->pStockMaxEntrustCount[i].nMaxBuyCaptial;
			m_rspQryAccountMaxEntrustCount.pStockMaxEntrustCount[i].nMaxSellVol = rsp->pStockMaxEntrustCount[i].nMaxSellVol;
		}
	}

	m_rspQryAccountMaxEntrustCount.bStatus = rsp->bStatus;
	m_rspQryAccountMaxEntrustCount.nAvailableCaptial = rsp->nAvailableCaptial;

	if(m_cb->cb_rspQryAccountMaxEntrustCount)
	{
		m_cb->cb_rspQryAccountMaxEntrustCount(nSessionId, &m_rspQryAccountMaxEntrustCount, error, isEnd);
	}

	if(m_rspQryAccountMaxEntrustCount.pStockMaxEntrustCount)
	{
		free(m_rspQryAccountMaxEntrustCount.pStockMaxEntrustCount);
	}

	memset(&m_rspQryAccountMaxEntrustCount, 0, sizeof(QP_RspQryAccountMaxEntrustCount));
}


void QP_CallbackWrap::onRtnOrderStatusChangeNotice(const TD_RtnOrderStatusChangeNotice *rsp)
{
	// QP_BASEMSG_FIELDS
	m_rtnOrderStatusChangeNotice.nReqId = rsp->nReqId;
	m_rtnOrderStatusChangeNotice.nStrategyId = rsp->nStrategyId;

	m_rtnOrderStatusChangeNotice.nUserInt = rsp->nUserInt;
	m_rtnOrderStatusChangeNotice.nUserDouble = rsp->nUserDouble;
	m_rtnOrderStatusChangeNotice.szUseStr = (char*)rsp->szUseStr;

	m_rtnOrderStatusChangeNotice.szClientId = (char*)rsp->szClientId;
	m_rtnOrderStatusChangeNotice.nUserId = rsp->nUserId;
	// QP_INSERTReq_FIELDS
	m_rtnOrderStatusChangeNotice.szContractCode = (char*)rsp->szContractCode;
	m_rtnOrderStatusChangeNotice.szContractName = (char*)rsp->szContractName;
	m_rtnOrderStatusChangeNotice.nTradeType = (TD_TradeType)rsp->nTradeType;
	m_rtnOrderStatusChangeNotice.nOffsetType = (TD_OffsetType)rsp->nOffsetType;
	m_rtnOrderStatusChangeNotice.nOrderVol = rsp->nOrderVol;
	m_rtnOrderStatusChangeNotice.nOrderPrice = rsp->nOrderPrice;
	m_rtnOrderStatusChangeNotice.nCloseR = rsp->nCloseR;
	m_rtnOrderStatusChangeNotice.nOrderNum = rsp->nOrderNum;

	if(m_rtnOrderStatusChangeNotice.nOrderNum != 0)
	{
		m_rtnOrderStatusChangeNotice.pOrderDetail = (QP_OrderDetail*)malloc(sizeof(QP_OrderDetail) * m_rtnOrderStatusChangeNotice.nOrderNum);

		for(int i = 0; i < m_rtnOrderStatusChangeNotice.nOrderNum; ++i)
		{
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].szOrderStreamId = rsp->pOrderDetail[i].szOrderStreamId;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].nAccountId = rsp->pOrderDetail[i].nAccountId;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].szAccountNickName = rsp->pOrderDetail[i].szAccountNickName;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].nOrderVol = rsp->pOrderDetail[i].nOrderVol;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].nDealedPrice = rsp->pOrderDetail[i].nDealedPrice;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].nDealedVol = rsp->pOrderDetail[i].nDealedVol;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].nWithDrawnVol = rsp->pOrderDetail[i].nWithDrawnVol;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].szOrderTime = rsp->pOrderDetail[i].szOrderTime;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].nStatus = rsp->pOrderDetail[i].nStatus;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].szText = rsp->pOrderDetail[i].szText;
			m_rtnOrderStatusChangeNotice.pOrderDetail[i].nFee = rsp->pOrderDetail[i].nFee;
		}
	}

	// QP_INSERTRsp_FIELDS
	m_rtnOrderStatusChangeNotice.nOrderOwnerId = rsp->nOrderOwnerId;
	m_rtnOrderStatusChangeNotice.nOrderId = rsp->nOrderId;
	m_rtnOrderStatusChangeNotice.nSubmitVol = rsp->nSubmitVol;
	m_rtnOrderStatusChangeNotice.nDealedPrice = rsp->nDealedPrice;
	m_rtnOrderStatusChangeNotice.nDealedVol = rsp->nDealedVol;
	m_rtnOrderStatusChangeNotice.nTotalWithDrawnVol = rsp->nTotalWithDrawnVol;
	m_rtnOrderStatusChangeNotice.nInValid = rsp->nInValid;
	m_rtnOrderStatusChangeNotice.nStatus = rsp->nStatus;
	m_rtnOrderStatusChangeNotice.szInsertTime = (char*)rsp->szInsertTime;
	m_rtnOrderStatusChangeNotice.nFee = rsp->nFee;

	if(m_cb->cb_rtnOrderStatusChangeNotice)
	{
		m_cb->cb_rtnOrderStatusChangeNotice(nSessionId, &m_rtnOrderStatusChangeNotice);
	}

	if(m_rtnOrderStatusChangeNotice.pOrderDetail)
	{
		free(m_rtnOrderStatusChangeNotice.pOrderDetail);
	}

	memset(&m_rtnOrderStatusChangeNotice, 0, sizeof(QP_RtnOrderStatusChangeNotice));
}


void QP_CallbackWrap::onRtnOrderMatchNotice(const TD_RtnOrderMatchNotice *rsp)
{
	// QP_BASEMSG_FIELDS
	m_rtnOrderMatchNotice.nReqId = rsp->nReqId;
	m_rtnOrderMatchNotice.nStrategyId = rsp->nStrategyId;

	m_rtnOrderMatchNotice.nUserInt = rsp->nUserInt;
	m_rtnOrderMatchNotice.nUserDouble = rsp->nUserDouble;
	m_rtnOrderMatchNotice.szUseStr = (char*)rsp->szUseStr;

	m_rtnOrderMatchNotice.szClientId = (char*)rsp->szClientId;
	m_rtnOrderMatchNotice.nUserId = rsp->nUserId;
	// QP_RtnOrderMatchNotice_FIELDS
	m_rtnOrderMatchNotice.nOrderId = rsp->nOrderId;
	m_rtnOrderMatchNotice.szOrderStreamId = (char*)rsp->szOrderStreamId;
	m_rtnOrderMatchNotice.nMatchStreamId = rsp->nMatchStreamId;
	m_rtnOrderMatchNotice.nMatchPrice = rsp->nMatchPrice;
	m_rtnOrderMatchNotice.nMatchVol = rsp->nMatchVol;
	m_rtnOrderMatchNotice.szContractCode = (char*)rsp->szContractCode;
	m_rtnOrderMatchNotice.szContractName = (char*)rsp->szContractName;
	m_rtnOrderMatchNotice.szMatchTime = (char*)rsp->szMatchTime;
	m_rtnOrderMatchNotice.nTradeType = rsp->nTradeType;
	m_rtnOrderMatchNotice.nAccountId = rsp->nAccountId;
	m_rtnOrderMatchNotice.szAccountNickName = (char*)rsp->szAccountNickName;

	if(m_cb->cb_rtnOrderMatchNotice)
	{
		m_cb->cb_rtnOrderMatchNotice(nSessionId, &m_rtnOrderMatchNotice);
	}

	memset(&m_rtnOrderMatchNotice, 0, sizeof(QP_RtnOrderMatchNotice));
}


void QP_CallbackWrap::onRtnUserAuthen(const TD_QuantUserAuthen* notice)
{
	// QP_BASEMSG_FIELDS
	m_quantUserAuthen.nReqId = notice->nReqId;
	m_quantUserAuthen.nStrategyId = notice->nStrategyId;

	m_quantUserAuthen.nUserInt = notice->nUserInt;
	m_quantUserAuthen.nUserDouble = notice->nUserDouble;
	m_quantUserAuthen.szUseStr = (char*)notice->szUseStr;

	m_quantUserAuthen.nUserId = notice->nUserId;
	m_quantUserAuthen.szClientId = (char*)notice->szClientId;
	// QP_QuantUserAuthen
	m_quantUserAuthen.nId = notice->nId;
	m_quantUserAuthen.nGroupId = notice->nGroupId;
	m_quantUserAuthen.ifStopTrade = notice->ifStopTrade;
	m_quantUserAuthen.nStopTradePostion = notice->nStopTradePostion;
	m_quantUserAuthen.nStopPercentTradePostion = notice->nStopPercentTradePostion;
	m_quantUserAuthen.nSinglePositionHoldTime = notice->nSinglePositionHoldTime;
	m_quantUserAuthen.nSinglePositionLoss = notice->nSinglePositionLoss;
	m_quantUserAuthen.nSinglePercentPositionLoss = notice->nSinglePercentPositionLoss;

	if(m_cb->cb_rtnUserAuthen)
	{
		m_cb->cb_rtnUserAuthen(nSessionId, &m_quantUserAuthen);
	}

	memset(&m_quantUserAuthen, 0, sizeof(QP_QuantUserAuthen));
}


void QP_CallbackWrap::onRtnMaxEntrustCount(const TD_RspQryMaxEntrustCount* notice)
{
	// QP_BASEMSG_FIELDS
	m_rspQryMaxEntrustCount.nReqId = notice->nReqId;
	m_rspQryMaxEntrustCount.nStrategyId = notice->nStrategyId;

	m_rspQryMaxEntrustCount.nUserInt = notice->nUserInt;
	m_rspQryMaxEntrustCount.nUserDouble = notice->nUserDouble;
	m_rspQryMaxEntrustCount.szUseStr = (char*)notice->szUseStr;

	m_rspQryMaxEntrustCount.szClientId = (char*)notice->szClientId;
	m_rspQryMaxEntrustCount.nUserId = notice->nUserId;
	// QP_RspQryMaxEntrustCount
	m_rspQryMaxEntrustCount.pStockMaxEntrustCount.nMaxBuyCaptial = notice->pStockMaxEntrustCount.nMaxBuyCaptial;
	m_rspQryMaxEntrustCount.pStockMaxEntrustCount.nMaxSellVol = notice->pStockMaxEntrustCount.nMaxSellVol;
	m_rspQryMaxEntrustCount.pStockMaxEntrustCount.szContractCode = (char*)notice->pStockMaxEntrustCount.szContractCode;

	if(m_cb->cb_rtnMaxEntrustCount)
	{
		m_cb->cb_rtnMaxEntrustCount(nSessionId, &m_rspQryMaxEntrustCount);
	}

	memset(&m_rspQryMaxEntrustCount, 0, sizeof(QP_RspQryMaxEntrustCount));
}


void QP_CallbackWrap::onRtnUpdateUserCodePool(const TD_QuantUserCodePool* notice)
{
	// QP_BASEMSG_FIELDS
	m_quantUserCodePool.nReqId = notice->nReqId;
	m_quantUserCodePool.nStrategyId = notice->nStrategyId;

	m_quantUserCodePool.nUserInt = notice->nUserInt;
	m_quantUserCodePool.nUserDouble = notice->nUserDouble;
	m_quantUserCodePool.szUseStr = (char*)notice->szUseStr;

	m_quantUserCodePool.szClientId = (char*)notice->szClientId;
	m_quantUserCodePool.nUserId = notice->nUserId;
	// QP_QuantUserCodePool
	m_quantUserCodePool.nId             = notice->nId;
	m_quantUserCodePool.nGroupId        = notice->nGroupId;
	m_quantUserCodePool.nCodeControlNum = notice->nCodeControlNum;
	m_quantUserCodePool.pCodeControl    = NULL;

	if(m_quantUserCodePool.nCodeControlNum)
	{
		m_quantUserCodePool.pCodeControl = (QP_QuantUserCodeInfo*)malloc(sizeof(QP_QuantUserCodeInfo) * m_quantUserCodePool.nCodeControlNum);

		for(int i = 0; i < m_quantUserCodePool.nCodeControlNum; ++i)
		{
			m_quantUserCodePool.pCodeControl[i].szWinCode = notice->pCodeControl[i].szWinCode;
			m_quantUserCodePool.pCodeControl[i].nCaptial = notice->pCodeControl[i].nCaptial;
			m_quantUserCodePool.pCodeControl[i].nLendingAmount = notice->pCodeControl[i].nLendingAmount;
		}
	}

	if(m_cb->cb_rtnUpdateUserCodePool)
	{
		m_cb->cb_rtnUpdateUserCodePool(nSessionId, &m_quantUserCodePool);
	}

	if(m_quantUserCodePool.pCodeControl)
	{
		free(m_quantUserCodePool.pCodeControl);
	}

	memset(&m_quantUserCodePool, 0, sizeof(QP_QuantUserCodePool));
}


void QP_CallbackWrap::onRtnSimulationAccount(const TD_SimulationAccount* notice)
{
	m_simulationAccount.nSimAccountId = notice->nSimAccountId;
	m_simulationAccount.szNickName = (char*)notice->szNickName;
	m_simulationAccount.szText = (char*)notice->szText;
	m_simulationAccount.nTotalAmount = notice->nTotalAmount;
	m_simulationAccount.nReservationNum = notice->nReservationNum;
	m_simulationAccount.pReservationCode = NULL;

	if(m_simulationAccount.nReservationNum)
	{
		m_simulationAccount.pReservationCode = (QP_SimulationReservation*)malloc(sizeof(QP_SimulationReservation) * m_simulationAccount.nReservationNum);

		for(int i = 0; i < m_simulationAccount.nReservationNum; ++i)
		{
			m_simulationAccount.pReservationCode[i].nLendingAmount = notice->pReservationCode[i].nLendingAmount;
			m_simulationAccount.pReservationCode[i].szWinCode = notice->pReservationCode[i].szWinCode;
			m_simulationAccount.pReservationCode[i].nPrice = notice->pReservationCode[i].nPrice;
		}
	}

	if(m_cb->cb_rtnSimulationAccount)
	{
		m_cb->cb_rtnSimulationAccount(nSessionId, &m_simulationAccount);
	}

	if(m_simulationAccount.pReservationCode)
	{
		free(m_simulationAccount.pReservationCode);
	}

	memset(&m_simulationAccount, 0, sizeof(QP_SimulationAccount));
}


// ///////////////////////////
// 行情
void QP_CallbackWrap::OnRtnMarket(MD_ReqID nReqID, MD_DATA_MARKET *pMarket)
{
	m_market.nReqId = nReqID;
	m_market.szWindCode = pMarket->szWindCode;
	m_market.szCode = pMarket->szCode;
	m_market.nActionDay = pMarket->nActionDay;
	m_market.nTime = pMarket->nTime;
	m_market.nStatus = pMarket->nStatus;
	m_market.nPreClose = pMarket->nPreClose;
	m_market.nOpen = pMarket->nOpen;
	m_market.nHigh = pMarket->nHigh;
	m_market.nLow = pMarket->nLow;
	m_market.nMatch = pMarket->nMatch;
	memcpy(m_market.nAskPrice, pMarket->nAskPrice, sizeof(unsigned int) * 10);
	memcpy(m_market.nAskVol, pMarket->nAskVol, sizeof(unsigned int) * 10);
	memcpy(m_market.nBidPrice, pMarket->nBidPrice, sizeof(unsigned int) * 10);
	memcpy(m_market.nBidVol, pMarket->nBidVol, sizeof(unsigned int) * 10);
	m_market.nNumTrades = pMarket->nNumTrades;
	m_market.iVolume = pMarket->iVolume;
	m_market.iTurnover = pMarket->iTurnover;
	m_market.nTotalBidVol = pMarket->nTotalBidVol;
	m_market.nTotalAskVol = pMarket->nTotalAskVol;
	m_market.nWeightedAvgBidPrice = pMarket->nWeightedAvgBidPrice;
	m_market.nWeightedAvgAskPrice = pMarket->nWeightedAvgAskPrice;
	m_market.nIOPV = pMarket->nIOPV;
	m_market.nYieldToMaturity = pMarket->nYieldToMaturity;
	m_market.nHighLimited = pMarket->nHighLimited;
	m_market.nLowLimited = pMarket->nLowLimited;

	if(m_cb->cb_dataMarket)
	{
		m_cb->cb_dataMarket(nSessionId, &m_market);
	}
}
void QP_CallbackWrap::OnRtnKLine(MD_ReqID nReqID, MD_DATA_KLINE *pKLine)
{
	m_kline.nReqId = nReqID;
	m_kline.nType = pKLine->nType;
	m_kline.szWindCode = pKLine->szWindCode;
	m_kline.szCode = pKLine->szCode;
	m_kline.szDatetime = pKLine->szDatetime;
	m_kline.nDate = pKLine->nDate;
	m_kline.nTime = pKLine->nTime;
	m_kline.nOpen = pKLine->nOpen;
	m_kline.nHigh = pKLine->nHigh;
	m_kline.nLow = pKLine->nLow;
	m_kline.nClose = pKLine->nClose;
	m_kline.nPreClose = pKLine->nPreClose;
	m_kline.nHighLimit = pKLine->nHighLimit;
	m_kline.nLowLimit = pKLine->nLowLimit;
	m_kline.iVolume = pKLine->iVolume;
	m_kline.nTurover = pKLine->nTurover;

	if(m_cb->cb_dataKLine)
	{
		m_cb->cb_dataKLine(nSessionId, &m_kline);
	}
}
void QP_CallbackWrap::OnRtnIndex(MD_ReqID nReqID, MD_DATA_INDEX *pIndex)
{
	m_index.nReqId = nReqID;
	m_index.szWindCode = pIndex->szWindCode;
	m_index.szCode = pIndex->szCode;
	m_index.nActionDay = pIndex->nActionDay;
	m_index.nTime = pIndex->nTime;
	m_index.nOpenIndex = pIndex->nOpenIndex;
	m_index.nHighIndex = pIndex->nHighIndex;
	m_index.nLowIndex = pIndex->nLowIndex;
	m_index.nLastIndex = pIndex->nLastIndex;
	m_index.iTotalVolume = pIndex->iTotalVolume;
	m_index.iTurnover = pIndex->iTurnover;
	m_index.nPreCloseIndex = pIndex->nPreCloseIndex;

	if(m_cb->cb_dataIndex)
	{
		m_cb->cb_dataIndex(nSessionId, &m_index);
	}
}
void QP_CallbackWrap::OnRtnTransaction(MD_ReqID nReqID, MD_DATA_TRANSACTION *pTrans)
{
	m_transaction.nReqId = nReqID;
	m_transaction.szWindCode = pTrans->szWindCode;
	m_transaction.szCode = pTrans->szCode;
	m_transaction.nActionDay = pTrans->nActionDay;
	m_transaction.nTime = pTrans->nTime;
	m_transaction.nIndex = pTrans->nIndex;
	m_transaction.nPrice = pTrans->nPrice;
	m_transaction.nVolume = pTrans->nVolume;
	m_transaction.nTurnover = pTrans->nTurnover;
	m_transaction.nBSFlag = pTrans->nBSFlag;
	m_transaction.chOrderKind = pTrans->chOrderKind;
	m_transaction.nAskOrder = pTrans->nAskOrder;
	m_transaction.nBidOrder = pTrans->nBidOrder;

	if(m_cb->cb_dataTransaction)
	{
		m_cb->cb_dataTransaction(nSessionId, &m_transaction);
	}
}
void QP_CallbackWrap::OnRtnOrderQueue(MD_ReqID nReqID, MD_DATA_ORDER_QUEUE *pQueue)
{
	m_queue.nReqId = nReqID;
	m_queue.szWindCode = pQueue->szWindCode;
	m_queue.szCode = pQueue->szCode;
	m_queue.nActionDay = pQueue->nActionDay;
	m_queue.nTime = pQueue->nTime;
	m_queue.nSide = pQueue->nSide;
	m_queue.nPrice = pQueue->nPrice;
	m_queue.nOrders = pQueue->nOrders;
	m_queue.nABItems = pQueue->nABItems;
	memcpy(m_queue.nABVolume, pQueue->nABVolume, sizeof(int) * 200);

	if(m_cb->cb_dataQueue)
	{
		m_cb->cb_dataQueue(nSessionId, &m_queue);
	}
}
void QP_CallbackWrap::OnRtnOrder(MD_ReqID nReqID, MD_DATA_ORDER *pOrder)
{
	m_order.nReqId = nReqID;
	m_order.szWindCode = pOrder->szWindCode;
	m_order.szCode = pOrder->szCode;
	m_order.nActionDay = pOrder->nActionDay;
	m_order.nTime = pOrder->nTime;
	m_order.nPrice = pOrder->nPrice;
	m_order.nVolume = pOrder->nVolume;
	m_order.chOrderKind = pOrder->chOrderKind;
	m_order.chFunctionCode = pOrder->chFunctionCode;

	if(m_cb->cb_dataOrder)
	{
		m_cb->cb_dataOrder(nSessionId, &m_order);
	}
}
void QP_CallbackWrap::OnRtnFuture(MD_ReqID nReqID, MD_DATA_FUTURE *pFuture)
{
	m_future.nReqId = nReqID;
	m_future.szWindCode = pFuture->szWindCode;
	m_future.szCode = pFuture->szCode;
	m_future.nActionDay = pFuture->nActionDay;
	m_future.nTime = pFuture->nTime;
	m_future.nStatus = pFuture->nStatus;
	m_future.iPreOpenInterest = pFuture->iPreOpenInterest;
	m_future.nPreClose = pFuture->nPreClose;
	m_future.nPreSettlePrice = pFuture->nPreSettlePrice;
	m_future.nOpen = pFuture->nOpen;
	m_future.nHigh = pFuture->nHigh;
	m_future.nLow = pFuture->nLow;
	m_future.nMatch = pFuture->nMatch;
	m_future.iVolume = pFuture->iVolume;
	m_future.iTurnover = pFuture->iTurnover;
	m_future.iOpenInterest = pFuture->iOpenInterest;
	m_future.nClose = pFuture->nClose;
	m_future.nSettlePrice = pFuture->nSettlePrice;
	m_future.nHighLimited = pFuture->nHighLimited;
	m_future.nLowLimited = pFuture->nLowLimited;
	memcpy(m_future.nAskPrice, pFuture->nAskPrice, sizeof(unsigned int) * 5);
	memcpy(m_future.nAskVol, pFuture->nAskVol, sizeof(unsigned int) * 5);
	memcpy(m_future.nBidPrice, pFuture->nBidPrice, sizeof(unsigned int) * 5);
	memcpy(m_future.nBidVol, pFuture->nBidVol, sizeof(unsigned int) * 5);

	if(m_cb->cb_dataFuture)
	{
		m_cb->cb_dataFuture(nSessionId, &m_future);
	}
}
void QP_CallbackWrap::OnRtnFutureOption(MD_ReqID nReqID, MD_DATA_FUTURE *pFuture)
{
	m_future.nReqId = nReqID;
	m_future.szWindCode = pFuture->szWindCode;
	m_future.szCode = pFuture->szCode;
	m_future.nActionDay = pFuture->nActionDay;
	m_future.nTime = pFuture->nTime;
	m_future.nStatus = pFuture->nStatus;
	m_future.iPreOpenInterest = pFuture->iPreOpenInterest;
	m_future.nPreClose = pFuture->nPreClose;
	m_future.nPreSettlePrice = pFuture->nPreSettlePrice;
	m_future.nOpen = pFuture->nOpen;
	m_future.nHigh = pFuture->nHigh;
	m_future.nLow = pFuture->nLow;
	m_future.nMatch = pFuture->nMatch;
	m_future.iVolume = pFuture->iVolume;
	m_future.iTurnover = pFuture->iTurnover;
	m_future.iOpenInterest = pFuture->iOpenInterest;
	m_future.nClose = pFuture->nClose;
	m_future.nSettlePrice = pFuture->nSettlePrice;
	m_future.nHighLimited = pFuture->nHighLimited;
	m_future.nLowLimited = pFuture->nLowLimited;
	memcpy(m_future.nAskPrice, pFuture->nAskPrice, sizeof(unsigned int) * 5);
	memcpy(m_future.nAskVol, pFuture->nAskVol, sizeof(unsigned int) * 5);
	memcpy(m_future.nBidPrice, pFuture->nBidPrice, sizeof(unsigned int) * 5);
	memcpy(m_future.nBidVol, pFuture->nBidVol, sizeof(unsigned int) * 5);

	if(m_cb->cb_dataFuture)
	{
		m_cb->cb_dataFutureOption(nSessionId, &m_future);
	}
}
void QP_CallbackWrap::OnRtnDayBegin(MD_ReqID nReqID, MD_ISODateTimeType pDate)
{
	if(m_cb->cb_rtnDayBegin)
	{
		m_cb->cb_rtnDayBegin(nSessionId, nReqID, pDate);
	}
}
void QP_CallbackWrap::OnRtnDayEnd(MD_ReqID nReqID, MD_ISODateTimeType pDate)
{
	if(m_cb->cb_rtnDayEnd)
	{
		m_cb->cb_rtnDayEnd(nSessionId, nReqID, pDate);
	}
}
void QP_CallbackWrap::OnRtnTimeless(MD_ReqID nReqID)
{
	if(m_cb->cb_rtnTimeLess)
	{
		m_cb->cb_rtnTimeLess(nSessionId, nReqID);
	}
}

void QP_CallbackWrap::OnRspTradingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg)
{
	m_rspDayInfo.nReqId = nReqID;
	m_rspDayInfo.pWindCode = NULL;
	m_rspDayInfo.nWindCodeNum = nWindCodeNum;
	m_rspDayInfo.szBeginDay = szBeginDay;
	m_rspDayInfo.szEndDay = szEndDay;
	m_rspDayInfo.nErrNo = nErrNo;
	m_rspDayInfo.szErrMsg = (char*)szErrMsg;

	if(nWindCodeNum)
	{
		m_rspDayInfo.pWindCode = (char**)malloc(sizeof(char*)*nWindCodeNum);

		for(int i = 0; i < nWindCodeNum; ++i)
		{
			m_rspDayInfo.pWindCode[i] = (char*)pWindCode[i];
		}
	}

	if(m_cb->cb_rspTradingDay)
	{
		m_cb->cb_rspTradingDay(nSessionId, &m_rspDayInfo);
	}

	if(m_rspDayInfo.pWindCode)
	{
		free(m_rspDayInfo.pWindCode);
	}

	memset(&m_rspDayInfo, 0, sizeof(QP_QryDayInfoRsp));
}
void QP_CallbackWrap::OnRspHaltingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg)
{
	m_rspDayInfo.nReqId = nReqID;
	m_rspDayInfo.pWindCode = NULL;
	m_rspDayInfo.nWindCodeNum = nWindCodeNum;
	m_rspDayInfo.szBeginDay = szBeginDay;
	m_rspDayInfo.szEndDay = szEndDay;
	m_rspDayInfo.nErrNo = nErrNo;
	m_rspDayInfo.szErrMsg = (char*)szErrMsg;

	if(nWindCodeNum)
	{
		m_rspDayInfo.pWindCode = (char**)malloc(sizeof(char*)*nWindCodeNum);

		for(int i = 0; i < nWindCodeNum; ++i)
		{
			m_rspDayInfo.pWindCode[i] = (char*)pWindCode[i];
		}
	}

	if(m_cb->cb_rspHaltingDay)
	{
		m_cb->cb_rspHaltingDay(nSessionId, &m_rspDayInfo);
	}

	if(m_rspDayInfo.pWindCode)
	{
		free(m_rspDayInfo.pWindCode);
	}

	memset(&m_rspDayInfo, 0, sizeof(QP_QryDayInfoRsp));
}
void QP_CallbackWrap::OnRspSubQuote(MD_ReqID nReqID, MD_SubType nSubType, MD_CycType nCycType, const MD_CodeType *pSubWindCode, long nSubWindCodeNum, MD_ISODateTimeType szBeginTime, MD_ISODateTimeType szEndTime, int nErrNo, const char *szErrMsg)
{
	m_rspSubQuote.nReqId = nReqID;
	m_rspSubQuote.nSubType = nSubType;
	m_rspSubQuote.nCycType = nCycType;
	m_rspSubQuote.pSubCode = NULL;
	m_rspSubQuote.nSubCodeNum = nSubWindCodeNum;
	m_rspSubQuote.szBeginTime = szBeginTime;
	m_rspSubQuote.szEndTime = szEndTime;
	m_rspSubQuote.nErrNo = nErrNo;
	m_rspSubQuote.szErrMsg = (char*)szErrMsg;

	if(nSubWindCodeNum)
	{
		m_rspSubQuote.pSubCode = (char**)malloc(sizeof(char*)*nSubWindCodeNum);

		for(int i = 0; i < nSubWindCodeNum; ++i)
		{
			m_rspSubQuote.pSubCode[i] = (char*)pSubWindCode[i];
		}
	}

	if(m_cb->cb_rspSubQuote)
	{
		m_cb->cb_rspSubQuote(nSessionId, &m_rspSubQuote);
	}

	if(m_rspSubQuote.pSubCode)
	{
		free(m_rspSubQuote.pSubCode);
	}

	memset(&m_rspSubQuote, 0, sizeof(QP_SubQuoteRsp));
}
void QP_CallbackWrap::OnRtnTradingCode(const MD_DATA_CODE *pWindCode, long nWindCodeNum, const MD_DATA_OPTION_CODE *pOptionCode, long nOptionCodeNum)
{
	QP_DATA_CODE * tempCode;
	QP_DATA_OPTION_CODE* tempOptionCode;

	if(nWindCodeNum != 0)
	{
		tempCode = new QP_DATA_CODE[nWindCodeNum];
		QP_DATA_CODE* ptrCode = tempCode;
		MD_DATA_CODE* ptrWincode = (MD_DATA_CODE*)pWindCode;

		for(int i = 0; i < nWindCodeNum; ++i)
		{
			ptrCode->szWindCode = ptrWincode->szWindCode;
			ptrCode->szMarket = ptrWincode->szMarket;
			ptrCode->szCode = ptrWincode->szCode;
			ptrCode->szENName = ptrWincode->szENName;
			ptrCode->szCNName = ptrWincode->szCNName;
			ptrCode->nType = ptrWincode->nType;

			++ptrCode;
			++ptrWincode;
		}
	}
	else
	{
		tempCode = NULL;
	}


	if(nOptionCodeNum != 0)
	{
		tempOptionCode = new QP_DATA_OPTION_CODE[nOptionCodeNum];
		QP_DATA_OPTION_CODE* ptrCode = tempOptionCode;
		MD_DATA_OPTION_CODE* ptrOptioncode = (MD_DATA_OPTION_CODE*)pOptionCode;

		for(int i = 0; i < nOptionCodeNum; ++i)
		{
			ptrCode->basicCode.szWindCode = ptrOptioncode->basicCode.szWindCode;
			ptrCode->basicCode.szMarket = ptrOptioncode->basicCode.szMarket;
			ptrCode->basicCode.szCode = ptrOptioncode->basicCode.szCode;
			ptrCode->basicCode.szENName = ptrOptioncode->basicCode.szENName;
			ptrCode->basicCode.szCNName = ptrOptioncode->basicCode.szCNName;
			ptrCode->basicCode.nType = ptrOptioncode->basicCode.nType;

			ptrCode->szContractID = ptrOptioncode->szContractID;
			ptrCode->szUnderlyingSecurityID = ptrOptioncode->szUnderlyingSecurityID;
			ptrCode->chCallOrPut = ptrOptioncode->chCallOrPut;
			ptrCode->nExerciseDate = ptrOptioncode->nExerciseDate;

			ptrCode->chUnderlyingType = ptrOptioncode->chUnderlyingType;
			ptrCode->chOptionType = ptrOptioncode->chOptionType;
			ptrCode->chPriceLimitType = ptrOptioncode->chPriceLimitType;
			ptrCode->nContractMultiplierUnit = ptrOptioncode->nContractMultiplierUnit;
			ptrCode->nExercisePrice = ptrOptioncode->nExercisePrice;
			ptrCode->nStartDate = ptrOptioncode->nStartDate;
			ptrCode->nEndDate = ptrOptioncode->nEndDate;
			ptrCode->nExpireDate = ptrOptioncode->nExpireDate;

			++ptrCode;
			++ptrOptioncode;
		}
	}
	else
	{
		tempOptionCode = NULL;
	}

	m_cb->cb_dataTradingCode(nSessionId, tempCode, nWindCodeNum, tempOptionCode, nOptionCodeNum);

	if(tempCode != NULL)
	{
		delete[] tempCode;
	}

	if(tempOptionCode != NULL)
	{
		delete[] tempOptionCode;
	}
}
void QP_CallbackWrap::OnRtnTradingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum)
{
	m_rtnDayInfo.nReqId = nReqID;
	m_rtnDayInfo.szWindCode = (char*)szWindCode;
	m_rtnDayInfo.pDay = NULL;
	m_rtnDayInfo.nDayNum = nDayNum;

	if(nDayNum)
	{
		m_rtnDayInfo.pDay = (char**)malloc(sizeof(char*) * nDayNum);

		for(int i = 0; i < nDayNum; ++i)
		{
			m_rtnDayInfo.pDay[i] = (char*)pDay[i];
		}
	}

	m_cb->cb_dataTradingDay(nSessionId, &m_rtnDayInfo);

	if(m_rtnDayInfo.pDay)
	{
		free(m_rtnDayInfo.pDay);
	}

	memset(&m_rtnDayInfo, 0, sizeof(QP_DayInfoRtn));
}
void QP_CallbackWrap::OnRtnHaltingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum)
{
	m_rtnDayInfo.nReqId = nReqID;
	m_rtnDayInfo.szWindCode = (char*)szWindCode;
	m_rtnDayInfo.pDay = NULL;
	m_rtnDayInfo.nDayNum = nDayNum;

	if(nDayNum)
	{
		m_rtnDayInfo.pDay = (char**)malloc(sizeof(char*) * nDayNum);

		for(int i = 0; i < nDayNum; ++i)
		{
			m_rtnDayInfo.pDay[i] = (char*)pDay[i];
		}
	}

	m_cb->cb_dataHaltingDay(nSessionId, &m_rtnDayInfo);

	if(m_rtnDayInfo.pDay)
	{
		free(m_rtnDayInfo.pDay);
	}

	memset(&m_rtnDayInfo, 0, sizeof(QP_DayInfoRtn));
}


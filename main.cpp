// test.cpp: 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <string.h>
#include "./src/QP_Api.h"
#pragma comment(lib,"../x64/Debug/QP_Api.lib")

void onConnect_cb(int sessionId, int srvTyep)       // sessionId, srvType
{

}
void onDisconnect_cb(int sessionId, int srvTyep)                   // sessionId, srvType
{

}
void rtnUserInfo_cb(int sessionId, const QP_QuantUserBase* pData)
{

}

void dataMarket_cb(int sessionId, const QP_DATA_MARKET* msgSt)
{
	printf("%d, %s, %d \n", sessionId, msgSt->szWindCode, msgSt->nTime);
	int x = 0;
}

int main()
{
	QP_CallBack* cb = new QP_CallBack;
	cb->cb_onConnect = onConnect_cb;
	cb->cb_onDisconnect = onDisconnect_cb;
	cb->cb_rtnUserInfo = rtnUserInfo_cb;

	cb->cb_dataMarket = dataMarket_cb;

	int sessionId = QP_CreatSession(cb, 0);
	int reqId = 0;

	QP_Login(sessionId, "abramwang", "abcd1234");

	QP_SubQuoteReq req;
	memset(&req, 0, sizeof(QP_SubQuoteReq));
	req.nReqId = reqId++;
	req.nSubType = QP_SubType_market;
	req.nCycType = QP_CycType_none;
	req.szBeginTime = new char[21];
	req.szEndTime = new char[21];
	strcpy_s(req.szBeginTime, 21, "2018-05-03 09:30:00");
	strcpy_s(req.szEndTime, 21, "2018-05-03 23:59:00");
	req.nSubCodeNum = 1;
	req.pSubCode = new char*[1];
	req.pSubCode[0] = new char[32];
	memset(req.pSubCode[0], 0, 32);
	memcpy(req.pSubCode[0], "600000.SH", 9);

	//QP_ReqSubQuote(sessionId, &req);

	while(true)
	{

	}

	return 0;
}


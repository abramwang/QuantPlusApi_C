#ifndef _QP_API_STRUCT_
#define _QP_API_STRUCT_
#endif

#include <stdint.h>

// 服务器类型
typedef int QP_SrvType;
#define QP_SrvType_none     0x0000      // 未知类型
#define QP_SrvType_history  0x0001      // 历史缓存行情服务器
#define QP_SrvType_cache    0x0002      // 实时缓存行情服务器
#define QP_SrvType_realtime 0x0004      // 实时推送行情服务器

// 订阅类型
typedef int QP_SubType;
#define QP_SubType_none             0x0000      // 未知类型
#define QP_SubType_market           0x0001      // 个股行情
#define QP_SubType_index            0x0002      // 指数行情
#define QP_SubType_trans            0x0004      // 逐笔成交
#define QP_SubType_order            0x0008      // 逐笔委托
#define QP_SubType_order_queue      0x0010      // 委托队列
#define QP_SubType_future           0x0020      // 期货行情
#define QP_SubType_future_option    0x0040      // 期权行情
#define QP_SubType_kline            0x0080      // K线行情

// 周期类型
typedef int QP_CycType;
#define QP_CycType_none             0x0000      // 未知类型
#define QP_CycType_second_10        0x0001      // 10秒
#define QP_CycType_minute           0x0002      // 分
#define QP_CycType_minute_5         0x0004      // 5分
#define QP_CycType_minute_15        0x0008      // 15分
#define QP_CycType_minute_30        0x0010      // 30分
#define QP_CycType_hour             0x0020      // 小时
#define QP_CycType_day              0x0040      // 日

// 交易类型
typedef int QP_TradeType;
#define QP_TradeType_None           0
#define QP_TradeType_Sell           1           // 卖出
#define QP_TradeType_Buy            2           // 买入

typedef int QP_OffsetType;
#define QP_OffsetType_None          0
#define QP_OffsetType_Open          1           //开仓
#define QP_OffsetType_Close         2           //平仓

typedef int QP_OrderStatusType;
#define QP_OrderStatusType_fail         -10     //指令失败
#define QP_OrderStatusType_removed      -9      //撤单成功
#define QP_OrderStatusType_allDealed    -8      //全部成交
#define QP_OrderStatusType_unAccpet     0        //未接受
#define QP_OrderStatusType_accpeted     1        //已接受未受理
#define QP_OrderStatusType_queued       2          //正在排队  (已受理状态)
#define QP_OrderStatusType_toRemove     3        //待报撤单
#define QP_OrderStatusType_removing     4        //已报待撤
#define QP_OrderStatusType_partRemoved  5     //部分撤单
#define QP_OrderStatusType_partDealed   6      //部分成交

typedef int QP_QuantUserType;
#define QP_QuantUserType_Risk          1     //  风控员
#define QP_QuantUserType_Trade         2     //  交易员


/*
    系统结构体
*/
typedef struct QP_UserBase
{
	int64_t nId;
	char* szUserName;
	char* szNickName;
	int nGroupId;
} QP_UserBase;

/*
    行情结构体
*/
#define QP_QryDayInfoReq_FIELDS       \
    unsigned int    nReqId;         \
    char*           szBeginDay;     \
    char*           szEndDay;       \
    unsigned int    nWindCodeNum;   \
    char**          pWindCode;      \

typedef struct QP_QryDayInfoReq
{
	QP_QryDayInfoReq_FIELDS
} QP_QryDayInfoReq;

typedef struct QP_QryDayInfoRsp
{
	QP_QryDayInfoReq_FIELDS
	int             nErrNo;
	char            *szErrMsg;
} QP_QryDayInfoRsp;


#define QP_SubQuoteReq_FIELDS       \
    unsigned int    nReqId;         \
    QP_SubType      nSubType;       \
    QP_CycType      nCycType;       \
    char*           szBeginTime;    \
    char*           szEndTime;      \
    unsigned int    nSubCodeNum;    \
    char**          pSubCode;       \

typedef struct QP_SubQuoteReq
{
	QP_SubQuoteReq_FIELDS
} QP_SubQuoteReq;

typedef struct QP_SubQuoteRsp
{
	QP_SubQuoteReq_FIELDS
	int nErrNo;
	char *szErrMsg;
} QP_SubQuoteRsp;

typedef struct QP_DayInfoRtn
{
	unsigned int    nReqId;
	char*           szWindCode;
	unsigned int    nDayNum;
	char**          pDay;
} QP_DayInfoRtn;


typedef struct QP_DATA_CODE
{
	char*   szWindCode;         //Wind Code: AG1302.SHF
	char*   szMarket;           //market code: SHF
	char*   szCode;             //original code:ag1302
	char*   szENName;
	char*   szCNName;           //chinese name: 沪银1302
	int     nType;
} QP_DATA_CODE;

typedef struct QP_DATA_OPTION_CODE
{
	QP_DATA_CODE basicCode;

	char* szContractID;             // 期权合约代码
	char* szUnderlyingSecurityID;   // 标的证券代码
	char chCallOrPut;               // 认购认沽C1        认购，则本字段为“C”；若为认沽，则本字段为“P”
	int  nExerciseDate;             // 期权行权日，YYYYMMDD

	//扩充字段
	char chUnderlyingType;          // 标的证券类型C3    0-A股 1-ETF (EBS – ETF， ASH – A 股)
	char chOptionType;              // 欧式美式C1        若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”

	char chPriceLimitType;          // 涨跌幅限制类型C1 ‘N’表示有涨跌幅限制类型, ‘R’表示无涨跌幅限制类型
	int  nContractMultiplierUnit;   // 合约单位,         经过除权除息调整后的合约单位, 一定是整数
	int  nExercisePrice;            // 期权行权价,       经过除权除息调整后的期权行权价，右对齐，精确到厘
	int  nStartDate;                // 期权首个交易日,YYYYMMDD
	int  nEndDate;                  // 期权最后交易日/行权日，YYYYMMDD
	int  nExpireDate;               // 期权到期日，YYYYMMDD
} QP_DATA_OPTION_CODE;

typedef struct QP_DATA_MARKET
{
	unsigned int    nReqId;
	char*           szWindCode;             //600001.SH
	char*           szCode;                 //原始Code
	int             nActionDay;             //业务发生日(自然日)
	int             nTime;                  //时间(HHMMSSmmm)
	int             nStatus;                //状态
	unsigned int    nPreClose;              //前收盘价=实际价格(单位: 元/手)x10000
	unsigned int    nOpen;                  //开盘价=实际价格(单位: 元/手)x10000
	unsigned int    nHigh;                  //最高价=实际价格(单位: 元/手)x10000
	unsigned int    nLow;                   //最低价=实际价格(单位: 元/手)x10000
	unsigned int    nMatch;                 //最新价=实际价格(单位: 元/手)x10000
	unsigned int    nAskPrice[10];          //申卖价=实际价格(单位: 元/手)x10000
	unsigned int    nAskVol[10];            //申卖量=实际手数(单位: 手)
	unsigned int    nBidPrice[10];          //申买价=实际价格(单位: 元/手)x10000
	unsigned int    nBidVol[10];            //申买量=实际手数(单位: 手)
	unsigned int    nNumTrades;             //成交笔数=实际笔数(单位: 笔)
	int64_t         iVolume;                //成交总量=实际手数(单位: 手)
	int64_t         iTurnover;              //成交总金额=实际金额(单位: 元)
	int64_t         nTotalBidVol;           //委托买入总量=实际手数(单位: 手)
	int64_t         nTotalAskVol;           //委托卖出总量=实际手数(单位: 手)
	unsigned int    nWeightedAvgBidPrice;   //加权平均委买价格=实际价格(单位: 元/手)x10000
	unsigned int    nWeightedAvgAskPrice;   //加权平均委卖价格=实际价格(单位: 元/手)x10000
	int             nIOPV;                  //IOPV净值估值
	int             nYieldToMaturity;       //到期收益率
	unsigned int    nHighLimited;           //涨停价=实际价格(单位: 元/手)x10000
	unsigned int    nLowLimited;            //跌停价=实际价格(单位: 元/手)x10000
} QP_DATA_MARKET;

typedef struct QP_DATA_INDEX
{
	unsigned int    nReqId;
	char*           szWindCode;         //600001.SH
	char*           szCode;             //原始Code
	int             nActionDay;             //业务发生日(自然日)
	int             nTime;                  //时间(HHMMSSmmm)
	int             nOpenIndex;             //今开盘指数=实际价格(单位: 元/手)x10000
	int             nHighIndex;             //最高指数=实际价格(单位: 元/手)x10000
	int             nLowIndex;              //最低指数=实际价格(单位: 元/手)x10000
	int             nLastIndex;             //最新指数=实际价格(单位: 元/手)x10000
	int64_t         iTotalVolume;           //参与计算相应指数的交易数量=实际手数(单位: 手)
	int64_t         iTurnover;              //参与计算相应指数的成交金额=实际金额(单位: 元)
	int             nPreCloseIndex;         //前盘指数=实际价格(单位: 元/手)x10000
} QP_DATA_INDEX;

typedef struct QP_DATA_FUTURE
{
	unsigned int    nReqId;
	char*           szWindCode;         //600001.SH
	char*           szCode;             //原始Code
	int             nActionDay;             //业务发生日(自然日)
	int             nTime;                  //时间(HHMMSSmmm)
	int             nStatus;                //状态
	int64_t         iPreOpenInterest;       //昨持仓
	unsigned int    nPreClose;              //昨收盘价=实际价格(单位: 元/手)x10000
	unsigned int    nPreSettlePrice;        //昨结算=实际价格(单位: 元/手)x10000
	unsigned int    nOpen;                  //开盘价=实际价格(单位: 元/手)x10000
	unsigned int    nHigh;                  //最高价=实际价格(单位: 元/手)x10000
	unsigned int    nLow;                   //最低价=实际价格(单位: 元/手)x10000
	unsigned int    nMatch;                 //最新价=实际价格(单位: 元/手)x10000
	int64_t         iVolume;                //成交总量=实际手数(单位: 手)
	int64_t         iTurnover;              //成交总金额=实际金额(单位: 元)
	int64_t         iOpenInterest;          //持仓总量=实际手数(单位: 手)
	unsigned int    nClose;                 //今收盘=实际价格(单位: 元/手)x10000
	unsigned int    nSettlePrice;           //今结算=实际价格(单位: 元/手)x10000
	unsigned int    nHighLimited;           //涨停价=实际价格(单位: 元/手)x10000
	unsigned int    nLowLimited;            //跌停价=实际价格(单位: 元/手)x10000
	unsigned int    nAskPrice[5];           //申卖价=实际价格(单位: 元/手)x10000
	unsigned int    nAskVol[5];             //申卖量=实际手数(单位: 手)
	unsigned int    nBidPrice[5];           //申买价=实际价格(单位: 元/手)x10000
	unsigned int    nBidVol[5];             //申买量=实际手数(单位: 手)
} QP_DATA_FUTURE;

typedef struct QP_DATA_ORDER_QUEUE
{
	unsigned int    nReqId;
	char*           szWindCode; //600001.SH
	char*           szCode;     //原始Code
	int             nActionDay;     //自然日
	int             nTime;          //时间(HHMMSSmmm)
	int             nSide;          //买卖方向('B':Bid 'A':Ask)
	int             nPrice;         //委托价格=实际价格(单位: 元/手)x10000
	int             nOrders;        //订单数量
	int             nABItems;       //明细个数
	int             nABVolume[200]; //订单明细=实际手数(单位: 手)
} QP_DATA_ORDER_QUEUE;

typedef struct QP_DATA_TRANSACTION
{
	unsigned int    nReqId;
	char*           szWindCode; //600001.SH
	char*           szCode;     //原始Code
	int             nActionDay;     //自然日
	int             nTime;          //成交时间(HHMMSSmmm)
	int             nIndex;         //成交编号
	int             nPrice;         //成交价格=实际价格(单位: 元/手)x10000
	int             nVolume;        //成交数量=实际手数(单位: 手)
	int             nTurnover;      //成交金额=实际金额(单位: 元)
	int             nBSFlag;        //买卖方向(买：'B', 卖：'A', 不明：' ')
	char            chOrderKind;    //成交类别
	int             nAskOrder;      //叫卖方委托序号
	int             nBidOrder;      //叫买方委托序号
} QP_DATA_TRANSACTION;

typedef struct QP_DATA_ORDER
{
	unsigned int    nReqId;
	char*           szWindCode; //600001.SH
	char*           szCode;     //原始Code
	int             nActionDay;     //委托日期(YYYYMMDD)
	int             nTime;          //委托时间(HHMMSSmmm)
	int             nOrder;         //委托号
	int             nPrice;         //委托价格=实际价格(单位: 元/手)x10000
	int             nVolume;        //委托数量=实际手数(单位: 手)
	char            chOrderKind;    //委托类别
	char            chFunctionCode; //委托代码('B','S','C')
} QP_DATA_ORDER;

typedef struct QP_DATA_KLINE                    //模拟数据请求
{
	unsigned int        nReqId;
	QP_CycType          nType;           //周期类型
	char*               szWindCode;      //600001.SH
	char*               szCode;          //原始Code
	char*               szDatetime;      //时间
	int                 nDate;           //日期 yyyyMMdd
	int                 nTime;           //时间 hhmmsszzz
	double              nOpen;           //开盘价=实际价格(单位: 元/手)
	double              nHigh;           //最高价=实际价格(单位: 元/手)
	double              nLow;            //最低价=实际价格(单位: 元/手)
	double              nClose;          //今收价=实际价格(单位: 元/手)
	double              nPreClose;       //昨收价=实际价格(单位: 元/手)
	double              nHighLimit;      //涨停价=实际价格(单位: 元/手)
	double              nLowLimit;       //跌停价=实际价格(单位: 元/手)
	int64_t             iVolume;         //成交数量=实际手数(单位: 手)
	int64_t             nTurover;        //成交金额=实际金额(单位: 元)
} QP_DATA_KLINE;


/*
    交易结构体
*/

#define QP_BASEMSG_FIELDS                                               \
    int         nReqId;                                                 \
    int64_t     nStrategyId;                                            \
    int         nUserInt;                                               \
    double      nUserDouble;                                            \
    char*       szUseStr;                                               \
    int64_t     nUserId;                                                \
    char*       szClientId;                                             \

typedef struct QP_OrderDetail
{
	char*               szOrderStreamId;    ///委托编号（broker 或交易所的唯一编号）
	int                 nAccountId;         ///券商资金账户Id           //  如需指定资金账号下单，此字段在下单的时候需要填写
	char*               szAccountNickName;  ///资金账户别名
	int                 nOrderVol;          ///委托申报量        //  如需指定资金账号下单，此字段在下单的时候需要填写
	int                 nDealedPrice;       ///成交均价  * 10000
	int                 nDealedVol;         ///成交量
	int                 nWithDrawnVol;      ///撤单数量
	char*               szOrderTime;        ///委托时间
	QP_OrderStatusType  nStatus;            ///状态
	char*               szText;             ///备注
	double              nFee;               ///手续费
}
QP_OrderDetail;

#define QP_INSERTReq_FIELDS                                             \
    QP_BASEMSG_FIELDS                                                   \
    char*               szContractCode;                                 \
    char*               szContractName;                                 \
    QP_TradeType        nTradeType;                                     \
    QP_OffsetType       nOffsetType;                                    \
    int                 nOrderPrice;                                    \
    int                 nOrderVol;                                      \
    int                 nOrderNum;                                      \
    QP_OrderDetail*     pOrderDetail;                                   \
    int                 nCloseR;                                        \

#define QP_INSERTRsp_FIELDS                                 \
    QP_INSERTReq_FIELDS                                     \
    int64_t         nOrderOwnerId;                          \
    int64_t         nOrderId;                               \
    int             nSubmitVol;                             \
    int             nDealedPrice;                           \
    int             nDealedVol;                             \
    int             nTotalWithDrawnVol;                     \
    int             nInValid;                               \
    QP_OrderStatusType  nStatus;                            \
    char* szInsertTime;                                     \
    double               nFee;                              \

typedef struct QP_OrderInsertReq
{
	QP_INSERTReq_FIELDS
} QP_OrderInsertReq;

typedef struct QP_OrderDeleteReq
{
	QP_BASEMSG_FIELDS
	int64_t             nOrderId;           ///原始订单服务器唯一Id
	char*               szOrderStreamId;    ///委托编号（broker 或交易所的唯一编号）
} QP_OrderDeleteReq;


typedef struct QP_OrderQryReq
{
	QP_BASEMSG_FIELDS
	char*              szContractCode;      //证券合约代码
	int                nIndex;              //起始位置(不填默认从头开始)
	int                nNum;                //数量(不填默认查全部)
} QP_OrderQryReq;


typedef struct QP_MatchQryReq
{
	QP_BASEMSG_FIELDS
	char*              szContractCode;      //证券合约代码
	int                nIndex;              //起始位置(不填默认从头开始)
	int                nNum;                //数量(不填默认查全部)
} QP_MatchQryReq;

typedef struct QP_PositionQryReq
{
	QP_BASEMSG_FIELDS
	char*              szContractCode;      //证券合约代码
} QP_PositionQryReq;

typedef struct QP_MaxEntrustCountQryReq
{
	QP_BASEMSG_FIELDS
	char*             szContractCode;      //股票代码

} QP_MaxEntrustCountQryReq;


typedef struct QP_AccountMaxEntrustCountQryReq
{
	QP_BASEMSG_FIELDS
	char*             szContractCode;      //股票代码
	int                nAccountId;         //资金账号

} QP_AccountMaxEntrustCountQryReq;


typedef struct QP_SimulationReservation
{
	char*      szWinCode;
	int         nLendingAmount;             // 底仓数量
	double      nPrice;                     // 底仓均价
} QP_SimulationReservation;



typedef struct QP_SimulationAccount
{
	int64_t        nSimAccountId;
	char*           szNickName;
	char*           szText;
	double          nTotalAmount;
	int             nReservationNum;   // 底仓股票数量
	QP_SimulationReservation   *pReservationCode;  // 底仓股票代码
} QP_SimulationAccount;



typedef struct QP_QuantUserCodeInfo
{
	char*       szWinCode;
	double      nCaptial;                   // 最大可用资金
	int         nLendingAmount;             // 最大可用券
} QP_QuantUserCodeInfo;

typedef struct QP_StockMaxEntrustCount
{
	char*       szContractCode;             //  股票代码
	double      nMaxBuyCaptial;             //  最大可买资金量
	int         nMaxSellVol;                //  最大可卖
} QP_StockMaxEntrustCount;


typedef  struct QP_QuantUserAuthen
{
	QP_BASEMSG_FIELDS
	int64_t             nId;
	int                 nGroupId;

	bool                ifStopTrade;                     // 是否停机
	int                 nStopTradePostion;               // 停机位(亏算资金量)
	double              nStopPercentTradePostion;        // 停机位(亏损比例)

	int                 nSinglePositionHoldTime;         // 单笔持仓时间阈值
	int                 nSinglePositionLoss;             // 单笔持仓亏损阈值(亏算资金量)
	double              nSinglePercentPositionLoss;      // 单笔持仓亏损阈值(亏损比例)


} QP_QuantUserAuthen;


typedef struct QP_RspQryPosition
{
	QP_BASEMSG_FIELDS
	char*   szContractCode;
	int     nPosition;          //  持仓总量
	double  nPrice;             //  持仓均价 * 10000
	double  nProfit;            //  浮盈
	double  nSelltleProfit;     //  已结算的盈利

} QP_RspQryPosition;

typedef QP_RspQryPosition QP_RtnProfit;

#define QP_RtnOrderMatchNotice_FIELDS                       \
    int64_t             nOrderId;                           \
    char*               szOrderStreamId;                    \
    int64_t             nMatchStreamId;                     \
    int                 nMatchPrice;                        \
    int                 nMatchVol;                          \
    char*               szContractCode;                     \
    char*               szContractName;                     \
    char*               szMatchTime;                        \
    QP_TradeType        nTradeType;                         \
    int                 nAccountId;                         \
    char*               szAccountNickName;                  \

typedef struct QP_RtnOrderMatchNotice
{
	QP_BASEMSG_FIELDS
	QP_RtnOrderMatchNotice_FIELDS
} QP_RtnOrderMatchNotice;

typedef struct QP_RspOrderInsert
{
	QP_INSERTRsp_FIELDS
} QP_RspOrderInsert;

typedef QP_RspOrderInsert QP_RtnOrderStatusChangeNotice;

typedef struct QP_RspQryMaxEntrustCount
{
	QP_BASEMSG_FIELDS
	QP_StockMaxEntrustCount pStockMaxEntrustCount;
} QP_RspQryMaxEntrustCount;

typedef struct QP_RspQryAccountMaxEntrustCount
{
	QP_BASEMSG_FIELDS
	int     nAccountId;                     ///  资金账号
	char*   szAccountNickName;              ///资金账户别名
	int     nNum;                           ///  可用股票数
	QP_StockMaxEntrustCount* pStockMaxEntrustCount;     ///  指针偏移
	bool bStatus;               /// 资金状态
	int nAvailableCaptial;      /// 资金账号层面可用资金
} QP_RspQryAccountMaxEntrustCount;

typedef struct QP_RspQryMatch
{
	QP_BASEMSG_FIELDS
	QP_RtnOrderMatchNotice_FIELDS
	int nIndex;
} QP_RspQryMatch;

typedef struct QP_RspQryOrder
{
	QP_INSERTRsp_FIELDS
	int            nIndex;
} QP_RspQryOrder;

typedef QP_OrderDeleteReq  QP_RspOrderDelete;


typedef struct QP_Priority
{
	int          nPriority;
	int64_t      nAccountId;
} QP_Priority;

typedef  struct QP_RspQryPriority
{
	QP_BASEMSG_FIELDS
	// 用户id
	int64_t               nQueryUserid;
	///证券合约代码
	char*                 szContractCode;

	int                   nNum;
	QP_Priority*          pPriority;
} QP_RspQryPriority;

typedef QP_RspQryPriority QP_RspUpdatePriority;

// 用户股票池
typedef struct QP_QuantUserDisablePublicCode
{
	QP_BASEMSG_FIELDS
	int64_t                        nId;
	int                         nGroupId;

	int                      nDisablePublicCodeNum;          //  不可用公用券数量
	char**             pDisablePublicCode;             //  不可用公用券指针
} QP_QuantUserDisablePublicCode;

typedef struct QP_QuantUserCodePool
{
	QP_BASEMSG_FIELDS
	int64_t                        nId;
	int                         nGroupId;

	int                      nCodeControlNum;       //  可用券数量
	QP_QuantUserCodeInfo* pCodeControl;          // （可用券信息）指针偏移
} QP_QuantUserCodePool;

// 券池类
typedef struct QP_QuantUserCodeControl
{
	char*               szWinCode;
	double             nCaptial;                   // 最大可用资金
	int                nLendingAmount;             // 最大可用券
} QP_QuantUserCodeControl;


// 用户信息
typedef struct QP_QuantUserBase
{
	int64_t                        nId;
	char*                   szUserName;                 // 用户名
	char*                   szNickName;                 // 用户别名
	int                       nGroupId;                 // 组ID

	QP_QuantUserType   nUserRole;                       // 用户角色

	double          nStampTax;                   //  印花税
	double          nTransferFees;               //  过户费
	double          nCommissions;                //  佣金
} QP_QuantUserBase;

typedef struct QP_QuantUser
{
	QP_QuantUserBase *pQuantUserBase;

	bool               ifStopTrade;                     // 是否停机
	int               nStopTradePostion;                // 停机位(亏算资金量)
	double     nStopPercentTradePostion;                // 停机位(亏损比例)

	int                nSinglePositionHoldTime;         // 单笔持仓时间阈值
	int                nSinglePositionLoss;             // 单笔持仓亏损阈值(亏算资金量)
	double      nSinglePercentPositionLoss;             // 单笔持仓亏损阈值(亏损比例)

	int                      nCodeControlNum;       //  可用券数量
	QP_QuantUserCodeControl* pCodeControl;          // （可用券信息）指针偏移

	int                      nDisableCodeNum;
	char**             pDisableCode;
} QP_QuantUser;


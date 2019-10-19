#ifndef TRANS_PROTOCOL_H
#define TRANS_PROTOCOL_H
namespace PROTOCOL {
enum REQUEST_TYPE
{
    DEBUG,                  //调试

    USER_LOGIN,             //用户登录请求
    USER_REGIST,            //用户注册请求
    USER_GETQUESTION,       //用户获取密保问题请求
    USER_FINDPWD,           //用户找回密码请求
    USER_GET_RENTCARINFO,   //用户获取可租车辆信息请求
    USER_GET_USERINFO,      //用户请求获取账户信息
    USER_RENTCAR,           //用户租车请求
    USER_CONFIRM_RENTCAR,   //用户确认租车请求
    USER_GET_HISTORYORDER,  //用户请求获取历史订单
    EMPLOYEE_CCL_OR_CFM,    //员工取消订单或确认取车操作

    EMPLOYEE_LOGIN,         //员工登录请求
    EMPLOYEE_GET_ORDER,     //员工获取订单
    EMPLOYEE_BACK_CAR,      //员工确认还车操作
    EMPLOYEE_BROKEN_INFO,	//车辆损坏记录
    EMPLOYEE_RECORD,    	//违章登记

    LOGIN_REPLY,            //服务器登录请求回复
    REGIST_REPLY,           //服务器注册请求回复
    GETQUESTION_REPLY,      //服务器获取密保信息回复
    FINDPWD_REPLY,          //服务器找回密码请求回复
    RENTCARINFO_REPLY,      //服务器可租车辆请求回复
    USERINFO_REPLY,         //用户获取账户信息回复
    RENTCAR_REPLY,          //用户租车请求回复
    CONFIRM_RENTCAR_REPLY,  //确认租车请求回复
    HISTORYORDER_REPLY,     //用户获取历史订单信息回复
    EP_GET_ORDER_REPLY,     //员工获取订单回复
    EP_CCL_OR_CFM_REPLY,    //员工对订单的操作恢复
    EP_BACK_CAR_REPLY,      //员工还车请求回复
    EP_BROKEN_REPLY,        //车辆损坏回复
    EP_RECORD_REPLY         //违章登记回复
};
}


#endif // TRANS_PROTOCOL_H

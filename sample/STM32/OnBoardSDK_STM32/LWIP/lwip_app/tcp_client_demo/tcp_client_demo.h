#ifndef __TCP_CLIENT_DEMO_H
#define __TCP_CLIENT_DEMO_H
#include "sys.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include "lwip/mem.h"
#include "lwip_comm.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//TCP Client 测试代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/8/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//修改信息
//无
////////////////////////////////////////////////////////////////////////////////// 	   
 
#define TCP_CLIENT_RX_BUFSIZE	200		//定义tcp client最大接收数据长度
#define	TCP_CLIENT_PORT			15010	//定义tcp client要连接的远端端口

//tcp服务器连接状态
enum tcp_client_states
{
	ES_TCPCLIENT_NONE = 0,		//没有连接
	ES_TCPCLIENT_INIT,
	ES_TCPCLIENT_CONNECTED,		//连接到服务器了 
	ES_TCPCLIENT_CLOSING,		//关闭连接
}; 
//LWIP回调函数使用的结构体
struct tcp_client_struct
{
	u8 state;               //当前连接状
	struct tcp_pcb *pcb;    //指向当前的pcb
	struct pbuf *p;         //指向接收/或传输的pbuf
};  

typedef struct{
	u8 connect_state; //see tcp_client_states
	u8 recv_state;  //0-数据未接收，1-接收到数据
	struct tcp_pcb *pcb;    //指向当前的pcb
	struct pbuf *send_p;  //指向待发送的pbuf，用户要发送的数据会转换缓存到此buf。 \
												//用户可直接调用函数tcp_client_senddata发送，如果未发送完全成功，在发送回调里也会继续tcp_client_senddata继续发送
	u8 recvbuf[TCP_CLIENT_RX_BUFSIZE];
}tcp_client_handle_s;

void tcp_client_set_remoteip(void);
void tcp_client_test(void);//TCP Client测试函数
err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err);
err_t tcp_client_recv(void *arg,struct tcp_pcb *tpcb,struct pbuf *p,err_t err);
void tcp_client_error(void *arg,err_t err);
err_t tcp_client_poll(void *arg, struct tcp_pcb *tpcb);
err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
//void tcp_client_senddata(struct tcp_pcb *tpcb, struct tcp_client_struct * es);
err_t tcp_client_senddata(struct tcp_pcb *tpcb, void *user_arg);
err_t tcp_client_send(struct tcp_pcb *tpcb, void *user_arg, u8 *sendbuf, u16 buf_len);
void tcp_client_connection_close(struct tcp_pcb *tpcb, struct tcp_client_struct * es );
void tcp_client_test(void);

#endif
























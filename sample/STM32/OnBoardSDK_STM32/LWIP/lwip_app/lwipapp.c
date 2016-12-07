/*
 *	File name   : lwipapp.c
 *  Created on  : 
 *  Author      : yanly
 *  Description :
 *  Version     :
 *  History     : <author>		<time>		<version>		<desc>
 */
 
#include "sys.h" 
#include "lwip_comm.h"
#include "tcp_client_demo.h"
#include "lwipapp.h"
 
//LWIP 应用主流程 //add by yanly
void lwip_process(void)
{
	if((lwipdev.netstatus != NET_INIT_OK)&&(lwipdev.linkstatus == LINK_UP)) //网络没有初始化成功，并且网线有连接
	{
		lwip_comm_init();
		return;
	}
	//zkrt_todo: 网络事件业务处理
	tcp_client_test();
	lwip_periodic_handle(); //固定调用
}

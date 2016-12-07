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
 
//LWIP Ӧ�������� //add by yanly
void lwip_process(void)
{
	if((lwipdev.netstatus != NET_INIT_OK)&&(lwipdev.linkstatus == LINK_UP)) //����û�г�ʼ���ɹ�����������������
	{
		lwip_comm_init();
		return;
	}
	//zkrt_todo: �����¼�ҵ����
	tcp_client_test();
	lwip_periodic_handle(); //�̶�����
}

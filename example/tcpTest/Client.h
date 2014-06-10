/*
 * zsummerX License
 * -----------
 * 
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2010-2014 YaweiZhang <yawei_zhang@foxmail.com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ===============================================================================
 * 
 * (end of COPYRIGHT)
 */


//! zsummer�Ĳ��Է���ģ��(��Ӧzsummer�ײ������װ���ϲ���Ʋ��Է���) ����Ϊ����˼ܹ��е� gateway����/agent����/ǰ�˷���, �ص��Ǹ߲�����������
//! Socket Clientͷ�ļ�

#ifndef ZSUMMER_CLIENT_H_
#define ZSUMMER_CLIENT_H_
#include "header.h"
#include "Process.h"

//! �ϲ�Socekt Client�Ķ��η�װ
class CClient : public std::enable_shared_from_this<CClient>
{
public:
	CClient(CProcess &proc, CTcpSocketPtr sockptr);
	~CClient();
	void Initialize();
private:
	void OnConnected(zsummer::network::ErrorCode ec);

	void DoRecv();
	void OnRecv(zsummer::network::ErrorCode ec, int nRecvedLen);
	void MessageEntry(zsummer::protocol4z::ReadStream<zsummer::protocol4z::DefaultStreamHeadTraits> & rs);



	void SendOnce();
	void DoSend(unsigned short protocolID, unsigned long long clientTick, const char* text);
	void DoSend(char *buf, unsigned short len);
	void OnSend(zsummer::network::ErrorCode ec,  int nSentLen);

	
	void OnClose();

	CProcess  & m_process;
	CTcpSocketPtr  m_sockptr;
	bool m_bEstablished = false;
	
	//! ����
	Packet m_recving;
	std::string m_recvTextCache;

	//! д������
	std::queue<Packet *> m_sendque;

	//! ��ǰд��

	char m_sendBuff[_SEND_BUF_LEN];
	unsigned short m_sendLen = 0;
	unsigned short m_curSendLen = 0;

	unsigned long long m_lastDelayTime = 0; //���һ���յ�echo��Ϣ���ӳ�ʱ��
};

#endif


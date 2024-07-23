#pragma once
class CServerSocket
{
public:
	static CServerSocket* getInstance();
	static void releaseInstance();
	BOOL InitSockEnv();
	BOOL InitSocket();
	BOOL AcceptClient();
	int DealCommand();
	void CloseClient();

private:
	CServerSocket();
	~CServerSocket();
	CServerSocket(const CServerSocket&) = delete;
	CServerSocket(CServerSocket&&) = delete;
	CServerSocket& operator=(const CServerSocket&) = delete;
	CServerSocket& operator=(CServerSocket&&) = delete;

private:
	class CHelper {
	public:
		CHelper() { CServerSocket::getInstance(); }
		~CHelper() { CServerSocket::releaseInstance(); }
	};

private:
	static CServerSocket* m_instance;
	static CHelper m_helper;

	SOCKET m_client;
	SOCKET m_sock;
};


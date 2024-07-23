#pragma once

// 字节对其长度为1
#pragma pack(push)
#pragma pack(1)
class CPacket
{
public:
	CPacket();
	CPacket(WORD nCmd, const BYTE* pData, size_t nSize);
	CPacket(const CPacket& pack);
	CPacket(const BYTE* pData, size_t& nSize);
	~CPacket() {}
	CPacket& operator=(const CPacket& pack);

	int Size() { return nLength + 6; } // 包的大小
	const char* Data();

public:
	WORD sHead;			//固定位 0xFEFF
	DWORD nLength;		//包长度（从控制命令开始，到和校验结束）
	WORD sCmd;			//控制命令
	std::string strData;//包数据
	WORD sSum;			//和校验
	std::string strOut;	//整个包的数据
};
#pragma pack(pop)

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
	CPacket m_packet;
};


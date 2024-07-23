#pragma once

// �ֽڶ��䳤��Ϊ1
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

	int Size() { return nLength + 6; } // ���Ĵ�С
	const char* Data();

public:
	WORD sHead;			//�̶�λ 0xFEFF
	DWORD nLength;		//�����ȣ��ӿ������ʼ������У�������
	WORD sCmd;			//��������
	std::string strData;//������
	WORD sSum;			//��У��
	std::string strOut;	//������������
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


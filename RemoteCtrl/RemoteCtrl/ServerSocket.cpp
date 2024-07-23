#include "pch.h"
#include "ServerSocket.h"

#define BUFFER_SIZE 4096

CServerSocket* CServerSocket::m_instance = NULL;
CServerSocket::CHelper CServerSocket::m_helper;

CServerSocket* CServerSocket::getInstance()
{
    if (m_instance == NULL)
    {
        m_instance = new CServerSocket();
    }
    return m_instance;
}

void CServerSocket::releaseInstance()
{
    if (m_instance != NULL)
    {
        CServerSocket* tmp = m_instance;
        m_instance = NULL;
        delete tmp;
    }
}

BOOL CServerSocket::InitSockEnv()
{
    WSADATA data;
    if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CServerSocket::InitSocket()
{
    if (m_sock == -1)
    {
        return FALSE;
    }

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.S_un.S_addr = INADDR_ANY;
    servAddr.sin_port = htons(9100);

    if (bind(m_sock, (sockaddr*) & servAddr, sizeof(servAddr)) == -1)
    {
        return FALSE;
    }

    if (listen(m_sock, 1) == -1)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CServerSocket::AcceptClient()
{
    TRACE("enter AcceptClient\r\n");

    sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    int clientLen = sizeof(clientAddr);
    m_client = accept(m_sock, (sockaddr*)&clientAddr, &clientLen);
    TRACE("m_client = %d\r\n", m_client);

    if (m_client == -1)
    {
        return FALSE;
    }

    return TRUE;
}

int CServerSocket::DealCommand()
{
}

void CServerSocket::CloseClient()
{
    closesocket(m_client);
    m_client = INVALID_SOCKET;
}

CServerSocket::CServerSocket()
{
    m_client = INVALID_SOCKET;
    if (InitSockEnv() == FALSE) 
    {
        MessageBox(NULL, _T("无法初始化套接字环境,请检查网络设置！"), _T("初始化错误！"), MB_OK | MB_ICONERROR);
        exit(0);
    }
    m_sock = socket(PF_INET, SOCK_STREAM, 0);
}

CServerSocket::~CServerSocket()
{
    closesocket(m_sock);
    WSACleanup();
}

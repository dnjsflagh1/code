#include "CUpdateVersion.h"

CUpdateVersion::CUpdateVersion()
{
	m_socket = NULL;
	m_inProcess = false;
}

CUpdateVersion::CUpdateVersion(const wxString &host, unsigned int port)
{
	m_socket = new wxSocketClient();
	m_addr.Hostname(host);
	m_addr.Service(port);
	m_socket->SetLocal(m_addr);
	m_inProcess = false;
}

CUpdateVersion::CUpdateVersion(wxSocketClient *socket)
{
	m_socket = socket;
	m_inProcess = false;
}

CUpdateVersion::~CUpdateVersion()
{
	if (m_socket)
		m_socket->Close();
	delete m_socket;
}

wxArrayString CUpdateVersion::GetUpdateGameHost()
{
	wxArrayString result;
	return result;
}

bool CUpdateVersion::NeedUpdateVersion(const wxString &currentVersion)
{
	return false;
}

bool CUpdateVersion::CanConnect()
{
	if (m_socket)
	{	
		m_socket->Connect(m_addr, false);
		m_socket->WaitOnConnect(10);		// 10s wait for response;
		if (m_socket->IsConnected())
			return true;
		m_socket->Close();
	}
	return false;
}

void CUpdateVersion::test1()
{
	// 置位系统忙
	m_inProcess = true;

	// 定义消息
	unsigned char len = 0;
	const wxChar *msg = _T("测试连接...\n");
	wxChar *msgBack = new wxChar[wxStrlen(msg)+1];
	m_msgType = (unsigned char)ENM_TEST_1;

	// 发送&接收消息
	m_socket->Write(&m_msgType, 1);
	m_socket->SetFlags(wxSOCKET_WAITALL);							// 设置状态位等待所有回应
	len = (unsigned char)((wxStrlen(msg)+1) * sizeof(wxChar));		// 计算消息发送字节长度。
	m_socket->Write(&len, 1);
	m_socket->Write(msg, len);

	m_socket->Read(msgBack, len);	

	// 结束
	delete[] msgBack;	
	m_inProcess = false;
}

void CUpdateVersion::SetAddr(const wxString &host, unsigned int port)
{	
	m_addr.Hostname(host);
	m_addr.Service(port);	
	m_socket->SetLocal(m_addr);
}

void CUpdateVersion::SetSocket(wxSocketClient *socket)
{
	if (m_socket)
	{
		m_socket->Close();
		delete m_socket;
		m_socket = NULL;
	}
	m_socket = socket;
}
#include "update.h"
// net
#include <wx/protocol/http.h>
#include <wx/protocol/ftp.h>
#include <wx/url.h>
// file
#include <wx/xml/xml.h>
#include <wx/thread.h>
#include <wx/stream.h>
#include <wx/sstream.h>
#include <wx/wfstream.h>
#include <wx/fileconf.h>
#include <wx/tokenzr.h>
// system
#include "systemInfo.h"

CUpdate::CUpdate()
{
	// TODO ��ʼ�����ݳ�Ա���Լ������ļ�
}

void CUpdate::initFromCfg()
{
	loadConfig(_("SYSTEM/versionUrl"), &m_cfgVersionURL);		
	loadConfig(_("SYSTEM/coreURL"), &m_cfgCoreFileURL);
	loadConfig(_("SYSTEM/gameVerion"), &m_showVersion);
	wxString temp;
	loadConfig(_("SYSTEM/version"), &temp);
	temp.ToLong(&m_localVersion);
}

///////////////////////////////////////////////////////////////////////////////////////// ��������
// ���ֲ���
void CUpdate::playMusic(const wxString fileName)
{
	if (m_sound.IsOk() == false)
	{
		//��ʽ���ַ�ΪUTF��ʽ������wxString�ַ������� 
		wxString soundString(m_skinDir + m_soundFile, wxConvUTF8); 
		//����wxSound���� 	 
		m_sound.Create(soundString,false); 	
		m_sound.Play(true);	
	}
}

// ��ȡԶ���ļ�
bool CUpdate::getUrlFile(const wxString &url, unsigned char urlType, const wxString dir, wxString saveName)
{
	// �����ļ���
	wxString fileName = url.substr(url.Last('/')+1);	// ���û��ָ���ļ�������ʹ�����ӵ�ַ�ļ���
	if (saveName.IsEmpty())
		saveName = fileName;
	bool res = true;
	// access save file.
	if (urlType == EUT_HTTP)
	{			
		wxURL *purl = new wxURL(url);		
		wxInputStream *in = purl->GetInputStream();		
		if (!in)
		{
			wxLogError("Couldn't get the file:%s",fileName);			
		}
		else
		{
			res &= SaveFile(in, saveName, dir);
			delete in;
		}
		in = NULL;
		delete purl;
	}
	else if (urlType == EUT_FTP)
	{
		wxFTP ftp;
		// access ftp hostName
		wxString tempFtpAddr = url.substr(0, url.Index('/'));
		// access ftp Dir
		wxString fileDir = url.substr(tempFtpAddr.Len(), url.Len()-tempFtpAddr.Len()-fileName.Len());		
		//ftp.SetUser(_("Anonymous"));	//��������
		ftp.SetUser(_("guest"));
		//ftp.SetPassword(wxEmptyString);
		if ( !ftp.Connect(tempFtpAddr))
		{
			wxLogError("Lost connect,The url is %s and filename is %s.",tempFtpAddr, fileName);
		}
		else
		{
			ftp.ChDir(fileDir);
			// �ļ�����С�ж�
			int size = ftp.GetFileSize(fileName);
			if ( size == -1 )
			{
				wxLogError("Couldn't get the file size for \"%s\"", fileName);
			}
			else
			{
				// �ļ����ж�
				wxInputStream *in = ftp.GetInputStream(fileName);
				if ( !in )
				{
					wxLogError("Couldn't get the file:%s",fileName);				
				}
				else
				{
					// �����ļ�
					res &= SaveFile(in, saveName, dir, size);
					delete in;
				}
				in = NULL;
			}
		}
		// gracefully close the connection to the server
		ftp.Close();
	}
	else if (urlType == EUT_HTTPS)
	{
		//TODO: ʵ��HTTPS,��������ļ�������ļ�
	}
	// ����ɹ��Ҵ������������㣬������������(�е������ж�)
	if (res && m_mainAmountValue>0)
	{
		m_mainAmountValue++;
	}
	return res;
}

// �����ļ���д	
bool CUpdate::setConfig(const wxString& key, const wxString& values, wxString fileName)
{
	if(fileName.IsEmpty())
	{
		fileName = m_configFile;
	}
	wxString	realFileName = m_skinDir +fileName;
	wxFileInputStream fis(realFileName);
	if (!fis.Ok())
	{
		assert("Config file not found.");
		return false;
	}
	wxFileConfig *conf = new wxFileConfig(fis);
	bool result = conf->Write(key, values);
	wxFileOutputStream os(realFileName);
	conf->Save(os);
	os.Close();	
	delete conf;
	return result;
}

bool CUpdate::loadConfig(const wxString& key, wxString* values, wxString fileName)
{
	if(fileName.IsEmpty())
	{
		fileName = m_configFile;
	}
	wxString	realFileName = m_skinDir +fileName;
	wxFileInputStream fis(realFileName);
	if (!fis.Ok())
	{
		assert("Config file not found.");
		return false;
	}
	wxFileConfig *conf = new wxFileConfig(fis);
	bool result = conf->Read(key, values);
	delete conf;
	return result;
}

// �ļ�����
bool CUpdate::SaveFile(wxInputStream *in, const wxString& fileName, const wxString dir, size_t size)
{
	m_subPercentage = 0;
	if (size == 0)
		size = in->GetSize();
	if (size>0)
	{
		char *data = new char[size];		
		if ( !in->Read(data, size) )
		{
			wxLogError("Read input stream failure!");
			return false;
		}
		else
		{
			// file data is in the buffer
			size_t i;
			wxString saveName = fileName;
			if (dir.IsEmpty() == false)
			{
				saveName = m_skinDir+"\\"+ dir+"\\" + fileName;
			}
			wxFileOutputStream out(saveName);

			/*ofstream out(saveName, ios::out|ios::binary);*/
			if(!out) 
			{				
				wxMessageBox("������Ϸ��Դ�ļ�����ʧ�ܡ�","�汾����");
				return false;
			}
			else
			{									
				for(i=0; i<size; i++) 
				{						
					/*out.put(data[i]);*/
					out.PutC(data[i]);
					// ����ٷֱ�
					int mark = (i*100)/size;
					if (mark>0)
					{
						if (mark == 100)
						{
							m_subPercentage = 0;
							continue;
						}
						m_subPercentage = mark;					
					}					
				}
			}
			/*out.flush();*/
			/*out.close();*/
			out.Sync();
			out.Close();
		}

		delete [] data;		
	}
	return true;
}

// �ͻ����Ƿ�������
bool CUpdate::IsClientRun()
{
	HWND hwnd = ::FindWindow(NULL,"ɽ��־ ONLINE");
	if(hwnd)
	{
		wxMessageBox(_("ɽ��־�ͻ����Ѿ������������ȹرտͻ��ˡ�"),_("ϵͳ��ʾ"));
		// ::SendMessage(hwnd, WM_CLOSE, NULL,NULL);												// û��Ҫǿ�ƹرտͻ���
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////// �汾���º���
// ���¼�⺯��
bool CUpdate::needUpdate(int remoteVersion)
{
	wxString values;
	bool res = loadConfig( _("SYSTEM/version"), &values);
	long lastVersion = 0;
	values.ToLong(&lastVersion);
	if(lastVersion < remoteVersion)
	{
		// ��Ҫ���£�����¼��Ҫ���µİ汾�ţ��Ա��д�����ļ���
		m_updateVersion = remoteVersion;
		return true;
	}
	return false;
}

// ��ȡ�ļ��汾
wxString CUpdate::getFileVersion(const wxString &fileName)
{
	wxString result;
	if (wxFile::Exists(fileName))
	{
		SystemInfo::GetFileVersionOfGame(fileName, &result);
		return result;
	}
	return wxEmptyString;
}

// ���̰߳汾����
void CUpdate::threadUpdate()
{
	m_thread = new MyThread(this);
	if (m_thread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError("Can't create the thread!");
		delete m_thread;
		m_thread = NULL;
	}
	else
	{
		if (m_thread->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError("Can't create the thread!");
			delete m_thread;
			m_thread = NULL;
		}
		else
		{
		}
	}
}

// ��ȡԶ�̰汾�ļ�
wxInputStream *CUpdate::getRemoteVersionFile(const wxString urlStr)
{
	wxURL url;
	wxInputStream *stream = NULL;
	if (m_cfgVersionURL.Index(";") != -1)
	{
		wxStringTokenizer tkz(m_cfgVersionURL, wxT(";"));
		while ( tkz.HasMoreTokens() )
		{
			wxString token = tkz.GetNextToken();
			if (token.EndsWith(_(".xml")) == false)
				token += _("/updateVersion.xml");
			// process token here
			url.SetURL(token);
			if (url.GetError() == wxURL_NOERR)
			{
				stream = url.GetInputStream();
				if (stream)
					return stream;
			}
		}
	}
	else
	{
		if (m_cfgVersionURL.IsEmpty() == false || urlStr.IsEmpty() == false)
		{
			// ���������ļ�
			url.SetURL(urlStr);
			if (urlStr.IsEmpty() == false && url.GetError() == wxURL_NOERR)
			{				
				stream = url.GetInputStream();
				if (stream)
					return stream;
			}
			else	// �����ļ�����
			{
				url.SetURL(m_cfgVersionURL);
				if (m_cfgVersionURL.EndsWith(_(".xml")) == false)
					m_cfgVersionURL += _("/updateVersion.xml");
				url.SetURL(m_cfgVersionURL);
				if (url.GetError() == wxURL_NOERR)
				{
					stream = url.GetInputStream();
					if (stream)
						return stream;
				}
			}
				
		}
	}
	// TODO: ����һ��Ĭ�ϰ汾����������Ĭ�ϰ汾��������ȡ�汾�ļ�
	return NULL;
}

// ��ʼ�����Ȱٷֱ�
bool CUpdate::InitMainGauge()
{
	wxInputStream *inputStream = getRemoteVersionFile();
	if (!inputStream)
		return false;
	wxXmlDocument doc;
	if (doc.Load(*inputStream) == false)
	{
		delete inputStream;
		return false;
	}
	wxXmlNode *root = doc.GetRoot();
	wxXmlNode *subRoot;
	if (root)
		root = root->GetChildren();
	wxString name,gameVersion, gameName;
	long remoteVersion = 0;

	// ��ʼ����
	while (root)
	{
		name = root->GetName();
		if (name.IsSameAs(_("comment")))
		{
			root = root->GetNext();
			continue;
		}
		gameName = root->GetPropVal(_("name"),wxEmptyString);
		if (root->GetName() == _("game") && gameName.IsSameAs(_("SHZ")))
		{
			gameVersion = root->GetPropVal(_("version"), _(""));									// ��ȡ�ø����б��Ӧ����Ϸ�汾			
			gameVersion.ToLong(&remoteVersion);
			if (needUpdate(remoteVersion) == false)
			{
				root = root->GetNext();
				continue;
			}
			subRoot = root->GetChildren();
			while (subRoot)
			{
				// �ж��Ƿ���ע�ͻ��ߴ���Ŀ¼
				name = subRoot->GetName();
				if (name.IsSameAs(_("comment")) || name.IsSameAs(_("dir")))
				{
					subRoot = subRoot->GetNext();
					continue;
				}								
				m_mainAmountValue++;
				subRoot = subRoot->GetNext();
			}			
		}
		root = root->GetNext();
	}
	delete inputStream;
	m_updateVersion = remoteVersion;	// ��ȡ���������°汾	
	return true;
}

// �汾���º��ĺ���
void CUpdate::doUpdateVersion()
{
	if (m_updateState == (unsigned char)EUS_UPDATE_FINISHED && m_newestVersion)
		return;
	// �ȳ�ʼ�������ļ��汾
	if (InitMainGauge() == false)
	{
		wxMessageBox(_T("�汾����������ʧ�ܣ�����ϵ�ͷ�"), _T("ϵͳ��ʾ"),wxOK);
		return;
	}
	bool processSuccess = true;

	// ��ȡ���·�������ַ
	if (true)
	{			
		wxInputStream *inputStream = getRemoteVersionFile();
		if (!inputStream)
		{
			wxMessageBox(_T("�汾����������ʧ�ܣ�����ϵ�ͷ�"), _T("ϵͳ��ʾ"),wxOK);
			return;
		}
		wxXmlDocument doc;	// XML�汾�ļ�		
		if (doc.Load(*inputStream) == false)
		{			
			wxMessageBox(_T("�汾�ļ�����ʧ�ܣ����Ժ����Ի���ϵ�ͷ�"), _T("ϵͳ��ʾ"),wxOK);
			return;		
		}

		// �ļ�����
		wxXmlNode *root = doc.GetRoot();		
		wxXmlNode *baseRoot = NULL;					// ������ڵ�
		wxXmlNode *subRoot = NULL;						// �ļ��ڵ�
		wxString gameName;								// ��Ϸ����		
		baseRoot = root->GetChildren();
		root = root->GetChildren();
		m_updateState = EUS_UPDATE;	

		// ��Ϸ�汾�ڵ�
		while(root)
		{			
			// �ж�Game�ڵ����Ϸ�����Ƿ���ɽ��־
			root->GetAttribute(_("name"), &gameName);			
			if (root->GetName() == _("game") && gameName.IsSameAs(_("SHZ")))
			{
				// �жϵ�ǰ����Ϸ�汾���Ƿ���Ҫ���£� 
				wxString fileName, fileVersion, fileUrl, updateType, fileLocal, realVersion;				
				realVersion = root->GetPropVal(_("version"), _(""));							// ��ȡ�ø����б��Ӧ����Ϸ�汾
				m_showVersion = root->GetPropVal(_("gameVersion"), m_showVersion);				// ��ȡԶ�̷������汾��
				long remoteVersion;
				realVersion.ToLong(&remoteVersion);						
				if (needUpdate(remoteVersion) == false)
				{
					root = root->GetNext();
					continue;
				}

				// ��Ϸ�汾���£���ȡGame�ڵ���ӽڵ������ļ�����
				subRoot = root->GetChildren();				
				while (subRoot)
				{
					updateType = subRoot->GetName();
					// �жϽڵ����ͣ�����[file/dir/zip/dat]������ע�ͣ������ע�ͣ���������һ�֡�
					// TODO: ��zip�ļ��Զ���ѹ
					if (updateType.IsSameAs(_("comment")))
					{
						subRoot = subRoot->GetNext();
						continue;
					}
					// �ļ���Ϣ��ȡ
					fileLocal = subRoot->GetPropVal(_("local"), wxEmptyString).Trim();								// ���ش��·��
					fileName = subRoot->GetPropVal(_("name"), wxEmptyString).Trim();								// �ļ�����
					fileVersion = subRoot->GetPropVal(_("version"),wxEmptyString).Trim();							// �ļ��汾
					fileUrl = subRoot->GetPropVal(_("url"),wxEmptyString).Trim();									// �ļ�����������λ��

					// �������ӵ�ַ����
					unsigned char urlType = EUT_NONE;
					if (fileUrl.IsEmpty() == false)
					{							
						if (fileUrl.StartsWith(_("ftp://")))
						{
							urlType = EUT_FTP;
							fileUrl = fileUrl.substr(6);
						}
						else if(fileUrl.StartsWith(_("http://"))) 
						{
							urlType = EUT_HTTP;
						}
						else if (fileUrl.StartsWith(_("https://")))
						{
							urlType = EUT_HTTPS;
						}
						else
						{
							assert("Invalid url for update...");
						}
					}

					// ����Ŀ¼
					if (updateType.IsSameAs(_("dir")))
					{
						// �����ļ��У�
						wxString dir = m_skinDir + "\\" + fileName;
						if (!::wxDirExists(dir))
						{
							::wxMkDir(dir);
						}
					}
					// �ļ�����
					else if (updateType.IsSameAs(_("exe")) || updateType.IsSameAs(_("dll")))
					{
						// �ļ�����
						if (getFileVersion(fileName).IsSameAs(fileVersion.c_str()) == false || fileVersion.IsEmpty())
						{
							processSuccess &= getUrlFile(fileUrl, urlType, fileLocal, fileName);
						}
					}
					// rar��dat ���������ļ����������¸���
					else
					{
						if (fileUrl.IsEmpty()==false && urlType != EUT_NONE)
							processSuccess &= getUrlFile(fileUrl, urlType, fileLocal, fileName);
					}
					wxThread::Sleep(1);
					// һ�������ӿ鴦����ɣ�������һ��
					subRoot = subRoot->GetNext();
				}
			}
			// ����ɽ��־��Ϸ�Ľڵ�ģ�飬�������Ǹ�ģ�鴦������		
			root = root->GetNext();
		}
		// delete inputStream;
	}

	// �汾�������
	m_updateState = EUS_UPDATE_FINISHED;		
	if (m_updateVersion > 0 && processSuccess == true)
	{// �汾��ȫ���³ɹ�
		wxMessageBox(_T("��Ϸ�汾���³ɹ����"),_T("�汾����"));
		setConfig(_("SYSTEM/version"), wxString::Format(wxT("%i"),m_updateVersion));
		setConfig(_("SYSTEM/gameVersion"), m_showVersion);
	}
}


////////////////////////////////////////////////////////////////////////// MyThread implementation.
MyThread::MyThread(CUpdate *app) : wxThread()
{
	m_count = 0;
	m_app = app;
}

void *MyThread::Entry()
{
	m_app->doUpdateVersion();
	return m_app;
}

void MyThread::OnExit()
{
	m_count = 0;
}

void MyThread::DoUpdate()
{

}

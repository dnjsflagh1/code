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
	// TODO 初始化数据成员，以及配置文件
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

///////////////////////////////////////////////////////////////////////////////////////// 辅助函数
// 音乐播放
void CUpdate::playMusic(const wxString fileName)
{
	if (m_sound.IsOk() == false)
	{
		//格式化字符为UTF格式并创建wxString字符串对象 
		wxString soundString(m_skinDir + m_soundFile, wxConvUTF8); 
		//创建wxSound对象 	 
		m_sound.Create(soundString,false); 	
		m_sound.Play(true);	
	}
}

// 获取远程文件
bool CUpdate::getUrlFile(const wxString &url, unsigned char urlType, const wxString dir, wxString saveName)
{
	// 处理文件名
	wxString fileName = url.substr(url.Last('/')+1);	// 如果没有指定文件名，则使用链接地址文件名
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
		//ftp.SetUser(_("Anonymous"));	//匿名访问
		ftp.SetUser(_("guest"));
		//ftp.SetPassword(wxEmptyString);
		if ( !ftp.Connect(tempFtpAddr))
		{
			wxLogError("Lost connect,The url is %s and filename is %s.",tempFtpAddr, fileName);
		}
		else
		{
			ftp.ChDir(fileDir);
			// 文件包大小判断
			int size = ftp.GetFileSize(fileName);
			if ( size == -1 )
			{
				wxLogError("Couldn't get the file size for \"%s\"", fileName);
			}
			else
			{
				// 文件流判断
				wxInputStream *in = ftp.GetInputStream(fileName);
				if ( !in )
				{
					wxLogError("Couldn't get the file:%s",fileName);				
				}
				else
				{
					// 保存文件
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
		//TODO: 实现HTTPS,传输机密文件或核心文件
	}
	// 传输成功且传输总数大于零，避免零作除数(有点冗余判断)
	if (res && m_mainAmountValue>0)
	{
		m_mainAmountValue++;
	}
	return res;
}

// 配置文件读写	
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

// 文件保存
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
				wxMessageBox("部分游戏资源文件更新失败。","版本更新");
				return false;
			}
			else
			{									
				for(i=0; i<size; i++) 
				{						
					/*out.put(data[i]);*/
					out.PutC(data[i]);
					// 计算百分比
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

// 客户端是否在运行
bool CUpdate::IsClientRun()
{
	HWND hwnd = ::FindWindow(NULL,"山海志 ONLINE");
	if(hwnd)
	{
		wxMessageBox(_("山海志客户端已经开启，请您先关闭客户端。"),_("系统提示"));
		// ::SendMessage(hwnd, WM_CLOSE, NULL,NULL);												// 没必要强制关闭客户端
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////// 版本更新函数
// 更新检测函数
bool CUpdate::needUpdate(int remoteVersion)
{
	wxString values;
	bool res = loadConfig( _("SYSTEM/version"), &values);
	long lastVersion = 0;
	values.ToLong(&lastVersion);
	if(lastVersion < remoteVersion)
	{
		// 需要更新，并记录需要更新的版本号，以便回写配置文件。
		m_updateVersion = remoteVersion;
		return true;
	}
	return false;
}

// 获取文件版本
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

// 多线程版本更新
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

// 获取远程版本文件
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
			// 先用配置文件
			url.SetURL(urlStr);
			if (urlStr.IsEmpty() == false && url.GetError() == wxURL_NOERR)
			{				
				stream = url.GetInputStream();
				if (stream)
					return stream;
			}
			else	// 配置文件加载
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
	// TODO: 给予一个默认版本服务器，从默认版本服务器获取版本文件
	return NULL;
}

// 初始化进度百分比
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

	// 开始处理
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
			gameVersion = root->GetPropVal(_("version"), _(""));									// 获取该更新列表对应的游戏版本			
			gameVersion.ToLong(&remoteVersion);
			if (needUpdate(remoteVersion) == false)
			{
				root = root->GetNext();
				continue;
			}
			subRoot = root->GetChildren();
			while (subRoot)
			{
				// 判断是否是注释或者创建目录
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
	m_updateVersion = remoteVersion;	// 获取服务器最新版本	
	return true;
}

// 版本更新核心函数
void CUpdate::doUpdateVersion()
{
	if (m_updateState == (unsigned char)EUS_UPDATE_FINISHED && m_newestVersion)
		return;
	// 先初始化本地文件版本
	if (InitMainGauge() == false)
	{
		wxMessageBox(_T("版本服务器连接失败，请联系客服"), _T("系统提示"),wxOK);
		return;
	}
	bool processSuccess = true;

	// 获取更新服务器地址
	if (true)
	{			
		wxInputStream *inputStream = getRemoteVersionFile();
		if (!inputStream)
		{
			wxMessageBox(_T("版本服务器连接失败，请联系客服"), _T("系统提示"),wxOK);
			return;
		}
		wxXmlDocument doc;	// XML版本文件		
		if (doc.Load(*inputStream) == false)
		{			
			wxMessageBox(_T("版本文件解析失败，请稍后重试或联系客服"), _T("系统提示"),wxOK);
			return;		
		}

		// 文件更新
		wxXmlNode *root = doc.GetRoot();		
		wxXmlNode *baseRoot = NULL;					// 保存根节点
		wxXmlNode *subRoot = NULL;						// 文件节点
		wxString gameName;								// 游戏名称		
		baseRoot = root->GetChildren();
		root = root->GetChildren();
		m_updateState = EUS_UPDATE;	

		// 游戏版本节点
		while(root)
		{			
			// 判断Game节点的游戏名称是否是山海志
			root->GetAttribute(_("name"), &gameName);			
			if (root->GetName() == _("game") && gameName.IsSameAs(_("SHZ")))
			{
				// 判断当前的游戏版本，是否需要更新： 
				wxString fileName, fileVersion, fileUrl, updateType, fileLocal, realVersion;				
				realVersion = root->GetPropVal(_("version"), _(""));							// 获取该更新列表对应的游戏版本
				m_showVersion = root->GetPropVal(_("gameVersion"), m_showVersion);				// 获取远程服务器版本号
				long remoteVersion;
				realVersion.ToLong(&remoteVersion);						
				if (needUpdate(remoteVersion) == false)
				{
					root = root->GetNext();
					continue;
				}

				// 游戏版本更新，获取Game节点的子节点所有文件属性
				subRoot = root->GetChildren();				
				while (subRoot)
				{
					updateType = subRoot->GetName();
					// 判断节点类型，包括[file/dir/zip/dat]，还有注释，如果是注释，则跳到下一轮。
					// TODO: 将zip文件自动解压
					if (updateType.IsSameAs(_("comment")))
					{
						subRoot = subRoot->GetNext();
						continue;
					}
					// 文件信息获取
					fileLocal = subRoot->GetPropVal(_("local"), wxEmptyString).Trim();								// 本地存放路径
					fileName = subRoot->GetPropVal(_("name"), wxEmptyString).Trim();								// 文件名称
					fileVersion = subRoot->GetPropVal(_("version"),wxEmptyString).Trim();							// 文件版本
					fileUrl = subRoot->GetPropVal(_("url"),wxEmptyString).Trim();									// 文件服务器下载位置

					// 下载链接地址处理
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

					// 创建目录
					if (updateType.IsSameAs(_("dir")))
					{
						// 创建文件夹：
						wxString dir = m_skinDir + "\\" + fileName;
						if (!::wxDirExists(dir))
						{
							::wxMkDir(dir);
						}
					}
					// 文件更新
					else if (updateType.IsSameAs(_("exe")) || updateType.IsSameAs(_("dll")))
					{
						// 文件更新
						if (getFileVersion(fileName).IsSameAs(fileVersion.c_str()) == false || fileVersion.IsEmpty())
						{
							processSuccess &= getUrlFile(fileUrl, urlType, fileLocal, fileName);
						}
					}
					// rar、dat 或者其它文件，立即更新覆盖
					else
					{
						if (fileUrl.IsEmpty()==false && urlType != EUT_NONE)
							processSuccess &= getUrlFile(fileUrl, urlType, fileLocal, fileName);
					}
					wxThread::Sleep(1);
					// 一个更新子块处理完成，处理下一个
					subRoot = subRoot->GetNext();
				}
			}
			// 不是山海志游戏的节点模块，或者是那个模块处理完了		
			root = root->GetNext();
		}
		// delete inputStream;
	}

	// 版本更新完成
	m_updateState = EUS_UPDATE_FINISHED;		
	if (m_updateVersion > 0 && processSuccess == true)
	{// 版本完全更新成功
		wxMessageBox(_T("游戏版本更新成功完成"),_T("版本更新"));
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

/***************************************************
** Copyright (C) 2006-2012 ORSHSOFT
** This file is part of the "Game Launcher".
** All rights reserved
** FilePath e:\Launcher\Core\source\systemInfo.cpp
** ���ܣ�ʵ���Զ�������ظ�������
****************************************************/
#ifndef _AUTOUPDATE_UPDATE_H_
#define _AUTOUPDATE_UPDATE_H_

#ifdef LAUNCHER_APP
#define DllExport   __declspec(dllimport)
#else
#define DllExport   __declspec(dllexport)
#endif

#include <wx/wx.h>
#include <wx/sound.h>

// predefine
class wxArrayString;
class CUpdate;
class wxThread;
class wxURL;



// ���߳���
class MyThread : public wxThread
{
public:
	MyThread(CUpdate *app);
	virtual void *Entry();
	virtual void OnExit();
	void DoUpdate();

public:
	unsigned int m_count;
	CUpdate *m_app;
};

// Զ���ļ�����
enum EURLType
{
	EUT_NONE,
	EUT_HTTP,
	EUT_FTP,
	EUT_HTTPS,
};

// ����״̬
enum EUPDATE_STATE
{
	EUS_INITIAL,
	EUS_UPDATE,
	EUS_UPDATE_FINISHED,
};

// �汾������
class DllExport CUpdate
{
public:
	CUpdate();
	inline void setMainPath(wxString mainPath){ m_skinDir = mainPath; }
	void initFromCfg();
	///////////////////////////////////////////////////////////////////////////////////////// ����ת��
	std::string static ToString(wxString wxStr){ return std::string(wxStr.mb_str()); }
	wxString static ToWString(std::string str){ return  wxString( str.c_str(), wxConvUTF8);}

	void playMusicStr(const std::string fileName){ playMusic(ToWString(fileName)); }
	std::string getFileVersionStr(const std::string &fileName){ return ToString(getFileVersion(ToWString(fileName))); }

	///////////////////////////////////////////////////////////////////////////////////////// ��������
	// ���ֲ���
	void playMusic(const wxString fileName);
	// �����ļ���д	
	bool setConfig(const wxString& key, const wxString& values, wxString fileName = wxEmptyString);
	bool loadConfig(const wxString& key, wxString* values, wxString fileName = wxEmptyString);
	// ���ͻ����Ƿ�����
	bool IsClientRun();

	///////////////////////////////////////////////////////////////////////////////////////// �汾���º���
	// ���¼�⺯��
	bool needUpdate(int remoteVersion);
	// ��ȡ�ļ��汾
	wxString getFileVersion(const wxString &fileName);
	// ���̰߳汾����
	void threadUpdate();

	///////////////////////////////////////////////////////////////////////////////////////// ���½���
	// ��ȡ�ļ��ӽ���
	inline int getSubPercentage(){ return m_subPercentage; }
	// ��ȡ�������
	inline int getMainPercentage(){ return m_mainPercentage; }
	// ��ȡ��Ҫ�����ļ�����
	inline int getNeedUpdateFileAmount(){ return m_mainAmountValue; }

protected:
	// ��ʼ�������Լ��ٷֱ�
	bool InitMainGauge();
	// ��ȡԶ���ļ�
	bool getUrlFile(const wxString &url, unsigned char urlType = 0, const wxString dir = "", wxString saveName = "");
	// �ļ�����
	bool SaveFile(wxInputStream *in, const wxString& fileName, const wxString dir, size_t size = 0);
	// ��ȡԶ�̰汾�ļ�
	wxInputStream *getRemoteVersionFile(const wxString url = wxEmptyString);
	// �汾���º��ĺ���
	void doUpdateVersion();
	friend class MyThread;

private:
	wxSound m_sound;					// ��������
	wxString m_soundFile;			// ���������ļ�
	wxString m_skinDir;				// ������Ŀ¼
	wxString m_configFile;			// �����ļ�·��
	wxString m_cfgVersionURL;		// ���õİ汾��������ַ
	wxString m_cfgCoreFileURL;		// ���õĺ����ļ���ַ
	// ����
	int m_mainAmountValue;			// ��Ҫ���µ����ļ�����
	int m_mainPercentage;			// ���ļ�����������Ȱٷֱ�
	int m_subPercentage;				// ��ǰ�ļ�������Ȱٷֱ�
	// config
	long m_updateVersion;			// ��Ҫ���µ��İ汾
	long m_localVersion;				// ���ذ汾
	unsigned char m_updateState;	// ״̬��־
	bool m_newestVersion;			// ���°汾
	wxString m_showVersion;			// ��Ϸ������ʾ�汾
	// thread
	MyThread *m_thread;
};
#endif
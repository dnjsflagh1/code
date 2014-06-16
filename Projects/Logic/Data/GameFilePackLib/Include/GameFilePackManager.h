/******************************************************************************/
#ifndef _GAMEFILEPACKMANAGER_H
#define _GAMEFILEPACKMANAGER_H
/******************************************************************************/

#include "Singleton.h"
#include "GameFilePackPreqs.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    // �ļ��������ϵͳ
    /******************************************************************************/
	class GameFilePackManager
    {
    public:

        SINGLETON_INSTANCE(GameFilePackManager);
        GameFilePackManager();
        virtual ~GameFilePackManager();

	public:

		/** 
			# �������д���ļ�
			@ ����ļ�����Config��Media�����е�CN�ļ�������
		*/
		void		load();
		// ж�����д���ļ�
		void		unload();

		// �õ�����·����(���������ǰ��findExistFile����)
		std::string	getWholeFilePath( const std::string& fileName, const std::string& type );

		// ��ѹ���ļ����ڴ�
		// �ļ���������·��
		bool		extractPackFile( const std::string& pathfilename, MGExtractedPackFile& file );

		// ��ѹ���ļ����ڴ�
		// �ļ���������·��
		bool		extractPackFile( const std::string& pathfilename, char*& buf, Int& size );

		// ��ѹ���ļ����ڴ�
		// �ļ���������·��
		bool		extractPackFile( const std::string& pathfilename, wchar_t*& buf );

		// �ļ��Ƿ����
		bool		isFileExist(const std::string& filename);

		// Ogreʹ��
		// ����ѹ����Ŀ¼�µ��ļ��б�
		StringMap	findZip(const std::string& path, const std::string& pattern);

		// ����ѹ����Ŀ¼���ļ���Ϣ�б�
		FileInfoVec findZipFileInfo(const std::string& path, const std::string& pattern);

		// ѹ�������Ƿ�����Դ�ļ�
		bool		isPackResEmpty();

	protected:

		////////////////////////////////////////////////////////////////////////////////////
		// �õ�����ļ�����ͨ������·����
		IMGPackFileSet*		getPackFileSetFromPath( const std::string& filePath );

		// �õ�����ļ�����ͨ������
		IMGPackFileSet*		getPackFileSetFromType( const std::string& type );

		////////////////////////////////////////////////////////////////////////////////////
		/**
			���ҵ�ǰĿ¼�µ�config��media�ļ���,������ѹ���ļ�(.cn�ļ����Զ�ȡ,�Ѽ��ܲ��Թ�)
			��·���µ��ļ�(.cn)������.
		*/
		void				findAndLoadPackFile(LPCSTR Path, LPCSTR filter);
		/** 
			# ��ȡ��Դ���Ľṹ
			# ��������Դ��Ŀ¼�ṹ
		*/
		void				loadPackFile( const std::string& filename, const char* password );
		// ж����Դ��
		void				unloadAllPackFile();

	private:

		/////////////////////////////////////////////////////////////////////////
		// ���д���ļ�����ӳ���б�
		ZIP_ARC_MAP	mPackSet;

		/////////////////////////////////////////////////////////////////////////
		// ����ѹ������·��ӳ��
		// ����·��(����Config/Base..�����ⲿ�ַ���)��keyֵ, ѹ��������value.
		// ���ڴ�·�������õ�ѹ��������(getPackFileSetFromPath����IMGPackFileSet*)
		StringMap mPathPackType;

		/////////////////////////////////////////////////////////////////////////
		// OGRE ʹ�õ��м�Ŀ¼�ṹ
		// ���ļ�·����ͬ���ļ�����.·��Ϊkeyֵ,valueֵΪ·����ͬ���ļ�.
		ResClassifyPathMap	mClassifyPathMap;

		// ͬһ·����ͬһ�ļ����͵��б����.
		ResClassifyPathTypeMap	mClassifyPathTypeMap;
		//////////////////////////////////////////////////////////////////////////

		// pack�������
		MGPackManager *mPackManager;
    };

}


#endif	

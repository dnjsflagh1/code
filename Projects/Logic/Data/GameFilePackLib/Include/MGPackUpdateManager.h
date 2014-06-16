/******************************************************************************/

/******************************************************************************/
#ifndef __MG_PACK_TOOL_MANAGER__
#define __MG_PACK_TOOL_MANAGER__


class GameFilePackManager;
namespace MG
{
	// �ⲿ����Դ������
	class MGPackUpdateManager
	{
	public:
		MGPackUpdateManager();
		virtual ~MGPackUpdateManager();

	public:
		// ���ºϲ���Դ��
		bool				resUpdate( const std::string& zipname, const std::string& unzipfolder,
								const std::string& gamefolder, const std::string& tempGamefolder);
		// ɾ���ļ��к�������ļ�(������Ŀ¼,�ݹ�)
		bool				deleteTempFolder(LPCSTR lpszPath);

	protected:
		////////////////////////////////////////////////////////////////////////////////////
		// ���°��ڲ�ʹ�ýӿ�
		// ��ѹ������ѹ��һ����ʱĿ¼��.
		bool				unZip(const std::string& zipname, const std::string& unzipfolder);

		// ����Ŀ¼�µ���Դ,����������ʱ�ļ���
		bool				findCopyPackFile(LPCSTR Path, LPCSTR gamefolder, LPCSTR tempGamefolder);
		// ������ѹ�������ļ���,���������б�,Ȼ��ѿͻ�������ͬ����Դ����������һ����ʱĿ¼
		bool				copyClientRes(LPCSTR filename, LPCSTR gamefolder,LPCSTR tempClienResfolder);

		// �ϲ�ѹ����
		bool				injectPack(const std::string& unzipfolder, const std::string& tempClienResfolder, 
								StringMap &filemap);


		// ����Դ�ϲ������Դ�����ؿͻ���
		bool				copyinjectResToGame(LPCSTR filename, LPCSTR gamefolder, LPCSTR tempClienResfolder);

		// �����ϲ������Դ�ļ���, Ȼ�����Դ�������ͻ���
		bool				traverseResAndCopy(LPCSTR tempGamefolder, LPCSTR gamefolder);

		
		// ɾ���ļ����ڵ��ļ�(������Ŀ¼,�ݹ�)
		bool				deleteFiles(LPCSTR lpszPath);
		//

	private:
		// pack�������
		MGPackManager *mPackManager;

		// ��Ҫ������.cn�ļ��б�
		StringMap	mPackFileMap;

		// ��������ļ�ʱ�������·��, һ��������·���Ա�
		// (��Ϊ�õĵݹ�,ÿ�����ֵ�����,�����þֲ�����).
		std::string mfindtempPath;

		//
		std::string mDeleteDirectory;
	};

} 
#endif

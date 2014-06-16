/******************************************************************************/
// �ļ��������ϵͳ
/******************************************************************************/
#ifndef __MG_EXTERNAL_PACK_MANAGER__
#define __MG_EXTERNAL_PACK_MANAGER__

#include "IMGPackExterInterface.h"

class GameFilePackManager;
namespace MG
{
	// �ⲿ����Դ������
	class MGExternalPackManager : public IMGExternalPackManager
	{
	public:
		MGExternalPackManager(GameFilePackManager* packManager);
		virtual ~MGExternalPackManager();

	public:
		// �ļ���������·��
		virtual bool		extractPackFile( const std::string& pathfilename, MG::MGExtractedPackFile& file );
		// ��ѹ���ļ����ڴ�
		// �ļ���������·��
		virtual bool		extractPackFile( const std::string& pathfilename, char*& buf, int& size );

		// ��ѹ���ļ����ڴ�
		// �ļ���������·��
		virtual bool		extractPackFile( const std::string& pathfilename, wchar_t*& buf );
		
		// ѹ�������Ƿ�����Դ�ļ�
		virtual bool		isPackResEmpty();
	private:
		GameFilePackManager* mPackManager;
	};

} 
#endif

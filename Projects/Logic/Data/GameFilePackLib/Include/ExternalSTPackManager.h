/******************************************************************************/
// SpeedTree�ļ��������ϵͳ
/******************************************************************************/
#ifndef __SPEEDTREE_EXTERNAL_PACK_MANAGER__
#define __SPEEDTREE_EXTERNAL_PACK_MANAGER__

#include "IExternalSTPackManager.h"

class GameFilePackManager;
namespace MG
{
	// SpeedTree��Դ������
	class ExternalSTPackManager : public SpeedTree::IExternalSTPackManager
	{
	public:
		ExternalSTPackManager(GameFilePackManager* packManager);
		virtual ~ExternalSTPackManager();

	public:
		// ��ѹ���ļ����ڴ�
		// �ļ���������·��
		virtual bool		extractPackFile( const char* pathfilename, char*& buf, int& size );

		// ��ѹ���ļ����ڴ�
		// �ļ���������·��
		virtual bool		extractPackFile( const char* pathfilename, wchar_t*& buf);

	private:
		GameFilePackManager* mPackManager;
	};

} 
#endif

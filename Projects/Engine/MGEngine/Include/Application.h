/******************************************************************************/
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IApplication.h"
#include "Singleton.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��Ϸ������
	/******************************************************************************/
	class Application : public IApplication, public MGSingleton<Application>
	{
	public:
        SINGLETON_DECLARE( Application )
        Application();
        virtual ~Application();

        /// ����Ogre����Ⱦ����
        virtual void    createWindow( CChar* name, Int width, Int height, Bool fullScreen = false, HWND handle = 0 );
		/// ��������ھ��
		virtual U32		getWindowHandle();
    private:

		/// ��������
        String mWindowName;
	};
	
}

/******************************************************************************/

#endif

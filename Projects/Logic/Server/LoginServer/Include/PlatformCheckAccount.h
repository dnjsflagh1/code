/******************************************************************************/
#ifndef _PLATFORMCHECKACCOUNT_H_
#define _PLATFORMCHECKACCOUNT_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//ƽ̨�ʺ���֤
	/******************************************************************************/
//#define USE_PLATFORMCHECKACCOUNT 1
	/*	--------------------------------------
	ƽ̨�û���¼���ش���
	21	�û���֤�ɹ���
	01	�˺Ÿ�ʽ����ȷ���Ҳ���Ϊ�գ�����UTF-8���룬������Χ4-15���ַ�
	02	���벻�淶(����Ϊ32λ) (6-15���ַ����ܵ�32λ)
	03	�û��������
	04	�û���������
	05	ǩ������
	06	��ʱ
	07	��������ID����
	08	����ѡ�����
	09	��Ϸ��Ų�����
	10	��������Ų�����
	--------------------------------------*/
	class PlatformCheckAccount
	{
	public:
		PlatformCheckAccount();
		~PlatformCheckAccount();
		SINGLETON_INSTANCE(PlatformCheckAccount);

	public:
		Int		checkAccount(Char16* accountName,Char16* psw,NetAddress& addr,std::map<Str16,Str16>& values);
		
		Bool	parseResponse(const Str16& response,std::map<Str16,Str16>& value);
	private:
		// # masterIP   
		Str8		mUip;
		// # ƽ̨�ӿڵ�ַ    
		Str8		mPlatformURL;		
		// # ��������
		Str8		mAction;			
		// # ƽ̨�ϸ���Ϸ�Ĺ�Կ
		Str8		mGameKey;			
		// # �ƹ�ƽ̨  
		Str8		mUnid;						  
	};
}
/******************************************************************************/
#endif
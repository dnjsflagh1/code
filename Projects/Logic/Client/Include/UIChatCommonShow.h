//***************************************************************************************************
#ifndef _H_UIChatCommonShow_
#define _H_UIChatCommonShow_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{

    struct ChatFaceplateConfig;
	class  MessageManager;
	class UIChatCommonShow : public UIObject
	{
		
	public:
		friend class MessageManager;
		UIChatCommonShow();
		~UIChatCommonShow();
		SINGLETON_INSTANCE(UIChatCommonShow);
	public:
        //������ʾ��� ��ͨ���������� 
		enum SHOW_PLACE
		{
           SHOW_PLACE_COMMON = 1,
		   SHOW_PLACE_LABA 
		};

		//����Ĭ���ۺ�����ǩ ������������Ƶ��
		void                InitDefaultFaceplate();
		virtual void		setEvent();

		//�¼�
		static  void        onChangeTag( void* widget );
        static  void        onRightClickTag( void* widget );

		//��ui
		virtual	Bool		openGui(); 
		virtual void        restore();
		
	protected:
		
		
		//��������������Ϣ
		void				addChatMsg(Byte channelId,CChar16* dataSender,Char16* data,I32 count);
		void                addChatResultMsg( U32 channelid,Byte result,Char16* data,I32 count );
		void                addChatMsgForTest(Char16* data);
		//�����������ü�¼�����������
		Bool                setChatFaceplate();
		void                setTextColour(Int _start, Int _count, const Color& value,SHOW_PLACE _showplace);

		void                clearCommonArea();
		void                clearLaBaArea();

		U32					getTextLength(SHOW_PLACE _showplace);

    protected:
	    U32                 getWidthStrAddBreak(Str16& src, Int width, Str8 fontName = "");   //���������ӻ��з�

	private:
        Int                 getEditBoxWidth(SHOW_PLACE _showplace);
		Int                 getEditBoxHeight(SHOW_PLACE _showplace);

	private:
		//����ϴε������������
        ChatFaceplateConfig* mChatfplatecfg;
		
	};




}








#endif
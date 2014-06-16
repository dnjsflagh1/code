//**********************************************************************************************************
#ifndef _H_IEDIT_578941320_
#define _H_IEDIT_578941320_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//�༭���ֽӿ�
namespace MG
{
    class IEdit
    {
    public:
        //��ÿؼ��Ĺ�ͬ���Բ��֡�
        virtual IWidget*    getWidget() = 0;
        //����Ϊ����ģʽ
        virtual void        setEditPassword(bool _value) = 0;
        //����Ƿ�Ϊ����ģʽ
        virtual bool        getEditPassword() = 0;
        //����Ϊ����ģʽ
        virtual void        setEditMultiLine(bool _value) = 0;
        //����Ƿ�Ϊ����ģʽ
        virtual bool        getEditMultiLine() = 0;
        //����Ϊ��̬ģʽ���൱��Text�����ǿ��Զ�����ʾ��
        virtual void        setEditStatic(bool _value) = 0;
        //����Ƿ�Ϊ��̬ģʽ��
        virtual bool        getEditStatic() = 0;
        //��text��
        virtual void        addText(const std::wstring& text) = 0;
        //
        virtual void            setTextColour(const Color& value) = 0;
        //
        virtual const Color     getTextColour() = 0;
        /** Set widget text align */
        virtual void            setTextAlign(MGAlign _value) = 0;
        /** Set widget text font */
        virtual void            setFontName(const std::string& _value) = 0;
        /** Get widget text font name */
        virtual const std::string& getFontName() = 0;
        /** Set widget text font height */
        virtual void            setFontHeight(int _value) = 0;
        /** Get widget text font height */
        virtual int             getFontHeight() = 0 ;
		/** Colour interval */
		virtual void setTextIntervalColour(Int _start, Int _count, const Color& value) = 0;
		/** set selected text */
		virtual void setTextSelection(U32 _start, U32 _end) = 0;
		/** Colour selected text */
		virtual void setTextSelectionColour(const Color& _value) = 0;
		virtual U32 getTextLength() const = 0;
		virtual U32 getMaxTextLength() const = 0;
		virtual const std::wstring& getCaption()const = 0;
		virtual void setCaption(std::wstring caption) = 0;
		virtual bool clearEditText(bool _history) = 0;

     public://�¼�
        virtual void        setSelectAcceptEvent(PVOID_CALLBACK) = 0;
        virtual void        setTextChangeEvent(PVOID_CALLBACK) = 0;

		//PVOIDPVOIDINT_CALLBACK�ص������������������
		//��һ������pvoid ΪIEdit�Լ���ָ��
		//�ڶ�������pvoid ΪIImageָ�룬����IEdit�ؼ��ڵ�ͼƬ
		//����������int ΪͼƬ��ID��
		//PVOIDPVOIDINT_CALLBACK�Ĺ���������IImageͼƬ������
		virtual void		setEditAddFaceEvent(PVOIDPVOIDINT_CALLBACK) = 0;

		//PVOIDVECI2U64INTBOOL_CALLBACK������������
		//��һ������pvoid ΪIEdit�Լ���ָ��
		//�ڶ�������vecI2Ϊ����λ��
		//����������u64 Ϊ�����ӵ�id�ţ�
		//���ĸ�����int Ϊ�����ӵ����͡�
		//���������bool Ϊ�Ƿ���ʾ�����ӡ�
		//PVOIDVECI2U64INTBOOL_CALLBACK ���Ƿ���ʾtips��
		virtual void        setShowLinkInfoEvent(PVOIDVECI2U64INTBOOL_CALLBACK) = 0; 

		//PVOIDU64INT_CALLBACK�������������
		//��һ������pvoid ΪIEdit�Լ���ָ��
		//����������u64 Ϊ�����ӵ�id�ţ�
		//���ĸ�����int Ϊ�����ӵ����͡�
		//PVOIDU64INT_CALLBACK�Ĺ����ǵ�������ӵ��¼���
		virtual void        setClickLinkEvent(PVOIDU64INT_CALLBACK) = 0;
    protected:
    private:
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************
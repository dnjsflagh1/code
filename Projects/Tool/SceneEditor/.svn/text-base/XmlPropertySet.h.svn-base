/******************************************************************************/
#ifndef _XMLPROPERTYSET_H_
#define _XMLPROPERTYSET_H_
/******************************************************************************/

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace System::Drawing;
using namespace System::Globalization;

/******************************************************************************/
namespace SceneEditor 
{
    /******************************************************************************/
    //XmlGroupPropertyConverter
    /******************************************************************************/
    public ref class XmlGroupPropertyConverter : public ExpandableObjectConverter
    {
    public:
        virtual Object^ ConvertTo(
            ITypeDescriptorContext^ context, 
            CultureInfo^ culture, 
            Object^ value, 
            Type^ destinationType
            ) override
        {
            return ExpandableObjectConverter::ConvertTo(context,culture,value,destinationType);
        }
    };

    /******************************************************************************/
    //XmlProperty
    /******************************************************************************/
    public ref class XmlStrProperty : public System::ComponentModel::PropertyDescriptor
    {
    public:
        XmlStrProperty(XMLElement* parent, String^ attrName, String^ attrValue, array<Attribute^>^ attrs)
            :PropertyDescriptor(attrName,attrs)
            ,mStrValue(attrValue)
            ,mParentXmlElm(parent)
        {
        }
    public:
        virtual property bool IsLocalizable {
            bool get () override
            {
                return true;
            }
        }
        virtual property Type^ ComponentType {
            Type^ get () override 
            {
                return this->GetType();
            } 
        }
        virtual property bool IsReadOnly {
            bool get () override    
            {
                return false;
            } 
        }
        virtual property Type^ PropertyType {
            Type^ get () override
            {
                return mStrValue->GetType();
            } 
        }
        virtual bool CanResetValue( Object^ component ) override
        {
            return false;
        }
        virtual Object^ GetValue( Object^ component ) override
        {
            return mStrValue;
        }
        virtual void ResetValue( Object^ component ) override
        {
        }
        virtual void SetValue( Object^ component, Object^ value ) override
        {
            mStrValue = value->ToString();
            saveXml();
        }
        virtual bool ShouldSerializeValue( Object^ component ) override
        {
            return true;
        }
    public:
        void              saveXml();
    public:
        String^         mStrValue;
        XMLElement*   mParentXmlElm;
    };


    /******************************************************************************/
    //XmlGroupProperty
    /******************************************************************************/
    public ref class XmlGroupPropertyContainer : public System::ComponentModel::ICustomTypeDescriptor
    {
    public:
        XmlGroupPropertyContainer()
        {
            array<System::ComponentModel::PropertyDescriptor^>^ descs = gcnew cli::array< System::ComponentModel::PropertyDescriptor^ >(0) {};
            mCollection    = gcnew System::ComponentModel::PropertyDescriptorCollection(descs,false);
        }
        virtual ~XmlGroupPropertyContainer()
        {
            for each ( PropertyDescriptor^ myProperty in mCollection )
            {
                delete myProperty;
            }

            delete mCollection;
        }
    public:
        virtual System::ComponentModel::AttributeCollection^ GetAttributes()
        {
            return System::ComponentModel::TypeDescriptor::GetAttributes(this,true);
        }
        virtual String^ GetClassName()
        {
            return System::ComponentModel::TypeDescriptor::GetClassName(this,true);
        }
        virtual String^ GetComponentName()
        {
            return System::ComponentModel::TypeDescriptor::GetComponentName(this,true);
        }
        virtual System::ComponentModel::TypeConverter^ GetConverter()
        {
            return System::ComponentModel::TypeDescriptor::GetConverter(this,true);
        }
        virtual System::ComponentModel::EventDescriptor^ GetDefaultEvent()
        {
            return System::ComponentModel::TypeDescriptor::GetDefaultEvent(this,true);
        }
        virtual System::ComponentModel::PropertyDescriptor^ GetDefaultProperty()
        {
            return System::ComponentModel::TypeDescriptor::GetDefaultProperty(this,true);
        }
        virtual Object^ GetEditor( Type^ editorBaseType )
        {
            return System::ComponentModel::TypeDescriptor::GetEditor(this,editorBaseType,true);
        }
        virtual System::ComponentModel::EventDescriptorCollection^ GetEvents()
        {
            return System::ComponentModel::TypeDescriptor::GetEvents(this,true);
        }
        virtual System::ComponentModel::EventDescriptorCollection^ GetEvents(cli::array<System::Attribute ^> ^ dimension)
        {
            return System::ComponentModel::TypeDescriptor::GetEvents(this,dimension,true);
        }
        virtual System::ComponentModel::PropertyDescriptorCollection^ GetProperties()
        {
            return mCollection;
        }
        virtual System::ComponentModel::PropertyDescriptorCollection^ GetProperties(cli::array<System::Attribute^> ^ dimension)
        {
            return this->GetProperties();
        }
        virtual Object^ GetPropertyOwner( System::ComponentModel::PropertyDescriptor^ pd )
        {
            return this;
        }
    public:
        System::ComponentModel::PropertyDescriptorCollection^ mCollection;
    };

    /******************************************************************************/
    //XmlGroupProperty
    /******************************************************************************/
    public ref class XmlGroupProperty : public System::ComponentModel::PropertyDescriptor
    {
    public:
        XmlGroupProperty(String^ name, array<Attribute^>^ attrs)
            :PropertyDescriptor(name,attrs)
        {
            mXmlElm           = NULL;
            mGroup         = gcnew XmlGroupPropertyContainer();
            m_convert       = gcnew XmlGroupPropertyConverter();
            mStrPropList      = gcnew List<XmlStrProperty^>();
            mGroupList    = gcnew List<XmlGroupProperty^>();
        }

        virtual ~XmlGroupProperty()
        {
            delete mGroup;
            delete m_convert;
            delete mStrPropList;
            delete mGroupList;
        }
    public:
        virtual property TypeConverter^ Converter {
            TypeConverter^ get () override
            {
                return m_convert;
            }
        }

        virtual property bool IsBrowsable {
            bool get () override
            {
                return true;
            }
        }
        virtual property bool IsLocalizable {
            bool get () override
            {
                return false;
            }
        }
        virtual property Type^ ComponentType {
            Type^ get () override 
            {
                return this->GetType();
            } 
        }
        virtual property bool IsReadOnly {
            bool get () override    
            {
                return false;
            } 
        }
        virtual property Type^ PropertyType {
            Type^ get () override
            {
                return mGroup->GetType();
            } 
        }
        virtual bool CanResetValue( Object^ component ) override
        {
            return false;
        }
        virtual Object^ GetValue( Object^ component ) override
        {
            return mGroup;
        }
        virtual void ResetValue( Object^ component ) override
        {
        }
        virtual void SetValue( Object^ component, Object^ value ) override
        {
        }
        virtual bool ShouldSerializeValue( Object^ component ) override
        {
            return false;
        }
    public:

        void    loadXml(XMLElement* elment);
        void    addXmlGroupProperty(XMLNode*elm);
        void    addXmlStrProperty(const XMLAttribute*attr);
        void    saveXml();

    public:
        XmlGroupPropertyContainer^  mGroup;
        XMLElement*               mXmlElm;
        XmlGroupPropertyConverter^  m_convert;
        List<XmlGroupProperty^>^    mGroupList ;
        List<XmlStrProperty^>^      mStrPropList ;
    };

    /******************************************************************************/
    //XmlPropertySet
    /******************************************************************************/
    public ref class XmlPropertySet : public System::ComponentModel::ICustomTypeDescriptor
    {
    public:
        XmlPropertySet()
        {
            array<System::ComponentModel::PropertyDescriptor^>^ descs = gcnew cli::array< System::ComponentModel::PropertyDescriptor^ >(0) {};
            mCollection    = gcnew System::ComponentModel::PropertyDescriptorCollection(descs,false);
            m_list          = gcnew List<XmlGroupProperty^>();
			m_subList		= gcnew List<XmlGroupProperty^>();
            m_RootAttrList = gcnew List<XmlStrProperty^>();
        }
        virtual ~XmlPropertySet()
        {
            delete mCollection;
            delete m_list;
            delete m_RootAttrList;
			delete m_subList;
        }
    public:
        virtual System::ComponentModel::AttributeCollection^ GetAttributes()
        {
            return System::ComponentModel::TypeDescriptor::GetAttributes(this,true);
        }
        virtual String^ GetClassName()
        {
            return System::ComponentModel::TypeDescriptor::GetClassName(this,true);
        }
        virtual String^ GetComponentName()
        {
            return System::ComponentModel::TypeDescriptor::GetComponentName(this,true);
        }
        virtual System::ComponentModel::TypeConverter^ GetConverter()
        {
            return System::ComponentModel::TypeDescriptor::GetConverter(this,true);
        }
        virtual System::ComponentModel::EventDescriptor^ GetDefaultEvent()
        {
            return System::ComponentModel::TypeDescriptor::GetDefaultEvent(this,true);
        }
        virtual System::ComponentModel::PropertyDescriptor^ GetDefaultProperty()
        {
            return System::ComponentModel::TypeDescriptor::GetDefaultProperty(this,true);
        }
        virtual Object^ GetEditor( Type^ editorBaseType )
        {
            return System::ComponentModel::TypeDescriptor::GetEditor(this,editorBaseType,true);
        }
        virtual System::ComponentModel::EventDescriptorCollection^ GetEvents()
        {
            return System::ComponentModel::TypeDescriptor::GetEvents(this,true);
        }
        virtual System::ComponentModel::EventDescriptorCollection^ GetEvents(cli::array<System::Attribute ^> ^ dimension)
        {
            return System::ComponentModel::TypeDescriptor::GetEvents(this,dimension,true);
        }
        virtual System::ComponentModel::PropertyDescriptorCollection^ GetProperties()
        {
            return mCollection;
        }
        virtual System::ComponentModel::PropertyDescriptorCollection^ GetProperties(cli::array<System::Attribute^> ^ dimension)
        {
            return this->GetProperties();
        }
        virtual Object^ GetPropertyOwner( System::ComponentModel::PropertyDescriptor^ pd )
        {
            return this;
        }

    public:

        void    loadXmlElement(XMLElement*elm);
        void    addXmlGroupProperty(XMLNode*elm);
        void    addRootXmlStrProperty(XMLElement* elm);
        void    saveXmlElement();
        void    clear();

		void		addSubGroupProperty(char* group_name, char* attr_name, char* attr_value);
		std::string	getSubGroupProperty(char* group_name, char* attr_name);

    public:
        System::ComponentModel::PropertyDescriptorCollection^ mCollection;
        List<XmlGroupProperty^>^ m_list ;
		List<XmlGroupProperty^>^ m_subList;			// Holding custom properties which added by user but do not need to save in XML file.
        List<XmlStrProperty^>^ m_RootAttrList;
    };
}

#endif //
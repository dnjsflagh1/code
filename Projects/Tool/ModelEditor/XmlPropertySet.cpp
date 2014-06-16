/******************************************************************************/
#include "stdafx.h"
#include "XmlPropertySet.h"
#include "CoreManager.h"
#include "direct.h"
#include "XmlHelper.h"
#include "Utility.h"
/******************************************************************************/


namespace ModelEditor
{
    /******************************************************************************/
    //XmlStrProperty
    /******************************************************************************/
    void XmlStrProperty::saveXml()
    {
        if (mParentXmlElm)
        {
            StrToChar8 attrName( Name );
            StrToChar8 attrValue( GetValue(this)->ToString() );
 
            XmlHelper::setAttribute( mParentXmlElm, attrValue.getChar8(), attrName.getChar8() );                
        }
    }
    /******************************************************************************/
    //XmlGroupProperty
    /******************************************************************************/
    void XmlGroupProperty::loadXml(XMLElement* elment)
    {
        if (elment)
        {
            mXmlElm = elment;

            //add str property
            int attr_count = 0;
            const XMLAttribute* attr = elment->FirstAttribute();
            for( ; attr; attr=attr->Next() ) 
            {
                addXmlStrProperty(attr);
  
            }

            //add group property
            XMLNode* currNode         = elment->FirstChild();
            XMLNode* firstSiblingNode = currNode;
            XMLNode* nextNode         = NULL;
            while( currNode )
            {   
                addXmlGroupProperty(currNode);
                //@ parallel 
                nextNode    = currNode->NextSibling();
                if (nextNode&&nextNode==firstSiblingNode)
                {
                    break;
                }
                currNode = nextNode;
            }
        }
    }
    //-----------------------------------------------------------------------------
    void XmlGroupProperty::saveXml()
    {
        if (mXmlElm)
        {
            for each ( XmlStrProperty^ myStrProperty in mStrPropList )
            {
                myStrProperty->saveXml();
            }
            
            for each ( XmlGroupProperty^ myGroupProperty in mGroupList )
            {
                myGroupProperty->saveXml();
            }
        }
    }
    //-----------------------------------------------------------------------------
    void XmlGroupProperty::addXmlStrProperty(const XMLAttribute*attr)
    {
        String^ attrName    = TypeConverter::Char8ToStr(attr->Name()); 
        String^ attrValue   = TypeConverter::Char8ToStr(attr->Value());
    
        array<Attribute^>^ descs = gcnew cli::array< Attribute^ >(0) {};
        XmlStrProperty^ xmlStrProp = gcnew XmlStrProperty(mXmlElm, attrName, attrValue, descs);

        mGroup->mCollection->Add(xmlStrProp);
        mStrPropList->Add(xmlStrProp);
    }
    //-----------------------------------------------------------------------------
    void XmlGroupProperty::addXmlGroupProperty(XMLNode*elm)
    {
        std::string formatType = elm->Value();

        String^ groupName = TypeConverter::Char8ToStr(formatType.c_str());
        
        array<Attribute^>^ attrs            = gcnew cli::array< Attribute^ >(0) {};
        XmlGroupProperty^ groupProperty     = gcnew XmlGroupProperty(groupName, attrs);
        groupProperty->loadXml(elm->ToElement());

        mGroup->mCollection->Add(groupProperty);
        mGroupList->Add(groupProperty);
    }

    /******************************************************************************/
    //XmlPropertySet
    /******************************************************************************/
    void XmlPropertySet::addRootXmlStrProperty(XMLElement* elm)
    {
        const XMLAttribute* xmlAttr = elm->FirstAttribute();
        for( ; xmlAttr; xmlAttr=xmlAttr->Next() ) 
        {
            String^ attrName = TypeConverter::Char8ToStr( xmlAttr->Name() );
            String^ attrValue = TypeConverter::Char8ToStr( xmlAttr->Value() );

            array<Attribute^>^ descs = gcnew cli::array< Attribute^ >(0) {};
            XmlStrProperty^ xmlStrProp = gcnew XmlStrProperty(elm, attrName, attrValue, descs);

            mCollection->Add(xmlStrProp);
            m_RootAttrList->Add(xmlStrProp);
        }
    }
    //-------------------------------------------------------------------------------
    void XmlPropertySet::loadXmlElement(XMLElement*elm)
    {
        clear();
        if (elm)
        {
            XMLNode* parentNode       = elm;

            addRootXmlStrProperty(parentNode->ToElement());

            XMLNode* currNode         = parentNode->FirstChild();
            XMLNode* firstSiblingNode = currNode;
            XMLNode* nextNode         = NULL;
            while( currNode )
            {
                addXmlGroupProperty(currNode);
                //@ parallel 
                nextNode    = currNode->NextSibling();
                if (nextNode&&nextNode==firstSiblingNode)
                {
                    break;
                }
                currNode = nextNode;
            }
        }
    }
    //-----------------------------------------------------------------------------
    void XmlPropertySet::addXmlGroupProperty(XMLNode* elm)
    {
        //TODO:
        std::string formatType = elm->Value();
        String^ group_name = TypeConverter::Char8ToStr( formatType.c_str() ); 

        array<Attribute^>^ attrs            = gcnew cli::array< Attribute^ >(0) {};
        XmlGroupProperty^ groupProperty     = gcnew XmlGroupProperty(group_name,attrs);
        groupProperty->loadXml(elm->ToElement());

        mCollection->Add(groupProperty);
        m_list->Add(groupProperty);
    }
    //-----------------------------------------------------------------------------
    void XmlPropertySet::saveXmlElement()
    {
        for each ( XmlGroupProperty^ myProperty in m_list )
        {
            myProperty->saveXml();
        }

        for each ( XmlStrProperty^ myPropertyDescriptor in m_RootAttrList )
        {   
            myPropertyDescriptor->saveXml();
        }
    }
    //-----------------------------------------------------------------------------
    void XmlPropertySet::clear()
    {
        for each ( PropertyDescriptor^ myProperty in mCollection )
        {
            delete myProperty;
        }

        for each ( XmlGroupProperty^ myGroupProperty in m_list )
        {
            delete myGroupProperty;
        }

        for each ( XmlStrProperty^ myStrProperty in m_RootAttrList )
        {
            delete myStrProperty;
        }

        mCollection->Clear();
        m_list->Clear();
        m_RootAttrList->Clear();
    }
}









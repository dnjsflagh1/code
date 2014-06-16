//***************************************************************************************************
#include "stdafx.h"
#include "UIClanRoleControl.h"
#include "CPlayer.h"
#include "UIGenrealEquip.h"

#include "PlayerCharacterData.h"
//***************************************************************************************************
namespace MG
{
    UIClanRoleControl::UIClanRoleControl()
    {

    }
    //------------------------------------------------------------------------------------
    UIClanRoleControl::~UIClanRoleControl()
    {

    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::setEvent()
    {
        IButton* pButton = getLayout()->getButton("button_equip");
        assert(pButton);
        pButton->getWidget()->setMouseButtonClickEvent(onClickGenrealEquip);

        pButton = getLayout()->getButton("button_skill");
        assert(pButton);
        pButton->getWidget()->setMouseButtonClickEvent(onClickGenrealSkill);

        pButton = getLayout()->getButton("button_feats");
        assert(pButton);
        pButton->getWidget()->setMouseButtonClickEvent(onClickGenrealFeats);

        IList* pList = getLayout()->getList("list_genreal");
        assert(pList);
        pList->setEventListMouseItemActivate(onClickGenreal);
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::updateGenrealInfo(CPlayerCharacter* pCharacter)
    {
        DYNAMIC_ASSERT(pCharacter);

        Str16  tempWstr;
        //服务器发送当前选中的角色信息更新
        //或者自己更换选择的角色
        IImage* pImage = getLayout()->getImage("image_genreal");
        //找到图片
        //pCharacter->getData()->charArtIcon;
        //pImage->setTexture();

        IText* pText = getLayout()->getText("text_name");
        pText->getWidget()->setCaption( pCharacter->getName() );

        pText = getLayout()->getText("text_zi");
        pText->getWidget()->setCaption( pCharacter->getData()->charZiName );

        //职业
        //pText = getLayout()->getText("text_job");
        //pText->getWidget()->setCaption( pCharacter->getData()-> );

        pText = getLayout()->getText("text_lvl");
        tempWstr.clear();
        tempWstr = pCharacter->getLevel();
        tempWstr += L"级";
        pText->getWidget()->setCaption( tempWstr );

        //官位
        //pText = getLayout()->getText("text_offpos");
        //pText->getWidget()->setCaption( pCharacter->getData()->charOfficialPos );

        //官品
        //pText = getLayout()->getText("text_offpos");
        //pText->getWidget()->setCaption( pCharacter->getData()->charOfficialPos );

        IComboBox* pComboBox = getLayout()->getComboBox("combobox_title");
        //找到称号，
        //pComboBox->addItem();
        //pComboBox->setIndexSelected();

        //属性
        //找Attr
        /*pText = getLayout()->getText("text_hp");
        pText->getWidget()->setCaption( pCharacter->getData()->charHP );

        pText = getLayout()->getText("text_ph");
        pText->getWidget()->setCaption( pCharacter->getData()-> );

        pText = getLayout()->getText("text_po");
        pText->getWidget()->setCaption( pCharacter->getData()-> );

        pText = getLayout()->getText("text_qk");
        pText->getWidget()->setCaption( pCharacter->getData()-> );
        */

        //介绍
        //IEdit* pEdit = getLayout()->getEdit("edit_genrealintro");
        //pEdit->addText();
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::onClickGenreal( void* widget, Int index )
    {
        assert(widget);
        UIClanRoleControl::getInstance().setGenrealInfo(index);
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::onClickGenrealEquip( void* widget )
    {
        assert(widget);
        //打开装备UI
        UIGenrealEquip::getInstance().openGui();
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::onClickGenrealSkill( void* widget )
    {
        assert(widget);
        //打开技能UI
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::onClickGenrealFeats( void* widget )
    {
        assert(widget);
        //打开功绩UI
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::onSelectComboboxItem( void* widget, Int index )
    {
        assert(widget);
        //向服务器申请设置当前称号
        IComboBox* pComboBox = (IComboBox*)widget;
        pComboBox->removeAllItems();
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::setGenrealInfo(Int index)
    {
        CClan* pClan = CPlayer::getInstance().getActiveClan();
        assert(pClan);

        if ( index == MG_NONE )
            return;
        //如果是上次选中的
        if ( index == mCurSelectIndex )
            return;
        //test
        IComboBox* pComboBox = getLayout()->getComboBox("combobox_title");
        //找到称号，
        Char16 tempStr[32] = L"";
        for (Int i=0; i<8; i++)
        {
            swprintf_s(tempStr, _countof(tempStr), L"牛逼称号%d", i+1);
            pComboBox->addItem( tempStr );
        }
        
        pComboBox->setIndexSelected(0);
        //end test;

        /*assert( index >= 0  &&  index < pClan->getPlayerCharacterNum() );
        std::wstring tempWstr;
        CPlayerCharacter* pCharacter = pClan->getPlayerCharacterByIndex(index);
        
        if ( pCharacter )
        {
            updateGenrealInfo(pCharacter);
        }*/
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::addCharacterList()
    {
        CClan* pClan = CPlayer::getInstance().getActiveClan();
        assert(pClan);
        CPlayerCharacter* pCharacter = NULL;

        IList* pList = getLayout()->getList("list_genreal");
        assert(pList);

        Char16 tempStr[32] = L"";
        for (Int i=0; i<8; i++)
        {
            swprintf_s(tempStr, _countof(tempStr), L"张辽%d", i+1);
            pList->addItem( tempStr );
        }
        /*Int nCount = pClan->getPlayerCharacterNum();
        for (Int i=0; i<nCount; i++)
        {
            pCharacter = pClan->getPlayerCharacterByIndex(i);
            assert(pCharacter);
            pList->addItem( pCharacter->getName() );
        }
        if ( nCount > 0 )
        {  
            pList->setIndexSelected(0);
            setGenrealInfo(0);
        }*/
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::addCharacter( CPlayerCharacter* pCharacter )
    {
        DYNAMIC_ASSERT(pCharacter);

        IList* pList = getLayout()->getList("list_genreal");
        assert(pList);

        pList->addItem( pCharacter->getName() );
    }
    //------------------------------------------------------------------------------------
    void UIClanRoleControl::deleteCharacer( CPlayerCharacter* pCharacter )
    {
        DYNAMIC_ASSERT(pCharacter);

        IList* pList = getLayout()->getList("list_genreal");
        assert(pList);

        U32 index = pList->findItemIndexWith( pCharacter->getName() );
        if (index != MG_NONE)
            pList->removeItemAt(index);
    }
}
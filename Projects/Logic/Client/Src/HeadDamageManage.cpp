//***********************************************************************************************************
#include "stdafx.h"
#include "HeadDamageManage.h"
#include "HeadDamage.h"
#include "CSceneManager.h"
#include "ClientMain.h"
//***********************************************************************************************************
namespace MG
{
    static Str8 headDamageResouce[3] = { "Main_Area_Num", "Main_Area_Num", "Main_Area_Num" };
    static Str8 headDamageGroup[3] = { "Reds", "Blues", "Greens" } ;
    //---------------------------------------------------------------------------------------
    HeadDamageManage::HeadDamageManage()
    {

    }
    //---------------------------------------------------------------------------------------
    HeadDamageManage::~HeadDamageManage()
    {
        clear();
    }
    //---------------------------------------------------------------------------------------
    void HeadDamageManage::addNum( Vec3 pos, Flt height, DamageType type, UInt num, Bool isAdd /*= true*/ )
    {
        //将pos 转化为 screen pos。
        VecI2 desPos;
        pos.y += height;
        worldPointToScreenPoint(pos, desPos);

        HEADDAMAGE_TYPE tempType = changeType(type);

        //获得图片的宽高和图片的资源，及图片的数量。
        Str8 tempResouce;
        Str8 tempGroup;
        Char8 tempItem[10] = "";
        UInt tempPicNum = 0;
        VecI2 tempSize(HeadDamageResouce::getInstance().getPicW(tempType), HeadDamageResouce::getInstance().getPicH(tempType));

        
        

        if ( tempType == HEADDAMAGE_TYPE_ALL )
        {
            for (Int i=HEADDAMAGE_TYPE_HP; i<HEADDAMAGE_TYPE_ALL; i++)
            {
                HeadDamageResouce::getInstance().getPicRecouse((HEADDAMAGE_TYPE)i, num, isAdd, tempResouce, tempGroup, tempItem, tempPicNum);                   
                //左上角位置。
                if ( i == HEADDAMAGE_TYPE_HP )
                    desPos.x -= ( tempSize.x * tempPicNum / 2 );
                desPos.y -= tempSize.y;
                //加图片
                addNumPic(desPos, tempSize, tempPicNum, tempResouce, tempGroup, tempItem);
            }
        }
        else
        {
            HeadDamageResouce::getInstance().getPicRecouse(tempType, num, isAdd, tempResouce, tempGroup, tempItem, tempPicNum);
            //左上角位置。
            desPos.x -= ( tempSize.x * tempPicNum / 2 );
            desPos.y -= tempSize.y;
            //加图片
            addNumPic(desPos, tempSize, tempPicNum, tempResouce, tempGroup, tempItem);
        }
        
    }
    //---------------------------------------------------------------------------------------
    void HeadDamageManage::addMiss( Vec3 pos, Flt height )
    {

    }
    //---------------------------------------------------------------------------------------
    void HeadDamageManage::update( Flt delta )
    {
		//FUNDETECTION(__MG_FUNC__);
        std::list<HeadDamage*>::iterator iter = mHeadDamageListWork.begin();
        while ( iter != mHeadDamageListWork.end() )
        {
            if ( (*iter)->dead() )
            {    
                (*iter)->close();
                mHeadDamageListFree.push_back((*iter));
                iter = mHeadDamageListWork.erase(iter);
            }
            else
            {
                (*iter)->update( delta );
                ++iter;
            }
        }
    }
    //---------------------------------------------------------------------------------------
    void HeadDamageManage::clear()
    {
        mHeadDamageListFree.clear();
        mHeadDamageListWork.clear();

        while ( mHeadDamageList.begin() != mHeadDamageList.end() )
        {
            delete *( mHeadDamageList.begin() );
            mHeadDamageList.erase( mHeadDamageList.begin() );
        }

        mHeadDamageList.clear();
    }
    //---------------------------------------------------------------------------------------
    void HeadDamageManage::worldPointToScreenPoint( Vec3 pos, VecI2& screenPos )
    {
        //将pos 转化为 screen pos。
        IScene* pScene = CSceneManager::getInstance().getEngineScene();
        assert(pScene);
        ICamera* pCamera = pScene->getActiveCamera();
        assert(pCamera);
        Vec2 tempScreenPos;
        pCamera->worldPointToScreenPoint(pos, tempScreenPos);
        //获得图片的下中位置
        IEngineMain* pEngineMain = ClientMain::getInstance().getEngine();
        assert(pEngineMain);
        IDisplay* pDisplay = pEngineMain->display();
        assert(pDisplay);
        screenPos.x = UInt(tempScreenPos.x * pDisplay->getWidth());
        screenPos.y = UInt(tempScreenPos.y * pDisplay->getHeight());
    }
    //---------------------------------------------------------------------------------------
    void HeadDamageManage::addNumPic( VecI2 pos, VecI2 size, UInt picNum, Str8 resouce, Str8 group, Char8* item )
    {
        //加图片
        HeadDamage* tempHeadDamage = NULL;
        for (UInt i=0; i<picNum; i++)
        {
            Str8 tempItem;
            tempItem += item[i];

            if ( mHeadDamageListFree.size() > 0 )
            {
                tempHeadDamage = mHeadDamageListFree.front();
                mHeadDamageListFree.pop_front();
                mHeadDamageListWork.push_back(tempHeadDamage);
                tempHeadDamage->resetHeadDamage( CoordI(pos.x, pos.y, size.x, size.y), resouce, group, tempItem );
            }
            else
            {
                
                tempHeadDamage = new HeadDamage( CoordI(pos.x, pos.y, size.x, size.y), resouce, group, tempItem );
                assert(tempHeadDamage);
                mHeadDamageList.push_back(tempHeadDamage);
                mHeadDamageListWork.push_back(tempHeadDamage);
            }
            pos.x += size.x;
        }
    }
    //---------------------------------------------------------------------------------------
    void HeadDamageManage::test( Flt delta, Vec3 pos )
    {
        static IdType tempStartTime = 0;
        if ( tempStartTime == 0 )
        {    
            tempStartTime =  GetTickCount() + 5000;
            DamageType type = (DamageType)MGRandom::getInstance().rand_ab_One((UInt)DT_HP, (UInt)DT_SP);
            UInt num = MGRandom::getInstance().rand_ab_One(10, 1000);
            Bool isAdd = (Bool)MGRandom::getInstance().rand_ab_One(0, 1);
            pos.y += 1.f;
            addNum( pos, 1.2, type, num, isAdd );

            return;
        }
        else
        {
            if ( GetTickCount() > tempStartTime )
            {
                tempStartTime = 0;
            }
            update( delta );
        }
    }
    //---------------------------------------------------------------------------------------
    MG::HEADDAMAGE_TYPE HeadDamageManage::changeType( DamageType type )
    {
       switch(type)
       {
       case DT_HP: return HEADDAMAGE_TYPE_HP;
       case DT_MP: return HEADDAMAGE_TYPE_MP;
       case DT_SP: return HEADDAMAGE_TYPE_SP;
       case DT_HPMP: return HEADDAMAGE_TYPE_ALL;
       }
       return HEADDAMAGE_TYPE_NULL;
    }

    void HeadDamageManage::clearAllImage()
    {
        std::list<HeadDamage*>::iterator iter = mHeadDamageListWork.begin();
        while ( iter != mHeadDamageListWork.end() )
        {   
            (*iter)->close();
            mHeadDamageListFree.push_back((*iter));
            iter = mHeadDamageListWork.erase(iter);
        }
    }
    //***********************************************************************************************
    HeadDamageResouce::HeadDamageResouce()
    {
       for (Int i=0; i<HEADDAMAGE_TYPE_MAX; i++)
       {
           mPicH[i] = 20;
           mPicW[i] = 16;
       }
    }
    //---------------------------------------------------------------------------------------
    HeadDamageResouce::~HeadDamageResouce()
    {

    }
    //---------------------------------------------------------------------------------------
    MG::UInt HeadDamageResouce::getPicW( HEADDAMAGE_TYPE type )
    {
        return mPicW[type];
    }
    //---------------------------------------------------------------------------------------
    MG::UInt HeadDamageResouce::getPicH( HEADDAMAGE_TYPE type )
    {
        return mPicH[type];
    }
    //---------------------------------------------------------------------------------------
    void HeadDamageResouce::getPicRecouse( HEADDAMAGE_TYPE type, UInt num, Bool isAdd, Str8& resouce, Str8& group, Char8* item, UInt& itemNum )
    {
        resouce = headDamageResouce[type-1];
        group = headDamageGroup[type-1];

        if ( isAdd )
            item[0] = '+';
        else
            item[0] = '-';

        Str8 tempNum;
        MGStrOp::toString(num, tempNum);

        UInt nCount = tempNum.length();
        for (UInt i=0; i<nCount; i++)
        {
            item[i+1] = tempNum[i];
        }

        itemNum = nCount +1;
    }
}
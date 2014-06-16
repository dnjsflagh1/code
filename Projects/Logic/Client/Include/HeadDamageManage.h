//***********************************************************************************************************
#ifndef _H_HEADDAMAGEMANAGE_
#define _H_HEADDAMAGEMANAGE_
//***********************************************************************************************************
#include "ClientPreqs.h"
//***********************************************************************************************************
namespace MG
{
    class HeadDamageResouce
    {
    public:
        HeadDamageResouce();
        ~HeadDamageResouce();
        SINGLETON_INSTANCE(HeadDamageResouce);

    public:
        UInt getPicW(HEADDAMAGE_TYPE type);
        UInt getPicH(HEADDAMAGE_TYPE type);
        void getPicRecouse( HEADDAMAGE_TYPE type, UInt num, Bool isAdd, Str8& resouce, Str8& group, Char8* item, UInt& itemNum );

    protected:
    private:
        UInt mPicW[HEADDAMAGE_TYPE_MAX];
        UInt mPicH[HEADDAMAGE_TYPE_MAX];
    };

    //***********************************************************************************************
    class HeadDamageManage
    {
    public: 
        HeadDamageManage();
        ~HeadDamageManage();
        SINGLETON_INSTANCE(HeadDamageManage);

    public:
        void addNum(Vec3 pos, Flt height, DamageType type, UInt num, Bool isAdd = true);
        void addMiss(Vec3 pos, Flt height);
        
        void update( Flt delta );

        void clearAllImage();

        void test( Flt delta, Vec3 pos );

    private:
        void clear();
        void worldPointToScreenPoint(Vec3 pos, VecI2& screenPos);
        void addNumPic(VecI2 pos, VecI2 size, UInt picNum, Str8 resouce, Str8 group, Char8* item);
        HEADDAMAGE_TYPE changeType( DamageType type );

    private:
        std::vector<HeadDamage*> mHeadDamageList;

        std::list<HeadDamage*> mHeadDamageListWork;
        std::list<HeadDamage*> mHeadDamageListFree;
    };
}
//***********************************************************************************************************
#endif
//***********************************************************************************************************
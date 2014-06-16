//***********************************************************************************************************
#ifndef _H_HEADDAMAGE_
#define _H_HEADDAMAGE_
//***********************************************************************************************************
namespace MG
{
    class HeadDamage
    {
    public: 
        HeadDamage(CoordI pos, Str8 Resouse, Str8 group, Str8 item);
        ~HeadDamage();

    public:
        void resetHeadDamage(CoordI pos, Str8 Resouse, Str8 group, Str8 item);
        void close();
        void update( Flt delta );
        Bool dead(){return mIsDead;}

    protected:
    private:
        Bool mIsDead;
        IImage* mImage;
        HEADDAMAGE_STATE mState;
        Vec2 mPos;
        Flt mSpeed;
        Flt mOffsetY;
        Flt mAlpha;
        Flt mMaxMoveHeight;
    };
}
//***********************************************************************************************************
#endif
//***********************************************************************************************************
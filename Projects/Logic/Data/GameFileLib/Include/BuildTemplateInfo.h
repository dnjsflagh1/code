#ifndef _BUILDINFO_H_
#define _BUILDINFO_H_

namespace MG
{
	/******************************************************************************/
	//建筑模板,对应策划文档
	/******************************************************************************/
	struct BuildTemplateInfo
	{
		UInt	id;				///	ID
		Str16	name;			///	名称,头衔
        U32     lvl;            /// 建筑初始等级
        U32     characterTempId;///角色模板ID
        UInt    artIconResId;   ///图标。
        UInt	artMeshResId;	///建筑的美术模型资源ID
		UInt	artMapResId;	///	建筑内部地图的美术资源ID
		UInt	audioResId;		///建筑播放的音乐资源ID   
		
		BuildTemplateInfo()
            :id(0)
            ,lvl(0)
            ,characterTempId(0)
            ,artIconResId(0)
            ,artMeshResId(0)
            ,artMapResId(0)
            ,audioResId(0)    
		{
		}
	};
	/******************************************************************************/
	//建筑模板集合
	/******************************************************************************/
	class BuildTemplateInfos
	{
	public:

		BuildTemplateInfos();
		~BuildTemplateInfos();
		SINGLETON_INSTANCE(BuildTemplateInfos)

    public:
		Bool											loadFile(CChar16* fileName);
        const BuildTemplateInfo*                        getBuildTemplateInfo(U32 buildTempID);
        Bool                                            getBuildTemplateInfo(U32 buildTempID, const BuildTemplateInfo*& info);

	protected:
		typedef std::map<UInt, BuildTemplateInfo*>::iterator	BuildInfoIt;

	private:
		std::map<UInt, BuildTemplateInfo*>						mBuildInfoList;
	};
}

#endif
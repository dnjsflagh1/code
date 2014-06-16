/******************************************************************************/
#ifndef _SCENEFILELOADER_H_
#define _SCENEFILELOADER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	struct BuildingInfoXml
	{
		Int				templateId;
		CHAR_BUILD_TYPE	buildingType;

		Vec3	pos;
		Vec3	dir;

		CharAppearType	appearType;
		

		BuildingInfoXml()
			:templateId(0)
			,buildingType(CHAR_BUILD_TYPE_NULL)
			,pos(0,0,0)
			,dir(0,0,-1)
			,appearType(CAT_ANY_SCENE)
		{

		}
	};

	struct CampInfoXml
	{
		Vec3	pos;
		Vec3	dir;

		Bool	isHeadQuarter;		//是否是【大本营】
		Int		templateId;

		CharAppearType	appearType;

		CampInfoXml()
			:pos(0,0,0)
			,dir(0,0,-1)
			,isHeadQuarter(false)
			,templateId(0)
			,appearType(CAT_ANY_SCENE)
		{

		}
	};


	struct ThirdPartCharacterInfoXml
	{
		Vec3 pos;
		Vec3 dir;

		Int charTemplateId;

		Vec3 posFront;		//根据pos计算出
		Vec3 posBack;

		ThirdPartCharacterInfoXml()
			:pos(0,0,0)
			,dir(0,0,-1)
			,charTemplateId(0)
			,posFront(0,0,0)
			,posBack(0,0,0)
		{

		}
	};

	struct MonsterInfoXml
	{
		Vec3 pos;
		Vec3 dir;

		Int charTemplateId;

		Vec3 posFront;		//根据pos计算出
		Vec3 posBack;

		CharAppearType	appearType;

		MonsterInfoXml()
			:pos(0,0,0)
			,dir(0,0,-1)
			,charTemplateId(0)
			,posFront(0,0,0)
			,posBack(0,0,0)
			,appearType(CAT_ANY_SCENE)
		{

		}
	};

	struct NPCInfoXml
	{
		Vec3 pos;
		Vec3 dir;

		Int charId;

		Vec3 posFront;		//根据pos计算出
		Vec3 posBack;

		NPCInfoXml()
			:pos(0,0,0)
			,dir(0,0,-1)
			,charId(0)
			,posFront(0,0,0)
			,posBack(0,0,0)
		{

		}
	};

	struct PlaceInfoXml
	{
		Vec3 pos;
		Vec3 dir;

		Vec3 posFront;		//根据pos计算出
		Vec3 posBack;

		PlaceInfoXml()
			:pos(0,0,0)
			,dir(0,0,-1)
			,posFront(0,0,0)
			,posBack(0,0,0)
		{

		}
	};

	struct StaticObjectXml
	{
		Vec3 pos;
		Vec3 dir;

		Vec3 posFront;		//根据pos计算出
		Vec3 posBack;

		StaticObjectXml()
			:pos(0,0,0)
			,dir(0,0,-1)
			,posFront(0,0,0)
			,posBack(0,0,0)
		{

		}
	};

	struct PointXml
	{
		Int PointId;
		Vec3 pos;
		Vec3 dir;

		PointXml()
			:pos(0,0,0)
			,PointId(0)
		{

		}
	};

	/******************************************************************************/
	class SceneFileObject
	{
	public:
		SceneFileObject();
		Int		id;
		Char16	pathName[MAX_ART_MAP_RES_PATH_NAME];
		
	public:
		void	addStaticList(StaticObjectXml* staticObj);
		void	addNormalJumpPos(PointXml* point);
		void	addTranslatePos(PointXml* point);
		void	addRelivePos(PointXml* point);

		void	addCampAttackPos(CampInfoXml* campInfo);
		void	addCampDefenserPos(CampInfoXml* campInfo);
		void	addAttackerGeneralPos(PointXml* point);
		void	addDefenserGeneralPos(PointXml* point);
		void	addAttackerTroopPos(PointXml* point);
		void	addDefenserTroopPos(PointXml* point);

		void	addAttackerCampBornPos(PointXml* point);
		void	addDefenserCampBornPos(PointXml* point);

		void	addAttackerGeneralRelivePos(PointXml* point);
		void	addDefenserGeneralRelivePos(PointXml* point);


		void	addThirdPartCharacter(ThirdPartCharacterInfoXml* thirdPartCharacter);
		void	addMonsterInfo(MonsterInfoXml* monster);
		void	addPlaceInfo(PlaceInfoXml* place);
		void	addNPCInfo(NPCInfoXml* npc);
		void	addBuildingInfo(BuildingInfoXml* building);

		//获取列表
		std::vector<ThirdPartCharacterInfoXml>* getThirdPartCharcterList()	{ return &thirdPartCharacterList; };
		std::vector<MonsterInfoXml>*			getMonsterList()			{ return &mMonsterList; };
		std::vector<BuildingInfoXml>*			getBuildingList()			{ return &mBuildingList;};


		//根据条件查找
		PointXml 		getRandAlivePoint();
		PointXml 		getRandNormalJumpPoint();

		PointXml		getCampaignCampPos(FORCE force, Int pointId);
		PointXml 		getCampaignTroopPos(FORCE force, Int pointId);



		//PointXml* 		getCampaignTroopPosByForce(FORCE force, Int index);
		//PointXml*		getCampaignGeneralPosByForce(FORCE force, Int index);

		PointXml		getCampaignCampPosByForce(FORCE force, Int index);

		

		//CampInfoXml*	getCampaignCampPosByForce(FORCE force, Int index);
		PointXml		getJumpPosFromSceneFileObj(JUMP_TYPE jumpType, Byte jumpIndex,Int pointId);

	private:
		void			getNormalJumpPointListByPointId(std::vector<PointXml>* outPointList, const Int pointId);

	private:
		std::vector<PointXml>					mRpgNormalJumpPos;				//调转地图时的坐标 JumpIn  JumpOut
		std::vector<PointXml>					mRpgTranslatePos;				//传送点
		std::vector<PointXml>					mRpgRelivePos;					//复活点

		std::vector<PointXml>					mSlgAttackerCampBornPos;		//攻击方军营出生点
		std::vector<PointXml>					mSlgAttackerGeneralPos;			//攻击方将领出生点列表
		std::vector<PointXml>					mSlgAttackerTroopBornPos;			//攻击方军队出生点列表
		std::vector<PointXml>					mSlgAttackerGeneralRelivePos;	//战场攻方将领复活点

		std::vector<PointXml>					mSlgDefenserCampBornPos;		//防守方军营出生点
		std::vector<PointXml>					mSlgDefenserGeneralBornPos;		//防守方将领出生点列表
		std::vector<PointXml>					mSlgDefenserTroopBornPos;		//防守方军队出生点列表
		std::vector<PointXml>					mSlgDefenserGeneralRelivePos;	//战场守方将领复活点

		std::vector<ThirdPartCharacterInfoXml>	thirdPartCharacterList;	//第三方角色列表
		std::vector<MonsterInfoXml>				mMonsterList;			//怪物列表
		std::vector<PlaceInfoXml>				mPlaceList;				//Place 列表
		std::vector<NPCInfoXml>					mNpcList;				//NPC列表
		std::vector<BuildingInfoXml>			mBuildingList;			//建筑列表

		//暂无用
		std::vector<StaticObjectXml>			mStaticList;				//Static 列表

		//准备删除
		std::vector<CampInfoXml>				campAttackerPos;		//攻击方军营出生点
		std::vector<CampInfoXml>				campDefenserPos;		//防守方军营出生点
	};


	/******************************************************************************/
	class SceneFileLoader
	{
	public:
		SceneFileLoader();
		~SceneFileLoader();
		SINGLETON_INSTANCE(SceneFileLoader);

		//读取【跳转点】列表
		SceneFileObject*	getSceneFileObjectByPath(CChar16* path);


	private:
		SceneFileObject*	findSceneFileObjectByPath(CChar16* path);

		void				loadSceneFile(CChar8* path, SceneFileObject* object);

		//Entity
		void				loadEntityGroup(XMLElement * groupElm, SceneFileObject* object);
		void				loadEntity(XMLElement * elm, SceneFileObject* object);

		Bool				isFocusEntityGroup(Str group);
		void				loadEntity(CharAppearType appearType,const Str& group, const Vec3& pos, const Vec4& orientation, std::map<Str,Str>& customAttr, SceneFileObject* object);

	private:
		typedef std::vector<SceneFileObject*>::iterator listSceneFileObjectIter;
		std::vector<SceneFileObject*> mListSceneFileObject;
		/// Xml文档对象.
        tinyxml2::XMLDocument*	mSceneXmlDoc;
	};


}	//namespace

#endif	//_SCENEFILELOADER_H_
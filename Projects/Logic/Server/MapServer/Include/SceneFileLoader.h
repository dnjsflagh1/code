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

		Bool	isHeadQuarter;		//�Ƿ��ǡ���Ӫ��
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

		Vec3 posFront;		//����pos�����
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

		Vec3 posFront;		//����pos�����
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

		Vec3 posFront;		//����pos�����
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

		Vec3 posFront;		//����pos�����
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

		Vec3 posFront;		//����pos�����
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

		//��ȡ�б�
		std::vector<ThirdPartCharacterInfoXml>* getThirdPartCharcterList()	{ return &thirdPartCharacterList; };
		std::vector<MonsterInfoXml>*			getMonsterList()			{ return &mMonsterList; };
		std::vector<BuildingInfoXml>*			getBuildingList()			{ return &mBuildingList;};


		//������������
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
		std::vector<PointXml>					mRpgNormalJumpPos;				//��ת��ͼʱ������ JumpIn  JumpOut
		std::vector<PointXml>					mRpgTranslatePos;				//���͵�
		std::vector<PointXml>					mRpgRelivePos;					//�����

		std::vector<PointXml>					mSlgAttackerCampBornPos;		//��������Ӫ������
		std::vector<PointXml>					mSlgAttackerGeneralPos;			//����������������б�
		std::vector<PointXml>					mSlgAttackerTroopBornPos;			//���������ӳ������б�
		std::vector<PointXml>					mSlgAttackerGeneralRelivePos;	//ս���������츴���

		std::vector<PointXml>					mSlgDefenserCampBornPos;		//���ط���Ӫ������
		std::vector<PointXml>					mSlgDefenserGeneralBornPos;		//���ط�����������б�
		std::vector<PointXml>					mSlgDefenserTroopBornPos;		//���ط����ӳ������б�
		std::vector<PointXml>					mSlgDefenserGeneralRelivePos;	//ս���ط����츴���

		std::vector<ThirdPartCharacterInfoXml>	thirdPartCharacterList;	//��������ɫ�б�
		std::vector<MonsterInfoXml>				mMonsterList;			//�����б�
		std::vector<PlaceInfoXml>				mPlaceList;				//Place �б�
		std::vector<NPCInfoXml>					mNpcList;				//NPC�б�
		std::vector<BuildingInfoXml>			mBuildingList;			//�����б�

		//������
		std::vector<StaticObjectXml>			mStaticList;				//Static �б�

		//׼��ɾ��
		std::vector<CampInfoXml>				campAttackerPos;		//��������Ӫ������
		std::vector<CampInfoXml>				campDefenserPos;		//���ط���Ӫ������
	};


	/******************************************************************************/
	class SceneFileLoader
	{
	public:
		SceneFileLoader();
		~SceneFileLoader();
		SINGLETON_INSTANCE(SceneFileLoader);

		//��ȡ����ת�㡿�б�
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
		/// Xml�ĵ�����.
        tinyxml2::XMLDocument*	mSceneXmlDoc;
	};


}	//namespace

#endif	//_SCENEFILELOADER_H_
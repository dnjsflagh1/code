
/******************************************************************************/
#ifndef __ITREE_H__
#define __ITREE_H__
/******************************************************************************/

#include "ISceneObject.h"

namespace MG
{

	struct TreeDeclaration 
	{
		U32		uId;
		Str		strName;
		Str		strPath;
		Flt		fLodStart;
		Flt		fLodEnd;
		Str		strNote;
	};
	
	struct GrassDeclaration
	{
		U32		uId;
		U32		uImageId;
		Str		strName;
		U32		uTotalRow;
		U32		uTotalCol;
		Flt		fWidth;
		Flt		fHeight;
		Flt		fWMin;
		Flt		fWMax;
		Flt		fHMin;
		Flt		fHMax;
		Flt		fRTWindWeight;		// right top
		Flt		fLTWindWeight;		// left top
		Flt		fLBWindWeight;		// left bottom
		Flt		fRBWindWeight;		// right bottom
		Str		strNote;
	};

	struct WorldEnvironment
	{
		WorldEnvironment()
		{
			vLightDir			= Vec3(1.f, 1.f, -1.f);
			cLightAmbient		= ColorSet::white();
			cLightDiffuse		= ColorSet::white();
			cLightSpecular		= ColorSet::white();
			cEmissive			= ColorSet::white();

			cGrassLightAmbient	= ColorSet::white();
			cGrassLightDiffuse	= ColorSet::white();
			cGrassLightSpecular	= ColorSet::white();
			cGrassEmissive		= ColorSet::white();

			cFogColor			= ColorSet::white();
			fFogStart			= 500.f;
			fFogEnd				= 5000.f;
		}

		// light
		Vec3	vLightDir;
		Color	cLightAmbient;
		Color	cLightDiffuse;
		Color	cLightSpecular;
		Color	cEmissive;

		//grass
		Color	cGrassLightAmbient;
		Color	cGrassLightDiffuse;
		Color	cGrassLightSpecular;
		Color	cGrassEmissive;

		// fog
		Color	cFogColor;
		Flt		fFogStart;
		Flt		fFogEnd;

		// shadow
	};
	
    /******************************************************************************/
    // ֲ������
    /******************************************************************************/
    class ITree : public ISceneObject
    {
	public:
		virtual UInt	getBaseTreeId() = 0;

		virtual	void	setReflect(Bool bReflect) = 0;

		virtual Bool	isNeedReflect() = 0;
    };

	class IGrass : public ISceneObject
	{
	public:
		virtual UInt	getBaseGrassId() = 0;

		virtual Flt		width() = 0;

		virtual void	width(Flt w) = 0;

		virtual Flt		height() = 0;

		virtual void	height(Flt h) = 0;
	};

    /******************************************************************************/
    // ֲ��������
    /******************************************************************************/
	class ITreeManager
	{
	public:
        
        // ���������
        virtual void							clear() = 0;

        // ����������
        virtual ITree*							createTree(CChar* name, U32 baseTreeID, const Vec3& pos) = 0;
        // ����������
		virtual ITree*							createTree(U32 baseTreeID, const Vec3& pos) = 0;

        // �õ�������
        virtual ITree*							getTree(CChar* name) = 0; 
        // ����������
        virtual void							destroyTree(CChar* name) = 0;
        // ����������
        virtual void							destroyAllTree() = 0;
		// ����������ɼ�����
		virtual void							setFarClipDistance(Flt farDistance) = 0;
		// �������绷��
		virtual void							setWorldEnv(const WorldEnvironment& env) = 0;
		//��ȡSpeedTree����
		virtual const WorldEnvironment&			getWorldEnv() = 0;
		// ������
		virtual	void							setFog(Color cFogColor,	Flt	fFogStart, Flt fFogEnd) = 0;

		/// �õ���ģ����������
		virtual UInt							getTreeDeclarationCount() = 0 ;
		/// �õ���ģ������
		virtual TreeDeclaration*				getTreeDeclarationByIndex( UInt index ) = 0 ;
		/// �õ�������ģ������
		virtual const std::map<MG::UInt, TreeDeclaration>& getTreeDeclMap() = 0;

		// �����ݶ���
		virtual IGrass*							createGrass(CChar* name, U32 textureID, const Vec3& vPos) = 0;
		// �����ݶ���
		virtual IGrass*							createGrass(U32 textureID, const Vec3& vPos) = 0;
		//
		virtual IGrass*							getGrass(CChar* name) = 0;
		// ���ò��Ŷ�λ�úͰ뾶
		virtual void							setGrassPerturbCircle(const Vec3& vPos, const Flt& radiu) = 0;
		// ���ٲݶ���
		virtual void							destroyGrass(CChar* name) = 0;
		// �������в�
		virtual void							destroyAllGrass() = 0;
		// ���²ݵ�Id
		virtual void							updateGrassIndex(Int iRow, Int iCol, UInt uGrassId) = 0;
		/// �õ�����ͼ��������
		virtual UInt							getGrassDeclarationCount() = 0 ;
		/// �õ�����ͼ����
		virtual GrassDeclaration*				getGrassDeclarationByIndex( UInt index ) = 0 ;
		/// �õ����в�ģ������
		virtual const std::map<MG::UInt, GrassDeclaration>& getGrassDeclMap() = 0;

		//���ط�
		virtual void							setWindEnable(Bool bEnable) = 0;

		//�Ƿ�����
		virtual Bool							isWindEnabled() = 0;

		//���÷��ǿ��
		virtual void							setGlobalWindStrength(Flt fStrength) = 0;
		//��ȡ���ǿ��
		virtual Flt								getGlobalWindStrength(void) const = 0;
		//���÷�ķ���
		virtual void							setGlobalWindDirection(Vec3& vDir) = 0;
		//��ȡ��ķ���
		virtual Vec3							getGlobalWindDirection(void) const = 0;

		//
		virtual Bool							EnableSpecularLight() = 0;

		//
		virtual void							EnableSpecularLight(Bool bEnable) = 0;

		//
		virtual Bool							EnableTransmissionLight() = 0;

		//
		virtual void							EnableTransmissionLight(Bool bEnable) = 0;

		//
		virtual Bool							EnableDetailLayer() = 0;

		//
		virtual void							EnableDetailLayer(Bool bEnable) = 0;

		//
		virtual Bool							EnableDetailNormalMap() = 0;

		//
		virtual void							EnableDetailNormalMap(Bool bEnable) = 0;

		//
		virtual Bool							EnableAmbientContrast() = 0;

		//
		virtual void							EnableAmbientContrast(Bool bEnable) = 0;

		virtual void							setGrassLod(Flt fStartFade, Flt fEndFade) = 0;

		virtual void							getGrassLod(Flt& fStartFade, Flt& fEndFade) = 0;
	};
}
#endif
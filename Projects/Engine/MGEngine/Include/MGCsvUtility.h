namespace MG
{
	/******************************************************************************/
	//引擎通用工具集
	/******************************************************************************/
	class MGCsvUtility
	{
	public:
		/******************************************************************************/
		//Vec3 CSV format
		/******************************************************************************/
		class CsvParseVec3
		{
		public:
			static Bool parse(Str16& src, Vec3& dest);
			static Bool write(Vec3& src, Str16& dest);
		};

		/******************************************************************************/
		//Vec3 CSV format
		/******************************************************************************/
		class CsvParseVec4
		{
		public:
			static Bool parse(Str16& src, Vec4& dest);
			static Bool write(Vec4& src, Str16& dest);
		};
		/******************************************************************************/
		//Color CSV format
		//Format:"r;g;b;a"
		/******************************************************************************/
		class CsvParseColor
		{
		public:
			static Bool parse(Str16& src, Color& dest);
			static Bool write(Color& src, Str16& dest);
		};
		/******************************************************************************/
		//Ambient CSV format
		//Format:"r;g;b;a"
		/******************************************************************************/
		class CsvParseAmbient : public CsvParseColor
		{
		};
		/******************************************************************************/
		//Diffuse CSV format
		//Format:"r;g;b;a"
		/******************************************************************************/
		class CsvParseDiffuse : public CsvParseColor
		{
		};
		/******************************************************************************/
		//Specular CSV format
		//Format:"r;g;b;a;shininess"
		/******************************************************************************/
		class CsvParseSpecular
		{
		public:
			static Bool parse(Str16& src, Color& destColor, Flt& destShininess);
			static Bool write(Color& src, Flt& destShininess, Str16& dest);
		};
		/******************************************************************************/
		//Culling CSV format
		//Format:"CullingHardWare;CullingSoftWare;"
		/******************************************************************************/
		class CsvParseCullingMode
		{
		public:
			static Bool parse(Str16& src, U8& CullingHardWare, U8& CullingSoftWare );
			static Bool write(U8& CullingHardWare, U8& CullingSoftWare, Str16& dest );
		};
		/******************************************************************************/
		//Alpha rejection CSV format
		//Format:"CullingHardWare;CullingSoftWare;"
		/******************************************************************************/
		class CsvParseAlphaRejection
		{
		public:
			static Bool parse(Str16& src, U8& alphaRejectionCmp, U8& alphaRejectionValue );
			static Bool write(U8& alphaRejectionCmp, U8& alphaRejectionValue, Str16& dest );
		};
		/******************************************************************************/
		//BlendMode CSV format
		//Format:"isUseBlendType;SceneBlendType;SceneBlendFactorSrc;SceneBlendFactorDest"
		/******************************************************************************/
		class CsvParseSceneBlendMode
		{
		public:
			static Bool parse(Str16& src, bool& isUseBlendType, U8& sceneBlendType, U8& sceneBlendFactorSrc, U8& sceneBlendFactorDest );
			static Bool write(bool& isUseBlendType, U8& sceneBlendType, U8& sceneBlendFactorSrc, U8& sceneBlendFactorDest, Str16& dest );
		};
	};
}

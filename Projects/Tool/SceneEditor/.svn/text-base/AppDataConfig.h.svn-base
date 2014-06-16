/******************************************************************************/
#ifndef AppDataConfig_h__
#define AppDataConfig_h__
#include <string>
/******************************************************************************/

/******************************************************************************/

namespace SceneEditor {

	///程序数据结构体
	struct AppData 
	{
		std::string		mapFilePath;
		bool            enableLightMap;
		unsigned int    shadowType;
		bool			receiveShadow;
		unsigned int	fogLevel;
	};

	///程序配置数据管理类
	//此类采用单件模式，通过getInstance函数获取句柄
	class AppDataManager
	{
	public:
		///获取管理器句柄
		static AppDataManager* getInstance();

		///释放管理器句柄
		static void destroyInstance();

		///获取地图文件路径
		std::string getMapFilePath();

		//保存地图文件路径
		void setMapFilePath(const std::string path);

		///查看是否启用光照贴图
		bool isLightMapEnbale();

		///启用光照贴图
		void setLightMapEnable(bool enable);

		///获取阴影类型
		unsigned int getShadowType();

		///设置阴影类型
		void setShadowType(unsigned int type);

		///查看是否开启阴影
		bool isReceiveShadow();

		///禁用地图阴影
		void setReceiveShadow(bool disable);

		///获取雾等级
		unsigned int getFogLevel();

		///设置雾等级
		void setFogLevel(unsigned int level);

		/////获取程序配置数据
		//AppData* getAppData();

		/////设置程序配置数据
		//void setAppData(AppData *data);

		///将程序数据保存到指定目录文件
		void saveToFile(const std::string fileName, const std::string path);

		///从文件中读取程序配置数据
		void loadFromFile(const std::string fileName, const std::string path);

	private:
		///构造函数,新建一个AppData结构体指针
		AppDataManager();

		///拷贝构造函数
		AppDataManager(const AppDataManager& mgr);

		////析构函数，释放AppData结构体
		~AppDataManager();

		///拷贝构造函数
		AppDataManager& operator=(const AppDataManager& mgr);


	private:
		static AppDataManager* instance;
		AppData* mAppData;     //程序配置数据
		std::string mFilePath; //配置文件路径
		std::string mFileName; //配置文件名
	};

}
/******************************************************************************/
#endif // AppDataConfig_h__
/******************************************************************************/
#ifndef AppDataConfig_h__
#define AppDataConfig_h__
#include <string>
/******************************************************************************/

/******************************************************************************/

namespace SceneEditor {

	///�������ݽṹ��
	struct AppData 
	{
		std::string		mapFilePath;
		bool            enableLightMap;
		unsigned int    shadowType;
		bool			receiveShadow;
		unsigned int	fogLevel;
	};

	///�����������ݹ�����
	//������õ���ģʽ��ͨ��getInstance������ȡ���
	class AppDataManager
	{
	public:
		///��ȡ���������
		static AppDataManager* getInstance();

		///�ͷŹ��������
		static void destroyInstance();

		///��ȡ��ͼ�ļ�·��
		std::string getMapFilePath();

		//�����ͼ�ļ�·��
		void setMapFilePath(const std::string path);

		///�鿴�Ƿ����ù�����ͼ
		bool isLightMapEnbale();

		///���ù�����ͼ
		void setLightMapEnable(bool enable);

		///��ȡ��Ӱ����
		unsigned int getShadowType();

		///������Ӱ����
		void setShadowType(unsigned int type);

		///�鿴�Ƿ�����Ӱ
		bool isReceiveShadow();

		///���õ�ͼ��Ӱ
		void setReceiveShadow(bool disable);

		///��ȡ��ȼ�
		unsigned int getFogLevel();

		///������ȼ�
		void setFogLevel(unsigned int level);

		/////��ȡ������������
		//AppData* getAppData();

		/////���ó�����������
		//void setAppData(AppData *data);

		///���������ݱ��浽ָ��Ŀ¼�ļ�
		void saveToFile(const std::string fileName, const std::string path);

		///���ļ��ж�ȡ������������
		void loadFromFile(const std::string fileName, const std::string path);

	private:
		///���캯��,�½�һ��AppData�ṹ��ָ��
		AppDataManager();

		///�������캯��
		AppDataManager(const AppDataManager& mgr);

		////�����������ͷ�AppData�ṹ��
		~AppDataManager();

		///�������캯��
		AppDataManager& operator=(const AppDataManager& mgr);


	private:
		static AppDataManager* instance;
		AppData* mAppData;     //������������
		std::string mFilePath; //�����ļ�·��
		std::string mFileName; //�����ļ���
	};

}
/******************************************************************************/
#endif // AppDataConfig_h__
#ifndef __EVENT_WIDGET_H__
#define __EVENT_WIDGET_H__

#include <QWidget>
#include "Define.h"
#include "ISceneObject.h"

class QString;
class QWidget;
class QTreeWidget;
class QTreeWidgetItem;

class QPushButton;

class ModelVisibleProWidget;
class ModelAniProWidget;
class ModelBindProWidget;

class PUStartProWidget;
class PUStopProWidget;
class PUBindProWidget;
class WeaponLightProWidget;
class EffectFadeProWidget;

class EventWidget : public QWidget
{
	Q_OBJECT
public:
	EventWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~EventWidget();

public:
	void					addNameToList(const std::string& name, const std::string& typeName);
	QTreeWidgetItem*		getCurrentItem();

	void					clear();

	void					setEventMap(std::map<std::string, std::string> eventmap);
private:
	void					createWidget();
	void					init();
	MG::SceneObjectTypes	getEventType(const std::string& eventName);

private slots:
	void					deleteClicked();
	void					changeSeleted(QTreeWidgetItem *item, int column);
private:
	QTreeWidget *mEventTreeWidget;
	QPushButton *mDeleteModelBtn;

	std::map<std::string, std::string> mEventNameList;

	QTreeWidgetItem* mSeletedItem;

	// PropertyWidget
	ModelVisibleProWidget*	mModelVisibleProWidget;
	ModelAniProWidget*		mModelAniProWidget;
	ModelBindProWidget*		mModelBindProWidget;

	PUStartProWidget*		mPUStartProWidget;
	PUStopProWidget*		mPUStopProWidget;
	PUBindProWidget*		mPUBindProWidget;

	WeaponLightProWidget*	mWeaponLightProWidget;
	EffectFadeProWidget*	mEffectFadeProWidget;
};

#endif
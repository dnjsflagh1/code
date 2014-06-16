#ifndef __WEAPON_LIGHT_PROPERTY_WIDGET_H__
#define __WEAPON_LIGHT_PROPERTY_WIDGET_H__

#include <QWidget>
#include "Define.h"

class QString;
class QWidget;
class QtProperty;
class QtTreePropertyBrowser;

class QtVariantPropertyManager;
class Vector3Manager;
class QtDoublePropertyManager;
class QtEnumPropertyManager;

class QtDoubleSpinBoxFactory;
class QtVariantEditorFactory;
class QtEnumEditorFactory;


class WeaponLightProWidget : public QWidget
{
	Q_OBJECT
public:
	WeaponLightProWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~WeaponLightProWidget();

public:
	void	loadElementProps(MG::IEffectObjectXmlFormat* format);

	void	clearElementProps();
private:
	void	createWidget();
	void	init();

	void	Weapon_Light_ProSet();

	void	setSeletedExModelIndex(QtProperty *pro, Str name);
	void	setSeletedEffectIndex(QtProperty *pro, Str name);
	private slots:
	void	enumValueChanged(QtProperty *, int);

	void	vector3ValueChanged(QtProperty *, const QVariant &);
	void	doubleValueChanged(QtProperty *, double);
private:
	QtTreePropertyBrowser *mPropertyBrw;

	QtDoublePropertyManager* mDoubleManager;
	QtEnumPropertyManager* mEnumManager;

	Vector3Manager    *mVector3Manager;
	QtVariantPropertyManager *mVarManVec;

	QtDoubleSpinBoxFactory *mDoubleSpinBoxFactory;
	QtVariantEditorFactory *mVariantEditFactory;
	QtEnumEditorFactory *mComboBoxFactory;

	///现在的XmlFormat对象
	IEffectObjectXmlFormat* mCurrObjectXmlFormat;

	/// 外部实体索引列表
	QStringList mExEntityIndexList;

	/// 特效名字列表
	QStringList mEffectList;

	unsigned int mCurrentEntityResID;
};

#endif
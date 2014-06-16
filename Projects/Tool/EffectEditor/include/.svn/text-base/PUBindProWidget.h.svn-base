#ifndef __PU_BIND_PROPERTY_WIDGET_H__
#define __PU_BIND_PROPERTY_WIDGET_H__

#include <QWidget>
#include "Define.h"

class QString;
class QWidget;
class QtProperty;
class QtTreePropertyBrowser;
class QtStringPropertyManager;
class QtBoolPropertyManager;
class QtVariantPropertyManager;
class QuaternionManager;
class Vector3Manager;
class QtDoublePropertyManager;
class QtEnumPropertyManager;

class QtLineEditFactory;
class QtCheckBoxFactory;
class QtDoubleSpinBoxFactory;
class QtVariantEditorFactory;
class QtEnumEditorFactory;


class PUBindProWidget : public QWidget
{
	Q_OBJECT
public:
	PUBindProWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~PUBindProWidget();

public:
	void	loadElementProps(MG::IEffectObjectXmlFormat* format);

	void	clearElementProps();
private:
	void	createWidget();
	void	init();

	void	PU_Bind_ProSet();

	void	setSeletedModelIndex(QtProperty *pro, Str name);
	void	setSeletedExModelIndex(QtProperty *pro, Str name);
	void	setSeletedEffectIndex(QtProperty *pro, Str name);
private slots:
	void	stringValueChanged(QtProperty *pro, const QString & proValue);
	void	boolValueChanged(QtProperty *pro, bool b);
	void	enumValueChanged(QtProperty *, int);

	void	quaternionValueChanged(QtProperty *, const QVariant &);
	void	vector3ValueChanged(QtProperty *, const QVariant &);
	void	doubleValueChanged(QtProperty *, double);
private:
	QtTreePropertyBrowser *mPropertyBrw;

	QtDoublePropertyManager* mDoubleManager;
	QtStringPropertyManager* mStringManager;
	QtBoolPropertyManager* mBoolManager;
	QtEnumPropertyManager* mEnumManager;

	QuaternionManager *mQuaternionManager;
	Vector3Manager    *mVector3Manager;
	QtVariantPropertyManager *mVarManQua;
	QtVariantPropertyManager *mVarManVec;

	QtLineEditFactory *mLineEditFactory;
	QtCheckBoxFactory *mCheckBoxFactory;
	QtDoubleSpinBoxFactory *mDoubleSpinBoxFactory;
	QtVariantEditorFactory *mVariantEditFactory;
	QtEnumEditorFactory *mComboBoxFactory;

	///现在的XmlFormat对象
	IEffectObjectXmlFormat* mCurrObjectXmlFormat;

	/// 实体名字列表
	QStringList mEntityList;

	/// 外部实体索引列表
	QStringList mExEntityIndexList;

	/// 特效名字列表
	QStringList mEffectList;

	unsigned int mCurrentEntityResID;
};

#endif
#ifndef __MODEL_ANIMATION_PRO_WIDGET_H__
#define __MODEL_ANIMATION_PRO_WIDGET_H__

#include <QWidget>
#include "Define.h"

class QString;
class QWidget;
class QtProperty;
class QtTreePropertyBrowser;
class QtStringPropertyManager;
class QtBoolPropertyManager;
class QtDoublePropertyManager;
class QtEnumPropertyManager;

class QtLineEditFactory;
class QtCheckBoxFactory;
class QtDoubleSpinBoxFactory;
class QtEnumEditorFactory;


class ModelAniProWidget : public QWidget
{
	Q_OBJECT
public:
	ModelAniProWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~ModelAniProWidget();

public:
	void	loadElementProps(MG::IEffectObjectXmlFormat* format);

	void	clearElementProps();
private:
	void	createWidget();
	void	init();

	void	Model_Animation_ProSet();

	void	setSeletedModelIndex(QtProperty *pro, Str name);
private slots:
	void	stringValueChanged(QtProperty *pro, const QString & proValue);
	void	boolValueChanged(QtProperty *pro, bool b);
	void	enumValueChanged(QtProperty *, int);
	void	doubleValueChanged(QtProperty *, double);
private:
	QtTreePropertyBrowser *mPropertyBrw;

	QtStringPropertyManager* mStringManager;
	QtDoublePropertyManager* mDoubleManager;
	QtEnumPropertyManager* mEnumManager;
	QtBoolPropertyManager* mBoolManager;

	QtLineEditFactory *mLineEditFactory;
	QtDoubleSpinBoxFactory *mDoubleSpinBoxFactory;
	QtEnumEditorFactory *mComboBoxFactory;
	QtCheckBoxFactory *mCheckBoxFactory;

	///现在的XmlFormat对象
	IEffectObjectXmlFormat* mCurrObjectXmlFormat;

	/// 实体名字列表
	QStringList mEntityList;

	//
	QStringList mAnimationList;

	unsigned int mCurrentEntityResID;
};

#endif
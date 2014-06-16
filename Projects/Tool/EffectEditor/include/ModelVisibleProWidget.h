#ifndef __MODEL_VISIBLE_PRO_WIDGET_H__
#define __MODEL_VISIBLE_PRO_WIDGET_H__

#include <QWidget>
#include "Define.h"

class QString;
class QWidget;
class QtProperty;
class QtTreePropertyBrowser;
class QtBoolPropertyManager;
class QtDoublePropertyManager;
class QtEnumPropertyManager;

class QtCheckBoxFactory;
class QtDoubleSpinBoxFactory;
class QtEnumEditorFactory;


class ModelVisibleProWidget : public QWidget
{
	Q_OBJECT
public:
	ModelVisibleProWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~ModelVisibleProWidget();

public:
	void	loadElementProps(MG::IEffectObjectXmlFormat* format);

	void	clearElementProps();
private:
	void	createWidget();
	void	init();

	void	Model_Visible_ProSet();
	void	setSeletedModelIndex(QtProperty *pro, Str name);
private slots:
	void	boolValueChanged(QtProperty *pro, bool b);
	void	enumValueChanged(QtProperty *, int);
	void	doubleValueChanged(QtProperty *, double);
private:
	QtTreePropertyBrowser *mPropertyBrw;

	QtDoublePropertyManager* mDoubleManager;
	QtEnumPropertyManager* mEnumManager;
	QtBoolPropertyManager* mBoolManager;

	QtDoubleSpinBoxFactory *mDoubleSpinBoxFactory;
	QtEnumEditorFactory *mComboBoxFactory;
	QtCheckBoxFactory *mCheckBoxFactory;

	///现在的XmlFormat对象
	IEffectObjectXmlFormat* mCurrObjectXmlFormat;

	/// 实体名字列表
	QStringList mEntityList;

	unsigned int mCurrentEntityResID;
};

#endif
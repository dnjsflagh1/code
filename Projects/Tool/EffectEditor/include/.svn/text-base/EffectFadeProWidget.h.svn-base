#ifndef __EFFECT_FADE_PRO_WIDGET_H__
#define __EFFECT_FADE_PRO_WIDGET_H__

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


class EffectFadeProWidget : public QWidget
{
	Q_OBJECT
public:
	EffectFadeProWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~EffectFadeProWidget();

public:
	void	loadElementProps(MG::IEffectObjectXmlFormat* format);

	void	clearElementProps();
private:
	void	createWidget();
	void	init();

	void	Effect_Fade_ProSet();
	void	setSeletedEffectIndex(QtProperty *pro, Str name);

private slots:
	void	enumValueChanged(QtProperty *, int);
	void	doubleValueChanged(QtProperty *, double);
private:
	QtTreePropertyBrowser *mPropertyBrw;

	QtDoublePropertyManager* mDoubleManager;
	QtEnumPropertyManager* mEnumManager;

	QtDoubleSpinBoxFactory *mDoubleSpinBoxFactory;
	QtEnumEditorFactory *mComboBoxFactory;

	///现在的XmlFormat对象
	IEffectObjectXmlFormat* mCurrObjectXmlFormat;

	/// PU名字列表
	QStringList mEffectList;
};

#endif
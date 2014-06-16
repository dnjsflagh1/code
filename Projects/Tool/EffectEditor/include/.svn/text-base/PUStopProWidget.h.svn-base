#ifndef __PU_STOP_PRO_WIDGET_H__
#define __PU_STOP_PRO_WIDGET_H__

#include <QWidget>
#include "Define.h"

class QString;
class QWidget;
class QtProperty;
class QtTreePropertyBrowser;

class QtDoublePropertyManager;
class QtEnumPropertyManager;

class QtDoubleSpinBoxFactory;
class QtEnumEditorFactory;


class PUStopProWidget : public QWidget
{
	Q_OBJECT
public:
	PUStopProWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~PUStopProWidget();

public:
	void	loadElementProps(MG::IEffectObjectXmlFormat* format);

	void	clearElementProps();
private:
	void	createWidget();
	void	init();

	void	PU_Stop_ProSet();
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

	/// 实体名字列表
	QStringList mEffectList;

	unsigned int mCurrentEntityResID;
};

#endif
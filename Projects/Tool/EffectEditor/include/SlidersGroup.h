#ifndef __SLIDERSGROUP__H__
#define __SLIDERSGROUP__H__

#include <QGroupBox>

QT_BEGIN_NAMESPACE
class QDial;
class QScrollBar;
class QSlider;
QT_END_NAMESPACE

class SlidersGroup : public QGroupBox
{
    Q_OBJECT

public:
    SlidersGroup(Qt::Orientation orientation, const QString &title,
                 QWidget *parent = 0);

signals:
    void valueChanged(int value);

public slots:
    void setValue(int value);
    void setMinimum(int value);
    void setMaximum(int value);
	void setPosition(int value);

private:
    QSlider *slider;
    //QScrollBar *scrollBar;
    //QDial *dial;
};

#endif

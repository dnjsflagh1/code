#include <QtGui>

#include "SlidersGroup.h"

SlidersGroup::SlidersGroup(Qt::Orientation orientation, const QString &title,
                           QWidget *parent)
    : QGroupBox(title, parent)
{
    slider = new QSlider(orientation);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(10);
    slider->setSingleStep(1);

    //scrollBar = new QScrollBar(orientation);
    //scrollBar->setFocusPolicy(Qt::StrongFocus);

    //dial = new QDial;
    //dial->setFocusPolicy(Qt::StrongFocus);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setPosition(int)));
    //connect(scrollBar, SIGNAL(valueChanged(int)), dial, SLOT(setValue(int)));
    //connect(dial, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    //connect(dial, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    QBoxLayout::Direction direction;

    if (orientation == Qt::Horizontal)
        direction = QBoxLayout::TopToBottom;
    else
        direction = QBoxLayout::LeftToRight;

    QBoxLayout *slidersLayout = new QBoxLayout(direction);
    slidersLayout->addWidget(slider);
    //slidersLayout->addWidget(scrollBar);
    //slidersLayout->addWidget(dial);
    setLayout(slidersLayout);
}

void SlidersGroup::setValue(int value)
{
    slider->setValue(value);
}

void SlidersGroup::setMinimum(int value)
{
    slider->setMinimum(value);
    //scrollBar->setMinimum(value);
    //dial->setMinimum(value);
}

void SlidersGroup::setMaximum(int value)
{
    slider->setMaximum(value);
    //scrollBar->setMaximum(value);
    //dial->setMaximum(value);
}

void SlidersGroup::setPosition( int value )
{
	valueChanged(value);
}
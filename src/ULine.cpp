//
// Created by kolya on 9/24/2021.
//

#include "ULine.h"
#include "QPainter"

ULine::ULine(QObject* parent, ELineAlgorithm algorithm)
    :QObject(parent),
    m_Algorithm(algorithm)
{

}

void ULine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::black);
    painter->drawPoint(10, 10);
    painter->drawPoint(11, 10);
    painter->drawPoint(12, 10);
    painter->drawPoint(13, 10);
    painter->drawPoint(14, 10);
    painter->drawPoint(15, 10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF ULine::boundingRect() const
{
    return {0, 0, 100, 100};
}

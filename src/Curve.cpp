//
// Created by kolya on 11/8/2021.
//

#include "Curve.h"

Curve::Curve(QObject *parent, ECurveAlgo algorithm)
    :QObject(parent),
    m_Algorithm(algorithm)
{

}


void Curve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF Curve::boundingRect() const
{
    return QRectF();
}

void Curve::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if (!m_IsMovingNow)
    {

    }
}

void Curve::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

    if (m_IsMovingNow)
    {

    }
}

void Curve::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    if (m_IsMovingNow)
    {

    }
}

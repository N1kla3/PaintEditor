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

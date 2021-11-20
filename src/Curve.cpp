//
// Created by kolya on 11/8/2021.
//

#include "Curve.h"
#include "QGraphicsSceneMouseEvent"
#include "QPainter"
#include "Matrix.h"
#include "GlobalShit.h"

Curve::Curve(QObject *parent, ECurveAlgo algorithm)
    :QObject(parent),
    m_Algorithm(algorithm),
    m_Points({{-10,-10},
              {-10, 10},
              {10, 10},
              {10, -10}})
{
    acceptHoverEvents();
}


void Curve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    prepareGeometryChange();
    auto prev = m_Points[3];
    for (auto point: m_Points)
    {
        painter->drawEllipse(point, 5, 5);
        painter->drawLine(prev, point);
        prev = point;
    }

    if (m_Algorithm == ECurveAlgo::ERMIT)
    {
        static const ::matrix<float> mat{{{2, -3, 0, 1},
                                         {-2, 3, 0, 0},
                                         {1, -2, 1, 0},
                                         {1, -1, 0, 0}}};
        //::matrix<float> final_matrix = mat * ::matrix<float>{{}};

    }
    else if (m_Algorithm == ECurveAlgo::BEZJE)
    {

    }
    else if (m_Algorithm == ECurveAlgo::SPLINE)
    {

    }
}

QRectF Curve::boundingRect() const
{
    return QRectF(-1000, -1000, 2000, 2000);
}

void Curve::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // CALL SUPER WILL CONSUME ALL NEXT EVENTS!!!!! to that item
    VERBOSE();

    if (!m_IsMovingNow)
    {
        m_MovingIndex = getPointFromLocation(event->scenePos());
        if (m_MovingIndex >= 0)
        {
            m_IsMovingNow = true;
        }
    }
}

void Curve::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

    if (m_IsMovingNow)
    {
        m_Points[m_MovingIndex] = event->pos();
    }
}

void Curve::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    VERBOSE();
    QGraphicsItem::mouseReleaseEvent(event);

    if (m_IsMovingNow)
    {
        m_IsMovingNow = false;
    }
}

int Curve::getPointFromLocation(QPointF point)
{
    for (int index = 0; index < 4; index++)
    {
        auto rect = QRectF{pos() + (m_Points[index] - QPoint(5,5)), QSizeF{10, 10}};
        if (rect.contains(point))
        {
            return index;
        }
    }
    return -1;
}

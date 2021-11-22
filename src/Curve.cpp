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
    m_Algorithm(algorithm)
{
    m_Points = {{-10,-10},
                {-10, 10},
                {10, 10},
                {10, -10}};
    acceptHoverEvents();
}


void Curve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    prepareGeometryChange();
    auto prev = m_Points[3];
    auto index = 1;
    for (auto point: m_Points)
    {
        painter->setPen(Qt::black);
        painter->drawEllipse(point, 5, 5);
        painter->drawLine(prev, point);
        painter->setPen(Qt::red);
        painter->drawText(point - QPoint(5, -5), QString::number(index));
        prev = point;
        index++;
    }

    if (m_Algorithm == ECurveAlgo::ERMIT)
    {
        //const ::matrix<float> mat{{{2, -3, 0, 1},
        //                                 {-2, 3, 0, 0},
        //                                 {1, -2, 1, 0},
        //                                 {1, -1, 0, 0}}};
        const ::matrix<float> mat{{{2, -2, 1, 1},
                                   {-3, 3, -2, -1},
                                   {0, 0, 1, 0},
                                   {1, 0, 0, 0}}};
        //::matrix<float> final_matrix = mat * ::matrix<float>{{{static_cast<float>(m_Points[0].x()), static_cast<float>(m_Points[0].y())},
        //                                                      {static_cast<float>(m_Points[3].x()), static_cast<float>(m_Points[3].y())},
        //                                                      {0, 1},
        //                                                      {1, 0}}};
        ::matrix<float> final_matrix = mat * ::matrix<float>{{{0, 0},
                                                              {1, 0},
                                                              {0, 1},
                                                              {1, 0}}};

        float max_diff = abs(m_Points[3].x() - m_Points[0].x());
        float step = 1 / max_diff;
        float t = 0;
        for (int pixel_step = 0; pixel_step < max_diff; pixel_step++)
        {
            t += step;
            ::matrix<float> step_matrix{{{t*t*t, t*t, t, 1}}};
            ::matrix<float> point = step_matrix * final_matrix;
            float first_coff = point.mat[0][0];
            float second_coff = point.mat[0][1];
            painter->drawPoint(pixel_step, second_coff * max_diff);
        }
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
        if (m_MovingIndex == 0)
        {
            setPos(event->scenePos());
            return;
        }
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

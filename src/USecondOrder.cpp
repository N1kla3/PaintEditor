//
// Created by kolya on 10/23/2021.
//

#include "USecondOrder.h"
#include "MainWindow.h"
#include "QPainter"

USecondOrder::USecondOrder(QObject *parent, ESecondOrderShape shapeType)
        :QObject(parent),
         m_ShapeType(shapeType)
{

}

void USecondOrder::SetupShape(QPoint start, QPoint end)
{
    m_Start = start;
    m_End = end;

    if (MainWindow::Window->DebugMode)
    {
        m_StartedWithDebug = true;
        connect(MainWindow::Window, &MainWindow::DebugIteration, [this](){
            debug_counter++;
            ENABLE_DEBUG_PRINT = true;
        });
    }
}

void USecondOrder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //TODO: remove
    painter->setPen(Qt::red);
    painter->drawRect(boundingRect());

    painter->setPen(Qt::black);
    if (m_ShapeType == ESecondOrderShape::CIRCLE)
    {
        float radius = sqrt(pow((m_Start.x() - m_End.x()), 2.f) + pow((m_Start.y() - m_End.y()), 2.f));
        float p = 0;
        float q = radius;
        float d = 3 - 2*radius;
        while (p <= q)
        {
            DrawCircle(painter, 0, 0, p, q);
            p++;
            if (d < 0)
            {
                d = d + 4.f * p + 6.f;
            }
            else
            {
                radius--;
                q = radius;
                d = d + 4.f * (p - q) + 10.f;
            }
        }
        DrawCircle(painter, 0, 0, p, q);
    }
    else if (m_ShapeType == ESecondOrderShape::ELLIPSE)
    {
        float rx = abs(m_Start.x() - m_End.x());
        float ry = abs(m_Start.y() - m_End.y());

        float x = 0;
        float y = ry;

        float d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx *rx);
        float dx = 2 * ry * ry * x;
        float dy = 2 * rx * rx * y;

        while (dx < dy)
        {
            painter->drawPoint(x, y);
            painter->drawPoint(-x, y);
            painter->drawPoint(x, -y);
            painter->drawPoint(-x, -y);
            if (d1 < 0)
            {
                x++;
                dx = dx + (2 * ry * ry);
                d1 = d1 + dx + (ry * ry);
            }
            else
            {
                x++;
                y--;
                dx = dx + (2 * ry * ry);
                dy = dy - (2 * rx * rx);
                d1 = d1 + dx - dy + (ry * ry);
            }
        }

        float d2 = ((ry * ry) * ((x + 0.5f) * (x + 0.5f))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

        while (y >= 0)
        {
            painter->drawPoint(x, y);
            painter->drawPoint(-x, y);
            painter->drawPoint(x, -y);
            painter->drawPoint(-x, -y);
            if (d2 > 0)
            {
                y--;
                dy = dy - (2 * rx * rx);
                d2 = d2 + (rx * rx) - dy;
            }
            else
            {
                y--;
                x++;
                dx = dx + (2 * ry * ry);
                dy = dy - (2 * rx * rx);
                d2 = d2 + dx - dy + (rx * rx);
            }
        }
    }
    else if (m_ShapeType == ESecondOrderShape::PARABOLA)
    {

    }
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QRectF USecondOrder::boundingRect() const
{
    if (m_ShapeType == ESecondOrderShape::CIRCLE)
    {
        float a = pow(m_Start.x() - m_End.x(), 2.f);
        float b = pow(m_Start.y() - m_End.y(), 2.f);
        float radius = sqrt(a + b);
        QRectF result(-radius, -radius, 2*radius, 2*radius);
        return result;
    }
    else if (m_ShapeType == ESecondOrderShape::ELLIPSE)
    {
        QPoint point = m_End - m_Start;
        QRectF result(-abs(point.x()), -abs(point.y()), 2*abs(point.x()), 2*abs(point.y()));
        return result;
    }
}

void USecondOrder::DrawCircle(QPainter* painter, float x, float y, float p, float q)
{
    painter->drawPoint(x + p, y + q);
    painter->drawPoint(x - p, y + q);
    painter->drawPoint(x + p, y - q);
    painter->drawPoint(x - p, y - q);
    painter->drawPoint(x + q, y + p);
    painter->drawPoint(x - q, y + p);
    painter->drawPoint(x + q, y - p);
    painter->drawPoint(x - q, y - p);
}

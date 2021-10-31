//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21

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
        /*
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
        */
        float radius = sqrt(pow((m_Start.x() - m_End.x()), 2.f) + pow((m_Start.y() - m_End.y()), 2.f));

        float x = 0;
        float y = radius;

        float delta = 2 - 2 * radius;
        float border = 0;

        painter->drawPoint(x, y);
        painter->drawPoint(-x, y);
        painter->drawPoint(x, -y);
        painter->drawPoint(-x, -y);
        while (y > border)
        {
            if (delta < 0)
            {
                x++;
                delta += 2*x + 1;
            }
            else
            {
                y--;
                delta += -2*y + 1;
            }
            painter->drawPoint(x, y);
            painter->drawPoint(-x, y);
            painter->drawPoint(x, -y);
            painter->drawPoint(-x, -y);
        }
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
    else if (m_ShapeType == ESecondOrderShape::HYPERBOLA)
    {

        float focus = abs(m_Start.x() - m_End.x());
        float a = focus;
        float b = abs(m_Start.y() - m_End.y());

        float x = focus;
        float y = 0;

        float delta = (focus * focus) - (b * b) + 2 * focus * b * b;

        painter->drawPoint(x, y);
        painter->drawPoint(-x, y);
        painter->drawPoint(x, -y);
        painter->drawPoint(-x, -y);
        while (y < b)
        {
            if (delta < 0)
            {
                x++;
                delta += 2 * x * b * b + b * b;
            }
            else
            {
                y++;
                delta += -(2 * y * a * a) - a * a;
            }
            painter->drawPoint(x, y);
            painter->drawPoint(-x, y);
            painter->drawPoint(x, -y);
            painter->drawPoint(-x, -y);
        }

    }
    else if (m_ShapeType == ESecondOrderShape::PARABOLA)
    {
        float p = abs(m_Start.x() - m_End.x());

        float x = 0;
        float y = 0;

        float delta = 2 * p - 1;

        painter->drawPoint(x, y);
        painter->drawPoint(-x, y);
        painter->drawPoint(x, -y);
        painter->drawPoint(-x, -y);
        while (x < 2 * p)
        {
            if (delta < 0)
            {
                x++;
                delta += 2 * p;
            }
            else
            {
                y++;
                delta += -(2 * y) - 1;
            }
            painter->drawPoint(x, y);
            painter->drawPoint(-x, y);
            painter->drawPoint(x, -y);
            painter->drawPoint(-x, -y);
        }
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
    else if (m_ShapeType == ESecondOrderShape::HYPERBOLA)
    {
        QPoint point = m_End - m_Start;
        QRectF result(-abs(2*point.x()), -abs(point.y()), 4*abs(point.x()), 2*abs(point.y()));
        return result;
    }
    else
    {
        QPoint point = m_End - m_Start;
        QRectF result(-abs(2.5f*point.x()), -2.25f*abs(point.x()), 5*abs(point.x()), 4.5f*abs(point.x()));
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

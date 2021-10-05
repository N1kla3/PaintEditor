//
// Created by kolya on 9/24/2021.
//

#include "ULine.h"
#include "QPainter"
#include "GlobalShit.h"
#include "MainWindow.h"

ULine::ULine(QObject* parent, ELineAlgorithm algorithm)
    :QObject(parent),
    m_Algorithm(algorithm)
{

}

void ULine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::black);

    prepareGeometryChange();
    if (m_Algorithm == ELineAlgorithm::DDA)
    {
        QPoint Diff = m_End - m_Start;
        int len = std::max(std::abs(Diff.x()), std::abs(Diff.y()));
        float dx = float(Diff.x()) / len;
        float dy = float(Diff.y()) / len;

        float x = 0;
        float y = 0;
        for (int i = 0; i < len; i++)
        {
            x = x + dx;
            y = y + dy;
            QPoint point{int(x), int(y)};
            m_LineRepresentation.push_back(point);
            painter->drawPoint(point);

            if (m_StartedWithDebug)
            {
                if (debug_counter == len || !MainWindow::Window->DebugMode)
                {
                    m_StartedWithDebug = false;
                }
                if (i == debug_counter) break;
            }
        }
    }
    else if (m_Algorithm == ELineAlgorithm::BRASENHAME)
    {
        // primary is the longest axis value
        QPoint Diff = m_End - m_Start;
        float delta_primary = std::abs(Diff.x()) >= std::abs(Diff.y()) ? Diff.x() : Diff.y();
        float delta_secondary = std::abs(Diff.y()) > std::abs(Diff.x()) ? Diff.x() : Diff.y();
        float e = delta_secondary / delta_primary - 0.5f;

        float primary = 0;
        float secondary = 0;
        float primary_grow = delta_primary > 0 ? 1 : -1;
        float secondary_grow = delta_secondary > 0 ? 1 : -1;
        for (int i = 0; i <= std::abs(delta_primary); i++)
        {
            if (e >= 0)
            {
                secondary += secondary_grow;
                e--;
            }
            primary += primary_grow;
            e = e + std::abs(delta_secondary / delta_primary);
            QPoint res = std::abs(Diff.x()) >= std::abs(Diff.y()) ? QPoint{int(primary), int(secondary)} : QPoint{int(secondary), int(primary)};
            m_LineRepresentation.push_back(res);
            painter->drawPoint(res);
            if (m_StartedWithDebug)
            {
                if (debug_counter == std::abs(delta_primary) || !MainWindow::Window->DebugMode)
                {
                    m_StartedWithDebug = false;
                }
                if (i == debug_counter) break;
            }
        }
    }
    else if (m_Algorithm == ELineAlgorithm::WU)
    {
        // primary is the longest axis value
        QPoint Diff = m_End - m_Start;
        float delta_primary = std::abs(Diff.x()) >= std::abs(Diff.y()) ? Diff.x() : Diff.y();
        float delta_secondary = std::abs(Diff.y()) > std::abs(Diff.x()) ? Diff.x() : Diff.y();
        float e = delta_secondary / delta_primary - 0.5f;

        float primary = 0;
        float secondary = 0;
        float primary_grow = delta_primary > 0 ? 1 : -1;
        float secondary_grow = delta_secondary > 0 ? 1 : -1;
        int increment = delta_secondary >= 0.f ? -1 : 1;
        for (int i = 0; i <= std::abs(delta_primary); i++)
        {
            if (e >= 0)
            {
                secondary += secondary_grow;
                e--;
            }

            primary += primary_grow;
            e = e + std::abs(delta_secondary / delta_primary);

            int new_color = 255 * (std::abs(e) - std::abs(int(e)));
            painter->setPen(QColor(new_color, new_color, new_color));
            QPoint res = std::abs(Diff.x()) >= std::abs(Diff.y()) ? QPoint{int(primary), int(secondary)} : QPoint{int(secondary), int(primary)};
            m_LineRepresentation.push_back(res);
            painter->drawPoint(res);
            if (i != 0 && i != std::abs(delta_primary))
            {
                new_color = 255 * (1 - (std::abs(e) - std::abs(int(e))));
                painter->setPen(QColor(new_color, new_color, new_color));
                int new_increment = e >= 0 ? increment * -1 : increment;
                QPoint res = std::abs(Diff.x()) >= std::abs(Diff.y()) ? QPoint{int(primary), int(secondary) + new_increment} : QPoint{int(secondary) + new_increment, int(primary)};
                m_LineRepresentation.push_back(res);
                painter->drawPoint(res);
            }
            if (m_StartedWithDebug)
            {
                if (debug_counter == std::abs(delta_primary) || !MainWindow::Window->DebugMode)
                {
                    m_StartedWithDebug = false;
                }
                if (i == debug_counter) break;
            }
        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF ULine::boundingRect() const
{
    int deltaY = m_End.y() - m_Start.y();
    int deltaX = m_End.x() - m_Start.x();
    int aleft = deltaX > 0 ? 0 : deltaX;
    int atop = deltaY > 0 ? 0 : deltaY;
    QRectF result(aleft, atop, std::abs(deltaX), std::abs(deltaY));
    return result;
}

void ULine::SetupLine(QPoint start, QPoint end)
{
    m_Start = start;
    m_End = end;
    m_Angle = AngleBetweenPoints(start, end);

    if (MainWindow::Window->DebugMode)
    {
        m_StartedWithDebug = true;
        connect(MainWindow::Window, &MainWindow::DebugIteration, [this](){
            debug_counter++;
        });
    }
}

float ULine::AngleBetweenPoints(QPoint first, QPoint second)
{
    //Make point1 the origin, make point2 relative to the origin so we do point1 - point1, and point2-point1,
    //since we dont need point1 for the equation to work, the equation works correctly with the origin 0,0.
    int deltaY = second.y() - first.y();
    int deltaX = second.x() - first.x(); //Vector 2 is now relative to origin, the angle is the same, we have just transformed it to use the origin.

    float angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.141;

    angleInDegrees *= -1; // Y axis is inverted in computer windows, Y goes down, so invert the angle.

    //Angle returned as:
    //                      90
    //            135                45
    //
    //       180          Origin           0
    //
    //           -135                -45
    //
    //                     -90

    return angleInDegrees;
}

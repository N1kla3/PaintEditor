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
    painter->drawPoint(1, 1);

    prepareGeometryChange();
    if (m_Algorithm == ELineAlgorithm::DDA)
    {
        QPoint Diff = m_End - m_Start;
        int len = std::max(Diff.x(), Diff.y());
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
        }
    }
    else if (m_Algorithm == ELineAlgorithm::BRASENHAME)
    {

    }
    else if (m_Algorithm == ELineAlgorithm::WU)
    {

    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF ULine::boundingRect() const
{
    return QRectF(QPointF{0, 0}, QPointF{100, 100});
}

void ULine::SetupLine(QPoint start, QPoint end)
{
    m_Start = start;
    m_End = end;
}

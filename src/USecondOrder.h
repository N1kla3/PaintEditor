//
// Created by kolya on 10/23/2021.
//

#pragma once

#include <QGraphicsItem>

enum class ESecondOrderShape
{
    CIRCLE,
    ELLIPSE,
    HYPERBOLA,
    PARABOLA
};

class USecondOrder : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit USecondOrder(QObject* parent = nullptr, ESecondOrderShape shapeType = ESecondOrderShape::CIRCLE);

    void SetupShape(QPoint start, QPoint end);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    virtual QRectF boundingRect() const override;

private:
    void DrawCircle(QPainter* painter, float x, float y, float p, float q);
    ESecondOrderShape m_ShapeType;

    QPoint m_Start;
    QPoint m_End;

    bool m_StartedWithDebug = false;
    bool ENABLE_DEBUG_PRINT = false;
    int debug_counter = 1;

    QVector<QPoint> m_ShapePixels;
};



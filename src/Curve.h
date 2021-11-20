//
// Created by kolya on 11/8/2021.
//

#pragma once

#include <QObject>
#include <QGraphicsItem>

enum class ECurveAlgo
{
    ERMIT,
    BEZJE,
    SPLINE
};

class Curve : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Curve(QObject* parent = nullptr, ECurveAlgo algorithm = ECurveAlgo::ERMIT);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    virtual QRectF boundingRect() const override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int getPointFromLocation(QPointF point);

    int m_MovingIndex;

    ECurveAlgo m_Algorithm;

    std::vector<QPointF> m_Points;

    bool m_IsMovingNow = false;

    bool m_StartedWithDebug = false;
    bool ENABLE_DEBUG_PRINT = false;
    int debug_counter = 1;

    QVector<QPoint> m_LineRepresentation;
};



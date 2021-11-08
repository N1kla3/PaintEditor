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

private:
    ECurveAlgo m_Algorithm;

    bool m_StartedWithDebug = false;
    bool ENABLE_DEBUG_PRINT = false;
    int debug_counter = 1;

    QVector<QPoint> m_LineRepresentation;
};



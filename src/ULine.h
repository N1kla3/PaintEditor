//
// Created by kolya on 9/24/2021.
//

#pragma once

#include <QObject>
#include <QGraphicsItem>

enum class ELineAlgorithm
{
    DDA,
    BRASENHAME,
    WU
};

class ULine : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    ULine(QObject* parent = nullptr, ELineAlgorithm algorithm = ELineAlgorithm::DDA);

    void SetupLine(QPoint start, QPoint end);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    virtual QRectF boundingRect() const override;

private:
    ELineAlgorithm m_Algorithm;

    QPoint m_Start;
    QPoint m_End;
};



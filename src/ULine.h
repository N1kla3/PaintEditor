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
    explicit ULine(QObject* parent = nullptr, ELineAlgorithm algorithm = ELineAlgorithm::DDA);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    ELineAlgorithm m_Algorithm;
};



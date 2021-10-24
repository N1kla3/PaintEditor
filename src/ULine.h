//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21

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

    void SetupLine(QPoint start, QPoint end);

    static float AngleBetweenPoints(QPoint first, QPoint second);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    virtual QRectF boundingRect() const override;

private:
    ELineAlgorithm m_Algorithm;

    QPoint m_Start;
    QPoint m_End;

    bool m_StartedWithDebug = false;
    bool ENABLE_DEBUG_PRINT = false;
    int debug_counter = 1;

    QVector<QPoint> m_LineRepresentation;
};



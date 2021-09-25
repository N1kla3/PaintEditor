//
// Created by kolya on 9/25/2021.
//

#pragma once

#include <QWeakPointer>

class QGraphicsScene;
class QGraphicsItem;
enum class ELineAlgorithm;

class DrawManager
{
public:
    explicit DrawManager(const QSharedPointer<QGraphicsScene>& scene);

    QGraphicsItem* DrawLine(QPoint start, QPoint end, ELineAlgorithm algorithm);

private:
    QWeakPointer<QGraphicsScene> m_Scene;
};



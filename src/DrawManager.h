//
// Created by kolya on 9/25/2021.
//

#pragma once

#include <QWeakPointer>
#include <memory>
#include "Mode.h"

class QGraphicsScene;
class QGraphicsItem;
enum class ELineAlgorithm;

class DrawManager
{
public:
    explicit DrawManager(const QSharedPointer<QGraphicsScene>& scene);

    QGraphicsItem* DrawLine(QPoint start, QPoint end, ELineAlgorithm algorithm);

    void SetMode(Mode* newMode);

private:

    std::unique_ptr<Mode> m_Mode;

    QWeakPointer<QGraphicsScene> m_Scene;
};



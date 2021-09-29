//
// Created by kolya on 9/25/2021.
//

#pragma once

#include <QWeakPointer>
#include <memory>
#include <QPointer>
#include "Mode.h"

class QGraphicsScene;
class QGraphicsItem;
enum class ELineAlgorithm;

class DrawManager
{
public:
    explicit DrawManager(const QSharedPointer<QGraphicsScene>& scene);

    void SetMode(Mode* newMode);

private:

    QPointer<Mode> m_Mode;

    QWeakPointer<QGraphicsScene> m_Scene;
};



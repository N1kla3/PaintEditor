//
// Created by kolya on 9/25/2021.
//

#pragma once

#include <QWeakPointer>

class QGraphicsScene;

class DrawManager
{
public:
    explicit DrawManager(const QSharedPointer<QGraphicsScene>& scene);

private:
    QWeakPointer<QGraphicsScene> m_Scene;
};



//
// Created by kolya on 9/25/2021.
//

#include "DrawManager.h"
#include <QGraphicsScene>
#include "ULine.h"

DrawManager::DrawManager(const QSharedPointer<QGraphicsScene>& scene)
{
    m_Scene = scene;
}

QGraphicsItem *DrawManager::DrawLine(QPoint start, QPoint end, ELineAlgorithm algorithm)
{
    auto* line = new ULine(m_Scene.data(), algorithm);
    line->setPos({200, 200});
    m_Scene.lock()->addItem(line);
    return line;
}

void DrawManager::SetMode(Mode* newMode)
{
    m_Mode.reset(newMode);
}

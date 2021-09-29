//
// Created by kolya on 9/25/2021.
//

#include "DrawManager.h"
#include <QGraphicsScene>
#include "ActionGraphicsScene.h"
#include "ULine.h"

DrawManager::DrawManager(const QSharedPointer<QGraphicsScene>& scene)
{
    m_Scene = scene;
}

void DrawManager::SetMode(Mode* newMode)
{
    m_Mode.clear();
    m_Mode = newMode;
    auto* action_scene = qobject_cast<ActionGraphicsScene*>(m_Scene.data());
    QObject::connect(action_scene, &ActionGraphicsScene::NewAction, m_Mode.data(), &Mode::ExecAction);
}

//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21

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
    if (m_Mode) delete m_Mode.data();
    m_Mode = newMode;
    auto* action_scene = qobject_cast<ActionGraphicsScene*>(m_Scene.data());
    QObject::connect(action_scene, &ActionGraphicsScene::NewAction, m_Mode.data(), &Mode::ExecAction);
}

//
// Created by kolya on 10/23/2021.
//

#include "SecondOrderMode.h"
#include "QGraphicsScene"
#include "GlobalShit.h"

SecondOrderMode::SecondOrderMode(const QSharedPointer<QGraphicsScene> &scene, ESecondOrderShape shape)
        : Mode(scene.get())
        , m_ShapeType(shape)
{
    m_Scene = scene;
}

void SecondOrderMode::ExecAction(const EditorAction &action)
{
    VERBOSE();
    m_ActionStack.push(action);
    if (m_ActionStack.size() >= 2)
    {
        EditorAction last_action = m_ActionStack.top();
        if (last_action.this_action_type != EAction::LeftReleased)
        {
            return;
        }
        m_ActionStack.pop();

        EditorAction first_action = m_ActionStack.top();
        if (first_action.this_action_type != EAction::LeftPressed) //TODO: maybe not release
        {
            m_ActionStack.push(last_action);
            return;
        }
        m_ActionStack.pop();

        CreateShape(first_action.action_location, last_action.action_location, m_ShapeType);
    }
}

void SecondOrderMode::RevertAction()
{

}

void SecondOrderMode::CreateItem()
{

}

void SecondOrderMode::CreateShape(QPoint start, QPoint end, ESecondOrderShape shape)
{
    auto* item = new USecondOrder(m_Scene.data(), shape);
    item->setPos(start);
    item->SetupShape(start, end);
    m_Scene.lock()->addItem(item);
}

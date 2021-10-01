//
// Created by kolya on 9/28/2021.
//

#include "LineMode.h"
#include "ULine.h"
#include <QGraphicsScene>
#include <iostream>

void LineMode::ExecAction(const EditorAction &action)
{
    std::cout << __func__ ;
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

        CreateLine(first_action.action_location, last_action.action_location, m_Algorithm);
    }
}

void LineMode::RevertAction()
{

}

void LineMode::CreateItem()
{

}

LineMode::LineMode(const QSharedPointer<QGraphicsScene>& scene, ELineAlgorithm algorithm)
    : Mode(scene.get())
    , m_Algorithm(algorithm)
{
    m_Scene = scene;
}

void LineMode::CreateLine(QPoint start, QPoint end, ELineAlgorithm algorithm)
{
    auto* line = new ULine(m_Scene.data(), algorithm);
    line->setPos(start);
    line->SetupLine(start, end);
    m_Scene.lock()->addItem(line);
}

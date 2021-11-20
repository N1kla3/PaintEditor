//
// Created by kolya on 11/8/2021.
//

#include "CurveMode.h"
#include "Curve.h"
#include "GlobalShit.h"
#include <QGraphicsScene>

CurveMode::CurveMode(const QSharedPointer<QGraphicsScene>& scene, ECurveAlgo algorithm)
        : Mode(scene.get())
        , m_Algorithm(algorithm)
{
    m_Scene = scene;
}

void CurveMode::ExecAction(const EditorAction &action)
{
    VERBOSE("Curve");
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

        CreateCurve(last_action.action_location, m_Algorithm);
    }
}

void CurveMode::RevertAction()
{

}

void CurveMode::CreateItem()
{

}

void CurveMode::CreateCurve(QPoint pos, ECurveAlgo algorithm)
{
    auto* curve = new Curve(m_Scene.data(), algorithm);
    curve->setPos(pos);
    m_Scene.lock()->addItem(curve);
}


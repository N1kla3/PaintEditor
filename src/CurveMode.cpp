//
// Created by kolya on 11/8/2021.
//

#include "CurveMode.h"
#include <QGraphicsScene>

CurveMode::CurveMode(const QSharedPointer<QGraphicsScene>& scene, ECurveAlgo algorithm)
        : Mode(scene.get())
        , m_Algorithm(algorithm)
{
    m_Scene = scene;
}

void CurveMode::ExecAction(const EditorAction &action)
{

}

void CurveMode::RevertAction()
{

}

void CurveMode::CreateItem()
{

}


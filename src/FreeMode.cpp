//
// Created by kolya on 11/14/2021.
//

#include "FreeMode.h"
#include "GlobalShit.h"
#include <QGraphicsScene>

FreeMode::FreeMode(const QSharedPointer<QGraphicsScene> &scene)
    : Mode(scene.get())
{
    m_Scene = scene;
}

void FreeMode::ExecAction(const EditorAction &action)
{
    VERBOSE("Free mode");
}

void FreeMode::RevertAction()
{

}

void FreeMode::CreateItem()
{

}

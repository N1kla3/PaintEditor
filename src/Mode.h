//
// Created by kolya on 9/27/2021.
//

#pragma once

struct EditorAction;
class QGraphicsScene;

#include "QWeakPointer"

/*
 * Basic class for every mode in painter
 */
class Mode
{
public:
    virtual void ExecAction(const EditorAction& action) = 0;

    virtual void RevertAction() = 0;

    virtual void CreateItem() = 0;

protected:
    QWeakPointer<QGraphicsScene> m_Scene;
};



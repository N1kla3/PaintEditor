//
// Created by kolya on 11/14/2021.
//

#pragma once

#include "Mode.h"
#include "EditorAction.h"
#include <QSharedPointer>

class FreeMode : public Mode
{
    Q_OBJECT
public:
    explicit FreeMode(const QSharedPointer<QGraphicsScene>& scene);

protected:
    virtual void ExecAction(const EditorAction& action) override;

    virtual void RevertAction() override;
    virtual void CreateItem() override;
};



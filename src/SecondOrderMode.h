//
// Created by kolya on 10/23/2021.
//

#pragma once

#include "Mode.h"
#include "USecondOrder.h"
#include "stack"
#include "EditorAction.h"

class SecondOrderMode : public Mode
{
    Q_OBJECT
public:
    explicit SecondOrderMode(const QSharedPointer<QGraphicsScene>& scene, ESecondOrderShape shape);

protected:
    virtual void ExecAction(const EditorAction &action) override;

    virtual void RevertAction() override;

    virtual void CreateItem() override;

private:
    void CreateShape(QPoint start, QPoint end, ESecondOrderShape shape);

    ESecondOrderShape m_ShapeType;

    std::stack<EditorAction> m_ActionStack{};
};



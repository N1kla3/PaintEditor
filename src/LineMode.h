//
// Created by kolya on 9/28/2021.
//

#pragma once

#include "Mode.h"
#include <stack>
#include "EditorAction.h"
#include <QSharedPointer>

enum class ELineAlgorithm;
class QGraphicsScene;
class QGraphicsItem;

class LineMode : public Mode
{
    Q_OBJECT
public:
    explicit LineMode(const QSharedPointer<QGraphicsScene>& scene, ELineAlgorithm algorithm);

protected:
    virtual void ExecAction(const EditorAction &action) override;

    virtual void RevertAction() override;

    virtual void CreateItem() override;

private:
    void CreateLine(QPoint start, QPoint end, ELineAlgorithm algorithm);

    ELineAlgorithm m_Algorithm;

    std::stack<EditorAction> m_ActionStack{};
};



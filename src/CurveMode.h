//
// Created by kolya on 11/8/2021.
//

#pragma once

#include "Mode.h"
#include <stack>
#include "EditorAction.h"
#include <QSharedPointer>

enum class ECurveAlgo;
class QGraphicsScene;
class QGraphicsItem;

class CurveMode : public Mode
{
    Q_OBJECT
public:
    explicit CurveMode(const QSharedPointer<QGraphicsScene>& scene, ECurveAlgo algorithm);

protected:
    virtual void ExecAction(const EditorAction &action) override;

    virtual void RevertAction() override;

    virtual void CreateItem() override;

private:
    void CreateCurve(QPoint pos, ECurveAlgo algorithm);

    ECurveAlgo m_Algorithm;

    std::stack<EditorAction> m_ActionStack{};
};



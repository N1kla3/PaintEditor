//
// Created by kolya on 9/28/2021.
//

#pragma once

#include "Mode.h"
#include <queue>
#include "EditorAction.h"

enum class ELineAlgorithm;

class LineMode : Mode
{
public:
    explicit LineMode(ELineAlgorithm algorithm);

protected:
    virtual void ExecAction(const EditorAction &action) override;

    virtual void RevertAction() override;

    virtual void CreateItem() override;

private:
    ELineAlgorithm m_Algorithm;

    std::queue<EditorAction> ActionQueue;
};



//
// Created by kolya on 9/27/2021.
//

#pragma once

#include <QPoint>

enum class EAction
{
    LeftPressed,
    LeftReleased,
    RightPressed,
    RightReleased
};

struct EditorAction
{
    EAction this_action_type = EAction::LeftPressed;

    QPoint action_location = QPoint{0, 0};
};



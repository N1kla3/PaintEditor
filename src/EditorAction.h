//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21

#pragma once

#include <QPoint>

enum class EAction
{
    LeftPressed,
    LeftReleased,
    RightPressed,
    RightReleased,
    NONE
};

struct EditorAction
{
    EAction this_action_type = EAction::NONE;

    QPoint action_location = QPoint{0, 0};
};



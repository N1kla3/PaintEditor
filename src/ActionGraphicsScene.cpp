//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21

#include "ActionGraphicsScene.h"
#include "EditorAction.h"
#include "GlobalShit.h"
#include <QGraphicsSceneMouseEvent>

ActionGraphicsScene::ActionGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void ActionGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    VERBOSE("scene");
    EditorAction action;
    action.action_location = event->scenePos().toPoint();
    if (event->button() == Qt::LeftButton)
    {
        action.this_action_type = EAction::LeftPressed;
    }
    else if (event->button() == Qt::RightButton)
    {
        action.this_action_type = EAction::RightPressed;
    }

    emit NewAction(action);
    QGraphicsScene::mousePressEvent(event);
}

void ActionGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void ActionGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    VERBOSE("scene");
    EditorAction action;
    action.action_location = event->scenePos().toPoint();
    if (event->button() == Qt::LeftButton)
    {
        action.this_action_type = EAction::LeftReleased;
    }
    else if (event->button() == Qt::RightButton)
    {
        action.this_action_type = EAction::RightReleased;
    }

    emit NewAction(action);
    QGraphicsScene::mouseReleaseEvent(event);
}

void ActionGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
}

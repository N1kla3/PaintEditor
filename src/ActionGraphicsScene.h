//
// Created by kolya on 9/29/2021.
//

#pragma once

#include <QGraphicsScene>

struct EditorAction;

class ActionGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ActionGraphicsScene(QObject* parent = nullptr);

signals:
    void NewAction(const EditorAction& action);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};



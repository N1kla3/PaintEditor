//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21

#pragma once

struct EditorAction;
class QGraphicsScene;

#include "QWeakPointer"

/*
 * Basic class for every mode in painter
 */
class Mode : public QObject
{
    Q_OBJECT
public:
    explicit Mode(QObject* parent) : QObject(parent) {}

    virtual void ExecAction(const EditorAction& action) = 0;

    virtual void RevertAction() = 0;

    virtual void CreateItem() = 0;

protected:
    QWeakPointer<QGraphicsScene> m_Scene;
};



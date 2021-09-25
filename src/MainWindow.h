//
// Created by kolya on 9/23/2021.
//

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QGraphicsScene;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

    virtual void resizeEvent(QResizeEvent* event) override;

    QGraphicsScene* GetScene() const { return m_Scene; }

private:
    Ui::MainWindow *ui;

    QGraphicsScene* m_Scene;
};



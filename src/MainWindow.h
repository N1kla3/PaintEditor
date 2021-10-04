//
// Created by kolya on 9/23/2021.
//

#pragma once

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QGraphicsScene;
class DrawManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

    virtual void resizeEvent(QResizeEvent* event) override;

    QSharedPointer<QGraphicsScene> GetScene() const { return m_Scene; }

    bool DebugMode = false;

    inline static MainWindow* Window = nullptr;

signals:
    void DebugIteration();

private:
    Ui::MainWindow *ui;

    QSharedPointer<QGraphicsScene> m_Scene;

    std::unique_ptr<DrawManager> m_DrawManager;

private slots:
    void actionDDA_triggered();
    void actionBrasen_triggered();
    void actionWu_triggered();

    void toggleDebugMode(bool toggle);
    void nextDebug();
};



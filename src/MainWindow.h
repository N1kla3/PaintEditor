//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21

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

    void AddConsoleLine(const QString& str);

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
    void actionCircle_triggered();
    void actionEllipse_triggered();
    void actionHyperbola_triggered();
    void actionParabola_triggered();
    void actionErmit_triggered();
    void actionBezje_triggered();
    void actionB_spline_triggered();

    void toggleDebugMode(bool toggle);
    void nextDebug();
};



//
// Created by kolya on 9/23/2021.
//

#include "MainWindow.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QRandomGenerator>
#include "DrawManager.h"
#include "LineMode.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "ULine.h"
#include "ActionGraphicsScene.h"
#include "GlobalShit.h"
#include "SecondOrderMode.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Scene = QSharedPointer<ActionGraphicsScene>::create();
    ui->graphicsView->setScene(m_Scene.get());

    m_DrawManager = std::make_unique<DrawManager>(m_Scene);

    MainWindow::Window = this;

    connect(ui->actionDDA, &QAction::triggered, this, &MainWindow::actionDDA_triggered);
    connect(ui->actionBrasenhaim, &QAction::triggered, this, &MainWindow::actionBrasen_triggered);
    connect(ui->actionWU, &QAction::triggered, this, &MainWindow::actionWu_triggered);
    connect(ui->actionCircle, &QAction::triggered, this, &MainWindow::actionCircle_triggered);
    connect(ui->actionEllipse, &QAction::triggered, this, &MainWindow::actionEllipse_triggered);
    connect(ui->actionHyperbola, &QAction::triggered, this, &MainWindow::actionHyperbola_triggered);
    connect(ui->actionParabola, &QAction::triggered, this, &MainWindow::actionParabola_triggered);

    connect(ui->DebugMode, &QAction::toggled, this, &MainWindow::toggleDebugMode);
    connect(ui->actionactionNextStep, &QAction::triggered, this, &MainWindow::nextDebug);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->tabWidget->resize(this->width()-20, this->height()-100);
    ui->plainTextEdit->resize(this->width()-50, this->height()-150);
    ui->graphicsView->resize(this->width()-40, this->height()-140);
    ui->graphicsView->scene()->setSceneRect(0,0, this->width()-40, this->height()-140);
    QWidget::resizeEvent(event);
}

void MainWindow::actionDDA_triggered()
{
    VERBOSE();
    m_DrawManager->SetMode(new LineMode(m_Scene, ELineAlgorithm::DDA));
}

void MainWindow::actionBrasen_triggered()
{
    VERBOSE();
    m_DrawManager->SetMode(new LineMode(m_Scene, ELineAlgorithm::BRASENHAME));
}

void MainWindow::actionWu_triggered()
{
    VERBOSE();
    m_DrawManager->SetMode(new LineMode(m_Scene, ELineAlgorithm::WU));
}

void MainWindow::actionCircle_triggered()
{
    VERBOSE();
    m_DrawManager->SetMode(new SecondOrderMode(m_Scene, ESecondOrderShape::CIRCLE));
}

void MainWindow::actionEllipse_triggered()
{
    VERBOSE();
    m_DrawManager->SetMode(new SecondOrderMode(m_Scene, ESecondOrderShape::ELLIPSE));
}

void MainWindow::actionHyperbola_triggered()
{
    VERBOSE();
    m_DrawManager->SetMode(new SecondOrderMode(m_Scene, ESecondOrderShape::HYPERBOLA));
}

void MainWindow::actionParabola_triggered()
{
    VERBOSE();
    m_DrawManager->SetMode(new SecondOrderMode(m_Scene, ESecondOrderShape::PARABOLA));
}

void MainWindow::toggleDebugMode(bool toggle)
{
    VERBOSE("Debug is ", toggle);
    DebugMode = toggle;
}

void MainWindow::nextDebug()
{
    emit DebugIteration();
}

void MainWindow::AddConsoleLine(const QString &str)
{
    ui->plainTextEdit->insertPlainText(str+"\n");
}

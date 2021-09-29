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

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Scene = QSharedPointer<ActionGraphicsScene>::create();
    ui->graphicsView->setScene(m_Scene.get());

    m_DrawManager = std::make_unique<DrawManager>(m_Scene);
    //m_DrawManager->DrawLine(QPoint(), QPoint(), ELineAlgorithm::DDA);

    connect(ui->actionDDA, &QAction::triggered, this, &MainWindow::actionDDA_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->resize(this->width()-20, this->height()-100);
    ui->graphicsView->scene()->setSceneRect(0,0, this->width()-20, this->height()-100);
    QWidget::resizeEvent(event);
}

void MainWindow::actionDDA_triggered()
{
    std::cout << "Action DDA triggered\n";
    m_DrawManager->SetMode(new LineMode(m_Scene, ELineAlgorithm::DDA));
}

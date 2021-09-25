//
// Created by kolya on 9/23/2021.
//

#include "MainWindow.h"
#include <QTabWidget>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QRandomGenerator>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_Scene);
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

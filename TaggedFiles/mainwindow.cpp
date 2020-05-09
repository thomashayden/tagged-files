#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::tableModel = new TableModel();
    MainWindow::tableModel->insertRows(0,2);
    MainWindow::tableModel->setData(MainWindow::tableModel->index(0,0), QString("test"));
    ui->tableView_files->setModel(MainWindow::tableModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


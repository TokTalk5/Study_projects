#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interface.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui (new Ui::MainWindow)
{
    ui->setupUi(this);
    // Создаем экземпляр интерфейса
    interface *interfaceWidget = new interface(this);
    // Устанавливаем интерфейс в качестве центрального виджета
    setCentralWidget(interfaceWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

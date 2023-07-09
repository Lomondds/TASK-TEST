#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   hide();
   window = new Secondwindow(this);
   window->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    hide();
    window2 = new thirdwindow(this);
    window2->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}

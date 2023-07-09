#include "mainwindow.h"
#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include <QMessageBox>
#include <QSqlQuery>

thirdwindow::thirdwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thirdwindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/SQLITE/database1.db");
    if (!db.open()) {
        QMessageBox::information(this, "infor","openfailed");
    }
    else
    {
        model = new QSqlRelationalTableModel(this, db);
        model->setTable("TypeVehicle");
        model->setRelation(2, QSqlRelation("Measurement", "id", "Measurement"));
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        model->select();

        delegate = new QSqlRelationalDelegate(ui->tableView);
        ui->tableView->setItemDelegate(delegate);
        ui->tableView->setModel(model);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSortingEnabled(true);
    }
}

thirdwindow::~thirdwindow()
{
    delete ui;
}

void thirdwindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

void thirdwindow::on_pushButton_2_clicked()
{
    db.removeDatabase("qt_sql_default_connection");
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    close();
}

void thirdwindow::on_pushButton_4_clicked()
{
    model->select();
}

void thirdwindow::on_pushButton_3_clicked()
{
    model->removeRow(currentRow);
    model->select();
}

void thirdwindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

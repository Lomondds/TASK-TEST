#include "mainwindow.h"
#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QMessageBox>
#include <QSqlQuery>

Secondwindow::Secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Secondwindow)
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
    model->setTable("trips");
    model->setRelation(2, QSqlRelation("TypeVehicle", "id", "Vehicle"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    delegate = new QSqlRelationalDelegate(ui->tableView);
    ui->tableView->setItemDelegate(delegate);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSortingEnabled(true);

    QSqlQuery query("SELECT name FROM trips", db);

        while (query.next())
        {
            QString columnValue = query.value(0).toString();
            ui->comboBox->addItem(columnValue);
        }
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &Secondwindow::onComboBoxIndexChanged);
    }
}

Secondwindow::~Secondwindow()
{
    db.close();
    delete ui;
}

void Secondwindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

void Secondwindow::on_pushButton_2_clicked()
{
       db.removeDatabase("qt_sql_default_connection");
       MainWindow *mainWindow = new MainWindow();
       mainWindow->show();
       close();
}
void Secondwindow::onComboBoxIndexChanged(int index)
{
    QString columnValue = ui->comboBox->itemText(index);
    QSqlQuery query;
            query.prepare("SELECT road FROM trips WHERE name = :name");
            query.bindValue(":name", columnValue);
            if (query.exec() && query.next())
            {
                QString road = query.value(0).toString();
                ui->lineEdit->setText(road);
            }

            query.prepare("SELECT TypeVehicle.Fuel, TypeVehicle.Consumption, TypeVehicle.Measurement_id, trips.road FROM TypeVehicle JOIN trips ON TypeVehicle.id = trips.Vehicle_id WHERE trips.name = :columnValue");
            query.bindValue(":columnValue", columnValue);
            if (query.exec() && query.next() && query.value(2)==1)
            {
                int Fuel = query.value(0).toInt();
                ui->lineEdit_2->setText(QString::number(Fuel));
                int Consumption = query.value(1).toInt();
                double road = query.value(3).toDouble();
                double result = (Fuel*800)/Consumption;
                ui->lineEdit_3->setText(QString::number(result));
                if (road>result)
                {
                    double result2 = (road - result)*200/800;
                    ui->lineEdit_4->setText(QString::number(result2));
                }
                else
                {
                     ui->lineEdit_4->setText("0");
                }

            }
            else
            {
                int Fuel = query.value(0).toInt();
                int Consumption = query.value(1).toInt();
                double road = query.value(3).toDouble();
                double result = (Fuel*100)/Consumption;
                ui->lineEdit_3->setText(QString::number(result));
                if (road>result)
                {
                    double result2 = (road - result)*12/100;
                    ui->lineEdit_4->setText(QString::number(result2));
                }
                else
                {
                     ui->lineEdit_4->setText("0");
                }

            }
}

void Secondwindow::on_pushButton_4_clicked()
{
    model->removeRow(currentRow);
    model->select();
}

void Secondwindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

void Secondwindow::on_pushButton_3_clicked()
{
    model->select();
}


#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

namespace Ui {
class Secondwindow;
}

class Secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Secondwindow(QWidget *parent = nullptr);
    ~Secondwindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onComboBoxIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::Secondwindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model2;
    QSqlRelationalTableModel *model;
    QSqlRelationalDelegate *delegate;
    QComboBox *comboBox;
    int currentRow;

};

#endif // SECONDWINDOW_H

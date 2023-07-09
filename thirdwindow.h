#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

namespace Ui {
class thirdwindow;
}

class thirdwindow : public QDialog
{
    Q_OBJECT

public:
    explicit thirdwindow(QWidget *parent = nullptr);
    ~thirdwindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::thirdwindow *ui;
    QSqlDatabase db;
    QSqlRelationalTableModel *model;
    QSqlRelationalDelegate *delegate;
    QSqlTableModel *model2;
    int currentRow;
};

#endif // THIRDWINDOW_H

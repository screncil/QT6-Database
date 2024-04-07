#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Add_clicked();

    void on_Delete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_Sort_clicked();

    void on_Average_clicked();

    void on_Search_clicked();

    void on_Download_clicked();

    void on_OpenExcel_clicked();

    void on_OpenWord_clicked();

    void on_OpenAccess_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

    int row; //Номер змінної для видалення значення в таблиці
};
#endif // MAINWINDOW_H

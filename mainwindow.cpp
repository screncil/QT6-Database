#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qsqlrecord>
#include <QMessageBox>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "OpenApps.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./TourDb");
    if(db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("close");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Touring(Маршрут TEXT, Прізвище TEXT, Відстань маршруту FLOAT, Ціна путівки INT )");

    model = new QSqlTableModel(this,db);
    model -> setTable("Touring");
    model -> select();


    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents(); // Автоматично регулює ширину стовпців

}

bool OpenExcel(int argc, TCHAR *argv[]) {
    // Путь к Excel
    TCHAR excelPath[] = TEXT("C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE");

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Запускаем Excel без указания файла
    if (!CreateProcess(NULL, excelPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    // Закрываем дескрипторы процесса и потока
    // CloseHandle(pi.hProcess);
    // CloseHandle(pi.hThread);

    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Add_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_Delete_clicked()
{
    model->removeRow(row);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void MainWindow::on_Sort_clicked()
{


}



void MainWindow::on_Average_clicked()
{
    int rowCount = model->rowCount();
    int priceColumnIndex = model->fieldIndex("Ціна");

    int total = 0;

    for (int i = 0; i < rowCount; ++i) {
        QModelIndex index = model->index(i, priceColumnIndex);
        total += model->data(index).toInt();
    }

    double average = static_cast<double>(total) / rowCount;

    ui->lineEdit->setText(QString::number(average));
}



void MainWindow::on_Search_clicked()

{
    QString surname = ui->searchLine->text(); // Отримати прізвище з lineEdit

    // Виконати запит до бази даних
    QSqlQuery query;
    query.prepare("SELECT * FROM Touring WHERE Прізвище = ?");
    query.addBindValue(surname);

    if (query.exec()) {
        // Вдало виконаний запит
        QSqlTableModel *searchModel = new QSqlTableModel(this, db);
        searchModel->setQuery(query);
        ui->tableView->setModel(searchModel); // Встановити модель для відображення результатів
    } else {
        QMessageBox searchingError;
        searchingError.setText("Помилка пошуку! /n Введіть інше значення або переконайтесь що воно існує");
        searchingError.exec();
    }
}



void MainWindow::on_Download_clicked()
{
    // Виконати запит для отримання всіх даних з бази даних
    QSqlQueryModel *downloadModel = new QSqlQueryModel(this);
    downloadModel->setQuery("SELECT * FROM Touring");

    // Встановити модель для відображення результатів
    ui->tableView->setModel(downloadModel);

}


void MainWindow::on_OpenExcel_clicked()
{
    Excel::OpenExcel();
}



void MainWindow::on_OpenWord_clicked()
{
    Word::OpenWord();
}


void MainWindow::on_OpenAccess_clicked()
{
    Access::OpenAccess();
}


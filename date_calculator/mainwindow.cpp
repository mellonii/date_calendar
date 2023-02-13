#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stored_save();
    storedOperator = '=';
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stored_save(){
    stored_sec = ui->sec->toPlainText().toInt();
    stored_min = ui->min->toPlainText().toInt();
    stored_hour = ui->hour->toPlainText().toInt();
    stored_day = ui->day->toPlainText().toInt();
    stored_year = ui->year->toPlainText().toInt();
}

void MainWindow::on_plus_clicked()
{
    stored_save();
    storedOperator = '+';
}

void MainWindow::on_pushButton_clicked()
{
    calculate(storedOperator);
    ui->sec->setPlainText(QString::number(stored_sec));
    ui->min->setPlainText(QString::number(stored_min));
    ui->hour->setPlainText(QString::number(stored_hour));
    ui->day->setPlainText(QString::number(stored_day));
    ui->year->setPlainText(QString::number(stored_year));
}

void MainWindow::calculate(char storedOperator)
{
    int sec = ui->sec->toPlainText().toInt();
    int min = ui->min->toPlainText().toInt();
    int hour = ui->hour->toPlainText().toInt();
    int day = ui->day->toPlainText().toInt();
    int year = ui->year->toPlainText().toInt();

    std::tuple<int,int,int,int,int> time = {sec,min,hour,day,year};
    std::tuple<int,int,int,int,int> stored_time = {stored_sec,stored_min,stored_hour,stored_day,stored_year};

    if (storedOperator == '+') {
        stored_time = plus(stored_time, time);
        storedOperator = '=';
        stored_sec = std::get<0>(stored_time);
        stored_min = std::get<1>(stored_time);
        stored_hour = std::get<2>(stored_time);
        stored_day = std::get<3>(stored_time);
        stored_year = std::get<4>(stored_time);
    }
    else if (storedOperator == '-') {
        stored_time = minus(stored_time, time);
        storedOperator = '=';
        stored_sec = std::get<0>(stored_time);
        stored_min = std::get<1>(stored_time);
        stored_hour = std::get<2>(stored_time);
        stored_day = std::get<3>(stored_time);
        stored_year = std::get<4>(stored_time);
    }
    else if (storedOperator == '=') {
        on_pushButton_clicked();
    }
}

int MainWindow::transf_forward(std::tuple<int,int,int,int,int> x) {
    return (sec * std::get<0>(x) + min * std::get<1>(x) + hour * std::get<2>(x) + day * std::get<3>(x) + year * std::get<4>(x));
}

std::tuple<int,int,int,int,int> MainWindow::transf_back(int x) {
    return{ x%min ,
            (x%hour)/min,
            (x%day)/hour,
            (x%year)/day,
            x / year
            };
}

std::tuple<int,int,int,int,int> MainWindow::plus(std::tuple<int,int,int,int,int> x,std::tuple<int,int,int,int,int> y){
    int sx = transf_forward(x);
    int sy = transf_forward(y);
    return transf_back(sx+sy);
}
std::tuple<int,int,int,int,int> MainWindow::minus(std::tuple<int,int,int,int,int> x,std::tuple<int,int,int,int,int> y){
    int sx = transf_forward(x);
    int sy = transf_forward(y);
    return transf_back(sx-sy);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->sec->setPlainText("0");
    ui->min->setPlainText("0");
    ui->hour->setPlainText("0");
    ui->day->setPlainText("0");
    ui->year->setPlainText("0");
}


void MainWindow::on_minus_clicked()
{
    stored_save();
    storedOperator = '-';
}


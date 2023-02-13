#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <tuple>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int stored_sec;
    int stored_min;
    int stored_hour;
    int stored_day;
    int stored_year;
    char storedOperator;

    void stored_save();
    void calculate(char storedOperator);

int sec = 1;
int min = 60;
int hour = min * 60;
int day = hour * 24;
int year = day * 365;


int transf_forward(std::tuple<int,int,int,int,int> x);
std::tuple<int,int,int,int,int> transf_back(int x);
std::tuple<int,int,int,int,int> plus(std::tuple<int,int,int,int,int> x,std::tuple<int,int,int,int,int> y);
std::tuple<int,int,int,int,int> minus(std::tuple<int,int,int,int,int> x,std::tuple<int,int,int,int,int> y);

private slots:
    void on_plus_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_minus_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

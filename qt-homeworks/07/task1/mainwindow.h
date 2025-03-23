#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>
#include <QtGlobal>
#include <QtConcurrent>
//#include <algorithm>

#include "graphic.h"

#define FD 1000.0 //частота дискретизации
// const uint32_t FD = 1000.0;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Метод считывает данные из исходного файла
    QVector<uint32_t> ReadFile(QString path, uint8_t numberChannel);
    //Метод преобразует данные физические величины, В?
    QVector<double> ProcessFile(QVector<uint32_t>& dataFile);
    //Метод ищет Максимумы
    QVector<double> FindMax(QVector<double>& resultData);
    //Метод ищет минимумы
    QVector<double> FindMin(QVector<double>& resultData);
    //Метод отображает результаты
    void DisplayResult(QVector<double> mins, QVector<double> maxs);

protected:

private slots:
    void on_pb_path_clicked();
    void on_pb_start_clicked();
    void view_graphic();
    void on_pb_clearResult_clicked();

private:
    void AllCeckBoxOff_();

    Ui::MainWindow *ui;
    QString pathToFile = "";
    uint8_t numberSelectChannel = 0xEA;
    Graphic* graphic_wnd_;

signals:
    void sig_data_ready(const QVector<double> x, const QVector<double> y);
};
#endif // MAINWINDOW_H

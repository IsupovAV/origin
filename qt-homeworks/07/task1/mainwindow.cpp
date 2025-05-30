#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    graphic_wnd_ = new Graphic(this);
    connect(this, &MainWindow::sig_data_ready, graphic_wnd_, &Graphic::UpdateData);
    connect(graphic_wnd_, &Graphic::sig_graphic, this, &MainWindow::view_graphic);
}

MainWindow::~MainWindow() {
    delete ui;
}

/****************************************************/
/*!
@brief:	Метод считывает данные из файла
@param: path - путь к файлу
        numberChannel - какой канал АЦП считать
*/
/****************************************************/
QVector<uint32_t> MainWindow::ReadFile(QString path, uint8_t numberChannel) {

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if (file.isOpen() == false) {

        if (pathToFile.isEmpty()) {
            QMessageBox mb;
            mb.setWindowTitle("Ошибка");
            mb.setText("Ошибка открытия фала");
            mb.exec();
        }
    }

    QDataStream dataStream;
    dataStream.setDevice(&file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    QVector<uint32_t> readData;
    readData.clear();
    uint32_t currentWord = 0, sizeFrame = 0;

    while (dataStream.atEnd() == false) {

        dataStream >> currentWord;

        if (currentWord == 0xFFFFFFFF) {

            dataStream >> currentWord;

            if (currentWord < 0x80000000) {

                dataStream >> sizeFrame;

                if (sizeFrame > 1500) {
                    continue;
                }

                for (int i = 0; i < sizeFrame / sizeof(uint32_t); i++) {

                    dataStream >> currentWord;

                    if ((currentWord >> 24) == numberChannel) {

                        readData.append(currentWord);
                    }
                }
            }
        }
    }
    ui->chB_readSucces->setChecked(true);
    return readData;
}

QVector<double> MainWindow::ProcessFile(QVector<uint32_t> &dataFile) {
    QVector<double> resultData;
    resultData.clear();

    foreach (int word, dataFile) {
        word &= 0x00FFFFFF;
        if (word > 0x800000) {
            word -= 0x1000000;
        }

        double res = ((double)word / 6000000) * 10;
        resultData.append(res);
    }
    ui->chB_procFileSucces->setChecked(true);

    return resultData;
}

QVector<double> MainWindow::FindMax(QVector<double> &resultData) {
    double max = 0, sMax = 0;
    // Поиск первого максиума
    foreach (double num, resultData) {
        // QThread::usleep(1);
        if (num > max) {
            max = num;
        }
    }

    // Поиск 2го максимума
    foreach (double num, resultData) {
        // QThread::usleep(1);
        if (num > sMax && (qFuzzyCompare(num, max) == false)) {
            sMax = num;
        }
    }

    QVector<double> maxs = {max, sMax};
    ui->chB_maxSucess->setChecked(true);
    return maxs;
}

QVector<double> MainWindow::FindMin(QVector<double> &resultData) {

    double min = 0, sMin = 0;
    // QThread::sleep(1);
    // Поиск первого максиума
    foreach (double num, resultData) {
        if (num < min) {
            min = num;
        }
    }
    // QThread::sleep(1);
    // Поиск 2го максимума
    foreach (double num, resultData) {
        if (num < sMin && (qFuzzyCompare(num, min) == false)) {
            sMin = num;
        }
    }

    QVector<double> mins = {min, sMin};
    ui->chB_minSucess->setChecked(true);
    return mins;
}

void MainWindow::DisplayResult(QVector<double> mins, QVector<double> maxs) {
    ui->te_Result->append("Расчет закончен!");

    ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
    ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

    ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
    ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)) +
                          "\n");
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Выбрать путь"
*/
/****************************************************/
void MainWindow::on_pb_path_clicked() {
    pathToFile = "";
    ui->le_path->clear();

    pathToFile = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "../../",
                                              tr("ADC Files (*.adc)"));

    ui->le_path->setText(pathToFile);
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Старт"
*/
/****************************************************/
void MainWindow::on_pb_start_clicked() {
    // проверка на то, что файл выбран
    if (pathToFile.isEmpty()) {

        QMessageBox mb;
        mb.setWindowTitle("Ошибка");
        mb.setText("Выберите файл!");
        mb.exec();
        return;
    }

    AllCeckBoxOff_();

    int selectIndex = ui->cmB_numCh->currentIndex();
    // Маски каналов
    if (selectIndex == 0) {
        numberSelectChannel = 0xEA;
    } else if (selectIndex == 1) {
        numberSelectChannel = 0xEF;
    } else if (selectIndex == 2) {
        numberSelectChannel = 0xED;
    }

    auto read = [&] { return ReadFile(pathToFile, numberSelectChannel); };
    auto process = [&](QVector<uint32_t> dataFile) {
        return ProcessFile(dataFile);
    };
    auto findMax = [&](QVector<double> dataProcess) {
        QVector<double> maxs = FindMax(dataProcess);
        QVector<double> mins = FindMin(dataProcess);
        DisplayResult(mins, maxs);

        // Тут необходимо реализовать код наполнения серии
        // и вызов сигнала для отображения графика
        QVector<double> x, y;
        x.resize(FD);
        y.resize(FD);
        for (uint32_t i = 0; i < FD; ++i) {
            x[i] = i / FD;
            y[i] = dataProcess[i];
        }
        emit sig_data_ready(x, y);
    };

    auto result = QtConcurrent::run(read).then(process).then(findMax);
}

void MainWindow::view_graphic() {
    auto title = "График канала: " + ui->cmB_numCh->currentText();
    graphic_wnd_->setWindowTitle(title);
    if(graphic_wnd_->isHidden())
        graphic_wnd_->show();
}

void MainWindow::on_pb_clearResult_clicked() {
    AllCeckBoxOff_();
    graphic_wnd_->ClearData();
}

void MainWindow::AllCeckBoxOff_()
{
    ui->chB_maxSucess->setChecked(false);
    ui->chB_procFileSucces->setChecked(false);
    ui->chB_readSucces->setChecked(false);
    ui->chB_minSucess->setChecked(false);
}


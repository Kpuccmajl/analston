#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QStringList>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAnal_clicked()
{
    ui->res->setText("идёт анализ, подождите..");
    qApp->processEvents();
    QProcess process;
    QStringList words = normalizedText();
    if (words.isEmpty())
    {
        ui->res->setText("Некорректный текст! Повторите ввод.");
        return;
    }
    QStringList params = QStringList() << "models.py" << words;
    process.start("python3", params);
    if(process.waitForFinished(-1)) {;}
    QString result = process.readAll();
    qDebug() << result;
    result.chop(1);
    ui->slider->setValue(result.toFloat() * 100);
    result.toFloat() > 0 ? ui->res->setText("анализ завершён! (Текст положительный на " + QString::number(result.toFloat() * 100) + "%)")
                         : ui->res->setText("анализ завершён! (Текст отрицательный на " + QString::number(result.toFloat() * -100) + "%)");
}

QStringList MainWindow::normalizedText()
{
    QString text = ui->text->toPlainText();
    QString toRemove = "В с у о к от до на по со из над "
                       "под при про без ради близ перед около "
                       "через вдоль после кроме сквозь вроде "
                       "вследствие благодаря вопреки согласно навстречу "
                       ", . ! ? - ( ) "
                       "и то это да ни как так нетолько но также тоже или либо толи "
                       "не то а это но да за то однако "
                       "как что бы будто словно точно чем тем когда едва как только пока прежде чем в "
                       "то покамесь после того как чтобы ради дабы потому что оттого ибо если коли "
                       "ежели хотя хоть несмотря";
    foreach(QString word, toRemove.split(" "))
        text = text.replace(" " + word + " ", " ");
    return text.split(" ");
}

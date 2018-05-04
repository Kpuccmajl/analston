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
    QStringList params = QStringList() << "models.py" << ui->text->toPlainText().split(" ") ;
    process.start("python3", params);
    if(process.waitForFinished(-1));
    QString result = process.readAll();
    result.chop(1);
    ui->slider->setValue(result.toFloat() * 100);
    result.toFloat() > 0 ? ui->res->setText("анализ завершён! (Текст положительный на " + QString::number(result.toFloat() * 100) + "%)")
                         : ui->res->setText("анализ завершён! (Текст отрицательный на " + QString::number(result.toFloat() * -100) + "%)");
}

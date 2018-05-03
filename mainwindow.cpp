#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStringList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loadData();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData()
{
    QFile file("data.txt");
    if(!file.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QStringList tokens = stream.readLine().split('_');
        if (tokens.count() < 3)
            continue;
        words << Word(tokens.at(0), tokens.at(1).toInt(), tokens.at(2).toInt());
    }

    file.close();
}

void MainWindow::on_btnAnal_clicked()
{
    ui->res->setText("идёт анализ..");

    QString text = ui->text->toPlainText();
    text.remove(QRegExp("[^а-яА-Я\\d\\s]"));
    QStringList list = text.split(" ");
    foreach (QString s, list)
        s = s.trimmed();

    int pos_count = 0;
    int neg_count = 0;
    int pos_tone = 0;
    int neg_tone = 0;

    foreach (QString s, list)
    {
        foreach (Word w, words)
        {
            if (w.word == s)
            {
                if (w.tone > 5) //positive
                {
                    ++pos_count;
                    pos_tone += w.tone * w.weight - 5 * w.weight;
                }
                else //negative
                {
                    ++neg_count;
                    neg_tone += w.tone * w.weight;
                }
                break;
            }
        }
    }

    if (pos_count != 0 || neg_count != 0)
    {
        int res = 0;
        if (pos_count != 0)
            res += (pos_tone / pos_count) + 50;
        else if (neg_count != 0)
            res += (neg_tone / neg_count) * 10 - 50;
        ui->res->setText("Положительный на " + QString::number(res) + "%");
        ui->slider->setValue(res);
    }
    else
        ui->res->setText("не удалось определить тональность");
}

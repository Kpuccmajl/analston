#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct Word
{
    Word(QString w, int we, int t) : word(w), weight(we), tone(t) {}

    QString word;
    int weight;
    int tone;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAnal_clicked();

private:
    Ui::MainWindow *ui;

    void loadData();

    QList<Word> words;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRunnable>
#include <QThreadPool>

class MainWindow : public QMainWindow, public QRunnable {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void buildField();
    void run();

public slots:
    void findZero();
    void permutations();
    QPoint searchZero();

private:
    QWidget*** field;
    QWidget* pb;
};

#endif // MAINWINDOW_H

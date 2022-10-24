#include "mainwindow.h"
#include "fishka.h"
#include "permutationsbutton.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    pb = new PermutationsButton(this);
    resize(610, 665);
    move(200, 100);
    buildField();
    show();
}

MainWindow::~MainWindow() {

}

void MainWindow::buildField() {
    int n = 0;
    field = new QWidget**[4];
    for (int y = 0; y < 4; ++y) {
        field[y] = new QWidget*[4];
        for (int x = 0; x < 4; ++x)
            if (x == 3 && y == 3)
                field[y][x] = 0;
            else field[y][x] = new Fishka(x, y, ++n, this);
    }
}

void MainWindow::findZero() {
    if (!pb -> isEnabled())
        return;
    Fishka* f = (Fishka*) QObject::sender();
    int x = f -> getX();
    int y = f -> getY();
    if (x > 0 && field[y][x - 1] == 0) {
        f -> getX() = x - 1;
        field[y][x - 1] = field[y][x];
        field[y][x] = 0;
        f -> step(-1, +0);
        return;
    }
    if (y > 0 && field[y - 1][x] == 0) {
        f -> getY() = y - 1;
        field[y - 1][x] = field[y][x];
        field[y][x] = 0;
        f -> step(+0, -1);
        return;
    }
    if (x < 3 && field[y][x + 1] == 0) {
        f -> getX() = x + 1;
        field[y][x + 1] = field[y][x];
        field[y][x] = 0;
        f -> step(+1, +0);
        return;
    }
    if (y < 3 && field[y + 1][x] == 0) {
        f -> getY() = y + 1;
        field[y + 1][x] = field[y][x];
        field[y][x] = 0;
        f -> step(+0, +1);
        return;
    }
}

QPoint MainWindow::searchZero() {
    for (int y = 0; y < 4; ++y)
        for (int x = 0; x < 4; ++x)
            if (field[y][x] == 0)
                return QPoint(x, y);
    return QPoint(3, 3);
}

void MainWindow::permutations() {
    setAutoDelete(false);
    QThreadPool::globalInstance() -> start(this);
}

void MainWindow::run() {
    pb -> setEnabled(false);
    QPoint point = searchZero();
    int x = point.x();
    int y = point.y();
    int i = 0;
    QObject* t = 0;
    do {
        int dx = 0, dy = 0;
        switch (rand() % 4) {
            case 0: dx = -1;
                    break;
            case 1: dy = -1;
                    break;
            case 2: dx = +1;
                    break;
            case 3: dy = +1;
                    break;
           default: dy = -1;
        }

        if (x + dx >= 0 && x + dx <= 3 && y + dy >= 0 && y + dy <= 3) {
            Fishka* f = (Fishka*) field[y + dy][x + dx];
            if (f != 0 && t != f) {
                x += dx; dx = -dx;
                y += dy; dy = -dy;
                t = f;
                f -> getX() = x + dx;
                f -> getY() = y + dy;
                field[y + dy][x + dx] = field[y][x];
                field[y][x] = 0;
                f -> step(dx, dy);
                QThread::msleep(100);
                ++i;
            }
        }
    } while (i < 100 || field[3][3] != 0);
    pb -> setEnabled(true);

}

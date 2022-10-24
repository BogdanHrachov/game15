#include "fishka.h"

Fishka::Fishka(int x, int y, int n, QWidget* parent) : QPushButton(parent),  x(x), y(y), parent(parent) {
    QObject::connect(this, SIGNAL(clicked()), parent, SLOT(findZero()));
    move(x * 150 + 5, y * 150 + 5);
    QString s; s.setNum(n);
    resize(150, 150);
    setText(s);
    show();
}

int& Fishka::getX() {
    return x;
}

int& Fishka::getY() {
    return y;
}

void Fishka::step(int dx, int dy) {
    this -> dx = dx;
    this -> dy = dy;
    setAutoDelete(false);
    QThreadPool::globalInstance() -> start(this);
}

void Fishka::run() {
    int x = (this -> x - dx) * 150 + 5;
    int y = (this -> y - dy) * 150 + 5;
    for (int i = 0; i < 150; i += 15) {
        move(QPoint(x = x + dx * 15, y = y + dy * 15));
        QThread::msleep(20);
    }
}

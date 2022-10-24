#ifndef FISHKA_H
#define FISHKA_H

#include <QPushButton>
#include <QRunnable>
#include <QThreadPool>

class Fishka : public QPushButton, public QRunnable {
    Q_OBJECT

public:
    Fishka(int x, int y, int n, QWidget* parent);
    void run();
    int& getX();
    int& getY();
    void step(int dx, int dy);

private:
    int x, y;
    QWidget* parent;
    int dx, dy;
};

#endif // FISHKA_H

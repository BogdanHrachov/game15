#include "permutationsbutton.h"

PermutationsButton::PermutationsButton(QWidget* parent) : QPushButton(parent) {
    QObject::connect(this, SIGNAL(clicked()), parent, SLOT(permutations()));
    setText("Permutations");
    resize(150, 50);
    move(5, 610);
    show();
}

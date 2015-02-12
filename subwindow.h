#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QDialog>

namespace Ui {
class Subwindow;
}

class Subwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Subwindow(QWidget *parent = 0);
    ~Subwindow();

private:
    Ui::Subwindow *ui;
};

#endif // SUBWINDOW_H

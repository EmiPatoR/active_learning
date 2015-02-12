#include "subwindow.h"
#include "ui_subwindow.h"

Subwindow::Subwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Subwindow)
{
    ui->setupUi(this);
}

Subwindow::~Subwindow()
{
    delete ui;
}

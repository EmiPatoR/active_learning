#include "subwindow.h"
#include "ui_subwindow.h"

#include <QCloseEvent>
#include <qwt/qwt_plot.h>

Subwindow::Subwindow(QString name, QString type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Subwindow)
{
    ui->setupUi(this);
    m_name = name;
    m_type = type;
    this->setWindowTitle(name + "(" + type + ")");
}

void Subwindow::closeEvent(QCloseEvent *event){
    emit signalClosed(m_name);
    event->accept();
}

Subwindow::~Subwindow()
{
    delete ui;
}

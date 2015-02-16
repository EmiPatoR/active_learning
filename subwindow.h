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
    explicit Subwindow(QString name, QString type, QWidget *parent = 0);
    QString getName(){return m_name;}
    Subwindow* getPointer(){return this;}
    ~Subwindow();

signals:
    void signalClosed(QString Name);

protected:
    void closeEvent(QCloseEvent *event);



private:
    Ui::Subwindow *ui;
    QString m_name;
    QString m_type;
};

#endif // SUBWINDOW_H

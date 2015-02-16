#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:
    explicit Wizard(QStringList windows, QWidget *parent = 0);
    QString getAlgName(){return m_algName;}
    QString getAlgType(){return m_algType;}
    ~Wizard();

protected:
    void accept();
    bool validateCurrentPage ();

private:
    Ui::Wizard      *ui;
    QStringList     m_list_windows;
    QString         m_algName;
    QString         m_algType;

};

#endif // WIZARD_H

#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

#define ALG_SVM 0
#define ALG_PER 1

#define C_SVC 0
#define NU_SVC 1
#define ONE_CLASS_SVM 2
#define EPS_SVR 3
#define NU_SVR 4

#define K_LIN 0
#define K_POLY 1
#define K_RADIAL 2
#define K_SIGMOID 3

#define PAGE_INTRO 1
#define PAGE_ALG 2
#define PAGE_SVM_PARAMS 3
#define PAGE_PER_PARAMS 4
#define PAGE_FINAL 5

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

public slots:
    void slot_typeChanged(int index);
    void slot_kernelChanged(int index);

protected:
    void accept();
    bool validateCurrentPage ();
    int nextId() const;

private:
    Ui::Wizard      *ui;
    QStringList     m_list_windows;
    QString         m_algName;
    QString         m_algType;
    int             m_alg;


};

#endif // WIZARD_H

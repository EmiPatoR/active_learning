#include "wizard.h"
#include "ui_wizard.h"

#include <iostream>
#include <QMessageBox>

Wizard::Wizard(QStringList windows, QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);
    m_list_windows = windows;

    //fields page 2
    ui->wizardPage1->registerField("algName*",ui->lineEdit);
    ui->wizardPage2->registerField("algType",ui->comboBox);

    //fields page 3
    ui->wizardPage3->registerField("SVM_type",ui->comboBox_2);
    ui->wizardPage3->registerField("SVM_kernel_type",ui->comboBox_3);
    ui->wizardPage3->registerField("SVM_C",ui->dblspin_C);
    ui->wizardPage3->registerField("SVM_NU",ui->dblspin_NU);
    ui->wizardPage3->registerField("SVM_P",ui->dblspin_p);
    ui->wizardPage3->registerField("SVM_gamma",ui->dblspin_gamma);
    ui->wizardPage3->registerField("SVM_coef",ui->dblspin_coef);
    ui->wizardPage3->registerField("SVM_deg",ui->dblspin_deg);

    //Connexions
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_typeChanged(int)));
    connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_kernelChanged(int)));

    //Initialisation de la page des parametres
    emit ui->comboBox_2->currentIndexChanged(0);
    emit ui->comboBox_3->currentIndexChanged(0);

}

void Wizard::slot_kernelChanged(int index){
    switch(index){
    case K_LIN:
        ui->lbl_coef->setDisabled(true);
        ui->dblspin_coef->setDisabled(true);
        ui->lbl_deg->setDisabled(true);
        ui->dblspin_deg->setDisabled(true);
        ui->lbl_gamma->setDisabled(true);
        ui->dblspin_gamma->setDisabled(true);
        break;
    case K_POLY:
        ui->lbl_coef->setEnabled(true);
        ui->dblspin_coef->setEnabled(true);
        ui->lbl_deg->setEnabled(true);
        ui->dblspin_deg->setEnabled(true);
        ui->lbl_gamma->setEnabled(true);
        ui->dblspin_gamma->setEnabled(true);
        break;
    case K_RADIAL:
        ui->lbl_coef->setDisabled(true);
        ui->dblspin_coef->setDisabled(true);
        ui->lbl_deg->setDisabled(true);
        ui->dblspin_deg->setDisabled(true);
        ui->lbl_gamma->setEnabled(true);
        ui->dblspin_gamma->setEnabled(true);
        break;
    case K_SIGMOID:
        ui->lbl_coef->setEnabled(true);
        ui->dblspin_coef->setEnabled(true);
        ui->lbl_deg->setDisabled(true);
        ui->dblspin_deg->setDisabled(true);
        ui->lbl_gamma->setEnabled(true);
        ui->dblspin_gamma->setEnabled(true);
        break;
    }
}

void Wizard::slot_typeChanged(int index){
    switch(index){
    case C_SVC:
        ui->lbl_C->setEnabled(true);
        ui->dblspin_C->setEnabled(true);
        ui->lbl_NU->setDisabled(true);
        ui->dblspin_NU->setDisabled(true);
        ui->lbl_p->setDisabled(true);
        ui->dblspin_p->setDisabled(true);
        break;
    case NU_SVC:
        ui->lbl_NU->setEnabled(true);
        ui->dblspin_NU->setEnabled(true);
        ui->lbl_C->setDisabled(true);
        ui->dblspin_C->setDisabled(true);
        ui->lbl_p->setDisabled(true);
        ui->dblspin_p->setDisabled(true);
        break;
    case ONE_CLASS_SVM:
        ui->lbl_NU->setEnabled(true);
        ui->dblspin_NU->setEnabled(true);
        ui->lbl_C->setDisabled(true);
        ui->dblspin_C->setDisabled(true);
        ui->lbl_p->setDisabled(true);
        ui->dblspin_p->setDisabled(true);
        break;
    case EPS_SVR:
        ui->lbl_NU->setDisabled(true);
        ui->dblspin_NU->setDisabled(true);
        ui->lbl_C->setEnabled(true);
        ui->dblspin_C->setEnabled(true);
        ui->lbl_p->setEnabled(true);
        ui->dblspin_p->setEnabled(true);
        break;
    case NU_SVR:
        ui->lbl_NU->setEnabled(true);
        ui->dblspin_NU->setEnabled(true);
        ui->lbl_C->setEnabled(true);
        ui->dblspin_C->setEnabled(true);
        ui->lbl_p->setDisabled(true);
        ui->dblspin_p->setDisabled(true);
        break;
    }
}

bool Wizard::validateCurrentPage (){
    switch(this->currentId()){
    case 1: // page 1
        for(QStringList::iterator it=m_list_windows.begin();it!=m_list_windows.end();++it){
            if((*it).compare(ui->lineEdit->text()) == 0){ // TODO a changer
                QMessageBox msg;
                msg.setText("Error ! An algorithm named '" + ui->lineEdit->text() + "' already exists !");
                msg.exec();
                return false;
            }
        }
        break;
    }
    return true;
}

int Wizard::nextId() const{
    switch (currentId()) {

    case PAGE_INTRO:
        return PAGE_ALG;
        break;

    case PAGE_ALG:
        if(ui->comboBox->currentIndex() == ALG_SVM)
            return PAGE_SVM_PARAMS;
        else
            return PAGE_PER_PARAMS;
        break;

    case PAGE_SVM_PARAMS:
        return PAGE_FINAL;
        break;

    case PAGE_PER_PARAMS:
        return PAGE_FINAL;
        break;

    default:
        return -1;
    }
}

void Wizard::accept(){
    m_algName = ui->wizardPage1->field("algName").toString();
    switch(ui->wizardPage2->field("algType").toInt()){
    case ALG_SVM :
        m_algType = "SVM";
        m_alg = ALG_SVM;
        break;

    case ALG_PER :
        m_algType ="Perceptron";
        m_alg = ALG_PER;
        break;
    }

    QDialog::accept();
}

Wizard::~Wizard()
{
    delete ui;
}

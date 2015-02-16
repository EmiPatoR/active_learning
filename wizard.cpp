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
    ui->wizardPage1->registerField("algName*",ui->lineEdit);
    ui->wizardPage2->registerField("algType",ui->comboBox);
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

void Wizard::accept(){
    m_algName = ui->wizardPage1->field("algName").toString();
    switch(ui->wizardPage2->field("algType").toInt()){
        case 0 :
            m_algType = "SVM";
            break;

        case 1 :
            m_algType ="Perceptron";
            break;
    }

    QDialog::accept();
}

Wizard::~Wizard()
{
    delete ui;
}

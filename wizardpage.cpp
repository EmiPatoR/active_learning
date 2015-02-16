#include "wizardpage.h"

#include <QVariant>

WizardPage::WizardPage(QWidget *parent) :
    QWizardPage(parent)
{

}

void WizardPage::registerField ( const QString& name, QWidget* widget, const char* property, const char* changedSignal ){
    QWizardPage::registerField(name,widget,property,changedSignal);
}

QVariant WizardPage::field(const QString &name) const {
    return QWizardPage::field(name);
}

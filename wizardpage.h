#ifndef WIZARDPAGE_H
#define WIZARDPAGE_H

#include <QWizardPage>

class WizardPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit WizardPage(QWidget *parent = 0);
    void registerField ( const QString& name, QWidget* widget, const char* property = 0, const char* changedSignal = 0 );
    QVariant field(const QString &name) const;

signals:

public slots:

};

#endif // WIZARDPAGE_H

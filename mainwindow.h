#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "subwindow.h"
#include "wizard.h"

#include <QMainWindow>
#include <QTranslator>
#include <QActionGroup>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void printStatus(QString message, unsigned int ms_time = 2000);
    bool initMenu();
    void loadLanguage(const QString& rLanguage);
    Subwindow* newFile(QString name, QString type);
    ~MainWindow();

public slots :
    void slotNotifyClosedWizard(int result);
    void slotLanguageChanged(QAction* action);
    void slotNotifyClosedSubWindow(QString name);
    void slotMaxMin(QModelIndex i);
    void slotNewFile();
    void slotClose();

private:

    // UI Fenetre principale
    Ui::MainWindow*               ui;

    // Fenetre ajout nouvel algo
    Wizard*                       m_w;

    //Listes de fenetres (String)
    QStringList*                 m_listWindows;

    //Liste des fenetres (pointeurs)
    QMap<QString, Subwindow*>    m_wlist;

    //Modeles
    QStringListModel*            m_windows;

    //Traduction
    QTranslator                  m_translator;
    QTranslator                  m_translatorQt;
    QString                      m_currLang;

    //Emplacements
    QString                      m_langPath;
    QString                      m_imgPath;

    //Interface graphique

    //Actions
    QActionGroup*               langGroup; // contient les langues
    QAction*                    actionExit;
    QAction*                    actionNew;
    QAction*                    actionOpen;
    QAction*                    actionSave;
    QAction*                    actionCopy;
    QAction*                    actionCut;
    QAction*                    actionPaste;
    QAction*                    actionFullscreen;

    //Barre de menus
    QMenu*                      menuFile;
    QMenu*                      menuEdit;
    QMenu*                      menuAbout;
    QMenu*                      menuLanguages;

};

#endif // MAINWINDOW_H

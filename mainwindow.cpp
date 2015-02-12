#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subwindow.h"
#include "wizard.h"

#include <iostream>
#include <QDir>
#include <qwt/qwt_plot.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Initialisation de le fenêtre par QT

    //Initisalisation des attributs
    m_w = NULL; // On initisalise la fenetre d'ajout d'algo à null

    //On aggrandi la fenêtre pour occuper tout l'écran
    this->showMaximized();

    //Init de la barre de menu
    if(!initMenu())
        std::cerr << "Cannot initialize menus" << std::endl;

    //Affiche le status "Ready"
    printStatus(tr("Ready"));

}

void MainWindow::slotLanguageChanged(QAction* action){
    if( action != NULL){
        loadLanguage(action->data().toString());
        setWindowIcon(action->icon());
    }
}

void MainWindow::slotNotifyClosedWizard(int result){
    if(result == QDialog::Accepted) // Si tout est OK
    {

    }
    else{ // Sinon on supprime le pointeur
        delete m_w;
        m_w = NULL;
    }
}

void MainWindow::slotClose(){
    ui->mdiArea->closeAllSubWindows();
    this->close();
}

void MainWindow::slotNewFile(){

    if(m_w == NULL){ // Si le wizard n'a pas déja été crée
        m_w = new Wizard(this); // Creation d'un nouveau wizard
        m_w->show(); // Affichage de ce dernier

        //connection
        connect(m_w,SIGNAL(finished(int)),this,SLOT(slotNotifyClosedWizard(int)));
    }
    else // Sinon si on essaye d'en creer un alors qu'il en existe déja un
    {
        m_w->setFocus(); // On lui redonne le focus
    }


    // Subwindow* child = newFile();
    // child->show();
}


Subwindow* MainWindow::newFile(){
    Subwindow *child = new Subwindow();
    ui->mdiArea->addSubWindow(child);
    return child;
}


void switchTranslator(QTranslator& translator, const QString& filename)
{
    // Supprime l'ancien translator
    qApp->removeTranslator(&translator);

    // charge le nouveau translator
    if(translator.load(filename))
        qApp->installTranslator(&translator);

}

void MainWindow::loadLanguage(const QString& rLanguage)
{
    if(m_currLang != rLanguage)
    {
        m_currLang = rLanguage;
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        QString languageName = QLocale::languageToString(locale.language());
        switchTranslator(m_translator, QApplication::applicationDirPath() + QString("/languages/al_%1.qm").arg(rLanguage));
        switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
        statusBar()->showMessage(tr("Current Language changed to %1").arg(languageName));

        //Retraduction des éléments crées dans l'éditeur
        ui->retranslateUi(this);

        //Retraduction des éléments crées dynamiquement

        //Menus

        //Menu "Fichier"
        menuFile->setTitle(tr("&File"));
        actionExit->setText(tr("&Exit"));
        actionExit->setStatusTip(tr("Exit the program."));
        actionSave->setText(tr("&Save"));
        actionSave->setStatusTip(tr("Save the current file."));
        actionOpen->setText(tr("&Open"));
        actionOpen->setStatusTip(tr("Open a file."));
        actionNew->setText(tr("&New"));
        actionNew->setStatusTip(tr("Create a file."));


        //Menu "Edition"
        menuEdit->setTitle(tr("&Edit"));

        //Menu "Langues"
        menuLanguages->setTitle(tr("&Languages"));

        //Menu "A propos de"
        menuAbout->setTitle(tr("&About"));

    }
}

bool MainWindow::initMenu(){

    //Creation du menu des langues

    //Le menu "Languages"
    menuLanguages = new QMenu(tr("&Languages"));

    //Creation du groupe d'actions
    langGroup = new QActionGroup(menuLanguages);
    langGroup->setExclusive(true);

    connect(langGroup,SIGNAL(triggered(QAction*)),this,SLOT(slotLanguageChanged(QAction*)));
    QString defaultLocale = QLocale::system().name(); // on recupere la locale sous forme fr_FR, en_EN, etc...
    defaultLocale.truncate(defaultLocale.lastIndexOf("_")); // on extrait la premiere partie de la locale

    //On defini le repertoire ou sont contenues les traductions
    m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/languages/");

    //On defini le repertoires des images
    m_imgPath = QApplication::applicationDirPath();
    m_imgPath.append("/imgs/");

    //On definit le repertoire ou sont contenues les traductions
    QDir dir(m_langPath);

    //On recupere la liste de toutes les langues disponibles
    QStringList filenames = dir.entryList(QStringList("al_*.qm"));

    //Pour chacune des langues
    for(int i=0 ; i<filenames.size() ; ++i){
        QString locale;
        locale = filenames[i];
        locale.truncate(locale.lastIndexOf(".")); // on enleve l'extension
        locale.remove(0,locale.indexOf("_") + 1); // on recupere que la locale a partir du nom de fichier

        // On definie le nom de la langue a partir de la locale
        QString lang = QLocale::languageToString(QLocale(locale).language());

        // On selectionne l'icone associée a la locale
        QIcon ico (QString("%1%2.png").arg(m_langPath).arg(locale));

        //On creer l'action correspondante
        QAction *action = new QAction(ico,lang,this);
        action->setStatusTip(tr("Change language"));
        action->setCheckable(true);
        action->setData(locale);

        //On ajoute l' action au menu
        menuLanguages->addAction(action);
        langGroup->addAction(action);

        //Si l'action est le language actuel, on le coche
        if (defaultLocale == locale)
        {
            action->setChecked(true);
        }

    }

    //Creation des autres menus
    //Le menu "File"
    menuFile = new QMenu(tr("&File"));
    //Le menu "Edit"
    menuEdit = new QMenu(tr("&Edit"));
    //Le menu "About"
    menuAbout = new QMenu(tr("&About"));

    //L'action "Exit"
    actionExit = new QAction(QIcon(m_imgPath + QString("new.png")),tr("&Exit"),this);
    actionExit->setShortcuts(QKeySequence::Quit);
    actionExit->setStatusTip(tr("Exit the program."));

    //L'action "New"
    actionNew = new QAction(QIcon(m_imgPath + QString("new.png")),tr("&New"),this);
    actionNew->setShortcuts(QKeySequence::New);
    actionNew->setStatusTip(tr("Create a new file."));

    //L'action "Open"
    actionOpen = new QAction(QIcon(m_imgPath + QString("open.png")),tr("&Open"),this);
    actionOpen->setShortcuts(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Open a file."));

    //L'action "Save"
    actionSave = new QAction(QIcon(m_imgPath + QString("save.png")),tr("&Save"),this);
    actionSave->setShortcuts(QKeySequence::Save);
    actionSave->setStatusTip(tr("Save the current file."));

    //L'action "Copy"
    actionCopy = new QAction(QIcon(m_imgPath + QString("copy.png")),tr("&Copy"),this);
    actionCopy->setShortcuts(QKeySequence::Copy);
    actionCopy->setStatusTip(tr("Copy to clipboard."));

    //L'action "Cut"
    actionCut = new QAction(QIcon(m_imgPath + QString("cut.png")),tr("&Cut"),this);
    actionCut->setShortcuts(QKeySequence::Cut);
    actionCut->setStatusTip(tr("Cut to clipboard."));

    //L'action "Paste"
    actionPaste = new QAction(QIcon(m_imgPath + QString("paste.png")),tr("&Paste"),this);
    actionPaste->setShortcuts(QKeySequence::Paste);
    actionPaste->setStatusTip(tr("Paste content from clipboard."));

    //Ajout des actions au menu "File" et à la toolbar
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionExit);
    ui->mainToolBar->addAction(actionNew);
    ui->mainToolBar->addAction(actionOpen);
    ui->mainToolBar->addAction(actionSave);


    ui->mainToolBar->addSeparator(); // Separateur

    //Ajout des actions au menu "Edit" et à la toolbar
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionPaste);
    ui->mainToolBar->addAction(actionCopy);
    ui->mainToolBar->addAction(actionCut);
    ui->mainToolBar->addAction(actionPaste);


    //Ajout des menus a la barre de menu
    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuEdit);
    menuBar()->addMenu(menuLanguages);
    menuBar()->addMenu(menuAbout);


    //Connexions
    connect(actionExit,SIGNAL(triggered()),this,SLOT(slotClose()));
    connect(actionNew,SIGNAL(triggered()),this,SLOT(slotNewFile()));

    return true;
}

void MainWindow::printStatus(QString message, unsigned int ms_time)
{
    statusBar()->clearMessage();
    statusBar()->showMessage(message, ms_time);
}

MainWindow::~MainWindow()
{
    delete ui;
}

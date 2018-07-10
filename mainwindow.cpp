#include "mainwindow.h"
#include "settings.h"
#include <QDebug>
#include <QtWidgets>
#include <QJsonDocument>
#include <QFont>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    setFixedSize(500,600);
    setWindowTitle("WordPad");
    mainWidget=new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->setFixedSize(this->width(),this->height());
    mainLayout=new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    textArea=new QTextEdit;
    mainLayout->addWidget(textArea);
    createActions();
    setUnifiedTitleAndToolBarOnMac(true);
    SizeFont=14;
    ColorFont="color: #000000";
    textArea->setStyleSheet("color: #000000");
    font.setPointSize(SizeFont);
    textArea->setFont(font);

}

void MainWindow::newFile()
{
    textArea->clear();
}

void MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Saved!");
        msgBox.exec();

    }

}
void MainWindow::saveAs()
{

    QString filename = QFileDialog::getSaveFileName(
                this, "Write file",
                ".","Text (*.txt)");
    curFile = filename;
    if(filename.size()!=0)
    {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream stream(&file);
    stream<<textArea->toHtml()<<endl;
    file.close();
    }

}

void MainWindow::info()
{
    QMessageBox msgBox;
    msgBox.setText("Programming by Nikos Kontothanasis");
    msgBox.exec();

}

void MainWindow::help()
{
    QMessageBox::about(this, "Help ",
                       "Help!"
                       "<br>"
                       "<br>"
                       "Με την εφαρμογή WordPad έχετε την δυνατότητα:"
                       "<ul>"
                       "<li><i> Δημηουργίας κειμένου </i></li>"
                       "<li><i> Επεξεργασίας & Αποθήκευσης κειμένου </i></li>"
                       "<li><i> Φόρτωση & Αποθήκευση ρυθμίσεων </i></li>"
                       "</ul>");
}

void MainWindow::loadSettings()
{
    QJsonObject obj;
    QString s;

    QString jfilename=QFileDialog::getOpenFileName(
                this, "Open File",
                ".","Json file (*.JSON)");
    if(jfilename.size()!=0)
    {
    QFile jsonfile(jfilename);
    if (!jsonfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    s=jsonfile.readAll();
      QJsonDocument doc=QJsonDocument::fromJson(s.toUtf8());
      obj=doc.object();

    ColorFont=obj["color"].toString();
    SizeFont=obj["size"].toInt();
    qDebug()<<"__ "<<obj;
    textArea->setStyleSheet(ColorFont);
    font.setPointSize(SizeFont);
    textArea->setFont(font);

    QMessageBox msgBox;
    msgBox.setText("Settings loaded!");
    msgBox.exec();
    }
}

void MainWindow::saveSettings(QString colorF, int sizeF)
{
    Settings settings1(colorF,sizeF);
    QJsonObject ob1=settings1.toObject();
    qDebug()<<"__ "<<ob1;

    QJsonDocument jdoc(ob1);

        QString jfilename = QFileDialog::getSaveFileName(
                    this, "Write file",
                    ".","JSON (*.JSON)");
        if(jfilename.size()!=0)
        {
        QFile jsonfile(jfilename);
        if (!jsonfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    jsonfile.write(jdoc.toJson());

    QMessageBox msgBox;
    msgBox.setText("Settings saved!");
    msgBox.exec();
}
}

void MainWindow::exit()
{
     qApp->exit(0);
}

void MainWindow::createActions()
{
    fileMenu=new QMenu("File");
    fileMenu->addAction("New");
    fileMenu->addAction("Save");
    fileMenu->addAction("Save As");
    fileMenu->addAction("Terminate");
    connect(fileMenu,SIGNAL(triggered(QAction*)),this,SLOT(fileSlot(QAction*)));

    editMenu=new QMenu("Edit");
    fontColorMenu=editMenu->addMenu(tr("Font Color"));
    fontColorMenu->addAction("Red");
    fontColorMenu->addAction("Green");
    fontColorMenu->addAction("Blue");
    fontColorMenu->addAction("Yellow");
    fontColorMenu->addAction("Pink");
    connect(fontColorMenu,SIGNAL(triggered(QAction*)),this,SLOT(fontColorSlot(QAction*)));
    editMenu->addAction("Font Size");
    editMenu->addAction("Save Settings");
    editMenu->addAction("Load Settings");
    connect(editMenu,SIGNAL(triggered(QAction*)),this,SLOT(editSlot(QAction*)));

    aboutMenu=new QMenu("About");
    aboutMenu->addAction("Help");
    aboutMenu->addAction("Info");
    connect(aboutMenu,SIGNAL(triggered(QAction*)),this,SLOT(aboutSlot(QAction*)));

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(aboutMenu);

}
void    MainWindow::fileSlot(QAction *action)
{
   if(action->text()=="New")
   {
       newFile();
   }
   else
   if(action->text()=="Save")
   {
       save();
   }
   else
   if(action->text()=="Save As")
   {
       saveAs();
   }
   else
   if(action->text()=="Terminate")
   {
       exit();
   }
}

void    MainWindow::editSlot(QAction *action)
{
    if(action->text()=="Load Settings")
    {
        loadSettings();
    }
    else
        if(action->text()=="Save Settings")
        {
            saveSettings(ColorFont,SizeFont);
        }
    else if(action->text()=="Font Size")
        {
            bool ok;
            QFont font = QFontDialog::getFont(&ok, this);
            if(ok)
            {
                textArea->setFont(font);
                SizeFont=font.pointSize();
                qDebug()<<SizeFont;

            }
        }
}

void    MainWindow::aboutSlot(QAction *action)
{
    if(action->text()=="Help")
    {
        help();
    }
    else if(action->text()=="Info")
    {
        info();
    }

}

void MainWindow::fontColorSlot(QAction *action)
{
    if(action->text()=="Red")
    {
        textArea->setStyleSheet("color: #FF0000");
        ColorFont="color: #FF0000";
    }
    else
    if(action->text()=="Green")
    {
        textArea->setStyleSheet("color: #008000");
        ColorFont="color: #008000";
    }
    else
    if(action->text()=="Blue")
    {
        textArea->setStyleSheet("color: #1E90FF");
        ColorFont="color: #1E90FF";
    }
    else
    if(action->text()=="Yellow")
    {
        textArea->setStyleSheet("color: #FFFF00");
        ColorFont="color: FFFF00";
    }
    else
    if(action->text()=="Pink")
    {
        textArea->setStyleSheet("color: #FF1493");
        ColorFont="color: #FF1493";
    }
}

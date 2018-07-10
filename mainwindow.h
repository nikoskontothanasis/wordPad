#ifndef MAINWINDOW_H
#define MAINWINDOW_H
# include <QMainWindow>
# include <QAction>
# include <QMenu>
# include <QPlainTextEdit>
# include <QSessionManager>
# include <QVBoxLayout>
# include <QLabel>
# include <QTextStream>
# include <QFileDialog>
# include <QFile>
# include <QSlider>
# include <QFont>
# include <QWidgetAction>
# include <QBoxLayout>
# include <QJsonObject>
# include <QPushButton>
#include<QJsonValue>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = 0);
     QString ColorFont;
     int SizeFont;
private slots:
    void fileSlot(QAction *action);
    void editSlot(QAction *action);
    void aboutSlot(QAction *action);
    void fontColorSlot(QAction *action);
    void newFile();
    void save();
    void saveAs();
    void exit();
    void help();
    void info();
    void loadSettings();
    void saveSettings(QString colorF, int sizeF);

private:
        void createActions();
        QMenu *fileMenu,*editMenu, *aboutMenu, *fontColorMenu;
        QTextEdit *textArea;
        QWidget *mainWidget;
        QVBoxLayout *mainLayout, *fontLayout;
        QTextStream *stream;
        QFont font;
        QString curFile;
};

#endif // MAINWINDOW_H

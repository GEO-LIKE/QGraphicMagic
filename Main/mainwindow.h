#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shapeplugininterface.h"
#include "plugindialog.h"
#include "ifile.h"
#include <QPainter>
#include <QToolBar>
#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPluginLoader>
#include <QFileInfoList>
#include <QMenu>
#include <QMenuBar>
namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void pluginLoaded();

private:
    void getPluginList();
    void aboutPlugin();
    Ui::MainWindow *ui;

    QStringList pluginList;
    QMenu *menu;
};

#endif // MAINWINDOW_H

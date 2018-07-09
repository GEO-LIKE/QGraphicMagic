#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PLUGIN_SUBFOLDER "/plugins/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(pluginLoaded()),this,SLOT(on_pluginLoaded()));
    getPluginList();
    menu = menuBar()->addMenu(tr("&About"));
    QAction *aboutPluginAction = menu->addAction("About Plugin");
    connect(aboutPluginAction,&QAction::triggered,this,&MainWindow::aboutPlugin);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getPluginList()
{
    QDir pluginsDir(qApp->applicationDirPath() +
                    PLUGIN_SUBFOLDER);
    QFileInfoList plugins = pluginsDir.entryInfoList(
                QDir::NoDotAndDotDot |
                QDir::Files,
                QDir::Name);
    foreach (QFileInfo plugin, plugins) {
        if(QLibrary::isLibrary(plugin.absoluteFilePath())){
            QPluginLoader pluginLoader(plugin.absoluteFilePath(),this);
            if(dynamic_cast<ShapePluginInterface*>(pluginLoader.instance())) {
                pluginList.append(plugin.fileName());
                ShapePluginInterface *shape_plugin =
                        dynamic_cast<ShapePluginInterface*>(pluginLoader.instance());
                shape_plugin->initialization(this);
//                pluginLoader.unload();
                emit pluginLoaded();
            }
            else{
                QMessageBox::warning(
                            this,tr("Warring"),
                            QString(tr("Make sure %1 is a coorrect"
                                       "plugin for this application<br>"
                                       "and it's not in use by some other"
                                       "application!").arg(plugin.fileName())));

            }
        }
        else{
            QMessageBox::warning(this, tr("Warning"),
                            QString(tr("Make sure only plugins"
                                " exist in plugins folder.<br>"
                                "%1 is not a plugin."))
                                .arg(plugin.fileName()));
        }
        if(pluginList.count() <= 0)
                  {
                    QMessageBox::critical(this, tr("No Plugins"),
                    tr("This application cannot work without plugins!"
                    "<br>Make sure that filter_plugins folder exists "
                    "in the same folder as the application<br>and that "
                    "there are some filter plugins inside it"));
                    this->setEnabled(false);
                  }
    }
}

void MainWindow::aboutPlugin()
{
    PluginDIalog dialog(pluginList,qApp->applicationDirPath() + PLUGIN_SUBFOLDER, this);
    dialog.exec();
}



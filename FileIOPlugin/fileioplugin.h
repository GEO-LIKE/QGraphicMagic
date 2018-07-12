#ifndef FILEIOPLUGIN_H
#define FILEIOPLUGIN_H

#include "fileioplugin_global.h"
#include "ifile.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QSvgRenderer>
#include <QSvgGenerator>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSvgItem>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QApplication>
#include <QStyle>
class FILEIOPLUGINSHARED_EXPORT FileIOPlugin:
        public QObject,
        public IFile
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.geolike.ifile")
    Q_INTERFACES(IFile)
public:
    FileIOPlugin();
    ~FileIOPlugin();

    QString description();
    void Initilization(QMainWindow *window);

    QGraphicsScene *getScene(QMainWindow *window);
    QGraphicsView *getView(QMainWindow *window);

    void openFile(QMainWindow *window);
    bool loadFile(QString &fileName, QMainWindow *window);

    void openSvgFile(QString &fileName, QGraphicsScene *scene);

    void saveFile(QMainWindow *window);
    void saveSvgFile(QString &fileName, QGraphicsView *view);

    QToolBar *createToolBar();

signals:
    void fileOpen();
    void fileSave();

};

#endif // FILEIOPLUGIN_H

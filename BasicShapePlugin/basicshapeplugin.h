#ifndef BASICSHAPEPLUGIN_H
#define BASICSHAPEPLUGIN_H

#include "basicshapeplugin_global.h"
#include "shapeplugininterface.h"
#include <QtPlugin>
#include <QDebug>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDockWidget>
#include <qcustomgraphicsscene.h>

class BASICSHAPEPLUGINSHARED_EXPORT BasicShapePlugin:
        public QObject,
        public ShapePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.geolike.shapeplugininterface")
    Q_INTERFACES(ShapePluginInterface)

public:
    BasicShapePlugin();
    ~BasicShapePlugin();
    QString description();
    void initialization(QMainWindow* window);
    QToolBar* createToolBar();
signals:
    void shapeTypeChanged(QCustomGraphicsScene::ItemType);

//public slots:
//    void on_Action_triggered(QCustomGraphicsScene *scene);

private:
    QGraphicsView *view = new QGraphicsView;
    QCustomGraphicsScene *scene = new QCustomGraphicsScene;
};

#endif // BASICSHAPEPLUGIN_H

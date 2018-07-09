#include "basicshapeplugin.h"


BasicShapePlugin::BasicShapePlugin(){}

BasicShapePlugin::~BasicShapePlugin(){}

QString BasicShapePlugin::description()
{
    return "This is a plugin to generate shapes.";
}

void BasicShapePlugin::initialization(QMainWindow *window)
{
//    auto *toolBar = new QToolBar;
//    auto *addShapeAction = toolBar->addAction("Shapes");
//    addShapeAction->setToolTip("Return a shape");
//    connect(addShapeAction, &QAction::triggered, this, &BasicShapePlugin::on_Action_triggered);
//    connect(addShapeAction, &QAction::triggered, [this](){on_Action_triggered(scene);});
//    window->addToolBar(toolBar);
    scene->setSceneRect(-200,-200,200,200);
    view->setScene(scene);
    view->setMouseTracking(true);
    connect(this,&BasicShapePlugin::shapeTypeChanged,
            scene,&QCustomGraphicsScene::setItemType);
    QDockWidget *leftDockWidget = new QDockWidget;
    QWidget *widget = new QWidget;
    leftDockWidget->setWidget(widget);
    window->addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget);
    window->setCentralWidget(view);
    auto *shapeToolBar =  createToolBar();
    window->addToolBar(shapeToolBar);
}

QToolBar* BasicShapePlugin::createToolBar()
{
    auto *toolBar = new QToolBar;
    QAction *insertPointAction =toolBar->addAction(
                QIcon(QCustomGraphicsItem::image(QCustomGraphicsItem::ITEM_POINT)),
                tr("Draw Point"));

    QAction *insertLineAction = toolBar->addAction(
                QIcon(QCustomGraphicsItem::image(QCustomGraphicsItem::ITEM_LINE)),
                tr("Draw Line"));
    QAction *insertPolygonAction = toolBar->addAction(
                QIcon(QCustomGraphicsItem::image(QCustomGraphicsItem::ITEM_POLYGON)),
                tr("Draw Polygon"));
    connect(insertPointAction,&QAction::triggered,
            [this](){emit shapeTypeChanged(QCustomGraphicsScene::POINT);});
    connect(insertLineAction,&QAction::triggered,
            [this](){emit shapeTypeChanged(QCustomGraphicsScene::LINE);});
    connect(insertPolygonAction,&QAction::triggered,
            [this](){emit shapeTypeChanged(QCustomGraphicsScene::POLYGON);});
    return toolBar;
}





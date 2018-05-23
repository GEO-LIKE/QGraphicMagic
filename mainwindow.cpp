#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QCustomGraphicsScene;
    scene->setSceneRect(0,0,100,100);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);

    connect(this,&MainWindow::itemTypeChange,
            scene,&QCustomGraphicsScene::setItemType);

    createActions();
    createMenu();
    createToolBar();
    createItemBar();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"), tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered(bool)), this, SLOT(bringToFront()));

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+T"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered(bool)), this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item"));
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteItem()));
}

void MainWindow::createMenu()
{
    menu = menuBar()->addMenu(tr("&Item"));
    menu->addAction(deleteAction);
    menu->addSeparator();
    menu->addAction(toFrontAction);
    menu->addAction(sendBackAction);
}

void MainWindow::createToolBox()
{

}

void MainWindow::createToolBar()
{
    ui->mainToolBar = addToolBar(tr("Edit"));
    ui->mainToolBar->addAction(deleteAction);
    ui->mainToolBar->addAction(toFrontAction);
    ui->mainToolBar->addAction(sendBackAction);
}

void MainWindow::createItemBar()
{
    QAction *insertPointAction =
            new QAction(QIcon(QCustomGraphicsItem::image(QCustomGraphicsItem::ITEM_POINT)),
                    tr("Draw Point"), this);
    QAction *insertLineAction =
            new QAction(QIcon(
                    QCustomGraphicsItem::image(QCustomGraphicsItem::ITEM_LINE)),
                    tr("Draw Line"), this);
    QAction *insertPolygonAction =
            new QAction(QIcon(
                    QCustomGraphicsItem::image(QCustomGraphicsItem::ITEM_POLYGON)),
                    tr("Draw Polygon"), this);
    connect(insertPointAction,SIGNAL(triggered(bool)),this,SLOT(on_pointBtn_clicked()));
    connect(insertLineAction,SIGNAL(triggered(bool)),this,SLOT(on_lineBtn_clicked()));
    connect(insertPolygonAction,SIGNAL(triggered(bool)),this,SLOT(on_polygonBtn_clicked()));

//    shapeBar = new QToolBar(tr("Shape Items"));
    ui->mainToolBar = addToolBar(tr("Shape Items"));
    ui->mainToolBar->addAction(insertPointAction);
    ui->mainToolBar->addAction(insertLineAction);
    ui->mainToolBar->addAction(insertPolygonAction);
}

void MainWindow::createCellWidget()
{

}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::bringToFront()
{
    if(scene->selectedItems().isEmpty())
        return;
    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if(item->zValue() >= zValue && item->type() == QCustomGraphicsItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::sendToBack()
{
    if(scene->selectedItems().isEmpty())
        return;
    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();
    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if(item->zValue() >= zValue && item->type() == QCustomGraphicsItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::on_pointBtn_clicked()
{
emit itemTypeChange(QCustomGraphicsScene::POINT);

}

void MainWindow::on_lineBtn_clicked()
{
emit itemTypeChange(QCustomGraphicsScene::LINE);

}

void MainWindow::on_polygonBtn_clicked()
{
emit itemTypeChange(QCustomGraphicsScene::POLYGON);

}


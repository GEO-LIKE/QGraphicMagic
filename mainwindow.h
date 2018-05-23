#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomgraphicsscene.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void createActions();
    void createMenu();
    void createToolBox();
    void createToolBar();
    void createItemBar();
    void createCellWidget();
public slots:
    void deleteItem();
    void bringToFront();
    void sendToBack();

signals:
    void itemTypeChange(QCustomGraphicsScene::ItemType);

private slots:

    void on_pointBtn_clicked();
    void on_lineBtn_clicked();
    void on_polygonBtn_clicked();

private:
    Ui::MainWindow *ui;
    QCustomGraphicsScene *scene;
    // Actions
    QAction *deleteAction;
    QAction *toFrontAction;
    QAction *sendBackAction;
    // Menu
    QMenu *menu;
    // Shape Item
    QToolBar *shapeBar;
};

#endif // MAINWINDOW_H

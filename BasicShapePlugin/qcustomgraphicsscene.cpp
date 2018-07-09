#include "qcustomgraphicsscene.h"
#include <QDebug>

QCustomGraphicsScene::QCustomGraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{
    isDrawing = false;
    initDrawing();
}

void QCustomGraphicsScene::initDrawing()
{
    qDebug() << "Initialization";

    isReleased = false;
    lineMode = LineMode::SEGEMNT_MODE;
    length = 0;
    points.clear();
}

void QCustomGraphicsScene::setItemType(QCustomGraphicsScene::ItemType type)
{
    if(!points.isEmpty()){
        item->updatePoints(points);
    }
    isDrawing = true;
    itemType = type;
    initDrawing();
}

void QCustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << isDrawing;
    if(!isDrawing){
        QGraphicsScene::mousePressEvent(event);
    }
    else{
        if(points.isEmpty()){
            item = new QCustomGraphicsItem(QCustomGraphicsItem::ItemType(itemType));
            addItem(item);
        }
        points.append(event->scenePos());
        item->updatePoints(points);
        if(itemType == POINT)
            initDrawing();
        length += 1;
        qDebug() << length;
    }
//    QGraphicsScene::mousePressEvent(event);

}

void QCustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isDrawing){
        QGraphicsScene::mouseMoveEvent(event);
    }
    else{
        if(points.isEmpty())
        {
//            if(itemType == POINT){
//                item->mouseTracker(points, event->scenePos());
//            }
            QGraphicsScene::mouseMoveEvent(event);
        }else{
            item->mouseTracker(points, event->scenePos());
        }
        // 画线
        if(length == 1 && !isReleased && itemType == LINE)
            lineMode = LineMode::SEGEMNT_MODE;
        else
            lineMode = LineMode::CONTINUOUS_MODE;
//        update();
    }
    update();
}

void QCustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isDrawing){
        QGraphicsScene::mouseReleaseEvent(event);
    }
    else{
        isReleased = true;
        if(lineMode == LineMode::SEGEMNT_MODE){
            points.append(event->scenePos());
            item->updatePoints(points);
            initDrawing();
        }
    }
}

void QCustomGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    isDrawing = false;
//    item->setSelected(true);
    initDrawing();
}


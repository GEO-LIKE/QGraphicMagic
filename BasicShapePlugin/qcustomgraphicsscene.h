#ifndef QCUSTOMGRAPHICSSCENE_H
#define QCUSTOMGRAPHICSSCENE_H

#include "qcustomgraphicsitem.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class QCustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QCustomGraphicsScene(QObject *parent = 0);
    enum LineMode {SEGEMNT_MODE, CONTINUOUS_MODE};
    enum ItemType {POINT, LINE, POLYGON};
    void initDrawing();

public slots:
    void setItemType(ItemType type);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool isDrawing;
    bool isReleased;
    QPointF lastPressed;
    int length;
    LineMode lineMode;
    ItemType itemType;
//    QGraphicsLineItem *line;
    QCustomGraphicsItem *item;
    QVector<QPointF> points;
};

#endif // QCUSTOMGRAPHICSSCENE_H

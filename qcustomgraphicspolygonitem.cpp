#include "qcustomgraphicspolygonitem.h"

QCustomGraphicsPolygonItem::QCustomGraphicsPolygonItem(QGraphicsItem * parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
}

void QCustomGraphicsPolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::green,2));
    painter->setBrush(QBrush(Qt::lightGray));
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawPolygon(mPolygon);

}

QRectF QCustomGraphicsPolygonItem::boundingRect() const
{
    return mRect;
}

QPainterPath QCustomGraphicsPolygonItem::shape() const
{
    QPainterPath path;
    path.addPolygon(mPolygon);
    return path;
}

void QCustomGraphicsPolygonItem::setPolygon(QVector<QPointF> pointList)
{
//    foreach (QPointF point, pointList) {
//        mPolygon.append();
//    }
    mPolygon.append(pointList);
    mRect = mPolygon.boundingRect();
    update();
}

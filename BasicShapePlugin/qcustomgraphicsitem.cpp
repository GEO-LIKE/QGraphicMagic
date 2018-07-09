#include "qcustomgraphicsitem.h"
#include <QDebug>

QCustomGraphicsItem::QCustomGraphicsItem(ItemType type, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    qDebug() << type;
    mType = type;
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
}

void QCustomGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen(QBrush(Qt::red),2));
    painter->setBrush(QBrush(Qt::lightGray));
    painter->setRenderHint(QPainter::Antialiasing);

    switch(mType){
    case ITEM_POINT:
        foreach (QPointF point, mPoints) {
            painter->drawEllipse(point,2,2);
        }
        break;
    case ITEM_LINE:
        foreach (QPointF point, mPoints) {
            painter->drawEllipse(point,2,2);
        }
        for(int i = 1; i < mPoints.length(); i++ ){
            painter->drawLine(mPoints[i-1], mPoints[i]);
        }
        break;
    case ITEM_POLYGON:
        painter->drawPolygon(mPolygon);
        break;
    default:
        foreach (QPointF point, mPoints) {
            painter->drawEllipse(point,2,2);
        }
    }

}

QPainterPath QCustomGraphicsItem::shape() const
{
    QPainterPath path;
    foreach(QPointF point, mPolygon){
        path.addEllipse(point,20,20);
        if(mType == ITEM_LINE)
            path.lineTo(point);
    }
    switch(mType){
    case ITEM_LINE:
        path.addPolygon(mPolygon);

    case ITEM_POLYGON:
        path.addPolygon(mPolygon);
    }
    QPainterPathStroker stroker;
    stroker.setCapStyle(Qt::RoundCap);  // 端点风格
    stroker.setJoinStyle(Qt::RoundJoin);  // 连接样式
    stroker.setDashPattern(Qt::DashLine);  // 虚线图案
    stroker.setWidth(2);  // 宽度
    QPainterPath outLinePath = stroker.createStroke(path);
    path.addPath(outLinePath);
    return path;
}

QRectF QCustomGraphicsItem::boundingRect() const
{
    QRectF newRect;
    newRect = QRectF(mRect.topLeft()+QPointF(-2,-2),
                     mRect.bottomRight()+QPointF(2,2));
    return newRect;
}

void QCustomGraphicsItem::updatePoints(QVector<QPointF> &points)
{
    prepareGeometryChange();
    mPoints.clear();
    mPoints.append(points);
    mPolygon = QPolygonF(mPoints);
    mRect = mPolygon.boundingRect();
}

void QCustomGraphicsItem::mouseTracker(QVector<QPointF> &points, QPointF point)
{
    prepareGeometryChange();
    mPoints.clear();
//    if(!points.isEmpty())
    mPoints.append(points);
    mPoints.append(point);
    mPolygon = QPolygonF(mPoints);
}

QPixmap QCustomGraphicsItem::image(QCustomGraphicsItem::ItemType type)
{
    QPixmap pixmap(150,150);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QPainterPath path;
    switch(type){
    case ITEM_POINT:
        path.addEllipse(QPointF(0,0),10,10);
        break;
    case ITEM_LINE:
        path.moveTo(-50,-50);
        path.lineTo(30,-30);
        path.lineTo(-30,30);
        path.lineTo(50,50);
        break;
    case ITEM_POLYGON:
        QPolygonF polygon;
        polygon << QPointF(-50,50)<<QPointF(-30,-50)
                 << QPointF(30,-30)<<QPointF(50,50)
                 << QPointF(-50,50);

        path.addPolygon(polygon);
        break;
    }
    painter.setPen(QPen(Qt::black,8));
    painter.translate(75,75);
    painter.drawPath(path);
    return pixmap;
}

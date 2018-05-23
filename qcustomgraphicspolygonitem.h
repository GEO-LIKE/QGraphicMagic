#ifndef QCUSTOMGRAPHICSPOLYGONITEM_H
#define QCUSTOMGRAPHICSPOLYGONITEM_H

#include <QGraphicsItem>
#include <QPainter>

class QCustomGraphicsPolygonItem : public QGraphicsItem
{
public:
    enum {Type = UserType + 1};
    QCustomGraphicsPolygonItem(QGraphicsItem * parent = nullptr);
    void setPolygon(QVector<QPointF> pointList);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape () const override;
    int type() const{return Type;}

private:
    QVector<QPointF> mPointList;
    QPolygonF mPolygon;
    QRectF mRect;
};

#endif // QCUSTOMGRAPHICSPOLYGONITEM_H

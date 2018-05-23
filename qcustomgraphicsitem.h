#ifndef QCUSTOMGRAPHICSITEM_H
#define QCUSTOMGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>

class QCustomGraphicsItem : public QGraphicsItem
{
public:
    enum {Type = UserType + 1};
    enum ItemType{ITEM_POINT, ITEM_LINE, ITEM_POLYGON};
    QCustomGraphicsItem(ItemType type, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const;
    QRectF boundingRect() const;
    int type(){return Type;}

    void updatePoints(QVector<QPointF> &points);
    void mouseTracker(QVector<QPointF> &points, QPointF point);

    static QPixmap image(ItemType type);
private:
    QVector<QPointF> mPoints;
    QPolygonF mPolygon;
    QRectF mRect;
    ItemType mType;
};

#endif // QCUSTOMGRAPHICSITEM_H

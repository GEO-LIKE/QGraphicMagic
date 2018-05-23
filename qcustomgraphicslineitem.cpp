#include "qcustomgraphicslineitem.h"

QCustomGraphicsLineItem::QCustomGraphicsLineItem(QGraphicsItem *parent)
    :QGraphicsLineItem(parent)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
}

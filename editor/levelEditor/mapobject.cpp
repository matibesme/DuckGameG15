#include "mapobject.h"

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QList>

MapObject::MapObject(const QPixmap &pixmap, const QString &type, QGraphicsItem *parent)
        : QGraphicsPixmapItem(pixmap, parent), type(type) {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QString MapObject::get_type(){
    return this->type;
}
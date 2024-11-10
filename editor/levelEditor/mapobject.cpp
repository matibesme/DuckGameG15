#include "mapobject.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QList>
#include <QMainWindow>

MapObject::MapObject(const QPixmap& pixmap, const QString& type, QGraphicsItem* parent):
        QGraphicsPixmapItem(pixmap, parent), type(type) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QString MapObject::get_type() { return this->type; }
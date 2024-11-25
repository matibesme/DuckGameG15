#include "mapobject.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsView>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QMenu>
MapObject::MapObject(const QPixmap &pixmap, const QString &type,
                     QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent), type(type) {
  setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QString MapObject::get_type() { return this->type; }

void MapObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  QMenu menu;
  QAction *action = menu.addAction("Delete");

  QAction *selected = menu.exec(event->screenPos());

  if (selected == action) {
    this->setVisible(false);
    this->setEnabled(false);
    this->setFlag(QGraphicsItem::ItemIsSelectable, false);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
  }
}

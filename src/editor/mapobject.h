#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QList>
#include <QMainWindow>

class MapObject : public QGraphicsPixmapItem {
public:
  MapObject(const QPixmap &pixmap, const QString &type,
            QGraphicsItem *parent = nullptr);
  QString get_type();

protected:
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
  QString type;
};

#endif

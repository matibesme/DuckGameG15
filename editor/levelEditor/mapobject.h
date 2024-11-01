#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QList>

class MapObject : public QGraphicsPixmapItem {
public:
    MapObject(const QPixmap &pixmap, const QString &type, QGraphicsItem *parent = nullptr);
    QString get_type();

private:
    QString type; 
};

#endif
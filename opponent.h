#ifndef OPPONENT_H
#define OPPONENT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QSize>

//виртуальный класс опонента, от него наследуется класс врага(Enemy) и босса(Boss)
//Opponent наследуется от QObject и QGraphicsPixmapItem, чтобы потомки могли корректно передвигаться
//и иметь собственные модели
class Opponent : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  virtual ~Opponent() = default;
  virtual void decreaseHealth(int damage) = 0;
  virtual QSize getSize() const = 0;
public slots:
  virtual void onMove() = 0;
};

#endif // OPPONENT_H

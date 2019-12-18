#ifndef OPPONENT_H
#define OPPONENT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QSize>

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

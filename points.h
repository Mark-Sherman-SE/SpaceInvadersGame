#ifndef POINTS_H
#define POINTS_H


#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
//#include <QKeyEvent>

#include "player.h"

class Points : public QGraphicsTextItem
{
public:
  Points(QGraphicsItem *pParent = nullptr);

  void increaseScore(int points);
  void decreaseScore();
  void decreaseHealth();

  int getHealth() const;
  int getScore() const;

  void reset();

private:
  int m_nHealth = 100;
  int m_nScore = 0;
};

#endif // POINTS_H

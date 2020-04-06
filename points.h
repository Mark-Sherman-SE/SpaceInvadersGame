#ifndef POINTS_H
#define POINTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>

//класс очков, необходим для вывода очков и здоровья на экран
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
  //здоровье базы по умолчанию
  int m_nHealth = 100;
  //счёт по умолчанию
  int m_nScore = 0;
};

#endif // POINTS_H

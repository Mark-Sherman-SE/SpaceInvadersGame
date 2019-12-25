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

  //метод увеличения очков
  void increaseScore(int points);
  //метод уменьшения очков
  void decreaseScore();
  //метод меньшения здоровья
  void decreaseHealth();

  //получаем количество жизней
  int getHealth() const;
  //получаем количество очков
  int getScore() const;

  //метод для перезапуска счёта
  void reset();

private:
  //здоровье базы по умолчанию
  int m_nHealth = 100;
  //счёт по умолчанию
  int m_nScore = 0;
};

#endif // POINTS_H

#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>

#include "opponent.h"

//описываем возможные типы врагов
enum class EnemyType
{
    Corporal, Interceptor, Fighter, Destroyer, Exterminator
};

//в качестве глобальных констант задаём размеры каждого врага
const QSize CORPORAL_SIZE = QSize(150, 70);
const QSize INTERCEPTOR_SIZE = QSize(70, 50);
const QSize FIGHTER_SIZE = QSize(190, 85);
const QSize DESTROYER_SIZE = QSize(220, 100);
const QSize EXTERMINATOR_SIZE = QSize(340, 190);

//класс врага, наследуется от Opponent
class Enemy :  public Opponent
{
  Q_OBJECT
public:
  Enemy(EnemyType enemyType, QGraphicsItem *pParent = nullptr);

  EnemyType getType() const;
  void setType(EnemyType enemyType);
  void decreaseHealth(int damage) override;

  QSize getSize() const override;

signals:
  //необходимые сигналы для корректного вычисления счёта, здоровья и момента конца игры
  void sigIncreaseScore(int);
  void sigDecreaseHealth();
  void sigGameOver();

public slots:
  //метод для передвижения врага
  void onMove() override;

private:
  EnemyType enemyType_;
  QTimer *pTimer;
  QSize size_;
  int enemySpeed_;
  int enemyHealth_;
  int points_;
};

#endif // ENEMY_H

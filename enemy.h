#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
//#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QSize>
//#include <QKeyEvent>
#include <QTimer>

#include "opponent.h"

enum class EnemyType
{
    Corporal, Interceptor, Fighter, Destroyer, Exterminator
};

const QSize CORPORAL_SIZE = QSize(150, 70);
const QSize INTERCEPTOR_SIZE = QSize(70, 50);
const QSize FIGHTER_SIZE = QSize(190, 85);
const QSize DESTROYER_SIZE = QSize(220, 100);
const QSize EXTERMINATOR_SIZE = QSize(340, 190);

class Enemy :  public Opponent
{
  Q_OBJECT
public:
  Enemy(EnemyType enemyType, QGraphicsItem *pParent = nullptr);
  //~Enemy() = default;

  //Enemy(const Enemy &);

  //~Enemy();

  //Enemy &operator =(const Enemy &);

  EnemyType getType() const;
  void setType(EnemyType enemyType);
  void decreaseHealth(int damage) override;

  QSize getSize() const override;

signals:
  void sigIncreaseScore(int);
  void sigDecreaseHealth();
  void sigGameOver();

public slots:
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

#ifndef BOSS_H
#define BOSS_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsItem>
#include <QSize>
#include <ctime>

#include "opponent.h"

enum class BossType
{
  Frost, Dominator, Soul
};

const QSize FROST_SIZE = QSize(550, 270);
const QSize DOMINATOR_SIZE = QSize(250, 500);
const QSize SOUL_SIZE = QSize(250, 220);

class Boss : public Opponent
{
  Q_OBJECT
public:
  Boss(BossType bossType, QGraphicsItem *pParent = nullptr);
  void setType(BossType bossType);
  void decreaseHealth(int damage) override;

  QSize getSize() const override;

signals:
  void sigIncreaseScore(int);
 // void sigDecreaseHealth();
  void sigGameOver();
  void sigWin();

public slots:
  void onMove() override;
  void onAttack();

private:
  BossType bossType_;
  QTimer *pTimer;
  QSize size_;
  int speed_;
  int health_;
  int damage_;
  int points_;
  clock_t time_ = 0;
};

#endif // BOSS_H

#ifndef BOSS_H
#define BOSS_H

/*#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsItem>
#include <QSize>
#include <ctime>

enum class BossType
{
  Frost, Dominator, Soul
};

class Boss : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Boss(BossType bossType, QGraphicsItem *pParent = nullptr);
  void setType(BossType bossType);
  void decreaseHealth(int damage);

signals:
  void sigIncreaseScore(int);
  void sigDecreaseHealth();
  void sigGameOver();
  void sigWin();

public slots:
  void onMove();
  void onAttack();

private:
  BossType bossType_;
  QTimer *pTimer;
  int speed_;
  int health_;
  int damage_;
  int points_;
  clock_t time_ = 0;
};*/

#endif // BOSS_H

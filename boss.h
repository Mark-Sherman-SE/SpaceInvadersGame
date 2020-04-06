#ifndef BOSS_H
#define BOSS_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsItem>
#include <ctime>

#include "opponent.h"

//описываем возможные типы боссов
enum class BossType
{
  Frost, Dominator, Soul
};

//в качестве глобальных констант задаём размеры каждого босса
const QSize FROST_SIZE = QSize(400, 230);
const QSize DOMINATOR_SIZE = QSize(250, 500);
const QSize SOUL_SIZE = QSize(250, 220);

//класс врага, наследуется от Opponent
class Boss : public Opponent
{
  Q_OBJECT
public:
  Boss(BossType bossType, QGraphicsItem *pParent = nullptr);
  void setType(BossType bossType);
  void decreaseHealth(int damage) override;

  QSize getSize() const override;

signals:
  //сигналы для корректного вычисления очков и конца игры
  void sigIncreaseScore(int);
  void sigGameOver();
  void sigWin();

public slots:
  void onMove() override;
  void onAttack();

private:
  BossType bossType_;
  //таймер для вычисления момента передвижения босса
  QTimer *pTimer;
  QSize size_;
  int speed_;
  int health_;
  int points_;
  //время предыдущей атаки, необходим для корректной стрельбы
  clock_t time_ = 0;
};

#endif // BOSS_H

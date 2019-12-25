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
  //конструктор, принимающий тип босса и указатель на QGraphicsItem
  //(по умолчанию nullptr, при дальнейшем улучшении кода можно будет передавать необходимый указатель
  Boss(BossType bossType, QGraphicsItem *pParent = nullptr);
  //метод установки типа босса
  void setType(BossType bossType);
  //метод уменьшения здоровья
  void decreaseHealth(int damage) override;

  //метод, возвращающий размер босса
  QSize getSize() const override;

signals:
  //сигналы для корректного вычисления очков и конца игры
  void sigIncreaseScore(int);
  void sigGameOver();
  void sigWin();

public slots:
  //метод появления
  void onMove() override;
  //метод атаки и передвижения
  void onAttack();

private:
  //тип босса
  BossType bossType_;
  //таймер для вычисления момента передвижения босса
  QTimer *pTimer;
  //размер босса
  QSize size_;
  //скорость
  int speed_;
  //здоровье
  int health_;
  //очки
  int points_;
  //время предыдущей атаки, необходим для корректной стрельбы
  clock_t time_ = 0;
};

#endif // BOSS_H

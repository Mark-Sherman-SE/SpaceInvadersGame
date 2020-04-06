#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QSize>
#include <ctime>
#include <QKeyEvent>
#include <QTimer>
#include "weapon.h"

//размер модели игрока
QSize const gPlayerSize = QSize(100, 100);

//класс игрока, наследуемся от QObject и QGraphicsPixmapItem для возможности управлять игроком
//и использовать в качестве модели заготовленную фотографию
class Player : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  //конструктор, принимающий тип оружия, которым будет пользоваться игрок, и указатель на QGraphicsItem
  //(по умолчанию nullptr, при дальнейшем улучшении кода можно будет передавать необходимый указатель
  Player(WeaponType weaponType, QGraphicsItem *pParent = nullptr);

  void shoot();
  void decreaseHealth(int damage);
  int getHealth() const;

signals:
  //необходимые сигналы для корректного вычисления счёта, здоровья и момента конца игры
  void sigIncreaseScore(int);
  void sigDecreaseScore();
  void sigDecreaseHealth();
  void sigGameOver();

private:
  WeaponType weaponType_;
  //время предыдущей атаки, необходим для корректной стрельбы
  clock_t time_ = 0;
  int health_;
};

#endif // PLAYER_H

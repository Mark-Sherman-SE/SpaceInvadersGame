#ifndef WEAPON_H
#define WEAPON_H

//#include "player.h"
#include <QGraphicsPixmapItem>
//#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
//#include <QKeyEvent>

//описываем возможные типы оружия
enum class WeaponType
{
  Bullet, Laser, Bomb
};

//описываем тех, у кого может быть оружие
enum class Holder
{
  Player, Enemy
};

//класс оружия, наследуемся от QObject и QGraphicsPixmapItem для возможности передвижения оружия
//и использовать в качестве модели заготовленную фотографию
class Weapon :  public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  //конструктор класса принимает тип оружия
  Weapon(WeaponType weaponType, Holder holder, QGraphicsItem *pParent = nullptr);

  //метод, возвращающий тип оружия
  WeaponType getWeaponType() const;
  //метод, возвращающий задержку оружия
  int getWeaponDelay() const;
  //метод, устанавливающий тип оружия
  void setWeaponType(WeaponType weaponType);

signals:
  //сигналы для корректного выичсления счёта
  void sigIncreaseScore(int);
  void sigDecreaseScore();

public slots:
  //метод, позволяющий боеприпасам двигаться по экрану
  void onMove();

private:
  //тип оружия
  WeaponType weaponType_;
  //скорость боеприпасов
  int weaponRate_;
  //урон от оружия
  int weaponDamage_;
  //задержка перед следующей атакой
  int weaponDelay_;
  //коэффициент носителя оружия
  int holderCoefficient_;
};

#endif // WEAPON_H

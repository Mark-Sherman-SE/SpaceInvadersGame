#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

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
  Weapon(WeaponType weaponType, Holder holder, QGraphicsItem *pParent = nullptr);

  WeaponType getWeaponType() const;
  int getWeaponDelay() const;
  void setWeaponType(WeaponType weaponType);

signals:
  //сигналы для корректного вычисления счёта
  void sigIncreaseScore(int);
  void sigDecreaseScore();

public slots:
  //метод, позволяющий боеприпасам двигаться по экрану
  void onMove();

private:
  WeaponType weaponType_;
  int weaponRate_;
  int weaponDamage_;
  //задержка перед следующей атакой
  int weaponDelay_;
  //коэффициент носителя оружия
  int holderCoefficient_;
};

#endif // WEAPON_H

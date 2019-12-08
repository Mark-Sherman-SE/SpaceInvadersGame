#ifndef WEAPON_H
#define WEAPON_H

//#include "player.h"
#include <QGraphicsPixmapItem>
//#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
//#include <QKeyEvent>

enum class WeaponType
{
  Bullet, Laser, Bomb
};

class Weapon :  public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Weapon(WeaponType weaponType, QGraphicsItem *pParent = nullptr);

  WeaponType getWeaponType() const;
  int getWeaponDelay() const;
  void setWeaponType(WeaponType weaponType);

signals:
  void sigIncreaseScore(int);
  void sigDecreaseScore();

public slots:
  void onMove();

private:
  WeaponType weaponType_;
  int weaponRate_;
  int weaponDamage_;
  int weaponDelay_;

};

#endif // WEAPON_H

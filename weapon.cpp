#include "weapon.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>

Weapon::Weapon(WeaponType weaponType, QGraphicsItem *pParent) :
  QGraphicsPixmapItem(pParent)
  /*weaponRate_(weaponRate),
  weaponDamage_(weaponDamage)*/
{
  setWeaponType(weaponType);
  QTimer *pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Weapon::onMove);
  pTimer->start(weaponRate_);
}

WeaponType Weapon::getWeaponType() const
{
  return weaponType_;
}

int Weapon::getWeaponDelay() const
{
  return weaponDelay_;
}

void Weapon::setWeaponType(WeaponType weaponType)
{
  weaponType_ = weaponType;
  QPixmap oPixmap(":/images/Resources/images/Weapons.png");
  switch (weaponType_)
  {
    case WeaponType::Bullet:
    {
      //QPixmap oPixmap(":/images/Resources/images/Weapons.png");
      //setPixmap(oPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio));
      QRect rect(172, 111, 11, 11); //183. 122
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      weaponRate_ = 5;
      weaponDamage_ = 50;
      weaponDelay_ = 100;
      break;
    }
    case WeaponType::Laser:
    {
      //QPixmap oPixmap(":/images/Resources/images/Weapons.png");
     // setPixmap(oPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio));
      QRect rect(362, 8, 14, 22);
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      weaponRate_ = 10;
      weaponDamage_ = 10;
      weaponDelay_ = 120;
      break;
    }
    case WeaponType::Bomb:
    {
      //QPixmap oPixmap(":/images/Resources/images/Weapons.png");
     // setPixmap(oPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio));
      QRect rect(201, 196, 11, 24); //212, 210
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      weaponRate_ = 20;
      weaponDamage_ = 20;
      weaponDelay_ = 120;
      break;
    }
    default:
    {
      QRect rect(172, 111, 11, 11); //183. 122
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      weaponRate_ = 100;
      weaponDamage_ = 5;
      weaponDelay_ = 120;
      break;
    }
  }
}

void Weapon::onMove()
{
  QList<QGraphicsItem *> lstCollidingItem= collidingItems();
  for (auto const pItem : lstCollidingItem)
  {
    Enemy *enemy = dynamic_cast<Enemy *>(pItem);
    if (enemy != nullptr)
    {
      /*if (enemy->getColor() == getColor())
      {
        scene()->removeItem(enemy);
        scene()->removeItem(this);

        emit sigIncreaseScore();
        delete enemy;
        delete this;
      }
      else
      {
        emit sigDecreaseScore();
        scene()->removeItem(this);
        delete this;
      }*/
      enemy->decreaseHealth(weaponDamage_);
      scene()->removeItem(this);
      delete this;
      return;
    }
  }
  setPos(x(), y() - 2);
  if (pos().y() < 0)
  {
    scene()->removeItem(this);
    delete this;
  }
}
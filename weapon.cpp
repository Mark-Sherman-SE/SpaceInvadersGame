#include "weapon.h"
#include "enemy.h"
#include "opponent.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsScene>

//конструктор
Weapon::Weapon(WeaponType weaponType, Holder holder, QGraphicsItem *pParent) :
  QGraphicsPixmapItem(pParent)
{
  holderCoefficient_ = holder == Holder::Player ? 1 : -1;
  setWeaponType(weaponType);
  //создаём таймер, чтобы каждое заданное время (зависит от скорости стрельбы) передвигался боезапас
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
  //каждый тип оружия имеет свою модель, скорость стрельбы, урон и задержку
  //в зависимости от того, кто держит оружие, поворачиваем его в нужную стророну
  switch (weaponType_)
  {
    case WeaponType::Bullet:
    {
      QRect rect(172, 111, 11, 11);
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      if (holderCoefficient_ == -1)
      {
        setTransformOriginPoint(newPixmap.height() / 2, newPixmap.width() / 2);
        setRotation(180);
      }
      weaponRate_ = 5;
      weaponDamage_ = 50;
      weaponDelay_ = 100;
      break;
    }
    case WeaponType::Laser:
    {
      QRect rect(362, 8, 14, 22);
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      if (holderCoefficient_ == -1)
      {
        setTransformOriginPoint(newPixmap.height() / 2, newPixmap.width() / 2);
        setRotation(180);
      }
      weaponRate_ = 10;
      weaponDamage_ = 75;
      weaponDelay_ = 200;
      break;
    }
    case WeaponType::Bomb:
    {
      QRect rect(201, 196, 11, 25);
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      if (holderCoefficient_ == -1)
      {
        setTransformOriginPoint(newPixmap.height() / 2, newPixmap.width() / 2);
        setRotation(180);
      }
      weaponRate_ = 25;
      weaponDamage_ = 150;
      weaponDelay_ = 400;
      break;
    }
    default:
    {
      QRect rect(172, 111, 11, 11);
      QPixmap newPixmap = oPixmap.copy(rect);
      setPixmap(newPixmap);
      if (holderCoefficient_ == -1)
      {
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(180);
      }
      weaponRate_ = 100;
      weaponDamage_ = 5;
      weaponDelay_ = 120;
      break;
    }
  }
}

//метод передвижения оружия
void Weapon::onMove()
{
  if (scene() != nullptr)
  {
    //в зависимости от владельца оружия (босс или игрок) боезапас будет двигаться в нужную сторону
    setPos(x(), y() - 2 * holderCoefficient_);
    //если боезапас ушёл за границу сцены - удаляем его
    if (pos().y() < 0 || pos().y() > scene()->height())
    {
      scene()->removeItem(this);
      delete this;
    }
    //если владелец игрок - проверяем, попали ли мы по врагу
    else if (holderCoefficient_ == 1)
    {
      QList<QGraphicsItem *> lstCollidingItem = collidingItems();
      for (auto const pItem : lstCollidingItem)
      {
        Opponent *enemy = dynamic_cast<Opponent *>(pItem);
        if (enemy != nullptr)
        {
          scene()->removeItem(this);
          enemy->decreaseHealth(weaponDamage_);
          delete this;
          return;
        }
      }
    }
    //если владелец -
    else
    {
      QList<QGraphicsItem *> lstCollidingItem = collidingItems();
      for (auto const pItem : lstCollidingItem)
      {
        Player *player = dynamic_cast<Player *>(pItem);
        if (player != nullptr)
        {
          if (player->getHealth() < weaponDamage_)
          {
            player->decreaseHealth(weaponDamage_);
          }
          else
          {
            player->decreaseHealth(weaponDamage_);
            scene()->removeItem(this);
            delete this;
            return;
          }
        }
      }
    }
  }
}

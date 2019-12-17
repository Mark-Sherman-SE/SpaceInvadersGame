#include "boss.h"
/*#include "player.h"
#include <QTimer>
#include <QGraphicsScene>

static bool path = true;

Boss::Boss(BossType bossType, QGraphicsItem *pParent) :
  QGraphicsPixmapItem(pParent)
{
  setType(bossType);

  pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Boss::onMove);
  pTimer->start(50);
  if (y() == 0)
  {
    pTimer->stop();
    disconnect(pTimer, &QTimer::timeout, this, &Boss::onMove);
    connect(pTimer, &QTimer::timeout, this, &Boss::onMove);
    pTimer->start(speed_);
  }
}

void Boss::setType(BossType bossType)
{
  bossType_ = bossType;

  switch (bossType_)
  {
    case BossType::Frost:
    {
        QPixmap oPixmap(":/images/Resources/images/Frost.png");
        setPixmap(oPixmap.scaled(QSize(500, 170), Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        speed_ = 20;
        damage_ = 200;
        health_ = 10000;
        points_ = 10000;
        break;
    }
    case BossType::Dominator:
    {
        QPixmap oPixmap(":/images/Resources/images/Dominator.png");
        setPixmap(oPixmap.scaled(QSize(250, 500), Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(180);
        speed_ = 10;
        health_ = 25000;
        damage_ = 100;
        points_ = 20000;
        break;
    }
    case BossType::Soul:
    {
        QPixmap oPixmap(":/images/Resources/images/Soul.png");
        setPixmap(oPixmap.scaled(QSize(150, 120), Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        speed_ = 2;
        health_ = 2000;
        damage_ = 50;
        points_ = 5000;
        break;
    }
  }
}

void Boss::decreaseHealth(int damage)
{
  health_ -= damage;
  if (health_ <= 0)
  {
    scene()->removeItem(this);
    emit sigIncreaseScore(points_);
    emit sigWin();
    delete this;
  }
}

void Boss::onMove()
{
  setPos(x(), y() + 2);
  if (y() > 0)
  {

  }
}

void Boss::onAttack()
{
 // bool k = true;
  if (path)
  {
      setPos(x() - 2, y());
      path = x() > 0 ? true : false;
  }
  else
  {
    setPos(x() + 2, y());
    path = x() < scene()->width() ? false : true;
  }
  switch (bossType_)
  {
    case BossType::Frost:
    {
      Weapon *bomb = new Weapon(WeaponType::Bomb);
      Weapon *leftBullet = new Weapon(WeaponType::Bullet);
      Weapon *rightBullet = new Weapon(WeaponType::Bullet);

      if (clock() - time_ < leftBullet->getWeaponDelay())
      {
        delete leftBullet;
        delete rightBullet;
        return;
      }
      else
      {
        //Weapon *pBullet = new Weapon(weaponType_);
        connect(leftBullet, &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        //connect(leftBullet, &Weapon::sigDecreaseScore, this, &Boss::sigDecreaseScore);

        connect(rightBullet, &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        leftBullet->setPos(x() + 50, y() - 10);
        scene()->addItem(leftBullet);
        rightBullet->setPos(x() - 50, y() - 10);
        scene()->addItem(rightBullet);
        time_ = clock();
      }

      connect(bomb, &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
      bomb->setPos(x(), y());
    }
    case BossType::Dominator:
    {
      Weapon *weapons[4];
      for (int i = 0; i < 4; ++i)
      {
        weapons[i] = new Weapon(WeaponType::Bullet);
      }
      Weapon *laser = new Weapon(WeaponType::Laser);
      if (clock() - time_ < weapons[0]->getWeaponDelay())
      {
        delete weapons[0];
        delete weapons[1];
        delete weapons[2];
        delete weapons[3];
        return;
      }
      else
      {
        for (int i = 0; i < 4; ++i)
        {
           connect(weapons[i], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
           weapons[i]->setPos(x() + i * 10, y() - 10);
           scene()->addItem(weapons[i]);
        }
        //Weapon *pBullet = new Weapon(weaponType_);
        connect(weapons[0], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        //connect(leftBullet, &Weapon::sigDecreaseScore, this, &Boss::sigDecreaseScore);
        connect(weapons[1], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        connect(weapons[2], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        connect(weapons[3], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        weapons[0]->setPos(x() + 50, y() - 10);
        scene()->addItem(weapons[0]);
        weapons[1]->setPos(x() + 40, y() - 10);
        scene()->addItem(weapons[1]);
        weapons[1]->setPos(x() + 40, y() - 10);
        scene()->addItem(weapons[1]);
        time_ = clock();
      }
    }
    case BossType::Soul:
    {
      Weapon *bomb = new Weapon(WeaponType::Bomb);
      connect(bomb, &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
      bomb->setPos(x() + 50, y() - 10);
    }
  }


}*/


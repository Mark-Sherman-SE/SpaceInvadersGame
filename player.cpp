#include "player.h"

#include <QGraphicsScene>

Player::Player(QGraphicsItem *pParent) : QGraphicsPixmapItem(pParent)
{
  QPixmap oPixmap(":/images/Resources/images/RedPlayer.png");
  setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
}

void Player::shoot()
{
  Weapon *pBullet = new Weapon(weaponType_);
  if (clock() - time_ < pBullet->getWeaponDelay())
  {
    delete pBullet;
    return;
  }
  else
  {
    //Weapon *pBullet = new Weapon(weaponType_);
    connect(pBullet, &Weapon::sigIncreaseScore, this, &Player::sigIncreaseScore);
    connect(pBullet, &Weapon::sigDecreaseScore, this, &Player::sigDecreaseScore);

    pBullet->setPos(x() + 27, y() - 10);
    scene()->addItem(pBullet);
    time_ = clock();
  }
}

/*EColor Player::getColor() const
{
  return m_eColor;
}*/

/*void Player::setColor(EColor eColor)
{
  m_eColor = eColor;
  switch (eColor)
  {
    case EColor::Red:
    {
        QPixmap oPixmap(":/images/Resources/images/RedCannon.png");
        setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
        break;
    }
    case EColor::Blue:
    {
        QPixmap oPixmap(":/images/Resources/images/BlueCannon.png");
        setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
        break;
    }
    case EColor::Pink:
    {
        QPixmap oPixmap(":/images/Resources/images/PinkCannon.png");
        setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
        break;
    }
    default:
    {
        QPixmap oPixmap(":/images/Resources/images/RedCannon.png");
        setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
        m_eColor = EColor::Red;
        break;
    }
  }
}*/

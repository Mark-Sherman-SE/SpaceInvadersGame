#include "player.h"
#include <QKeyEvent>

#include <QGraphicsScene>

Player::Player(QGraphicsItem *pParent) :
  QObject(),
  QGraphicsPixmapItem(pParent),
  health_(2000)
{
  QPixmap oPixmap(":/images/Resources/images/RedPlayer.png");
  setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
  /////////////////////
  /*QTimer *pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Player::keyPressEvent);
  pTimer->start(2);*/
}

void Player::shoot()
{
  Weapon *pBullet = new Weapon(weaponType_, Holder::Player);
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

void Player::decreaseHealth(int damage)
{
  health_ -= damage;
  if (health_ <= 0)
  {
    scene()->removeItem(this);
    emit sigGameOver();
    delete this;
  }
}

/*void Player::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_Left:
    {
      if (this->pos().x() > 0)
      {
        this->setPos(this->x() - 20, this->y());
      }
      break;
    }
    case Qt::Key_Right:
    {
      if (this->pos().x() + gPlayerSize.width() < 1920)
      {
        this->setPos(this->x() + 20, this->y());
      }
      break;
    }
    case Qt::Key_Space:
    {
      this->shoot();
      break;
    }
  }
}*/

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

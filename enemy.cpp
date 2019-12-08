#include "enemy.h"
#include "player.h"

#include <QTimer>
#include <QGraphicsScene>

Enemy::Enemy(EnemyType enemyType, QGraphicsItem *pParent) :
  QGraphicsPixmapItem(pParent)
{
  setType(enemyType);

  QTimer *pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Enemy::onMove);
  pTimer->start(enemySpeed_);
}

EnemyType Enemy::getType() const
{
  return enemyType_;
}

void Enemy::setType(EnemyType enemyType)
{
  enemyType_ = enemyType;

  switch (enemyType_)
  {
    case EnemyType::Corporal:
    {
        QPixmap oPixmap(":/images/Resources/images/Corporal.png");
        setPixmap(oPixmap.scaled(QSize(150, 70), Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        enemySpeed_ = 20;
        enemyHealth_ = 100;
        points_ = 10;
        break;
    }
    case EnemyType::Interceptor:
    {
        QPixmap oPixmap(":/images/Resources/images/Interceptor.png");
        setPixmap(oPixmap.scaled(CORPORAL_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        enemySpeed_ = 10;
        enemyHealth_ = 25;
        points_ = 15;
        break;
    }
    case EnemyType::Fighter:
    {
        QPixmap oPixmap(":/images/Resources/images/Fighter.png");
        setPixmap(oPixmap.scaled(FIGHTER_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        enemySpeed_ = 25;
        enemyHealth_ = 200;
        points_ = 25;
        break;
    }
    case EnemyType::Destroyer:
    {
        QPixmap oPixmap(":/images/Resources/images/Destoyer.png");
        setPixmap(oPixmap.scaled(DESTROYER_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        enemySpeed_ = 30;
        enemyHealth_ = 500;
        points_ = 50;
        break;
    }
    case EnemyType::Exterminator:
    {
        QPixmap oPixmap(":/images/Resources/images/Exterminator.png");
        setPixmap(oPixmap.scaled(EXTERMINATOR_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        enemySpeed_ = 40;
        enemyHealth_ = 1000;
        points_ = 100;
        break;
    }
  }
}

void Enemy::decreaseHealth(int damage)
{
  enemyHealth_ -= damage;
  if (enemyHealth_ <= 0)
  {
    scene()->removeItem(this);
    emit sigIncreaseScore(points_);
    delete this;
  }
}

void Enemy::onMove()
{
  setPos(x(), y() + 2);
  if (pos().y() >= (scene()->height() - gPlayerSize.height()))
  {
    scene()->removeItem(this);
    emit sigDecreaseHealth();
    delete this;
  }
  QList<QGraphicsItem *> lstCollidingItem = collidingItems();
  for (auto const pItem : lstCollidingItem)
  {
    if (dynamic_cast<Player *>(pItem))
    {
      emit sigGameOver();
    }
  }
}

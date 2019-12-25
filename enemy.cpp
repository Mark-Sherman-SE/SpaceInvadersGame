#include "enemy.h"
#include "player.h"

#include <QGraphicsScene>

//конструктор
Enemy::Enemy(EnemyType enemyType, QGraphicsItem *pParent) :
  Opponent()
{
  setType(enemyType);

  pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Enemy::onMove);
  pTimer->start(enemySpeed_);
}

//получаем тип врага
EnemyType Enemy::getType() const
{
  return enemyType_;
}

//установка типа врага
void Enemy::setType(EnemyType enemyType)
{
  enemyType_ = enemyType;

  //для каждого типа варага предусмотрена своя модель, размер, скорость, здоровье и очки
  switch (enemyType_)
  {
    case EnemyType::Corporal:
    {
        QPixmap oPixmap(":/images/Resources/images/Corporal.png");
        setPixmap(oPixmap.scaled(QSize(150, 70), Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        size_ = CORPORAL_SIZE;
        enemySpeed_ = 20;
        enemyHealth_ = 100;
        points_ = 10;
        break;
    }
    case EnemyType::Interceptor:
    {
        QPixmap oPixmap(":/images/Resources/images/Interceptor.png");
        setPixmap(oPixmap.scaled(INTERCEPTOR_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        size_ = INTERCEPTOR_SIZE;
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
        size_ = FIGHTER_SIZE;
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
        size_ = DESTROYER_SIZE;
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
        size_ = EXTERMINATOR_SIZE;
        enemySpeed_ = 40;
        enemyHealth_ = 1000;
        points_ = 100;
        break;
    }
  }
}

//метод уменьшения здоровья врага
void Enemy::decreaseHealth(int damage)
{
  enemyHealth_ -= damage;
  //когда здоровье закончилось - увеличиваем счёт и удаляем врага
  if (enemyHealth_ <= 0)
  {
    scene()->removeItem(this);
    emit sigIncreaseScore(points_);
    delete this;
  }
}

//получаем размер врага
QSize Enemy::getSize() const
{
  return size_;
}

//метод передвижения врага
void Enemy::onMove()
{
  if (scene() != nullptr)
  {
    this->setPos(x(), y() + 2);
    //если враг успел пробраться за игрока - уменьшаем здоровье базы
    if (this->pos().y() >= (scene()->height() - gPlayerSize.height()))
    {
      scene()->removeItem(this);
      emit sigDecreaseHealth();
      delete this;
    }
    else
    {
      //если игрок пересёкся с врагом - посылаем сигнал конца игры
      QList<QGraphicsItem *> lstCollidingItem = collidingItems();
      if (!lstCollidingItem.empty())
      {
        for (auto const pItem : lstCollidingItem)
        {
          if (dynamic_cast<Player *>(pItem))
          {
            emit sigGameOver();
          }
        }
      }
    }
  }
}

#include "boss.h"
#include "player.h"
#include <QGraphicsScene>

static bool path = true;

//конструктор
Boss::Boss(BossType bossType, QGraphicsItem *pParent) :
  Opponent()
{
  setType(bossType);

  pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Boss::onMove);
  pTimer->start(10);
}

//устанавливаем тип босса
void Boss::setType(BossType bossType)
{
  bossType_ = bossType;

  switch (bossType_)
  {
    case BossType::Frost:
    {
        QPixmap oPixmap(":/images/Resources/images/Frost.png");
        setPixmap(oPixmap.scaled(FROST_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(90);
        size_ = FROST_SIZE;
        speed_ = 50;
        health_ = 10000;
        points_ = 10000;
        break;
    }
    case BossType::Dominator:
    {
        QPixmap oPixmap(":/images/Resources/images/Dominator.png");
        setPixmap(oPixmap.scaled(DOMINATOR_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(180);
        size_ = DOMINATOR_SIZE;
        speed_ = 30;
        health_ = 25000;
        points_ = 20000;
        break;
    }
    case BossType::Soul:
    {
        QPixmap oPixmap(":/images/Resources/images/Soul.png");
        setPixmap(oPixmap.scaled(SOUL_SIZE, Qt::KeepAspectRatio));
        setTransformOriginPoint(oPixmap.height() / 2, oPixmap.width() / 2);
        setRotation(180);
        size_ = SOUL_SIZE;
        speed_ = 15;
        health_ = 2000;
        points_ = 5000;
        break;
    }
  }
}

//метод уменьшения здоровья
void Boss::decreaseHealth(int damage)
{
  health_ -= damage;
  //если здоровье закончилось - посылаем сигнал конца игры и увеличения очков
  if (health_ <= 0)
  {
    scene()->removeItem(this);
    emit sigIncreaseScore(points_);
    emit sigWin();
    delete this;
  }
}

//получаем размер босса
QSize Boss::getSize() const
{
  return size_;
}

//метод появления босса
void Boss::onMove()
{
  //пока не достигли нужно точки - босс пояляется
  //когда появился - разъединяем таймер с методом поялвения исоединяем его с методом атаки
  if (y() < 100)
  {
    setPos(x(), y() + 1);
  }
  else
  {
    pTimer->stop();
    disconnect(pTimer, &QTimer::timeout, this, &Boss::onMove);
    connect(pTimer, &QTimer::timeout, this, &Boss::onAttack);
    pTimer->start(speed_);
  }
}

//метод атаки
void Boss::onAttack()
{
  //выбираем направление движения так, чтобы не ушёл за границу сцены
  if (path)
  {
      setPos(x() - 2, y());
      path = x() > 0 ? true : false;
  }
  else
  {
    setPos(x() + 2, y());
    path = x() < scene()->width() - size_.width() * 1.5 ? false : true;
  }
  //в зависимости от типа врага даём ему необходимое оружее
  switch (bossType_)
  {
    case BossType::Frost:
    {
      Weapon *bomb = new Weapon(WeaponType::Bomb, Holder::Enemy);
      Weapon *leftLaser = new Weapon(WeaponType::Laser, Holder::Enemy);
      Weapon *rightLaser = new Weapon(WeaponType::Laser, Holder::Enemy);

      if (clock() - time_ < leftLaser->getWeaponDelay() * 5)
      {
        delete leftLaser;
        delete rightLaser;
        return;
      }
      else
      {
        connect(leftLaser, &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        connect(rightLaser, &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        leftLaser->setPos(x(), y() + size_.width() * 4 / 5);
        scene()->addItem(leftLaser);
        rightLaser->setPos(x() + size_.height(), y() + size_.width() * 4 / 5);
        scene()->addItem(rightLaser);
        time_ = clock();
      }

      static time_t bombTime = 0;
      if (clock() - bombTime < bomb->getWeaponDelay())
      {
        delete bomb;
        return;
      }
      else
      {
        bomb->setPos(x() + size_.height() / 2, y() + size_.width());
        scene()->addItem(bomb);
        bombTime = clock();
      }
      break;
    }
    case BossType::Dominator:
    {
      Weapon *weapons[4];
      for (int i = 0; i < 4; ++i)
      {
        weapons[i] = new Weapon(WeaponType::Bullet, Holder::Enemy);
      }
      if (clock() - time_ < weapons[0]->getWeaponDelay() * 4)
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
        connect(weapons[0], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        connect(weapons[1], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        connect(weapons[2], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        connect(weapons[3], &Weapon::sigIncreaseScore, this, &Boss::sigIncreaseScore);
        weapons[0]->setPos(x() + DOMINATOR_SIZE.width() / 6, y() + DOMINATOR_SIZE.height() * 2 / 3);
        scene()->addItem(weapons[0]);
        weapons[1]->setPos(x() + DOMINATOR_SIZE.width() / 7, y() + DOMINATOR_SIZE.height() * 2 / 3);
        scene()->addItem(weapons[1]);
        weapons[2]->setPos(x() + DOMINATOR_SIZE.width() * 5 / 6, y() + DOMINATOR_SIZE.height()* 2 / 3);
        scene()->addItem(weapons[2]);
        weapons[3]->setPos(x() + DOMINATOR_SIZE.width() * 5 / 7, y() + DOMINATOR_SIZE.height() * 2 / 3);
        scene()->addItem(weapons[3]);
        time_ = clock();
        break;
      }
    }
    case BossType::Soul:
    {
      Weapon *bomb = new Weapon(WeaponType::Bomb, Holder::Enemy);
      if (clock() - time_ < bomb->getWeaponDelay())
      {
        delete bomb;
        return;
      }
      else
      {
        bomb->setPos(x() + SOUL_SIZE.width(), y() + SOUL_SIZE.height());
        scene()->addItem(bomb);
        time_ = clock();
      }
    }
  }
}

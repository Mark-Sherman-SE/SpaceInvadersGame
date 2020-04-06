#include "player.h"
#include <QGraphicsScene>

//конструктор
Player::Player(WeaponType weaponType, QGraphicsItem *pParent) :
  QObject(),
  QGraphicsPixmapItem(pParent),
  weaponType_(weaponType),
  health_(2000)
{
  //устанавливаем модель игрока
  QPixmap oPixmap(":/images/Resources/images/RedPlayer.png");
  setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
}

//метод стрельбы, каждый раз при стрельбе создаём боеприпас необходимого типа оружия
//далее проверяем, прошло ли необходимое время после предыдущей атаки
//если нет - удаляем созданный боеприпас, если да - соединяем необходимые сигналы, устанавливаем позицию оружия
//и добавляем его на сцену
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
  //если здоровье кончилось - посылаем сигнал окончания игры
  if (health_ <= 0)
  {
    scene()->removeItem(this);
    emit sigGameOver();
    delete this;
  }
}


int Player::getHealth() const
{
  return health_;
}

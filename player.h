#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
//#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QSize>
#include <ctime>
#include "weapon.h"
#include <QKeyEvent>
//#include "EColor.h"
#include <QTimer>
#include "windows.h"

/*enum class EColor
{
    Red, Pink, Blue
};*/

QSize const gPlayerSize = QSize(100, 100);

class Player : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Player(QGraphicsItem *pParent = nullptr);

  void shoot();

  void decreaseHealth(int damage);

signals:
 // void sigMove();
  void sigIncreaseScore(int);
  void sigDecreaseScore();

  void sigDecreaseHealth();

  void sigGameOver();
  ////////////////////////////
/*public slots:
  void keyPress(QKeyEvent *event);*/

private:
  WeaponType weaponType_;
  clock_t time_ = 0;
  int health_;
};

#endif // PLAYER_H

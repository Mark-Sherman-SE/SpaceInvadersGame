#ifndef ENEMY_H
#define ENEMY_H


#include <QGraphicsPixmapItem>
//#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
//#include <QKeyEvent>

enum class EnemyType
{
    Corporal, Interceptor, Fighter, Destroyer, Exterminator
};


class Enemy :  public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Enemy(EnemyType enemyType, QGraphicsItem *pParent = nullptr);
  EnemyType getType() const;
  void setType(EnemyType eColor);
  void decreaseHealth(int damage);

signals:
  void sigIncreaseScore();
  void sigDecreaseHealth();
  void sigGameOver();

public slots:
  void onMove();

private:
  EnemyType enemyType_;
  int enemySpeed_;
  int enemyHealth_;
  int points_;
};

#endif // ENEMY_H

#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
//#include <QSize>
#include <QTimer>

#include "opponent.h"

//описываем возможные типы врагов
enum class EnemyType
{
    Corporal, Interceptor, Fighter, Destroyer, Exterminator
};

//в качестве глобальных констант задаём размеры каждого врага
const QSize CORPORAL_SIZE = QSize(150, 70);
const QSize INTERCEPTOR_SIZE = QSize(70, 50);
const QSize FIGHTER_SIZE = QSize(190, 85);
const QSize DESTROYER_SIZE = QSize(220, 100);
const QSize EXTERMINATOR_SIZE = QSize(340, 190);

//класс врага, наследуется от Opponent
class Enemy :  public Opponent
{
  Q_OBJECT
public:
  //конструктор, принимающий тип врага и указатель на QGraphicsItem
  //(по умолчанию nullptr, при дальнейшем улучшении кода можно будет передавать необходимый указатель
  Enemy(EnemyType enemyType, QGraphicsItem *pParent = nullptr);

  //метод, возвращающий тип врага
  EnemyType getType() const;
  //метод установки типа врага
  void setType(EnemyType enemyType);
  //метод уменьшения здоровья врага
  void decreaseHealth(int damage) override;

  //метод, возвращающий размер врага
  QSize getSize() const override;

signals:
  //необходимые сигналы для корректного вычисления счёта, здоровья и момента конца игры
  void sigIncreaseScore(int);
  void sigDecreaseHealth();
  void sigGameOver();

public slots:
  //метод для передвижения врага
  void onMove() override;

private:
  //тип врага
  EnemyType enemyType_;
  //таймер для вычисления момента передвижения врага
  QTimer *pTimer;
  //размер врага
  QSize size_;
  //скорость врага
  int enemySpeed_;
  //здоровье врага
  int enemyHealth_;
  //очки за уничтожение врага
  int points_;
};

#endif // ENEMY_H

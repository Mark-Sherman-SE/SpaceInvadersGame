#ifndef GAME_H
#define GAME_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <vector>
#include <QList>
#include <iterator>

#include <memory>

#include "player.h"
#include "weapon.h"
#include "enemy.h"
#include "points.h"
#include "boss.h"

const int VARIABLE_AMOUNT_OF_ENEMIES = 20;

class Game : public QGraphicsView
{
  Q_OBJECT
public:
  Game(QSize oScreenSize, QWidget *pParent = nullptr);

  void Run();
  void CheckPoints();

protected:
  void keyPressEvent(QKeyEvent *event) override;

public slots:
  void onCreateEnemy();
  void onIncreaseScore(int points);
  void onDecreaseScore();
  void onDecreaseHealth();
  void onGameOver();
private:
  Player *m_pPlayer = nullptr;
  Points *m_pPoints = nullptr;
  QTimer *pTimer = nullptr;
  QSize m_oScreenSize;
  std::vector<Enemy *> enemies_;
  std::vector<Enemy *>::iterator ourEnemy_;
  //QList<Enemy *>::iterator currentEnemy_;
  std::size_t currentEnemy_;
};

#endif // GAME_H

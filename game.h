#ifndef GAME_H
#define GAME_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>

#include "player.h"
#include "weapon.h"
#include "enemy.h"
#include "points.h"

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
  QSize m_oScreenSize;
};

#endif // GAME_H

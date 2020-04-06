#ifndef GAME_H
#define GAME_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <vector>
#include <iterator>

#include "player.h"
#include "weapon.h"
#include "enemy.h"
#include "points.h"
#include "boss.h"
#include "opponent.h"
#include "button.h"

//константа переменного количества врагов
const int VARIABLE_AMOUNT_OF_ENEMIES = 20;

//основной класс - класс игры
class Game : public QGraphicsView
{
  Q_OBJECT
public:
  //конструктор принимает размер экрана
  Game(QSize oScreenSize, QWidget *pParent = nullptr);

  //метод проверки очков и жизней
  void CheckPoints();

protected:
  //метод нажатия на клавишу (необходим для передвижения и атаки игрока)
  void keyPressEvent(QKeyEvent *event) override;

public slots:
  void displayMainMenu();
  void displayGameOverMenu();
  void Run();
  void onCreateEnemy();
  void onIncreaseScore(int points);
  void onDecreaseScore();
  void onDecreaseHealth();
  void onGameOver();
private:
  Player *m_pPlayer = nullptr;
  Points *m_pPoints = nullptr;
  QTimer *pTimer = nullptr;
  int scorePoints;
  QSize m_oScreenSize;
  std::vector<Opponent *> enemies_;
  std::vector<Opponent *>::iterator ourEnemy_;
  EnemyType enemyType_;
};

#endif // GAME_H

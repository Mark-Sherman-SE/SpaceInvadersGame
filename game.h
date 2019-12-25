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
  //отображение главного меню
  void displayMainMenu();
  //отображение меню конца игры
  void displayGameOverMenu();
  //метод начала игры
  void Run();
  //метод создания врага
  void onCreateEnemy();
  //метод учвеличения очков
  void onIncreaseScore(int points);
  //метод уменьшения очков
  void onDecreaseScore();
  //метод уменьшения здоровья базы
  void onDecreaseHealth();
  //метод конца игры
  void onGameOver();
private:
  //указатель на игрока
  Player *m_pPlayer = nullptr;
  //указатель на очки
  Points *m_pPoints = nullptr;
  //таймер игры
  QTimer *pTimer = nullptr;
  //очки за игру
  int scorePoints;
  //размер экрана
  QSize m_oScreenSize;
  //вектор указателей на наших врагов
  std::vector<Opponent *> enemies_;
  //итератор по вектору врагов
  std::vector<Opponent *>::iterator ourEnemy_;
  //тип текущего врага
  EnemyType enemyType_;
};

#endif // GAME_H

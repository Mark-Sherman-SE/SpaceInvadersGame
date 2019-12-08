#include "game.h"

#include <QTimer>

Game::Game(QSize oScreenSize, QWidget *pParent) :
  QGraphicsView(pParent),
  m_oScreenSize(oScreenSize)
{
  QGraphicsScene * pScene = new QGraphicsScene();
  setScene(pScene);

  pScene->setSceneRect(0, 0, m_oScreenSize.width(), m_oScreenSize.height());
  setBackgroundBrush(QBrush(QImage(":/images/Resources/images/SpaceInvadersBg.jpg")));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setCursor(Qt::PointingHandCursor);
  setStyleSheet("border-style:none");
}

void Game::Run()
{
  scene()->clear();
  setCursor(Qt::BlankCursor);
  m_pPlayer = new Player();
  m_pPlayer->setPos(m_oScreenSize.width() / 2, m_oScreenSize.height() - gPlayerSize.height());
  m_pPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
  m_pPlayer->setFocus();
  scene()->addItem(m_pPlayer);

  connect(m_pPlayer, &Player::sigIncreaseScore, this, &Game::onIncreaseScore);
  connect(m_pPlayer, &Player::sigDecreaseScore, this, &Game::onDecreaseScore);
  /////////////////////////////////////////////////////////////////////////////////
 /* int amountOfEnemies = 20 + rand() % VARIABLE_AMOUNT_OF_ENEMIES;
  for (int i = 0; i < amountOfEnemies; ++i)
  {
    int nType = rand() % 5;
    Enemy *pEnemy = new Enemy(static_cast<EnemyType>(nType));

    int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(pEnemy->x()));

    pEnemy->setPos(nPos, 0);
    connect(pEnemy, &Enemy::sigGameOver, this, &Game::onGameOver);
    connect(pEnemy, &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
    connect(pEnemy, &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
    enemies_.push_back(pEnemy);
  }
  currentEnemy_ = enemies_.begin();*/
////////////////////////////////////////////////////////////////////////////////
  m_pPoints = new Points();
  scene()->addItem(m_pPoints);


  QTimer *pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
  pTimer->start(2000);
}

void Game::CheckPoints()
{
  if ((m_pPoints->getScore() < 0) || (m_pPoints->getHealth() <= 0))
  {
    m_pPoints->reset();
    onGameOver();
  }
}

void Game::keyPressEvent(QKeyEvent *event)
{
  if (m_pPlayer == nullptr)
  {
    return;
  }
  switch (event->key())
  {
    case Qt::Key_Left:
    {
      if (m_pPlayer->pos().x() > 0)
      {
        m_pPlayer->setPos(m_pPlayer->x() - 20, m_pPlayer->y());
      }
      break;
    }
    case Qt::Key_Right:
    {
      if (m_pPlayer->pos().x() + gPlayerSize.width() < m_oScreenSize.width())
      {
        m_pPlayer->setPos(m_pPlayer->x() + 20, m_pPlayer->y());
      }
      break;
    }
   /* case Qt::Key_Z:
    {
      int nColor = static_cast<int>(m_pPlayer->getColor());
      ++nColor;
      if (nColor > static_cast<int>(EColor::Blue))
      {
        nColor = static_cast<int>(EColor::Red);
      }
      m_pPlayer->setColor(static_cast<EColor>(++nColor));
      break;
    }*/
    case Qt::Key_Space:
    {
      m_pPlayer->shoot();
      break;
    }
  }
}

void Game::onCreateEnemy()
{
  /*int nType = rand() % 5;
  Enemy *pEnemy = new Enemy(static_cast<EnemyType>(nType));

  int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(pEnemy->x()));

  pEnemy->setPos(nPos, 0);
  enemies_.push_back(pEnemy);*/

  int nPos = 100 + (rand() % (m_oScreenSize.width() - 100));
    int nType = rand() % 5;

    Enemy *pEnemy = new Enemy(static_cast<EnemyType>(nType));
    pEnemy->setPos(nPos, 0);

    scene()->addItem(pEnemy);
    connect(pEnemy, &Enemy::sigGameOver, this, &Game::onGameOver);
    connect(pEnemy, &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
    connect(pEnemy, &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);

 /* scene()->addItem(*currentEnemy_);
  connect(*currentEnemy_, &Enemy::sigGameOver, this, &Game::onGameOver);
  connect(*currentEnemy_, &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(*currentEnemy_, &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
  if (std::next(*currentEnemy_) == nullptr)
  {
    pTimer->stop();
  }*/
  //////////////////////////////////////
 // enemies_.push_back(pEnemy);
}

void Game::onIncreaseScore(int points)
{
  m_pPoints->increaseScore(points);
  CheckPoints();
}

void Game::onDecreaseScore()
{
  m_pPoints->decreaseScore();
  CheckPoints();
}

void Game::onDecreaseHealth()
{
  m_pPoints->decreaseHealth();
  CheckPoints();
}

void Game::onGameOver()
{
  close();
}

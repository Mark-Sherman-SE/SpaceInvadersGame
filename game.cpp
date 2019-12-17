#include "game.h"

#include <QDebug>

//#include <QTimer>

static int ENEMY_NUMBER = 0;

Game::Game(QSize oScreenSize, QWidget *pParent) :
  QGraphicsView(pParent),
  m_oScreenSize(oScreenSize),
  currentEnemy_(0)
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

  std::size_t amountOfEnemies = 20 + rand() % VARIABLE_AMOUNT_OF_ENEMIES;
  Enemy *pEnemy = nullptr;
  int nType;
  int nPos;
  for (std::size_t i = 0; i < amountOfEnemies; ++i)
  {
    nType = rand() % 5;
    pEnemy = new Enemy(static_cast<EnemyType>(nType));
    enemies_.push_back(pEnemy);
    nPos = rand() % (m_oScreenSize.width() - static_cast<int>(enemies_.back()->x()));
    enemies_.back()->setPos(nPos, 0);

    /*connect(enemies_.back(), &Enemy::sigGameOver, this, &Game::onGameOver);
    connect(enemies_.back(), &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
    connect(enemies_.back(), &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);*/
  }
  ourEnemy_ = enemies_.begin();

 /* std::size_t amountOfEnemies = 20 + rand() % VARIABLE_AMOUNT_OF_ENEMIES;//////////////////////////////

  std::vector<Enemy> vect(amountOfEnemies, Enemy(EnemyType::Corporal));
  enemies_ = vect;
  for (std::size_t i = 0; i < amountOfEnemies; ++i)
  {
    int nType = rand() % 5;
    enemies_[i].setType(static_cast<EnemyType>(nType));
    int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(enemies_[i].x()));
    enemies_[i].setPos(nPos, 0);
  }
  ourEnemy_ = &enemies_[0];*/ ///////////////////////////////////////////////////////////////////
  /*int amountOfEnemies = 20 + rand() % VARIABLE_AMOUNT_OF_ENEMIES;
  for (int i = 0; i <= amountOfEnemies; ++i)
  {
    int nType = rand() % 5;

    enemies_.emplace_back(static_cast<EnemyType>(nType));
    ourEnemy_ = &(enemies_.back());
    int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(ourEnemy_->x()));

    ourEnemy_->setPos(nPos, 0);
    connect(ourEnemy_, &Enemy::sigGameOver, this, &Game::onGameOver);
    connect(ourEnemy_, &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
    connect(ourEnemy_, &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
    enemies_.push_back(pEnemy);
  }
  ourEnemy_ = &(enemies_.front());*/
  ////////////////////////////////////////////////
  /*int amountOfEnemies = 20 + rand() % VARIABLE_AMOUNT_OF_ENEMIES;
    for (int i = 0; i <= amountOfEnemies; ++i)
    {
      int nType = rand() % 5;
      Enemy *pEnemy = new Enemy(static_cast<EnemyType>(nType));
      enemies_.push_back(pEnemy);
      //delete pEnemy;
     // int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(enemies_.back()->x()));
      //enemies_.back()->setPos(nPos, 0);

     connect(enemies_.back(), &Enemy::sigGameOver, this, &Game::onGameOver);
      connect(enemies_.back(), &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
      connect(enemies_.back(), &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
    }*/
    //currentEnemy_ = &enemies_.front();
////////////////////////////////////////////////////////////////////////////////
  m_pPoints = new Points();
  scene()->addItem(m_pPoints);

  //QTimer *pTimer = new QTimer(this);
  pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
  qDebug() << "start";
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
  /*if (event->key() == Qt::Key_Left)
  {
    if (event->key() == Qt::Key_Space)
    {
      m_pPlayer->shoot();
    }
    if (m_pPlayer->pos().x() > 0)
    {
      m_pPlayer->setPos(m_pPlayer->x() - 20, m_pPlayer->y());
    }
  }
  else if (event->key() == Qt::Key_Right)
  {
    if (event->key() == Qt::Key_Space)
    {
      m_pPlayer->shoot();
    }
    if (m_pPlayer->pos().x() + gPlayerSize.width() < m_oScreenSize.width())
    {
      m_pPlayer->setPos(m_pPlayer->x() + 20, m_pPlayer->y());
    }
  }
  else if (event->key() == Qt::Key_Space)
  {
    m_pPlayer->shoot();
  }*/
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
///////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  /*qDebug() << "start1";
  scene()->addItem(ourEnemy_);
  qDebug() << "start2";
  connect(ourEnemy_, &Enemy::sigGameOver, this, &Game::onGameOver);
  connect(ourEnemy_, &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(ourEnemy_, &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
  if (++ourEnemy_ == nullptr)
  {
    pTimer->stop();
    disconnect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
  }*/
  qDebug() << "start1";
  scene()->addItem(*ourEnemy_);
  qDebug() << "start2";
  connect(*ourEnemy_, &Enemy::sigGameOver, this, &Game::onGameOver);
  connect(*ourEnemy_, &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(*ourEnemy_, &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
  ++ourEnemy_;
  if (*ourEnemy_ == nullptr)
  {
    pTimer->stop();
    disconnect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
   /* Boss *boss = new Boss(BossType::Soul);
    int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(boss->x()));
    boss->setPos(nPos, 0);
    scene()->addItem(boss);
    connect(boss, &Boss::sigGameOver, this, &Game::onGameOver);
    connect(boss, &Boss::sigIncreaseScore, this, &Game::onIncreaseScore);
    connect(boss, &Boss::sigWin, this, &Game::onGameOver);*/
  }
  /*else
  {
    ++ourEnemy_;
  }*/
  /////////////////////////////////
  /*int nType = rand() % 5;
  Enemy *pEnemy = new Enemy(static_cast<EnemyType>(nType));
  enemies_.push_back(pEnemy);
  int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(enemies_.back()->x()));

  enemies_.back()->setPos(nPos, 0);
  scene()->addItem(enemies_.back());
  connect(enemies_.back(), &Enemy::sigGameOver, this, &Game::onGameOver);
  connect(enemies_.back(), &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(enemies_.back(), &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);*/
  /////////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  /*int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(enemies_.back()->x()));
  enemies_.at(currentEnemy_)->setPos(nPos, 0);

  scene()->addItem(enemies_.at(currentEnemy_));
  connect(enemies_.at(currentEnemy_), &Enemy::sigGameOver, this, &Game::onGameOver);
  connect(enemies_.at(currentEnemy_), &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(enemies_.at(currentEnemy_), &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
  ++currentEnemy_;
  if (enemies_[currentEnemy_] == nullptr)
  {
    pTimer->stop();
  }*/
  /*scene()->addItem(currentEnemy_);
  if (std::next(currentEnemy_) == nullptr)
  {
    pTimer->stop();
  }
  else
  {
    ++currentEnemy_;
  }*/
////////////////////////
  //currentEnemy_.
  //Enemy *pEnemy = *currentEnemy_;
  /////////////////////////////////////////
 /* int nPos = rand() % (m_oScreenSize.width() - static_cast<int>((*currentEnemy_)->x()));
  (*currentEnemy_)->setPos(nPos, 0);
  scene()->addItem((*currentEnemy_));
  connect(*currentEnemy_, &Enemy::sigGameOver, this, &Game::onGameOver);
  connect(*currentEnemy_, &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(*currentEnemy_, &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
  if (std::next(*currentEnemy_) == nullptr)
  {
    pTimer->stop();
  }
  else
  {
    currentEnemy_++;
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

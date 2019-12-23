#include "game.h"

#include <QDebug>

#include <QTime>
#include <QCoreApplication>

static int ENEMY_NUMBER = 0;

Game::Game(QSize oScreenSize, QWidget *pParent) :
  QGraphicsView(pParent),
  scorePoints(0),
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

  scorePoints = 0;

  m_pPlayer = new Player();
  m_pPlayer->setPos(m_oScreenSize.width() / 2, m_oScreenSize.height() - gPlayerSize.height());
  m_pPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
  m_pPlayer->setFocus();
  scene()->addItem(m_pPlayer);

  connect(m_pPlayer, &Player::sigGameOver, this, &Game::displayGameOverMenu);
  connect(m_pPlayer, &Player::sigIncreaseScore, this, &Game::onIncreaseScore);
  connect(m_pPlayer, &Player::sigDecreaseScore, this, &Game::onDecreaseScore);
  /////////////////////////////////////////////////////////////////////////////////

  std::size_t amountOfEnemies = 10;//20 + rand() % VARIABLE_AMOUNT_OF_ENEMIES;
  Opponent *pEnemy = nullptr;
  int nType;
  int nPos;
  for (std::size_t i = 0; i < amountOfEnemies; ++i)
  {
    nType = rand() % 5;
    pEnemy = new Enemy(static_cast<EnemyType>(nType));
    enemies_.push_back(pEnemy);
   // nPos = rand() % (m_oScreenSize.width() - static_cast<int>(enemies_.back()->getSize().width() * 2));
    nPos = rand() % static_cast<int>(scene()->width() - enemies_.back()->getSize().width());
    enemies_.back()->setPos(nPos, 0);

    /*connect(enemies_.back(), &Enemy::sigGameOver, this, &Game::onGameOver);
    connect(enemies_.back(), &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
    connect(enemies_.back(), &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);*/
  }
  ourEnemy_ = enemies_.begin();

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
  //scorePoints += m_pPoints->getScore();
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
  else
  {
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
      default:
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
  connect(dynamic_cast<Enemy *>(*ourEnemy_), &Enemy::sigGameOver, this, &Game::displayGameOverMenu);
  connect(dynamic_cast<Enemy *>(*ourEnemy_), &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(dynamic_cast<Enemy *>(*ourEnemy_), &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
  enemyType_ = (dynamic_cast<Enemy *>(*ourEnemy_))->getType();
  ++ourEnemy_;
  qDebug() << "added";
  if (ourEnemy_ == enemies_.end())//*ourEnemy_ == nullptr)
  {
    qDebug() << "in";
    enemies_.clear();
    pTimer->stop();
    disconnect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);

    QTime dieTime= QTime::currentTime().addSecs(15);

    while (QTime::currentTime() < dieTime)
    {
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    //Sleep(6000);
   /* pTimer = new QTimer(this);
    pTimer->setSingleShot(true);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
    pTimer->start(6000);*/

   // pTimer->start(4000);
   // pTimer->stop();
    Boss *boss = new Boss(BossType::Soul);
    int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(boss->getSize().width()));
    boss->setPos(nPos, 0);
    scene()->addItem(boss);
    connect(boss, &Boss::sigGameOver, this, &Game::displayGameOverMenu);
    connect(boss, &Boss::sigIncreaseScore, this, &Game::onIncreaseScore);
    connect(boss, &Boss::sigWin, this, &Game::displayGameOverMenu);
  }
}

void Game::displayMainMenu()
{
    // create title text
  scene()->clear();
  QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
  QPixmap oPixmap(":/images/Resources/images/mainLogo.png");
  title->setPixmap(oPixmap.scaled(QSize(400, 1000), Qt::KeepAspectRatio));
  /*QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Space Invaders"));
  QFont titleFont("comic sans", 50);
  titleText->setFont(titleFont);
  int xTitlePos = this->width()/2 - titleText->boundingRect().width()/2;
  int yTitlePos = 150;
  titleText->setPos(xTitlePos, yTitlePos);
  scene()->addItem(titleText);*/
  int xTitlePos = this->width()/2 - title->boundingRect().width()/2;
  int yTitlePos = 150;
  title->setPos(xTitlePos, yTitlePos);
  scene()->addItem(title);

  // create play button
  Button *playButton = new Button(QString("Play"));
  int xPlayPos = this->width()/2 - playButton->boundingRect().width()/2;
  int yPlayPos = 275;
  playButton->setPos(xPlayPos, yPlayPos);
  connect(playButton, &Button::clicked, this, &Game::Run);
  scene()->addItem(playButton);

  // create quit button
  Button *quitButton = new Button(QString("Quit"));
  int xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
  int yQuitPos = 425;
  quitButton->setPos(xQuitPos, yQuitPos);
  connect(quitButton, &Button::clicked, this, &Game::onGameOver);
  scene()->addItem(quitButton);
}

void Game::displayGameOverMenu()
{
  //int scorePoints = m_pPoints->getScore();
  pTimer->stop();
  disconnect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
 /* disconnect(m_pPlayer, &Player::sigGameOver, this, &Game::displayGameOverMenu);
  disconnect(m_pPlayer, &Player::sigIncreaseScore, this, &Game::onIncreaseScore);
  disconnect(m_pPlayer, &Player::sigDecreaseScore, this, &Game::onDecreaseScore);*/
  //delete *ourEnemy_;
  enemies_.clear();

  scene()->clear();
  setCursor(Qt::ArrowCursor);

  //int scorePoints = m_pPoints->getScore();

  scene()->items().clear();

  //delete m_pPlayer;
  m_pPlayer = nullptr;

  //SetKeyboardState()

  QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
  QPixmap oPixmap(":/images/Resources/images/result.jpg");
  QRect rect(108, 150, 370, 181);
  QPixmap newPixmap = oPixmap.copy(rect);
  title->setPixmap(newPixmap.scaled(QSize(400, 1000), Qt::KeepAspectRatio));
  int xTitlePos = this->width()/2 - title->boundingRect().width()/2;
  int yTitlePos = 150;
  title->setPos(xTitlePos, yTitlePos);
  scene()->addItem(title);

  QGraphicsTextItem *score = new QGraphicsTextItem(QString("Score: ") + QString::number(scorePoints));
  QFont scoreFont("comic sans", 50);
  score->setFont(scoreFont);
  int xScorePos = this->width() / 2 - score->boundingRect().width() / 2;
  int yScorePos = 200;
  score->setPos(xScorePos, yScorePos);
  scene()->addItem(score);

  Button *retryButton = new Button(QString("Retry"));
  int xPlayPos = this->width()/2 - retryButton->boundingRect().width()/2;
  int yPlayPos = 275;
  retryButton->setPos(xPlayPos, yPlayPos);
  connect(retryButton, &Button::clicked, this, &Game::Run);
  scene()->addItem(retryButton);

  Button *menuButton = new Button(QString("Menu"));
  int xMenuPos = this->width()/2 - menuButton->boundingRect().width()/2;
  int yMenuPos = 350;
  menuButton->setPos(xMenuPos, yMenuPos);
  connect(menuButton, &Button::clicked, this, &Game::displayMainMenu);
  scene()->addItem(menuButton);

  Button *quitButton = new Button(QString("Quit"));
  int xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
  int yQuitPos = 425;
  quitButton->setPos(xQuitPos, yQuitPos);
  connect(quitButton, &Button::clicked, this, &Game::onGameOver);
  scene()->addItem(quitButton);
}

void Game::onIncreaseScore(int points)
{
  scorePoints += points;
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

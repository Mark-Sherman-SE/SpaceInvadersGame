#include "game.h"

#include <QDebug>

#include <QTime>
#include <QCoreApplication>

//конструктор игры
Game::Game(QSize oScreenSize, QWidget *pParent) :
  QGraphicsView(pParent),
  scorePoints(0),
  m_oScreenSize(oScreenSize)
{
  //создаём сцену
  QGraphicsScene * pScene = new QGraphicsScene();
  setScene(pScene);

  //устанавливаем размер сцены и её параметры
  pScene->setSceneRect(0, 0, m_oScreenSize.width(), m_oScreenSize.height());
  setBackgroundBrush(QBrush(QImage(":/images/Resources/images/SpaceInvadersBg.jpg")));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setCursor(Qt::PointingHandCursor);
  setStyleSheet("border-style:none");
}

//метод начала игры
void Game::Run()
{
  //очищаем сцену и убираем курсор
  scene()->clear();
  setCursor(Qt::BlankCursor);

  scorePoints = 0;

  //выбираем случайно оружие для игрока и создаём его
  int pType = rand() % 3;
  m_pPlayer = new Player(static_cast<WeaponType>(pType));
  //устанавливаем положение игрока
  m_pPlayer->setPos(m_oScreenSize.width() / 2, m_oScreenSize.height() - gPlayerSize.height());
  m_pPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
  m_pPlayer->setFocus();
  //добавляем игрока на сцену
  scene()->addItem(m_pPlayer);

  //соединяем сигналы
  connect(m_pPlayer, &Player::sigGameOver, this, &Game::displayGameOverMenu);
  connect(m_pPlayer, &Player::sigIncreaseScore, this, &Game::onIncreaseScore);
  connect(m_pPlayer, &Player::sigDecreaseScore, this, &Game::onDecreaseScore);

  //задаём количество врагов от 20 до 39
  std::size_t amountOfEnemies = 20 + rand() % VARIABLE_AMOUNT_OF_ENEMIES;
  Opponent *pEnemy = nullptr;
  int nType;
  int nPos;
  //цикл заполнения списка врагов
  for (std::size_t i = 0; i < amountOfEnemies; ++i)
  {
    nType = rand() % 5;
    pEnemy = new Enemy(static_cast<EnemyType>(nType));
    enemies_.push_back(pEnemy);
    nPos = rand() % static_cast<int>(scene()->width() - enemies_.back()->getSize().width());
    enemies_.back()->setPos(nPos, 0);
  }
  //устанавливаем итератор на начало списка
  ourEnemy_ = enemies_.begin();

  //создаём очки
  m_pPoints = new Points();
  scene()->addItem(m_pPoints);

  //таймер для создания врагов
  pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
  //каждые 3 секунды будет появлять враг
  pTimer->start(3000);
}

//проверяем очки, если счёт меньше 0 или жизни базы закончились, то заканчиваем игру
void Game::CheckPoints()
{
  if ((m_pPoints->getScore() < 0) || (m_pPoints->getHealth() <= 0))
  {
    m_pPoints->reset();
    onGameOver();
  }
}

//метод управления игроком
//стрелка влево - перемещение влево, стрелка вправо - перемещение вправо, пробел - атака
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
  //добавляем врага на сцену и соединаем все сигналы
  scene()->addItem(*ourEnemy_);
  connect(dynamic_cast<Enemy *>(*ourEnemy_), &Enemy::sigGameOver, this, &Game::displayGameOverMenu);
  connect(dynamic_cast<Enemy *>(*ourEnemy_), &Enemy::sigDecreaseHealth, this, &Game::onDecreaseHealth);
  connect(dynamic_cast<Enemy *>(*ourEnemy_), &Enemy::sigIncreaseScore, this, &Game::onIncreaseScore);
  enemyType_ = (dynamic_cast<Enemy *>(*ourEnemy_))->getType();
  //переводим итератор на следующего врага
  ++ourEnemy_;
  //если враги закончились, то...
  if (ourEnemy_ == enemies_.end())
  {
    //очищаем вектор врагов
    enemies_.clear();
    //останавливаем таймер и отсоединяем его от метода создания врагов
    pTimer->stop();
    disconnect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);

    //ждём 15 секунд
    QTime dieTime= QTime::currentTime().addSecs(15);

    while (QTime::currentTime() < dieTime)
    {
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    //выбираем случайный тип босса, создаём его, задаём позицию, добавляем на сцену и соединяем сигналы
    int bType = rand() % 3;
    Boss *boss = new Boss(static_cast<BossType>(bType));
    int nPos = rand() % (m_oScreenSize.width() - static_cast<int>(boss->getSize().width()));
    boss->setPos(nPos, 0);
    scene()->addItem(boss);
    connect(boss, &Boss::sigGameOver, this, &Game::displayGameOverMenu);
    connect(boss, &Boss::sigIncreaseScore, this, &Game::onIncreaseScore);
    connect(boss, &Boss::sigWin, this, &Game::displayGameOverMenu);
  }
}

//отображение главного меню
void Game::displayMainMenu()
{
  //очищаем сцену
  scene()->clear();
  //создаём заголовок главного меню
  QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
  QPixmap oPixmap(":/images/Resources/images/mainLogo.png");
  title->setPixmap(oPixmap.scaled(QSize(400, 1000), Qt::KeepAspectRatio));
  int xTitlePos = this->width()/2 - title->boundingRect().width()/2;
  int yTitlePos = 150;
  title->setPos(xTitlePos, yTitlePos);
  scene()->addItem(title);

  //создаём кнопку начала игры
  Button *playButton = new Button(QString("Play"));
  int xPlayPos = this->width()/2 - playButton->boundingRect().width()/2;
  int yPlayPos = 275;
  playButton->setPos(xPlayPos, yPlayPos);
  connect(playButton, &Button::clicked, this, &Game::Run);
  scene()->addItem(playButton);

  //создаём кнопку выхода
  Button *quitButton = new Button(QString("Quit"));
  int xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
  int yQuitPos = 425;
  quitButton->setPos(xQuitPos, yQuitPos);
  connect(quitButton, &Button::clicked, this, &Game::onGameOver);
  scene()->addItem(quitButton);
}

//меню конца игры
void Game::displayGameOverMenu()
{
  //останавливаем таймер, отсоединяем его, очищаем список врагов
  pTimer->stop();
  disconnect(pTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
  enemies_.clear();

  //очищаем сцену и устанавливаем курсор
  setCursor(Qt::ArrowCursor);

  //удаляем объекты со сцены
  scene()->items().clear();
  scene()->clear();

  m_pPlayer = nullptr;

  QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
  QPixmap oPixmap(":/images/Resources/images/result.jpg");
  QRect rect(108, 150, 370, 181);
  QPixmap newPixmap = oPixmap.copy(rect);
  title->setPixmap(newPixmap.scaled(QSize(400, 1000), Qt::KeepAspectRatio));
  int xTitlePos = this->width()/2 - title->boundingRect().width()/2;
  int yTitlePos = 150;
  title->setPos(xTitlePos, yTitlePos);
  scene()->addItem(title);

  //выводим количество очков на экран
  QGraphicsTextItem *score = new QGraphicsTextItem(QString("Score: ") + QString::number(scorePoints));
  QFont scoreFont("comic sans", 50);
  score->setFont(scoreFont);
  int xScorePos = this->width() / 2 - score->boundingRect().width() / 2;
  int yScorePos = 200;
  score->setPos(xScorePos, yScorePos);
  scene()->addItem(score);

  //создаём кнопку повтора
  Button *retryButton = new Button(QString("Retry"));
  int xPlayPos = this->width()/2 - retryButton->boundingRect().width()/2;
  int yPlayPos = 275;
  retryButton->setPos(xPlayPos, yPlayPos);
  connect(retryButton, &Button::clicked, this, &Game::Run);
  scene()->addItem(retryButton);

  //создаём кнопку выхода в главное меню
  Button *menuButton = new Button(QString("Menu"));
  int xMenuPos = this->width()/2 - menuButton->boundingRect().width()/2;
  int yMenuPos = 350;
  menuButton->setPos(xMenuPos, yMenuPos);
  connect(menuButton, &Button::clicked, this, &Game::displayMainMenu);
  scene()->addItem(menuButton);

  //создаём кнопку выхода
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

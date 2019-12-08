#include "points.h"
//#include <QTimer>
#include <QGraphicsScene>

Points::Points(QGraphicsItem *pParent) : QGraphicsTextItem(pParent)
{
  setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n"
               + QString("Score : ") + QString::number(m_nScore));
  setDefaultTextColor(Qt::red);
  setFont(QFont("times", 24));
}

void Points::increaseScore(int points)
{
  m_nScore += points;
  setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n"
               + QString("Score : ") + QString::number(m_nScore));
}

void Points::decreaseScore()
{
  m_nScore -= 50;
  setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n"
               + QString("Score : ") + QString::number(m_nScore));
}

void Points::decreaseHealth()
{
  m_nHealth--;
  setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n"
               + QString("Score : ") + QString::number(m_nScore));
}

int Points::getHealth() const
{
  return m_nHealth;
}

int Points::getScore() const
{
  return m_nScore;
}

void Points::reset()
{
  m_nScore = 0;
  m_nHealth = 100;
  setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n"
               + QString("Score : ") + QString::number(m_nScore));
}

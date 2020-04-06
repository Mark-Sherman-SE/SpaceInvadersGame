#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

//класс кнопки, необходимый для меню
//наследуемся от QObject и QGraphicsRectItem, для корректной обработки взаимодействия
//и установки необходимой формы
class Button: public QObject, public QGraphicsRectItem
{
  Q_OBJECT
public:
  Button(QString name, QGraphicsItem *parent = nullptr);

  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
  void clicked();

private:
  QGraphicsTextItem *text;
};

#endif // BUTTON_H

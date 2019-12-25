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
  //конструктор класса, принимает название кнопки
  Button(QString name, QGraphicsItem *parent = nullptr);

  //метод нажатия на кнопу
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  //меняем цвет кнопки, когда указываем на неё
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  //возвпащаем предыдущий цвет кнопки, когда убираем с неё мышку
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
  //сигнал нажатия на кнопку
  void clicked();

private:
  //текст на кнопке
  QGraphicsTextItem *text;

};

#endif // BUTTON_H

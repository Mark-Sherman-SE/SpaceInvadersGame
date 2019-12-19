#include <QApplication>
#include <QScreen>
#include "game.h"

int main(int argc, char *argv[])
{
  srand(time(nullptr));
  QApplication a(argc, argv);
  Game *pGame = new Game(qApp->screens()[0]->size());
  pGame->showFullScreen();
  pGame->displayMainMenu();//Run();
  return a.exec();
}

#include <QApplication>
#include <QScreen>
#include "game.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Game *pGame = new Game(qApp->screens()[0]->size());
  pGame->showFullScreen();
  pGame->Run();
  return a.exec();
}

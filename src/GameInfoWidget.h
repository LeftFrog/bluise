#pragma once
#include <QLabel>
#include "Game.h"
#include <QMenu>
#include "QtAwesome/QtAwesome/QtAwesome.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GameInfoWidget;
}
QT_END_NAMESPACE

class GameInfoWidget : public QWidget {
  Q_OBJECT
public:
  explicit GameInfoWidget(QWidget *parent = nullptr);
  ~GameInfoWidget();
public slots:
  void setGame(const QModelIndex& index);
protected:
  // void resizeEvent(QResizeEvent *event) override;
private slots:
  void play();
  void settings();
  void popupMenu();
  void setIcon(Qt::ColorScheme scheme);
private:
  Game *game;
  QMenu *menu;
  fa::QtAwesome *awesome = new fa::QtAwesome;
  Ui::GameInfoWidget *ui;
};
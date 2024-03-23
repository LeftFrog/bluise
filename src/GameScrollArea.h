#pragma once
#include <QScrollArea>

class GameScrollArea : public QScrollArea {
  Q_OBJECT
public:
  GameScrollArea(QWidget *parent = nullptr);
};
#pragma once 
#include <QWidget>
#include "GameOptionWidget.h"
#include "ChoosePictureWidget.h"
#include <QPushButton>
#include "bluise.h"

class GameAddWidget : public QWidget
{
    Q_OBJECT
private:
    GameOptionWidget* name;
    GameOptionWidget* working_directory;
    GameOptionWidget* exec;
    GameOptionWidget* save_path;
    ChoosePictureWidget* choose;
    QPushButton* addButton;
private slots:
    void closeWin() { close(); }
    void addGame();
public:
    GameAddWidget(QWidget* parent = nullptr);
};
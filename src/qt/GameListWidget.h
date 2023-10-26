#include <QtWidgets>
#include "bluise.h"
#include "GameWidget.h"

class GameListWidget : public QWidget {
    Q_OBJECT
private:
    QVector<GameWidget> game_widgets;
public:
    GameListWidget(QWidget *parent = nullptr);
};
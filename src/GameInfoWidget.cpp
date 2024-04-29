#include "GameInfoWidget.h"
#include "./ui_GameInfoWidget.h"
#include <QtWidgets>
#include "GameEditWidget.h"
#include "bluise.h"

GameInfoWidget::GameInfoWidget(QWidget *parent) : QWidget(parent), ui(new Ui::GameInfoWidget) {
  ui->setupUi(this);
  setFixedHeight(100);

  menu = new QMenu();

  awesome = new fa::QtAwesome;
  awesome->initFontAwesome();
  
  QAction *play = new QAction(/*awesome->icon(fa::fa_solid, fa::fa_play),*/ "Play", menu);
  connect(play, &QAction::triggered, this, &GameInfoWidget::play);
  QAction *settings = new QAction(/*awesome->icon(fa::fa_solid, fa::fa_gear),*/ "Settings", menu);
  connect(settings, &QAction::triggered, this, &GameInfoWidget::settings);
  menu->addAction(play);
  menu->addSeparator();
  menu->addAction(settings);

  connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, this, &GameInfoWidget::setIcon);

  connect(ui->pushButton_2, &QPushButton::clicked, this, &GameInfoWidget::play);
  connect(ui->pushButton, &QPushButton::clicked, this, &GameInfoWidget::popupMenu);

  ui->pushButton->setIcon(awesome->icon(fa::fa_solid, fa::fa_chevron_down));
  setIcon(QApplication::styleHints()->colorScheme());

  // QPalette palette = this->palette();
  // palette.setColor(QPalette::Window, palette.color(QPalette::Midlight));
  setBackgroundRole(QPalette::Midlight);
  setAutoFillBackground(true);
  // this->setPalette(palette);

  ui->label->setFont(QFont("Arial", 22));
}

GameInfoWidget::~GameInfoWidget() {
  delete ui;
}

void GameInfoWidget::setGame(const QModelIndex& index) {
  game = index.data(Qt::UserRole + 1).value<Game *>();
  if(game == nullptr) {
    return;
  }
  ui->label->setText(game->getName());
  this->show();
}

void GameInfoWidget::play() {
  if(game->isDisabled()) {
    QMessageBox::critical(this, "Error", "This game is not available.");
  }
  else {
    game->execute();
  }
}

void GameInfoWidget::settings() {
  GameEditWidget *edit_widget = new GameEditWidget(game);
  edit_widget->show();
}


void GameInfoWidget::popupMenu() {
  qDebug() << "KOK";
  menu->popup(QCursor::pos());
}

void GameInfoWidget::setIcon(Qt::ColorScheme scheme) {
  delete awesome;
  awesome = new fa::QtAwesome;
  awesome->initFontAwesome();
  ui->pushButton->setIcon(awesome->icon(fa::fa_solid, fa::fa_chevron_down));
}
#include "GameEditWidget.h"
#include "ChoosePictureWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>

GameEditWidget::GameEditWidget(Game* _game, QWidget* parent) : QWidget(parent), game(_game) {
    name = new GameOptionWidget("Name: ", QString::fromStdString(game->get_name()));
    
    working_directory = new GameOptionWidget("Working directory: ", QString::fromStdString(game->get_working_directory()), false);

    exec = new GameOptionWidget("Executable: ", QString::fromStdString(game->get_executable()), true);

    save_path = new GameOptionWidget("Save path: ", QString::fromStdString(game->get_save_path()), false);

    QPushButton* apply = new QPushButton("Apply");
    connect(apply, &QPushButton::clicked, this, &GameEditWidget::apply);
    apply->setDefault(true);
    QPushButton* cancel = new QPushButton("Cancel");
    connect(cancel, &QPushButton::clicked, this, &GameEditWidget::closeWin);
    QHBoxLayout* HBL4 = new QHBoxLayout;
    HBL4->addWidget(cancel);
    HBL4->addWidget(apply);

    QVBoxLayout* VBL = new QVBoxLayout;
    ChoosePictureWidget* choose = new ChoosePictureWidget();
    choose->setPicture(game->get_header_path());
    VBL->addWidget(choose);
    VBL->addWidget(name);
    VBL->addWidget(working_directory);
    VBL->addWidget(exec);
    VBL->addWidget(save_path);
    VBL->addLayout(HBL4);
    setLayout(VBL);
}

void GameEditWidget::closeWin()
{
    close();
}

void GameEditWidget::apply()
{
    game->set_name(name->text().toStdString());
    game->set_working_directory(working_directory->text().toStdString());
    game->set_executable(exec->text().toStdString());
    game->set_save_path(save_path->text().toStdString());
    emit gameChanged();
    close();
}
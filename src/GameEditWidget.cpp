#include "GameEditWidget.h"
#include "ChoosePictureWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

GameEditWidget::GameEditWidget(Game* _game, QWidget* parent) : QWidget(parent), game(_game) {
    name = new GameOptionWidget("Name: ", game->get_name());
    connect(name, &GameOptionWidget::gameChanged, this, &GameEditWidget::changed);
    
    working_directory = new GameOptionWidget("Working directory: ", game->get_working_directory(), false);
    connect(working_directory, &GameOptionWidget::gameChanged, this, &GameEditWidget::changed);

    exec = new GameOptionWidget("Executable: ", game->get_executable(), true);
    connect(exec, &GameOptionWidget::gameChanged, this, &GameEditWidget::changed);

    save_path = new GameOptionWidget("Save path: ", game->get_save_path(), false);
    connect(save_path, &GameOptionWidget::gameChanged, this, &GameEditWidget::changed);

    applyButton = new QPushButton("Apply");
    connect(applyButton, &QPushButton::clicked, this, &GameEditWidget::apply);
    applyButton->setDefault(true);
    applyButton->setDisabled(true);
    QPushButton* cancel = new QPushButton("Cancel");
    connect(cancel, &QPushButton::clicked, this, &GameEditWidget::closeWin);
    QHBoxLayout* HBL4 = new QHBoxLayout;
    HBL4->addWidget(cancel);
    HBL4->addWidget(applyButton);

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
    game->set_name(name->text());
    game->set_working_directory(working_directory->text());
    game->set_executable(exec->text());
    game->set_save_path(save_path->text());
    emit gameChanged();
    close();
}

void GameEditWidget::changed()
{
    if(!applyButton->isEnabled()) {
        if(name->isChanged() || working_directory->isChanged() || exec->isChanged() || save_path->isChanged()) {
            applyButton->setEnabled(true);
        }
    }
    else {
        if(!name->isChanged() && !working_directory->isChanged() && !exec->isChanged() && !save_path->isChanged()) {
            applyButton->setDisabled(true);
        }
    }
}

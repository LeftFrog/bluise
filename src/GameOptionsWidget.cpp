#include "GameOptionsWidget.h"



GameOptionsWidget::GameOptionsWidget(QWidget * parent)
{
    name = new GameOptionWidget("Name: ", "");
    working_directory = new GameOptionWidget("Working directory: ", "");
    exec = new GameOptionWidget("Executable: ", "");
    save_path = new GameOptionWidget("Save path: ", "");
    choose = new ChoosePictureWidget("");
    applyButton = new QPushButton("Apply");
    connect(applyButton, &QPushButton::clicked, this, &GameOptionsWidget::apply);
    applyButton->setDefault(true);
    applyButton->setDisabled(true);
    QPushButton* cancel = new QPushButton("Cancel");
    connect(cancel, &QPushButton::clicked, this, &GameOptionsWidget::closeWin);
    QHBoxLayout* HBL = new QHBoxLayout;
    HBL->addWidget(cancel);
    HBL->addWidget(applyButton);
    QVBoxLayout* VBL = new QVBoxLayout;
    VBL->addWidget(choose);
    VBL->addWidget(name);
    VBL->addWidget(working_directory);
    VBL->addWidget(exec);
    VBL->addWidget(save_path);
    VBL->addLayout(HBL);
    setLayout(VBL);
}

GameOptionsWidget::GameOptionsWidget(const Game game, QWidget * parent)
{
    name = new GameOptionWidget("Name: ", game.get_name());
    working_directory = new GameOptionWidget("Working directory: ", game.get_working_directory());
    exec = new GameOptionWidget("Executable: ", game.get_executable());
    save_path = new GameOptionWidget("Save path: ", game.get_save_path());
    choose = new ChoosePictureWidget(game.get_header_path());
    applyButton = new QPushButton("Apply");
    connect(applyButton, &QPushButton::clicked, this, &GameOptionsWidget::apply);
    applyButton->setDefault(true);
    applyButton->setDisabled(true);
    QPushButton* cancel = new QPushButton("Cancel");
    connect(cancel, &QPushButton::clicked, this, &GameOptionsWidget::closeWin);
    QHBoxLayout* HBL = new QHBoxLayout;
    HBL->addWidget(cancel);
    HBL->addWidget(applyButton);
    QVBoxLayout* VBL = new QVBoxLayout;
    VBL->addWidget(choose);
    VBL->addWidget(name);
    VBL->addWidget(working_directory);
    VBL->addWidget(exec);
    VBL->addWidget(save_path);
    VBL->addLayout(HBL);
    setLayout(VBL);
}

void GameOptionsWidget::closeWin()
{
    close();
}
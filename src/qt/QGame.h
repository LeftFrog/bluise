#pragma once
#include <QIcon>
#include <QString>
#include <string>
#include <filesystem>
#include "bluise.h"
#include "Game.h"

class QGame : public Game {
public:
    QGame(const string& n, const string& wd, const string& e, const string& sp);
    QIcon get_icon() const { return icon; }
    QIcon get_header() const { return header; }
private:
    QIcon icon;
    QIcon header;
};
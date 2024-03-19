#include "FileValidator.h"
#include <filesystem>


FileValidator::FileValidator(bool _isDirectory, QObject * parent) : QValidator(parent), isDirectory(_isDirectory) {
}

QValidator::State FileValidator::validate(QString& str, int& pos) const {
    if(isDirectory) {
        if(std::filesystem::is_directory(str.toStdString())) {
            return QValidator::Acceptable;
        }
        else {
            return QValidator::Intermediate;
        }
    }
    else {
        if(std::filesystem::exists(str.toStdString())) {
            return QValidator::Acceptable;
        }
        else {
            return QValidator::Intermediate;
        }
    }
}

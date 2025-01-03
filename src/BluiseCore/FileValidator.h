#pragma once
#include <QValidator>

class FileValidator : public QValidator {
public:
    FileValidator(bool _isDirectory = false, QObject* parent = nullptr);
    virtual State validate(QString& str, int& pos) const override;

private:
    bool isDirectory;
};

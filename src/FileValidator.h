#include <QValidator>

class FileValidator : public QValidator
{
private:
    bool isDirectory;
public:
    FileValidator(bool _isDirectory = false, QObject* parent = nullptr);
    virtual State validate(QString& str, int& pos) const override;
};

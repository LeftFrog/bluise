#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileDialog>

class GameOptionWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* ledit;
    QLabel* lbl;
    bool has_file_dialog;
private slots:
    void open_file();
public:
    GameOptionWidget(const QString& label, const QString& text, QWidget* parent = nullptr);
    GameOptionWidget(const QString& label, const QString& text, bool _has_file_dialog, QWidget* parent = nullptr);
    QString text() const { return ledit->text(); }
};

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include "ColorBox.h"
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    std::shared_ptr<QPushButton> startButton_;
    void startButtonClicked();
    void runMindReading(int number);
};
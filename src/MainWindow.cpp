#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <iostream>
#include <QApplication>
#include <QInputDialog>
#include <QLabel>
#include <QWidget>
#include <QPalette>
#include <QTimer>
#include <QPainter>
#include "ColorBox.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 创建一个中心小部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget); // 设置中心小部件

    auto mainLayout = new QVBoxLayout(centralWidget);            // 使用水平布局
    startButton_ = std::make_shared<QPushButton>("Start", this); // 指定父对象

    mainLayout->addWidget(startButton_.get());

    // 连接按钮点击信号
    connect(startButton_.get(), &QPushButton::clicked, this, &MainWindow::startButtonClicked);
}

void MainWindow::startButtonClicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle("MindReader");
    dialog.setLabelText(QString("Please input a number between 1 and 10"));
    dialog.setTextValue("");
    dialog.setOkButtonText("read my mind");
    dialog.setCancelButtonText("Cancel");
    if (dialog.exec() == QDialog::Accepted)
    {
        startButton_->setVisible(false);

        QString input = dialog.textValue();
        int number = input.toInt();
        runMindReading(number);
    }
}
// ... existing code ...
void MainWindow::runMindReading(int number)
{
    // 创建一个新的窗口
    QWidget *colorWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(colorWidget);
    colorWidget->resize(200, 100);
    // 创建一个可以涂色的框
    ColorBox *colorBox = new ColorBox(this);

    // 创建一段文字
    QLabel *textLabel = new QLabel("Analysing brainwaves...", this);
    textLabel->setFixedHeight(50);            // 设置 QLabel 的固定高度
    textLabel->setAlignment(Qt::AlignCenter); // 设置文本居中对齐

    layout->addWidget(textLabel);

    // 将框和文字添加到布局中
    layout->addWidget(colorBox);

    // 显示新的窗口
    colorWidget->setLayout(layout);
    colorWidget->show();

    // 设置定时器以逐渐改变颜色
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [colorBox, textLabel, this, timer, number]() {
        static int step = 0;
        int maxSteps = 90; // 颜色变化的步数

        // 第一次填充颜色
        if (step < maxSteps)
        {
            colorBox->fillColor(step); // 填充颜色
            step++;
            QCoreApplication::processEvents(); // 处理事件以避免界面冻结
        }
        else
        {
            // 停止当前定时器
            timer->stop();                              // 使用捕获的 timer 停止定时器
            textLabel->setText("Scanning memories..."); // 更新文本内容为扫描阶段
            step = 0;                                   // 重置步数

            // 启动新的定时器以进行第二次填充
            QTimer *secondTimer = new QTimer(this);
            connect(secondTimer, &QTimer::timeout, [colorBox, textLabel, this, secondTimer, maxSteps, number]() {
                static int secondStep = 0;
                if (secondStep < maxSteps) {
                    colorBox->fillColor(secondStep + 90); // 填充颜色
                    secondStep++;
                    QCoreApplication::processEvents(); // 处理事件以避免界面冻结
                } else {
                    secondTimer->stop(); // 停止第二个定时器
                    textLabel->setText("Calculating Probability..."); // 
                    step = 0;
                    QTimer *thirdTimer = new QTimer(this);
                    connect(thirdTimer, &QTimer::timeout, [colorBox, textLabel, this, thirdTimer, maxSteps, number]() {
                        static int thirdStep = 0;
                        if (thirdStep < maxSteps) {
                            colorBox->fillColor(thirdStep);
                            thirdStep++;
                            QCoreApplication::processEvents();
                        } else {
                            thirdTimer->stop();
                            textLabel->setText("Decoding Thoughts...");
                            step = 0;
                            QTimer *fourthTimer = new QTimer(this);
                            connect(fourthTimer, &QTimer::timeout, [colorBox, textLabel, this, fourthTimer, maxSteps, number]() {
                                static int fourthStep = 0;
                                if (fourthStep < maxSteps) {
                                    colorBox->fillColor(fourthStep + 90);
                                    fourthStep++;
                                    QCoreApplication::processEvents();
                                } else {
                                    fourthTimer->stop();
                                    QMessageBox msgBox; // 创建消息框
                                    msgBox.setIcon(QMessageBox::NoIcon); // 设置无图标
                                    msgBox.setText("You are thinking about the number " + QString::number(number)); // 设置文本
                                    msgBox.exec(); // 显示消息框
                                }
                            });
                            fourthTimer->start(50);
                        }
                    });
                    thirdTimer->start(50);
                }
            });
            secondTimer->start(50); // 启动新的定时器以进行第二次填充
        }
    });
    timer->start(50); // 每100毫秒更新一次
    
}

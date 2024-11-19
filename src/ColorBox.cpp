#include "ColorBox.h"

ColorBox::ColorBox(QWidget *parent) : QWidget(parent), filledWidth(0) {
    setFixedSize(500, 100); // 设置框的大小
}

void ColorBox::fillColor(int width) {
    filledWidth = width;
    update(); // 触发重绘
}

void ColorBox::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event); // 避免未使用参数的警告
    QPainter painter(this);
    painter.setBrush(QColor(0, 255, 0)); // 设置填充颜色为绿色
    painter.drawRect(0, 0, filledWidth,20); // 绘制填充矩形
}

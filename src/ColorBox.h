#ifndef COLORBOX_H
#define COLORBOX_H

#include <QWidget>
#include <QPainter>

class ColorBox : public QWidget {
    Q_OBJECT

public:
    explicit ColorBox(QWidget *parent = nullptr);
    void fillColor(int width);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int filledWidth; // 已填充的宽度
};

#endif // COLORBOX_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <cmath>

class FunctionPlotter : public QWidget {
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 坐标轴
        painter.setPen(Qt::black);
        // 两个点坐标之间的连线
        painter.drawLine(20, height() / 2, width() - 20, height() / 2); // X轴
        painter.drawLine(width() / 2, 20, width() / 2, height() - 20); // Y轴

        // 画函数 y = sin(x)
        painter.setPen(Qt::red);
        for (int x = -width() / 2; x < width() / 2; x++) {
            int y1 = -std::sin(x / 50.0) * 100; // 归一化
            int y2 = -std::sin((x + 1) / 50.0) * 100;
            painter.drawLine(width() / 2 + x, height() / 2 + y1,
                             width() / 2 + x + 1, height() / 2 + y2);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FunctionPlotter plotter;
    plotter.resize(600, 400);
    plotter.setWindowTitle("数学函数绘制");
    plotter.show();

    return app.exec();
}

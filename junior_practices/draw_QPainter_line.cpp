#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <vector>

class ScatterPlot : public QWidget {
private:
    double x_min = -5, x_max = 5; // ✅ 指定 X 轴范围
    double y_min = -3, y_max = 3; // ✅ 指定 Y 轴范围
    std::vector<QPointF> points = {
        // ✅ 指定散点坐标
        {-4, -1}, {-2, 1.5}, {0, 0}, {1.5, -2}, {3, 1}, {4, -1.5}
    };

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 窗口大小
        int width = this->width();
        int height = this->height();

        // 坐标轴边界
        // 其实是上下左右间距
        int margin = 50;
        double axis_margin = 5;

        int x_start = margin, x_end = width - margin;
        int y_start = margin, y_end = height - margin;

        double y_axis_start = y_start + axis_margin;
        double y_axis_end = y_end - axis_margin;
        double x_axis_start = x_start + axis_margin;
        double x_axis_end = x_end - axis_margin;

        // 画背景
        painter.fillRect(rect(), Qt::white);

        // 画坐标轴
        // 原点坐标其实是 (width/2, height/2)
        painter.setPen(Qt::black);
        painter.drawLine(x_start, height / 2, x_end, height / 2); // x 轴
        painter.drawLine(width / 2, y_start, width / 2, y_end); // y 轴

        // **X 轴刻度**
        int num_x_ticks = 10;
        double x_step_val = (x_max - x_min) / num_x_ticks;

        int x_step = (x_axis_end - x_axis_start) / num_x_ticks;
        for (int i = 0; i <= num_x_ticks; ++i) {
            int x = x_axis_start + i * x_step;
            double value = x_min + i * x_step_val;
            painter.drawLine(x, height / 2, x, height / 2 + 5);
            painter.drawText(x - 10, height / 2 + 20, QString::number(value));
        }

        // **Y 轴刻度**
        int num_y_ticks = 6;

        double y_step_val = (y_max - y_min) / num_y_ticks;
        int y_step = (y_axis_end - y_axis_start) / num_y_ticks;
        for (int i = 0; i <= num_y_ticks; ++i) {
            int y = y_axis_end - i * y_step;
            double value = y_min + i * y_step_val;
            if (i == 3)
                continue;
            painter.drawLine(width / 2 - 5, y, width / 2, y);
            painter.drawText(width / 2 - 25, y + 5, QString::number(value));
        }

        // **坐标变换函数**
        auto mapX = [&](double x) {
            return x_axis_start + ((x - x_min) / (x_max - x_min)) * (x_axis_end - x_axis_start);
        };
        auto mapY = [&](double y) { return y_end - ((y - y_min) / (y_max - y_min)) * (y_end - y_start); };

        // **绘制散点**
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::blue);
        for (const auto &point: points) {
            painter.drawEllipse(QPointF(mapX(point.x()), mapY(point.y())), 5, 5);
        }

        // ** 绘制函数**
        painter.setPen(Qt::red);
        int num_points = 1000;
        double step = (x_max - x_min) / num_points;
        for (int i = 0; i <= num_points; ++i) {
            double x1 = x_min + i * step;
            double y1 = sin(x1);
            double x2 = x_min + (i + 1) * step;
            double y2 = sin(x2);
            painter.drawLine(mapX(x1), mapY(y1), mapX(x2), mapY(y2));
        }
    }

public:
    ScatterPlot(QWidget *parent = nullptr) : QWidget(parent) {
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ScatterPlot window;
    window.resize(600, 400);
    window.setWindowTitle("QPainter Scatter Plot (Custom Range)");
    window.show();
    return app.exec();
}

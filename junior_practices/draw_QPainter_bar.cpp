//
// Created by Zhen Chen on 2025/3/1.
//

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <vector>

class BarChartWidget : public QWidget {
    QPushButton *saveButton;

public:
    BarChartWidget() {
        saveButton = new QPushButton("保存图片", this);
        saveButton->setGeometry(5, 5, 80, 30);
        connect(saveButton, &QPushButton::clicked, this, &BarChartWidget::saveImage);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        std::vector<int> values = {30, 80, 50, 100, 60};
        std::vector<QString> labels = {"A", "B", "C", "D", "E"};

        int margin = 50;
        int barWidth = (width() - 2 * margin) / values.size();
        int maxBarHeight = height() - 100;

        painter.setPen(Qt::black);
        painter.drawLine(margin, height() - margin, width() - margin, height() - margin);
        painter.drawLine(margin, height() - margin, margin, margin);

        for (size_t i = 0; i < values.size(); ++i) {
            int barHeight = (values[i] * maxBarHeight) / 100;
            int x = margin + i * barWidth;
            int y = height() - margin - barHeight;

            painter.setBrush(QColor(100, 149, 237));
            painter.drawRect(x + 5, y, barWidth - 10, barHeight);
            painter.drawText(x + barWidth / 4, y - 5, QString::number(values[i]));
            painter.drawText(x + barWidth / 4, height() - margin + 20, labels[i]);
        }
    }

    void saveImage() {
        QPixmap pixmap(this->size());

        this->render(&pixmap);

        pixmap.save("/Users/zhenchen/CLionProjects/CppClion/barchart.png");
//        pixmap.save("/Users/zhenchen/CLionProjects/CppClion/barchart.png", "PNG")
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    BarChartWidget window;
    window.resize(500, 400);
    window.setWindowTitle("QPainter 柱状图");
    window.show();
    return app.exec();
}

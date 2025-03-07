/*
 * Created by Zhen Chen on 2025/3/6.
 * Email: chen.zhen5526@gmail.com
 * Description: 必须在 qt 项目里才能用这个库
 *
 *
 */
#include <QApplication>
#include <QMainWindow>
#include <QVector>
#include <qcustomplot.h>  // 需要 QCustomPlot 头文件

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//
//     // 创建主窗口
//     QMainWindow window;
//     window.resize(600, 400);
//
//     // 创建 QCustomPlot 组件
//     QCustomPlot *customPlot = new QCustomPlot(&window);
//     window.setCentralWidget(customPlot);
//
//     // 🔹 生成 sin(x) 数据
//     QVector<double> x(1001), y(1001);
//     for (int i = 0; i < 1001; ++i) {
//         x[i] = -10 + i * 0.02; // x 从 -10 到 10
//         y[i] = std::sin(x[i]); // y = sin(x)
//     }
//
//     // 🔹 添加图表
//     customPlot->addGraph();
//     customPlot->graph(0)->setData(x, y);
//     customPlot->xAxis->setLabel("X Axis");
//     customPlot->yAxis->setLabel("Y Axis");
//     customPlot->xAxis->setRange(-10, 10);
//     customPlot->yAxis->setRange(-1, 1);
//     customPlot->replot();
//
//     // 显示窗口
//     window.show();
//     return app.exec();
// }

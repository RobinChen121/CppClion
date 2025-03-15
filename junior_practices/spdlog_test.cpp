/*
 * Created by Zhen Chen on 2025/3/11.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */
#include <iostream>

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main() {
    // 创建一个文件日志记录器
    const auto logger = spdlog::basic_logger_mt("file_logger", "app.log");

    // 写入日志
    logger->info("程序启动");
    logger->warn("警告：内存不足");
    logger->error("错误：文件未找到");

    std::cout << "日志已生成，请查看 app.log 文件。" << std::endl;

    // 创建一个控制台日志器
    const auto console = spdlog::stdout_color_mt("console");

    // 设置日志级别（可选）
    console->set_level(spdlog::level::debug);

    // 输出各种级别的日志
    console->trace("这是 trace 级别日志");
    console->debug("这是 debug 级别日志");
    console->info("这是 info 级别日志");
    console->warn("这是 warn 级别日志");
    console->error("这是 error 级别日志");
    console->critical("这是 critical 级别日志");
    return 0;
}

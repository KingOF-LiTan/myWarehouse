#define _CRT_SECURE_NO_WARNINGS 1
#include "Log.h"
    void Logger::log(const std::string& message) {
        std::ofstream logFile("log.txt", std::ios::app);//追加模式打开文件，末尾添加
        if (logFile.is_open()) {
            time_t now = time(0);
            tm* timeinfo = localtime(&now);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S] ", timeinfo);
            logFile << buffer << message << std::endl;
            logFile.close();
        }
    }

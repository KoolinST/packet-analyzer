#include "Logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

Logger::Logger() : running(true){
    workerThread = std::thread(&Logger::processLogs, this);
}

Logger::~Logger(){
    running = false;
    cv.notify_all();
    if (workerThread.joinable())
        workerThread.join();

    std::lock_guard<std::mutex> lock(logMutex);
    while(!logQueue.empty()){
        if(logFile)
            logFile << logQueue.front() << std::endl;
        logQueue.pop();
    }
    if(logFile) logFile.close();
}

Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const std::string& filename){
    std::lock_guard<std::mutex> lock(logMutex);
    logFile.open(filename, std::ios::out | std::ios::app);
    if(!logFile){
        std::cerr << "Failed to open log file!" << std::endl;
    }
}

void Logger::log(const std::string& message){
    std::lock_guard<std::mutex> lock(logMutex);
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm local_tm;
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&local_tm, &now_c);
#else
        localtime_r(&now_c, &local_tm);
#endif
    std::ostringstream oss;
    oss << "[" << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S")
        << "." << std::setfill('0') << std::setw(3) << now_ms.count() << "] ";
    std::string fullMessage = oss.str() + message;
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        logQueue.push(fullMessage);
    }
    cv.notify_all();
}

void Logger::processLogs() {
    while (running) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [this] { return !logQueue.empty() || !running; });

        while (!logQueue.empty()) {
            std::string logEntry = std::move(logQueue.front());
            logQueue.pop();
            lock.unlock();
            {
                std::lock_guard<std::mutex> fileLock(logMutex);
                if (logFile) {
                    logFile << logEntry << std::endl;
                }
            }
            lock.lock();
        }
    }
}
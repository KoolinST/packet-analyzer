#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>
#include <thread>

class Logger{
    public:
        static Logger& getInstance();
        void log(const std::string& message);
        void setLogFile(const std::string& filename);
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
    private:
        std::ofstream logFile;
        std::mutex logMutex;
        std::queue<std::string> logQueue;
        std::mutex queueMutex;
        std::condition_variable cv;
        std::thread workerThread;
        std::atomic<bool> running;
        Logger();
        ~Logger();

        void processLogs();
};

#endif
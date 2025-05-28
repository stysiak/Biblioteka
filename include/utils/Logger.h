#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <ctime>
#include <sstream>
#include <iomanip>

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static Logger& getInstance();
    void log(Level level, const std::string& message);
    void setLogFile(const std::string& path);

    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string getCurrentTimestamp() const;
    std::string levelToString(Level level) const;

    std::ofstream logFile;
    std::mutex mtx;
    static constexpr const char* DEFAULT_LOG_PATH = "../../logs/library.log";
};
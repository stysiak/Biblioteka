#include "../../include/utils/Logger.h"
#include <iostream>

using namespace std;

Logger::Logger() {
    setLogFile(DEFAULT_LOG_PATH);
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const string& path) {
    lock_guard<mutex> lock(mtx);
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(path, ios::app);
    if (!logFile.is_open()) {
        cerr << "Nie można otworzyć pliku logów: " << path << endl;
    }
}

string Logger::getCurrentTimestamp() const {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

string Logger::levelToString(Level level) const {
    switch (level) {
        case Level::DEBUG:   return "DEBUG";
        case Level::INFO:    return "INFO";
        case Level::WARNING: return "WARNING";
        case Level::ERROR:   return "ERROR";
        default:            return "UNKNOWN";
    }
}

void Logger::log(Level level, const string& message) {
    lock_guard<mutex> lock(mtx);
    string timestamp = getCurrentTimestamp();
    string levelStr = levelToString(level);

    string logMessage =
        "[" + timestamp + "] [" + levelStr + "] " + message + "\n";

    if (logFile.is_open()) {
        logFile << logMessage;
        logFile.flush();
    }

    cout << logMessage;
}

void Logger::debug(const string& message) {
    getInstance().log(Level::DEBUG, message);
}

void Logger::info(const string& message) {
    getInstance().log(Level::INFO, message);
}

void Logger::warning(const string& message) {
    getInstance().log(Level::WARNING, message);
}

void Logger::error(const string& message) {
    getInstance().log(Level::ERROR, message);
}
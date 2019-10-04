//
// Created by emre on 2019-02-28.
//

#ifndef THESIS_PROJECT_LOGGER_H
#define THESIS_PROJECT_LOGGER_H


#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <ostream>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

using namespace logging::trivial;
using std::string;
class Logger {

public:
    static Logger* GetInstance();
    static src::severity_logger<severity_level>* GetLoggerInstance();
    static const char* to_string(severity_level lvl);
    static const char* get_timestamp();
    void setFilename(char *filename) {
        Logger::filename = filename;
    }

    void setFormat(char *format) {
        Logger::format = format;
    }

    void setAutoflush(bool autoflush) {
        Logger::autoflush = autoflush;
    }
    
    src::severity_logger<severity_level> getLogger()
    {
        return lg;
    }

    void logInfo(std::string message);
    void logDebug(std::string message);
    void logWarn(std::string message);
    void logError(std::string message);
    void logFatal(std::string message);
    template <class T>
    void appendLog(const T &obj, severity_level l)
    {
        BOOST_LOG_SEV(lg, l) << obj;
    }
    
#define LOG(lvl) BOOST_LOG_SEV(*(Logger::GetLoggerInstance()), lvl)
//#define LOG(lvl) (std::cout << "[" << Logger::get_timestamp() << "]" << to_string(severity_level lvl))

private:
    Logger();
    ~Logger() = default;
    void init();

    string filename;
    string format;
    bool autoflush;
    src::severity_logger<severity_level> lg;
    std::stringstream logStream;
};


#endif //THESIS_PROJECT_LOGGER_H

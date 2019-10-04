//
// Created by emre on 2019-02-28.
//

#include "Logger.h"
#include <boost/format.hpp>

Logger *Logger::GetInstance() {
    static Logger log;
    
    return &log;
}

src::severity_logger<severity_level>* Logger::GetLoggerInstance()
{
    return &(GetInstance()->lg);
}

const char* Logger::to_string(severity_level lvl)
{
    switch (lvl) {
        case debug:
            return "debug";
        case fatal:
            return "fatal";
        case error:
            return "error";
        case info:
            return "info";
        case warning:
            return "warning";
        default:
            return "";
    }
}

const char* Logger::get_timestamp()
{
    time_t rawtime;
    struct tm * timeinfo;
    char *buffer = new char[80];
    
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    
    strftime (buffer,80,"%F %T",timeinfo);
    return buffer;
}


Logger::Logger() {
    filename = "sample_%N.log";
    format = "[%TimeStamp%]: <%Severity%> %Message%";
    autoflush = true;
    
    init();
}

void Logger::init() {
    logging::register_simple_formatter_factory<severity_level, char>("Severity");
    logging::add_file_log
    (
     keywords::file_name = filename.c_str(),
     keywords::format = format.c_str(),
     keywords::auto_flush = autoflush
     );
    boost::log::add_common_attributes();
    
    logging::core::get()->set_filter
    (
     logging::trivial::severity >= logging::trivial::info
     );
}

void Logger::logDebug(std::string message) {
    
    BOOST_LOG_SEV(lg, debug) << message;
}

void Logger::logFatal(std::string message) {
    
    BOOST_LOG_SEV(lg, fatal) << message;
}

void Logger::logError(std::string message) {
    
    BOOST_LOG_SEV(lg, error) << message;
}

void Logger::logInfo(std::string message) {
    
    BOOST_LOG_SEV(lg, info) << message;
}

void Logger::logWarn(std::string message) {
    
    BOOST_LOG_SEV(lg, warning) << message;
}

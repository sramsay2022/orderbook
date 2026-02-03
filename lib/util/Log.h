#ifndef EB25FA42_CDDD_47F9_B66D_C401A227302A
#define EB25FA42_CDDD_47F9_B66D_C401A227302A

#include <ctime>
#include <fstream>
#include <iostream>
#include <source_location>
#include <string>
#include <string_view>

class Log
{
    enum LEVEL
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };
    
    void log_info(const std::string_view&    msg,
                  const std::source_location loc = std::source_location::current())
    {
        std::cerr << "[INFO] " << loc.file_name() << ":" << loc.line() << " " << msg << "\n";
    }
};

#define LOG_INFO(msg)    Log::log_info((msg))
#define LOG_DEBUG(msg)   Log::log_info((msg))
#define LOG_WARNING(msg) Log::log_info((msg))
#define LOG_ERROR(msg)   Log::log_info((msg))

#endif /* EB25FA42_CDDD_47F9_B66D_C401A227302A */

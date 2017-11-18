/******************************************
* Logger Template, from Dr. Dobb's, 
* -- modified by Nick G. 
******************************************/

#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <string>
#include <sys/time.h>
#include <stdio.h>

inline std::string NowTime();

enum LogLevel {ERROR, WARNING, INFO, DEBUG };

template <typename T>
class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream& Get(LogLevel level = INFO);
public:
    static LogLevel& ReportingLevel();
    static std::string ToString(LogLevel level);
    static LogLevel FromString(const std::string& level);
protected:
    std::ostringstream os;
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

template <typename T>
Log<T>::Log() {
}

template <typename T>
std::ostringstream& Log<T>::Get(LogLevel level) {
    os << "[" << ToString(level);
    os << "] [" << NowTime() << "]: ";
    os << std::string(level > DEBUG ? level - DEBUG : 0, '\t');
    return os;
}

template <typename T>
Log<T>::~Log() {
    os << std::endl;
    fprintf(stderr, "%s", os.str().c_str());
    fflush(stderr);
}

template <typename T>
LogLevel& Log<T>::ReportingLevel() {
    static LogLevel reportingLevel = DEBUG;
    return reportingLevel;
}

template <typename T>
std::string Log<T>::ToString(LogLevel level) {
	static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
    return buffer[level];
}

template <typename T>
LogLevel Log<T>::FromString(const std::string& level) {
    if (level == "DEBUG")
        return DEBUG;
    if (level == "INFO")
        return INFO;
    if (level == "WARNING")
        return WARNING;
    if (level == "ERROR")
        return ERROR;
    Log<T>().Get(WARNING) << "Unknown logging level '" << level << "'. Using INFO level as default.";
    return INFO;
}

class Output_To_FILE
{
public:
    static FILE*& Stream();
    static void Output(const std::string& msg);
};

inline FILE*& Output_To_FILE::Stream()
{
    static FILE* pStream = stderr;
    return pStream;
}

inline void Output_To_FILE::Output(const std::string& msg)
{   
    FILE* pStream = Stream();
    if (!pStream)
        return;
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}

#define FILELOG_DECLSPEC
class FILELOG_DECLSPEC pLog : public Log<Output_To_FILE> {};

#ifndef LOG_MAX_LEVEL
#define LOG_MAX_LEVEL DEBUG
#endif

#define LOG(level) \
    if (level > LOG_MAX_LEVEL) ;\
    else if (level > pLog::ReportingLevel()) ; \
    else pLog().Get(level)

inline std::string NowTime() {
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000); 
    return result;
}


#endif //__LOG_H__
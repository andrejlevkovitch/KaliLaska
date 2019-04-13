// logger.hpp

#pragma once

#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

// all log info
#define LOGFILE_FULL "KL_full.log"
// info about warnings, errors and unexpected behaviour
#define LOGFILE_IMPORTANT "KL_important.log"

inline static boost::log::sources::severity_logger<
    boost::log::trivial::severity_level>
    severityLogger;

BOOST_LOG_ATTRIBUTE_KEYWORD(logger_value_file, "File", std::string_view)
BOOST_LOG_ATTRIBUTE_KEYWORD(logger_value_line, "Line", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(logger_value_function, "Function", std::string_view)

// severity logger
#define LOGGER(severity) BOOST_LOG_SEV(severityLogger, severity)

// and logger macroses

// for trace only
#define LOG_TRACE                                                              \
  LOGGER(boost::log::trivial::trace)                                           \
      << boost::log::add_value(logger_value_file, __FILE__)                    \
      << boost::log::add_value(logger_value_line, __LINE__)                    \
      << boost::log::add_value(logger_value_function, __FUNCTION__)

// trace and some needed debug info
#define LOG_DEBUG                                                              \
  LOGGER(boost::log::trivial::debug)                                           \
      << boost::log::add_value(logger_value_file, __FILE__)                    \
      << boost::log::add_value(logger_value_line, __LINE__)                    \
      << boost::log::add_value(logger_value_function, __FUNCTION__)

// some information without trace
#define LOG_INFO LOGGER(boost::log::trivial::info)

// just warning
#define LOG_WARNING                                                            \
  LOGGER(boost::log::trivial::warning)                                         \
      << boost::log::add_value(logger_value_file, __FILE__)                    \
      << boost::log::add_value(logger_value_line, __LINE__)                    \
      << boost::log::add_value(logger_value_function, __FUNCTION__)

// error, which we can handle
#define LOG_ERROR                                                              \
  LOGGER(boost::log::trivial::error)                                           \
      << boost::log::add_value(logger_value_file, __FILE__)                    \
      << boost::log::add_value(logger_value_line, __LINE__)                    \
      << boost::log::add_value(logger_value_function, __FUNCTION__)

// error, which we can not handle
#define LOG_FATAL                                                              \
  LOGGER(boost::log::trivial::fatal)                                           \
      << boost::log::add_value(logger_value_file, __FILE__)                    \
      << boost::log::add_value(logger_value_line, __LINE__)                    \
      << boost::log::add_value(logger_value_function, __FUNCTION__)

// exception logging
#define LOG_THROW(exception_type, info)                                        \
  LOG_ERROR << info;                                                           \
  throw exception_type{info};

void initLogger();

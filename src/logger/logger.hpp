// logger.hpp

#pragma once

#include "kalilaska_export.h"
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/record_ordering.hpp>

class KALILASKA_EXPORT UniqueLogger final {
  using TextFile = boost::log::sinks::text_file_backend;
  using TextSink = boost::log::sinks::asynchronous_sink<
      TextFile,
      boost::log::sinks::unbounded_ordering_queue<
          boost::log::attribute_value_ordering<unsigned int,
                                               std::less<unsigned int>>>>;
  using SinkLocker = boost::log::v2_mt_posix::aux::locking_ptr<
      boost::log::v2_mt_posix::sinks::text_file_backend,
      boost::recursive_mutex>;

public:
  UniqueLogger();
  ~UniqueLogger();

  std::pair<SinkLocker, SinkLocker> lock();

  UniqueLogger(const UniqueLogger &) = delete;
  UniqueLogger &operator=(const UniqueLogger &) = delete;
  UniqueLogger(UniqueLogger &&)                 = delete;
  UniqueLogger &operator=(UniqueLogger &&) = delete;

private:
  boost::shared_ptr<TextSink> fullSink_;
  boost::shared_ptr<TextSink> importantSink_;
};

// all log info
#define LOGFILE_FULL "log/KL_full_%Y-%m-%d_%H-%M-%S.log"
// info about warnings, errors and unexpected behaviour
#define LOGFILE_IMPORTANT "log/KL_important_%Y-%m-%d_%H-%M-%S.log"

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

// init logger
inline static UniqueLogger logger{};

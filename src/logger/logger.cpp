// logger.cpp

#include "logger.hpp"
#include <boost/core/null_deleter.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <fstream>
#include <ostream>

namespace bl = boost::log;

void initLogger() {
  // clang-format off
  bl::formatter formatter =
                     bl::expressions::stream
                      << std::setw(4) << std::setfill('-')
                      << bl::expressions::attr<unsigned int>("LineID")
                      << std::setfill(' ')
                      << '[' << bl::expressions::format_date_time<bl::attributes::basic_time_traits::time_type>("TimeStamp", "%Y-%m-%d %H:%M:%S:%f") << ']'
                      << '[' << bl::expressions::attr<bl::attributes::current_thread_id::value_type>("ThreadID") << ']'
                      << '<' << bl::trivial::severity << '>' << "\t\t"
                      << std::setw(64) << std::left << bl::expressions::smessage 
                      << std::right
                      << '(' << logger_value_file << ':' << logger_value_line << ' ' << logger_value_function << ')';
  // clang-format on

  using TextSink =
      bl::sinks::asynchronous_sink<bl::sinks::text_ostream_backend>;

  auto backendFull = boost::make_shared<bl::sinks::text_ostream_backend>();
  backendFull->add_stream(boost::make_shared<std::ofstream>(LOGFILE_FULL));
  backendFull->auto_flush(true);

  auto backendImportant = boost::make_shared<bl::sinks::text_ostream_backend>();
  backendImportant->add_stream(
      boost::make_shared<std::ofstream>(LOGFILE_IMPORTANT));
  backendImportant->auto_flush(true);

  auto fullSink = boost::make_shared<TextSink>(backendFull);
  fullSink->set_formatter(formatter);

  auto importantSink = boost::make_shared<TextSink>(backendImportant);
  importantSink->set_formatter(formatter);
  importantSink->set_filter(boost::log::trivial::severity >
                            boost::log::trivial::info);

  bl::core::get()->add_sink(fullSink);
  bl::core::get()->add_sink(importantSink);

  bl::add_common_attributes();
}

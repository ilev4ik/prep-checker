#include "mainwindow.h"
#include <QApplication>

#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

void init_logging()
{
	namespace logging = boost::log;
	namespace keywords = logging::keywords;
	namespace sinks = logging::sinks;
	logging::add_common_attributes();
	logging::add_file_log
	(
		keywords::file_name = "logs/gui_%N.log",
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format = "[%TimeStamp%]: %Message%"
	);
}

int main(int argc, char* argv[])
{
	init_logging();
	BOOST_LOG_TRIVIAL(info) << "Qt components set up";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	BOOST_LOG_TRIVIAL(info) << "Program started...";
	auto res = a.exec();
	BOOST_LOG_TRIVIAL(info) << "Quit from event loop";
    return res;
}

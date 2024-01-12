#include <example/source/log.h>

int main() {
	EXAMPLE_LOG_TRACE("log_test!");
	EXAMPLE_LOG_DEBUG("log_test!");
	EXAMPLE_LOG_INFO("log_test!");
	EXAMPLE_LOG_WARN("log_test!");
	EXAMPLE_LOG_ERROR("log_test!");
	EXAMPLE_LOG_FATAL("log_test!");
	EXAMPLE_LOG_TRACE("log_test_after_set_level!");
	EXAMPLE_LOG_INFO("log_test_after_set_level!");
	framework::util::log::Logger::shutdown();
	return 0;
}


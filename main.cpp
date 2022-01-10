#include "logger.h"
#include <fstream>

int main(int argc, char const *argv[])
{
    /**
     * @brief usages:
     *        Logger << messages << ... << ns_log::endl;
     */
    ns_log::info << "this is a 'info' message. Pi = " << 3.14f << ns_log::endl;
    ns_log::warning << "this is a 'warning' message. E = " << 2.71f << ns_log::endl;
    ns_log::error << "this is a 'error' message." << ns_log::endl;
    ns_log::fatal << "this is a 'fatal' message." << ns_log::endl;

    std::fstream file("../log.log", std::ios::out);
    ns_log::setLoggerOS(file);
    ns_log::info << "this is a 'info' message. Pi = " << 3.14f << ns_log::endl;
    ns_log::warning << "this is a 'warning' message. E = " << 2.71f << ns_log::endl;
    ns_log::error << "this is a 'error' message." << ns_log::endl;
    ns_log::fatal << "this is a 'fatal' message." << ns_log::endl;
    file.close();
    
    return 0;
}

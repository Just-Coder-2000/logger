#include "logger.h"
#include <fstream>

int main(int argc, char const *argv[])
{
/**
     * @brief 
     * apis that you can use:
     * 
     * [0] ns_log::info
     * [1] ns_log::process
     * [2] ns_log::warning
     * [3] ns_log::error
     * [4] ns_log::fatal
     * 
     * [5] ns_log::endl
     * 
     * [6] ns_log::setOstream()
     * [7] ns_log::setPrintTime()
     * 
     * usages : Logger << messages << ... << ns_log::endl;
     */

    // for std::cout
    ns_log::info << "this is a 'info' message. Pi = " << 3.14f << ns_log::endl;
    ns_log::process << "this is a 'process' message." << ns_log::endl;
    ns_log::process << "this is a 'process' message." << ns_log::endl;
    ns_log::warning << "this is a 'warning' message. E = " << 2.71f << ns_log::endl;
    ns_log::error << "this is a 'error' message." << ns_log::endl;
    ns_log::error << "this is a 'error' message." << ns_log::endl;
    ns_log::fatal << "this is a 'fatal' message." << ns_log::endl;

    // for std::ofstream
    std::fstream file("../log.log", std::ios::out);
    ns_log::setOstream(file);
    ns_log::info << "this is a 'info' message. Pi = " << 3.14f << ns_log::endl;
    ns_log::process << "this is a 'process' message." << ns_log::endl;
    ns_log::warning << "this is a 'warning' message. E = " << 2.71f << ns_log::endl;
    ns_log::error << "this is a 'error' message." << ns_log::endl;
    ns_log::fatal << "this is a 'fatal' message." << ns_log::endl;

    file.close();

    return 0;
}

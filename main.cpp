#include "logger.h"

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
    return 0;
}

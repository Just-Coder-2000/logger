#include "logger.h"
#include <fstream>

int main(int argc, char const *argv[])
{
    /**
     * @brief macro
     * @attention ostream without [_BEG | _OUT | _END] will output the symbal and time each time with a endl.
     * @attention ostreams with [_BEG | _OUT _END] can be use at the same time.
     * 
     * [1] INFO INFO_BEG INFO_OUT INFO_END
     * [2] PROCESS PROCESS_BEG PROCESS_OUT PROCESS_END
     * [3] WARNING WARNING_BEG WARNING_OUT WARNING_END
     * [4] ERROR ERROR_BEG ERROR_OUT ERROR_END
     * [5] FATAL FATAL_BEG FATAL_OUT FATAL_END
     * 
     * @attention just output context like [std::cout | std::ostream]
     * [6] PLAINTEXT
     */

    /**
     * @brief log for std::cout
     */
    ns_log::setOstream(std::cout);
    WARNING_BEG("Here, I want to say something:");
    WARNING_OUT("[1] No pains, no gains.");
    WARNING_OUT("[2] A friend in need is a friend indeed.");
    WARNING_OUT("[3] Cpp is the best programing language.");
    WARNING_END("well, I finished.");

    PROCESS("to open the file 'nofile.txt'");
    std::ifstream file("nofile.txt");
    if (!file.is_open())
    {
        ERROR("the file 'nofile.txt' open faild.");
        PLAINTEXT("maybe the file is miss or the filename is wrong.");
    }
    FATAL("this is a fatal message.");
    INFO("this is a info message.");
    std::vector<uint> vec{0, 1, 2, 3};
    INFO("this is a vector: ", vec);

    /**
     * @brief log for std::ofstream
     */
    std::ofstream ofs("../log.log");
    ns_log::setOstream(ofs);
    WARNING_BEG("Here, I want to say something:");
    WARNING_OUT("[1] No pains, no gains.");
    WARNING_OUT("[2] A friend in need is a friend indeed.");
    WARNING_OUT("[3] Cpp is the best programing language.");
    WARNING_END("well, I finished.");

    PROCESS("to open the file 'nofile.txt'");
    if (!file.is_open())
    {
        ERROR("the file 'nofile.txt' open faild.");
        PLAINTEXT("maybe the file is miss or the filename is wrong.");
    }
    FATAL("this is a fatal message.");
    INFO("this is a vector: ", vec);
    return 0;
}

# Simple Logger With Color
>___Author : csl___   
>___E-Mail : 3079625093@qq.com___   

## Override
This is just a simple logger, usage is also simple.
```cpp
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
```

## Usage
```cpp
int main(int argc, char const *argv[])
{
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
    INFO("this is a info message.");
    return 0;
}
```
## Display
<img src="./img/output.png">

the log file is [here](./log.log)
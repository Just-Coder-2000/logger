# Simple Logger With Color
>___Author : csl___   

>___E-Mail : 3079625093@qq.com___   

## Override
This is just a simple logger, usage is also simple.


|message type|describe|
|---|---| 
|info|Information; Message; real-time info Of information; Of messages; Informative;|
|process|The process of achieving a goal; The development of things, especially the steps of natural change;|
|warning|about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered|
|error|Error; Errors; Fallacy;|
|fatal|Fatal; Catastrophic; Destructive; Cause failure|

|main method|
|---|
|void setCurOS(std::ostream &os) set the output stream|


## Usage
```cpp
void log()
{
    INFO("this", ' ', "is", ' ', "a", ' ', "vector<int>: ", std::vector<int>{1, 2, 3, 4, 5});
    PROCESS("we all konw that PI equals to ", M_PI);
    WARNING("here is a 'Info' type struct object: ", Info(12, 13.4f));
    ERROR("the ofstream is open? (", true, ")");
    FATAL("hello, world. ", "My E-Mail is ", "3079625093@qq.com.");
}

int main(int argc, char const *argv[])
{
    /**
     * @brief std::cout
     */
    ::log();

    /**
     * @brief std::ofstream
     */
    std::ofstream ofs("../log.log");
    ns_log::setCurOS(ofs);
    ::log();
    ofs.close();
    return 0;
}
```

the log file is [here](./log.log)
```log
[ info  ] [13:58:28] this is a vector<int>: [1, 2, 3, 4, 5]
[process] [13:58:28] we all konw that PI equals to 3.14159
[warning] [13:58:28] here is a 'Info' type struct object: {'id': 12, 'dur': 13.4}
[ error ] [13:58:28] the ofstream is open? (1)
[ fatal ] [13:58:28] hello, world. My E-Mail is 3079625093@qq.com.
```
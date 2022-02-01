# Simple Logger With Color
>___Author : csl___   

>___E-Mail : 3079625093@qq.com___   

## Override
This is just a simple logger, usage is also simple.
```ABAP                                   
_|                                                          
_|          _|_|      _|_|_|    _|_|_|    _|_|    _|  _|_|  
_|        _|    _|  _|    _|  _|    _|  _|_|_|_|  _|_|      
_|        _|    _|  _|    _|  _|    _|  _|        _|        
_|_|_|_|    _|_|      _|_|_|    _|_|_|    _|_|_|  _|        
                          _|        _|                      
                      _|_|      _|_|                       
```

<center>

log message macroes

|message type|describe|
|---|---| 
|info|Information; Message; real-time info Of information; Of messages; Informative;|
|process|The process of achieving a goal; The development of things, especially the steps of natural change;|
|warning|about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered|
|error|Error; Errors; Fallacy;|
|fatal|Fatal; Catastrophic; Destructive; Cause failure|

</center>

<center>

setting methods

|main method|describe|
|---|---|
|void setCurOS(std::ostream &)|Set the output stream|
|static void setSplitor(const std::string &sp)|Set the splitor for container output format|
|static void setFirSedName(const std::string &firstName, const std::string &secondName)|Set the firName and sedName for std::pair|

</center>

<center>

format macroes for STL containers

|describe|format macroes|
|---|---|
|the map relatived containers|FORMAT_MAP FORMAT_MULTIMAP FORMAT_UNORDERED_MAP FORMAT_UNORDERED_MULTIMAP|
|the set relatived containers|FORMAT_SET FORMAT_UNORDERED_SET FORMAT_MULTISET FORMAT_UNORDERED_MULTISET|
|the sequence containers|FORMAT_VECTOR FORMAT_LIST FORMAT_DEQUE FORMAT_ARRAY|
|the stack and queue|FORMAT_STACK FORMAT_QUEUE|

</center>

## Usage
```cpp
#define FORMAT_ARRAY
#define FORMAT_LIST
#define FORMAT_VECTOR

#include "logger.h"

void log()
{
    INFO("this is a list<int>: ", std::list<int>{1, 2, 3, 4, 5});
    TEXT("this is a text message: ", "hello, ", "world.");
    INFO("this is a array<int, 3>: ", std::array<int, 3>{1, 4, 5});
    INFO("this is a empty vector<double>: ", std::vector<double>{});
    TEXT();
    PROCESS("we all konw that PI equals to ", M_PI);
    INFO();
    WARNING("here is a 'Info' type struct object: ", Info(12, 13.4f));
    ERROR("the ofstream is open? (", true, ")");
    FATAL("hello, world. ", "My E-Mail is ", "[3079625093@qq.com].");
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
[ info  ] [9:46:28] this is a list<int>: [1, 2, 3, 4, 5]
this is a text message: hello, world.
[ info  ] [9:46:28] this is a array<int, 3>: [1, 4, 5]
[ info  ] [9:46:28] this is a empty vector<double>: [(empty)]

[process] [9:46:28] we all konw that PI equals to 3.14159
[ info  ] [9:46:28]
[warning] [9:46:28] here is a 'Info' type struct object: {'id': 12, 'dur': 13.4}
[ error ] [9:46:28] the ofstream is open? (1)
[ fatal ] [9:46:28] hello, world. My E-Mail is [3079625093@qq.com].
```
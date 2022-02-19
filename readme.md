# Simple Logger
>___Author : csl___   

>___E-Mail : 3079625093@qq.com___   

[TOC]

## 1. Override

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

log message methods

|message type|describe|
|---|---| 
|info|Information; Message; real-time info Of information; Of messages; Informative;|
|process|The process of achieving a goal; The development of things, especially the steps of natural change;|
|warning|about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered|
|error|Error; Errors; Fallacy;|
|fatal|Fatal; Catastrophic; Destructive; Cause failure|

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

## 2. Usage
```cpp
void cos() {
  std::unordered_map<std::string, std::string> m;
  m.insert({"cpp", "std11"});
  m.insert({"python", "3.8"});
  info("this is a 'info' message");
  process("we all know that 'pi' equals to ", M_PI);
  warning("It's time to eat!");
  error("the file hasn't been closed! (", false, ")");
  fatal("the vector elems are: ", std::vector<int>{1, 5, 6, 2, 4, 78});
  info("the standard of the langs are: ", m);
}

void fos() {
  std::unordered_map<std::string, std::string> m;
  m.insert({"cpp", "std11"});
  m.insert({"python", "3.8"});
  FLogger flogger("../log.log");
  flogger.info("this is a 'info' message");
  flogger.process("we all know that 'pi' equals to ", M_PI);
  flogger.warning("It's time to eat!");
  flogger.error("the file hasn't been closed! (", false, ")");
  flogger.fatal("the vector elems are: ", std::vector<int>{1, 5, 6, 2, 4, 78});
  flogger.info("the standard of the lang is: ", m);
}
```

the log file is [here](./log.log)
```log
[  info   ]-[ 1645249195.619 ] this is a 'info' message
[ process ]-[ 1645249195.619 ] we all know that 'pi' equals to 3.14159
[ warning ]-[ 1645249195.619 ] It's time to eat!
[  error  ]-[ 1645249195.619 ] the file hasn't been closed! (0)
[  fatal  ]-[ 1645249195.619 ] the vector elems are: [1, 5, 6, 2, 4, 78]
[  info   ]-[ 1645249195.619 ] the standard of the lang is: [{'python': 3.8}, {'cpp': std11}]
```
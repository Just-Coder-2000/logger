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

## 2. Usage
```cpp

void cos() {
  Info("this is a 'info' message");
  Process("we all know that 'pi' equals to ", M_PI);
  Warning("It's time to eat!");
  Error("the file hasn't been closed! (", false, ")");
  Fatal("the vector elems are: ", std::vector<int>{1, 5, 6, 2, 4, 78});
}

void fos() {
  ns_log::FLogger flogger("../log.log");
  flogger.info("this is a 'info' message");
  flogger.process("we all know that 'pi' equals to ", M_PI);
  flogger.warning("It's time to eat!");
  flogger.error("the file hasn't been closed! (", false, ")");
  flogger.fatal("the vector elems are: ", std::vector<int>{1, 5, 6, 2, 4, 78});
}
```

the log file is [here](./log.log)
```log
[  info   ]-[ 1645108700.679 ] this is a 'info' message
[ process ]-[ 1645108700.679 ] we all know that 'pi' equals to 3.14159
[ warning ]-[ 1645108700.679 ] It's time to eat!
[  error  ]-[ 1645108700.679 ] the file hasn't been closed! (0)
[  error  ]-[ 1645108700.679 ] the vector elems are: [1, 5, 6, 2, 4, 78]
```
#define FORMAT_VECTOR
#define FORMAT_UNORDERED_MAP
#include "logger.h"

#include <cmath>

using namespace ns_log;

void stdcout() {
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
  FileLogger flogger("../log.log");
  flogger.info("this is a 'info' message");
  flogger.process("we all know that 'pi' equals to ", M_PI);
  flogger.warning("It's time to eat!");
  flogger.error("the file hasn't been closed! (", false, ")");
  flogger.fatal("the vector elems are: ", std::vector<int>{1, 5, 6, 2, 4, 78});
  flogger.info("the standard of the lang is: ", m);
}

int main(int argc, char const *argv[]) {
  /**
   * @brief std::cout
   */
  ::stdcout();

  /**
   * @brief std::ofstream
   */
  ::fos();
  return 0;
}
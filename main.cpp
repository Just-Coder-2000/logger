#define FORMAT_VECTOR
#include "logger.h"
#include <cmath>
#include <vector>

void cos() {
  INFO("this is a 'info' message");
  PROCESS("we all know that 'pi' equals to ", M_PI);
  WARNING("It's time to eat!");
  ERROR("the file hasn't been closed! (", false, ")");
  FATAL("the vector elems are: ", std::vector<int>{1, 5, 6, 2, 4, 78});
}

void fos() {
  ns_log::FLogger flogger("../log.log");
  flogger.info("this is a 'info' message");
  flogger.process("we all know that 'pi' equals to ", M_PI);
  flogger.warning("It's time to eat!");
  flogger.error("the file hasn't been closed! (", false, ")");
  flogger.fatal("the vector elems are: ", std::vector<int>{1, 5, 6, 2, 4, 78});
}

int main(int argc, char const *argv[]) {
  /**
   * @brief std::cout
   */
  ::cos();

  /**
   * @brief std::ofstream
   */
  ::fos();
  return 0;
}
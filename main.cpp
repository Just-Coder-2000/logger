#define FORMAT_VECTOR
#include "logger.h"
#include <cmath>
#include <vector>

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
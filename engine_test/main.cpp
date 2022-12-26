#include "pch.h"
#include "gtest/gtest.h"

#include "src/engine.h"

// Define a function that returns the order in which the tests should be run
int TestCaseOrder(const ::testing::TestCase& test_case) {
   if (test_case.name() == "OBJECT_TEST") {
      return 1;
   }
   return 0;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  int returnValue = 0;
  /*
  Workaround to run firstly the object test
  */
  ::testing::GTEST_FLAG(filter) = "OBJECT_TEST*";
  returnValue = RUN_ALL_TESTS();

  if (returnValue == 1) {
     return returnValue;
  }
  /*
  Run all test without object
  */

  /*
  Initialize OpenGL context
  */
  Engine::init("engine_test", 650, 650, &argc, argv);

  ::testing::GTEST_FLAG(filter) = "*:-OBJECT_TEST*";
  returnValue = RUN_ALL_TESTS();

  Engine::free();
  return returnValue;
}

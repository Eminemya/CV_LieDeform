/**
 * @file slipp_test_main.cpp
 *
 * The main function for each testing program
 * 
 * @author Dahua Lin
 */


#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv)
{
  std::cout << "BCSLib Testing" << std::endl;
  std::cout << "======================" << std::endl;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(pager LANGUAGES CXX)

ADD_LIBRARY(pager INTERFACE)
SET_TARGET_PROPERTIES(pager PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)
TARGET_INCLUDE_DIRECTORIES(pager INTERFACE header)

ADD_EXECUTABLE(test-pager test/tests.cc)
SET_TARGET_PROPERTIES(test-pager PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-pager pager Catch2)

ENABLE_TESTING()
ADD_TEST(test-pager test-pager)


find_package(Boost 1.62 REQUIRED COMPONENTS unit_test_framework)

set(TEST_RESOURCES TestResource.txt TestResource?.txt TestResourceObj.obj Directory/TestResource.txt)

find_package(PythonInterp 2.7 REQUIRED)

set(PYTHONINTERP_FOUND FALSE)

add_executable(TestUsingCMakeGenerator InlineResourcesTest.cpp)
inline_resources(TestUsingCMakeGenerator ${TEST_RESOURCES})
target_link_libraries(TestUsingCMakeGenerator InlineResources Boost::unit_test_framework)

add_test(TestUsingCMakeGenerator TestUsingCMakeGenerator)

set(PYTHONINTERP_FOUND TRUE)

add_executable(TestUsingPyGenerator InlineResourcesTest.cpp)
inline_resources(TestUsingPyGenerator ${TEST_RESOURCES})
target_link_libraries(TestUsingPyGenerator InlineResources Boost::unit_test_framework)

add_test(TestUsingPyGenerator TestUsingPyGenerator)

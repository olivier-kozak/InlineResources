enable_testing()

find_package(Boost 1.62 REQUIRED COMPONENTS unit_test_framework)

add_executable(InlineResourcesTest InlineResourcesTest.cpp)
inline_resources(InlineResourcesTest TestResource1.txt TestResource2.txt)
target_link_libraries(InlineResourcesTest InlineResources Boost::unit_test_framework)

add_test(InlineResourcesTest InlineResourcesTest)

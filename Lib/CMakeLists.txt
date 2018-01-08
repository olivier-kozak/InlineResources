include_directories(.)

find_package(Boost 1.62 REQUIRED)

add_library(InlineResources InlineResources.cpp InlineResources.h)
target_include_directories(InlineResources PUBLIC ${Boost_INCLUDE_DIRS})
set_target_properties(InlineResources PROPERTIES PUBLIC_HEADER InlineResources.h)

install(TARGETS InlineResources ARCHIVE DESTINATION lib PUBLIC_HEADER DESTINATION include)

add_subdirectory(Test)

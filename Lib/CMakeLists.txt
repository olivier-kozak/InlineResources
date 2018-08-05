include_directories(.)

find_package(Boost 1.62 REQUIRED COMPONENTS filesystem)
find_package(PortableWildcards REQUIRED)

add_library(InlineResources InlineResources.cpp InlineResources.h)
target_include_directories(InlineResources PUBLIC ${Boost_INCLUDE_DIRS} ${PortableWildcards_INCLUDE_DIR})
target_link_libraries(InlineResources Boost::filesystem ${PortableWildcards_LIBRARY})
set_target_properties(InlineResources PROPERTIES PUBLIC_HEADER InlineResources.h)

install(TARGETS InlineResources ARCHIVE DESTINATION lib PUBLIC_HEADER DESTINATION include)

add_subdirectory(Test)

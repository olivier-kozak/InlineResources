# InlineResources #

InlineResources is a small tool that can be used to inline resources in
C++ executables and libraries.

It works in combination with [CMake](https://cmake.org/).

It is licensed under the MIT License.

## Requirements ##

* A C++11 compliant compiler,
* CMake >= 3.9,
* Boost.Test >= 1.62.

## Getting started ##

* First, build and install the package as follows:
    ```
    cmake . && make && sudo make install
    ```

* You can now use it in your own project as follows:

    * CMakeLists.txt
        ```
        find_package(InlineResources REQUIRED)

        add_executable(MyProgram main.cpp ...)

        inline_resources(MyProgram "resource.txt" "otherResource.txt" ...)

        target_include_directories(${yourTarget} PRIVATE ${InlineResources_INCLUDE_DIR})
        target_link_libraries(${yourTarget} ${InlineResources_LIBRARY})
        ```

    * main.cpp
        ```
        #include <InlineResources.h>

        int main() {
            std::vector<char> resource = InlineResources::getResource("resource.txt");
            std::vector<char> otherResource = InlineResources::getResource("otherResource.txt");

            ...

            return 0;
        }
        ```

# InlineResources #

*InlineResources* is a small tool that can be used to inline resources within C++ executables and libraries.

It works in combination with [CMake](https://cmake.org/).

It is licensed under the MIT License.

## Requirements ##

* A C++11 compliant compiler,
* CMake >= 3.9,
* Boost.Filesystem >= 1.62,
* Boost.Test >= 1.62,
* PortableWildcards >= 1.0.0.

## Getting started ##

* First, build and install the package:
    ```
    cmake . && make && sudo make install
    ```

* Then, in your project's `CMakeLists.txt` file:

    * Mark the package as required, plus all the needed extra dependencies:
        ```
        find_package(InlineResources REQUIRED)
        find_package(PortableWildcards REQUIRED)
        find_package(Boost 1.62 REQUIRED COMPONENTS filesystem)
        ```

    * Declare the resources to inline with your target:
        ```
        add_executable(MyProgram main.cpp ...)

        inline_resources(MyProgram resource.txt otherResource.txt ...)
        ```

    * Declare the required include directory and libraries:
        ```
        target_include_directories(MyProgram PRIVATE ${InlineResources_INCLUDE_DIR})
        target_link_libraries(MyProgram ${InlineResources_LIBRARY} ${PortableWildcards_LIBRARY} ${Boost_LIBRARIES})
        ```

* You can now access your resources as follows:
    ```
    #include <InlineResources.h>

    int main() {
        auto resource = InlineResources::getResourceAs<std::string>("resource.txt");
        auto otherResource = InlineResources::getResourceAs<std::string>("otherResource.txt");

        ...

        return 0;
    }
    ```

## Usage ##

### Access resources from memory ###

This is the fastest way to access your resources, as they can be directly streamed from memory with no extra cost:
```
#include <InlineResources.h>

int main() {
    auto resource = InlineResources::getResourceAs<std::string>("resource.txt");
    auto otherResource = InlineResources::getResourceAs<std::string>("otherResource.txt");

    ...

    return 0;
}
```

### Access resources from disk ###

Sometimes, streaming resources directly from memory may not be possible. It can be the case, for example, when using
libraries that simply do not support anything else but disk files.

In that case, you first need to unpack your resources -all or just a subset of them- on disk, then read them with
standard C++, which can be done as follows:
```
#include <fstream>

#include <InlineResources.h>

int main() {
    InlineResources::UnpackedResources unpackedResources("*.txt");
    std::ifstream resource((unpackedResources.path / "resource.txt").string());
    std::ifstream resource((unpackedResources.path / "otherResource.txt").string());

    ...

    return 0;
}
```

Be aware that `UnpackedResources` uses RTTI to clean up written files at the end of the scope, so do not try to access
your resources outside of it.

### Specify a parent directory ###

Declaring and accessing resources that are all being stored within the same subdirectory may be a little bit cumbersome:
```
inline_resources(MyProgram path/to/resources/resource.txt path/to/resources/otherResource.txt ...)
```

Fortunately, this can be simplified by using the parameter *PARENT*:
```
inline_resources(MyProgram resource.txt otherResource.txt ... PARENT path/to/resources)
```

## Troubleshooting ##

### The generation process is way too slow ###

*InlineResources* provides 2 distinct generators:

* One is based on pure CMake,
* One is based on Python.

The later will be used whenever Python 2.7 (or greater) is available on your system. If not, *InlineResources* will fall
back to the pure CMake generator, which works everywhere at the cost of being much slower. For small resources, this
does not really matter, but for bigger resources (e.g. images), it can be so slow that it becomes unusable.

In that case, the solution is to install Python 2.7 (or greater) to take advantage of the faster Python generator.

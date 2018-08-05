#include <InlineResources.h>

#include <fstream>
#include <map>
#include <stdexcept>

#include <PortableWildcards.h>

namespace InlineResources {
    std::map<std::string, std::vector<unsigned char>> &getResourcesMap();
}

namespace {
    boost::filesystem::path unpackResources(const std::string &namePattern) {
        auto unpackedResourcesPath = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();

        boost::filesystem::create_directories(unpackedResourcesPath.string());

        for (auto resource : InlineResources::getResourcesMap()) {
            if (PortableWildcards::matches(resource.first, namePattern)) {
                boost::filesystem::create_directories((unpackedResourcesPath / resource.first).parent_path().string());

                std::ofstream file;

                file.exceptions(std::ios::badbit | std::ios::failbit);
                file.open((unpackedResourcesPath / resource.first).string());

                file.write(reinterpret_cast<const char *>(resource.second.data()), resource.second.size());
            }
        }

        return unpackedResourcesPath;
    }
}

namespace InlineResources {
    std::map<std::string, std::vector<unsigned char>> &getResourcesMap() {
        static std::map<std::string, std::vector<unsigned char>> resources {};

        return resources;
    };

    const std::vector<unsigned char> &getResource(const std::string &name) {
        if (getResourcesMap().count(name) == 1) {
            return getResourcesMap()[name];
        }

        throw std::runtime_error("Failed to get non existing resource \"" + name + "\"");
    }

    UnpackedResources::UnpackedResources(const std::string &namePattern) : path(unpackResources(namePattern)) {}

    UnpackedResources::~UnpackedResources() {
        boost::filesystem::remove_all(path);
    }
}

#include <InlineResources.h>

#include <map>
#include <stdexcept>

namespace InlineResources {
    std::map<std::string, std::vector<unsigned char>> &getResourcesMap() {
        static std::map<std::string, std::vector<unsigned char>> resources;

        return resources;
    };

    const std::vector<unsigned char> &getResource(const std::string &name) {
        if (getResourcesMap().count(name) == 1) {
            return getResourcesMap()[name];
        }

        throw std::runtime_error("Failed to get non existing resource \"" + name + "\"");
    }
}

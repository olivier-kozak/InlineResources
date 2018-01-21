#include <InlineResources.h>

#include <map>
#include <stdexcept>

#include <boost/format.hpp>

namespace InlineResources {
    std::map<std::string, std::vector<char>> &getResourcesMap() {
        static std::map<std::string, std::vector<char>> resources;

        return resources;
    };

    const std::vector<char> &getResource(const std::string &name) {
        if (getResourcesMap().count(name) == 1) {
            return getResourcesMap()[name];
        } else {
            throw std::runtime_error((boost::format("Failed to get non existing resource %1%") % name).str());
        }
    }

    std::string getResourceAsStr(const std::string &name) {
        const std::vector<char> &resource = getResource(name);

        return std::string(resource.begin(), resource.end());
    }

    const char *getResourceAsCStr(const std::string &name) {
        const std::vector<char> &resource = getResource(name);

        return resource.data();
    }
}

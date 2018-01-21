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
        }

        throw std::runtime_error((boost::format("Failed to get non existing resource %1%") % name).str());
    }

    std::map<std::string, std::string> resourcesStrs;

    const std::string &getResourceAsStr(const std::string &name) {
        const std::vector<char> &resource = getResource(name);

        if (resourcesStrs.count(name) == 0) {
            resourcesStrs[name] = std::string(resource.begin(), resource.end());
        }

        return resourcesStrs[name];
    }

    const char *getResourceAsCStr(const std::string &name) {
        return getResourceAsStr(name).c_str();
    }
}

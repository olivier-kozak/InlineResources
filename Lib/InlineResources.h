#ifndef INLINE_RESOURCES_H
#define INLINE_RESOURCES_H

#include <memory>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace InlineResources {
    const std::vector<unsigned char> &getResource(const std::string &name);

    template <typename T> T getResourceAs(const std::string &name) {
        const std::vector<unsigned char> &resource = getResource(name);

        return { resource.begin(), resource.end() };
    }

    class UnpackedResources {
    public:
        explicit UnpackedResources(const std::string &namePattern);
        UnpackedResources(const UnpackedResources &_) = delete;

        ~UnpackedResources();

        const boost::filesystem::path path;
    };
}

#endif //INLINE_RESOURCES_H

#ifndef INLINE_RESOURCES_H
#define INLINE_RESOURCES_H

#include <string>
#include <vector>

namespace InlineResources {
    const std::vector<unsigned char> &getResource(const std::string &name);

    template <typename T> T getResourceAs(const std::string &name) {
        const std::vector<unsigned char> &resource = getResource(name);

        return { resource.begin(), resource.end() };
    }
}

#endif //INLINE_RESOURCES_H

#ifndef INLINE_RESOURCES_H
#define INLINE_RESOURCES_H

#include <string>
#include <vector>

namespace InlineResources {
    const std::vector<char> &getResource(const std::string &name);
}

#endif //INLINE_RESOURCES_H

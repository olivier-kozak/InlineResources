#include <cstring>
#include <stdexcept>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE InlineResources

#include <boost/test/unit_test.hpp>

#include <InlineResources.h>

BOOST_AUTO_TEST_CASE(getTestResource1) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("TestResource1.txt");

    BOOST_TEST(resourceStr == "Here is a test resource.");
}

BOOST_AUTO_TEST_CASE(getTestResource2) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("TestResource2.txt");

    BOOST_TEST(resourceStr == "Here is another test resource.");
}

BOOST_AUTO_TEST_CASE(getNonExistingResource) {
    BOOST_CHECK_THROW(InlineResources::getResource("NonExistingResource.txt"), std::runtime_error);
}

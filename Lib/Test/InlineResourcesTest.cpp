#include <cstring>
#include <stdexcept>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE InlineResources

#include <boost/test/unit_test.hpp>

#include <InlineResources.h>

BOOST_AUTO_TEST_CASE(getTestResource) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("TestResource.txt");

    BOOST_TEST(resourceStr == "Here is a test resource.");
}

BOOST_AUTO_TEST_CASE(getTestResource1) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("TestResource1.txt");

    BOOST_TEST(resourceStr == "Here is a first test resource in a bundle.");
}

BOOST_AUTO_TEST_CASE(getTestResource2) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("TestResource2.txt");

    BOOST_TEST(resourceStr == "Here is a second test resource in a bundle.");
}

BOOST_AUTO_TEST_CASE(getTestResourceObj) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("TestResourceObj.obj");

    BOOST_TEST(resourceStr == "Here is an OBJ test resource.");
}

BOOST_AUTO_TEST_CASE(getTestResourceWithinDirectory) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("Directory/TestResource.txt");

    BOOST_TEST(resourceStr == "Here is a test resource within a directory.");
}

BOOST_AUTO_TEST_CASE(getNonExistingResource) {
    BOOST_CHECK_THROW(InlineResources::getResource("NonExistingResource.txt"), std::runtime_error);
}

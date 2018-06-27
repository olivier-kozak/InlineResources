#include <cstring>
#include <stdexcept>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE InlineResources

#include <boost/test/unit_test.hpp>

#include <InlineResources.h>

BOOST_AUTO_TEST_CASE(getTestResource) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/TestResource.txt");

    BOOST_TEST(resourceStr == "Here is a test resource.");
}

BOOST_AUTO_TEST_CASE(getTestResource1) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/TestResource1.txt");

    BOOST_TEST(resourceStr == "Here is a first test resource in a bundle.");
}

BOOST_AUTO_TEST_CASE(getTestResource2) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/TestResource2.txt");

    BOOST_TEST(resourceStr == "Here is a second test resource in a bundle.");
}

BOOST_AUTO_TEST_CASE(getTestResourceObj) {
    auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/TestResourceObj.obj");

    BOOST_TEST(resourceStr == "Here is a test resource of type OBJ.");
}

BOOST_AUTO_TEST_CASE(getNonExistingResource) {
    BOOST_CHECK_THROW(InlineResources::getResource("Resources/NonExistingResource.txt"), std::runtime_error);
}

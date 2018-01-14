#include <stdexcept>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE InlineResources

#include <boost/test/unit_test.hpp>

#include <InlineResources.h>

BOOST_AUTO_TEST_CASE(getTestResource1) {
    const std::vector<char> &resource = InlineResources::getResource("TestResource1.txt");
    std::string resourceStr(resource.begin(), resource.end());

    BOOST_TEST(resourceStr == "Here is a test resource.");
}

BOOST_AUTO_TEST_CASE(getTestResource2) {
    const std::vector<char> &resource = InlineResources::getResource("TestResource2.txt");
    std::string resourceStr(resource.begin(), resource.end());

    BOOST_TEST(resourceStr == "Here is another test resource.");
}

BOOST_AUTO_TEST_CASE(getNonExistingResource) {
    BOOST_CHECK_THROW(InlineResources::getResource("NonExistingResource.txt"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(getTestResourceAsStr) {
    std::string resourceStr = InlineResources::getResourceAsStr("TestResourceContainingString.txt");

    BOOST_TEST(resourceStr == "Here is a test resource containing a string.");
}

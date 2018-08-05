#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE InlineResources

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <InlineResources.h>

namespace {
    const std::string readFileAsStr(const boost::filesystem::path &path) {
        std::ifstream file(path.string());

        return {std::istreambuf_iterator<std::string::value_type>(file),
                std::istreambuf_iterator<std::string::value_type>()};
    }
}

BOOST_AUTO_TEST_SUITE(getResource)
    BOOST_AUTO_TEST_CASE(getResource) {
        auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/Resource.txt");

        BOOST_TEST(resourceStr == "Here is a resource.");
    }

    BOOST_AUTO_TEST_CASE(getFirstResourceInBundle) {
        auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/Bundle/Resource1.txt");

        BOOST_TEST(resourceStr == "Here is a first resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(getSecondResourceInBundle) {
        auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/Bundle/Resource2.txt");

        BOOST_TEST(resourceStr == "Here is a second resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(getResourceOfTypeObj) {
        auto resourceStr = InlineResources::getResourceAs<std::string>("Resources/ResourceObj.obj");

        BOOST_TEST(resourceStr == "Here is a resource of type OBJ.");
    }

    BOOST_AUTO_TEST_CASE(getNonExistingResource) {
        BOOST_CHECK_THROW(InlineResources::getResource("Resources/NonExistingResource.txt"), std::runtime_error);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unpackResources)
    BOOST_AUTO_TEST_CASE(unpackOneResource) {
        InlineResources::UnpackedResources unpackedResources("Resources/Resource.txt");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resources/Resource.txt"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resources/Resource.txt") == "Here is a resource.");

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource1.txt"));
        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource2.txt"));
    }

    BOOST_AUTO_TEST_CASE(unpackAllResourcesInBundle) {
        InlineResources::UnpackedResources unpackedResources("Resources/Bundle/*");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resources/Resource.txt"));

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource1.txt"));
        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource2.txt"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resources/Bundle/Resource1.txt") ==
                   "Here is a first resource in a bundle.");
        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resources/Bundle/Resource2.txt") ==
                   "Here is a second resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(unpackAllResources) {
        InlineResources::UnpackedResources unpackedResources("Resources/*");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resources/Resource.txt"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resources/Resource.txt") == "Here is a resource.");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource1.txt"));
        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource2.txt"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resources/Bundle/Resource1.txt") ==
                   "Here is a first resource in a bundle.");
        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resources/Bundle/Resource2.txt") ==
                   "Here is a second resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(unpackNonExistingResource) {
        InlineResources::UnpackedResources unpackedResources("Resources/NonExistingResource.txt");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resources/Resource.txt"));

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource1.txt"));
        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resources/Bundle/Resource2.txt"));
    }
BOOST_AUTO_TEST_SUITE_END()

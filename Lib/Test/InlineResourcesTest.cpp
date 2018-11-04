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
    BOOST_AUTO_TEST_CASE(getOneResource) {
        auto resourceStr = InlineResources::getResourceAs<std::string>("Resource.obj");

        BOOST_TEST(resourceStr == "Here is a resource.");
    }

    BOOST_AUTO_TEST_CASE(getFirstResourceInBundle) {
        auto resourceStr = InlineResources::getResourceAs<std::string>("Bundle/Resource1.obj");

        BOOST_TEST(resourceStr == "Here is a first resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(getSecondResourceInBundle) {
        auto resourceStr = InlineResources::getResourceAs<std::string>("Bundle/Resource2.obj");

        BOOST_TEST(resourceStr == "Here is a second resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(getNonExistingResource) {
        BOOST_CHECK_THROW(InlineResources::getResource("NonExistingResource.txt"), std::runtime_error);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unpackResources)
    BOOST_AUTO_TEST_CASE(unpackOneResource) {
        InlineResources::UnpackedResources unpackedResources("Resource.obj");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resource.obj"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resource.obj") == "Here is a resource.");

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Bundle/Resource1.obj"));
        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Bundle/Resource2.obj"));
    }

    BOOST_AUTO_TEST_CASE(unpackAllResourcesInBundle) {
        InlineResources::UnpackedResources unpackedResources("Bundle/*");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resource.obj"));

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Bundle/Resource1.obj"));
        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Bundle/Resource2.obj"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Bundle/Resource1.obj") ==
                   "Here is a first resource in a bundle.");
        BOOST_TEST(readFileAsStr(unpackedResources.path / "Bundle/Resource2.obj") ==
                   "Here is a second resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(unpackAllResources) {
        InlineResources::UnpackedResources unpackedResources("*");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Resource.obj"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Resource.obj") == "Here is a resource.");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Bundle/Resource1.obj"));
        BOOST_TEST(boost::filesystem::exists(unpackedResources.path / "Bundle/Resource2.obj"));

        BOOST_TEST(readFileAsStr(unpackedResources.path / "Bundle/Resource1.obj") ==
                   "Here is a first resource in a bundle.");
        BOOST_TEST(readFileAsStr(unpackedResources.path / "Bundle/Resource2.obj") ==
                   "Here is a second resource in a bundle.");
    }

    BOOST_AUTO_TEST_CASE(unpackNonExistingResource) {
        InlineResources::UnpackedResources unpackedResources("NonExistingResource.txt");

        BOOST_TEST(boost::filesystem::exists(unpackedResources.path));

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Resource.obj"));

        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Bundle/Resource1.obj"));
        BOOST_TEST(!boost::filesystem::exists(unpackedResources.path / "Bundle/Resource2.obj"));
    }
BOOST_AUTO_TEST_SUITE_END()

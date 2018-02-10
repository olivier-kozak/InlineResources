FROM ubuntu:17.10

RUN apt-get update && apt-get install -y build-essential cmake libboost-test-dev python

COPY CMake/ /opt/InlineResources/CMake/
COPY Lib/ /opt/InlineResources/Lib/
COPY CMakeLists.txt /opt/InlineResources/

WORKDIR /opt/InlineResources/

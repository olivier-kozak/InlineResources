FROM ubuntu:18.04

RUN apt-get update && apt-get install -y build-essential cmake libboost-filesystem-dev libboost-test-dev python wget

RUN wget https://github.com/olivier-kozak/PortableWildcards/archive/1.0.0.tar.gz -O /tmp/PortableWildcards-1.0.0.tar.gz &&\
    tar -xzf /tmp/PortableWildcards-1.0.0.tar.gz -C /tmp && cd /tmp/PortableWildcards-1.0.0 &&\
    cmake . && make && make install

COPY CMake/ /opt/InlineResources/CMake/
COPY Lib/ /opt/InlineResources/Lib/
COPY CMakeLists.txt /opt/InlineResources/

WORKDIR /opt/InlineResources/

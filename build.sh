#!/usr/bin/env bash

docker build -t inline-resources . && docker run inline-resources bash -c "cmake . && make && make test"

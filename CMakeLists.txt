cmake_minimum_required(VERSION 3.1)

project(v4l2-wrapper LANGUAGES C CXX)

add_library(target v4l2.cc)


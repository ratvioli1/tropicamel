cmake_minimum_required(VERSION 3.16)
project(tropicamel LANGUAGES CXX)

add_executable(tropicamel src/main.cpp src/Tropicamel.cpp)
target_compile_features(tropicamel PRIVATE cxx_std_17)

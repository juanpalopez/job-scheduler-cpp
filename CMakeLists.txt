cmake_minimum_required(VERSION 3.26)
project(JobScheduler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(JobScheduler
        main.cpp
        include/Job.h
        include/Schedule.h)

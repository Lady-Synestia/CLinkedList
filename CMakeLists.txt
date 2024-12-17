cmake_minimum_required(VERSION 3.30)
project(CLinkedList C)

set(CMAKE_C_STANDARD 11)

add_executable(CLinkedList main.c
        linkedlist.c
        linkedlist.h)

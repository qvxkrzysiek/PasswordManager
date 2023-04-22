cmake_minimum_required(VERSION 3.21)
project(PROJEKT_PJC)

set(CMAKE_CXX_STANDARD 17)

add_executable(PROJEKT_PJC main.cpp FileHandler.cpp FileHandler.h PasswordManager.cpp PasswordManager.h Cryptor.cpp Cryptor.h)

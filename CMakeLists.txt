cmake_minimum_required(VERSION 3.20)
project(TPRO C)

set(CMAKE_C_STANDARD 11)

add_executable(TPRO main.c kruskalLc.h PrimAdja.h PrimLC.h DjisktraLc.h DjisktraAdja.h)

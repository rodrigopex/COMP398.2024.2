# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(es_aula_threads)

list(APPEND SRCS src/main.c src/calc.c)

# zephyr_library_sources_ifdef(CONFIG_GREETINGS src/greetings.c)

zephyr_include_directories(include)

target_sources(app PRIVATE ${SRCS})

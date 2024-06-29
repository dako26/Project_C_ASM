cmake_minimum_required(VERSION 3.28)
project(Project_C_ASM C)

set(CMAKE_C_STANDARD 90)

include_directories(.)

add_executable(Project_C_ASM
        macro.c
        macro.h
        main.c
        main.h
        util.c
        util.h
        firstPass.c
        firstPass.h
        inputValidation.c
        inputValidation.h
        table.c
        table.h
        assembly.c
        assembly.h
        memory.c
        memory.h
)

cmake_minimum_required(VERSION 3.12)
project(MyProject C)

set(CMAKE_C_STANDARD 11)

# Flaguri pentru compilator
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")

# fisierele sursa
set(SRCS crc.c main.c)

# Bibliotecile dinamice
add_library(libcrc SHARED ${SRCS})

# Executabilul principal
add_executable(crc_main main.c)

# Legarea executabilului principal de biblioteca distribuita
target_link_libraries(crc_main PRIVATE libcrc)

# seteaza numele bibliotecii distribuite
set_target_properties(libcrc PROPERTIES OUTPUT_NAME "crc")

# Numele executabilului principal
set_target_properties(crc_main PROPERTIES OUTPUT_NAME "crc_main")

# Directoarele in care vor fi instalate fisierele
install(TARGETS libcrc DESTINATION lib)
install(TARGETS crc_main DESTINATION bin)

# Instalarea fisierelor de tip header 
install(FILES crc.h DESTINATION include)

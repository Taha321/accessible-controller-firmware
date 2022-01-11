if(EXISTS  ${CMAKE_CURRENT_LIST_DIR}/FindArduino.cmake)
    set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(TRIPLE "arm-none-eabi")
set(TOOLCHAIN_ROOT "C:\\Program Files (x86)\\Arduino\\hardware\\tools\\arm")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# Find arduino sdk from cmake module
include(FindArduino)

find_file(TEENSY_BASE hardware/teensy/avr ${ARDUINO_SDK_PATH})
if(NOT EXISTS ${TEENSY_BASE})
    message(FATAL_ERROR "Could not find the teensy SDK under the arduino SDK, make sure teensyduino is properly installed or set $TEENSY_BASE yourself")
endif()

set(TEENSY_LIB_ROOT "${TEENSY_BASE}/libraries")
set(TEENSY_CORES_ROOT "${TEENSY_BASE}/cores")# CACHE PATH "Path to the Teensy 'cores' repository")
set(TEENSY_ROOT "${TEENSY_CORES_ROOT}/teensy4")
set(ARDUINO_LIB_ROOT "${ARDUINO_SDK_PATH}/libraries")# CACHE PATH "Path to the Arduino library directory")

set(TEENSY_MODEL "MK20DX256" CACHE STRING "Model of the Teensy MCU")

file(READ ${ARDUINO_SDK_PATH}/lib/version.txt ARDUINO_VERSION)
string(REGEX REPLACE "-.*" "" ARDUINO_VERSION ${ARDUINO_VERSION})
string(REPLACE "." "" ARDUINO_VERSION ${ARDUINO_VERSION})

file(READ ${TEENSY_BASE}/platform.txt TEENSYDUINO_VERSION)
string(REGEX MATCH "[\n\r]version=([^\n\r]*)" TEENSYDUINO_VERSION ${TEENSYDUINO_VERSION})
string(REGEX MATCH "[0-9].*" TEENSYDUINO_VERSION ${TEENSYDUINO_VERSION})
string(REPLACE "." "" TEENSYDUINO_VERSION ${TEENSYDUINO_VERSION})

set(TEENSY_FREQUENCY "96" CACHE STRING "Frequency of the Teensy MCU (Mhz)")
set_property(CACHE TEENSY_FREQUENCY PROPERTY STRINGS 96 72 48 24 16 8 4 2)

set(TEENSY_USB_MODE "SERIAL" CACHE STRING "What kind of USB device the Teensy should emulate")
set_property(CACHE TEENSY_USB_MODE PROPERTY STRINGS SERIAL HID SERIAL_HID MIDI RAWHID FLIGHTSIM)


if(WIN32)
    set(TOOL_OS_SUFFIX .exe)
else(WIN32)
    set(TOOL_OS_SUFFIX )
endif(WIN32)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_C_COMPILER "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-gcc${TOOL_OS_SUFFIX}" CACHE PATH "gcc" FORCE)
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-g++${TOOL_OS_SUFFIX}" CACHE PATH "g++" FORCE)
set(CMAKE_AR "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-ar${TOOL_OS_SUFFIX}" CACHE PATH "archive" FORCE)
set(CMAKE_LINKER "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-ld${TOOL_OS_SUFFIX}" CACHE PATH "linker" FORCE)
set(CMAKE_NM "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-nm${TOOL_OS_SUFFIX}" CACHE PATH "nm" FORCE)
set(CMAKE_OBJCOPY "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-objcopy${TOOL_OS_SUFFIX}" CACHE PATH "objcopy" FORCE)
set(CMAKE_OBJDUMP "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-objdump${TOOL_OS_SUFFIX}" CACHE PATH "objdump" FORCE)
set(CMAKE_STRIP "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-strip${TOOL_OS_SUFFIX}" CACHE PATH "strip" FORCE)
set(CMAKE_RANLIB "${TOOLCHAIN_ROOT}/bin/${TRIPLE}-ranlib${TOOL_OS_SUFFIX}" CACHE PATH "ranlib" FORCE)

include_directories("${TEENSY_ROOT}")

set(TARGET_FLAGS "-mcpu=cortex-m4 -mthumb")
set(BASE_FLAGS "-Os -Wall -nostdlib -ffunction-sections -fdata-sections ${TARGET_FLAGS}")

set(CMAKE_C_FLAGS "${BASE_FLAGS} -DTIME_T=1421620748" CACHE STRING "c flags") # XXX Generate TIME_T dynamically.
set(CMAKE_CXX_FLAGS "${BASE_FLAGS} -fno-exceptions -fno-rtti -felide-constructors -std=gnu++0x" CACHE STRING "c++ flags")

set(LINKER_FLAGS "-Os -Wl,--gc-sections ${TARGET_FLAGS} -T${TEENSY_ROOT}/mk20dx256.ld" )
set(LINKER_LIBS "-lm" )
set(CMAKE_SHARED_LINKER_FLAGS "${LINKER_FLAGS}" CACHE STRING "linker flags" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS "${LINKER_FLAGS}" CACHE STRING "linker flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS}" CACHE STRING "linker flags" FORCE)

# Do not pass flags like '-ffunction-sections -fdata-sections' to the linker.
# This causes undefined symbol errors when linking.
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> -o <TARGET>  <OBJECTS> <LINK_LIBRARIES> ${LINKER_LIBS}" CACHE STRING "Linker command line" FORCE)

add_definitions("-DARDUINO=${ARDUINO_VERSION}")
add_definitions("-DTEENSYDUINO=${TEENSYDUINO_VERSION}")
add_definitions("-D__${TEENSY_MODEL}__")
add_definitions(-DLAYOUT_US_ENGLISH)
add_definitions(-DUSB_VID=null)
add_definitions(-DUSB_PID=null)
add_definitions(-MMD)

FILE(GLOB_RECURSE TEENSY_C_CORE_FILES "${TEENSY_ROOT}/*.c")
FILE(GLOB_RECURSE TEENSY_CXX_CORE_FILES "${TEENSY_ROOT}/*.cpp")

macro(add_teensy_executable TARGET_NAME)
    # Determine the target flags for this executable.
    set(USB_MODE_DEF)
    if(${TEENSY_USB_MODE} STREQUAL SERIAL)
        set(USB_MODE_DEF USB_SERIAL)
    elseif(${TEENSY_USB_MODE} STREQUAL HID)
        set(USB_MODE_DEF USB_HID)
    elseif(${TEENSY_USB_MODE} STREQUAL SERIAL_HID)
        set(USB_MODE_DEF USB_SERIAL_HID)
    elseif(${TEENSY_USB_MODE} STREQUAL MIDI)
        set(USB_MODE_DEF USB_MIDI)
    elseif(${TEENSY_USB_MODE} STREQUAL RAWHID)
        set(USB_MODE_DEF USB_RAWHID)
    elseif(${TEENSY_USB_MODE} STREQUAL FLIGHTSIM)
        set(USB_MODE_DEF USB_FLIGHTSIM)
    else()
        message(FATAL_ERROR "Invalid USB mode: ${TEENSY_USB_MODE}")
    endif()
    set(TARGET_FLAGS "-D${USB_MODE_DEF} -DF_CPU=${TEENSY_FREQUENCY}000000 ${TEENSY_FLAGS}")
    set(TARGET_C_FLAGS "${TARGET_FLAGS} ${TEENSY_C_FLAGS}")
    set(TARGET_CXX_FLAGS "${TARGET_FLAGS} ${TEENSY_CXX_FLAGS}")

    # Build the Teensy 'core' library.
    # Per-target because of preprocessor definitions.
    add_library(${TARGET_NAME}_TeensyCore
        ${TEENSY_C_CORE_FILES}
        ${TEENSY_CXX_CORE_FILES}
    )
    set_source_files_properties(${TEENSY_C_CORE_FILES} 
        PROPERTIES COMPILE_FLAGS ${TARGET_C_FLAGS})
    set_source_files_properties(${TEENSY_CXX_CORE_FILES}
        PROPERTIES COMPILE_FLAGS ${TARGET_CXX_FLAGS})

    set(FINAL_SOURCES ${TEENSY_LIB_SOURCES})
    foreach(SOURCE ${SOURCES})
        get_filename_component(SOURCE_EXT ${SOURCE} EXT)
        get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
        get_filename_component(SOURCE_PATH ${SOURCE} REALPATH)
        if((${SOURCE_EXT} STREQUAL .ino) OR (${SOURCE_EXT} STREQUAL .pde))
            # Generate a stub C++ file from the Arduino sketch file.
            set(GEN_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_NAME}.cpp")
            set(TEMPLATE_FILE "${SOURCE}.in")
            if(NOT EXISTS "${TEMPLATE_FILE}")
                set(TEMPLATE_FILE "${CMAKE_SOURCE_DIR}/cmake/Arduino.inc.in")
            endif()

            configure_file("${TEMPLATE_FILE}" "${GEN_SOURCE}")
            set(FINAL_SOURCES ${FINAL_SOURCES} ${GEN_SOURCE})
        else()
            set(FINAL_SOURCES ${FINAL_SOURCES} ${SOURCE})
        endif()
    endforeach(SOURCE ${SOURCES})
    
    # Add the Arduino library directory to the include path if found.
    if(EXISTS ${ARDUINO_LIB_ROOT})
        include_directories(${ARDUINO_LIB_ROOT})
    endif(EXISTS ${ARDUINO_LIB_ROOT})
    
    # Build the ELF executable.
    add_executable(${TARGET_NAME} ${FINAL_SOURCES})
    set_source_files_properties(${FINAL_SOURCES}
        PROPERTIES COMPILE_FLAGS ${TARGET_CXX_FLAGS})
    target_link_libraries(${TARGET_NAME} ${TARGET_NAME}_TeensyCore)
    set_target_properties(${TARGET_NAME} PROPERTIES
        OUTPUT_NAME ${TARGET_NAME}
        SUFFIX ".elf"
    )
    set(TARGET_ELF "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.elf")
    
    # Generate the hex firmware files that can be flashed to the MCU.
    set(EEPROM_OPTS -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0)
    set(HEX_OPTS -O ihex -R .eeprom)
    add_custom_command(OUTPUT ${TARGET_ELF}.eep
                       COMMAND ${CMAKE_OBJCOPY} ${EEPROM_OPTS} ${TARGET_ELF} ${TARGET_ELF}.eep
                       DEPENDS ${TARGET_ELF})
    add_custom_command(OUTPUT ${TARGET_ELF}.hex
                       COMMAND ${CMAKE_OBJCOPY} ${HEX_OPTS} ${TARGET_ELF} ${TARGET_ELF}.hex
                       DEPENDS ${TARGET_ELF})
    add_custom_target(${TARGET_NAME}_Firmware ALL
                      DEPENDS ${TARGET_ELF}.eep ${TARGET_ELF}.hex)
    add_dependencies(${TARGET_NAME}_Firmware ${TARGET_NAME})
endmacro(add_teensy_executable) 

macro(import_arduino_library LIB_NAME)
    # Check if we can find the library.

    if(NOT EXISTS ${ARDUINO_LIB_ROOT})
        message(FATAL_ERROR "Could not find the Arduino library directory")
    endif(NOT EXISTS ${ARDUINO_LIB_ROOT})
    if(NOT EXISTS ${TEENSY_LIB_ROOT})
        message(FATAL_ERROR "Could not find the Teensy library directory")
    endif(NOT EXISTS ${TEENSY_LIB_ROOT})

    # Look for library in arduino and teensy root library folders
    set(ARD_LIB_DIR "${ARDUINO_LIB_ROOT}/${LIB_NAME}/src")
    set(TEN_LIB_DIR "${TEENSY_LIB_ROOT}/${LIB_NAME}")
    if(NOT EXISTS "${ARD_LIB_DIR}" AND NOT EXISTS ${TEN_LIB_DIR})
        message(FATAL_ERROR "Could not find the directory for library ${LIB_NAME}")
    endif(NOT EXISTS "${ARD_LIB_DIR}" AND NOT EXISTS ${TEN_LIB_DIR})

    # We prioritize the implementation of the library in the teensy cores
    if(EXISTS "${TEN_LIB_DIR}")
        set(LIB_DIR ${TEN_LIB_DIR})
    else()
        set(LIB_DIR ${ARD_LIB_DIR})
    endif(EXISTS "${TEN_LIB_DIR}")

    # Add it to the include path.
    include_directories("${LIB_DIR}")
    
    # Mark source files to be built along with the sketch code.
    file(GLOB SOURCES_CPP ABSOLUTE "${LIB_DIR}" "${LIB_DIR}/*.cpp")
    foreach(SOURCE_CPP ${SOURCES_CPP})
        set(TEENSY_LIB_SOURCES ${TEENSY_LIB_SOURCES} ${SOURCE_CPP})
    endforeach(SOURCE_CPP ${SOURCES_CPP})
    file(GLOB SOURCES_C ABSOLUTE "${LIB_DIR}" "${LIB_DIR}/*.c")
    foreach(SOURCE_C ${SOURCES_C})
        set(TEENSY_LIB_SOURCES ${TEENSY_LIB_SOURCES} ${SOURCE_C})
    endforeach(SOURCE_C ${SOURCES_C})
endmacro(import_arduino_library)

macro(_add_sketch_internal SKETCH_DIR SKETCH)
    set(SKETCH_SOURCE_INO "${SKETCH_DIR}/${SKETCH}/${SKETCH}.ino")
    set(SKETCH_SOURCE_PDE "${SKETCH_DIR}/${SKETCH}/${SKETCH}.pde")
    get_filename_component(SKETCH_DIR_NAME ${SKETCH_DIR} NAME)
    set(SKETCH_TARGET_NAME ${SKETCH})
    if(NOT ${SKETCH_DIR_NAME} STREQUAL "sketches")
        set(SKETCH_TARGET_NAME "${SKETCH_DIR_NAME}_${SKETCH_TARGET_NAME}")
    endif()
    if(EXISTS ${SKETCH_SOURCE_INO})
        add_teensy_executable(${SKETCH_TARGET_NAME} ${SKETCH_SOURCE_INO})
    elseif(EXISTS ${SKETCH_SOURCE_PDE})
        add_teensy_executable(${SKETCH_TARGET_NAME} ${SKETCH_SOURCE_PDE})
    endif()
endmacro(_add_sketch_internal)

# Create a target for every Arduino sketch file in sub-directories.
macro(add_sketches)
    set(SKETCH_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    file(GLOB SKETCHES RELATIVE ${SKETCH_DIR} ${SKETCH_DIR}/*)
    foreach(SKETCH ${SKETCHES})
        set(SKETCH_CONFIG "${SKETCH_DIR}/${SKETCH}/CMakeLists.txt")
        if(EXISTS ${SKETCH_CONFIG})
            # If there is a CMakeLists.txt file in the sketch's directory,
            # it is probably configuration settings. Include it.
            subdirs("${SKETCH_DIR}/${SKETCH}")
        else()
            _add_sketch_internal(${SKETCH_DIR} ${SKETCH})
        endif()
    endforeach()
endmacro()

# Create a target for the sketch in the current directory.
macro(add_sketch)
    get_filename_component(SKETCH "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
    get_filename_component(SKETCH_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
    _add_sketch_internal(${SKETCH_DIR} ${SKETCH})
endmacro()
cmake_minimum_required(VERSION 3.13)

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(
  buzzer
  LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

include("~/warez/TM1637-pico/PicoTM1637.cmake")

if (TARGET tinyusb_device)
	add_executable(buzzer buzzer.c)

	target_link_libraries(buzzer pico_stdlib PicoTM1637)

    pico_enable_stdio_usb(buzzer 1)
    pico_enable_stdio_uart(buzzer 0)

	pico_add_extra_outputs(buzzer)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()

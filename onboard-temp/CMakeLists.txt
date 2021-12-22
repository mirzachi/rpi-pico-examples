add_executable(onboard_temp)

target_sources(onboard_temp PRIVATE main.c)

target_link_libraries(onboard_temp PRIVATE
        pico_stdlib
        hardware_adc
        )

pico_enable_stdio_uart(onboard_temp 0)
pico_enable_stdio_usb(onboard_temp 1)

pico_add_extra_outputs(onboard_temp)


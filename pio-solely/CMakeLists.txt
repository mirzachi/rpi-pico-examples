add_executable(pio_solely)

pico_generate_pio_header(pio_solely ${CMAKE_CURRENT_LIST_DIR}/pio-provider-asm.pio)
pico_generate_pio_header(pio_solely ${CMAKE_CURRENT_LIST_DIR}/pio-consumer-asm.pio)

target_sources(pio_solely PRIVATE main.c)

target_link_libraries(pio_solely PRIVATE
        pico_stdlib
        hardware_pio
        hardware_dma
        )

pico_add_extra_outputs(pio_solely)


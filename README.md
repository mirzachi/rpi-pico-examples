# Raspberry Pi Pico examples

Projects and experiments including RPi Pico hardware platform.

## [*pio-solely*](./pio-solely)

RPi Pico comes with 2 programmable logic IO blocks (PIO). Each block has dedicated connections
to the bus fabric, GPIO and interrupt controller.
PIO is programmable in the same sense as a processor. 
It has its own instruction set. It can be used to offload the processor from the
heavily deterministic IO work.

This example demonstrates how 2 state machines from a single PIO block may interact
with each other using a DMA controller, that is, without having to interact through the 
processor, which can be used to perform some other tasks.
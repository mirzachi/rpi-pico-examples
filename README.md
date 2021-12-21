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

SM0 generates periodically 0/1 (roughly 2 times per second) and pushes the
result in its RX queue. The DMA controller transfers the data from the SM0 
RX queue into the TX queue of SM1. SM1 pulls the 0/1 from queue and forwards the value
to the LED pin on the board. Additionally, it copies the same value in its
RX queue so that the value can be debugged via one of the 2 available M0
Cortex cores. The end result is the periodic toggling of the LED on the board.
The 2 Cortex M0 cores are not involved in this process. More precisely,
core 0 pulls the value from the RX queue of SM1 when available and forwards the
value via USB to the attached computer. With *minicom*, one can observe the
value received by SM1 from SM0. Core 1 does not perform any tasks.

*Note*: System clock is set to operate on 100 MHz. The SMs are configured
to operate on the 50000 times lower frequency via its clock dividers.
That is, the SMs operate on 2kHz. The SM0 (provider) introduces an
additional artificial delay in its assembly program, so that 0/1s are
generated each 930 cycles within the 2kHz operating frequency.
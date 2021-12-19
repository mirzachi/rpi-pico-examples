#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"

// PIO assembly code for the provider and consumer state machines
#include "pio-provider-asm.pio.h"
#include "pio-consumer-asm.pio.h"

int main() {
    // Set the system clock to 48 MHz and set the peripheral clock to match
    set_sys_clock_48mhz();

    // Choose which PIO block to use
    // Both state machines will run on the same PIO block
    PIO pio = pio0;

    // Our assembled programs need to be loaded into the PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our programs.
    uint offset_provider = pio_add_program(pio, &provider_program);
    uint offset_consumer = pio_add_program(pio, &consumer_program);

    // Find a free state machines on our chosen PIO (erroring if there are
    // none). Configure them to run our programs.
    uint sm_provider = pio_claim_unused_sm(pio, true);
    uint sm_consumer = pio_claim_unused_sm(pio, true);

    provider_program_init(pio, sm_provider, offset_provider);
    consumer_program_init(pio, sm_consumer, offset_consumer, PICO_DEFAULT_LED_PIN);

    // DMA configuration and initialization
    uint dma_channel = 0;

    dma_channel_config c = dma_channel_get_default_config(dma_channel);
    channel_config_set_read_increment(&c, false); // Read always from the same address (FIFO)
    channel_config_set_write_increment(&c, false); // Write always to the same address (FIFO)
    // Configure DMA timer (how often the data should be transferred)
    dma_timer_set_fraction(0, 1, 48 * MHZ); // each second
    channel_config_set_dreq(&c, dma_get_timer_dreq(0));

    dma_channel_configure(dma_channel,
                          &c,
                          &pio->txf[sm_consumer], // destination address
                          &pio->rxf[sm_provider], // source address
                          1000000, // number of transfers
                          true); // start immediately

    // Start programs on state machines
    provider_program_start(pio, sm_provider);
    consumer_program_start(pio, sm_consumer);

    while (true) {
        // TODO: read from SM2 FIFO and send via usb to be able to debug
        sleep_ms(1000);
    }
}

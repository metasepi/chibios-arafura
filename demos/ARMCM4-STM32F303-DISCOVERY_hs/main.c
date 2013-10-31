/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "jhc_rts_header.h"

extern void malloc_init(void);
extern void forkOS_createThread_init(void);

#if 0
/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palSetPad(GPIOE, GPIOE_LED3_RED);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED3_RED);
    palSetPad(GPIOE, GPIOE_LED5_ORANGE);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED5_ORANGE);
    palSetPad(GPIOE, GPIOE_LED7_GREEN);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED7_GREEN);
    palSetPad(GPIOE, GPIOE_LED9_BLUE);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED9_BLUE);
    palSetPad(GPIOE, GPIOE_LED10_RED);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED10_RED);
    palSetPad(GPIOE, GPIOE_LED8_ORANGE);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED8_ORANGE);
    palSetPad(GPIOE, GPIOE_LED6_GREEN);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED6_GREEN);
    palSetPad(GPIOE, GPIOE_LED4_BLUE);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOE, GPIOE_LED4_BLUE);
  }
}
#endif /* 0 */


static const SPIConfig spi1cfg = {
  NULL,
  /* HW dependent part.*/
  GPIOE,
  GPIOE_SPI1_CS,
  SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_CPOL | SPI_CR1_CPHA,
  0
};

uint8_t readByteSPI(uint8_t reg)
{
	char txbuf[2] = {0x80 | reg, 0xFF};
	char rxbuf[2];
	spiSelect(&SPID1);
	spiExchange(&SPID1, 2, txbuf, rxbuf);
	spiUnselect(&SPID1);
	return rxbuf[1];
}

uint8_t writeByteSPI(uint8_t reg, uint8_t val)
{
	char txbuf[2] = {reg, val};
	char rxbuf[2];
	spiSelect(&SPID1);
	spiExchange(&SPID1, 2, txbuf, rxbuf);
	spiUnselect(&SPID1);
	return rxbuf[1];
}

void initGyro(void)
{
    /* see the L3GD20 Datasheet */
    writeByteSPI(0x20, 0xcF);
}

int readGyro(float *data_x, float *data_y, float *data_z)
{
    /* read from L3GD20 registers and assemble data */
    /* 0xc0 sets read and address increment */
    char txbuf[8] = {0xc0 | 0x27, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    char rxbuf[8];
    spiSelect(&SPID1);
    spiExchange(&SPID1, 8, txbuf, rxbuf);
    spiUnselect(&SPID1);
    if (rxbuf[1] & 0x7) {
        int16_t val_x = (rxbuf[3] << 8) | rxbuf[2];
        int16_t val_y = (rxbuf[5] << 8) | rxbuf[4];
        int16_t val_z = (rxbuf[7] << 8) | rxbuf[6];
#define MDPS_PER_DIGIT (8.75)
        *data_x = (((float)val_x) * MDPS_PER_DIGIT)/1000.0;
        *data_y = (((float)val_y) * MDPS_PER_DIGIT)/1000.0;
        *data_z = (((float)val_z) * MDPS_PER_DIGIT)/1000.0;
        return 1;
    }
    return 0;
}

/*
 * Application entry point.
 */
int main(void) {
  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit(); /* Use Alloc API following line. */

  /*
   * Activates the serial driver 1 using the driver default configuration.
   * PA9(TX) and PA10(RX) are routed to USART1.
   */
  sdStart(&SD1, NULL);
  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));
  palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));

  spiStart(&SPID1, &spi1cfg);
  initGyro();

#if 0
  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
#endif /* 0 */

  { /* Init Ajhc RTS (Haskell) */
    int hsargc = 1;
    char *hsargv = "q";
    char **hsargvp = &hsargv;

    malloc_init();
    forkOS_createThread_init();

    hs_init(&hsargc, &hsargvp);
    _amain();
  }

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched.
   */
  while (TRUE) {
    if (palReadPad(GPIOA, GPIOA_BUTTON))
      TestThread(&SD1);
    chThdSleepMilliseconds(500);
  }
}

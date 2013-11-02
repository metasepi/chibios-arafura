import ChibiOSWrap

import Control.Monad
import Control.Concurrent
import Foreign.C.String

{--
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
--}
main :: IO ()
main = void $ forkOS threadBlinkOrange

{--
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(500);
--}
blinkOrange :: IO ()
blinkOrange = do
  c_palSetPad c_GPIOD c_GPIOD_LED3
  c_chThdSleepMilliseconds 500
  c_palClearPad c_GPIOD c_GPIOD_LED3
  c_chThdSleepMilliseconds 500

{--
/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
  chRegSetThreadName("blinker");
  while (TRUE) {
	  blinkOrange();
  }
--}
threadBlinkOrange :: IO ()
threadBlinkOrange = do
--  newCString "blinker" >>= c_chRegSetThreadName
  forever blinkOrange

import ChibiOSWrap

import Control.Monad
import Foreign.C.String

main :: IO ()
main = return ()

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
  chRegSetThreadName("blinker");
  while (TRUE) {
	  blinkOrange();
  }
--}
foreign export ccall "threadBlinkOrange" threadBlinkOrange :: IO ()
threadBlinkOrange :: IO ()
threadBlinkOrange = do
  newCString "blinker" >>= c_chRegSetThreadName
  forever blinkOrange

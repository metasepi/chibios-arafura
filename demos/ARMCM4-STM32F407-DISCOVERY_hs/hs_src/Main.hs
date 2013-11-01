import ChibiOSWrap

main :: IO ()
main = return ()

{--
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(500);
--}
foreign export ccall "blinkOrange" blinkOrange :: IO ()
blinkOrange :: IO ()
blinkOrange = do
  c_palSetPad c_GPIOD c_GPIOD_LED3
  c_chThdSleepMilliseconds 500
  c_palClearPad c_GPIOD c_GPIOD_LED3
  c_chThdSleepMilliseconds 500

{-# LANGUAGE ForeignFunctionInterface #-}
module ChibiOSWrap where

import Foreign.Ptr
import Data.Word

newtype {-# CTYPE "ioportid_t" #-} IoportidT = IoportidT Word32
type SystimeT = Word32

foreign import primitive "const.GPIOD" c_GPIOD :: IoportidT
foreign import primitive "const.GPIOD_LED3" c_GPIOD_LED3 :: Int
foreign import capi "c_extern.h palSetPad" c_palSetPad :: IoportidT -> Int -> IO ()
foreign import capi "c_extern.h palClearPad" c_palClearPad :: IoportidT -> Int -> IO ()
foreign import capi "c_extern.h chThdSleepMilliseconds" c_chThdSleepMilliseconds :: SystimeT -> IO ()
foreign import ccall "c_extern.h &jhc_zeroAddress" c_jhc_zeroAddress :: Ptr ()

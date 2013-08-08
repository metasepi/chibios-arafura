{-# LANGUAGE ForeignFunctionInterface #-}
module Sleep (
  threadDelayMicroseconds
  ) where
import Data.Word

threadDelayMicroseconds :: Word32 -> IO ()
threadDelayMicroseconds = c_chThdSleepMilliseconds

foreign import ccall "c_extern.h chThdSleepMilliseconds" c_chThdSleepMilliseconds :: Word32 -> IO ()

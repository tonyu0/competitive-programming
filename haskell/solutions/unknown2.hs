-- module Main where

-- import Lib
import Data.List
import Data.Ord

main :: IO ()
main = do
  [n, k] <- map read . words <$> getLine :: IO [Int]
  ls <- map read . words <$> getLine :: IO [Int]
  print $ sum $ take k $ sortOn Down ls

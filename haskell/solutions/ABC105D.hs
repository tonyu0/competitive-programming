import           Data.List
main = do
  [_, m] <- map read . words <$> getLine :: IO [Integer]
  as     <- map read . words <$> getLine :: IO [Integer]
  let mod_cum = map (`mod` m) $ scanl (+) 0 as
      ans =
        sum $ map ((\x -> x * (x - 1) `div` 2) . length) (group $ sort mod_cum)
  print ans


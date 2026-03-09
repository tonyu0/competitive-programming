main = do
  [n, k] <- map read . words <$> getLine :: IO [Integer]
  print $ solve n n k

solve :: Integer -> Integer -> Integer -> Integer

solve 0 n k = if k == 0 then (-n) else 0
solve i n k = res + solve (i - 1) n k
  where res = max 0 (div n i * (i - k)) + max 0 (mod n i - k + 1)

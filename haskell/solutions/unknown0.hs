main = do
  n <- readLn
  print $ sum [i * div (m * (m + 1)) 2 | i <- [1 .. n], let m = div n i]
-- nCk
comb n k = iterate (scanl1 (+)) [1, 1 ..] !! (n - k) !! k

-- digit sum
digitSum :: Integer -> Integer
digitSum x
  | x > 0 = mod x 10 + digitSum (div x 10)
  | otherwise = 0

primes :: Integral a => [a]
primes = map fromIntegral $ [2, 3] ++ primes'
  where
    primes' = [5] ++ f 1 7 primes'
    f m s (p : ps) = [n | n <- ns, gcd m n == 1] ++ f (m * p) (p * p) ps
      where
        ns = [x + y | x <- [s, s + 6 .. p * p - 2], y <- [0, 4]]

-- n^p(mod p)を求める。
modPow :: Integral a => a -> a -> a -> a
modPow n 0 m = 1
modPow n 1 m = mod n m
modPow n p m = mod (k * k * (if mod p 2 == 0 then 1 else n)) m
  where k = modPow n (div p 2) m

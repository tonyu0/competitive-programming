main=readLn>>=(\n->print$(solve 1 n)-2)
 
solve :: Integral n => n -> n -> n
solve i n
  | i * i > n = 10^12
  | otherwise = if mod n i == 0 then min (i + (div n i)) $ solve (i+1) n else solve (i+1) n

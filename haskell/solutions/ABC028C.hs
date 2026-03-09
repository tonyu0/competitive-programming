import Data.List
main = do
  as <- map read . words <$> getLine
  print ((reverse $ sort [s|i<-[0..4],j<-[i+1..4],k<-[j+1..4],let s = as!!i + as!!j + as!!k])!!2)
p=3.1415926535
main=do
  [a,b,x]<-map read . words <$> getLine
  print $ if x > a*a*b/2 then (atan (2*(a*a*b-x)/(a^3)))*180/p else (atan (a*b*b/(x*2)))*180/p

import Control.Monad
main = do
  n <- readLn
  mapM_ putStrLn $ replicateM n "abc"

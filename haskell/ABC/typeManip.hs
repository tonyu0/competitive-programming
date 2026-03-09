-- Integerのlengthをとる
length' :: [Integer] -> Integer
length' as = fromIntegral $ length as

-- 配列を文字列にする
listToStr :: [Integer] -> String
listToStr (x:xs) = show x ++ "\n" ++ listToStr xs
listToStr [] = ""

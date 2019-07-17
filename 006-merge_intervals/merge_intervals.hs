import Data.Functor ((<&>))

main :: IO ()
main = interact (lines <&> map (read <&> merge_intervals <&> show) <&> unlines)

merge_intervals :: [(Integer, Integer)] -> [(Integer, Integer)]
merge_intervals [] = []
merge_intervals [x] = [x]
merge_intervals (x:xs) = if overlapping
    then ((fst x, snd (head xs)) : merge_intervals(tail xs))
    else (x: (merge_intervals(xs)))
        where 
            overlapping = fst (head xs) <= snd x

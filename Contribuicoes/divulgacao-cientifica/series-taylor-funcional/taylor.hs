{-
	Aplicando conhecimentos da série de Taylor funcionalmente utilizando a linguagem Haskell.

	Veja ../docs/serieTaylor.pdf para obter mais informações	
-}

-- Módulo responsável por adicionar compatibilidade com os números naturais e facilitar a leitura
import Numeric.Natural

{-
	Função principal. Serve apenas para mostrar as informações na tela
	é uma função impura
-}
main :: IO()
main = do
       putStrLn ("Valor do seno:    " ++ show (senT pi 10))
       putStrLn ("Valor do cosseno: " ++ show (cosT pi 10))

{-
	função recursiva que calcula o fatorial de n
	Esta função será usada na formação da série de Taylor para calcular o Seno e o Cosseno
-}
fatorial :: Natural -> Natural
fatorial 0 = 1
fatorial n = n * fatorial (n - 1)


{-
	Somatório de (-1)^n x^(2n + 1) / (2n + 1)! 
	com n indo de 0 até o infinito
-}
senT :: Double -> Natural -> Double
senT x n = sum (take (fromIntegral n) [ ((-1) ^ k) * (x ^ (2*k + 1)) / 
                       fromIntegral(fatorial(fromIntegral(2*k + 1)))
                       | k <- [0..]])


{-
	Somatório de (-1)^n x^2n / (2n)!
	com n indo de 0 até o infinito
-}
cosT :: Double -> Natural -> Double 
cosT x n = sum (take (fromIntegral n) [ ((-1) ^ k) * (x ^ (2*k)) / 
                       fromIntegral(fatorial(fromIntegral(2*k)))
                       | k <- [0..]])

import multiprocessing as mp
import math as m

#utilizando la Identidad de euler:
#π⁴/90 = 1/1⁴ + 1/2⁴ + 1/3⁴ + 1/4⁴+...

def euler(x):
  s = 1/x**4
  return s

if __name__=="__main__":
  N = 10000
  l1 = list(range(1,N+1))
  with mp.Pool() as pool:
  	res = sum(pool.map(euler,l1))
  	pi = (90*res)**0.25
  	print(f"El calculo de PI con N= {N} es: {pi}")

from z3 import *

X = [[0] * 9 for _ in range(9)]
elements = input().split()
for i in range(9):
    for j in range(9):
        X[i][j] = int(elements[i * 9 + j])
    
A = [ [ Int("x_%s_%s" % (i+1, j+1)) for j in range(9) ] for i in range(9) ]

val_bnd = [ And(A[i][j]>0,A[i][j]<=9) for j in range(9) for i in range(9)]
uniq_row = [ Distinct(A[i]) for i in range(9)]
uniq_col = [ Distinct([ A[i][j] for i in range(9)]) for j in range(9)]
uniq_block = [ Distinct([ A[3*i0 + i][3*j0 + j] for i in range(3) for j in range(3)]) for i0 in range(3) for j0 in range(3)]
given_val = [ If(X[i][j]==0,True,A[i][j]==X[i][j]) for i in range(9) for j in range(9)]

tot_const = val_bnd + uniq_row + uniq_col + uniq_block + given_val

s=Solver()
s.add(tot_const)

if s.check()==sat:
    model=s.model()
    sol=[ [model.evaluate(A[i][j]) for j in range(9)] for i in range(9)]
    for row in sol:
        print(*row, end=" ")
else:
    print(-1)

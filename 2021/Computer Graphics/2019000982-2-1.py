import numpy as np

# A
M = np.array(range(25))
for i in range(0, 25):
    M[i] = i + 2
    
print(M)
print()

# B
M = M.reshape(5, 5)

print(M)
print()

# c
for i in range(0, 5):
    M[i, 0] = 0

print(M)
print()

# D
M = M @ M

print(M)
print()


# E
v = np.arange(5)
v = M[0]
mag = np.sqrt(v @ v)

print(mag)

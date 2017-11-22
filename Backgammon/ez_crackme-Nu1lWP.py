from z3 import *
vec = []
for i in range(35):
    vec.append(BitVec('ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'[i], 8))
def fxor(data):
    return data^0x76
def de1(data):
    return 2 * (data ^ 0xad) & 0xAA | LShR(((data ^ 0xad) & 0xAA), 1)
def de2(data):
    return 4 * (data ^ 0xBE) & 0xCC | LShR(((data ^ 0xBE) & 0xCC), 2)
def de3(data):
    return 16 * (data ^ 0xEF) & 0xF0 | LShR(((data ^ 0xEF) & 0xF0), 4)
table = [ 0x1E, 0x15, 0x02, 0x10, 0x0D, 0x48, 0x48, 0x6F, 0xDD, 0xDD,
  0x48, 0x64, 0x63, 0xD7, 0x2E, 0x2C, 0xFE, 0x6A, 0x6D, 0x2A,
  0xF2, 0x6F, 0x9A, 0x4D, 0x8B, 0x4B, 0xFF, 0xFF, 0x4F, 0x4E,
  0x14, 0x4F, 0x40, 0x41, 0x0B]
solver = Solver()
for i in range(7):
    solver.add(table[i] == fxor(vec[i]))
for i in range(7,14):
    solver.add(table[i] == de1(fxor(vec[i])))
for i in range(14,21):
    solver.add(table[i] == de2(fxor(vec[i])))
for i in range(21,28):
    solver.add(table[i] == de3(fxor(vec[i])))
for i in range(28,35):
    solver.add(table[i] == fxor(vec[i]))
print solver.check()
s = ''
for i in vec:
    s += chr(int((solver.model()[i]).as_string()))
print s
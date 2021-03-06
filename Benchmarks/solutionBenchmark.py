#move up one directory layer to execute or fix module import otherwise
import kociemba,time
from SolverBackend.Cube import Cube as erno
from PyQt5.QtCore import QElapsedTimer
f = open("scrambles.txt", "r")
lines = f.readlines()
f2 = open("solutionBenchmark.txt", 'w')
cube = erno()
counter = 0
for line in lines: 
    counter += 1
    f2.write("{}: ;".format(counter)+line.strip() + ";\n")
    cube.__init__()
    cube.scramble(line.strip())
    print(cube.cubestring)
    for i in range(1,21):
        
        timer = QElapsedTimer()
        timer.start()
        solution = kociemba.solve(cube.cubestring)
        elapsed = timer.nsecsElapsed()
        f2.write(solution + "; {};\n".format(elapsed))



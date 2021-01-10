import SolverBackend.AlgorithmPython.solver as solver
import SolverBackend.Cube as erno
import time
teststring = 'DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL'; 

result, nmoves= solver.solve(teststring, max_length = 20, timeout = 10)
print(result)  
print(nmoves)
cube = erno.Cube()
cube.U()
#cube.rotate_x()
start = time.time()
result, nmoves = solver.solve(cube.cubestring, max_length = 20, timeout = 10)
end = time.time()
print(result)
print(nmoves)
print(f'solver took: {end-start} seconds')  
cube.print()
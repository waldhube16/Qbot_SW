import SolverBackend.AlgorithmPython.solver as solver
import SolverBackend.Cube as erno
teststring = 'DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL'; 

result = solver.solve(teststring, max_length = 20, timeout = 10)
print(result)  

cube = erno.Cube()
cube.U()
#cube.rotate_x()

result = solver.solve(cube.cubestring, max_length = 20, timeout = 10)
print(result)  
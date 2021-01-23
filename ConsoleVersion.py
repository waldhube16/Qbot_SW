import SolverBackend.Cube as erno
import time
import cv2 as cv
import kociemba
cube = erno.Cube()

def chooseCommand(argument):
    #python does not feature a switch-case structure
    #using this dictionary keys can be mapped to functions
    switcher = {
    "U": cube.U,
    "u": cube.u,    
    "R": cube.R,
    "r": cube.r,    
    "F": cube.F,
    "f": cube.f,    
    "D": cube.D,
    "d": cube.d,    
    "L": cube.L,
    "l": cube.l,        
    "B": cube.B,
    "b": cube.b,
    "p": cube.print,
    "res": cube.__init__,
    "x": exit
    }
    func = switcher.get(argument, lambda: print("Invalid command"))
    func()

if __name__ == "__main__": 
    # teststring = 'DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL'; 

    # result, nmoves= solver.solve(teststring, max_length = 20, timeout = 10)
    # print(result)  
    # print(nmoves)

    # cube.U()
    # #cube.rotate_x()
    # start = time.time()
    # result, nmoves = solver.solve(cube.cubestring, max_length = 20, timeout = 10)
    # end = time.time()
    # print(result)
    # print(nmoves)
    # print(f'solver took: {end-start} seconds')   
    img = cv.imread("ExampleImages/Back.jpeg")
    cv.imshow("test",img)
    cv.waitKey(0)
    cv.destroyAllWindows()
    while True:
        cmd = input("Enter Command:\n")
        if cmd == "solve":
            start = time.time()
            result, nmoves = kociemba.solve(cube.cubestring)
            end = time.time()
            print(result)
            print(nmoves)
        else:
            chooseCommand(cmd)
    




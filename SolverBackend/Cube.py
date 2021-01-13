"""
This is the Cube object. It contains the facemap and the functions that can be performed on the cube . 
"""
"""
The properties of the Cpp class are:
	CubeFace WHITE_;
	CubeFace GREEN_;
	CubeFace RED_ ;
	CubeFace BLUE_ ;
	CubeFace ORANGE_ ;
	CubeFace YELLOW_ ;

	CubeFace* ptr_UP_;
	CubeFace* ptr_FRONT_;
	CubeFace* ptr_RIGHT_;
	CubeFace* ptr_BACK_;
	CubeFace* ptr_LEFT_;
	CubeFace* ptr_DOWN_;


	std::string face_Map_[9][12];

To make the class simpler these will be reduced to just a cubestring which will be manipulated. 

"""


from .constants import Colors 
import numpy as np

class Cube():
    """
    The Cube object consists of the cubestring and the manipulation methods.
    """
    cubestring = str('')
    colors = dict() #fixed right now, maybe add the possibility to set custom colors

    def __init__(self):
        """
        initializes the Cube to the solved state with standard colors in rgb format
        can also be used to reset the cube to the initial state
        """
        self.cubestring = 'UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB'
        self.colors = {'U': Colors.white, 'R': Colors.red, 'F': Colors.green, 'D': Colors.yellow, 'L': Colors.orange, 'B': Colors.blue}
        pass
    

    def scramble(self, scramblestring):
        """
        scrambles the cubestring based on an input string 
        This imputstring can be either a cubestring or a sequence of moves. 
        """
        if len(scramblestring) == 0:
            #no input given --> generate random cube
            bRandom = True
        elif len(scramblestring) == 54 and checkString(scramblestring):
            #A cubestring was used
            bString = True
        else:
            #A sequence was chosen
            bSequence = True
            switcher = {
                "U": self.U,
                "U'": self.u,
                "R": self.R,
                "R'": self.r,
                "F": self.F,
                "F'": self.f,
                "D": self.D,
                "D'": self.d,
                "L": self.L,
                "L'": self.l,
                "B": self.B,
                "B'": self.b,
                "x": self.rotate_x,
                "x'": self.rotate_xprime,
                "y": self.rotate_y,
                "y'": self.rotate_yprime,
                "z": self.rotate_z,
                "z'": self.rotate_zprime
            }
            #replace 2s in string with preceding letter
            while scramblestring.find("2") != -1:
                index = scramblestring.find("2")
                scramblestring[index] = " " + scramblestring[index-1]

            moveset = scramblestring.split(" ")
            for move in moveset:
                switcher[move]()
        pass

    def U(self):
        """
        Turn the upper layer clockwise.
        """
        oldfaces, newfaces = self.getCubeFaces()
 
        #rotate Up face clockwise
        newfaces['U'] = np.rot90(oldfaces['U'],k=-1)
        #L<-F
        newfaces['L'][0]  = oldfaces['F'][0]
        #F<-R
        newfaces['F'][0]  = oldfaces['R'][0] 
        #R<-B
        newfaces['R'][0]  = oldfaces['B'][0] 
        #B<-L
        newfaces['B'][0]  = oldfaces['L'][0] 

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring

        #print(newcubestring)
        pass
    def u(self):
        """
        Turn the upper layer counterclockwise.
        rotate up face counter-clockwise
        upper 3 cubies of F,L,R,B are rotated in order
        """
        oldfaces, newfaces = self.getCubeFaces()
 
        #rotate Up face counter-clockwise
        newfaces['U'] = np.rot90(oldfaces['U'],k=1)
        #L->F
        newfaces['F'][0]  = oldfaces['L'][0]
        #F->R
        newfaces['R'][0]  = oldfaces['F'][0] 
        #R->B
        newfaces['B'][0]  = oldfaces['R'][0] 
        #B->L
        newfaces['L'][0]  = oldfaces['B'][0] 

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring 
        #print(newcubestring)
        pass

    def R(self):
        """
        Turn right layer clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_zprime()
        self.U()
        self.rotate_z()
        pass
    def r(self):
        """
        Turn right layer counter-clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_zprime()
        self.u()
        self.rotate_z()
        pass

    def F(self):
        """
        Turn front layer clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_x()
        self.U()
        self.rotate_xprime()
        pass
    def f(self):
        """
        Turn front layer counter-clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_x()
        self.u()
        self.rotate_xprime()
        pass

    def D(self):
        """
        Turn down layer clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_xprime()
        self.rotate_xprime()
        self.U()
        self.rotate_x()
        self.rotate_x()
        pass
    def d(self):
        """
        Turn down layer counter-clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_xprime()
        self.rotate_xprime()
        self.u()
        self.rotate_x()
        self.rotate_x()
        pass 

    def L(self):
        """
        Turn left layer clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_z()
        self.U()
        self.rotate_zprime()
        pass
    def l(self):
        """
        Turn left layer counter-clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_z()
        self.u()
        self.rotate_zprime()
        pass

    def B(self):
        """
        Turn back layer clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_xprime()
        self.U()
        self.rotate_x()
        pass
    def b(self):
        """
        Turn back layer counter-clockwise by flipping to the top rotating there and flipping back
        """
        self.rotate_xprime()
        self.u()
        self.rotate_x()
        pass

    def rotate_y(self):
        """
        Rearrange the cubefaces to emulate the rotation of the cube in clockwise y-direction. 
        Imagine an axis through U/D faces
        """
        oldfaces, newfaces = self.getCubeFaces()
        #rotate Up/down face 
        newfaces['U'] = np.rot90(oldfaces['U'],k=-1)
        newfaces['D'] = np.rot90(oldfaces['D'],k=1)
        #L<-F
        newfaces['L']  = oldfaces['F']
        #F<-R
        newfaces['F'] = oldfaces['R']
        #R<-B
        newfaces['R']  = oldfaces['B']
        #B<-L
        newfaces['B']  = oldfaces['L']

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring
        #print(newcubestring) 
        pass
    def rotate_yprime(self):
        """
        Rearrange the cubefaces to emulate the rotation of the cube in counterclockwise y-direction. 
        """
        oldfaces, newfaces = self.getCubeFaces()
        #rotate Up/down face 
        newfaces['U'] = np.rot90(oldfaces['U'],k=1)
        newfaces['D'] = np.rot90(oldfaces['D'],k=-1)
        #L->F
        newfaces['F']   = oldfaces['L'] 
        #F->R
        newfaces['R']   = oldfaces['F']  
        #R->B
        newfaces['B']   = oldfaces['R']  
        #B->L
        newfaces['L']   = oldfaces['B']  

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring
        #print(newcubestring)
        pass

    def rotate_x(self):
        """
        Rearrange the cubefaces to emulate the rotation of the cube in clockwise x-direction. 
        Imagine axis through L/R faces
        """
        oldfaces, newfaces = self.getCubeFaces()
        #rotate Up/down face #k=-1 -> clockwise
        newfaces['R'] = np.rot90(oldfaces['R'],k=-1) 
        newfaces['L'] = np.rot90(oldfaces['L'],k=1) 
        oldfaces['U'] = np.rot90(oldfaces['U'],k=-2) 
        oldfaces['B'] = np.rot90(oldfaces['B'],k=-2) 
        #U->B
        newfaces['B']   = oldfaces['U'] 
        #F->U
        newfaces['U']   = oldfaces['F']  
        #D->F
        newfaces['F']   = oldfaces['D']  
        #B->D
        newfaces['D']   = oldfaces['B']  

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring
        #print(newcubestring)
        pass
    def rotate_xprime(self):
        """
        Rearrange the cubefaces to emulate the rotation of the cube in clockwise x-direction. 
        """
        oldfaces, newfaces = self.getCubeFaces()
        #rotate Up/down face #k=-1 -> clockwise
        newfaces['R'] = np.rot90(oldfaces['R'],k=1) 
        newfaces['L'] = np.rot90(oldfaces['L'],k=-1) 
        oldfaces['D'] = np.rot90(oldfaces['D'],k=2) 
        oldfaces['B'] = np.rot90(oldfaces['B'],k=2) 
        #D->B
        newfaces['B']   = oldfaces['D'] 
        #B->U
        newfaces['U']   = oldfaces['B']  
        #U->F
        newfaces['F']   = oldfaces['U']  
        #F->D
        newfaces['D']   = oldfaces['F']  

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring
        #print(newcubestring)
        pass

    def rotate_z(self):
        """
        Rearrange the cubefaces to emulate the rotation of the cube in clockwise x-direction. 
        Imagine axis through F/B faces
        """
        oldfaces, newfaces = self.getCubeFaces()
        #rotate Up/down face #k=-1 -> clockwise
        oldfaces['U'] = np.rot90(oldfaces['U'],k=-1) 
        oldfaces['F'] = np.rot90(oldfaces['F'],k=-1) 
        oldfaces['R'] = np.rot90(oldfaces['R'],k=-1) 
        oldfaces['D'] = np.rot90(oldfaces['D'],k=-1) 
        oldfaces['L'] = np.rot90(oldfaces['L'],k=-1) 
        oldfaces['B'] = np.rot90(oldfaces['B'],k=1)
        
        newfaces['F']   = oldfaces['F'] 
        newfaces['B']   = oldfaces['B'] 
        #U->R
        newfaces['R']   = oldfaces['U'] 
        #R->D
        newfaces['D']   = oldfaces['R']  
        #D->L
        newfaces['L']   = oldfaces['D']  
        #L->U
        newfaces['U']   = oldfaces['L']  

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring
        #print(newcubestring)
        pass
    def rotate_zprime(self):
        """
        Rearrange the cubefaces to emulate the rotation of the cube in clockwise x-direction. 
        """
        oldfaces, newfaces = self.getCubeFaces()
        #rotate Up/down face #k=-1 -> clockwise
        oldfaces['U'] = np.rot90(oldfaces['U'],k=1) 
        oldfaces['F'] = np.rot90(oldfaces['F'],k=1) 
        oldfaces['R'] = np.rot90(oldfaces['R'],k=1) 
        oldfaces['D'] = np.rot90(oldfaces['D'],k=1) 
        oldfaces['L'] = np.rot90(oldfaces['L'],k=1) 
        oldfaces['B'] = np.rot90(oldfaces['B'],k=-1)
        
        newfaces['F']   = oldfaces['F'] 
        newfaces['B']   = oldfaces['B'] 
        #D->R
        newfaces['R']   = oldfaces['D'] 
        #L->D
        newfaces['D']   = oldfaces['L']  
        #U->L
        newfaces['L']   = oldfaces['U']  
        #R->U
        newfaces['U']   = oldfaces['R']  

        newcubestring = self.getCubeString(newfaces)

        self.cubestring = newcubestring
        #print(newcubestring)
        pass

    def getCubeString(self, newfaces):
        """
        Takes the cubefaces and and return the cubestring. 
        """
        newcubestring = ''
        order = ["U", "R", "F", "D", "L", "B"] 
        for face in order:
            #transform each array into 1x9
            newfaces[face] = np.reshape(newfaces[face], (1,9))
            #convert back to bytes and decode
            newfaces[face] = newfaces[face].tobytes().decode()
            #concatenate the strings
            newcubestring = newcubestring+newfaces[face]
        return newcubestring

    def getCubeFaces(self):
        """
        Takes the cubestring and returns a dictionary with numpy arrays.
        """
        oldcubestring_bytes = str.encode(self.cubestring)
        #create dict with the faces and the starting indices in the cubestring
        oldfaces = {'U': 0, 'R': 9, 'F': 18, 'D': 27, 'L': 36, 'B': 45}
        newfaces = dict()
        for face in oldfaces:
            #transform string into 6 1x9 arrays
            oldfaces[face]  = np.frombuffer(oldcubestring_bytes, dtype="S1", count=9, offset=oldfaces[face])
            #transform each array into 3x3
            oldfaces[face] = np.reshape(oldfaces[face], (3,3))
            #needs to be copied using numpy because just copying the dict makes the array in newfaces read-only
            newfaces[face] = np.copy(oldfaces[face])
        return oldfaces,newfaces
    
    def print(self):
        """
        Prints the cubestring formatted to the console
        """
        spaces = "   "
        st = self.cubestring
        #print up face
        print(spaces + st[0:3] + spaces + spaces)
        print(spaces + st[3:6] + spaces + spaces)
        print(spaces + st[6:9] + spaces + spaces)
        #print L/F/R/B faces
        print(st[36:39]+st[18:21]+st[9:12]+st[45:48])
        print(st[39:42]+st[21:24]+st[12:15]+st[48:51])
        print(st[42:45]+st[24:27]+st[15:18]+st[51:54])
        #print down face
        print(spaces + st[27:30] + spaces + spaces)
        print(spaces + st[30:33] + spaces + spaces)
        print(spaces + st[33:36] + spaces + spaces)
        pass
    pass

def checkString(strg):
    """
    checks if the input string contains 
    returns True if it only contains the characters URFDLB
    """
    import re
    search=re.compile(r'[^URFDLB]').search
    result = bool(search(strg))
    return not result

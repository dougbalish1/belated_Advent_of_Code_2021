from IPython.display import display, clear_output
from time import sleep 

class Octo:
    def __init__(self, initEnergy, idx):
        self.energy = initEnergy
        self.blinks = 0
        self.blinked = False
        self.noNeighbors = True
        self.neighbors = []
        self.i = idx

    def getNeighbors(self, j):
        indices = [self.i - j - 1, self.i - j, self.i - j + 1,
                self.i - 1, self.i + 1,
                  self.i + j - 1, self.i + j, self.i + j + 1]
        indices = [i for i in indices if (0 <= i) and (i < (j ** 2))]
        indices = [i for i in indices if not ((self.i % j == 0) and ((i + 1) % j == 0))]
        indices = [i for i in indices if not (((self.i + 1) % j == 0) and (i % j == 0) )]
        self.noNeighbors = False
        self.neighbors = indices
        
    def blink(self, cave): #set blinked true, add one to blinks, add to and check any unblinked neighbors
        if self.noNeighbors: self.getNeighbors(cave.dimensions)
        self.blinked = True
        self.blinks += 1
        for i in self.neighbors:
            cave.octos[i].energy += 1
            if (cave.octos[i].energy > 9) and not cave.octos[i].blinked:
                cave.octos[i].blink(cave)
            

class Cave:
    def __init__(self, inFile):
        self.octos = []
        self.dimensions = 0
        self.flag = True
        with open(inFile) as input:
            idx = 0
            while True:
                octo = input.read(1)
                if not octo: break
                if octo == '\n': continue
                self.octos.append(Octo(int(octo), idx))
                idx += 1
        self.dimensions = int(idx ** 0.5)

    def check(self):
        for octo in self.octos:
            if not octo.blinked and octo.energy > 9: octo.blink(self)
        numSynced = 0
        for octo in self.octos:
            if octo.blinked: numSynced += 1
        if numSynced == self.dimensions ** 2: 
            self.flag = False

    def step(self):
        #inc all energy, step 1
        for octo in self.octos:
            octo.energy += 1
        #check all points for octo with enough energy
        self.check()
        #reset blinked octos
        for octo in self.octos:
            if octo.blinked:
                octo.energy = 0
                octo.blinked = False
        self.print()

    def printRes(self):
        output = 0
        for octo in self.octos:
            output += octo.blinks
        print(output)
    
    def print(self):
        clear_output(wait=True)
        grid = ''
        for i in range(self.dimensions):
            line = [octo.energy for octo in self.octos[self.dimensions * i : self.dimensions + self.dimensions * i]]
            grid += ''.join([str(item) for item in line])
            grid += '\n'
        display(grid)
        sleep(.1)

layout = Cave(r'/mnt/c/Users/dougb/Desktop/Advent_of_Code/belated_Advent_of_Code_2021/Day_11/input_11.txt')
i = 1
while layout.flag:
    layout.step()
    i += 1
print(i)
layout.printRes()
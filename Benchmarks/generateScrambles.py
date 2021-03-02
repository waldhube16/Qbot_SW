import io
def genRandom(length):
    """
    generates a random cube scramble, for now fixed lengh to 20 moves
    """
    import random
    scramble_length = length
    moves = ["U", "U'", "U2", "R", "R'", "R2", "F", "F'", "F2", "D", "D'", "D2", "L", "L'", "L2", "B", "B'", "B2"]	
    random_moves = []
    for index in range(0, scramble_length):
        currmove = moves[random.randint(0, len(moves) - 1)]
        random_moves.append(currmove)
        random.shuffle(random_moves)
    random_string = " ".join(random_moves)

    return random_string

if __name__ == "__main__":
    f = open("scrambles.txt", "w")
    for i in range(1,21):
        scramble = genRandom(i)
        print(scramble)
        f.write(scramble + "\n")
    f.close()

    f = open("scrambles.txt", "r")
    lines = f.readlines()
    count = 0
    for line in lines:
        count += 1
        print("{}".format(count)+ ": " + line.strip())
    f.close()


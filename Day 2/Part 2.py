import re

def parseLine():
    sumOfPowers = 0
    file = open("Games.txt", "r")
    setsRegex = "(?<=:)(.*)"
    redsRegex = "(\\d+)(?=\\sred)"
    greensRegex = "(\\d+)(?=\\sgreen)"
    bluesRegex = "(\\d+)(?=\\sblue)"

    for line in file:
        redMax = 0
        greenMax = 0
        blueMax = 0
        sets = re.search(setsRegex, line).group(0)
        sets = re.split(";", sets)
        for set in sets:
            currRed = re.search(redsRegex, set)
            if(currRed):
                currRed = int(currRed.group(0))
                if(currRed > redMax): redMax = currRed

            currGreen = re.search(greensRegex, set)
            if(currGreen):
                currGreen = int(currGreen.group(0))
                if(currGreen > greenMax): greenMax = currGreen

            currBlue = re.search(bluesRegex, set)
            if(currBlue):
                currBlue = int(currBlue.group(0))
                if(currBlue > blueMax): blueMax = currBlue
        power = redMax * greenMax * blueMax
        sumOfPowers += power

    print("The sum of the powers of the minimum cubes is: " + str(sumOfPowers))

    file.close()

parseLine()
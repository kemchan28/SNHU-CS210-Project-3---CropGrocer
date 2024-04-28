import re
import string 

def ReadFile():
    filepath = 'CS210_Project_Three_InputFile.txt'
    with open(filepath, encoding='utf-16-sig') as fp:
        line = fp.readline()
        cnt = 1
        while line:
            print(line.strip())
            line = fp.readline()
    return 0;

def SingleItem(s):
    text = open("CS210_Project_Three_Input_FIle.txt", "r", encoding='utf-8-sig')
    d = dict()
    s = s.lower()
    print("you are searching for " + str(s))
    for line in text:
        line = line.strip()
        line = line.lower()
        words = line.split(" ")
        for word in words:
            if word in d:
                d[word] = d[word] + 1
            else:
                d[word] = 1

    for key in sorted(d.keys()):
        if str(key) == s:
            return int (d[key]);

    return 0;

def WriteItems():
    text = open("CS210_Project_Three_Input_File.txt", "r", encoding='utf-8-sig')
    f = open("frequency.dat", "w")
    d = dict()

    for line in text:
        line = line.strip()
        line = line.lower()
        words = line.split(" ")
        for word in words:
            if word in d:
                d[word] = d[word] + 1
            else:
                d[word] = 1

    for key in sorted(d.keys()):
        s = str(key) + " " + str(d[key]) + "\n"
        f.write(s)

    f.write("end")

def ListItems():
    # opens the file to read mode
    text = open("CS210_Project_Three_Input_File.txt", "r", encoding='utf-8-sig')
    # creates an empty dictionary
    d = dict()

    # loops through each line of the file
    for line in text:
        # removes the leading spaces and newline character
        line = line.strip()
        # convert the character in line to lowercase to avoid mismatch
        line = line.lower()
        # splits line in to words
        words = line.split(" ")

        # iterates over each word in line
        for word in words:
            # checks if the word is already in dictionary
            if word in d:
                # increments count of word by 1
                d[word] = d[word] + 1
            else:
                # adds the word to dictionary with count 1
                d[word] = 1

    # prints the contents of dictionary
    print("ALL ITEMS PURCHASED TODAY\n")
    for key in sorted(d.keys()):
        print("|", key, ":", k[key])




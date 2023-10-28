import sys

def nth (str, index) :
    # une erreur ici
    if index <= 0 :
        print ("Error. Index out of bounds.")
    else :
        l = len(str)
        if l <= index :
            print ("Error. Index out of bounds.")
        else :
            print (str[index])

nth(sys.argv[1], int(sys.argv[2]))

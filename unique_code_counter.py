# this simple script assumes an input of a formatted text file with no garbage lines
# will count the number of unique codes in a file of icd10 codes

count = 0
code_list =[]

with open("myFile.txt") as myFile:
    lines = myFile.readlines()
    for line in lines:
        code = line.split()[0]
        if code in code_list:
            continue
        else:
            code_list.append(code)
            count += 1

print(code_list)
print(count)

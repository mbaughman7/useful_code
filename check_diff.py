'''
this script is for determining differences between two text files.
it is looking for differences in the presence or absence of data, not in the order.
'''

import sys

with open(sys.argv[1], 'r') as f1, open(sys.argv[2], 'r') as f2:
    lines1 = {line.strip() for line in f1}
    lines2 = {line.strip() for line in f2}

diff1 = lines1 - lines2
diff2 = lines2 - lines1
all_diff = set(diff1.union(diff2))

counter = 0

if len(all_diff) > 0:
    print("Files are different.  Up to 20 lines of differences will be displayed below.  Adjust script to show more.")

    for line in all_diff:
        if counter < 20:
            print(line)
        counter += 1

else:
    print("Files are the same")
#!/usr/bin/env python
"""mapper.py"""

import sys

# input comes from STDIN (standard input)


# a = ["1,abc,2,1233", "2,afc,3,1234","3,asc,2.4,1243","4,acc,5,1255","5,aac,4,1273"]

infile = sys.stdin
next(infile)
next(infile)
for line in infile:
# for line in a:
    line = line.strip()
    line = line.split(",")

    if len(line) >=2:
        movieId = line[1]
        rating = line[2]

        print '%s\t%s' % (movieId, rating)
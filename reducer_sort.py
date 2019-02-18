#!/usr/bin/env python
"""reducer_sort.py"""

import sys

for line in reversed(sys.stdin.readlines()):
    line = line.strip()
    avg_rating, movie_name = line.split("\t")
    print '%s\t%s' % (avg_rating,movie_name)

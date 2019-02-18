#!/usr/bin/env python
"""mapper_sort.py"""

import sys
import string

for line in sys.stdin:
    line = line.strip()
    movie_name, avg_rating = line.split("\t")
    print '%s\t%s' % (avg_rating,movie_name)

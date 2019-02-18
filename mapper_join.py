#!/usr/bin/env python
"""mapper_join.py"""
import sys

for line in sys.stdin:
    # Setting some defaults
    movie_id = ""
    avg_rating = "-"
    movie_name = "-"

    line = line.strip()
    splits = line.split(",")
    if len(splits) == 2:
        movie_id = splits[0]
        avg_rating = splits[1]
    else:
        try:
            splits[0] = int(splits[0])
        except Exception as e:
            pass
        if type(splits[0]) == int:
            movie_id = splits[0]
            movie_name = splits[1]
        else:
            continue
    print '%s\t%s\t%s' % (movie_id, avg_rating, movie_name)
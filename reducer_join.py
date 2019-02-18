#!/usr/bin/env python
"""reducer_join.py"""

import sys
import string

last_movie_id = None
cur_movie_name = "-"

for line in sys.stdin:
    # print line
    line = line.strip()
    movie_id, avg_rating, movie_name = line.split('\t')

    if not last_movie_id or last_movie_id != movie_id:
        last_movie_id = movie_id
        cur_movie_name = movie_name
    elif movie_id == last_movie_id and cur_movie_name != '-':
        movie_name = cur_movie_name
        print '%s\t%s' % (movie_name, avg_rating)
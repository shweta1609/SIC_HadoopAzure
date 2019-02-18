#!/usr/bin/env python
"""reducer.py"""
from operator import itemgetter
import sys

movie_rating = {}
#
# inp = ["abc	2.333333",
#        "afc	3.033301",
#        "asc	2.433345",
#        "abc	5.3333121",
#        "asc	4.3333434"]

#Partitoner
for line in sys.stdin:
# for line in inp:
    line = line.strip()
    movieId, rating = line.split('\t')

    if movieId in movie_rating:
        movie_rating[movieId].append(float(rating))
    else:
        movie_rating[movieId] = []
        movie_rating[movieId].append(float(rating))

#Reducer
for movieId in movie_rating.keys():
    avg_rating = sum(movie_rating[movieId])*1.0 / len(movie_rating[movieId])
    print '%s,%s'% (movieId, round(avg_rating,2))
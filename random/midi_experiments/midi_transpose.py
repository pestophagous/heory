#!/usr/bin/python3

import argparse
import copy
import itertools
import json
import math
import os
import pprint
import random
import string
import sys


PP = pprint.PrettyPrinter(indent=4)

"""
midicomp  get_notes_w_sentinel_1353.mid | grep -w On | cut -d' ' -f4 | cut -c3- | awk '{printf("%s,\n", $1)}'
"""

# TODO: figure out how to add tempo meta-data related to this length, so that
#   when the generated midi files are opened in other editors we end up with
#   (for example, in the common case) clean quarter-notes on a 4/4 staff.
BEAT_LENGTH = 100

TRANSPOSITIONS = [
    -14,
    -13,
    -12,
    -9,
    -7,
]

SENTINEL = 36

NOTES_IN = [
    69,
    64,
    36,
    36,
    36,
    36,
    36,
    67,
    69,
    72,
    67,
    36,
    36,
    36,
    36,
    36,
    72,
    74,
    76,
    36,
    36,
    79,
    74,
    36,
    36,
    76,
    72,
    69,
    36,
    36,
    36,
    36,
    36,
    36,
    81,
    36,
    36,
    36,
    36,
    36,
    79,
    36,
    79,
    76,
    36,
    36,
    36,
    36,
    36,
    36,
    81,
    36,
    36,
    36,
    36,
    36,
    79,
    36,
    79,
    76,
    36,
    36,
    36,
    36,
    36,
    36,
    76,
    71,
    36,
    36,
    36,
    36,
    76,
    74,
    76,
    72,
    36,
    36,
    36,
    36,
    72,
    74,
    76,
    36,
    36,
    79,
    74,
    36,
    36,
    76,
    72,
    69,
    36,
    36,
    36,
    36,
    36,
    36,
]


def output_transposed_midi(int_diff, start_time):
    currtime = start_time
    last_note = None

    for n in NOTES_IN:
        if n == SENTINEL:
            # print('sentinel')
            pass
        else:
            target_note = n + int_diff
            # print(1440 On ch=1 n=36 v=100)
            if last_note is not None:
                print("%s Off ch=1 n=%s v=100" % (currtime, last_note))
            print("%s On ch=1 n=%s v=100" % (currtime, target_note))
            last_note = target_note

        currtime += BEAT_LENGTH

    # end last note?
    if last_note is not None:
        print("%s Off ch=1 n=%s v=100" % (currtime, last_note))

    return currtime


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-s',
        '--shortcircuit',
        action='store_true',
        help="only creates stimuli structures; does not upload to anki")
    parser.add_argument("deckname")
    parser.add_argument("inputfile")
    args = parser.parse_args()

    print("MFile 1 1 128\nMTrk")

    starttime = BEAT_LENGTH * 4
    for t in TRANSPOSITIONS:
        starttime = output_transposed_midi(t, starttime)
        print("\n\n\n")

    starttime += BEAT_LENGTH
    print("%s Meta TrkEnd\nTrkEnd" % (starttime))

    # o = get_processed_lines(args.inputfile)

    # if args.shortcircuit:
    #    sys.exit(0)

    # PP.pprint(qo)


if __name__ == '__main__':
    main()

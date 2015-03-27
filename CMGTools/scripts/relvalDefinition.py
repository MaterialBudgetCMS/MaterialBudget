#!/usr/bin/env python

from MaterialBudget.CMGTools.relvalDefinition import *

if __name__ == '__main__':
    import sys
    dataset = sys.argv[1]
    rd = relvalDefinition( dataset )
    print rd

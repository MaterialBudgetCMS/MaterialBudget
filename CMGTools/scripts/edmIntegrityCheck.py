#!/usr/bin/env python

from MaterialBudget.CMGTools.edmIntegrityCheck import PublishToFileSystem, IntegrityCheck
import Das

import copy, os

if __name__ == '__main__':
    
    from optparse import OptionParser, OptionGroup
    
    usage = """usage: %prog [options] /Sample/Name/On/Castor

e.g.: %prog -u wreece -p -w PFAOD_*.root /MultiJet/Run2011A-05Aug2011-v1/AOD/V2
    """
    das = Das.DASOptionParser(usage=usage)
    group = OptionGroup(das.parser,'edmIntegrityCheck Options','Options related to checking files on CASTOR')
    
    group.add_option("-d", "--device", dest="device", default='cmst3',help="The storage device to write to, e.g. 'cmst3'")
    group.add_option("-n", "--name", dest="name", default=None,help='The name of the dataset in DAS. Will be guessed if not specified')
    group.add_option("-p", "--printout", dest="printout", default=False, action='store_true',help='Print a report to stdout')    
    group.add_option("-r", "--recursive", dest="resursive", default=False, action='store_true',help='Walk the mass storage device recursively')
    group.add_option("-u", "--user", dest="user", default=os.getlogin(),help='The username to use when looking at mass storage devices')
    group.add_option("-w", "--wildcard", dest="wildcard", default=None,help='A UNIX style wildcard to specify which files to check')
    das.parser.add_option_group(group)    
    (opts, datasets) = das.get_opt()

    if len(datasets)==0:
        print das.parser.print_help()
        print
        print 'need to provide a dataset in argument'
        
    for d in datasets:
        
        #allows us to specify the user in the dataset string
        op = copy.deepcopy(opts)
        tokens = d.split('%')
        if len(tokens) == 2:
            op.user = tokens[0]
            d = tokens[1]
        
        check = IntegrityCheck(d,op)
        check.test()
        if op.printout:
            check.report()
        report = check.structured()
        pub = PublishToFileSystem(check)
        pub.publish(report)


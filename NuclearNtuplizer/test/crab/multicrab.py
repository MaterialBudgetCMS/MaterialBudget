import os
from WMCore.Configuration import Configuration
config = Configuration()

pyCfgParams = ['outputFile=ZeroBias_Run2015B.root']

config.section_('General')
config.General.transferLogs = True
config.General.workArea     = 'crab_projects_Run2015B'  # Make sure you set this parameter

config.section_('JobType')
config.JobType.pluginName       = 'Analysis'
#config.JobType.pluginName       = 'PrivateMC'
config.JobType.psetName         = 'NtupleMakerWithReReco_Run2015B_cfg.py'
config.JobType.maxJobRuntimeMin = 2800
config.JobType.outputFiles      = ['ZeroBias_Run2015B.root']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')    
config.Data.inputDBS      = 'global'
#config.Data.splitting     = 'FileBased'
config.Data.splitting     = 'LumiBased'
config.Data.unitsPerJob   = 5 # number of files, lumi sec. or events depending of "splitting"
config.Data.totalUnits    = 5 # total number of files, lumi sec. or events depending of "splitting"
config.Data.outLFNDirBase = '/store/group/phys_higgs/cmshww/kropiv/Run2015B/'

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'


import sys

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand

    def submit(config):
        print " to do: ",config
        res = crabCommand('submit', config = config)

    ######### From now on this is what users should modify. It is the a-la-CRAB2 configuration part.
   
    print sys.argv
    if len(sys.argv) <= 1 :
       print "no arguments?"
       print "Usage: python multicrab_template.py test.py"
       exit()
       

    samples = {}
    SamplesFile = sys.argv[1]
    print " SamplesFile = ", SamplesFile
    
    if os.path.exists(SamplesFile):
       handle = open(SamplesFile,'r')
       exec(handle)
       handle.close()
                
    # samples to be analysed
                   
    for key, value in samples.iteritems():
        print key, ' -> ', value
        
        config.General.requestName = key
        config.Data.inputDataset = value[0]
        config.JobType.pyCfgParams = list(pyCfgParams)
        config.JobType.pyCfgParams.extend(value[1])
        submit(config)


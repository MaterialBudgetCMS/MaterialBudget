import os
from WMCore.Configuration import Configuration
config = Configuration()

pyCfgParams = ['outputFile=Run2018.root']

config.section_('General')
config.General.transferLogs = True
config.General.workArea     = 'projects_Run2018'  # Make sure you set this parameter

config.section_('JobType')
config.JobType.pluginName       = 'Analysis'
#config.JobType.pluginName       = 'PrivateMC'
config.JobType.psetName         = 'NtupleMaker_Run2018_cfg.py'
config.JobType.maxJobRuntimeMin = 2750
config.JobType.outputFiles      = ['Run2018.root']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')    
config.Data.inputDBS      = 'global'
#config.Data.splitting     = 'FileBased'
config.Data.splitting     = 'LumiBased'
config.Data.unitsPerJob   = 50 # number of files, lumi sec. or events depending of "splitting"
#config.Data.totalUnits    = 50 # total number of files, lumi sec. or events depending of "splitting"
# Tracker + DCS good files:
#config.Data.lumiMask = 'json_Tracker_2018.05.02.txt'
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/PromptReco/Cert_314472-316723_13TeV_PromptReco_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/Run2018'
# to run on Tier1
#config.Data.ignoreLocality = True
#T1_US_FNAL_Disk

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
#config.section_('Site'config.Site.storageSite = 'T2_CH_CERN'
#config.Site.storageSite = 'T2_CH_CERN'


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


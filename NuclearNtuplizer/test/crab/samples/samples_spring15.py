########
# 25 ns
########
#        CRAB task name       DAS name                                                                                    Latino name
#samples['25ns_DY_Spring15']        = ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/AODSIM',  ['globalTag=MCRUN2_74_V9']]
#samples['25ns_DY']        = ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/AODSIM',  ['globalTag=MCRUN2_74_V9','outputFile=tnpZ_MC.root']]
#samples['25ns_DY']        = ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/AODSIM',  ['label=DY',        'id=0001', 'globalTag=MCRUN2_74_V9']]
#samples['25ns_ggHToWWTo2L2Nu'] = ['/GluGluHToWWTo2L2Nu_M120_13TeV_powheg_JHUgen_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/AODSIM',         ['label=ggHToWWTo2L2Nu', 'id=0002', 'globalTag=MCRUN2_74_V9']]


########
# 50 ns
########
#        CRAB task name       DAS name                                                                                    Latino name
samples['MinBiasCastor_Spring15']        = ['/MinBias_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-NoPURawReco_castor_MCRUN2_74_V8B-v1/GEN-SIM-RECO',  ['globalTag=MCRUN2_74_V8B']] # 10^6 events 55 files
samples['DYJetsToLL_Spring15']        = ['/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-AsymptNoPURawReco_MCRUN2_74_V9A-v4/GEN-SIM-RECO',  ['globalTag=MCRUN2_74_V9A']] # 28*10^6 3142, files



########
# Alternative global configuration
########
# config.Data.outLFNDirBase = '/store/user/piedra/test'
# config.Site.storageSite   = 'T2_ES_IFCA'

Testing version
===

It works only in CMSSW_7_3_0, in CMSSW_7_4_* generate error.

To run:

root -l runNtupleReaderNuclearInteractions_2015.cc 

To run (PlotProduction):

root -l
[] PlotProduction.C++
[] PlotProduction m
[] m.GetEntry(0)
[] m.Loop()

To run (CutAnalyzer):

root -l
[] CutAnalyzer.C++
[] CutAnalyzer m
[] m.GetEntry(0)
[] m.Loop()

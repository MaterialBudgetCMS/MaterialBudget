run fit:

Universal Fit program could fit Beam Pipe, Pixel Shield or Pixel Support, just uncomment correct lines in code and run:

Compiled version works for any CMSSW versions:

For 2018 data:
      root.exe -b revisionsInnerTrackerFit_2018.C++
      root.exe -b PixelFit_2018.C++

For 2017 data:
      root.exe -b revisionsInnerTrackerFit_2017.C++

For paper last version (2015):
      root.exe -b revisionsInnerTrackerFit_paper.C++

For paper v1 (2015):
      root.exe -b InnerTrackerFit.C++
 
For 2015 reReco Data:
     cmsrel CMSSW_7_4_14

For 2016 Data:

     export SCRAM_ARCH=slc6_amd64_gcc530
     cmsrel CMSSW_8_0_20

===========

Old uncompiled version, works only for CMSSW_7_3_X (do not support higher versions) :

Universal Fit program could fit Beam Pipe, Pixel Shield or Pixel Support, just uncomment correct lines in code and run:

      root -b HistogramFitterNuclearInteractions_UniFit.C

===========

Old example for Beam Pipe fit, you could use it only for some learning tasks:

      root -b HistogramFitterNuclearInteractions_BeamPipe.C

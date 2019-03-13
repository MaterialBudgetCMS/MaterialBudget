To run fit:

Universal Fit program could fit Beam Pipe, Pixel Shield or Pixel Support, just uncomment correct lines in code and run:

Compiled version works for any CMSSW versions:

   * For 2018 data:

```
root.exe -b revisionsInnerTrackerFit_2018.C++
root.exe -b PixelFit_2018.C++
root.exe -b TrackerMaterialEstimation_2018.C++
```

   * For 2018 data for public data at CMS-DP-2019-001:

```
root.exe -b revisionsInnerTrackerFit_2018Prel.C++
root.exe -b PixelFit_2018Prel.C++
```

   * For 2017 data:

```
root.exe -b revisionsInnerTrackerFit_2017.C++
```

   * For paper last version (2015):

   This code is working up to `CMSSW_9_2_12` (after root was changed and new code for 2018 was adjust to it)
```
root.exe -b revisionsInnerTrackerFit_paper.C++
root.exe -b revisionsInnerTrackerFit_paperScale2018.C++
```
===========

For 2015 reReco Data:

     cmsrel CMSSW_7_4_14

For 2016 Data:

     export SCRAM_ARCH=slc6_amd64_gcc530
     cmsrel CMSSW_8_0_20




 * 2018B: 1.247 /fb
 * 2018C: 1.060 /fb
 * 2018D: 2.032 /fb 

 In total: 4.3 /fb for SingleMu collection

 * Details for 2018B:

```
awk '{for(i=1;i<=NF;i++)if($i~/Run/ && /LumiSection/) print substr($(i+1), 1, length($(i+1))-1), $(i+5)}' DirOut/Dir2018B/cmsRun-stdout*.log > List_2018B.txt
```
to uniq:
```
awk '!array[$0]++' List_2018B.txt > List_2018B_Uniq.txt
```
to sort:
```
sort -n -k1,1 -k2,2 < List_2018B_Uniq.txt > List_2018B_Sort.txt
```
to produce json file (code is working only after uniq and sort!!!):
```
python pythonLumiJson.py > LumiJson_2018B.txt

```
 * Lumi POG recommendations: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiLUM

 * To install brilcalc:

    * work with centrally installed virtual environment: `export PATH=$HOME/.local/bin:/afs/cern.ch/cms/lumi/brilconda-1.1.7/bin:$PATH #(bash, CERN only)`
    * install brilcalc at CERN:`pip install --install-option="--prefix=$HOME/.local" brilws`
    * Lumi POG recommendation:
```
brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -u /fb -i LumiJson_2018B.txt ### your jsont
```
 * Details for 2018C:
```
awk '{for(i=1;i<=NF;i++)if($i~/Run/ && /LumiSection/) print substr($(i+1), 1, length($(i+1))-1), $(i+5)}' DirOut/Dir2018C/cmsRun-stdout*.log > List_2018C.txt
awk '!array[$0]++' List_2018C.txt > List_2018C_Uniq.txt
sort -n -k1,1 -k2,2 < List_2018C_Uniq.txt > List_2018C_Sort.txt
python pythonLumiJson.py > LumiJson_2018C.txt
brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -u /fb -i LumiJson_2018C.txt ### your jsont
``` 
 * Details for 2018D:
```
awk '{for(i=1;i<=NF;i++)if($i~/Run/ && /LumiSection/) print substr($(i+1), 1, length($(i+1))-1), $(i+5)}' DirOut/Dir2018D/cmsRun-stdout*.log > List_2018D.txt
awk '!array[$0]++' List_2018D.txt > List_2018D_Uniq.txt
sort -n -k1,1 -k2,2 < List_2018D_Uniq.txt > List_2018D_Sort.txt
python pythonLumiJson.py > LumiJson_2018D.txt
brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -u /fb -i LumiJson_2018D.txt ### your jsont
``` 


Run 2015D start from Run 256630 

How to install brilcalc on lxplus:

       export PATH=$HOME/.local/bin:/afs/cern.ch/cms/lumi/brilconda-1.0.3/bin:$PATH (bash)
       pip install --install-option="--prefix=$HOME/.local" brilws

to check version and updates:

       pip show brilws

to upgrade (didn't work in my case):

       pip install --upgrade pip 

to run for our case:

       brilcalc lumi -b "STABLE BEAMS" -u /fb -i Cert_13TeV_16Dec2015ReReco_Collisions15_25ns_JSON_Silver_v2.txt

more information here:

http://cms-service-lumi.web.cern.ch/cms-service-lumi/brilwsdoc.html

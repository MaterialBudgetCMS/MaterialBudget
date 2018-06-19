DirName=$1
#DirName="/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_step1/"
#DirName="/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_step2/"
#DirName="/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/"


rm -rf FileList_Mod.txt
ls -all $DirName|grep root > FileList.txt
echo  $DirName
#awk -v z="$DirName" 'BEGIN {print "'\''file:"z$NF"'\'',"}' FileList.txt > FileList_Mod.txt 
awk -v z="$DirName" '{print "'\''file:"z$NF"'\'',"}' FileList.txt > FileList_Mod.txt 
rm -rf FileList.txt

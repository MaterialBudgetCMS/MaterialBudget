//void runNtupleReader_Training( const std::string fileList = "prova_Run2015D.txt", const Long64_t maxEvents = -1 )
void runNtupleReader_Training( const std::string fileList = "prova_MC.txt", const Long64_t maxEvents = -1 )
//void runNtupleReader_Training( const std::string fileList = "prova_MC.txt", const Long64_t maxEvents = 1000 )
{
  gSystem->CompileMacro("NtupleReader_Training.C");
  NtupleReader_Training m( fileList, maxEvents );
  m.beginJob();
  m.analyze();
  m.endJob();
}


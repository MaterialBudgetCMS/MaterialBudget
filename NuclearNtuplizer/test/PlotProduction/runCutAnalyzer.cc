//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova.txt", const Long64_t maxEvents = -1 )
//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova_Run2015B.txt", const Long64_t maxEvents = -1 )
//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova_Run2015C.txt", const Long64_t maxEvents = -1 )
//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova_Run2015C_50ns.txt", const Long64_t maxEvents = -1 )
//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova_Run2015C_25ns.txt", const Long64_t maxEvents = -1 )
//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova_Run2015D.txt", const Long64_t maxEvents = -1 )
void runCutAnalyzer( const std::string fileList = "prova_MC.txt", const Long64_t maxEvents = -1 )
//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova_Run2016B.txt", const Long64_t maxEvents = -1 )
//void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova_Run2015DreReco.txt", const Long64_t maxEvents = -1 )
{
  gSystem->CompileMacro("CutAnalyzer.C");
  CutAnalyzer m( fileList, maxEvents );
  m.beginJob();
  m.analyze();
  m.endJob();
}

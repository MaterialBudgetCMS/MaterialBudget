void runNtupleReaderNuclearInteractions( const std::string fileList = "prova.txt", const Long64_t maxEvents = -1 )
{
  gSystem->CompileMacro("NtupleReaderNuclearInteractions.C");
  NtupleReaderNuclearInteractions m( fileList, maxEvents );
  m.beginJob();
  m.analyze();
  m.endJob();
}


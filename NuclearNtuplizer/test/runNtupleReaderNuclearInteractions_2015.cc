void runNtupleReaderNuclearInteractions_2015( const std::string fileList = "prova.txt", const Long64_t maxEvents = -1 )
{
  gSystem->CompileMacro("NtupleReaderNuclearInteractions_2015.C");
  NtupleReaderNuclearInteractions_2015 m( fileList, maxEvents );
  m.beginJob();
  m.analyze();
  m.endJob();
}


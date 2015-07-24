void runHistogramFitterNuclearInteractions_BeamPipe( )
{
  gSystem->CompileMacro("HistogramFitterNuclearInteractions_BeamPipe.C");
  HistogramFitterNuclearInteractions_BeamPipe m;
  m.beginJob();
  m.analyze();
  m.endJob();
}


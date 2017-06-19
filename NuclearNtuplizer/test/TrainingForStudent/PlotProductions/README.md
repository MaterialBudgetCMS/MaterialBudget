To run in root:

    .x Analyzer.C++
    Analyzer m
    m.GetEntry(0) # run over all events
    m.Loop()  


To produce new class Analyzer.C/h (only once, you don't need to do it):

    TFile *f = new TFile("Ntuple_MC_10GeV_900.root")
    f->ls()
    new TBrowser()
    NuclearInteractionsTree->MakeClass("Analyzer")


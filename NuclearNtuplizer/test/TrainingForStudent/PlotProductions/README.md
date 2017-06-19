To run:

    .x Analyzer.C++
    Analyzer m
    m.GetEntry(0) # run over all events
    m.Loop()  

To produce new class (only once):

    TFile *f = new TFile("TTbar_Incl_10000.root")
    f->ls()
    new TBrowser()
    NuclearInteractionsTree->MakeClass("Analyzer")


// -*- C++ -*-
//
// FWLite PAT analyzer-selector for dilepton analyses
//
// Adapted from StopEventSelector
// Aram Avetisyan, September 2012
// Updated
// Rizki Syarif, March 2019
//
#ifndef FWLJMET_LJMet_interface_DileptonEventSelector_h
#define FWLJMET_LJMet_interface_DileptonEventSelector_h



#include <cmath>
#include <iostream>

#include "FWLJMET/LJMet/interface/BaseEventSelector.h"
#include "FWLJMET/LJMet/interface/LjmetFactory.h"


#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TTree.h"
#include "TVector3.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/TriggerObject.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "FWLJMET/LJMet/interface/MiniIsolation.h"

#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFMuonSelector.h"
#include "PhysicsTools/SelectorUtils/interface/PVSelector.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"

#include "FWLJMET/LJMet/interface/JetMETCorrHelper.h"

using trigger::TriggerObject;


class DileptonEventSelector : public BaseEventSelector {

public:


    DileptonEventSelector();
    ~DileptonEventSelector();


    // executes before loop over events
    virtual void BeginJob(const edm::ParameterSet& iConfig, edm::ConsumesCollector && iC);

    // main method where the cuts are applied
    virtual bool operator()( edm::Event const & event, pat::strbitset & ret);

    // executes after loop over events
    virtual void EndJob(){}


    virtual void AnalyzeEvent( edm::EventBase const & event, LjmetEventContent & ec );


    boost::shared_ptr<PFJetIDSelectionFunctor> const & jetSel()        const { return jetSel_;}
    boost::shared_ptr<PVSelector>              const & pvSel()         const { return pvSel_;}


protected:

    std::string legend;
    bool bFirstEntry;


    boost::shared_ptr<PFJetIDSelectionFunctor> jetSel_;


private:

    void initialize(std::map<std::string, edm::ParameterSet const> par);


    bool debug;
    bool isMc;

    //Triggers
    bool trigger_cut;
    bool dump_trigger;
    std::vector<std::string> trigger_path_ee;
    std::vector<std::string> trigger_path_em;
    std::vector<std::string> trigger_path_mm;

    //PV
    bool pv_cut;
    boost::shared_ptr<PVSelector>              pvSel_;

    //MET Filter
    bool   metfilters;

	//Muon
    bool muon_cuts;
    int min_muon;
    int max_muon;
    double muon_minpt;
    double muon_maxeta;

    // bool jet_cuts;
    // bool jet_minpt;
    // double jet_maxeta;
    // int min_jet;
    // int max_jet;
    // JetMETCorrHelper JetMETCorr;

    // bool electron_cuts;
    // int min_electron;
    // int max_electron;
    // double electron_minpt;
    // double electron_maxeta;

    // int min_lepton;

    // bool met_cuts;

    // flag_tag;
    // trigger_collection;
    // pv_collection;
    // jet_collection;
    // muon_collection;
    // electron_collection;
    // met_collection;

    // bool doNewJEC;
    // bool doLepJetCleaning;

    // //mva value
    // bool UseElMVA;


    edm::Handle<edm::TriggerResults >           TriggerHandle;
    edm::Handle<std::vector<pat::Muon> >        muonsHandle;
    // edm::Handle<std::vector<pat::Jet> >         mhJets;
    // edm::Handle<std::vector<pat::Electron> >    mhElectrons;
    // edm::Handle<std::vector<pat::MET> >         mhMet;
    // edm::Handle<double>                         h_rho;
    // edm::Handle<std::vector<reco::Vertex> >     h_primVtx;

    // std::vector<edm::Ptr<reco::Vertex> >  good_pvs_;

    // //Tokens
    edm::EDGetTokenT<edm::TriggerResults>            triggersToken;
    edm::EDGetTokenT<reco::VertexCollection>         PVToken;
    edm::EDGetTokenT<edm::TriggerResults>            METfilterToken;
    edm::EDGetTokenT<bool>                           METfilterToken_extra;
    edm::EDGetTokenT<pat::MuonCollection>            muonsToken;
    // edm::EDGetTokenT<pat::JetCollection>             jetsToken;
    // edm::EDGetTokenT<pat::ElectronCollection>        electronsToken;
    // edm::EDGetTokenT<std::vector<pat::MET> >         METtoken;
    // edm::EDGetTokenT<double>                         rhoJetsToken;
    // edm::EDGetTokenT<double>                         rhoJetsNC_Token;
    // edm::EDGetTokenT<edm::TriggerResults>            METfilterToken;
    // edm::EDGetTokenT<pat::PackedCandidateCollection> PFCandToken;

    // //Separate methods for each selction for organization
    bool TriggerSelection  (edm::Event const & event);
    bool PVSelection       (edm::Event const & event);
    bool METfilter         (edm::Event const & event);
    bool MuonSelection     (edm::Event const & event, pat::strbitset & ret);
    // void ElectronSelection (edm::Event const & event);
    // bool LeptonsSelection  (edm::Event const & event, pat::strbitset & ret);
    // bool JetSelection      (edm::Event const & event, pat::strbitset & ret);
    // bool METSelection      (edm::Event const & event);

};

#endif

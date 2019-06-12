#ifndef FWLJMET_LJMet_interface_DileptonCalc_h
#define FWLJMET_LJMet_interface_DileptonCalc_h

#include <iostream>
#include <string>
#include "FWLJMET/LJMet/interface/BaseCalc.h"
#include "FWLJMET/LJMet/interface/LjmetFactory.h"
#include "FWLJMET/LJMet/interface/LjmetEventContent.h"

#include "FWLJMET/LJMet/interface/TopElectronSelector.h"

#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
#include "DataFormats/MuonReco/interface/MuonPFIsolation.h"

#include "DataFormats/BTauReco/interface/CATopJetTagInfo.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "FWLJMET/LJMet/interface/MiniIsolation.h"
#include "HepPDT/ParticleID.hh"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/GridPDF.h"
#include "LHAPDF/Info.h"
#include "LHAPDF/Config.h"
#include "LHAPDF/PDFInfo.h"
#include "LHAPDF/PDFSet.h"
#include "LHAPDF/Factories.h"

using std::cout;
using std::endl;

class LjmetFactory;



class DileptonCalc : public BaseCalc {
    
public:
    
    DileptonCalc();
    virtual ~DileptonCalc(){}
    
    virtual int BeginJob(edm::ConsumesCollector && iC);
    virtual int AnalyzeEvent(edm::Event const & event, BaseEventSelector * selector);
    virtual int EndJob(){return 0;}
    
private:

    void AnalyzeDataType(edm::Event const & event, BaseEventSelector * selector);
    void AnalyzeTriggers(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzePV(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzePU(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzeBadDupMu(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzeMuon(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzeElectron(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzeJets(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzeAK8Jets(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzeMET(edm::Event const & event, BaseEventSelector * selector);
//     void AnalyzeGenInfo(edm::Event const & event, BaseEventSelector * selector);
    
    bool                      debug;
    bool                      isMc;
    std::string               dataType;

	//Triggers
    bool doTriggerStudy_; 

//     edm::InputTag             genParticles_it;
//     edm::InputTag             packedPFCandsLabel_;
//     edm::InputTag             triggerObjects_;

//     //get electrons for mva vid
//     edm::InputTag electronsMiniAODLabel_;
//     edm::InputTag eleLooseIdMapLabel_;
//     edm::InputTag eleTightIdMapLabel_;
//     bool UseElMVA;
// 
//     edm::InputTag mvaValuesMapLabel_;
// 
//     bool keepFullMChistory;
//     double rhoIso;
//     
//     bool orlhew;
//     std::string basePDFname;
//     std::string newPDFname;

//     boost::shared_ptr<TopElectronSelector>     electronSelL_, electronSelM_, electronSelT_;
//     std::vector<reco::Vertex> goodPVs;

    edm::EDGetTokenT<edm::TriggerResults>                    triggersToken;
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectToken;
//     edm::EDGetTokenT<reco::VertexCollection>           pvToken;
//     edm::EDGetTokenT<std::vector<PileupSummaryInfo>>   PupInfoToken;
//     edm::EDGetTokenT<edm::TriggerResults >             muflagtagToken;
//     edm::EDGetTokenT<double>                           rhoJetsNCToken;
//     edm::EDGetTokenT<double>                           rhoJetsToken;
//     edm::EDGetTokenT<pat::PackedCandidateCollection>   PFCandToken;
//     edm::EDGetTokenT<reco::GenParticleCollection>      genParticlesToken;
//     edm::EDGetTokenT<std::vector<pat::MET> >           METnoHFtoken;
//     edm::EDGetTokenT<std::vector<pat::MET> >           METmodToken;
//     edm::EDGetTokenT<GenEventInfoProduct>              genToken;
//     edm::EDGetTokenT<LHEEventProduct>                  LHEToken;
//     edm::EDGetTokenT<std::vector< reco::GenJet> >      genJetsToken;


    int findMatch(const reco::GenParticleCollection & genParticles, int idToMatch, double eta, double phi);
    double mdeltaR(double eta1, double phi1, double eta2, double phi2);
    void fillMotherInfo(
        const reco::Candidate *mother, 
        int i, 
        std::vector <int> & momid, 
        std::vector <int> & momstatus, 
        std::vector<double> & mompt, 
        std::vector<double> & mometa, 
        std::vector<double> & momphi, 
        std::vector<double> & momenergy
        );
};

#endif
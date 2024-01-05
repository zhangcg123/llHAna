#include "llHAna.h"

DECLARE_COMPONENT(llHAna)

// Constructor
llHAna::llHAna(const std::string& name, ISvcLocator* pSvcLocator)
    : GaudiAlgorithm(name, pSvcLocator),
      S(0., 0., 0., 240.){
        declareProperty("MCParticleCollection", mcParticleCol, "Handle for the MCParticleCollection");
        declareProperty("ReconstructedParticleCollection", recParticleCol, "Handle for the ReconstructedParticleCollection");
        //declareProperty("MCTruthLinkCollection", mcTruthLinkCol, "Handle for the MCTruthLinkCollection");
    }

// Method to initialize your analysis
StatusCode llHAna::initialize() {
    // Initialization code goes here
    debug() << "Initializing llHAna" << endmsg;

    cutFlow = new TH1D("cutFlow", "", 6, 0, 6);
    cutFlow->GetXaxis()->SetBinLabel(1, "Total");
    cutFlow->GetXaxis()->SetBinLabel(2, "SFOS");
    cutFlow->GetXaxis()->SetBinLabel(3, "Recoil Mass");
    cutFlow->GetXaxis()->SetBinLabel(4, "Z Mass");
    cutFlow->GetXaxis()->SetBinLabel(5, "pT Cut");
    cutFlow->GetXaxis()->SetBinLabel(6, "Delta Phi");


    rootFile = TFile::Open("llHAna.root", "RECREATE");
    tree = new TTree("llHAna", "llHAna");
    tree->SetAutoSave(32*1024*1024);
    tree->Branch("pos_energy", &pos_energy);
    tree->Branch("pos_px", &pos_px);
    tree->Branch("pos_py", &pos_py);
    tree->Branch("pos_pz", &pos_pz);
    tree->Branch("pos_pt", &pos_pt);
    tree->Branch("pos_p", &pos_p);
    tree->Branch("pos_eta", &pos_eta);
    tree->Branch("pos_phi", &pos_phi);
    tree->Branch("neg_energy", &neg_energy);
    tree->Branch("neg_px", &neg_px);
    tree->Branch("neg_py", &neg_py);
    tree->Branch("neg_pz", &neg_pz);
    tree->Branch("neg_pt", &neg_pt);
    tree->Branch("neg_p", &neg_p);
    tree->Branch("neg_eta", &neg_eta);
    tree->Branch("neg_phi", &neg_phi);

    tree->Branch("ll_energy", &ll_energy);
    tree->Branch("ll_px", &ll_px);
    tree->Branch("ll_py", &ll_py);
    tree->Branch("ll_pz", &ll_pz);
    tree->Branch("ll_pt", &ll_pt);
    tree->Branch("ll_p", &ll_p);
    tree->Branch("ll_mass", &ll_mass);
    tree->Branch("ll_eta", &ll_eta);
    tree->Branch("ll_phi", &ll_phi);

    tree->Branch("recoil_mass", &recoil_mass);

    return GaudiAlgorithm::initialize();
}
// Method to execute your analysis
StatusCode llHAna::execute() {

    debug() << "Executing llHAna" << endmsg;

    cutFlow->SetBinContent(1, cutFlow->GetBinContent(1) + 1);

    const edm4hep::MCParticleCollection* mcParticleCollection = mcParticleCol.get();

    const edm4hep::ReconstructedParticleCollection* recParticleCollection = recParticleCol.get();
    // Get the MCTruthLinkCollection from the event store
    //const edm4hep::MCTruthLinkCollection* mcTruthLinkCollection = mcTruthLinkCol.get();

    int nElements = recParticleCollection->size();
    
    std::vector<edm4hep::ReconstructedParticle> pos_particles; pos_particles.clear();
    std::vector<edm4hep::ReconstructedParticle> neg_particles; neg_particles.clear();

    for(int i = 0; i < nElements; ++i){

        const edm4hep::ReconstructedParticle recParticle = recParticleCollection->at(i);
        if ( recParticle.getType() == 13 ) neg_particles.push_back(recParticle);
        if ( recParticle.getType() == -13 ) pos_particles.push_back(recParticle);

    }

    if ( pos_particles.size() != 1 || neg_particles.size() != 1 ){

        return StatusCode::SUCCESS;

    }else{

        cutFlow->SetBinContent(2, cutFlow->GetBinContent(2) + 1);

        edm4hep::ReconstructedParticle pos_particle = pos_particles.at(0);
        edm4hep::ReconstructedParticle neg_particle = neg_particles.at(0);

        pos_energy = pos_particle.getEnergy();
        neg_energy = neg_particle.getEnergy();

        pos_px = pos_particle.getMomentum()[0];
        pos_py = pos_particle.getMomentum()[1];
        pos_pz = pos_particle.getMomentum()[2];

        neg_px = neg_particle.getMomentum()[0];
        neg_py = neg_particle.getMomentum()[1];
        neg_pz = neg_particle.getMomentum()[2];

        TLorentzVector lep1, lep2;
        lep1.SetPxPyPzE( pos_px, pos_py, pos_pz, pos_energy );
        lep2.SetPxPyPzE( neg_px, neg_py, neg_pz, neg_energy );

        pos_pt = lep1.Pt();
        neg_pt = lep2.Pt();
        pos_p = lep1.P();
        neg_p = lep2.P();
        pos_eta = lep1.Eta();
        neg_eta = lep2.Eta();
        pos_phi = lep1.Phi();
        neg_phi = lep2.Phi();

        TLorentzVector ll = lep1 + lep2;
        
        ll_mass = ll.M();
        ll_energy = ll.E();
        ll_p = ll.P();
        ll_pt = ll.Pt();
        ll_px = ll.Px();
        ll_py = ll.Py();
        ll_pz = ll.Pz();
        ll_eta = ll.Eta();
        ll_phi = ll.Phi();

        recoil_mass = (S - ll).M();

        if ( recoil_mass < 150.0 && recoil_mass > 120.0 ){
                
                cutFlow->SetBinContent(3, cutFlow->GetBinContent(3) + 1);
        }

        if ( ll_mass < 100. && ll_mass > 80. ){

                cutFlow->SetBinContent(4, cutFlow->GetBinContent(4) + 1);
        }

        if ( pos_pt > 20. && neg_pt > 20. ){

                cutFlow->SetBinContent(5, cutFlow->GetBinContent(5) + 1);
        }
        
        info() << "llHAna: " << "ll_mass = " << ll_mass << endmsg;
        info() << "recoil_mass = " << recoil_mass << endmsg;
        
	tree->Fill();

    }
    return StatusCode::SUCCESS;

}

// Method to finalize your analysis
StatusCode llHAna::finalize() {
    // Finalization code goes here

    cutFlow->Scale(1./cutFlow->GetBinContent(1));
    rootFile->cd();
    tree->Write();
    cutFlow->Write();
    rootFile->Close();
    return GaudiAlgorithm::finalize();
}

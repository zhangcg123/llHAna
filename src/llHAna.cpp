#include "llHAna.h"

DECLARE_COMPONENT(llHAna)

// Constructor
llHAna::llHAna(const std::string& name, ISvcLocator* pSvcLocator)
    : GaudiAlgorithm(name, pSvcLocator) {
        declareProperty("MCParticleCollection", mcParticleCol, "Handle for the MCParticleCollection");
        declareProperty("ReconstructedParticleCollection", recParticleCol, "Handle for the ReconstructedParticleCollection");
        //declareProperty("MCTruthLinkCollection", mcTruthLinkCol, "Handle for the MCTruthLinkCollection");
    }

// Method to initialize your analysis
StatusCode llHAna::initialize() {
    // Initialization code goes here
    debug() << "Initializing llHAna" << endmsg;
    return GaudiAlgorithm::initialize();
}
// Method to execute your analysis
StatusCode llHAna::execute() {

    debug() << "Executing llHAna" << endmsg;
    // Get the MCParticleCollection from the event store
    const edm4hep::MCParticleCollection* mcParticleCollection = mcParticleCol.get();
    // Get the ReconstructedParticleCollection from the event store
    const edm4hep::ReconstructedParticleCollection* recParticleCollection = recParticleCol.get();
    // Get the MCTruthLinkCollection from the event store
    //const edm4hep::MCTruthLinkCollection* mcTruthLinkCollection = mcTruthLinkCol.get();
    
    int nElements = recParticleCollection->size();
    //debug() << "Reconstructed Particle Collection has " << nElements << " elements" << endmsg;
    
    std::vector<edm4hep::ReconstructedParticle> pos_particles; pos_particles.clear();
    std::vector<edm4hep::ReconstructedParticle> neg_particles; neg_particles.clear();

    for(int i = 0; i < nElements; ++i){

        const edm4hep::ReconstructedParticle recParticle = recParticleCollection->at(i);

        if ( recParticle.getEnergy() < 30.0 ) continue;

        if ( recParticle.getType() == 13 ) neg_particles.push_back(recParticle);
        if ( recParticle.getType() == -13 ) pos_particles.push_back(recParticle);

    }

    if ( pos_particles.size() != 1 || neg_particles.size() != 1 ){

        return StatusCode::SUCCESS;

    }else{

        edm4hep::ReconstructedParticle pos_particle = pos_particles.at(0);
        edm4hep::ReconstructedParticle neg_particle = neg_particles.at(0);

        double pos_energy = pos_particle.getEnergy();
        double neg_energy = neg_particle.getEnergy();

        double pos_px = pos_particle.getMomentum()[0];
        double pos_py = pos_particle.getMomentum()[1];
        double pos_pz = pos_particle.getMomentum()[2];

        double neg_px = neg_particle.getMomentum()[0];
        double neg_py = neg_particle.getMomentum()[1];
        double neg_pz = neg_particle.getMomentum()[2];

        double pos_p = sqrt( pos_px*pos_px + pos_py*pos_py + pos_pz*pos_pz );
        double neg_p = sqrt( neg_px*neg_px + neg_py*neg_py + neg_pz*neg_pz );

        double pos_pt = sqrt( pos_px*pos_px + pos_py*pos_py );
        double neg_pt = sqrt( neg_px*neg_px + neg_py*neg_py );

        double pos_theta = acos( pos_pz/pos_p );
        double neg_theta = acos( neg_pz/neg_p );

        double pos_phi = atan2( pos_py, pos_px );
        double neg_phi = atan2( neg_py, neg_px );

        double pos_mass = sqrt( pos_energy*pos_energy - pos_p*pos_p );
        double neg_mass = sqrt( neg_energy*neg_energy - neg_p*neg_p );

        double pos_eta = -log( tan( pos_theta/2.0 ) );
        double neg_eta = -log( tan( neg_theta/2.0 ) );

        double pos_rapidity = 0.5*log( (pos_energy+pos_pz)/(pos_energy-pos_pz) );
        double neg_rapidity = 0.5*log( (neg_energy+neg_pz)/(neg_energy-neg_pz) );

        TLorentzVector lep1, lep2;
        lep1.SetPxPyPzE( pos_px, pos_py, pos_pz, pos_energy );
        lep2.SetPxPyPzE( neg_px, neg_py, neg_pz, neg_energy );
        TLorentzVector ll = lep1 + lep2;

        double ll_mass = ll.M();
        double ll_energy = ll.E();
        double ll_px = ll.Px();
        double ll_py = ll.Py();
        double ll_pz = ll.Pz();
        double ll_p = ll.P();
        double ll_pt = ll.Pt();

        info() << "llHAna: " << "ll_mass = " << ll_mass << endmsg;

    }

    return StatusCode::SUCCESS;

}

// Method to finalize your analysis
StatusCode llHAna::finalize() {
    // Finalization code goes here
    return GaudiAlgorithm::finalize();
}

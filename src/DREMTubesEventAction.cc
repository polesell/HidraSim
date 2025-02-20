//**************************************************
// \file DREMTubesEventAction.cc
// \brief: Implementation of DREMTubesEventAction 
//         class
// \author: Lorenzo Pezzotti (CERN EP-SFT-sim)
//          @lopezzot
// \start date: 7 July 2021
//**************************************************

//Includers from project files
//
#include "DREMTubesEventAction.hh"
#include "DREMTubesRunAction.hh"
#include "DREMTubesDetectorConstruction.hh"
//Includers from Geant4
//
#include "g4root.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

//Includers from C++
//
#include <iomanip>
#include <vector>

//Define constructor
//
DREMTubesEventAction::DREMTubesEventAction()
    : G4UserEventAction(),
    EnergyScin(0.),
    EnergyCher(0.),
    NofCherDet(0),
    NofScinDet(0),
    EnergyTot(0.),
    PrimaryPDGID(0),
    PrimaryX(0),
    PrimaryY(0),
    PrimaryParticleEnergy(0.),
    EscapedEnergy(0.),
    EscapedEnergyl(0.),
    EscapedEnergyd(0.),
    PSEnergy(0.),
    VectorSignals(0.),
    VectorSignalsCher(0.),
    VecSPMT(0.),
    VecCPMT(0.),
    VecTowerE(0.) {
}

//Define de-constructor
//
DREMTubesEventAction::~DREMTubesEventAction() {}

//Define BeginOfEventAction() and EndOfEventAction() methods
//
void DREMTubesEventAction::BeginOfEventAction(const G4Event*) {  
    
    //Initialize data memebers at begin of each event
    //
    EnergyScin = 0.;
    EnergyCher = 0.;
    NofCherDet = 0;
    NofScinDet = 0;
    EnergyTot = 0.;
    PrimaryPDGID = 0;
    PrimaryX = 0;
    PrimaryY = 0;
    PrimaryParticleEnergy = 0.;
    EscapedEnergy = 0.;
    EscapedEnergyl = 0.;
    EscapedEnergyd = 0.;
    PSEnergy = 0.;

    VectorSignals.clear();
    VectorSignalsCher.clear();
    VecSPMT.clear();
    VecCPMT.clear();
    VecTowerE.clear();

    VectorSignals.assign(NoFibersTower*NoModulesSiPM, 0.);
    VectorSignalsCher.assign(NoFibersTower*NoModulesSiPM, 0.);
    VecSPMT.assign(NoModulesActive, 0.);
    VecCPMT.assign(NoModulesActive, 0.);
    VecTowerE.assign(NoModulesActive, 0.);

}

void DREMTubesEventAction::EndOfEventAction(const G4Event* ) {
 
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    //Add all p.e. in Scin and Cher fibers before calibration
    //
    for (auto& n : VectorSignals) NofScinDet += n;
    for (auto& n : VecSPMT) NofScinDet += n;
    for (auto& n : VectorSignalsCher) NofCherDet += n;
    for (auto& n : VecCPMT) NofCherDet += n;

    //Fill ntuple event by event
    //entries with vectors are automatically filled
    //
    analysisManager->FillNtupleDColumn(0, EnergyScin);
    analysisManager->FillNtupleDColumn(1, EnergyCher);
    analysisManager->FillNtupleDColumn(2, NofCherDet);
    analysisManager->FillNtupleDColumn(3, NofScinDet);
    analysisManager->FillNtupleDColumn(4, EnergyTot);
    analysisManager->FillNtupleDColumn(5, PrimaryParticleEnergy);
    analysisManager->FillNtupleIColumn(6, PrimaryPDGID);
    analysisManager->FillNtupleDColumn(7, EscapedEnergyl);
    analysisManager->FillNtupleDColumn(8, EscapedEnergyd);
    analysisManager->FillNtupleDColumn(9, PSEnergy);
    analysisManager->FillNtupleDColumn(10, PrimaryX);
    analysisManager->FillNtupleDColumn(11,PrimaryY);
    analysisManager->AddNtupleRow();
    //Vector entries in ntuple are automatically filled

}

//**************************************************

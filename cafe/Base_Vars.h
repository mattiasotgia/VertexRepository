#pragma once


// Standard stuff here
#include "sbnana/CAFAna/Core/Cut.h"
#include "sbnana/CAFAna/Core/ISyst.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnana/CAFAna/Core/Tree.h"
#include "sbnana/CAFAna/Core/Utilities.h"
#include "sbnana/CAFAna/Core/Var.h"

// Using Jacob's (the one) Larkin's from sbnana
#include "sbnana/SBNAna/Cuts/NumuCutsIcarus202401.h"
#include "sbnana/SBNAna/Vars/NumuVarsIcarus202401.h"

// Stuff to do variations right
#include "sbnana/CAFAna/Systs/SBNWeightSysts.h"
#include "sbnana/CAFAna/Systs/SBNOnOffSysts.h"
#include "sbnana/CAFAna/Systs/UniverseOracle.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <utility>

namespace ana 
{
    // ooOOoooOOoooOOoo Some thresholds for visibility ooOOoooOOoooOOoo
    const double VISIBILITY_THRESHOLD_P = 0.05; // Minimum energy for protons [GeV]
    const double VISIBILITY_THRESHOLD_PI = 0.025; // Minimum energy for pions (charged) [GeV]
    const int CALO_PLANE = 2; // Use collection plane for calorimetry

    const Var kSlcVX = SIMPLEVAR(vertex.x);
    const Var kSlcVY = SIMPLEVAR(vertex.y);
    const Var kSlcVZ = SIMPLEVAR(vertex.z);
    
    const Var kIndex = SIMPLEVAR(truth.index);
    const Var kTMatchEff = SIMPLEVAR(tmatch.eff);
    
    // ooOOoooOOoooOOoo Truth variables ooOOoooOOoooOOoo
    const TruthVar kIsCC = SIMPLETRUTHVAR(iscc);
    const TruthVar kPdg = SIMPLETRUTHVAR(pdg);
    const TruthVar kTrueE = SIMPLETRUTHVAR(E);

    /*
     * enum genie_interaction_mode_
     * {
     *     // Low part of the enum, used to encode mode
     *     kUnknownInteractionMode    =   -1,
     *     kQE                        =    0,
     *     kRes                       =    1,
     *     kDIS                       =    2,
     *     kCoh                       =    3,
     *     kCohElastic                =    4,
     *     kElectronScattering        =    5,
     *     kIMDAnnihilation           =    6,
     *     kInverseBetaDecay          =    7,
     *     kGlashowResonance          =    8,
     *     kAMNuGamma                 =    9,
     *     kMEC                       =   10,
     *     kDiffractive               =   11,
     *     kEM                        =   12,
     *     kWeakMix                   =   13
     * };
    */

    const TruthVar kGenieInteractionMode = SIMPLETRUTHVAR(genie_mode);

    const TruthVar kNumOf (unsigned int whatPdg, double thr = 0)
    {
        return TruthVar([&](const caf::SRTrueInteractionProxy *nu) -> double {
            double n{0};
            
            for (auto const prim: nu->prim)
            {
                const double cryostat{(prim.start.x > 0 ? 1 : 0)};
                if (std::isnan(cryostat) || cryostat < 0)
                    continue;
                if(std::abs(prim.pdg) == 2212 && prim.plane[cryostat][CALO_PLANE].visE > thr)
                    n++;
            }
            return n;
        });
    }

    const TruthVar kNumOfProtons = kNumOf(2212, VISIBILITY_THRESHOLD_P);
    const TruthVar kNumOfChargedPions = kNumOf(211, VISIBILITY_THRESHOLD_PI);
    const TruthVar kNumOfMuons = kNumOf(13);
    const TruthVar kNumOfElectrons = kNumOf(11);
    const TruthVar kNumOfNeutralPions = kNumOf(111);
    const TruthVar kNumOfPhotons = kNumOf(22);
}


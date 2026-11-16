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

    // Standard no-return value
    const Var kCounting ([](const caf::SRSliceProxy *slc) {
        return 1;
    });

    struct PlotDef
    {
        std::string name = "";
        std::string label = "";
        Var var = kCounting;
    }

    
}
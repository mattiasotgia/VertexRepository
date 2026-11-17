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

#include "Base_Vars.h"

namespace ana 
{
    bool kIsInFV(const caf::Proxy<caf::SRVector3D> *point) 
    {
        double x{point->x}, y{point->y}, z{point->z};

        if (std::isnan(x) || std::isnan(y) || std::isnan(z)) 
            return false;

        return (( ( x < -61.94 - 25 && x > -358.49 + 25 ) ||
            ( x >  61.94 + 25 && x <  358.49 - 25 )) &&
            ( ( y > -181.86 + 25 && y < 134.96 - 25 ) &&
            ( z > -894.95 + 30 && z < 894.95 - 50 ) ));
    }

    bool kIsInContained(const caf::Proxy<caf::SRVector3D> *point) 
    { 
        double x{point->x}, y{point->y}, z{point->z};

        if (std::isnan(x) || std::isnan(y) || std::isnan(z)) 
            return false;

        return (( ( x < -61.94 - 5 && x > -358.49 + 5 ) ||
            ( x >  61.94 + 5 && x <  358.49 - 5 )) &&
            ( ( y > -181.86 + 5 && y < 134.96 - 5 ) &&
            ( z > -894.95 + 5 && z < 894.95 - 5 ) ));
    }

    const TruthCut kVertexInFV ([](const caf::SRTrueInteractionProxy* nu) -> bool {
        return kIsInFV(&(nu->position));
    });
}


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

#define SHOW(...) std::cout << #__VA_ARGS__ << " : " << __VA_ARGS__ << '\n'

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
    };

    template<class T, bool is_reco_from_truth = false>
    const SpillMultiVar kGetIfPreselection(const T &what,
                                        const Cut cut = kNoCut,
                                        const TruthCut truth_cut = kNoTruthCut)
    {
        return SpillMultiVar([what, cut, truth_cut](const caf::SRSpillProxy *sr) -> std::vector<double> {
            std::vector<double> ret_v;

            if constexpr (!is_reco_from_truth)
            {
                if constexpr (std::is_same<T, Var>::value)
                {
                    for (auto const& slc : sr->slc)
                    {
                        if (!cut(&slc) || !truth_cut(&(slc.truth)))
                            continue;
                        ret_v.push_back(static_cast<double>(what(&slc)));
                    }
                }
                else if constexpr (std::is_same<T, TruthVar>::value)
                {
                    for (auto const& nu : sr->mc.nu)
                    {
                        if (!truth_cut(&nu))
                            continue;
                        ret_v.push_back(static_cast<double>(what(&nu)));
                    }
                }
                else
                {
                    static_assert(!std::is_same<T, T>::value, "T must be ana::Var or ana::TruthVar");
                }
            }
            else
            {
                if constexpr (std::is_same<T, TruthVar>::value)
                {
                    for (auto const& slc : sr->slc)
                    {
                        if (!cut(&slc) || !truth_cut(&(slc.truth)))
                            continue;
                        ret_v.push_back(static_cast<double>(what(&(slc.truth))));
                    }
                }
                else
                {
                    static_assert(is_reco_from_truth && !std::is_same<T, T>::value, 
                        "Given that is_reco_from_truth, T must be ana::TruthVar");
                }
            }
            
            return ret_v;
        });
    }
}
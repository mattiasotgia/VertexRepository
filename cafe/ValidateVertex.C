



#include "Analysis.h"

#include "Base_Cuts.h"
#include "Base_Vars.h"

#include "Commons.h"

#define GV(...)     ana::kGetIfPreselection<ana::Var>(__VA_ARGS__, ana::kNoCut, ana::kVertexInFV)
#define GTV(...)    ana::kGetIfPreselection<ana::TruthVar>(__VA_ARGS__, ana::kNoCut, ana::kVertexInFV)
#define GTV2V(...)  ana::kGetIfPreselection<ana::TruthVar, true>(__VA_ARGS__, ana::kNoCut, ana::kVertexInFV)

void ValidateVertex() 
{

    std::unique_ptr<TFile> writer(new TFile("../outputs/ValidateVertexWriter_RecoTruth.root", "RECREATE"));

    // Analysis::Analysis<ana::SpillMultiVar> TruthAna("Truth");

    // TruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_nue_stage1_caf_DL_v10_06_00_06p03_caf", "bnb_nue_DL");
    // TruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_numu_stage1_caf_DL_v10_06_00_06p03_caf", "bnb_numu_DL");
    // TruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_nue_stage1_caf_Standard_v10_06_00_06p03_caf", "bnb_nue_Standard");
    // TruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_numu_stage1_caf_Standard_v10_06_00_06p03_caf", "bnb_numu_Standard");

    // TruthAna.AddVariable("E", GTV(ana::kTrueE));
    // TruthAna.AddVariable("InFV", GTV(static_cast<ana::TruthVar>(ana::kVertexInFV)));
    // TruthAna.AddVariable("IsCC", GTV(ana::kIsCC));
    // TruthAna.AddVariable("Pdg", GTV(ana::kPdg));
    // TruthAna.AddVariable("GenieInteractionMode", GTV(ana::kGenieInteractionMode));
    // TruthAna.AddVariable("NumOfProtons", GTV(ana::kNumOfProtons));
    // TruthAna.AddVariable("NumOfChargedPions", GTV(ana::kNumOfChargedPions));
    // TruthAna.AddVariable("NumOfMuons", GTV(ana::kNumOfMuons));
    // TruthAna.AddVariable("NumOfElectrons", GTV(ana::kNumOfElectrons));
    // TruthAna.AddVariable("NumOfNeutralPions", GTV(ana::kNumOfNeutralPions));
    // TruthAna.AddVariable("NumOfPhotons", GTV(ana::kNumOfPhotons));
    
    // TruthAna.AddVariable("NuVertexX", GTV(ana::kNuVertexX));
    // TruthAna.AddVariable("NuVertexY", GTV(ana::kNuVertexY));
    // TruthAna.AddVariable("NuVertexZ", GTV(ana::kNuVertexZ));

    // TruthAna.Go();

    // TruthAna.WriteTo(writer.get());

    Analysis::Analysis<ana::SpillMultiVar> RecoTruthAna("RecoTruth");

    RecoTruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_nue_stage1_caf_DL_v10_06_00_06p03_caf", "bnb_nue_DL");
    RecoTruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_numu_stage1_caf_DL_v10_06_00_06p03_caf", "bnb_numu_DL");
    RecoTruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_nue_stage1_caf_Standard_v10_06_00_06p03_caf", "bnb_nue_Standard");
    RecoTruthAna.AddDataset("msotgia_mc_2026_pandora_DL_vertex_bnb_numu_stage1_caf_Standard_v10_06_00_06p03_caf", "bnb_numu_Standard");

    RecoTruthAna.AddVariable("E", GTV2V(ana::kTrueE));
    RecoTruthAna.AddVariable("InFV", GTV2V(static_cast<ana::TruthVar>(ana::kVertexInFV)));
    RecoTruthAna.AddVariable("IsCC", GTV2V(ana::kIsCC));
    RecoTruthAna.AddVariable("Pdg", GTV2V(ana::kPdg));
    RecoTruthAna.AddVariable("GenieInteractionMode", GTV2V(ana::kGenieInteractionMode));
    RecoTruthAna.AddVariable("NumOfProtons", GTV2V(ana::kNumOfProtons));
    RecoTruthAna.AddVariable("NumOfChargedPions", GTV2V(ana::kNumOfChargedPions));
    RecoTruthAna.AddVariable("NumOfMuons", GTV2V(ana::kNumOfMuons));
    RecoTruthAna.AddVariable("NumOfElectrons", GTV2V(ana::kNumOfElectrons));
    RecoTruthAna.AddVariable("NumOfNeutralPions", GTV2V(ana::kNumOfNeutralPions));
    RecoTruthAna.AddVariable("NumOfPhotons", GTV2V(ana::kNumOfPhotons));
    
    RecoTruthAna.AddVariable("NuVertexX", GTV2V(ana::kNuVertexX));
    RecoTruthAna.AddVariable("NuVertexY", GTV2V(ana::kNuVertexY));
    RecoTruthAna.AddVariable("NuVertexZ", GTV2V(ana::kNuVertexZ));

    RecoTruthAna.AddVariable("SlcVertexX", GV(ana::kSlcVertexX));
    RecoTruthAna.AddVariable("SlcVertexY", GV(ana::kSlcVertexY));
    RecoTruthAna.AddVariable("SlcVertexZ", GV(ana::kSlcVertexZ));

    RecoTruthAna.AddVariable("Index", GV(ana::kIndex));
    RecoTruthAna.AddVariable("TMatchEff", GV(ana::kTMatchEff));

    RecoTruthAna.Go();

    RecoTruthAna.WriteTo(writer.get());

    return;
}
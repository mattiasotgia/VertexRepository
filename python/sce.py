#!/usr/bin/env python3

'''
SCE studies python utility
Author: M Sotgia <msotgia@fnal.gov>
Date: Nov 3, 2026
'''

import click
import numpy 
import matplotlib
import matplotlib.pyplot as plt
import uproot

from ICARUSservices import ServiceManager
ServiceManager.setConfiguration("larg4_icarus_sce.fcl")

### BEGIN ###  stuff that one day will be in sbnalg/icarusalg  ##################
import LArSoftUtils
ServiceManager.ICARUSextraServices['SpaceChargeService'] = LArSoftUtils.SimpleServiceLoader(
  "spacecharge::SpaceChargeICARUS",
  interfaceClass="spacecharge::SpaceCharge",
  headers="icaruscode/TPC/Simulation/SpaceCharge/SpaceChargeICARUS.h",
  libraries="icaruscode_TPC_Simulation_SpaceCharge",
  )

import ROOT, ROOTutils
ROOT.Math.DisplacementVector3D[ROOT.Math.Cartesian3D["double"],ROOT.Math.GlobalCoordinateSystemTag].__str__ = ROOTutils.TVector3ToString
ROOT.Math.PositionVector3D[ROOT.Math.Cartesian3D["double"],ROOT.Math.GlobalCoordinateSystemTag].__str__ = ROOTutils.TVector3ToString
###  END  ###  stuff that one day will be in sbnalg/icarusalg  ##################

SpaceCharge = ServiceManager.get('SpaceChargeService')


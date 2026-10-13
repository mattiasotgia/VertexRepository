#!/usr/bin/env bash

eventTwoVertices="361 365 368 375 376 152 156 174 178 193 455 475 488 5 9 26 32 35 305 310 317 320 335 344 345 252 264 265 268 292 403 421 422 430 58 59 65 67 77 83 92 96 100 101 113 116 123 129 131 148 206 210 212 213 225 247"
eventThreeVertices="360 367 154 476 494 432 219"

# mkdir -p twoVerticesEvents
# cd twoVerticesEvents
# for i in $eventTwoVertices; do
#     lar -c testTraining_stage1.fcl -n1 -s /pnfs/icarus/scratch/users/msotgia/vertexTraining/v10_06_00_04p04/BNB/stageZero_1d/out/*/*/msotgia*NuMI* -e 1:0:$i
#     mv ICARUS_DLVertexTrain_Pass1_CaloHitListU.csv ICARUS_DLVertexTrain_Pass1_CaloHitListU-$i.csv
#     mv ICARUS_DLVertexTrain_Pass1_CaloHitListV.csv ICARUS_DLVertexTrain_Pass1_CaloHitListV-$i.csv
#     mv ICARUS_DLVertexTrain_Pass1_CaloHitListW.csv ICARUS_DLVertexTrain_Pass1_CaloHitListW-$i.csv
# done

# cd ..
mkdir -p threeVerticesEvents
cd threeVerticesEvents
for i in $eventThreeVertices; do
    lar -c testTraining_stage1.fcl -n1 -s /pnfs/icarus/scratch/users/msotgia/vertexTraining/v10_06_00_04p04/BNB/stageZero_1d/out/*/*/msotgia*NuMI* -e 1:0:$i
    mv ICARUS_DLVertexTrain_Pass1_CaloHitListU.csv ICARUS_DLVertexTrain_Pass1_CaloHitListU-$i.csv
    mv ICARUS_DLVertexTrain_Pass1_CaloHitListV.csv ICARUS_DLVertexTrain_Pass1_CaloHitListV-$i.csv
    mv ICARUS_DLVertexTrain_Pass1_CaloHitListW.csv ICARUS_DLVertexTrain_Pass1_CaloHitListW-$i.csv
done

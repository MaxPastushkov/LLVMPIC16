//===---- PIC16ISelDAGToDAG.h - A Dag to Dag Inst Selector for PIC16 ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the PIC16 target.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_PIC16_PIC16ISELDAGTODAG_H
#define LLVM_LIB_TARGET_PIC16_PIC16ISELDAGTODAG_H

#include "PIC16Subtarget.h"
#include "PIC16TargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {
class PIC16DAGToDAGISel : public SelectionDAGISel {
public:
  explicit PIC16DAGToDAGISel(PIC16TargetMachine &TM, CodeGenOptLevel OL)
      : SelectionDAGISel(TM, OL), Subtarget(nullptr) {}

  // Pass Name (SelectionDAGISel no longer has this virtual)
  // StringRef getPassName() const {
  //   return "CPU0 DAG->DAG Pattern Instruction Selection";
  // }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void Select(SDNode *Node) override;

#include "PIC16GenDAGISel.inc"

private:
  const PIC16Subtarget *Subtarget;
};

class PIC16DAGToDAGISelLegacy : public SelectionDAGISelLegacy {
public:
  static char ID;
  explicit PIC16DAGToDAGISelLegacy(PIC16TargetMachine &TM,
                                   CodeGenOptLevel OptLevel);
};
}

#endif // end LLVM_LIB_TARGET_PIC16_PIC16ISELDAGTODAG_H

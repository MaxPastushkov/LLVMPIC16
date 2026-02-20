//===-- PIC16ISelDAGToDAG.cpp - A Dag to Dag Inst Selector for PIC16 ------===//
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

#include "PIC16.h"
#include "PIC16ISelDAGToDAG.h"
#include "PIC16Subtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/IR/PassManager.h"
#include "llvm/PassRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "pic16-isel"

bool PIC16DAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget = &static_cast<const PIC16Subtarget &>(MF.getSubtarget());
  return SelectionDAGISel::runOnMachineFunction(MF);
}

void PIC16DAGToDAGISel::Select(SDNode *Node) {
  // If we have a custom node, we already have selected!
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(errs() << "== "; Node->dump(CurDAG); errs() << "\n");
    Node->setNodeId(-1);
    return;
  }

  // Instruction Selection not handled by the auto-generated tablegen selection
  // should be handled here.
  unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);

  switch(Opcode) {
  case ISD::Constant: {
    auto ConstNode = cast<ConstantSDNode>(Node);
    if (ConstNode->isZero()) {
      SDValue New = CurDAG->getCopyFromReg(CurDAG->getEntryNode(), SDLoc(Node),
                                           PIC16::X0, MVT::i32);
      ReplaceNode(Node, New.getNode());
      return;
    }
    break;
  }
  default: break;
  }

  // Select the default instruction
  SelectCode(Node);
}

#define PASS_NAME "PIC16 DAG->DAG Pattern Instruction Selection"

FunctionPass *llvm::createPIC16ISelDag(PIC16TargetMachine &TM,
                                       CodeGenOptLevel OptLevel) {
  return new PIC16DAGToDAGISelLegacy(TM, OptLevel);
}

char PIC16DAGToDAGISelLegacy::ID = 0;

PIC16DAGToDAGISelLegacy::PIC16DAGToDAGISelLegacy(PIC16TargetMachine &TM,
                                                 CodeGenOptLevel OptLevel)
    : SelectionDAGISelLegacy(
          ID, std::make_unique<PIC16DAGToDAGISel>(TM, OptLevel)) {}

INITIALIZE_PASS(PIC16DAGToDAGISelLegacy, DEBUG_TYPE, PASS_NAME, false, false)

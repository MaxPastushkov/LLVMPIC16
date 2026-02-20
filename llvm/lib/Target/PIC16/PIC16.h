//=== PIC16.h - Top-level interface for PIC16 representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM PIC16 backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_PIC16_PIC16_H
#define LLVM_LIB_TARGET_PIC16_PIC16_H

#include "MCTargetDesc/PIC16MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class FunctionPass;
  class PassRegistry;
  class PIC16TargetMachine;

  FunctionPass *createPIC16ISelDag(PIC16TargetMachine &TM,
                                   CodeGenOptLevel OptLevel);

  void initializePIC16DAGToDAGISelLegacyPass(PassRegistry &);

} // end namespace llvm;

#endif // end LLVM_LIB_TARGET_PIC16_PIC16_H

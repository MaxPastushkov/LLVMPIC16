//=== PIC16MachineFunctionInfo.h - Private data used for PIC16 ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the PIC16 specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_PIC16_PIC16MACHINEFUNCTION_H
#define LLVM_LIB_TARGET_PIC16_PIC16MACHINEFUNCTION_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// PIC16FunctionInfo - This class is derived from MachineFunction private
/// PIC16 target-specific information for each MachineFunction.
class PIC16FunctionInfo : public MachineFunctionInfo {
private:
  MachineFunction &MF;

public:
  PIC16FunctionInfo(MachineFunction &MF) : MF(MF) {}
};

} // end of namespace llvm

#endif // end LLVM_LIB_TARGET_PIC16_PIC16MACHINEFUNCTION_H

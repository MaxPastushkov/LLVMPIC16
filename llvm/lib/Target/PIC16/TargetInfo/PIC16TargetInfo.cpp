//===-- PIC16TargetInfo.cpp - PIC16 Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/PIC16TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getThePIC16Target() {
  static Target ThePIC16Target;
  return ThePIC16Target;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializePIC16TargetInfo() {
  RegisterTarget<Triple::pic16> X(getThePIC16Target(), "pic16",
                                  "32-bit RISC-V", "PIC16");
}

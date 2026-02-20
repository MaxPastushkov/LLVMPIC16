//===-- PIC16MCAsmInfo.h - PIC16 Asm Info ------------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the PIC16MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_PIC16_MCTARGETDESC_PIC16MCASMINFO_H
#define LLVM_LIB_TARGET_PIC16_MCTARGETDESC_PIC16MCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

class PIC16MCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit PIC16MCAsmInfo(const Triple &TheTriple);
};

} // namespace llvm

#endif // end LLVM_LIB_TARGET_PIC16_MCTARGETDESC_PIC16MCASMINFO_H

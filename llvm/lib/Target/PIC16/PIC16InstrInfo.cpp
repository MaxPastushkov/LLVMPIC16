//===-- PIC16InstrInfo.cpp - PIC16 Instruction Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the PIC16 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "PIC16InstrInfo.h"

#include "PIC16TargetMachine.h"
#include "PIC16MachineFunction.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

#define DEBUG_TYPE "pic16-instrinfo"

#define GET_INSTRINFO_CTOR_DTOR
#include "PIC16GenInstrInfo.inc"

PIC16InstrInfo::PIC16InstrInfo(const PIC16Subtarget &STI)
    : PIC16GenInstrInfo(STI, *STI.getRegisterInfo(),
                        PIC16::ADJCALLSTACKDOWN, PIC16::ADJCALLSTACKUP),
      Subtarget(STI)
{
}

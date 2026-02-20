//===-- PIC16RegisterInfo.cpp - PIC16 Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the PIC16 implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "PIC16RegisterInfo.h"
#include "PIC16Subtarget.h"
#include "llvm/Support/Debug.h"

#define GET_REGINFO_TARGET_DESC
#include "PIC16GenRegisterInfo.inc"

#define DEBUG_TYPE "pic16-reginfo"

using namespace llvm;

PIC16RegisterInfo::PIC16RegisterInfo(const PIC16Subtarget &ST)
  : PIC16GenRegisterInfo(PIC16::X1, /*DwarfFlavour*/0, /*EHFlavor*/0,
                         /*PC*/0), Subtarget(ST) {}

const MCPhysReg *
PIC16RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return PIC16_CalleeSavedRegs_SaveList;
}

const TargetRegisterClass *PIC16RegisterInfo::intRegClass(unsigned Size) const {
  return &PIC16::GPRRegClass;
}

const uint32_t *
PIC16RegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID) const {
  return PIC16_CalleeSavedRegs_RegMask;
}

BitVector PIC16RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  markSuperRegs(Reserved, PIC16::X0); // zero
  markSuperRegs(Reserved, PIC16::X2); // sp
  markSuperRegs(Reserved, PIC16::X3); // gp
  markSuperRegs(Reserved, PIC16::X4); // tp

  return Reserved;
}

bool PIC16RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj,
                                            unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  llvm_unreachable("Unsupported eliminateFrameIndex");
}

bool
PIC16RegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
PIC16RegisterInfo::requiresFrameIndexScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
PIC16RegisterInfo::requiresFrameIndexReplacementScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
PIC16RegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

Register PIC16RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? PIC16::X8 : PIC16::X2;
}


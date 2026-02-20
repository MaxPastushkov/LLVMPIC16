//===-- PIC16MCTargetDesc.cpp - PIC16 Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides PIC16 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "PIC16MCTargetDesc.h"
#include "PIC16InstPrinter.h"
#include "PIC16MCAsmInfo.h"
#include "TargetInfo/PIC16TargetInfo.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "PIC16GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "PIC16GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "PIC16GenRegisterInfo.inc"

static MCInstrInfo *createPIC16MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitPIC16MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createPIC16MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  return X;
}

static MCSubtargetInfo *
createPIC16MCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  std::string CPUName = CPU.str();
  if (CPUName.empty())
    CPUName = "generic";
  return createPIC16MCSubtargetInfoImpl(TT, CPUName, CPUName, FS);
}

static MCInstPrinter *createPIC16MCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new PIC16InstPrinter(MAI, MII, MRI);
}

static MCAsmInfo *createPIC16MCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new PIC16MCAsmInfo(TT);

  unsigned WP = MRI.getDwarfRegNum(PIC16::X2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, WP, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

extern "C" void LLVMInitializePIC16TargetMC() {
  for (Target *T : {&getThePIC16Target()}) {
    // Register the MC asm info.
    TargetRegistry::RegisterMCAsmInfo(*T, createPIC16MCAsmInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createPIC16MCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createPIC16MCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(*T, createPIC16MCSubtargetInfo);

    // Register the MCInstPrinter.
    TargetRegistry::RegisterMCInstPrinter(*T, createPIC16MCInstPrinter);
  }
}

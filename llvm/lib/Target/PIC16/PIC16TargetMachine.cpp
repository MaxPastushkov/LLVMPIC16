//===-- PIC16TargetMachine.cpp - Define TargetMachine for PIC16 -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about PIC16 target spec.
//
//===----------------------------------------------------------------------===//

#include "PIC16.h"
#include "PIC16TargetMachine.h"
#include "PIC16ISelDAGToDAG.h"
#include "PIC16Subtarget.h"
#include "PIC16TargetObjectFile.h"
#include "TargetInfo/PIC16TargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/PassRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializePIC16Target() {
  // Register the target.
  //- Little endian Target Machine
  RegisterTargetMachine<PIC16TargetMachine> X(getThePIC16Target());
  PassRegistry *PR = PassRegistry::getPassRegistry();
  initializePIC16DAGToDAGISelLegacyPass(*PR);
}

static std::string computeDataLayout() {
  std::string Ret = "";

  // Little endian
  Ret += "e";

  // ELF name mangling
  Ret += "-m:e";

  // 32-bit pointers, 32-bit aligned
  Ret += "-p:32:32";

  // 64-bit integers, 64 bit aligned
  Ret += "-i64:64";

  // 32-bit native integer width i.e register are 32-bit
  Ret += "-n32";

  // 128-bit natural stack alignment
  Ret += "-S128";

  return Ret;
}

static Reloc::Model getEffectiveRelocModel(std::optional<CodeModel::Model> CM,
                                           std::optional<Reloc::Model> RM) {
  if (!RM.has_value())
    return Reloc::Static;
  return *RM;
}

PIC16TargetMachine::PIC16TargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL,
                                       bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(), TT, CPU, FS, Options,
                              getEffectiveRelocModel(CM, RM),
                              getEffectiveCodeModel(CM, CodeModel::Medium), OL),
      TLOF(std::make_unique<PIC16TargetObjectFile>()) {
  // initAsmInfo will display features by llc -march=pic16 on 3.7
  initAsmInfo();
}

const PIC16Subtarget *
PIC16TargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU = !CPUAttr.hasAttribute(Attribute::None)
                        ? CPUAttr.getValueAsString().str()
                        : TargetCPU;
  std::string FS = !FSAttr.hasAttribute(Attribute::None)
                       ? FSAttr.getValueAsString().str()
                       : TargetFS;

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {
    // This needs to be done before we create a new subtarget since any
    // creation will depend on the TM and the code generation flags on the
    // function that reside in TargetOptions.
    resetTargetOptions(F);
    I = std::make_unique<PIC16Subtarget>(TargetTriple, CPU, FS, *this);
  }
  return I.get();
}

namespace {
class PIC16PassConfig : public TargetPassConfig {
public:
  PIC16PassConfig(PIC16TargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  PIC16TargetMachine &getPIC16TargetMachine() const {
    return getTM<PIC16TargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
}

TargetPassConfig *PIC16TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new PIC16PassConfig(*this, PM);
}

// Install an instruction selector pass using
// the ISelDag to gen PIC16 code.
bool PIC16PassConfig::addInstSelector() {
  addPass(createPIC16ISelDag(getPIC16TargetMachine(), getOptLevel()));
  return false;
}

// Implemented by targets that want to run passes immediately before
// machine code is emitted. return true if -print-machineinstrs should
// print out the code after the passes.
void PIC16PassConfig::addPreEmitPass() {
}

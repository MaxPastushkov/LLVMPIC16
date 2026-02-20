//=== PIC16.td - Describe the PIC16 Target Machine ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Top tablegen file that pulls in code from the LLVM framework along with
// code specific to this target.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions, Register information, etc
//===----------------------------------------------------------------------===//

include "PIC16Schedule.td"
include "PIC16RegisterInfo.td"
include "PIC16CallingConv.td"
include "PIC16InstrInfo.td"

def PIC16InstrInfo : InstrInfo;

defm : RemapAllTargetPseudoPointerOperands<GPR>;

//===----------------------------------------------------------------------===//
// PIC16 processors supported
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic",  NoSchedModel, []>;

//===----------------------------------------------------------------------===//
// PIC16 Target declaration
//===----------------------------------------------------------------------===//

def PIC16 : Target {
  let InstructionSet = PIC16InstrInfo;
}

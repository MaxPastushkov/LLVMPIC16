add_llvm_component_group(PIC16)

set(LLVM_TARGET_DEFINITIONS PIC16.td)

tablegen(LLVM PIC16GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM PIC16GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM PIC16GenCodeEmitter.inc -gen-emitter)
tablegen(LLVM PIC16GenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM PIC16GenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM PIC16GenDAGISel.inc -gen-dag-isel)
tablegen(LLVM PIC16GenCallingConv.inc -gen-callingconv)
tablegen(LLVM PIC16GenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM PIC16GenMCPseudoLowering.inc -gen-pseudo-lowering)

# PIC16CommonTableGen must be defined
add_public_tablegen_target(PIC16CommonTableGen)

# PIC16CodeGen should match with LLVMBuild.txt PIC16CodeGen
add_llvm_target(PIC16CodeGen
  PIC16AsmPrinter.cpp
  PIC16FrameLowering.cpp
  PIC16InstrInfo.cpp
  PIC16ISelLowering.cpp
  PIC16RegisterInfo.cpp
  PIC16Subtarget.cpp
  PIC16TargetObjectFile.cpp
  PIC16ISelDAGToDAG.cpp
  PIC16TargetMachine.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  MC
  PIC16Desc
  PIC16Info
  SelectionDAG
  Support
  Target
  TargetParser

  ADD_TO_COMPONENT
  PIC16
)

# Should match with "subdirectories =  MCTargetDesc TargetInfo" in LLVMBuild.txt
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)

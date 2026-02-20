add_llvm_component_library(LLVMPIC16Info
  PIC16TargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  PIC16
)

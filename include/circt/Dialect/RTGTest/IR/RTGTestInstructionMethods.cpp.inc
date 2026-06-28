/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* RTG Instruction Method Implementations                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTGTest.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

bool ADD::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool ADD::isDestinationRegister(unsigned index) {
  return index == 0;
}

void ADD::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "add ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void ADD::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 0));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool ADDI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool ADDI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void ADDI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "addi ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
}

void ADDI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 0));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool AND::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool AND::isDestinationRegister(unsigned index) {
  return index == 0;
}

void AND::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "and ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void AND::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 7));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool ANDI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool ANDI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void ANDI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "andi ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
}

void ANDI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 7));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool AUIPC::isSourceRegister(unsigned index) {
  return false;
}

bool AUIPC::isDestinationRegister(unsigned index) {
  return index == 0;
}

void AUIPC::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "auipc ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void AUIPC::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(20, 12));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 23));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool BEQ::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool BEQ::isDestinationRegister(unsigned index) {
  return false;
}

void BEQ::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "beq ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void BEQ::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(1, 12));
  binary = binary.concat(imm.extractBits(6, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 0));
  binary = binary.concat(imm.extractBits(4, 1));
  binary = binary.concat(imm.extractBits(1, 11));
  binary = binary.concat(llvm::APInt(7, 99));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool BGE::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool BGE::isDestinationRegister(unsigned index) {
  return false;
}

void BGE::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "bge ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void BGE::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(1, 12));
  binary = binary.concat(imm.extractBits(6, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 5));
  binary = binary.concat(imm.extractBits(4, 1));
  binary = binary.concat(imm.extractBits(1, 11));
  binary = binary.concat(llvm::APInt(7, 99));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool BGEU::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool BGEU::isDestinationRegister(unsigned index) {
  return false;
}

void BGEU::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "bgeu ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void BGEU::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(1, 12));
  binary = binary.concat(imm.extractBits(6, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 7));
  binary = binary.concat(imm.extractBits(4, 1));
  binary = binary.concat(imm.extractBits(1, 11));
  binary = binary.concat(llvm::APInt(7, 99));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool BLT::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool BLT::isDestinationRegister(unsigned index) {
  return false;
}

void BLT::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "blt ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void BLT::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(1, 12));
  binary = binary.concat(imm.extractBits(6, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 4));
  binary = binary.concat(imm.extractBits(4, 1));
  binary = binary.concat(imm.extractBits(1, 11));
  binary = binary.concat(llvm::APInt(7, 99));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool BLTU::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool BLTU::isDestinationRegister(unsigned index) {
  return false;
}

void BLTU::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "bltu ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void BLTU::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(1, 12));
  binary = binary.concat(imm.extractBits(6, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 6));
  binary = binary.concat(imm.extractBits(4, 1));
  binary = binary.concat(imm.extractBits(1, 11));
  binary = binary.concat(llvm::APInt(7, 99));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool BNE::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool BNE::isDestinationRegister(unsigned index) {
  return false;
}

void BNE::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "bne ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void BNE::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(1, 12));
  binary = binary.concat(imm.extractBits(6, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 1));
  binary = binary.concat(imm.extractBits(4, 1));
  binary = binary.concat(imm.extractBits(1, 11));
  binary = binary.concat(llvm::APInt(7, 99));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool EBREAKOp::isSourceRegister(unsigned index) {
  return false;
}

bool EBREAKOp::isDestinationRegister(unsigned index) {
  return false;
}

void EBREAKOp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "ebreak";
}

void EBREAKOp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(12, 1));
  binary = binary.concat(llvm::APInt(13, 0));
  binary = binary.concat(llvm::APInt(7, 115));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool ECALLOp::isSourceRegister(unsigned index) {
  return false;
}

bool ECALLOp::isDestinationRegister(unsigned index) {
  return false;
}

void ECALLOp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "ecall";
}

void ECALLOp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(12, 0));
  binary = binary.concat(llvm::APInt(13, 0));
  binary = binary.concat(llvm::APInt(7, 115));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool JAL::isSourceRegister(unsigned index) {
  return false;
}

bool JAL::isDestinationRegister(unsigned index) {
  return index == 0;
}

void JAL::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "jal ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringSigned(strBuf);
      os << strBuf;
    }
  }
}

void JAL::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(1, 20));
  binary = binary.concat(imm.extractBits(10, 1));
  binary = binary.concat(imm.extractBits(1, 11));
  binary = binary.concat(imm.extractBits(8, 12));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 111));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool JALROp::isSourceRegister(unsigned index) {
  return index == 1;
}

bool JALROp::isDestinationRegister(unsigned index) {
  return index == 0;
}

void JALROp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "jalr ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ")";
}

void JALROp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 0));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 103));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool LA::isSourceRegister(unsigned index) {
  return false;
}

bool LA::isDestinationRegister(unsigned index) {
  return index == 0;
}

void LA::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "la ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getMem())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getMem())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void LA::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(false && "binary not supported");
}

bool LBOp::isSourceRegister(unsigned index) {
  return index == 1;
}

bool LBOp::isDestinationRegister(unsigned index) {
  return index == 0;
}

void LBOp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "lb ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ")";
}

void LBOp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 0));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 3));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool LBUOp::isSourceRegister(unsigned index) {
  return index == 1;
}

bool LBUOp::isDestinationRegister(unsigned index) {
  return index == 0;
}

void LBUOp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "lbu ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ")";
}

void LBUOp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 4));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 3));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool LHOp::isSourceRegister(unsigned index) {
  return index == 1;
}

bool LHOp::isDestinationRegister(unsigned index) {
  return index == 0;
}

void LHOp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "lh ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ")";
}

void LHOp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 1));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 3));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool LHUOp::isSourceRegister(unsigned index) {
  return index == 1;
}

bool LHUOp::isDestinationRegister(unsigned index) {
  return index == 0;
}

void LHUOp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "lhu ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ")";
}

void LHUOp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 5));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 3));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool LUI::isSourceRegister(unsigned index) {
  return false;
}

bool LUI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void LUI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "lui ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  if (auto label = ::llvm::dyn_cast<::circt::rtg::LabelAttr>(adaptor.getImm())) {
    os << label.getName();
  } else if (auto imm = ::llvm::dyn_cast<::circt::rtg::ImmediateAttr>(adaptor.getImm())) {
    {
      ::llvm::SmallVector<char> strBuf;
      imm.getValue().toStringUnsigned(strBuf);
      os << strBuf;
    }
  }
}

void LUI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  assert(!::llvm::isa<::circt::rtg::LabelAttr>(adaptor.getImm()) && "labels not supported in binary format");
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(20, 12));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 55));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool LWOp::isSourceRegister(unsigned index) {
  return index == 1;
}

bool LWOp::isDestinationRegister(unsigned index) {
  return index == 0;
}

void LWOp::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "lw ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ")";
}

void LWOp::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 2));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 3));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool OR::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool OR::isDestinationRegister(unsigned index) {
  return index == 0;
}

void OR::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "or ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void OR::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 6));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool ORI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool ORI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void ORI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "ori ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
}

void ORI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 6));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SB::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool SB::isDestinationRegister(unsigned index) {
  return false;
}

void SB::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sb ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ")";
}

void SB::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(7, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 0));
  binary = binary.concat(imm.extractBits(5, 0));
  binary = binary.concat(llvm::APInt(7, 35));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SH::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool SH::isDestinationRegister(unsigned index) {
  return false;
}

void SH::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sh ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ")";
}

void SH::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(7, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 1));
  binary = binary.concat(imm.extractBits(5, 0));
  binary = binary.concat(llvm::APInt(7, 35));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SLL::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool SLL::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SLL::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sll ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void SLL::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 1));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SLLI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool SLLI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SLLI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "slli ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringUnsigned(strBuf);
    os << strBuf;
  }
}

void SLLI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 1));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SLT::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool SLT::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SLT::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "slt ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void SLT::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 2));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SLTI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool SLTI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SLTI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "slti ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
}

void SLTI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 2));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SLTIU::isSourceRegister(unsigned index) {
  return index == 1;
}

bool SLTIU::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SLTIU::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sltiu ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
}

void SLTIU::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 3));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SLTU::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool SLTU::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SLTU::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sltu ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void SLTU::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 3));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SRA::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool SRA::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SRA::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sra ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void SRA::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 32));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 5));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SRAI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool SRAI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SRAI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "srai ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringUnsigned(strBuf);
    os << strBuf;
  }
}

void SRAI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 32));
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 5));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SRL::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool SRL::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SRL::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "srl ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void SRL::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 5));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SRLI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool SRLI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SRLI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "srli ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringUnsigned(strBuf);
    os << strBuf;
  }
}

void SRLI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 5));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SUB::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool SUB::isDestinationRegister(unsigned index) {
  return index == 0;
}

void SUB::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sub ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void SUB::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 32));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 0));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool SW::isSourceRegister(unsigned index) {
  return index == 0 || index == 1;
}

bool SW::isDestinationRegister(unsigned index) {
  return false;
}

void SW::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "sw ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
  os << "(";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
  os << ")";
}

void SW::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm.extractBits(7, 5));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 2));
  binary = binary.concat(imm.extractBits(5, 0));
  binary = binary.concat(llvm::APInt(7, 35));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool XOR::isSourceRegister(unsigned index) {
  return index == 1 || index == 2;
}

bool XOR::isDestinationRegister(unsigned index) {
  return index == 0;
}

void XOR::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "xor ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getRegisterAssembly();
}

void XOR::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt rs2 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs2()).getClassIndex());
  ::llvm::APInt rs1 = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs1()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(llvm::APInt(7, 0));
  binary = binary.concat(rs2);
  binary = binary.concat(rs1);
  binary = binary.concat(llvm::APInt(3, 4));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 51));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}

bool XORI::isSourceRegister(unsigned index) {
  return index == 1;
}

bool XORI::isDestinationRegister(unsigned index) {
  return index == 0;
}

void XORI::printInstructionAssembly(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  os << "xori ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getRegisterAssembly();
  os << ", ";
  os << ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getRegisterAssembly();
  os << ", ";
  {
    ::llvm::SmallVector<char> strBuf;
    ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue().toStringSigned(strBuf);
    os << strBuf;
  }
}

void XORI::printInstructionBinary(llvm::raw_ostream &os, FoldAdaptor adaptor) {
  ::llvm::APInt imm = ::llvm::cast<::circt::rtg::ImmediateAttr>(adaptor.getImm()).getValue();
  ::llvm::APInt rs = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRs()).getClassIndex());
  ::llvm::APInt rd = ::llvm::APInt(5, ::llvm::cast<::circt::rtg::RegisterAttrInterface>(adaptor.getRd()).getClassIndex());

  ::llvm::APInt binary = llvm::APInt::getZero(0);
  binary = binary.concat(imm);
  binary = binary.concat(rs);
  binary = binary.concat(llvm::APInt(3, 4));
  binary = binary.concat(rd);
  binary = binary.concat(llvm::APInt(7, 19));

  ::llvm::SmallVector<char> str;
  binary.toStringUnsigned(str, 16);
  os << str;
}


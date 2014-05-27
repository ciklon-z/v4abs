#include "VExprIdentifier.h"
#include "exception/Exception.h" 
#include "VExprExpression.h"
#include "VExprRegLvalue.h"
#include "VExprNetLvalue.h"

VExprIdentifierHandle vexpr_identifier_mk_single_identifier(std::string identifier, size_t size) {
    return VExprIdentifierHandle(VExprIdentifier(VExprSingleIdentifierHandle(VExprSingleIdentifier(identifier, size))));
}

VExprIdentifierHandle vexpr_identifier_mk_hier_identifier(std::string prefix, std::string identifier, size_t size) {
    return VExprIdentifierHandle(VExprIdentifier(VExprHierIdentifierHandle(VExprHierIdentifier(prefix, identifier, size))));
}

VExprIdentifierHandle vexpr_identifier_mk_hier_identifier(std::vector<std::string> vecPrefix, std::string identifier, size_t size) {
    return VExprIdentifierHandle(VExprIdentifier(VExprHierIdentifierHandle(VExprHierIdentifier(vecPrefix, identifier, size))));
}



VExprIdentifierInterface::~VExprIdentifierInterface() { }

std::string VExprIdentifierInterface::getName() const
  { throw NotImplementedException(); }
    
size_t VExprIdentifierInterface::getSize() const
  { throw NotImplementedException(); }

std::string VExprIdentifierInterface::getString() const
  { throw NotImplementedException(); }

VExprIdentifier::VExprIdentifier(VExprSingleIdentifierHandle pSingleIdentifier)
  : _pInterface(shared_ptr_cast<VExprIdentifierInterface>(pSingleIdentifier))
  , _pSingleIdentifier(pSingleIdentifier)
  { }

VExprIdentifier::VExprIdentifier(VExprHierIdentifierHandle pHierIdentifier)
  : _pInterface(shared_ptr_cast<VExprIdentifierInterface>(pHierIdentifier))
  , _pHierIdentifier(pHierIdentifier)
  { }
    
VExprSingleIdentifierHandle 
VExprIdentifier::getSingleIdentifierHandle() const
  { return _pSingleIdentifier; }
    
VExprHierIdentifierHandle 
VExprIdentifier::getHierIdentifierHandle() const  { return _pHierIdentifier; }

size_t VExprIdentifier::getSize() const {
    return _pInterface->getSize();
}

std::string VExprIdentifier::getString() const
  { return _pInterface->getString(); }
    
VExprExpressionHandle VExprIdentifier::toExpressionHandle() const {
    return VExprExpressionHandle(VExprExpression(VExprPrimaryHandle(VExprPrimary(VExprIdentifierHandle(*this)))));
}
    
VExprRegLvalueHandle VExprIdentifier::toRegLvalueHandle() const {
    return VExprRegLvalueHandle(VExprRegLvalue(VExprIdentifierHandle(*this)));
}

VExprNetLvalueHandle VExprIdentifier::toNetLvalueHandle() const {
    return VExprNetLvalueHandle(VExprNetLvalue(VExprIdentifierHandle(*this)));
}

VExprSingleIdentifier::VExprSingleIdentifier(std::string identifier, size_t size)
  : _identifier(identifier)
  , _size(size)
  { }

std::string VExprSingleIdentifier::getName() const
  { return _identifier; }
size_t VExprSingleIdentifier::getSize() const
  { return _size; }
std::string VExprSingleIdentifier::getString() const
  { return getName(); }

VExprHierIdentifier::VExprHierIdentifier(std::string prefix, std::string identifier, size_t size) {
    _vecPrefix.push_back(prefix);
    _identifier = identifier;
    _size = size;
}

VExprHierIdentifier::VExprHierIdentifier(std::vector<std::string> vecPrefix, std::string identifier, size_t size) {
    _vecPrefix = vecPrefix;
    _identifier = identifier;
    _size = size;
}
    
VExprHierIdentifier::VExprHierIdentifier(std::vector<std::string> vecAll, size_t size) {
    assert(vecAll.size() >= 1);
    for (size_t i = 0; i < vecAll.size()-1; ++i)
        _vecPrefix.push_back(vecAll[i]);
    _identifier = vecAll[vecAll.size()-1];
    _size = size;
}

std::string VExprHierIdentifier::getName() const {
    if (_vecPrefix.size() == 0)
        return _identifier;

    std::string s = _vecPrefix[0];
    for (unsigned int i = 1; i < _vecPrefix.size(); ++i)
        s = s + "." + _vecPrefix[i];
    s = s + "." + _identifier;
    return s;
}

size_t VExprHierIdentifier::getSize() const {
    return _size;
}

std::string VExprHierIdentifier::getString() const {
    return getName();
}

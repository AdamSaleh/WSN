//
// Generated file, do not edit! Created by opp_msgc 4.2 from messages/StaticNetwPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "StaticNetwPkt_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(StaticNetwPkt);

StaticNetwPkt::StaticNetwPkt(const char *name, int kind) : NetwPkt(name,kind)
{
    this->nbHops_var = 0;
}

StaticNetwPkt::StaticNetwPkt(const StaticNetwPkt& other) : NetwPkt(other)
{
    copy(other);
}

StaticNetwPkt::~StaticNetwPkt()
{
}

StaticNetwPkt& StaticNetwPkt::operator=(const StaticNetwPkt& other)
{
    if (this==&other) return *this;
    NetwPkt::operator=(other);
    copy(other);
    return *this;
}

void StaticNetwPkt::copy(const StaticNetwPkt& other)
{
    this->finalDestAddr_var = other.finalDestAddr_var;
    this->initialSrcAddr_var = other.initialSrcAddr_var;
    this->nbHops_var = other.nbHops_var;
}

void StaticNetwPkt::parsimPack(cCommBuffer *b)
{
    NetwPkt::parsimPack(b);
    doPacking(b,this->finalDestAddr_var);
    doPacking(b,this->initialSrcAddr_var);
    doPacking(b,this->nbHops_var);
}

void StaticNetwPkt::parsimUnpack(cCommBuffer *b)
{
    NetwPkt::parsimUnpack(b);
    doUnpacking(b,this->finalDestAddr_var);
    doUnpacking(b,this->initialSrcAddr_var);
    doUnpacking(b,this->nbHops_var);
}

LAddress::L3Type& StaticNetwPkt::getFinalDestAddr()
{
    return finalDestAddr_var;
}

void StaticNetwPkt::setFinalDestAddr(const LAddress::L3Type& finalDestAddr)
{
    this->finalDestAddr_var = finalDestAddr;
}

LAddress::L3Type& StaticNetwPkt::getInitialSrcAddr()
{
    return initialSrcAddr_var;
}

void StaticNetwPkt::setInitialSrcAddr(const LAddress::L3Type& initialSrcAddr)
{
    this->initialSrcAddr_var = initialSrcAddr;
}

int StaticNetwPkt::getNbHops() const
{
    return nbHops_var;
}

void StaticNetwPkt::setNbHops(int nbHops)
{
    this->nbHops_var = nbHops;
}

class StaticNetwPktDescriptor : public cClassDescriptor
{
  public:
    StaticNetwPktDescriptor();
    virtual ~StaticNetwPktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(StaticNetwPktDescriptor);

StaticNetwPktDescriptor::StaticNetwPktDescriptor() : cClassDescriptor("StaticNetwPkt", "NetwPkt")
{
}

StaticNetwPktDescriptor::~StaticNetwPktDescriptor()
{
}

bool StaticNetwPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<StaticNetwPkt *>(obj)!=NULL;
}

const char *StaticNetwPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int StaticNetwPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int StaticNetwPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *StaticNetwPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "finalDestAddr",
        "initialSrcAddr",
        "nbHops",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int StaticNetwPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "finalDestAddr")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "initialSrcAddr")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nbHops")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *StaticNetwPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "LAddress::L3Type",
        "LAddress::L3Type",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *StaticNetwPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int StaticNetwPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    StaticNetwPkt *pp = (StaticNetwPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string StaticNetwPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    StaticNetwPkt *pp = (StaticNetwPkt *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFinalDestAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getInitialSrcAddr(); return out.str();}
        case 2: return long2string(pp->getNbHops());
        default: return "";
    }
}

bool StaticNetwPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    StaticNetwPkt *pp = (StaticNetwPkt *)object; (void)pp;
    switch (field) {
        case 2: pp->setNbHops(string2long(value)); return true;
        default: return false;
    }
}

const char *StaticNetwPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "LAddress::L3Type",
        "LAddress::L3Type",
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *StaticNetwPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    StaticNetwPkt *pp = (StaticNetwPkt *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFinalDestAddr()); break;
        case 1: return (void *)(&pp->getInitialSrcAddr()); break;
        default: return NULL;
    }
}



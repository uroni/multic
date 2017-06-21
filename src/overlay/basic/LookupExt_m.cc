//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/datatest/../../overlay/basic/LookupExt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "LookupExt_m.h"

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




Register_Class(LookupExt);

LookupExt::LookupExt(const char *name, int kind) : cPacket(name,kind)
{
    this->hops_var = 0;
    pathNodes_arraysize = 0;
    this->pathNodes_var = 0;
    this->sequence_id_var = 0;
    this->senttime_var = 0;
}

LookupExt::LookupExt(const LookupExt& other) : cPacket()
{
    setName(other.getName());
    pathNodes_arraysize = 0;
    this->pathNodes_var = 0;
    operator=(other);
}

LookupExt::~LookupExt()
{
    delete [] pathNodes_var;
}

LookupExt& LookupExt::operator=(const LookupExt& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->hops_var = other.hops_var;
    delete [] this->pathNodes_var;
    this->pathNodes_var = (other.pathNodes_arraysize==0) ? NULL : new int[other.pathNodes_arraysize];
    pathNodes_arraysize = other.pathNodes_arraysize;
    for (unsigned int i=0; i<pathNodes_arraysize; i++)
        this->pathNodes_var[i] = other.pathNodes_var[i];
    this->sequence_id_var = other.sequence_id_var;
    this->senttime_var = other.senttime_var;
    return *this;
}

void LookupExt::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->hops_var);
    b->pack(pathNodes_arraysize);
    doPacking(b,this->pathNodes_var,pathNodes_arraysize);
    doPacking(b,this->sequence_id_var);
    doPacking(b,this->senttime_var);
}

void LookupExt::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->hops_var);
    delete [] this->pathNodes_var;
    b->unpack(pathNodes_arraysize);
    if (pathNodes_arraysize==0) {
        this->pathNodes_var = 0;
    } else {
        this->pathNodes_var = new int[pathNodes_arraysize];
        doUnpacking(b,this->pathNodes_var,pathNodes_arraysize);
    }
    doUnpacking(b,this->sequence_id_var);
    doUnpacking(b,this->senttime_var);
}

int LookupExt::getHops() const
{
    return hops_var;
}

void LookupExt::setHops(int hops_var)
{
    this->hops_var = hops_var;
}

void LookupExt::setPathNodesArraySize(unsigned int size)
{
    int *pathNodes_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = pathNodes_arraysize < size ? pathNodes_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        pathNodes_var2[i] = this->pathNodes_var[i];
    for (unsigned int i=sz; i<size; i++)
        pathNodes_var2[i] = 0;
    pathNodes_arraysize = size;
    delete [] this->pathNodes_var;
    this->pathNodes_var = pathNodes_var2;
}

unsigned int LookupExt::getPathNodesArraySize() const
{
    return pathNodes_arraysize;
}

int LookupExt::getPathNodes(unsigned int k) const
{
    if (k>=pathNodes_arraysize) throw cRuntimeError("Array of size %d indexed by %d", pathNodes_arraysize, k);
    return pathNodes_var[k];
}

void LookupExt::setPathNodes(unsigned int k, int pathNodes_var)
{
    if (k>=pathNodes_arraysize) throw cRuntimeError("Array of size %d indexed by %d", pathNodes_arraysize, k);
    this->pathNodes_var[k]=pathNodes_var;
}

int LookupExt::getSequence_id() const
{
    return sequence_id_var;
}

void LookupExt::setSequence_id(int sequence_id_var)
{
    this->sequence_id_var = sequence_id_var;
}

simtime_t LookupExt::getSenttime() const
{
    return senttime_var;
}

void LookupExt::setSenttime(simtime_t senttime_var)
{
    this->senttime_var = senttime_var;
}

class LookupExtDescriptor : public cClassDescriptor
{
  public:
    LookupExtDescriptor();
    virtual ~LookupExtDescriptor();

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

Register_ClassDescriptor(LookupExtDescriptor);

LookupExtDescriptor::LookupExtDescriptor() : cClassDescriptor("LookupExt", "cPacket")
{
}

LookupExtDescriptor::~LookupExtDescriptor()
{
}

bool LookupExtDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<LookupExt *>(obj)!=NULL;
}

const char *LookupExtDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LookupExtDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int LookupExtDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *LookupExtDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "hops",
        "pathNodes",
        "sequence_id",
        "senttime",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int LookupExtDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pathNodes")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequence_id")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senttime")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *LookupExtDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *LookupExtDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int LookupExtDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LookupExt *pp = (LookupExt *)object; (void)pp;
    switch (field) {
        case 1: return pp->getPathNodesArraySize();
        default: return 0;
    }
}

std::string LookupExtDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    LookupExt *pp = (LookupExt *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHops());
        case 1: return long2string(pp->getPathNodes(i));
        case 2: return long2string(pp->getSequence_id());
        case 3: return double2string(pp->getSenttime());
        default: return "";
    }
}

bool LookupExtDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LookupExt *pp = (LookupExt *)object; (void)pp;
    switch (field) {
        case 0: pp->setHops(string2long(value)); return true;
        case 1: pp->setPathNodes(i,string2long(value)); return true;
        case 2: pp->setSequence_id(string2long(value)); return true;
        case 3: pp->setSenttime(string2double(value)); return true;
        default: return false;
    }
}

const char *LookupExtDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *LookupExtDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LookupExt *pp = (LookupExt *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}



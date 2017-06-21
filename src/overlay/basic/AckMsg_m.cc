//
// Generated file, do not edit! Created by opp_msgc 4.1 from overlay/basic/AckMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "AckMsg_m.h"

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




Register_Class(AckMsg);

AckMsg::AckMsg(const char *name, int kind) : BaseOverlayMessage(name,kind)
{
    this->hops_var = 0;
    this->seq_id_var = 0;
    pathNodes_arraysize = 0;
    this->pathNodes_var = 0;
    this->datasenttime_var = 0;
}

AckMsg::AckMsg(const AckMsg& other) : BaseOverlayMessage()
{
    setName(other.getName());
    pathNodes_arraysize = 0;
    this->pathNodes_var = 0;
    operator=(other);
}

AckMsg::~AckMsg()
{
    delete [] pathNodes_var;
}

AckMsg& AckMsg::operator=(const AckMsg& other)
{
    if (this==&other) return *this;
    BaseOverlayMessage::operator=(other);
    this->hops_var = other.hops_var;
    this->seq_id_var = other.seq_id_var;
    delete [] this->pathNodes_var;
    this->pathNodes_var = (other.pathNodes_arraysize==0) ? NULL : new int[other.pathNodes_arraysize];
    pathNodes_arraysize = other.pathNodes_arraysize;
    for (unsigned int i=0; i<pathNodes_arraysize; i++)
        this->pathNodes_var[i] = other.pathNodes_var[i];
    this->datasenttime_var = other.datasenttime_var;
    return *this;
}

void AckMsg::parsimPack(cCommBuffer *b)
{
    BaseOverlayMessage::parsimPack(b);
    doPacking(b,this->hops_var);
    doPacking(b,this->seq_id_var);
    b->pack(pathNodes_arraysize);
    doPacking(b,this->pathNodes_var,pathNodes_arraysize);
    doPacking(b,this->datasenttime_var);
}

void AckMsg::parsimUnpack(cCommBuffer *b)
{
    BaseOverlayMessage::parsimUnpack(b);
    doUnpacking(b,this->hops_var);
    doUnpacking(b,this->seq_id_var);
    delete [] this->pathNodes_var;
    b->unpack(pathNodes_arraysize);
    if (pathNodes_arraysize==0) {
        this->pathNodes_var = 0;
    } else {
        this->pathNodes_var = new int[pathNodes_arraysize];
        doUnpacking(b,this->pathNodes_var,pathNodes_arraysize);
    }
    doUnpacking(b,this->datasenttime_var);
}

int AckMsg::getHops() const
{
    return hops_var;
}

void AckMsg::setHops(int hops_var)
{
    this->hops_var = hops_var;
}

unsigned int AckMsg::getSeq_id() const
{
    return seq_id_var;
}

void AckMsg::setSeq_id(unsigned int seq_id_var)
{
    this->seq_id_var = seq_id_var;
}

void AckMsg::setPathNodesArraySize(unsigned int size)
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

unsigned int AckMsg::getPathNodesArraySize() const
{
    return pathNodes_arraysize;
}

int AckMsg::getPathNodes(unsigned int k) const
{
    if (k>=pathNodes_arraysize) throw cRuntimeError("Array of size %d indexed by %d", pathNodes_arraysize, k);
    return pathNodes_var[k];
}

void AckMsg::setPathNodes(unsigned int k, int pathNodes_var)
{
    if (k>=pathNodes_arraysize) throw cRuntimeError("Array of size %d indexed by %d", pathNodes_arraysize, k);
    this->pathNodes_var[k]=pathNodes_var;
}

simtime_t AckMsg::getDatasenttime() const
{
    return datasenttime_var;
}

void AckMsg::setDatasenttime(simtime_t datasenttime_var)
{
    this->datasenttime_var = datasenttime_var;
}

class AckMsgDescriptor : public cClassDescriptor
{
  public:
    AckMsgDescriptor();
    virtual ~AckMsgDescriptor();

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

Register_ClassDescriptor(AckMsgDescriptor);

AckMsgDescriptor::AckMsgDescriptor() : cClassDescriptor("AckMsg", "BaseOverlayMessage")
{
}

AckMsgDescriptor::~AckMsgDescriptor()
{
}

bool AckMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AckMsg *>(obj)!=NULL;
}

const char *AckMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AckMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int AckMsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *AckMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "hops",
        "seq_id",
        "pathNodes",
        "datasenttime",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int AckMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "seq_id")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "pathNodes")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "datasenttime")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AckMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "unsigned int",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *AckMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int AckMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AckMsg *pp = (AckMsg *)object; (void)pp;
    switch (field) {
        case 2: return pp->getPathNodesArraySize();
        default: return 0;
    }
}

std::string AckMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AckMsg *pp = (AckMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHops());
        case 1: return ulong2string(pp->getSeq_id());
        case 2: return long2string(pp->getPathNodes(i));
        case 3: return double2string(pp->getDatasenttime());
        default: return "";
    }
}

bool AckMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AckMsg *pp = (AckMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setHops(string2long(value)); return true;
        case 1: pp->setSeq_id(string2ulong(value)); return true;
        case 2: pp->setPathNodes(i,string2long(value)); return true;
        case 3: pp->setDatasenttime(string2double(value)); return true;
        default: return false;
    }
}

const char *AckMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *AckMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AckMsg *pp = (AckMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}



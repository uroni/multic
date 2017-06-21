//
// Generated file, do not edit! Created by opp_msgc 4.1 from overlay/basic/AckMsg.msg.
//

#ifndef _ACKMSG_M_H_
#define _ACKMSG_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include <CommonMessages_m.h>
#include <simtime_t.h>
// }}



/**
 * Class generated from <tt>overlay/basic/AckMsg.msg</tt> by opp_msgc.
 * <pre>
 * packet AckMsg extends BaseOverlayMessage
 * {
 *     int hops;
 *     unsigned int seq_id;
 *     int pathNodes[];
 *     simtime_t datasenttime;
 * }
 * </pre>
 */
class AckMsg : public ::BaseOverlayMessage
{
  protected:
    int hops_var;
    unsigned int seq_id_var;
    int *pathNodes_var; // array ptr
    unsigned int pathNodes_arraysize;
    simtime_t datasenttime_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AckMsg&);

  public:
    AckMsg(const char *name=NULL, int kind=0);
    AckMsg(const AckMsg& other);
    virtual ~AckMsg();
    AckMsg& operator=(const AckMsg& other);
    virtual AckMsg *dup() const {return new AckMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getHops() const;
    virtual void setHops(int hops_var);
    virtual unsigned int getSeq_id() const;
    virtual void setSeq_id(unsigned int seq_id_var);
    virtual void setPathNodesArraySize(unsigned int size);
    virtual unsigned int getPathNodesArraySize() const;
    virtual int getPathNodes(unsigned int k) const;
    virtual void setPathNodes(unsigned int k, int pathNodes_var);
    virtual simtime_t getDatasenttime() const;
    virtual void setDatasenttime(simtime_t datasenttime_var);
};

inline void doPacking(cCommBuffer *b, AckMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, AckMsg& obj) {obj.parsimUnpack(b);}


#endif // _ACKMSG_M_H_

/*
 * \file       rctdl_c_api_obj.h
 * \brief      Reference CoreSight Trace Decoder : C API callback objects. 
 * 
 * \copyright  Copyright (c) 2015, ARM Limited. All Rights Reserved.
 */

#ifndef ARM_RCTDL_C_API_OBJ_H_INCLUDED
#define ARM_RCTDL_C_API_OBJ_H_INCLUDED

#include "c_api/ocsd_c_api_types.h"
#include "interfaces/trc_gen_elem_in_i.h"
 

class TraceElemCBBase
{
public:
    TraceElemCBBase() {};
    virtual ~TraceElemCBBase() {};
};

class GenTraceElemCBObj : public ITrcGenElemIn, public TraceElemCBBase
{
public:
    GenTraceElemCBObj(FnTraceElemIn pCBFn, const void *p_context);
    virtual ~GenTraceElemCBObj() {};

    virtual rctdl_datapath_resp_t TraceElemIn(const rctdl_trc_index_t index_sop,
                                              const uint8_t trc_chan_id,
                                              const RctdlTraceElement &elem);

private:
    FnTraceElemIn m_c_api_cb_fn;
    const void *m_p_cb_context;
};

/************************************************************************/
/*** ETMv4 ***/
/************************************************************************/

class EtmV4ICBObj : public IPktDataIn<EtmV4ITrcPacket>, public TraceElemCBBase
{
public:
    EtmV4ICBObj(FnEtmv4IPacketDataIn pCBFn, const void *p_context);
    virtual ~EtmV4ICBObj() {};
    
    virtual rctdl_datapath_resp_t PacketDataIn( const rctdl_datapath_op_t op,
                                                const rctdl_trc_index_t index_sop,
                                                const EtmV4ITrcPacket *p_packet_in);

private:

    FnEtmv4IPacketDataIn m_c_api_cb_fn;
    const void *m_p_cb_context;
};


class EtmV4IPktMonCBObj : public IPktRawDataMon<EtmV4ITrcPacket>, public TraceElemCBBase
{
public:
    EtmV4IPktMonCBObj(FnEtmv4IPktMonDataIn pCBFn, const void *p_context);
    virtual ~EtmV4IPktMonCBObj() {};
    
    virtual void RawPacketDataMon( const rctdl_datapath_op_t op,
                                   const rctdl_trc_index_t index_sop,
                                   const EtmV4ITrcPacket *p_packet_in,
                                   const uint32_t size,
                                   const uint8_t *p_data);
                                   
private:
    FnEtmv4IPktMonDataIn m_c_api_cb_fn;
    const void *m_p_cb_context;
};

/************************************************************************/
/*** ETMv3 ***/
/************************************************************************/

class EtmV3CBObj : public IPktDataIn<EtmV3TrcPacket>, public TraceElemCBBase
{
public:
    EtmV3CBObj(FnEtmv3PacketDataIn pCBFn, const void *p_context);
    virtual ~EtmV3CBObj() {};
    
    virtual rctdl_datapath_resp_t PacketDataIn( const rctdl_datapath_op_t op,
                                                const rctdl_trc_index_t index_sop,
                                                const EtmV3TrcPacket *p_packet_in);

private:

    FnEtmv3PacketDataIn m_c_api_cb_fn;
    const void *m_p_cb_context;
};

class EtmV3PktMonCBObj : public IPktRawDataMon<EtmV3TrcPacket>, public TraceElemCBBase
{
public:
    EtmV3PktMonCBObj(FnEtmv3PktMonDataIn pCBFn, const void *p_context);
    virtual ~EtmV3PktMonCBObj() {};
    
    virtual void RawPacketDataMon( const rctdl_datapath_op_t op,
                                   const rctdl_trc_index_t index_sop,
                                   const EtmV3TrcPacket *p_packet_in,
                                   const uint32_t size,
                                   const uint8_t *p_data);
                                   
private:
    FnEtmv3PktMonDataIn m_c_api_cb_fn;
    const void *m_p_cb_context;
};

/************************************************************************/
/*** STM ***/
/************************************************************************/

class StmCBObj : public IPktDataIn<StmTrcPacket>, public TraceElemCBBase
{
public:
    StmCBObj(FnStmPacketDataIn pCBFn, const void *p_context);
    virtual ~StmCBObj() {};
    
    virtual rctdl_datapath_resp_t PacketDataIn( const rctdl_datapath_op_t op,
                                                const rctdl_trc_index_t index_sop,
                                                const StmTrcPacket *p_packet_in);

private:
    FnStmPacketDataIn m_c_api_cb_fn;
    const void *m_p_cb_context;
};

class StmPktMonCBObj : public IPktRawDataMon<StmTrcPacket>, public TraceElemCBBase
{
public:
    StmPktMonCBObj(FnStmPktMonDataIn pCBFn, const void *p_context);
    virtual ~StmPktMonCBObj() {};
    
    virtual void RawPacketDataMon( const rctdl_datapath_op_t op,
                                   const rctdl_trc_index_t index_sop,
                                   const StmTrcPacket *p_packet_in,
                                   const uint32_t size,
                                   const uint8_t *p_data);
                                   
private:
    FnStmPktMonDataIn m_c_api_cb_fn;
    const void *m_p_cb_context;
};

#endif // ARM_RCTDL_C_API_OBJ_H_INCLUDED

/* End of File rctdl_c_api_obj.h */

/*
 * \file       trc_pkt_decode_etmv4i.h
 * \brief      Reference CoreSight Trace Decoder : ETMv4 instruction decoder
 * 
 * \copyright  Copyright (c) 2015, ARM Limited. All Rights Reserved.
 */

/* 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution. 
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 * may be used to endorse or promote products derived from this software without 
 * specific prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */ 

#ifndef ARM_TRC_PKT_DECODE_ETMV4I_H_INCLUDED
#define ARM_TRC_PKT_DECODE_ETMV4I_H_INCLUDED

#include "trc_pkt_decode_base.h"
#include "etmv4/trc_pkt_elem_etmv4i.h"
#include "etmv4/trc_cmp_cfg_etmv4.h"

#include <deque>

class AddrValStack;
class TrcStackElem;

class TrcPktDecodeEtmV4I : public TrcPktDecodeBase<EtmV4ITrcPacket, EtmV4Config>
{
public:
    TrcPktDecodeEtmV4I();
    TrcPktDecodeEtmV4I(int instIDNum);
    virtual ~TrcPktDecodeEtmV4I();

protected:
    /* implementation packet decoding interface */
    virtual rctdl_datapath_resp_t processPacket();
    virtual rctdl_datapath_resp_t onEOT();
    virtual rctdl_datapath_resp_t onReset();
    virtual rctdl_datapath_resp_t onFlush();
    virtual rctdl_err_t onProtocolConfig();
    virtual const uint8_t getCoreSightTraceID() { return m_CSID; };

    /* local decode methods */
    void initDecoder();      // initial state on creation (zeros all config)
    void resetDecoder();     // reset state to start of decode. (moves state, retains config)

    rctdl_err_t findCodeWaypoint(); // search for next waypoint in the code.

    rctdl_datapath_resp_t decodePacket(bool &Complete);    // return true to indicate decode complete - can change FSM to commit state - return is false.
    rctdl_datapath_resp_t commitElements(bool &Complete);   // commit elements - may get wait response, or flag completion.

    void doTraceInfoPacket();

private:
//** intra packet state (see ETMv4 spec 6.2.1);

    // timestamping
    uint64_t m_timestamp;   // last broadcast global Timestamp.

    // address values stack   
    AddrValStack *m_pAddrRegs;

    // state and context 
    uint32_t m_context_id;              // most recent context ID
    uint32_t m_vmid_id;                 // most recent VMID
    bool m_is_secure;                   // true if Secure
    bool m_is_64bit;                    // true if 64 bit

    // cycle counts 
    int m_cc_threshold;

    // speculative trace (unsupported at present in the decoder).
    int m_curr_spec_depth;                
    int m_max_spec_depth; 
    
    // data trace associative elements (unsupported at present in the decoder).
    int m_p0_key;
    int m_p0_key_max;

    // conditional non-branch trace - when data trace active (unsupported at present in the decoder)
    int m_cond_c_key;
    int m_cond_r_key;
    int m_cond_key_max_incr;

//** Other processor state;

    // trace decode FSM
    typedef enum {
        NO_SYNC,        //!< pre start trace - init state or after reset or overflow, loss of sync.
        WAIT_SYNC,      //!< waiting for sync packet.
        WAIT_TINFO,     //!< waiting for trace info packet.
        DECODE_PKTS,    //!< processing packets - creating decode elements
        COMMIT_ELEM,    //!< commit elements for execution - create generic trace elements and pass on.
    } processor_state_t;

    processor_state_t m_curr_state;
    bool m_need_ctxt;
    bool m_need_addr;
    bool m_except_pending_addr_ctxt; 
    uint8_t m_CSID;
    
    rctdl_instr_info m_instr_info;  //!< instruction info for code follower.

    etmv4_trace_info_t m_trace_info;

//** P0 element stack
    std::deque<TrcStackElem *> m_P0_stack;

    int m_P0_commit;
};

#endif // ARM_TRC_PKT_DECODE_ETMV4I_H_INCLUDED

/* End of File trc_pkt_decode_etmv4i.h */

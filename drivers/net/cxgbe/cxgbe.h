/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2014-2018 Chelsio Communications.
 * All rights reserved.
 */

#ifndef _CXGBE_H_
#define _CXGBE_H_

#include "common.h"
#include "t4_regs.h"

#define CXGBE_MIN_RING_DESC_SIZE      128  /* Min TX/RX descriptor ring size */
#define CXGBE_MAX_RING_DESC_SIZE      4096 /* Max TX/RX descriptor ring size */

#define CXGBE_DEFAULT_TX_DESC_SIZE    1024 /* Default TX ring size */
#define CXGBE_DEFAULT_RX_DESC_SIZE    1024 /* Default RX ring size */

#define CXGBE_MIN_RX_BUFSIZE ETHER_MIN_MTU /* min buf size */
#define CXGBE_MAX_RX_PKTLEN (9000 + ETHER_HDR_LEN + ETHER_CRC_LEN) /* max pkt */

/* Max poll time is 100 * 100msec = 10 sec */
#define CXGBE_LINK_STATUS_POLL_MS 100 /* 100ms */
#define CXGBE_LINK_STATUS_POLL_CNT 100 /* Max number of times to poll */

#define CXGBE_DEFAULT_RSS_KEY_LEN     40 /* 320-bits */
#define CXGBE_RSS_HF_IPV4_MASK (ETH_RSS_IPV4 | ETH_RSS_FRAG_IPV4 | \
				ETH_RSS_NONFRAG_IPV4_OTHER)
#define CXGBE_RSS_HF_IPV6_MASK (ETH_RSS_IPV6 | ETH_RSS_FRAG_IPV6 | \
				ETH_RSS_NONFRAG_IPV6_OTHER | \
				ETH_RSS_IPV6_EX)
#define CXGBE_RSS_HF_TCP_IPV6_MASK (ETH_RSS_NONFRAG_IPV6_TCP | \
				    ETH_RSS_IPV6_TCP_EX)
#define CXGBE_RSS_HF_UDP_IPV6_MASK (ETH_RSS_NONFRAG_IPV6_UDP | \
				    ETH_RSS_IPV6_UDP_EX)
#define CXGBE_RSS_HF_ALL (ETH_RSS_IP | ETH_RSS_TCP | ETH_RSS_UDP)

#define CXGBE_DEVARG_KEEP_OVLAN "keep_ovlan"
#define CXGBE_DEVARG_FORCE_LINK_UP "force_link_up"

bool force_linkup(struct adapter *adap);
int cxgbe_probe(struct adapter *adapter);
int cxgbevf_probe(struct adapter *adapter);
void cxgbe_get_speed_caps(struct port_info *pi, u32 *speed_caps);
int cxgbe_set_link_status(struct port_info *pi, bool status);
int cxgbe_up(struct adapter *adap);
int cxgbe_down(struct port_info *pi);
void cxgbe_close(struct adapter *adapter);
void cxgbe_stats_get(struct port_info *pi, struct port_stats *stats);
void cxgbevf_stats_get(struct port_info *pi, struct port_stats *stats);
void cxgbe_stats_reset(struct port_info *pi);
int cxgbe_poll_for_completion(struct sge_rspq *q, unsigned int us,
			      unsigned int cnt, struct t4_completion *c);
int link_start(struct port_info *pi);
void init_rspq(struct adapter *adap, struct sge_rspq *q, unsigned int us,
	       unsigned int cnt, unsigned int size, unsigned int iqe_size);
int setup_sge_fwevtq(struct adapter *adapter);
int setup_sge_ctrl_txq(struct adapter *adapter);
void cfg_queues(struct rte_eth_dev *eth_dev);
int cfg_queue_count(struct rte_eth_dev *eth_dev);
int init_rss(struct adapter *adap);
int setup_rss(struct port_info *pi);
void cxgbe_enable_rx_queues(struct port_info *pi);
void print_port_info(struct adapter *adap);
void print_adapter_info(struct adapter *adap);
int cxgbe_get_devargs(struct rte_devargs *devargs, const char *key);
void configure_max_ethqsets(struct adapter *adapter);

#endif /* _CXGBE_H_ */

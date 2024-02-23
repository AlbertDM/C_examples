
#include <stdio.h>
/*
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202301L
#define C23_STYLE 1
#endif
*/
// #define C23_STYLE 0
#define C23_STYLE 1

#if !C23_STYLE
#include <stdbool.h>
#endif

#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_IPV6 0x86DD
#define MIN_ETHERNET_FRAME 64   /* Octets */
#define MAX_ETHERNET_FRAME 1522 /* Octets */
#define MAX_MQTT_PACKET 256
#define MAX_PAYLOAD_DATA MAX_MQTT_PACKET

/* L5: App Data based in simplified MQTT */
typedef struct {
  unsigned char packet_type : 4;  // Packet type
  unsigned char flags : 4;        // Flags
} control_field_t;
typedef struct {
  control_field_t control_field;      // Control field struct
  unsigned char remaining_length[4];  // Variable length depending on packet size
} app_header_t;

/* L4: TCP segment header */
typedef struct {
  unsigned short src_port;        // Source port number
  unsigned short dst_port;        // Destination port number
  unsigned int seq_num;           // Sequence number
  unsigned int ack_num;           // Acknowledgment number
  unsigned char data_offset : 4;  // Data offset in 4-byte words
  unsigned char reserved1 : 3;    // Reserved bits
  unsigned char ns : 1;           // NS (Nonce Sum) flag
  unsigned char cwr : 1;          // CWR (Congestion Window Reduced) flag
  unsigned char ece : 1;          // ECE (Echo) flag
  unsigned char urg : 1;          // URG (Urgent) flag
  unsigned short window;          // Window size
  unsigned short checksum;        // Checksum
  unsigned short urgent_ptr;      // Urgent pointer
  unsigned char options : 3;      // Reserved bits
  unsigned char padding : 1;      // NS (Nonce Sum) flag
} tcp_header_t;

/* L3: IP datagram header */
typedef struct {  
  unsigned char version : 4;        // IP version
  unsigned char ihl : 4;            // Internet Header Length (in 4-byte words)
  unsigned char type_of_service;    // Type of service
  unsigned short total_length;      // Total length of the IP datagram
  unsigned short identification;    // Unique ID for the datagram
  unsigned short flags_and_offset;  // Flags and fragment offset
  unsigned char time_to_live;       // Time to live
  unsigned char protocol;           // Protocol (e.g., TCP, UDP)
  unsigned short header_checksum;   // Checksum of the header
  unsigned int src_addr;            // Source IP address
  unsigned int dst_addr;            // Destination IP address
  // More IP options ....
} ip_header_t;

/* L2: IEEE 802.3 Ethernet frame */
typedef struct {  
  unsigned char dst_mac[6];   // Destination MAC address
  unsigned char src_mac[6];   // Source MAC address
  unsigned short ethertype;   // EtherType (e.g., 0x0800 for IPv4)
} ethernet_header_t;
typedef struct {  
  unsigned int crc;   // Cyclic Redundancy Check (CRC) for error detection
} ethernet_trailer_t;

/* Protocol Stack Message */
typedef struct {
  ip_header_t ip_header;
  tcp_header_t tcp_header;
  app_header_t app_header;
  unsigned char payload[];
  // ethernet_trailer_t not set intentionally
} protocol_message_t;



void initTcpHeader_C23 (tcp_header_t *tcp) {

  tcp_header_t tcptmp = {
    .src_port = 0x1234,
    .dst_port = 0x5678,
    .seq_num = 1,
    .ack_num = 2,
  };
  
  *tcp = tcptmp;
}

int main() {
  void (*initTcpHeader_ptr)(tcp_header_t *tcp);
  void (*initIpHeader_ptr)(ip_header_t *ip);
  void (*initEthernetHeader_ptr)(ethernet_header_t *eth);
  void (*initAppHeader_ptr)(app_header_t *app_pkt);
  protocol_message_t msg;

  #if C23_STYLE
    initTcpHeader_ptr = initTcpHeader_C23;
    initIpHeader_ptr = initIpHeader_C23;
    initEthernetHeader_ptr = initEthernetHeader_C23;
    initAppHeader_ptr = initAppHeader_C23;
  #else
    initTcpHeader_ptr = initTcpHeader_C99;
    initIpHeader_ptr = initIpHeader_C99;
    initEthernetHeader_ptr = initEthernetHeader_C99;
    initAppHeader_ptr = initAppHeader_C99;
  #endif

  return  0;
}

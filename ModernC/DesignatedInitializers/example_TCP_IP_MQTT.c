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

/* L2: IEEE 802.3 Ethernet frame */
typedef struct {  
  unsigned char dst_mac[6];   // Destination MAC address
  unsigned char src_mac[6];   // Source MAC address
  unsigned short ethertype;   // EtherType (e.g., 0x0800 for IPv4)
} ethernet_header_t;
typedef struct {  
  unsigned int crc;   // Cyclic Redundancy Check (CRC) for error detection
} ethernet_trailer_t;

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

/* L5: App Data based in simplified MQTT */
typedef struct {
  unsigned char packet_type : 4;  // Packet type
  unsigned char flags : 4;        // Flags
} control_field_t;
typedef struct {
  control_field_t control_field;      // Control field struct
  unsigned char remaining_length[4];  // Variable length depending on packet size
} app_header_t;

/* Protocol Stack Message */
typedef struct {
  ip_header_t ip_header;
  tcp_header_t tcp_header;
  app_header_t app_header;
  unsigned char payload[];
  // ethernet_trailer_t not set intentionally
} protocol_message_t;

/*----*/

// Function to initialize members of the Ethernet header
void initEthernetHeader_C23 (ethernet_header_t *eth) {

  ethernet_header_t ethtmp = {
    .src_port = 0x1234,
    0x5678,
    .seq_num = 1,
    .ack_num = 2,
  };
  
  *eth = ethtmp;
}

// Function to initialize members of the IP header
void initIpHeader_C23 (ip_header_t *ip) {

  ip_header_t iptmp = {
    .src_port = 0x1234,
    0x5678,
    .seq_num = 1,
    .ack_num = 2,
  };
  
  *ip = iptmp;
}

// Function to initialize members of the TCP header
void initTcpHeader_C23 (tcp_header_t *tcp) {

  tcp_header_t tcptmp = {
    .src_port = 0x1234,
    0x5678,
    .seq_num = 1,
    .ack_num = 2,
  };
  
  *tcp = tcptmp;
}

// Function to initialize members of the App header
void initAppHeader_C23 (app_header_t *app) {

  app_header_t apptmp = {
    .src_port = 0x1234,
    0x5678,
    .seq_num = 1,
    .ack_num = 2,
  };
  
  *app = apptmp;
}

// Function to print members of the TCP header
void printMembersTcpHeader(tcp_header_t tcp) {

  printf("TCP Header:\n");
  printf("Source Port: \t\t%u\n", tcp.src_port);        // Source port
  printf("Destination Port: \t%u\n", tcp.dst_port);     // Destination port
  printf("Sequencue number: \t%u\n", tcp.seq_num);      // Sequence number
  printf("Acnowledgement number: \t%u\n", tcp.ack_num); // Acknowledgment number
#if C23_STYLE
  printf("Data offset: \t\t%b\n", tcp.data_offset);     // Data offset in 4-byte words
  printf("Reserved bits: \t\t%b\n", tcp.reserved1);     // Reserved bits
  printf("Nonce sum: \t\t%b\n", tcp.ns);                // NS (Nonce Sum) flag
  printf("CWR flag: \t\t%b\n", tcp.cwr);                // CWR (Congestion Window Reduced) flag
  printf("ECE flag: \t\t%b\n", tcp.ece);                // ECE (Echo) flag
  printf("URG flag: \t\t%b\n", tcp.urg);                // URG (Urgent) flag
#else // C99
  printf("Data offset: \t\t%x\n", tcp.data_offset);     // Data offset in 4-byte words
  printf("Reserved bits: \t\t%x\n", tcp.reserved1);     // Reserved bits
  printf("Nonce sum: \t\t%x\n", tcp.ns);                // NS (Nonce Sum) flag
  printf("CWR flag: \t\t%x\n", tcp.cwr);                // CWR (Congestion Window Reduced) flag
  printf("ECE flag: \t\t%x\n", tcp.ece);                // ECE (Echo) flag
  printf("URG flag: \t\t%x\n", tcp.urg);                // URG (Urgent) flag
#endif
  printf("Window size: \t\t%u\n", tcp.window);          // Window size
  printf("Checksum: \t\t%u\n", tcp.checksum);           // Checksum
  printf("Urgent pointer: \t%u\n", tcp.urgent_ptr);     // Urgent pointer
#if C23_STYLE
  printf("Options: \t\t%b\n", tcp.options);             // Reserved bits
  printf("Padding: \t\t%b\n", tcp.padding);             // NS (Nonce Sum) flag
#else // C99
  printf("Options: \t\t%x\n", tcp.options);             // Reserved bits
  printf("Padding: \t\t%x\n", tcp.padding);             // NS (Nonce Sum) flag
#endif

}

// Function to print members of the IP header
void printMembersIpHeader(ip_header_t ip) {

  printf("IP Header:\n");
  printf("Source IP: %u\n", ip.src_addr);
  printf("Destination IP: %u\n", ip.dst_addr);
  // Add more printf statements for other members

}

// Function to print members of the Ethernet header
void printMembersEthernetHeader(ethernet_header_t eth) {

  printf("Ethernet Header:\n");
  // Print MAC addresses, EtherType, etc.
}

// Function to print members of the App header
void printMembersAppHeader(app_header_t app) {

  printf("App Header:\n");
  printf("Packet Type: %u\n", app.control_field.packet_type);
  printf("Flags: %u\n", app.control_field.flags);
  // Add more printf statements for other members

}

// Main function
int main() {

  tcp_header_t tcp; 
  ip_header_t ip;
  ethernet_header_t eth;
  app_header_t app_pkt;
  protocol_message_t msg;

  void (*initTcpHeader_ptr)(tcp_header_t *tcp);
  void (*initIpHeader_ptr)(ip_header_t *ip);
  void (*initEthernetHeader_ptr)(ethernet_header_t *eth);
  void (*initAppHeader_ptr)(app_header_t *app_pkt);
  void (*initProtocolPacket_ptr)(tcp_header_t tcp, 
                                 ip_header_t ip, 
                                 ethernet_header_t eth, 
                                 app_header_t app_pkt, 
                                 protocol_message_t *msg);

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
  
  initTcpHeader_ptr(&tcp);
  initIpHeader_ptr(&ip);
  initEthernetHeader_ptr(&eth);
  initAppHeader_ptr(&app_pkt);

  printMembersTcpHeader(tcp);
  printMembersIpHeader(ip);
  printMembersEthernetHeader(eth);
  printMembersAppHeader(app_pkt);
 
  return  0;

}

# UCCN2243 Internetworking Principles and Practices Assignment

## Faculty of Information and Communication Technology  
**Course**: UCCN2243 Internetworking Principles and Practices  
**Lecturer**: Ts Dr. Gan Ming Lee  
**Group Name**: Iacnic  

---

## Group Members

| No | Name          | Student ID | Practical Group | Programme |
|----|---------------|------------|-----------------|-----------|
| 1  | Foo Kar Yeng  | 2300422    | P1              | CN        |
| 2  | Liew Ren Yi   | 2300434    | P1              | CN        |
| 3  | Tan Yi Fei    | 2200842    | P1              | CN        |
| 4  | Wong Pei Kei  | 2207466    | P1              | CN        |

---

## Project Overview

This assignment showcases the implementation and understanding of key internetworking topics using GNS3 and Wireshark. The assignment is divided into two main parts:

- **Part 1:** DHCP server setup, NAT configuration on routers (Router0 and Router1), and DHCP relay verification.
- **Part 2:** Edge Router NAT configuration, connectivity testing (ping/telnet), and detailed traffic analysis using Wireshark.

---

## My Contribution – Part 2 (Edge Router Configuration & Wireshark Analysis)

I was fully responsible for **Part 2** of the assignment, which included both **router configuration** and **Wireshark packet analysis**. My contributions include:

### ✅ Part 2a – Router & NAT Configuration

- Configured the **Edge Router** to support NAT/PAT translation.
- Implemented **ACLs (Access Control Lists)** to control which IP ranges can access external networks.
- Enabled routing and ensured proper communication between PC1/PC2 and external servers.

### ✅ Part 2b – Network Testing & Wireshark Analysis

- Conducted connectivity tests:
  - PC1 was able to ping both the **Internet Gateway** and **Telnet Server**.
  - PC2 failed to ping the Internet Gateway (due to ACL rules) but could reach the Telnet Server.
- Performed packet capture with **Wireshark** on key interfaces:
  - Identified NAT/PAT behavior in ICMP and TCP packets.
  - Verified port translations, IP mappings, and packet flow through different network layers.
- Explained how NAT, ACLs, and routing decisions affected packet delivery and firewall rules.

---

## Tools & Technologies Used

- **GNS3** – for virtual router and network setup
- **Wireshark** – for traffic capture and packet-level analysis
- **Cisco IOS CLI** – for configuration of routers, NAT, DHCP, ACL
- **Ping & Telnet utilities** – to test end-to-end connectivity

---

## How to Run the Project

1. Open the provided GNS3 topology.
2. Start all devices: PC1, PC2, Edge Router, Internet Gateway, Telnet Server.
3. Verify interface configurations and routing.
4. Initiate packet captures on PC1 and Edge Router interfaces.
5. Use ping and telnet commands to observe network behavior.
6. Analyze captured traffic in Wireshark to see NAT, ACL, and routing effects.

---

## References

Please refer to the assignment report for a full list of sources (pages 20–21), including:
- Cisco official documentation
- NAT/PAT configuration guides
- Wireshark tutorials and protocol deep-dives

---

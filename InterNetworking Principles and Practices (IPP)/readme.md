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

This assignment demonstrates hands-on knowledge and understanding of **DHCP configuration**, **NAT (Network Address Translation)**, **routing**, and **Wireshark packet capture** using GNS3.

It consists of two major sections:

- **Question 1:** DHCP and NAT configuration on routers (Router0 and Router1), and demonstration of DHCP server functionality.
- **Question 2:** Configuration of the Edge Router with NAT, and analysis of packet transmission using Wireshark to evaluate communication between PCs, Internet Gateway, and Telnet Server.

---

## My Contribution – Question 2b: Wireshark Analysis

I was responsible for **Part B (Question 2b)** of the assignment, which involved integrating **Wireshark with GNS3** and analyzing network traffic. My tasks included:

- **Demonstrating PC1 and PC2 network behavior:**
  - PC1 successfully pinging the Internet Gateway and Telnet Server.
  - PC2 failing to ping the Internet Gateway but able to ping the Telnet Server.

- **Performing NAT Analysis in Wireshark:**
  - Capturing ICMP packets and interpreting NAT behavior on both PC1 and the Edge Router interface.
  - Explaining how PAT (Port Address Translation) and ACLs influence access based on IP ranges.
  - Identifying packet flow transformations and correlating it with NAT rules applied on the router.

- **Conclusion and Insight:**
  - Showcased how NAT and ACL misconfiguration impacted connectivity.
  - Highlighted the translation process of private to public IPs and vice versa.

This section helped reinforce practical knowledge of how NAT and port forwarding interact with ICMP and TCP protocols and how to debug network issues using Wireshark in real time.

---

## Tools & Technologies Used

- Cisco Packet Tracer / GNS3 for topology simulation
- Wireshark for packet-level analysis
- Cisco IOS CLI for router configuration
- Static and dynamic routing, NAT, PAT, DHCP Relay

---

## How to Run the Project

1. Open the provided GNS3 project file (`.gns3`) in GNS3.
2. Start all routers and hosts (ensure DHCP Server is operational).
3. Configure interfaces and NAT rules according to the documented running configurations.
4. Use Wireshark to monitor specific interface traffic (e.g., `Ethernet0` on PC1, `FastEthernet0/1` on Edge Router).
5. Test connectivity using `ping` and `telnet` commands between hosts.
6. Analyze NAT behavior using the IP source/destination and payload IDs in Wireshark.

---

## References

A list of references is available in the assignment report (pages 20–21), covering Cisco documentation, GNS3-Wireshark tutorials, and networking fundamentals.

---


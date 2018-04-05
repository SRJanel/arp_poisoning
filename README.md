# ARP Poisoning
An ARP Poisoning tool in C without using any libraries.  
This tool was coded during a **live coding session** for the Astek Lab at Epitech and was slightly modified afterwards.
***

## Overview
This is a tool which performs a MITM attack on a network using the ARP poisoning method.
ARP poisoning or ARP cache poisoning is a method in which an attacker sends spoofed ARP messages to "poison" a victim's ARP table in order to create a MITM attack.  
![alt text](https://qph.ec.quoracdn.net/main-qimg-b1a85eb67f3df59f3eaf3a3697c03b10 "MITM attack pic")

## Description
In this tool, I create a (Data-Link/L2) socket using `AF_PACKET` as first argument to the socket() system call. I am using `SOCK_RAW` as well for the second argument to socket(), in combination with `AF_PACKET` as this gives us control over the Data-link Layer. That means that everything (ethernet + ARP header) must be constructed manually. Another way to code this tool would be to initialize the socket with `SOCK_DGRAM`, which operates on a slightly "higher level". By using `SOCK_DGRAM`, the Kernel removes or adds the ethernet header before the packet is sent to the user space. The header gets filled based on the informations specified by the user in the `sockaddr_ll` structure. In this project, we use `SOCK_RAW` and we create all the needed structures by ourselves to make things easier to understand. The third argument of the socket is `ETH_P_ARP` because when we call `recvfrom()` we want the kernel to pass to our socket only ARP packets and nothing else as it is a waste of resources.

To be able to perfom a MITM attack by (ab)using the ARP protocol, spoofed ARP Reply packets must be sent to both parties. For each party, I specify as source IP address the address of the other party. Source MAC address is set at the address of the other party and source IP address is set to our IP (the attacker). This will have as result to associate on those machines the mac address of the other party with our IP address. Destination MAC address is the destination of the machine that we are sending the crafted message; In order to obtain that, I first send an ARP Request to the MAC broadcast address asking "who has that IP address?" and then I listen for an ARP Reply coming from the target to extract and obtain his MAC address.

## Usage
To create a MITM attack between victim1 and victim2 with you (the attacker) in the middle:  
```sudo ./arp_poisoning victim1_IP_address victim2_IP_address interface```  
```sudo ./arp_poisoning victim2_IP_address victim1_IP_address interface```  
```echo 1 > /proc/sys/net/ipv4/ip_forward``` #(to enable ip_forward)  

## Inspired by
* the arpspoof tool from Kali linux
* m0nad

## Prevention Methods
* Static ARP entries
* ARP spoofing detection and prevention softwares

## Notes
This tool was coded during a live coding session and is meant for **educational and informational purposes** only.  
It is your responsibility to make sure you have permission from the network owner before running this tool against it.  
The authors of this tool are **not** responsible for your personal actions or choices.

## Authors
* SRJanel
* Pandor

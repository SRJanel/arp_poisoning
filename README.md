# ARP Poisoning
An ARP Poisoning tool in C using raw Data Link Layer sockets.  
This tool was coded during a live coding session for the Astek Lab at Epitech and was slightly modified afterwards.
***

## Overview
This is a tool which performs a MITM attack on a network using the ARP poisoning method.
ARP poisoning or ARP cache poisoning is a method in which an attacker sends spoofed ARP messages to "poison" a victim's ARP table in order to create a MITM attack.  
![alt text](https://qph.ec.quoracdn.net/main-qimg-b1a85eb67f3df59f3eaf3a3697c03b10 "MITM attack pic")

## Description
In this tool, we create a Data-Link Layer 2 socket (using `AF_PACKET` as first argument to our socket() system call) in order to create the address resolution protocol which lays in the Layer 2 of the OSI model. We will use `SOCK_RAW` as well for the second argument to socket(), in combination with `AF_PACKET` as this will give us full-control over the Data-link Layer. That means that we must construct everything by ourselves, which means the ARP protocol + the ethernet header. Another way to code this tool would be to initialize the packet socket with `SOCK_DGRAM`, which operates on a slightly higher level. By using `SOCK_DGRAM`, the Kernel adds and removes the physical (ethernet) header before the packet is passed to the user space based on the information specified by the user in the `sockaddr_ll` structure. In this tool, we will use `SOCK_RAW` + we will create every structure by ourselves in order to understand better what is truly happening at a deeper level inside the Kernel space. The third argument of the socket is `ETH_P_ARP` because when we call `recvfrom()` we want the kernel to pass to our socket only ARP packets and nothing else as it is a waste of resources.

In order to create a MITM attack by (ab)using the ARP protocol we must send spoofed ARP Reply packets to both parties by specifying as source IP address the address of one's another. Destination MAC address should be the destination of the target; In order to obtain that, we first send an ARP Request to the MAC broadcast address asking who has that IP address and then then we listen for an ARP Reply coming from the target in order to extract from the packet and obtain his MAC address.

## Usage
To create a MITM attack between victim1 and victim2 with you (the attacker) in the middle:  
```sudo ./arp_poisoning victim1_IP_address victim2_IP_address interface```  
```sudo ./arp_poisoning victim2_IP_address victim1_IP_address interface```

## Motivation
This tool was created using low level socket programming, without using any library.
The main motivation was to understand the different mechanisms that take place inside the Kernel.

## Prevention Methods
* Static ARP entries
* ARP spoofing detection and prevention softwares

## Notes
This tool is meant for **educational and informational purposes** only.  
It is your responsibility to make sure you have permission from the network owner before running this tool against it.  
The authors of this tool are **not** responsible for your personal actions or choices.

## Authors
* SRJanel
* Pandor

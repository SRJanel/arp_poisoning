# ARP Poisoning
An ARP Poisoning tool in C without using only libc.  
This tool was coded during a **live coding session** for the Astek Lab at Epitech (and was slightly modified afterwards).  
**Epitech students: Please note that this project has been scanned/imported into Epitech's moulitriche system. Copying any parts of it might result in a -84 or -42 mark during evaluation.**
***

## Overview
This is a tool which performs a MITM attack in a network using the ARP poisoning method.
ARP poisoning or ARP cache poisoning is a method in which an attacker sends spoofed ARP messages to "poison" a victim's ARP table in order to create a MITM attack.  
![alt text](https://tournasdimitrios1.files.wordpress.com/2011/02/arp-spoofing.png "MITM attack pic example")

## Description
In this tool, a L2 socket is created by using `AF_PACKET` as first argument to the socket() system call. In combination with `AF_PACKET`, `SOCK_RAW` is also used as a second argument as this gives us control over some parts of the Data-link Layer (mainly most of the ethernet frame header). That means that everything must be constructed manually. Another way to code this tool would be to initialize the socket with `SOCK_DGRAM`, which operates on a slightly "higher level". By using `SOCK_DGRAM`, the Kernel removes/adds the ethernet header (the "MAC header" part) before the packet is sent to/from user space. Then if needed, usually, the ethernet frame header gets filled based on information specified by the user in the `sockaddr_ll` structure. In this project, `SOCK_RAW` is used and all needed structures are manually created (not using Kernel headers) to make things easier to understand. The third argument of the socket is `ETH_P_ARP` because when `recvfrom()` is called only ARP packets and nothing else gets copied on the socket as it is a waste of resources.

To be able to perfom a MITM attack by (ab)using the ARP protocol, spoofed ARP Reply packets must be sent to both parties (although the attack can also be made with ARP requests and has been proven to be stealthier http://blog.zorinaq.com/a-more-powerful-stealthier-and-uncommon-arp-poisoning-technique/). The source IP address (in the ARP header), is set at the address of the other party and source MAC address (Ethernet Frame header) is set to our MAC (the attacker). By sending unicast ARPs to both victims, will have as result to associate on those machines the other victim's IP with our MAC address. Destination MAC address is the destination of the machine that we are sending the crafted message; To obtain that, we first send a (broadcast) ARP Request to the MAC broadcast address asking "who has that IP address?" and then we listen for any ARP Reply coming from the target in order to extract and obtain his MAC address.

## Usage
To create a MITM attack between ip1 and ip2 with you (the attacker) in the middle:  
```sudo ./arp_poisoning ip1_address ip2_address interface```  
```sudo ./arp_poisoning ip2_address ip1_address interface```  
```echo 1 > /proc/sys/net/ipv4/ip_forward``` #(to enable ip_forward)  

## Inspired mainly by
* the arpspoof tool from dsniff package
* m0nad (https://github.com/m0nad/ARP-Poison/blob/master/arp-poison.c)

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

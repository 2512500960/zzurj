/*++

Copyright (c) 1997-1999  Microsoft Corporation

Module Name:

    public\sdk\inc\iphlpapi.h

Abstract:
    Header file for functions to interact with the IP Stack for MIB-II and
    related functionality

Revision History:
    Amritansh Raghav    Created
    NK Srinivas         Added

--*/

#ifndef __IPHLPAPI_H__
#define __IPHLPAPI_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// IPRTRMIB.H has the definitions of the strcutures used to set and get     //
// information                                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#include <iprtrmib.h>
#include "ipexport.h"
#include "iptypes.h"

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The GetXXXTable APIs take a buffer and a size of buffer.  If the buffer  //
// is not large enough, they APIs return ERROR_INSUFFICIENT_BUFFER  and     //
// *pdwSize is the required buffer size                                     //
// The bOrder is a BOOLEAN, which if TRUE sorts the table according to      //
// MIB-II (RFC XXXX)                                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Retrieves the number of interfaces in the system. These include LAN and  //
// WAN interfaces                                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


DWORD
WINAPI
GetNumberOfInterfaces(
    OUT PDWORD  pdwNumIf
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the MIB-II ifEntry                                                  //
// The dwIndex field of the MIB_IFROW should be set to the index of the     //
// interface being queried                                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIfEntry(
    IN OUT PMIB_IFROW   pIfRow
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the MIB-II IfTable                                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIfTable(
    OUT    PMIB_IFTABLE pIfTable,
    IN OUT PULONG       pdwSize,
    IN     BOOL         bOrder
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the Interface to IP Address mapping                                 //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIpAddrTable(
    OUT    PMIB_IPADDRTABLE pIpAddrTable,
    IN OUT PULONG           pdwSize,
    IN     BOOL             bOrder
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the current IP Address to Physical Address (ARP) mapping            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIpNetTable(
    OUT    PMIB_IPNETTABLE pIpNetTable,
    IN OUT PULONG          pdwSize,
    IN     BOOL            bOrder
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the IP Routing Table  (RFX XXXX)                                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIpForwardTable(
    OUT    PMIB_IPFORWARDTABLE pIpForwardTable,
    IN OUT PULONG              pdwSize,
    IN     BOOL                bOrder
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets TCP Connection/UDP Listener Table                                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetTcpTable(
    OUT    PMIB_TCPTABLE pTcpTable,
    IN OUT PDWORD        pdwSize,
    IN     BOOL          bOrder
    );

DWORD
WINAPI
GetUdpTable(
    OUT    PMIB_UDPTABLE pUdpTable,
    IN OUT PDWORD        pdwSize,
    IN     BOOL          bOrder
    );


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets IP/ICMP/TCP/UDP Statistics                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIpStatistics(
    OUT  PMIB_IPSTATS   pStats
    );

DWORD
WINAPI
GetIcmpStatistics(
    OUT PMIB_ICMP   pStats
    );


DWORD
WINAPI
GetTcpStatistics(
    OUT PMIB_TCPSTATS   pStats
    );

DWORD
WINAPI
GetUdpStatistics(
    OUT PMIB_UDPSTATS   pStats
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the ifAdminStatus on an interface.  The only fields of the   //
// MIB_IFROW that are relevant are the dwIndex (index of the interface      //
// whose status needs to be set) and the dwAdminStatus which can be either  //
// MIB_IF_ADMIN_STATUS_UP or MIB_IF_ADMIN_STATUS_DOWN                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
SetIfEntry(
    IN PMIB_IFROW pIfRow
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create, modify or delete a route.  In all cases the              //
// dwForwardIfIndex, dwForwardDest, dwForwardMask, dwForwardNextHop and     //
// dwForwardPolicy MUST BE SPECIFIED. Currently dwForwardPolicy is unused   //
// and MUST BE 0.                                                           //
// For a set, the complete MIB_IPFORWARDROW structure must be specified     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
CreateIpForwardEntry(
    IN PMIB_IPFORWARDROW pRoute
    );

DWORD
WINAPI
SetIpForwardEntry(
    IN PMIB_IPFORWARDROW pRoute
    );

DWORD
WINAPI
DeleteIpForwardEntry(
    IN PMIB_IPFORWARDROW pRoute
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the ipForwarding to ON or OFF (currently only ON->OFF is     //
// allowed) and to set the defaultTTL.  If only one of the fields needs to  //
// be modified and the other needs to be the same as before the other field //
// needs to be set to MIB_USE_CURRENT_TTL or MIB_USE_CURRENT_FORWARDING as  //
// the case may be                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


DWORD
WINAPI
SetIpStatistics(
    IN PMIB_IPSTATS pIpStats
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the defaultTTL.                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
SetIpTTL(
    UINT nTTL
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create, modify or delete an ARP entry.  In all cases the dwIndex //
// dwAddr field MUST BE SPECIFIED.                                          //
// For a set, the complete MIB_IPNETROW structure must be specified         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
CreateIpNetEntry(
    IN PMIB_IPNETROW    pArpEntry
    );

DWORD
WINAPI
SetIpNetEntry(
    IN PMIB_IPNETROW    pArpEntry
    );

DWORD
WINAPI
DeleteIpNetEntry(
    IN PMIB_IPNETROW    pArpEntry
    );

DWORD
WINAPI
FlushIpNetTable(
    IN DWORD   dwIfIndex
    );


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create or delete a Proxy ARP entry. The dwIndex is the index of  //
// the interface on which to PARP for the dwAddress.  If the interface is   //
// of a type that doesnt support ARP, e.g. PPP, then the call will fail     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
CreateProxyArpEntry(
    IN  DWORD   dwAddress,
    IN  DWORD   dwMask,
    IN  DWORD   dwIfIndex
    );

DWORD
WINAPI
DeleteProxyArpEntry(
    IN  DWORD   dwAddress,
    IN  DWORD   dwMask,
    IN  DWORD   dwIfIndex
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the state of a TCP Connection. The only state that it can be //
// set to is MIB_TCP_STATE_DELETE_TCB.  The complete MIB_TCPROW structure   //
// MUST BE SPECIFIED                                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
SetTcpEntry(
    IN PMIB_TCPROW pTcpRow
    );


DWORD
WINAPI
GetInterfaceInfo(
    IN PIP_INTERFACE_INFO pIfTable,
    OUT PULONG            dwOutBufLen
    );

DWORD
WINAPI
GetUniDirectionalAdapterInfo(OUT PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo,
                 OUT PULONG dwOutBufLen
                 );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the "best" outgoing interface for the specified destination address //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetBestInterface(
    IN  IPAddr  dwDestAddr,
    OUT PDWORD  pdwBestIfIndex
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the best (longest matching prefix) route for the given destination  //
// If the source address is also specified (i.e. is not 0x00000000), and    //
// there are multiple "best" routes to the given destination, the returned  //
// route will be one that goes out over the interface which has an address  //
// that matches the source address                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetBestRoute(
    IN  DWORD               dwDestAddr,
    IN  DWORD               dwSourceAddr, OPTIONAL
    OUT PMIB_IPFORWARDROW   pBestRoute
    );

DWORD
WINAPI
NotifyAddrChange(
    OUT PHANDLE      Handle,
    IN  LPOVERLAPPED overlapped
    );


DWORD
WINAPI
NotifyRouteChange(
    OUT PHANDLE      Handle,
    IN  LPOVERLAPPED overlapped
    );


DWORD
WINAPI
GetAdapterIndex(
    IN LPWSTR  AdapterName,
    OUT PULONG IfIndex
    );

DWORD
WINAPI
AddIPAddress(
    IPAddr  Address,
    IPMask  IpMask,
    DWORD   IfIndex,
    PULONG  NTEContext,
    PULONG  NTEInstance
    );

DWORD
WINAPI
DeleteIPAddress(
    ULONG NTEContext
    );

DWORD
WINAPI
GetNetworkParams(
    PFIXED_INFO pFixedInfo, PULONG pOutBufLen
    );

DWORD
WINAPI
GetAdaptersInfo(
    PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen
    );

DWORD
WINAPI
GetPerAdapterInfo(
    ULONG IfIndex, PIP_PER_ADAPTER_INFO pPerAdapterInfo, PULONG pOutBufLen
    );

DWORD
WINAPI
IpReleaseAddress(
    PIP_ADAPTER_INDEX_MAP  AdapterInfo
    );


DWORD
WINAPI
IpRenewAddress(
    PIP_ADAPTER_INDEX_MAP  AdapterInfo
    );

DWORD
WINAPI
SendARP(
    IPAddr DestIP,
    IPAddr SrcIP,
    PULONG pMacAddr,
    PULONG  PhyAddrLen
    );

BOOL
WINAPI
GetRTTAndHopCount(
    IPAddr DestIpAddress,
    PULONG HopCount,
    ULONG  MaxHops,
    PULONG RTT
    );

DWORD
WINAPI
GetFriendlyIfIndex(
    DWORD IfIndex
    );

#ifdef __cplusplus
}
#endif

#endif //__IPHLPAPI_H__



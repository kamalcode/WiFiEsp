/*--------------------------------------------------------------------
This file is part of the Arduino WiFiEsp library.

The Arduino WiFiEsp library is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

The Arduino WiFiEsp library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Arduino WiFiEsp library.  If not, see
<http://www.gnu.org/licenses/>.
--------------------------------------------------------------------*/

#ifndef WiFiEsp_h
#define WiFiEsp_h

#include <Arduino.h>
#include <IPAddress.h>
#include <inttypes.h>

#include "WiFiEspClient.h"
#include "WiFiEspServer.h"
#include "utility/EspDrv.h"
#include "utility/RingBuffer.h"


class WiFiEspClass
{

public:

	static int16_t _state[MAX_SOCK_NUM];

	WiFiEspClass();
	

	/**
	* Initialize the ESP serial interface
	*/
	static void init(unsigned long baud=115200);

	/**
	* Get firmware version
	*/
	static char* firmwareVersion();


	/**
	* Start Wifi connection for open networks
	*
	* param ssid: Pointer to the SSID string.
	*/
	int begin(char* ssid);


	/**
	* Start Wifi connection with WEP encryption.
	* Configure a key into the device. The key type (WEP-40, WEP-104)
	* is determined by the size of the key (5 bytes for WEP-40, 13 bytes for WEP-104).
	*
	* param ssid: Pointer to the SSID string.
	* param key_idx: The key index to set. Valid values are 0-3.
	* param key: Key input buffer.
	*/
	int begin(char* ssid, uint8_t key_idx, const char* key);


	/**
	* Start Wifi connection with passphrase
	* the most secure supported mode will be automatically selected
	*
	* param ssid: Pointer to the SSID string.
	* param passphrase: Passphrase. Valid characters in a passphrase
	*		  must be between ASCII 32-126 (decimal).
	*/
	int begin(char* ssid, const char*passphrase);


	/**
	* Change Ip configuration settings disabling the DHCP client
	*
	* param local_ip:	Static ip configuration
	*/
	void config(IPAddress local_ip);


	/**
	* Change Ip configuration settings disabling the DHCP client
	*
	* param local_ip:	Static ip configuration
	* param dns_server:		IP configuration for DNS server 1
	*/
	void config(IPAddress local_ip, IPAddress dns_server);


	/**
	* Change Ip configuration settings disabling the DHCP client
	*
	* param local_ip:	Static ip configuration
	* param dns_server:		IP configuration for DNS server 1
	* param gateway :	Static gateway configuration
	*/
	void config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway);


	/** Change Ip configuration settings disabling the DHCP client
	*
	* param local_ip:	Static ip configuration
	* param dns_server:		IP configuration for DNS server 1
	* param gateway:	Static gateway configuration
	* param subnet:		Static Subnet mask
	*/
	void config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);

	/** Change DNS Ip configuration
	*
	* param dns_server1: ip configuration for DNS server 1
	*/
	void setDNS(IPAddress dns_server1);

	/** Change DNS Ip configuration
	*
	* param dns_server1: ip configuration for DNS server 1
	* param dns_server2: ip configuration for DNS server 2
	*
	*/
	void setDNS(IPAddress dns_server1, IPAddress dns_server2);

	/**
	* Disconnect from the network
	*
	* return: one value of wl_status_t enum
	*/
	int disconnect(void);

	/**
	* Get the interface MAC address.
	*
	* return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
	*/
	uint8_t* macAddress(uint8_t* mac);

	/**
	* Get the interface IP address.
	*
	* return: Ip address value
	*/
	IPAddress localIP();

	/**
	* Get the interface subnet mask address.
	*
	* return: subnet mask address value
	*/
	IPAddress subnetMask();

	/**
	* Get the gateway ip address.
	*
	* return: gateway ip address value
	*/
   IPAddress gatewayIP();

	/**
	* Return the current SSID associated with the network
	*
	* return: ssid string
	*/
	char* SSID();

	/**
	* Return the current BSSID associated with the network.
	* It is the MAC address of the Access Point
	*
	* return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
	*/
	uint8_t* BSSID(uint8_t* bssid);

	/**
	* Return the current RSSI /Received Signal Strength in dBm)
	* associated with the network
	*
	* return: signed value
	*/
	int32_t RSSI();

	/**
	* Return the Encryption Type associated with the network
	*
	* return: one value of wl_enc_type enum
	*/
	uint8_t	encryptionType();

	/**
	* Start scan WiFi networks available
	*
	* return: Number of discovered networks
	*/
	int8_t scanNetworks();

	/**
	* Return the SSID discovered during the network scan.
	*
	* param networkItem: specify from which network item want to get the information
	*
	* return: ssid string of the specified item on the networks scanned list
	*/
	char*	SSID(uint8_t networkItem);

	/**
	* Return the encryption type of the networks discovered during the scanNetworks
	*
	* param networkItem: specify from which network item want to get the information
	*
	* return: encryption type (enum wl_enc_type) of the specified item on the networks scanned list
	*/
	uint8_t	encryptionType(uint8_t networkItem);

	/**
	* Return the RSSI of the networks discovered during the scanNetworks
	*
	* param networkItem: specify from which network item want to get the information
	*
	* return: signed value of RSSI of the specified item on the networks scanned list
	*/
	int32_t RSSI(uint8_t networkItem);

	/**
	* Return Connection status.
	*
	* return: one of the value defined in wl_status_t
	*/
	uint8_t status();

	/**
	* Resolve the given hostname to an IP address.
	* param aHostname: Name to be resolved
	* param aResult: IPAddress structure to store the returned IP address
	* result: 1 if aIPAddrString was successfully converted to an IP address,
	*         else error code
	*/
	int hostByName(const char* aHostname, IPAddress& aResult);
	
	
	////////////////////////////////////////////////////////////////////////////
	// Non standard methods
	////////////////////////////////////////////////////////////////////////////

	/**
	* Ping a host.
	*/
	bool ping(const char *host);
	

	friend class WiFiEspClient;
	friend class WiFiEspServer;

private:

};

extern WiFiEspClass WiFi;

#endif

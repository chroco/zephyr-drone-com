#ifndef _DRONE_COM_H_
#define _DRONE_COM_H_

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/net/dhcpv4_server.h>

#define MACSTR "%02X:%02X:%02X:%02X:%02X:%02X"

#define NET_EVENT_WIFI_MASK                                                                        \
	(NET_EVENT_WIFI_CONNECT_RESULT | NET_EVENT_WIFI_DISCONNECT_RESULT |                        \
	 NET_EVENT_WIFI_AP_ENABLE_RESULT | NET_EVENT_WIFI_AP_DISABLE_RESULT |                      \
	 NET_EVENT_WIFI_AP_STA_CONNECTED | NET_EVENT_WIFI_AP_STA_DISCONNECTED)

/* AP Mode Configuration */
#define WIFI_AP_SSID       "Lightside"
#define WIFI_AP_PSK        ""
#define WIFI_AP_IP_ADDRESS "192.168.4.1"
#define WIFI_AP_NETMASK    "255.255.255.0"

/* STA Mode Configuration */
#define WIFI_SSID "Darkside"     /* Replace `SSID` with WiFi ssid. */
#define WIFI_PSK  "AnnieAreYouOK?" /* Replace `PASSWORD` with Router password. */

class Wifi
{
  public:
    Wifi();
    ~Wifi();
  
    int connect(void);
  private:
    static net_if *ap_iface;
    static net_if *sta_iface;

    static wifi_connect_req_params ap_config;
    static wifi_connect_req_params sta_config;

    static net_mgmt_event_callback cb;

    static void wifi_event_handler(net_mgmt_event_callback *, uint32_t mgmt_event, net_if *);
    static void enable_dhcpv4_server(void);
    static int enable_ap_mode(void);
    static int connect_to_wifi(void);
};

int startSocketServer(void);

#endif

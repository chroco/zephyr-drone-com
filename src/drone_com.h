#ifndef _DRONE_COM_H_
#define _DRONE_COM_H_

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/net/dhcpv4_server.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/linker/sections.h>
#include <errno.h>
#include <zephyr/net/net_core.h>
#include <zephyr/net/tls_credentials.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/net/net_event.h>
#include <zephyr/net/conn_mgr_monitor.h>
#include "certificate.h"
#include "common.h"

#define APP_BANNER "Run echo server"


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

class SocketServer
{
  public:
    SocketServer();
    ~SocketServer();
  
    int startEchoServer(void);
  private:
    static void init_app(void);
    //static void event_handler(net_mgmt_event_callback *, uint32_t, net_if *);
    static void start_udp_and_tcp(void);
    static void stop_udp_and_tcp(void);

    //static bool want_to_quit;
    //static bool connected;
    static net_mgmt_event_callback mgmt_cb;
};


#endif

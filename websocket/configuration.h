#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

namespace uranium {

#define SOCKET_DATA_MAX_LEN        128 // byte

#define SERVER_PULL_CLIENT_TIMEOUT 100 // ms
#define SERVER_POLL_DATA_TIMEOUT   200

#define CLIENT_POLL_DATA_TIMEOUT   200
#define CLIENT_CONNECT_RETRY_TIME  100
#define CLIENT_CONNECT_NOTIFIER_TIME 5

#define MAX_CLIENT_ALLOWED         20

#define TESTER_SERVER_PORT         8083

};

#endif

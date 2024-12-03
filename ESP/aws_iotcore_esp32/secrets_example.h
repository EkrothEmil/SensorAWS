#include <pgmspace.h>

#define SECRET

const char WIFI_SSID[] = "Mimmis hus";
const char WIFI_PASSWORD[] = "Grevture6";
const char AWS_IOT_ENDPOINT[] = "ayh7f270zn632-ats.iot.eu-north-1.amazonaws.com";


// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----

)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
-----END RSA PRIVATE KEY-----
)KEY";

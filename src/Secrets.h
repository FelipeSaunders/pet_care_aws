#include <pgmspace.h>

#define THINGNAME "GP_PET_Care"

const char WIFI_SSID[] = "uaifai-brum";
const char WIFI_PASSWORD[] = "bemvindoaocesar";

const char AWS_IOT_ENDPOINT[] = "a34ypir054ngjb-ats.iot.us-east-2.amazonaws.com";

static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUIUPlSZNibjTjnozVd8A2O4kxb34wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDIyOTE0MTIz
M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL/bucTDDJbjZo0rEvk3
GqsSnA8RPQDr9ceMDiNpK4sO/UNWvni8Ue8Rro7Tuv+PNevl4b/YRtm9VNvh2WML
3yGnkWBY0k1QlQ3ENmWCOIifs8A67K2pgfblJvVvuxI0Eq+ev51JSsoy8TTLVyg/
MgvsCf+o3yQIz/xZT8XuD/ScjirZN6/nPw6uIHaz4P3MFNXrPJHYGSSO7IW6jDZT
98/QjFwOfxnByXDaRbJHy4MYp7XlV60Qd1XdDJZzodx2zoH+vfFafE0aym8g0krM
cOABs4EAuqD79eLQtVHqiHv9TGdarcOYX+ex8sOtxbpKwiVeabucOLq/ut7jFOB5
o/cCAwEAAaNgMF4wHwYDVR0jBBgwFoAUU0+wjQmJswSXfP+cbkhXHJd/2AwwHQYD
VR0OBBYEFCP/fK5tLlEPfiZD7G1G+71JMiGOMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAv5PlkcnGwqGNj5wt7DGYthMmu
HV1tcqUjqdk3ZF85LUBxkPKdgu0PinwqMrQ/AHKxSKGL7MkTbfk6MYOJpxmisTic
Uhbi6LJTkplPRFbz8Bjrb72FHKNonqsuvSRdD0lN8pXNxild/TNcX48dWzTUXyCR
fg2wMnOMPfgdZOmsGjt5jwuoYKIqZ+dLn6GGiT6YNozCGFt28CDdErs3qC7H/AgI
GalQawwD9gNVp/QjuVtzk+1ib5DMwdPwDJOxngT5w/a6Ta1aEyklgdUtSVa6pClH
uDsEzgUFjho5Q1MxcSxUYE3CT8adpl88sXvS0bqvnGheep4bg3tggIfvVJ9z
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAv9u5xMMMluNmjSsS+TcaqxKcDxE9AOv1x4wOI2kriw79Q1a+
eLxR7xGujtO6/4816+Xhv9hG2b1U2+HZYwvfIaeRYFjSTVCVDcQ2ZYI4iJ+zwDrs
ramB9uUm9W+7EjQSr56/nUlKyjLxNMtXKD8yC+wJ/6jfJAjP/FlPxe4P9JyOKtk3
r+c/Dq4gdrPg/cwU1es8kdgZJI7shbqMNlP3z9CMXA5/GcHJcNpFskfLgxinteVX
rRB3Vd0MlnOh3HbOgf698Vp8TRrKbyDSSsxw4AGzgQC6oPv14tC1UeqIe/1MZ1qt
w5hf57Hyw63FukrCJV5pu5w4ur+63uMU4Hmj9wIDAQABAoIBAQC1s+94PhIKRUu2
nvjVNi73niRW0Mipus+HMUmil9Q5WvTZdanmxtQCSwi7FCOiLYuv4oOvIbHYPcvE
g11SxMeKJB021mg1+P9xjkbGVFIecsHWaPgGcOc5YUVIZY0SbGbWFM78s5E1dpGi
ooHlCBTp3Z6KlvDeO8pfAGbg2doamxOLPpWagWEt7TZx9qBQYsZk7aLsVHvE8w8r
DoF9XmueCuUVc49I+yCCIv62t5vcRnbo7uTypKmT4lKtW/NmakeIENnnSdZaICv/
nuXBQlCiZxQ+Tg9XDS/C1c7fmGPNfnG7G0q2YsCbpwTorIzw0vPheCTo04JaYo9B
k2eKKu1BAoGBAPuo+We0ImbbzDZlkPCBWpfTgG5xF5f/rc5hKzrDnXqmfLJTCqPx
7N4AAiFmVI904q5v6nQJeTB3+GPg6yD5ZDgOAmrc2NKEY+wINlv8pSwVInCGUJE2
q0CgfjRUjUq21Z4CLOtSDJPTQdLng5d1vpSnC4GhWGpvdvfsf8YUlLx5AoGBAMMq
vUdPK7HPibbcRblvrXa1WtG3ZeFfBfUWRACbtfkxFndTd9FWR71n9DORGa5ODHOX
nxHkpwxL5wpparzlp+dEa5RDZR1nBOETV2SaLRF20NkSmczXGePVOxYLLRYEwxzG
9VhjIyNHTY8Kojry9xk7bJnMhj8urEEfjG7L0WfvAoGAL7M5gsSL+L8UmALsVAnQ
qBJ4t3ZMKI1X3lRgo0TMpqDD5fEDhUunv/R0cuw4fvCCvtmLsO7Sv7Mdq6DIMHnU
2yMcpjCyEETzw5tS4mCi1hYzbuymfL/F+fvxr+2O0miRWN/Er93fcG2MfnNPZ/fz
Za276pgwcAwsmpWDKoJgJtECgYEAwGsU7odqBwcdOcJ2o9stZMps3jM5KTgsgXUQ
WqEqiqMRCVir2yJ73IvvQiAe97FPqW+lj1imMgNrqOJCMDckkWjtv+GqgZCeSOJu
2WsAYCWKx1oFdOXmSrBibttZ+kl7rJWkMx6a+B9Gom7Tf9coNCJYclIpUYXMovBd
3qbosNUCgYEAtAmBjTvlua19QeblJsqyyokMT74B+F+izbvnBfNB5U+fzaXAsxOT
x9Hlu0JsNbM6aC0WPLKig/eTVnILOb2CvJ6I35BNPd9k9iYyIYAF7TtT91oixMNs
po0M/mALmTo0KZPtVaOjW6d9h5FkGazCq0LyomTITd3VP9Dpa1PjcMw=
-----END RSA PRIVATE KEY-----
)KEY";


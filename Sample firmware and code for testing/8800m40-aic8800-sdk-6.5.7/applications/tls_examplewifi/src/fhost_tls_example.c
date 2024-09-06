 /**
 *******************************************************************************
 *
 * @file fhost_example.c
 *
 * @brief Definition of an example application task for Fully Hosted firmware.
 *
 * Copyright (C) RivieraWaves 2019-2019
 *
 *******************************************************************************
 */

#include "fhost.h"
#include "netdb.h"
#ifndef MBEDTLS_DRBG_ALT
#include "ctr_drbg.h"
#endif

// select one of them
#define GITHUB_DOWNLOAD_TEST
//#define MBED_HELLOWORLD_TEST

/* Change to a number between 1 and 4 to debug the TLS connection */
#define DEBUG_LEVEL 1

/* Change to 1 to skip certificate verification (UNSAFE, for debug only!) */
#define UNSAFE 1

#include "platform.h"
#include "ssl.h"
#include "entropy.h"
#include "ctr_drbg.h"
#include "error.h"
#if DEBUG_LEVEL > 0
#include "debug.h"
#endif


/**
 *******************************************************************************
 * @defgroup FHOST_EXAMPLE FHOST_EXAMPLE
 * @ingroup FHOST
 * @{
 *
 * This module contains code of an example application.\n
 * Each application needs to define a few mandatory functions:
 * - fhost_application_init: Called during firmware intialization to prepare
 *   the application task.\n
 *   In this example the function creates a single task.
 *
 * - fhost_config_get_next_item: Used by control task to retrieve runtime
 *   configuration of the wifi firmware.\n
 *   In this example the configuration is read from variable @ref example_config
 *
 * This example application is very basic:
 * - First it connect to an Access Point.
 *   Credentials/config of the AP are hardcoded in @ref example_ap_cfg.
 * - Then a DHCP procedure is started to retrieve an IP address.
 * - Finally it connects to a website (forismatic) to retrieve a random quote
 *
 *******************************************************************************
 */
#ifdef GITHUB_DOWNLOAD_TEST
const char *HTTPS_SERVER_NAME = "codeload.github.com";
const char HTTPS_PATH[] = "/ARMmbed/mbed-os/legacy.tar.gz/mbed-os-5.15.0";
#endif /* GITHUB_DOWNLOAD_TEST */
#ifdef MBED_HELLOWORLD_TEST
const char *HTTPS_SERVER_NAME = "os.mbed.com";
const char HTTPS_PATH[] = "/media/uploads/mbed_official/hello.txt";
#endif /* MBED_HELLOWORLD_TEST */

const int HTTPS_SERVER_PORT = 443;
const int RECV_BUFFER_SIZE = 1536;

const uint16_t HTTPS_PATH_LEN = sizeof(HTTPS_PATH) - 1;

/* Test related data */
const char *HTTPS_OK_STR = "200 OK";
const char *HTTPS_HELLO_STR = "Hello world!";

#ifndef MBEDTLS_DRBG_ALT
/* personalization string for the drbg */
const char *DRBG_PERS = "mbed TLS helloword client";
#endif

/* List of trusted root CA certificates
 * currently only GlobalSign, the CA for developer.mbed.org
 *
 * To add more than one root, just concatenate them.
 */
const char SSL_CA_PEM[] =
/* GlobalSign Root certificate */
#ifdef GITHUB_DOWNLOAD_TEST
"-----BEGIN CERTIFICATE-----\n"
"MIIEFzCCAv+gAwIBAgIQB/LzXIeod6967+lHmTUlvTANBgkqhkiG9w0BAQwFADBh\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
"QTAeFw0yMTA0MTQwMDAwMDBaFw0zMTA0MTMyMzU5NTlaMFYxCzAJBgNVBAYTAlVT\n"
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxMDAuBgNVBAMTJ0RpZ2lDZXJ0IFRMUyBI\n"
"eWJyaWQgRUNDIFNIQTM4NCAyMDIwIENBMTB2MBAGByqGSM49AgEGBSuBBAAiA2IA\n"
"BMEbxppbmNmkKaDp1AS12+umsmxVwP/tmMZJLwYnUcu/cMEFesOxnYeJuq20ExfJ\n"
"qLSDyLiQ0cx0NTY8g3KwtdD3ImnI8YDEe0CPz2iHJlw5ifFNkU3aiYvkA8ND5b8v\n"
"c6OCAYIwggF+MBIGA1UdEwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFAq8CCkXjKU5\n"
"bXoOzjPHLrPt+8N6MB8GA1UdIwQYMBaAFAPeUDVW0Uy7ZvCj4hsbw5eyPdFVMA4G\n"
"A1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwdgYI\n"
"KwYBBQUHAQEEajBoMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5j\n"
"b20wQAYIKwYBBQUHMAKGNGh0dHA6Ly9jYWNlcnRzLmRpZ2ljZXJ0LmNvbS9EaWdp\n"
"Q2VydEdsb2JhbFJvb3RDQS5jcnQwQgYDVR0fBDswOTA3oDWgM4YxaHR0cDovL2Ny\n"
"bDMuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0R2xvYmFsUm9vdENBLmNybDA9BgNVHSAE\n"
"NjA0MAsGCWCGSAGG/WwCATAHBgVngQwBATAIBgZngQwBAgEwCAYGZ4EMAQICMAgG\n"
"BmeBDAECAzANBgkqhkiG9w0BAQwFAAOCAQEAR1mBf9QbH7Bx9phdGLqYR5iwfnYr\n"
"6v8ai6wms0KNMeZK6BnQ79oU59cUkqGS8qcuLa/7Hfb7U7CKP/zYFgrpsC62pQsY\n"
"kDUmotr2qLcy/JUjS8ZFucTP5Hzu5sn4kL1y45nDHQsFfGqXbbKrAjbYwrwsAZI/\n"
"BKOLdRHHuSm8EdCGupK8JvllyDfNJvaGEwwEqonleLHBTnm8dqMLUeTF0J5q/hos\n"
"Vq4GNiejcxwIfZMy0MJEGdqN9A57HSgDKwmKdsp33Id6rHtSJlWncg+d0ohP/rEh\n"
"xRqhqjn1VtvChMQ1H3Dau0bwhr9kAMQ+959GG50jBbl9s08PqUU643QwmA==\n"
"-----END CERTIFICATE-----\n";
#endif
#if 0//def GITHUB_DOWNLOAD_TEST
"-----BEGIN CERTIFICATE-----\n"
"MIIHQjCCBiqgAwIBAgIQCgYwQn9bvO1pVzllk7ZFHzANBgkqhkiG9w0BAQsFADB1\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
"d3cuZGlnaWNlcnQuY29tMTQwMgYDVQQDEytEaWdpQ2VydCBTSEEyIEV4dGVuZGVk\n"
"IFZhbGlkYXRpb24gU2VydmVyIENBMB4XDTE4MDUwODAwMDAwMFoXDTIwMDYwMzEy\n"
"MDAwMFowgccxHTAbBgNVBA8MFFByaXZhdGUgT3JnYW5pemF0aW9uMRMwEQYLKwYB\n"
"BAGCNzwCAQMTAlVTMRkwFwYLKwYBBAGCNzwCAQITCERlbGF3YXJlMRAwDgYDVQQF\n"
"Ewc1MTU3NTUwMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQG\n"
"A1UEBxMNU2FuIEZyYW5jaXNjbzEVMBMGA1UEChMMR2l0SHViLCBJbmMuMRMwEQYD\n"
"VQQDEwpnaXRodWIuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA\n"
"xjyq8jyXDDrBTyitcnB90865tWBzpHSbindG/XqYQkzFMBlXmqkzC+FdTRBYyneZ\n"
"w5Pz+XWQvL+74JW6LsWNc2EF0xCEqLOJuC9zjPAqbr7uroNLghGxYf13YdqbG5oj\n"
"/4x+ogEG3dF/U5YIwVr658DKyESMV6eoYV9mDVfTuJastkqcwero+5ZAKfYVMLUE\n"
"sMwFtoTDJFmVf6JlkOWwsxp1WcQ/MRQK1cyqOoUFUgYylgdh3yeCDPeF22Ax8AlQ\n"
"xbcaI+GwfQL1FB7Jy+h+KjME9lE/UpgV6Qt2R1xNSmvFCBWu+NFX6epwFP/JRbkM\n"
"fLz0beYFUvmMgLtwVpEPSwIDAQABo4IDeTCCA3UwHwYDVR0jBBgwFoAUPdNQpdag\n"
"re7zSmAKZdMh1Pj41g8wHQYDVR0OBBYEFMnCU2FmnV+rJfQmzQ84mqhJ6kipMCUG\n"
"A1UdEQQeMByCCmdpdGh1Yi5jb22CDnd3dy5naXRodWIuY29tMA4GA1UdDwEB/wQE\n"
"AwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwdQYDVR0fBG4wbDA0\n"
"oDKgMIYuaHR0cDovL2NybDMuZGlnaWNlcnQuY29tL3NoYTItZXYtc2VydmVyLWcy\n"
"LmNybDA0oDKgMIYuaHR0cDovL2NybDQuZGlnaWNlcnQuY29tL3NoYTItZXYtc2Vy\n"
"dmVyLWcyLmNybDBLBgNVHSAERDBCMDcGCWCGSAGG/WwCATAqMCgGCCsGAQUFBwIB\n"
"FhxodHRwczovL3d3dy5kaWdpY2VydC5jb20vQ1BTMAcGBWeBDAEBMIGIBggrBgEF\n"
"BQcBAQR8MHowJAYIKwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTBS\n"
"BggrBgEFBQcwAoZGaHR0cDovL2NhY2VydHMuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0\n"
"U0hBMkV4dGVuZGVkVmFsaWRhdGlvblNlcnZlckNBLmNydDAMBgNVHRMBAf8EAjAA\n"
"MIIBfgYKKwYBBAHWeQIEAgSCAW4EggFqAWgAdgCkuQmQtBhYFIe7E6LMZ3AKPDWY\n"
"BPkb37jjd80OyA3cEAAAAWNBYm0KAAAEAwBHMEUCIQDRZp38cTWsWH2GdBpe/uPT\n"
"Wnsu/m4BEC2+dIcvSykZYgIgCP5gGv6yzaazxBK2NwGdmmyuEFNSg2pARbMJlUFg\n"
"U5UAdgBWFAaaL9fC7NP14b1Esj7HRna5vJkRXMDvlJhV1onQ3QAAAWNBYm0tAAAE\n"
"AwBHMEUCIQCi7omUvYLm0b2LobtEeRAYnlIo7n6JxbYdrtYdmPUWJQIgVgw1AZ51\n"
"vK9ENinBg22FPxb82TvNDO05T17hxXRC2IYAdgC72d+8H4pxtZOUI5eqkntHOFeV\n"
"CqtS6BqQlmQ2jh7RhQAAAWNBYm3fAAAEAwBHMEUCIQChzdTKUU2N+XcqcK0OJYrN\n"
"8EYynloVxho4yPk6Dq3EPgIgdNH5u8rC3UcslQV4B9o0a0w204omDREGKTVuEpxG\n"
"eOQwDQYJKoZIhvcNAQELBQADggEBAHAPWpanWOW/ip2oJ5grAH8mqQfaunuCVE+v\n"
"ac+88lkDK/LVdFgl2B6kIHZiYClzKtfczG93hWvKbST4NRNHP9LiaQqdNC17e5vN\n"
"HnXVUGw+yxyjMLGqkgepOnZ2Rb14kcTOGp4i5AuJuuaMwXmCo7jUwPwfLe1NUlVB\n"
"Kqg6LK0Hcq4K0sZnxE8HFxiZ92WpV2AVWjRMEc/2z2shNoDvxvFUYyY1Oe67xINk\n"
"myQKc+ygSBZzyLnXSFVWmHr3u5dcaaQGGAR42v6Ydr4iL38Hd4dOiBma+FXsXBIq\n"
"WUjbST4VXmdaol7uzFMojA4zkxQDZAvF5XgJlAFadfySna/teik=\n"
"-----END CERTIFICATE-----\n";
#endif /* GITHUB_DOWNLOAD_TEST */

#ifdef MBED_HELLOWORLD_TEST
"-----BEGIN CERTIFICATE-----\n"
"MIIEkjCCA3qgAwIBAgITBn+USionzfP6wq4rAfkI7rnExjANBgkqhkiG9w0BAQsF\n"
"ADCBmDELMAkGA1UEBhMCVVMxEDAOBgNVBAgTB0FyaXpvbmExEzARBgNVBAcTClNj\n"
"b3R0c2RhbGUxJTAjBgNVBAoTHFN0YXJmaWVsZCBUZWNobm9sb2dpZXMsIEluYy4x\n"
"OzA5BgNVBAMTMlN0YXJmaWVsZCBTZXJ2aWNlcyBSb290IENlcnRpZmljYXRlIEF1\n"
"dGhvcml0eSAtIEcyMB4XDTE1MDUyNTEyMDAwMFoXDTM3MTIzMTAxMDAwMFowOTEL\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
"jgSubJrIqg0CAwEAAaOCATEwggEtMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/\n"
"BAQDAgGGMB0GA1UdDgQWBBSEGMyFNOy8DJSULghZnMeyEE4KCDAfBgNVHSMEGDAW\n"
"gBScXwDfqgHXMCs4iKK4bUqc8hGRgzB4BggrBgEFBQcBAQRsMGowLgYIKwYBBQUH\n"
"MAGGImh0dHA6Ly9vY3NwLnJvb3RnMi5hbWF6b250cnVzdC5jb20wOAYIKwYBBQUH\n"
"MAKGLGh0dHA6Ly9jcnQucm9vdGcyLmFtYXpvbnRydXN0LmNvbS9yb290ZzIuY2Vy\n"
"MD0GA1UdHwQ2MDQwMqAwoC6GLGh0dHA6Ly9jcmwucm9vdGcyLmFtYXpvbnRydXN0\n"
"LmNvbS9yb290ZzIuY3JsMBEGA1UdIAQKMAgwBgYEVR0gADANBgkqhkiG9w0BAQsF\n"
"AAOCAQEAYjdCXLwQtT6LLOkMm2xF4gcAevnFWAu5CIw+7bMlPLVvUOTNNWqnkzSW\n"
"MiGpSESrnO09tKpzbeR/FoCJbM8oAxiDR3mjEH4wW6w7sGDgd9QIpuEdfF7Au/ma\n"
"eyKdpwAJfqxGF4PcnCZXmTA5YpaP7dreqsXMGz7KQ2hsVxa81Q4gLv7/wmpdLqBK\n"
"bRRYh5TmOTFffHPLkIhqhBGWJ6bt2YFGpn6jcgAKUj6DiAdjd4lpFw85hdKrCEVN\n"
"0FE6/V1dN2RMfjCyVSRCnTawXZwXgWHxyvkQAiSr6w10kY17RSlQOYiypok1JR4U\n"
"akcjMS9cmvqtmg5iUaQqqcT5NJ0hGA==\n"
"-----END CERTIFICATE-----\n";
#endif /* MBED_HELLOWORLD_TEST */
#if 0
"-----BEGIN CERTIFICATE-----\n"
"MIIEaTCCA1GgAwIBAgILBAAAAAABRE7wQkcwDQYJKoZIhvcNAQELBQAwVzELMAkG\n"
"A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\n"
"b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw0xNDAyMjAxMDAw\n"
"MDBaFw0yNDAyMjAxMDAwMDBaMGYxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\n"
"YWxTaWduIG52LXNhMTwwOgYDVQQDEzNHbG9iYWxTaWduIE9yZ2FuaXphdGlvbiBW\n"
"YWxpZGF0aW9uIENBIC0gU0hBMjU2IC0gRzIwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n"
"DwAwggEKAoIBAQDHDmw/I5N/zHClnSDDDlM/fsBOwphJykfVI+8DNIV0yKMCLkZc\n"
"C33JiJ1Pi/D4nGyMVTXbv/Kz6vvjVudKRtkTIso21ZvBqOOWQ5PyDLzm+ebomchj\n"
"SHh/VzZpGhkdWtHUfcKc1H/hgBKueuqI6lfYygoKOhJJomIZeg0k9zfrtHOSewUj\n"
"mxK1zusp36QUArkBpdSmnENkiN74fv7j9R7l/tyjqORmMdlMJekYuYlZCa7pnRxt\n"
"Nw9KHjUgKOKv1CGLAcRFrW4rY6uSa2EKTSDtc7p8zv4WtdufgPDWi2zZCHlKT3hl\n"
"2pK8vjX5s8T5J4BO/5ZS5gIg4Qdz6V0rvbLxAgMBAAGjggElMIIBITAOBgNVHQ8B\n"
"Af8EBAMCAQYwEgYDVR0TAQH/BAgwBgEB/wIBADAdBgNVHQ4EFgQUlt5h8b0cFilT\n"
"HMDMfTuDAEDmGnwwRwYDVR0gBEAwPjA8BgRVHSAAMDQwMgYIKwYBBQUHAgEWJmh0\n"
"dHBzOi8vd3d3Lmdsb2JhbHNpZ24uY29tL3JlcG9zaXRvcnkvMDMGA1UdHwQsMCow\n"
"KKAmoCSGImh0dHA6Ly9jcmwuZ2xvYmFsc2lnbi5uZXQvcm9vdC5jcmwwPQYIKwYB\n"
"BQUHAQEEMTAvMC0GCCsGAQUFBzABhiFodHRwOi8vb2NzcC5nbG9iYWxzaWduLmNv\n"
"bS9yb290cjEwHwYDVR0jBBgwFoAUYHtmGkUNl8qJUC99BM00qP/8/UswDQYJKoZI\n"
"hvcNAQELBQADggEBAEYq7l69rgFgNzERhnF0tkZJyBAW/i9iIxerH4f4gu3K3w4s\n"
"32R1juUYcqeMOovJrKV3UPfvnqTgoI8UV6MqX+x+bRDmuo2wCId2Dkyy2VG7EQLy\n"
"XN0cvfNVlg/UBsD84iOKJHDTu/B5GqdhcIOKrwbFINihY9Bsrk8y1658GEV1BSl3\n"
"30JAZGSGvip2CTFvHST0mdCF/vIhCPnG9vHQWe3WVjwIKANnuvD58ZAWR65n5ryA\n"
"SOlCdjSXVWkkDoPWoC209fN5ikkodBpBocLTJIg1MGCUF7ThBCIxPTsvFwayuJ2G\n"
"K1pp74P1S8SqtCr4fKGxhZSM9AyHDPSsQPhZSZg=\n"
"-----END CERTIFICATE-----\n";
#endif

volatile bool _error;           /**< Status flag for an error */
int _tcpsocket = 0;

/******************************************************************************
 * Application code:
 *****************************************************************************/
/**
 * Helper for pretty-printing mbed TLS error codes
 */
static void print_mbedtls_error(const char *name, int err) {
    char buf[128];
    mbedtls_strerror(err, buf, sizeof (buf));
    dbg("%s() failed: -0x%04x (%d): %s\r\n", name, -err, err, buf);
}

#if DEBUG_LEVEL > 0
/**
 * Debug callback for mbed TLS
 * Just prints on the USB serial port
 */
static void my_debug(void *ctx, int level, const char *file, int line,
                     const char *str)
{
    const char *p, *basename;
    (void) ctx;

    /* Extract basename from file */
    for(p = basename = file; *p != '\0'; p++) {
        if(*p == '/' || *p == '\\') {
            basename = p + 1;
        }
    }

    dbg("%s:%04d: |%d| %s", basename, line, level, str);
}

/**
 * Certificate verification callback for mbed TLS
 * Here we only use it to display information on each cert in the chain
 */
static int my_verify(void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags)
{
    char buf[1024];
    int ret = 0;

    *flags &= ~MBEDTLS_X509_BADCERT_FUTURE & ~MBEDTLS_X509_BADCERT_EXPIRED;

    ret = mbedtls_x509_crt_info(buf, sizeof (buf), "\r  ", crt);
    if (ret < 0) {
        dbg("mbedtls_x509_crt_info() returned -0x%04X\n", -ret);
    } else {
        ret = 0;
        dbg("Verifying certificate at depth %d:\n%s\n",
                       depth, buf);
    }

    return ret;
}
#endif

/**
 * Receive callback for mbed TLS
 */
static int ssl_recv(void *ctx, unsigned char *buf, size_t len) {
    int r = -1;

    r = recv(_tcpsocket, buf, len, 0);
    if(-1 == r){
        return MBEDTLS_ERR_SSL_WANT_READ;
    }else if(r < 0){
        return -1;
    }else{
        return r;
    }
}

/**
 * Send callback for mbed TLS
 */
static int ssl_send(void *ctx, const unsigned char *buf, size_t len) {
   int size = -1;

    size =  send(_tcpsocket, buf, len, 0);
    if(size > 0){
        return len;
    }else if(size < 0){
        return -1;
    }else{
        return size;
    }
}

void onError(int s, int error) {
    dbg("MBED: Socket Error: %d\r\n", error);
    close(s);
    _error = true;
}

static void tls_task(void)
{
    const char *_domain = HTTPS_SERVER_NAME;            /**< The domain name of the HTTPS server */
    char _buffer[RECV_BUFFER_SIZE]; /**< The response buffer */
    uint16_t _bpos;                 /**< The current offset in the response buffer */
    volatile bool _got200;          /**< Status flag for HTTPS 200 */
    volatile bool _gothello;        /**< Status flag for finding the test string */

#ifndef MBEDTLS_DRBG_ALT
    mbedtls_entropy_context _entropy;
    mbedtls_ctr_drbg_context _ctr_drbg;
#endif
    mbedtls_x509_crt _cacert;
    mbedtls_ssl_context _ssl;
    mbedtls_ssl_config _ssl_conf;

    _error = false;
    _gothello = false;
    _got200 = false;
    _bpos = 0;

    _tcpsocket = socket(AF_INET, SOCK_STREAM, 0);

#ifndef MBEDTLS_DRBG_ALT
    mbedtls_entropy_init(&_entropy);
    mbedtls_ctr_drbg_init(&_ctr_drbg);
#endif
    mbedtls_x509_crt_init(&_cacert);
    mbedtls_ssl_init(&_ssl);
    mbedtls_ssl_config_init(&_ssl_conf);

    /* Fill the request buffer */
    #ifdef GITHUB_DOWNLOAD_TEST
    _bpos = os_snprintf(_buffer, sizeof(_buffer) - 1, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n"
                                                      "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.117 Safari/537.36\r\n"
                                                      "Sec-Fetch-User: ?1\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"
                                                      "Sec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nAccept-Encoding: gzip, deflate, br\r\n"
                                                      "Accept-Language: zh-CN,zh;q=0.9\r\nCookie: __utmz=156426281.1578992468.1.1.utmcsr=baidu|utmccn=(organic)|utmcmd=organic; __utma=156426281.2087582525.1578992468.1578996291.1579003161.3; __utmc=156426281; __utmb=156426281.1.10.1579003161\r\n\r\n", HTTPS_PATH, HTTPS_SERVER_NAME);
    #endif /* GITHUB_DOWNLOAD_TEST */
    #ifdef MBED_HELLOWORLD_TEST
    _bpos = os_snprintf(_buffer, sizeof(_buffer) - 1, "GET %s HTTP/1.1\nHost: %s\n\n", HTTPS_PATH, HTTPS_SERVER_NAME);
    #endif /* MBED_HELLOWORLD_TEST */
    /*
     * Initialize TLS-related stuf.
     */
    int ret;
#ifndef MBEDTLS_DRBG_ALT
    if ((ret = mbedtls_ctr_drbg_seed(&_ctr_drbg, mbedtls_entropy_func, &_entropy,
                      (const unsigned char *) DRBG_PERS,
                      sizeof (DRBG_PERS))) != 0) {
        print_mbedtls_error("mbedtls_crt_drbg_init", ret);
        _error = true;
        return;
    }
#endif
    if ((ret = mbedtls_x509_crt_parse(&_cacert, (const unsigned char *) SSL_CA_PEM,
                       sizeof (SSL_CA_PEM))) != 0) {
        print_mbedtls_error("mbedtls_x509_crt_parse", ret);
        _error = true;
        return;
    }

    if ((ret = mbedtls_ssl_config_defaults(&_ssl_conf,
                    MBEDTLS_SSL_IS_CLIENT,
                    MBEDTLS_SSL_TRANSPORT_STREAM,
                    MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
        print_mbedtls_error("mbedtls_ssl_config_defaults", ret);
        _error = true;
        return;
    }

    mbedtls_ssl_conf_ca_chain(&_ssl_conf, &_cacert, NULL);
    mbedtls_ssl_conf_max_frag_len(&_ssl_conf, MBEDTLS_SSL_MAX_FRAG_LEN_4096);
#ifndef MBEDTLS_DRBG_ALT
    mbedtls_ssl_conf_rng(&_ssl_conf, mbedtls_ctr_drbg_random, &_ctr_drbg);
#else
    mbedtls_ssl_conf_rng(&_ssl_conf, mbedtls_ctr_drbg_random, NULL);
#endif

#if UNSAFE
    mbedtls_ssl_conf_authmode(&_ssl_conf, MBEDTLS_SSL_VERIFY_REQUIRED);
#endif

#if DEBUG_LEVEL > 0
    mbedtls_ssl_conf_verify(&_ssl_conf, my_verify, NULL);
    mbedtls_ssl_conf_dbg(&_ssl_conf, my_debug, NULL);
    mbedtls_debug_set_threshold(DEBUG_LEVEL);
#endif

    if ((ret = mbedtls_ssl_setup(&_ssl, &_ssl_conf)) != 0) {
        print_mbedtls_error("mbedtls_ssl_setup", ret);
        _error = true;
        return;
    }

    mbedtls_ssl_set_hostname(&_ssl, HTTPS_SERVER_NAME);

    mbedtls_ssl_set_bio(&_ssl, (void *)(_tcpsocket),
                               ssl_send, ssl_recv, NULL );

    /* Connect to the server */
    dbg("Connecting with %s\r\n", _domain);

    struct addrinfo hints;
    struct addrinfo *res = NULL;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_NUMERICSERV;
    if (getaddrinfo(_domain, "443", &hints, &res))
    {
        return;
    }
    else
    {
        if (connect(_tcpsocket, res->ai_addr, res->ai_addrlen) < 0)
           return;

        freeaddrinfo(res);
        res = NULL;
    }

   /* Start the handshake, the rest will be done in onReceive() */
    dbg("Starting the TLS handshake...\r\n");
    ret = mbedtls_ssl_handshake(&_ssl);
    if (ret < 0) {
        //if (ret != MBEDTLS_ERR_SSL_WANT_READ &&
        //    ret != MBEDTLS_ERR_SSL_WANT_WRITE)
            {
            print_mbedtls_error("mbedtls_ssl_handshake", ret);
            onError(_tcpsocket, -1 );
        }
        return;
    }
    ret = mbedtls_ssl_write(&_ssl, (const unsigned char *) _buffer, _bpos);
    if (ret < 0) {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ &&
            ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
            print_mbedtls_error("mbedtls_ssl_write", ret);
            onError(_tcpsocket, -1 );
        }
        return;
    }

    /* It also means the handshake is done, time to print info */
    dbg("TLS connection to %s established\r\n", HTTPS_SERVER_NAME);

    char buf[1024];
    mbedtls_x509_crt_info(buf, sizeof(buf), "\r    ",
                    mbedtls_ssl_get_peer_cert(&_ssl));
    dbg("Server certificate:\r\n%s\r", buf);

#if UNSAFE
    uint32_t flags = mbedtls_ssl_get_verify_result(&_ssl);
    if( flags != 0 )
    {
        mbedtls_x509_crt_verify_info(buf, sizeof (buf), "\r  ! ", flags);
        dbg("Certificate verification failed:\r\n%s\r\r\n", buf);
    }
    else
#endif
        dbg("Certificate verification passed\r\n\r\n");


    /* Read data out of the socket */
    ret = mbedtls_ssl_read(&_ssl, (unsigned char *) _buffer, sizeof(_buffer));
    if (ret < 0) {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
            print_mbedtls_error("mbedtls_ssl_read", ret);
            onError(_tcpsocket, -1 );
        }
        return;
    }
    _bpos = (uint16_t)(ret);

    _buffer[_bpos] = 0;

    /* Print status messages */
    dbg("HTTPS: Received %d chars from server\r\n", _bpos);

    /* Check each of the flags */
    _got200 = _got200 || strstr(_buffer, HTTPS_OK_STR) != NULL;
    #ifdef MBED_HELLOWORLD_TEST
    _gothello = _gothello || strstr(_buffer, HTTPS_HELLO_STR) != NULL;
    dbg("HTTPS: Received '%s' status ... %s\r\n", HTTPS_HELLO_STR, _gothello ? "[OK]" : "[FAIL]");
    _error = !(_got200 && _gothello);
    #endif /* MBED_HELLOWORLD_TEST */

    dbg("HTTPS: Received 200 OK status ... %s\r\n", _got200 ? "[OK]" : "[FAIL]");
    dbg("HTTPS: Received message:\r\n\r\n");
    dbg("%s\r\n", _buffer);


    #ifdef GITHUB_DOWNLOAD_TEST
    do {
        ret = mbedtls_ssl_read(&_ssl, (unsigned char *) _buffer, sizeof(_buffer));
        if (ret < 0) {
            if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
                print_mbedtls_error("mbedtls_ssl_read", ret);
                onError(_tcpsocket, -1 );
            }
            return;
        }
        _bpos = (uint16_t)(ret);
        _buffer[_bpos] = 0;
        dbg("HTTPS: Received %d chars from server\r\n", _bpos);
    } while(_bpos > 0);
    #endif /* GITHUB_DOWNLOAD_TEST */

    if (_tcpsocket > 0)
        close(_tcpsocket);
}

/*
 * Entry point of this example application
 */
static RTOS_TASK_FCT(fhost_tls_example_task)
{
    #if 0
    mbedtls_sha256_self_test(1); // passed

    mbedtls_aes_self_test(1); // passed

    mbedtls_ecp_self_test(1); // passed

    //mbedtls_mpi_self_test(1); // not support

    mbedtls_gcm_self_test(1); // passed
    while(1) ;
    #endif


    const char *ssid = "tls", *pw = "password";
    static uint8_t mac_addr[6] = {0x88, 0x00, 0x33, 0xee, 0x49, 0x67};
    set_mac_address(mac_addr);

    wlan_start_sta(ssid, pw, 0);

    //TLS TASK
    tls_task();

    // Delete task
    rtos_task_delete(NULL);
}

/******************************************************************************
 * Fhost FW interfaces:
 * These are the functions required by the fhost FW that are specific to the
 * final application.
 *****************************************************************************/
/*
 * fhost_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'fhost_example_task'. The rest on the initialization will be done in this
 * function.
 */
int fhost_application_init(void)
{
    if (rtos_task_create(fhost_tls_example_task, "TLS Example task", APPLICATION_TASK,
                         5*1024, NULL, RTOS_TASK_PRIORITY(1), NULL))
        return 1;

    return 0;
}

/**
 * @}
 */



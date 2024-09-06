/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "dma_api.h"
#include "ce_api.h"
#include "dbg.h"
#include <stdint.h>
#include "aes.h"
#include "sha1.h"
#include "sha256.h"
#ifdef CFG_TEST_CE

/*
 * MACROS
 ****************************************************************************************
 */
#define AES_TEST
//#define AES_GCM_TEST
//#define ECC_256_TEST
//#define RSA_1024_TEST
//#define HASH_TEST
//#define CHKSUM_TEST
#define UART_PRINT              dbg

/*
 * GLOBAL CONSTANTS & VARIABLES
 ****************************************************************************************
 */
static AIC_CE_TypeDef * const aic_ce = AIC_CE;
dma_cypt_t dma_cypt_obj = {0};

#ifdef AES_TEST
aes_state_t aes_obj = {0};
//key & iv is same endian
unsigned char ecb_cbc_key[32];
unsigned char aes_test_data[272];
unsigned char cbc_iv[16];
static uint32_t aes_result[16];

static const unsigned char aes_test_ctr_nonce_counter[2][16] =
{
    { 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
    { 0x00, 0x6C, 0xB6, 0xDB, 0xC0, 0x54, 0x3B, 0x59,
      0xDA, 0x48, 0xD9, 0x0B, 0x00, 0x00, 0x00, 0x01 },
};

uint32_t aes_test_key[8] = {0x30313233, 0x34353637, 0x38394142, 0x43444546, 0x4748494A, 0x4B4C4D4E, 0x4F505152, 0x53545556};
uint32_t aes_cbc_iv[4] = {0x31323334,0x35363738,0x39303132,0x33343536};
uint32_t test_aes_data_b[16] ={0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
0X71727374, 0x75767778, 0x797A3030, 0x30303030, 0x30303030, 0x30303030,
0x30303030, 0x30303030, 0x30303030, 0x30303030, 0x30303030, 0x30303030
};
#endif

#ifdef ECC_256_TEST
//ECC-256 test data
static uint32_t ecc_result[64];
//LSB
//only for bt
uint32_t secret_key[8] = {0x1a8b7f78,0x502959d8,0x2b894868,0x6c0356a7,0x08cdb7ff,0x3477d43f,0x70a3a52b,0x28e4baf1};
uint32_t BasePoint_x_256[8] = {0xd898c296,0xf4a13945,0x2deb33a0,0x77037d81,0x63a440f2,0xf8bce6e5,0xe12c4247,0x6b17d1f2};
uint32_t BasePoint_y_256[8] = {0x37bf51f5,0xcbb64068,0x6b315ece,0x2bce3357,0x7c0f9e16,0x8ee7eb4a,0xfe1a7f9b,0x4fe342e2};
uint32_t coef_A[8]     = {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000};
uint32_t Mod_P_256[8]  = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x00000000,0x00000000,0x00000000,0x00000001,0xFFFFFFFF};
uint32_t R2modP[9]     = {0};
#endif

#ifdef RSA_1024_TEST
//RSA-1024 test data
static uint32_t rsa_result[64];
//LSB
uint32_t rsa_test_data[32] = {0x00111222,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000};
uint32_t Rsa_index[32] = {0x00010001,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000};
uint32_t Mod_P_1024[32] = {0x422B3E65,0x534A821D,0xE1FB2567,0xD7F0127F,
0xD94B1257,0xF1DA5984,0x2EF08D6B,0xBF6F7F79,0x80CE8C3A,0x7A61EF11,0x5425EAC2,0x200EBDCD,
0xE937488C,0x5E863522,0xD3917D3C,0x3D5408F2,0xDF343885,0x1D962CB2,0x252C4F38,0x55190E28,
0x6E2683F8,0x570DB35A,0x30691930,0x4881A663,0x9854EA94,0xE29D30D6,0x707CF988,0x675D84B9,
0x16E79D22,0x2DFDBF8A,0x9EEC3F1A,0xA97B317D};
#endif

#ifdef HASH_TEST
//SHA256
hash_state_t sha256_obj;
uint8_t hash_test_data[1024];
uint8_t hmac_key[8] = {0x12,0x34,0x56,0x78,0x12,0x34,0x56,0x78};
uint8_t hash_result[32]; //SHA256 result
uint8_t hmac_data[32];

uint8_t test_hash_data1[56] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
0x38,0x39,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,
0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x30,0x30,0x30,0x30,
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30};

uint8_t test_hash_data2[74] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
0x38,0x39,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,
0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x30,0x30,0x30,0x30,
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
0x38,0x39};
#endif

#ifdef AES_GCM_TEST
aes_gcm_state_t aes_gcm_obj = {0};
static uint8_t aes_gcm_res[128];
static uint8_t aes_gcm_tag[32];
//-------------------------------------------//
//little endian
uint32_t gcm_test_key_case2_l[8] = {0x00000000,0x00000000,0x00000000,0x00000000};
uint32_t aes_gcm_iv_case2_l[3] = {0x00000000,0x00000000,0x00000000};
//uint32_t aes_gcm_auth_data_case2 = NULL;
uint8_t aes_gcm_cipher_data_case2_l[16] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t aes_gcm_tag_test_case2_l[16] = {0xab,0x6e,0x47,0xd4, 0x2c,0xec,0x13,0xbd,
0xf5,0x3a,0x67,0xb2, 0x12,0x57,0xbd,0xdf};
uint8_t aes_gcm_res_test_case2_l[16] = {0x03,0x88,0xda,0xce, 0x60,0xb6,0xa3,0x92,
0xf3,0x28,0xc2,0xb9, 0x71,0xb2,0xfe,0x78};

//little endian
uint32_t gcm_test_key_case34_l[5] = {0x92e9fffe,0x1c736586,0x948f6a6d,0x08833067};
uint32_t aes_gcm_iv[4] = {0xbebafeca,0xaddbcefa,0x88f8cade};
uint8_t aes_gcm_auth_data_l[20] = {0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,
0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xab,0xad,0xda,0xd2};
uint8_t aes_gcm_cipher_data_l[68] = {
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};
uint8_t aes_gcm_cipher_data_l_shift1[69] = {
0xFF,
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};
uint8_t aes_gcm_cipher_data_l_shift2[70] = {
0xFF,0xFF,
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};
uint8_t aes_gcm_cipher_data_l_shift3[71] = {
0xFF,0xFF,0xFF,
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};

uint8_t *aes_gcm_data_shift = NULL;
uint8_t *aes_gcm_res_shift = NULL;
#endif

#ifdef CHKSUM_TEST
dma_desc_t dma_obj = {0};

uint8_t chksum_src4[1504];
uint8_t chksum_dest4[32];

uint32_t *chksum_src_shift = NULL;
#endif
/*
 * FUNCTIONS
 ****************************************************************************************
 */

#ifdef AES_TEST
int mbedtls_ecb_cmp_test(int key_len, int len, int encr_decr_sel, int src_shift, int dest_shift)
{
    int i, j;
    unsigned char buf[16];
    unsigned char buf_out[16];
    unsigned char buf_out_sw[256];
    unsigned char buf_out_hw[272];
    mbedtls_aes_context ctx;
    dma_cypt_t dma_cypt_obj = {0};
    aes_state_t aes_obj = {0};

    mbedtls_aes_init( &ctx );
    if(encr_decr_sel == MBEDTLS_AES_ENCRYPT) {
        mbedtls_aes_setkey_enc( &ctx, ecb_cbc_key, key_len );
    } else {
        mbedtls_aes_setkey_dec( &ctx, ecb_cbc_key, key_len );
    }
    for(i = 0;i <= (len - 16); i += 16) {//0 to len -16
        memcpy(buf, aes_test_data + i + src_shift, 16);
        mbedtls_aes_crypt_ecb( &ctx, encr_decr_sel, buf, buf_out);
#if 0
        dbg("ecb_res_sw :\n");
        for(j = 0; j < 16; j++) {
            if(j%8 == 7) {
                dbg(" %02x\n", *(buf_out + j));
            } else {
                dbg(" %02x", *(buf_out + j));
            }
        }
        dbg("\n");
#endif
        memcpy(buf_out_sw + i, buf_out, 16);
    }

    mbedtls_aes_free( &ctx );

    dma_cypt_obj.ce_chn = DMA_CHANNEL_CYPT_IDX0;
    dma_cypt_obj.dma_cypt_mode = AES_MODE;
    //aes_encr
    if( encr_decr_sel == MBEDTLS_AES_ENCRYPT )
        dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    else
        dma_cypt_obj.aes_enc_decr_sel = AES_DECR;
    //aes_mode
    dma_cypt_obj.aes_mode = AES_ECB_MODE;

    //key length
    if(key_len == 128) {
        dma_cypt_obj.aes_keylen = AES_128_MODE;
    }
    else if(key_len == 192) {
        dma_cypt_obj.aes_keylen = AES_192_MODE;
    }
    else if(key_len == 256) {
        dma_cypt_obj.aes_keylen = AES_256_MODE;
    } else {
        dbg("unsupport aes len %d\n",key_len);
    }
    dma_cypt_obj.aes_endian_sel = AES_LITTLE_ENDIAN;

    for(j = 0; j < (dma_cypt_obj.aes_keylen); j++) {
        dma_cypt_obj.aes_key[j] = *((uint32_t *)(ecb_cbc_key + 4*j));
//        dbg("  0x%08x", dma_cypt_obj.aes_key[j]);
    }
//    dbg("\n");

    dma_cypt_init(&dma_cypt_obj);
    aes_obj.aes_data = (uint32_t *)(aes_test_data + src_shift);
    aes_obj.length_byte = len;

    aes_calc(&dma_cypt_obj, &aes_obj, (uint32_t *)(buf_out_hw + dest_shift));
#if 0
    dbg("ecb_res_hw :\n");
    for(j = 0; j < len; j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(buf_out_hw + j));
        } else {
            dbg(" %02x", *(buf_out_hw + j));
        }
    }
    dbg("\n");
#endif
    if( memcmp( buf_out_sw, (buf_out_hw + dest_shift), len ) != 0 )
    {
        dbg( "%s failed ", ( encr_decr_sel == MBEDTLS_AES_DECRYPT ) ? "dec" : "enc" );
        return 0;
    } else {
        dbg( "%s passed \n", ( encr_decr_sel == MBEDTLS_AES_DECRYPT ) ? "dec" : "enc" );
       return 1;
    }
}

int mbedtls_cbc_cmp_test(int key_len, int len, int encr_decr_sel, int src_shift, int dest_shift)
{
    int j;
    unsigned char buf[256];
    unsigned char buf_out_sw[256];
    unsigned char buf_out_hw[256];
    mbedtls_aes_context ctx;
    dma_cypt_t dma_cypt_obj = {0};
    aes_state_t aes_obj = {0};

    for (j = 0; j < 16; j++) {
        cbc_iv[j] = j;
    }
//HW calc frist
    dma_cypt_obj.ce_chn = DMA_CHANNEL_CYPT_IDX0;
    dma_cypt_obj.dma_cypt_mode = AES_MODE;
    //aes_encr
    if( encr_decr_sel == MBEDTLS_AES_ENCRYPT )
        dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    else
        dma_cypt_obj.aes_enc_decr_sel = AES_DECR;
    //aes_mode
    dma_cypt_obj.aes_mode = AES_CBC_MODE;

    for(j = 0; j < 4; j++) {
        dma_cypt_obj.aes_iv[j] = *((uint32_t *)(cbc_iv + 4*j));
//        dbg("  0x%08x", dma_cypt_obj.aes_iv[j]);
    }
//    dbg("\n");

    //key length
    if(key_len == 128) {
        dma_cypt_obj.aes_keylen = AES_128_MODE;
    }
    else if(key_len == 192) {
        dma_cypt_obj.aes_keylen = AES_192_MODE;
    }
    else if(key_len == 256) {
        dma_cypt_obj.aes_keylen = AES_256_MODE;
    } else {
        dbg("unsupport aes len %d\n",key_len);
    }
    dma_cypt_obj.aes_endian_sel = AES_LITTLE_ENDIAN;

    for(j = 0; j < (dma_cypt_obj.aes_keylen); j++) {
        dma_cypt_obj.aes_key[j] = *((uint32_t *)(ecb_cbc_key + 4*j));
//        dbg("  0x%08x", dma_cypt_obj.aes_key[j]);
    }
//    dbg("\n");
    dma_cypt_init(&dma_cypt_obj);
    aes_obj.aes_data = (uint32_t *)(aes_test_data + src_shift);
    aes_obj.length_byte = len;

    aes_calc(&dma_cypt_obj, &aes_obj, (uint32_t *)buf_out_hw);
#if 0
    dbg("cbc_res_hw :\n");
    for(j = 0; j < len; j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(buf_out_hw + j));
        } else {
            dbg(" %02x", *(buf_out_hw + j));
        }
    }
    dbg("\n");
#endif

    mbedtls_aes_init( &ctx );
    if(encr_decr_sel == MBEDTLS_AES_ENCRYPT) {
        mbedtls_aes_setkey_enc( &ctx, ecb_cbc_key, key_len );
    } else {
        mbedtls_aes_setkey_dec( &ctx, ecb_cbc_key, key_len );
    }

    memcpy(buf, aes_test_data + src_shift, len);
    mbedtls_aes_crypt_cbc( &ctx, encr_decr_sel, len, cbc_iv, buf, buf_out_sw );
#if 0
    dbg("cbc_res_sw :\n");
    for(j = 0; j < len; j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(buf_out_sw + j));
        } else {
            dbg(" %02x", *(buf_out_sw + j));
        }
    }
    dbg("\n");
#endif
    mbedtls_aes_free( &ctx );

        if( memcmp( buf_out_sw, buf_out_hw, len ) != 0 )
        {
            dbg( "%s failed ", ( encr_decr_sel == MBEDTLS_AES_DECRYPT ) ? "dec" : "enc" );
            return 0;
        } else {
            dbg( "%s passed \n", ( encr_decr_sel == MBEDTLS_AES_DECRYPT ) ? "dec" : "enc" );
           return 1;
        }
}

int mbedtls_ctr_cmp_test(int key_len, int len, int encr_decr_sel, int src_shift, int dest_shift)
{
    int j;
    unsigned char buf[256];
    unsigned char buf_out_sw[256];
    unsigned char buf_out_hw[256];
    unsigned char nonce_counter[16];
    unsigned char stream_block[16];
    size_t offset;
    mbedtls_aes_context ctx;
    dma_cypt_t dma_cypt_obj = {0};
    aes_state_t aes_obj = {0};

    memcpy( nonce_counter, aes_test_ctr_nonce_counter[1], 16 );
    offset = 0;
    mbedtls_aes_init( &ctx );
    mbedtls_aes_setkey_enc( &ctx, ecb_cbc_key, key_len );
    memcpy( buf, aes_test_data + src_shift, len );
    mbedtls_aes_crypt_ctr( &ctx, len, &offset, nonce_counter, stream_block,
                   buf, buf_out_sw );
#if 0
    dbg("ctr_res_sw :\n");
    for(j = 0; j < len; j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(buf_out_sw + j));
        } else {
            dbg(" %02x", *(buf_out_sw + j));
        }
    }
    dbg("\n");
#endif
    mbedtls_aes_free( &ctx );

    dma_cypt_obj.ce_chn = DMA_CHANNEL_CYPT_IDX0;
    dma_cypt_obj.dma_cypt_mode = AES_MODE;
    //aes_encr
    if( encr_decr_sel == MBEDTLS_AES_ENCRYPT )
        dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    else
        dma_cypt_obj.aes_enc_decr_sel = AES_DECR;
    //aes_mode
    dma_cypt_obj.aes_mode = AES_CTR_MODE;

    for(j = 0; j < 4; j++) {
        dma_cypt_obj.aes_iv[j] = *((uint32_t *)(aes_test_ctr_nonce_counter[1] + 4*j));
//        dbg("  0x%08x", dma_cypt_obj.aes_iv[j]);
    }
//    dbg("\n");

    //key length
    if(key_len == 128) {
        dma_cypt_obj.aes_keylen = AES_128_MODE;
    }
    else if(key_len == 192) {
        dma_cypt_obj.aes_keylen = AES_192_MODE;
    }
    else if(key_len == 256) {
        dma_cypt_obj.aes_keylen = AES_256_MODE;
    } else {
        dbg("unsupport aes len %d\n",key_len);
    }
    dma_cypt_obj.aes_endian_sel = AES_LITTLE_ENDIAN;

    for(j = 0; j < (dma_cypt_obj.aes_keylen); j++) {
        dma_cypt_obj.aes_key[j] = *((uint32_t *)(ecb_cbc_key + 4*j));
//        mbedtls_printf("  0x%08x", dma_cypt_obj.aes_key[j]);
    }
//    mbedtls_printf("\n");
    dma_cypt_init(&dma_cypt_obj);
    aes_obj.aes_data = (uint32_t *)(aes_test_data + src_shift);
    aes_obj.length_byte = len;

    aes_calc(&dma_cypt_obj, &aes_obj, (uint32_t *)buf_out_hw);
#if 0
    dbg("ctr_res_hw :\n");
    for(j = 0; j < len; j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(buf_out_hw + j));
        } else {
            dbg(" %02x", *(buf_out_hw + j));
        }
    }
    dbg("\n");
#endif
    if( memcmp( buf_out_sw, buf_out_hw, len ) != 0 )
    {
        dbg( "%s failed ", ( encr_decr_sel == MBEDTLS_AES_DECRYPT ) ? "dec" : "enc" );
        return 0;
    } else {
        dbg( "%s passed \n", ( encr_decr_sel == MBEDTLS_AES_DECRYPT ) ? "dec" : "enc" );
       return 1;
    }
}

void mbedtls_aes_test_regression(void)
{
    int ret;
    int key_len, len, src_shift = 0,j = 0;
//init key & data
    for (j = 0; j < 32; j++) {
        ecb_cbc_key[j] = j;
    }
    for (j =0; j < 256; j++) {
        aes_test_data[j] = j % 256;
    }
//    dma_trsc_init(DMA_CHANNEL_CYPT_IDX0);

    dbg("start ecb regression\n");
    for(key_len = 128 ; key_len <= 256; key_len += 64) {// 3 loop
        dbg("key_len: %d\n",key_len);
        for(len = 16; len <= 256; len += 16) {//8 loop
            dbg("data len %d\n",len);
            for(src_shift = 0; src_shift < 16; src_shift++) {//4 loop
                ret = mbedtls_ecb_cmp_test(key_len, len, 1, src_shift ,0);
                if(!ret) {
                    dbg("key len: %d, len: %d, src_shift: %d, dest_shift %d\n", key_len, len, src_shift, j);
                }
                ret = mbedtls_ecb_cmp_test(key_len, len, 0, src_shift ,0);
                if(!ret) {
                    dbg("key len: %d, len: %d, src_shift: %d, dest_shift %d\n", key_len, len, src_shift, j);
                }
            }
        }
    }

    dbg("start cbc regression\n");
    for(key_len = 128 ; key_len <= 256; key_len += 64) {// 3 loop
        dbg("key_len: %d\n",key_len);
        for(len = 16; len <= 256; len += 16) {//8 loop
            dbg("data len %d\n",len);
            for(src_shift = 0; src_shift < 16; src_shift++) {//4 loop
                ret = mbedtls_cbc_cmp_test(key_len, len, 1, src_shift ,0);
                if(!ret) {
                    dbg("key len: %d, len: %d, src_shift: %d, dest_shift %d\n", key_len, len, src_shift, j);
                }
                ret = mbedtls_cbc_cmp_test(key_len, len, 0, src_shift ,0);
                if(!ret) {
                    dbg("key len: %d, len: %d, src_shift: %d, dest_shift %d\n", key_len, len, src_shift, j);
                }
            }
        }
    }

    dbg("start ctr regression\n");
    for(key_len = 128 ; key_len <= 256; key_len += 64) {// 3 loop
        dbg("key_len: %d\n",key_len);
        for(len = 16; len <= 256; len += 16) {//8 loop
            dbg("data len %d\n",len);
            for(src_shift = 0; src_shift < 16; src_shift++) {//4 loop
                ret = mbedtls_ctr_cmp_test(key_len, len, 1, src_shift ,0);
                if(!ret) {
                    dbg("key len: %d, len: %d, src_shift: %d, dest_shift %d\n", key_len, len, src_shift, j);
                }
                ret = mbedtls_ctr_cmp_test(key_len, len, 0, src_shift ,0);
                if(!ret) {
                    dbg("key len: %d, len: %d, src_shift: %d, dest_shift %d\n", key_len, len, src_shift, j);
                }
            }
        }
    }
}
#endif

#ifdef HASH_TEST
#if 1
int mbedtls_sha1_cmp_test(size_t len){
    int j;
    uint8_t sha1sum_sw[20];
    uint8_t sha1sum_hw[20];
//    dma_cypt_t dma_cypt_obj = {0};
//    hash_state_t sha1_obj = {0};
    mbedtls_sha1_context ctx;

    mbedtls_sha1_init( &ctx );
    mbedtls_sha1_starts( &ctx );
    mbedtls_sha1_update( &ctx, hash_test_data, len );
    mbedtls_sha1_finish( &ctx, sha1sum_sw );
    mbedtls_sha1_free( &ctx );
#if 0
    dbg("sha1_res_sw :\n");
    for(j = 0; j < 20; j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(sha1sum_sw + j));
        } else {
            dbg(" %02x", *(sha1sum_sw + j));
        }
    }
    dbg("\n");
#endif
    sha1_calc((uint8_t *)hash_test_data, len, sha1sum_hw);
#if 0
    dbg("sha1_res_hw :\n");
    for(j = 0; j < 20; j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(sha1sum_hw + j));
        } else {
            dbg(" %02x", *(sha1sum_hw + j));
        }
    }
    dbg("\n");
#endif
    if( memcmp( sha1sum_sw, sha1sum_hw, 20 ) != 0 )
    {
        dbg( "failed ");
        return 0;
    } else {
        dbg( "passed \n");
       return 1;
    }
}

void mbedtls_sha1_test_regression(void)
{
    int ret, j;
    size_t len;

    for (j =0; j < 1024; j++) {
        hash_test_data[j] = j%64;
    }
    dbg("start sha1 regression\n");
    for(len =1; len < 1024; len++) {
        ret = mbedtls_sha1_cmp_test(len);
        if(!ret) {
            dbg("at len %d\n", len);
        }
    }

}
#endif
int mbedtls_sha256_224_cmp_test(int len, int mode){
    int j;
    unsigned char sha2sum_sw[32];
    unsigned char sha2sum_hw[32];
    mbedtls_sha256_context ctx;
    dma_cypt_t dma_cypt_obj = {0};
    hash_state_t sha2_obj = {0};

    mbedtls_sha256_init( &ctx );
    mbedtls_sha256_starts( &ctx, mode);
    mbedtls_sha256_update( &ctx, hash_test_data, len );
    mbedtls_sha256_finish( &ctx, sha2sum_sw );
#if 0
    dbg("sha%s_res_sw :\n", mode ? "224" : "256");
    for(j = 0; j < (32 - 4 * mode); j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(sha2sum_sw + j));
        } else {
            dbg(" %02x", *(sha2sum_sw + j));
        }
    }
    dbg("\n");
#endif
    dma_cypt_obj.ce_chn = DMA_CHANNEL_CYPT_IDX0;
    dma_cypt_obj.dma_cypt_mode = HASH_MODE;
    if(mode) {
        dma_cypt_obj.hash_mode = HASH_SHA224_MODE;
    } else {
        dma_cypt_obj.hash_mode = HASH_SHA256_MODE;
    }
    dma_cypt_obj.hash_pad_sel = HASH_HW_PAD;
    dma_cypt_init(&dma_cypt_obj);
    sha2_obj.buf = hash_test_data;
    sha2_obj.length_byte = len;
    hash_proc_512bit(&dma_cypt_obj, &sha2_obj, (uint32_t *)sha2sum_hw);
#if 0
    dbg("sha%s_res_hw :\n", mode ? "224" : "256");
    for(j = 0; j < (32 - 4 * mode); j++) {
        if(j%8 == 7) {
            dbg(" %02x\n", *(sha2sum_hw + j));
        } else {
            dbg(" %02x", *(sha2sum_hw + j));
        }
    }
    dbg("\n");
#endif
    if( memcmp( sha2sum_sw, sha2sum_hw, (32 - 4 *mode)) != 0 )
    {
        dbg( "failed ");
        return 0;
    } else {
        dbg( "passed \n");
       return 1;
    }
}

void mbedtls_sha2_test_regression(void)
{
    int ret;
    int i,j; // i=0:256 i=1: 224

    for (j =0; j < 1024; j++) {
        hash_test_data[j] = j%64;
    }
    dbg("start sha2 regression\n");
    for (i = 0; i <= 1; i++) {
        dbg("%s start\n",i ? "sha224" : "sha256");
        for(j = 1; j < 1024; j++) {
            ret = mbedtls_sha256_224_cmp_test(j, i);
            if(!ret) {
                dbg("at mode %s len %d\n", (i ? "sha224" : "sha256"),j);
            }
        }
    }
}
#endif

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void ce_test(void)
{
    const int ch = DMA_CHANNEL_CYPT_IDX0;
    uint32_t i,j,k;
#ifdef CHKSUM_TEST
    uint32_t chksum_len;
    uint32_t chksum_endian = 1;
    uint32_t chksum_SW_res;
    uint32_t chksum_HW_res;
#endif
#ifdef AES_GCM_TEST
    uint32_t auth_pad_len;
    uint8_t aes_gcm_res_pass = 1;
    uint8_t aes_gcm_tag_pass = 1;
#endif
    // DMA init
    dma_init();
    dma_cypt_obj.ce_chn = ch;

    #ifdef ECC_256_TEST
    dma_cypt_obj.dma_cypt_mode = ECC_MODE;
    dma_cypt_obj.ecc_mode = ECC_256_MODE;
    dma_cypt_obj.ecc_a_eq_p3 = ECC_A_EQ_MINUS_3;
    dma_cypt_obj.mod_mult_parameter = Mod_P_256[0];

    dma_cypt_init(&dma_cypt_obj);
    //dma_cypt_obj.R2modP_sta = PKA_R2_MODP_READY;
    curve_coef_init(&dma_cypt_obj, coef_A, Mod_P_256, R2modP);
    ecc_generate_key(&dma_cypt_obj, secret_key, BasePoint_x_256, BasePoint_y_256, ecc_result);
    while(aic_get_ecc_generate_key_ready() == 0);

    for(i = 0; i < 16; i++) {
        dbg("ecc_res: %08x\n", ecc_result[i]);
    }
    #endif

    #ifdef RSA_1024_TEST
    dma_cypt_obj.dma_cypt_mode = RSA_MODE;
    dma_cypt_obj.rsa_keylen = 1;
    dma_cypt_obj.rsa_mode = RSA_1024_MODE;
    dma_cypt_obj.mod_mult_parameter = Mod_P_1024[0];
    dma_cypt_init(&dma_cypt_obj);
    rsa_coef_init(Rsa_index, Mod_P_1024);
    rsa_calc(&dma_cypt_obj, rsa_test_data, rsa_result);
    for(i = 0; i < 32; i++) {
        dbg("rsa_res: %08x\n", rsa_result[i]);
    }
    #endif

    #ifdef HASH_TEST
    mbedtls_sha1_test_regression();
    mbedtls_sha2_test_regression();

    aic_ce->DMA_MON_SEL = 0x1;
    dma_cypt_obj.dma_cypt_mode = HASH_MODE;

//hash 1 test
    dma_cypt_obj.hash_mode = HASH_SHA1_MODE;
    dma_cypt_obj.hash_pad_sel = HASH_HW_PAD;
    dma_cypt_obj.hash_endian_sel = AES_LITTLE_ENDIAN;
    dma_cypt_init(&dma_cypt_obj);
    sha256_obj.buf = test_hash_data2;
    sha256_obj.length_byte = sizeof(test_hash_data2);
    hash_proc_512bit(&dma_cypt_obj, &sha256_obj, (uint32_t *)hash_result);
    aic_ce->DMA_MON_SEL = 0x0;
#if 0
    dbg("hw_pad\n");
    dbg("sha1_res1:\n");
    for(i = 0; i < 20; i++) {
        if(i%8 == 7) {
            dbg(" %02x\n", hash_result[i]);
        } else {
            dbg(" %02x ", hash_result[i]);
        }
    }
    dbg("\n");
#endif
    dma_cypt_init(&dma_cypt_obj);
    sha256_obj.buf = test_hash_data1;
    sha256_obj.length_byte = sizeof(test_hash_data1);
    hash_proc_512bit(&dma_cypt_obj, &sha256_obj, (uint32_t *)hash_result);
#if 0
    dbg("hw_pad\n");
    dbg("sha1_res2:\n");
    for(i = 0; i < 20; i++) {
        if(i%8 == 7) {
            dbg(" %02x\n", hash_result[i]);
        } else {
            dbg(" %02x ", hash_result[i]);
        }
    }
    dbg("\n");
#endif
    while(1);
    #endif //HASH_TEST

    #ifdef AES_TEST
    mbedtls_aes_test_regression();

    dma_cypt_obj.dma_cypt_mode = AES_MODE;
//aes_encr
    dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    //dma_cypt_obj.aes_enc_decr_sel = AES_DECR;
//aes_mode
    //dma_cypt_obj.aes_mode = AES_ECB_MODE;
    dma_cypt_obj.aes_mode = AES_CBC_MODE;
    //dma_cypt_obj.aes_mode = AES_CTR_MODE;
//key length
    dma_cypt_obj.aes_keylen = AES_128_MODE;
    dma_cypt_obj.aes_endian_sel = AES_BIG_ENDIAN;

    for(i = 0; i < 8; i++) {
        dma_cypt_obj.aes_key[i] = aes_test_key[i];
    }
    //dma_aes_cbc
    for(i = 0; i < 4; i++) {
        dma_cypt_obj.aes_iv[i] = aes_cbc_iv[i];
//        dma_cypt_obj.aes_iv[i] = aes_ctr_iv[i];
    }

    dma_cypt_init(&dma_cypt_obj);
    aes_obj.aes_data = (uint32_t*)test_aes_data_b;
    aes_obj.length_byte = sizeof(test_aes_data_b);
    aes_calc(&dma_cypt_obj, &aes_obj, aes_result);
    for(i = 0; i < (aes_obj.length_byte / 4); i++) {
        dbg("aes_res: %08x\n", aes_result[i]);
    }
    #endif

    #ifdef AES_GCM_TEST
    dma_cypt_obj.dma_cypt_mode = AES_MODE;
    dma_cypt_obj.aes_mode = AES_GCM_MODE;
    //key length
    dma_cypt_obj.aes_keylen = AES_128_MODE;
    //dma_cypt_obj.aes_keylen = AES_192_MODE;
    //dma_cypt_obj.aes_keylen = AES_256_MODE;
#if 1
//standard test
//litte endian
    dma_cypt_obj.aes_endian_sel = AES_LITTLE_ENDIAN;
    //aes gcm case 2
    //aes_encr
    dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    dbg("gcm encr\n\r");
    for(i = 0; i < dma_cypt_obj.aes_keylen; i++) {
        dma_cypt_obj.aes_key[i] = gcm_test_key_case2_l[i];
    }
    //dma_aes_cbc
    for(i = 0; i < 3; i++) {
        dma_cypt_obj.aes_iv[i] = aes_gcm_iv_case2_l[i];
    }
    if(dma_cypt_obj.aes_endian_sel == AES_BIG_ENDIAN) {
        dma_cypt_obj.aes_iv[3] = 0x00000001;
    } else {
        dma_cypt_obj.aes_iv[3] = 0x01000000;
    }
    aes_gcm_obj.auth_dat_len_byte = 0; // case 2 has no auth data
    auth_pad_len = aes_gcm_obj.auth_dat_len_byte;
    if(auth_pad_len & 0x3) {
        auth_pad_len = (((auth_pad_len >> 2) + 1) << 2);
    } else {
        auth_pad_len = aes_gcm_obj.auth_dat_len_byte;
    }
    aes_gcm_obj.auth_dat_pad_len_byte = auth_pad_len;
//    aes_gcm_obj.auth_data = (uint32_t *)aes_gcm_auth_data;//padding
    aes_gcm_obj.cipher_dat_len_byte = sizeof(aes_gcm_cipher_data_case2_l);
    aes_gcm_obj.aes_data = (uint32_t *)aes_gcm_cipher_data_case2_l;
    dma_cypt_obj.aes_a_len = aes_gcm_obj.auth_dat_len_byte * 8;//byte2bit
    dma_cypt_obj.aes_plain_len = aes_gcm_obj.cipher_dat_len_byte * 8;//byte2bit
    dma_cypt_init(&dma_cypt_obj);
    aes_gcm_calc(&dma_cypt_obj, &aes_gcm_obj, (uint32_t *)aes_gcm_res, (uint32_t *)aes_gcm_tag);
    dbg("gcm_res_addr: %08x\n", aes_gcm_res);
    dbg("aes_res :\n");
    for(i = 0; i < aes_gcm_obj.cipher_dat_len_byte; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_res[i]);
        } else {
            dbg(" %02x", aes_gcm_res[i]);
        }

        if(aes_gcm_res[i] != aes_gcm_res_test_case2_l[i]) {
            aes_gcm_res_pass = 0;
        }
    }
    dbg("\n");
    if(aes_gcm_res_pass) {
        dbg("gcm_case2_data_pass\n");
    } else {
        dbg("gcm_case2_data_fail\n");
        aes_gcm_res_pass = 1;
    }
    dbg("auth_tag_addr: %08x\n", aes_gcm_tag);
    dbg("auth_tag:\n");
    for(i = 0; i < 16; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_tag[i]);
        } else {
            dbg(" %02x", aes_gcm_tag[i]);
        }
        if(aes_gcm_tag[i] != aes_gcm_tag_test_case2_l[i]) {
            aes_gcm_tag_pass = 0;
        }
    }
    dbg("\n");
    if(aes_gcm_tag_pass) {
        dbg("gcm_case2_tag_pass\n");
    } else {
        dbg("gcm_case2_tag_fail\n");
        aes_gcm_tag_pass = 1;
    }

    dma_cypt_obj.aes_enc_decr_sel = AES_DECR;
    dbg("gcm decr\n\r");
    aes_gcm_obj.auth_dat_len_byte = 0; // case 2 has no auth data

    aes_gcm_obj.aes_data = (uint32_t *)aes_gcm_res;
    dma_cypt_obj.aes_a_len = aes_gcm_obj.auth_dat_len_byte * 8;//byte2bit
    dma_cypt_obj.aes_plain_len = aes_gcm_obj.cipher_dat_len_byte * 8;//byte2bit
    dma_cypt_init(&dma_cypt_obj);
    aes_gcm_calc(&dma_cypt_obj, &aes_gcm_obj, (uint32_t *)aes_gcm_res, (uint32_t *)aes_gcm_tag);
    dbg("gcm_res_addr: %08x\n", aes_gcm_res);
    dbg("aes_res :\n");
    for(i = 0; i < aes_gcm_obj.cipher_dat_len_byte; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_res[i]);
        } else {
            dbg(" %02x", aes_gcm_res[i]);
        }
        if(aes_gcm_res[i] != aes_gcm_cipher_data_case2_l[i]) {
            aes_gcm_res_pass = 0;
        }
    }
    dbg("\n");
    if(aes_gcm_res_pass) {
        dbg("gcm_case2_data_pass\n");
    } else {
        dbg("gcm_case2_data_fail\n");
        aes_gcm_res_pass = 1;
    }
    dbg("auth_tag_addr: %08x\n", aes_gcm_tag);
    dbg("auth_tag:\n");
    for(i = 0; i < 16; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_tag[i]);
        } else {
            dbg(" %02x", aes_gcm_tag[i]);
        }
        if(aes_gcm_tag[i] != aes_gcm_tag_test_case2_l[i]) {
            aes_gcm_tag_pass = 0;
        }
    }
    dbg("\n");
    if(aes_gcm_tag_pass) {
        dbg("gcm_case2_tag_pass\n");
    } else {
        dbg("gcm_case2_tag_fail\n");
        aes_gcm_tag_pass = 1;
    }
#endif

#if 1
//aes gcm no align
    dma_cypt_obj.aes_endian_sel = AES_LITTLE_ENDIAN;
    dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    for(i = 0; i < dma_cypt_obj.aes_keylen; i++) {
        dma_cypt_obj.aes_key[i] = gcm_test_key_case34_l[i];
    }
    //dma_aes_cbc
    for(i = 0; i < 3; i++) {
        dma_cypt_obj.aes_iv[i] = aes_gcm_iv[i];
    }
    if(dma_cypt_obj.aes_endian_sel == AES_BIG_ENDIAN) {
        dma_cypt_obj.aes_iv[3] = 0x00000001;
    } else {
        dma_cypt_obj.aes_iv[3] = 0x01000000;
    }
    aes_gcm_obj.auth_dat_len_byte = 20;
    auth_pad_len = aes_gcm_obj.auth_dat_len_byte;
    if(auth_pad_len & 0x3) {
        auth_pad_len = (((auth_pad_len >> 2) + 1) << 2);
    } else {
        auth_pad_len = aes_gcm_obj.auth_dat_len_byte;
    }
    aes_gcm_obj.auth_dat_pad_len_byte = auth_pad_len;
    aes_gcm_obj.auth_data = (uint32_t *)aes_gcm_auth_data_l;//padding
    aes_gcm_obj.cipher_dat_len_byte = 55;
    for(k=0;k<4;k++) {
    for(j=0;j<4;j++) {
        if(j==0) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_l + j);
        }
        else if(j==1) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_l_shift1 + j);
        }
        else if(j==2) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_l_shift2 + j);
        }
        else if(j==3) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_l_shift3 + j);
        }
        aes_gcm_obj.aes_data = (uint32_t *)aes_gcm_data_shift;
        dbg("gcm src addr: %08x\n", aes_gcm_data_shift);
        dma_cypt_obj.aes_a_len = aes_gcm_obj.auth_dat_len_byte * 8;//byte2bit
        dma_cypt_obj.aes_plain_len = aes_gcm_obj.cipher_dat_len_byte * 8;//byte2bit
        aes_gcm_res_shift = (aes_gcm_res + k);
        dma_cypt_init(&dma_cypt_obj);
        aes_gcm_calc(&dma_cypt_obj, &aes_gcm_obj, (uint32_t *)aes_gcm_res_shift, (uint32_t *)aes_gcm_tag);

        dbg("gcm_res_addr: %08x\n", aes_gcm_res_shift);
        dbg("aes_res :\n");
        for(i = 0; i < aes_gcm_obj.cipher_dat_len_byte; i++) {
            if(i%8 == 7){
                dbg(" %02x\n", *(aes_gcm_res_shift + i));
            } else {
                dbg(" %02x", *(aes_gcm_res_shift + i));
            }
        }
        dbg("\n");
//        dbg("auth_tag_addr: %08x\n", aes_gcm_tag);
        dbg("auth_tag:\n");
        for(i = 0; i < 16; i++) {
            if(i%8 == 7){
                dbg(" %02x\n", aes_gcm_tag[i]);
            } else {
                dbg(" %02x", aes_gcm_tag[i]);
            }
        }
        dbg("\n");
    }//loop of j
    }//loop of k

    #endif
#endif

#ifdef CHKSUM_TEST
    dma_trsc_init(DMA_CHANNEL_CYPT_IDX1);
    //    dbg("chksum test start\n");
    /*
        dma_obj.SAR = (uint32_t)chksum_src_d;
        dma_obj.DAR = (uint32_t)chksum_dest_d;
        dma_desc_length_set(&dma_obj, 4896);
        dma_obj.LNAR = 0;
        dma_push(&dma_obj, &dma_obj, 0);
    */
#if 1
    for(i=0;i<1500;i++){
        chksum_src4[i] = i%64;
    }

    for(i=4;i<1000;i++){
        chksum_len = i;
        for(j=0;j<4;j++){
            chksum_src_shift = (uint32_t *)(chksum_src4 + j);
            dbg("src addr %08x, len %d\n",chksum_src_shift,i);
            //chksum_SW_res = lwip_standard_chksum((uint32_t *)chksum_src_shift, chksum_len);
            chksum_calc((uint32_t *)chksum_src_shift,chksum_len,chksum_endian);
            chksum_HW_res = chksum_result_get();
            //if(chksum_SW_res != chksum_HW_res){
            //    aic_ce->DMA_MON_SEL = 0x80000000;
            //    dbg("chksum_err len:%d, offset:%d, SW res:%04x, HW res:%04x\n",i,j,chksum_SW_res,chksum_HW_res);
            //}
        }
    }
#endif
#endif
}

#endif /* CFG_TEST_CE */

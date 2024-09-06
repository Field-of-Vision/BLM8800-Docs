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
#include <string.h>
#include <stdint.h>
#include "reg_sysctrl.h"
#include "dma_api.h"
#include "ce_api.h"
#include "dbg.h"
#ifdef CFG_TEST_AES
#define MBEDTLS_AES_ENCRYPT     1 /**< AES encryption. */
#define MBEDTLS_AES_DECRYPT     0 /**< AES decryption. */

dma_cypt_t dma_cypt_obj = {0};

aes_state_t aes_obj = {0};
//key & iv is same endian
unsigned char ecb_cbc_key[32];
unsigned char aes_test_data[272];
unsigned char cbc_iv[16];

static const unsigned char aes_test_ctr_nonce_counter[2][16] =
{
    { 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
    { 0x00, 0x6C, 0xB6, 0xDB, 0xC0, 0x54, 0x3B, 0x59,
      0xDA, 0x48, 0xD9, 0x0B, 0x00, 0x00, 0x00, 0x01 },
};

aes_gcm_state_t aes_gcm_obj = {0};
static uint8_t aes_gcm_res[128];
static uint8_t aes_gcm_tag[32];
//-------------------------------------------//
//little endian
uint32_t gcm_test_key_case0[8] = {0x00000000,0x00000000,0x00000000,0x00000000};
uint32_t aes_gcm_iv_case0[3] = {0x00000000,0x00000000,0x00000000};
//uint32_t aes_gcm_auth_data_case2 = NULL;
uint8_t aes_gcm_cipher_data_case0[16] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t aes_gcm_tag_test_case0[16] = {0xab,0x6e,0x47,0xd4, 0x2c,0xec,0x13,0xbd,
0xf5,0x3a,0x67,0xb2, 0x12,0x57,0xbd,0xdf};
uint8_t aes_gcm_res_test_case0[16] = {0x03,0x88,0xda,0xce, 0x60,0xb6,0xa3,0x92,
0xf3,0x28,0xc2,0xb9, 0x71,0xb2,0xfe,0x78};

uint32_t gcm_test_key_case1[5] = {0x92e9fffe,0x1c736586,0x948f6a6d,0x08833067};
uint32_t aes_gcm_iv_case1[4] = {0xbebafeca,0xaddbcefa,0x88f8cade};
uint8_t aes_gcm_auth_data_case1[20] = {0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,
0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xab,0xad,0xda,0xd2};
uint8_t aes_gcm_cipher_data_case1[68] = {
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};
uint8_t aes_gcm_cipher_data_case1_shift1[69] = {
0xFF,
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};
uint8_t aes_gcm_cipher_data_case1_shift2[70] = {
0xFF,0xFF,
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};
uint8_t aes_gcm_cipher_data_case1_shift3[71] = {
0xFF,0xFF,0xFF,
0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
0x12,0x23,0x34,0x45
};
uint8_t *aes_gcm_data_shift = NULL;
uint8_t *aes_gcm_res_shift = NULL;

int mbedtls_ecb_test(int key_len, int len, int encr_decr_sel, int src_shift, int dest_shift)
{
    int j;
    unsigned char buf_out_hw[272];
    dma_cypt_t dma_cypt_obj = {0};
    aes_state_t aes_obj = {0};

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
    }

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
    return 1;
}

int mbedtls_cbc_test(int key_len, int len, int encr_decr_sel, int src_shift, int dest_shift)
{
    int j;
    unsigned char buf_out_hw[256];
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
    }

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
    }
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
    return 1;
}

int mbedtls_ctr_test(int key_len, int len, int encr_decr_sel, int src_shift, int dest_shift)
{
    int j;
    unsigned char buf_out_hw[256];
    dma_cypt_t dma_cypt_obj = {0};
    aes_state_t aes_obj = {0};

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
    }

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
    }
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
    return 1;
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
                //encr
                ret = mbedtls_ecb_test(key_len, len, 1, src_shift ,0);
                //decr
                ret = mbedtls_ecb_test(key_len, len, 0, src_shift ,0);
            }
        }
    }

    dbg("start cbc regression\n");
    for(key_len = 128 ; key_len <= 256; key_len += 64) {// 3 loop
        dbg("key_len: %d\n",key_len);
        for(len = 16; len <= 256; len += 16) {//8 loop
            dbg("data len %d\n",len);
            for(src_shift = 0; src_shift < 16; src_shift++) {//4 loop
                //encr
                ret = mbedtls_cbc_test(key_len, len, 1, src_shift ,0);
                //decr
                ret = mbedtls_cbc_test(key_len, len, 0, src_shift ,0);
            }
        }
    }

    dbg("start ctr regression\n");
    for(key_len = 128 ; key_len <= 256; key_len += 64) {// 3 loop
        dbg("key_len: %d\n",key_len);
        for(len = 16; len <= 256; len += 16) {//8 loop
            dbg("data len %d\n",len);
            for(src_shift = 0; src_shift < 16; src_shift++) {//4 loop
                //encr
                ret = mbedtls_ctr_test(key_len, len, 1, src_shift ,0);
                //decr
                ret = mbedtls_ctr_test(key_len, len, 0, src_shift ,0);
            }
        }
    }
    (void)ret; // fix warning
}

void aes_test(void)
{
    const int ch = DMA_CHANNEL_CYPT_IDX0;
    uint32_t i;
    uint32_t auth_pad_len;
    uint8_t aes_gcm_res_pass = 1;
    uint8_t aes_gcm_tag_pass = 1;

    // DMA init
    dma_init();
    dma_cypt_obj.ce_chn = ch;

    mbedtls_aes_test_regression();

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
    //aes_encr
    dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    dbg("gcm encr\n\r");
    for(i = 0; i < dma_cypt_obj.aes_keylen; i++) {
        dma_cypt_obj.aes_key[i] = gcm_test_key_case0[i];
    }
    //dma_aes_cbc
    for(i = 0; i < 3; i++) {
        dma_cypt_obj.aes_iv[i] = aes_gcm_iv_case0[i];
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
    aes_gcm_obj.cipher_dat_len_byte = sizeof(aes_gcm_cipher_data_case0);
    aes_gcm_obj.aes_data = (uint32_t *)aes_gcm_cipher_data_case0;
    dma_cypt_obj.aes_a_len = aes_gcm_obj.auth_dat_len_byte * 8;//byte2bit
    dma_cypt_obj.aes_plain_len = aes_gcm_obj.cipher_dat_len_byte * 8;//byte2bit
    dma_cypt_init(&dma_cypt_obj);
    aes_gcm_calc(&dma_cypt_obj, &aes_gcm_obj, (uint32_t *)aes_gcm_res, (uint32_t *)aes_gcm_tag);
#if 0
    dbg("aes_res :\n");
    for(i = 0; i < aes_gcm_obj.cipher_dat_len_byte; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_res[i]);
        } else {
            dbg(" %02x", aes_gcm_res[i]);
        }
    }
    dbg("\n");
#endif
    if(memcmp(aes_gcm_res,aes_gcm_res_test_case0,sizeof(aes_gcm_res_test_case0)) != 0) {
        aes_gcm_res_pass = 0;
    }

    if(aes_gcm_res_pass) {
        dbg("gcm_case0_data_pass\n");
    } else {
        dbg("gcm_case0_data_fail\n");
        aes_gcm_res_pass = 1;
    }
#if 0
    dbg("auth_tag_addr: %08x\n", aes_gcm_tag);
    dbg("auth_tag:\n");
    for(i = 0; i < 16; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_tag[i]);
        } else {
            dbg(" %02x", aes_gcm_tag[i]);
        }
    }
    dbg("\n");
#endif
    if(memcmp(aes_gcm_tag,aes_gcm_tag_test_case0,sizeof(aes_gcm_tag_test_case0)) != 0) {
        aes_gcm_tag_pass = 0;
    }

    if(aes_gcm_tag_pass) {
        dbg("gcm_case0_tag_pass\n");
    } else {
        dbg("gcm_case0_tag_fail\n");
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
#if 0
    dbg("gcm_res_addr: %08x\n", aes_gcm_res);
    dbg("aes_res :\n");
    for(i = 0; i < aes_gcm_obj.cipher_dat_len_byte; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_res[i]);
        } else {
            dbg(" %02x", aes_gcm_res[i]);
        }
    }
    dbg("\n");
#endif
    if(memcmp(aes_gcm_res,aes_gcm_cipher_data_case0,sizeof(aes_gcm_cipher_data_case0)) != 0) {
        aes_gcm_res_pass = 0;
    }

    if(aes_gcm_res_pass) {
        dbg("gcm_case0_data_pass\n");
    } else {
        dbg("gcm_case0_data_fail\n");
        aes_gcm_res_pass = 1;
    }
#if 0
    dbg("auth_tag_addr: %08x\n", aes_gcm_tag);
    dbg("auth_tag:\n");
    for(i = 0; i < 16; i++) {
        if(i%8 == 7){
            dbg(" %02x\n", aes_gcm_tag[i]);
        } else {
            dbg(" %02x", aes_gcm_tag[i]);
        }
    }
    dbg("\n");
#endif
    if(memcmp(aes_gcm_tag,aes_gcm_tag_test_case0,sizeof(aes_gcm_tag_test_case0)) != 0) {
        aes_gcm_tag_pass = 0;
    }

    if(aes_gcm_tag_pass) {
        dbg("gcm_case0_tag_pass\n");
    } else {
        dbg("gcm_case0_tag_fail\n");
        aes_gcm_tag_pass = 1;
    }
#endif

#if 0
//aes gcm no align
    uint32_t j,k;
    dma_cypt_obj.aes_endian_sel = AES_LITTLE_ENDIAN;
    dma_cypt_obj.aes_enc_decr_sel = AES_ENCR;
    for(i = 0; i < dma_cypt_obj.aes_keylen; i++) {
        dma_cypt_obj.aes_key[i] = gcm_test_key_case1[i];
    }
    //dma_aes_cbc
    for(i = 0; i < 3; i++) {
        dma_cypt_obj.aes_iv[i] = aes_gcm_iv_case1[i];
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
    aes_gcm_obj.auth_data = (uint32_t *)aes_gcm_auth_data_case1;//padding
    aes_gcm_obj.cipher_dat_len_byte = 55;
    for(k=0;k<4;k++) {
    for(j=0;j<4;j++) {
        if(j==0) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_case1 + j);
        }
        else if(j==1) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_case1_shift1 + j);
        }
        else if(j==2) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_case1_shift2 + j);
        }
        else if(j==3) {
            aes_gcm_data_shift = (aes_gcm_cipher_data_case1_shift3 + j);
        }
        aes_gcm_obj.aes_data = (uint32_t *)aes_gcm_data_shift;
//        dbg("gcm src addr: %08x\n", aes_gcm_data_shift);
        dma_cypt_obj.aes_a_len = aes_gcm_obj.auth_dat_len_byte * 8;//byte2bit
        dma_cypt_obj.aes_plain_len = aes_gcm_obj.cipher_dat_len_byte * 8;//byte2bit
        aes_gcm_res_shift = (aes_gcm_res + k);
        dma_cypt_init(&dma_cypt_obj);
        aes_gcm_calc(&dma_cypt_obj, &aes_gcm_obj, (uint32_t *)aes_gcm_res_shift, (uint32_t *)aes_gcm_tag);

//        dbg("gcm_res_addr: %08x\n", aes_gcm_res_shift);
#if 0
        dbg("aes_res :\n");
        for(i = 0; i < aes_gcm_obj.cipher_dat_len_byte; i++) {
            if(i%8 == 7){
                dbg(" %02x\n", *(aes_gcm_res_shift + i));
            } else {
                dbg(" %02x", *(aes_gcm_res_shift + i));
            }
        }
        dbg("\n");
#endif
//        dbg("auth_tag_addr: %08x\n", aes_gcm_tag);
#if 0
        dbg("auth_tag:\n");
        for(i = 0; i < 16; i++) {
            if(i%8 == 7){
                dbg(" %02x\n", aes_gcm_tag[i]);
            } else {
                dbg(" %02x", aes_gcm_tag[i]);
            }
        }
        dbg("\n");
#endif
    }//loop of j
    }//loop of k
#endif

}



#endif /* CFG_TEST_AES */


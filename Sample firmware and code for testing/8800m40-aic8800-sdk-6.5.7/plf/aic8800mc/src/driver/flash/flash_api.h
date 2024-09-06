#ifndef _FLASH_API_H_
#define _FLASH_API_H_

/**
 * Includes
 */

/**
 * Macros
 */
#define IS_FLASH_MEM_VALID(addr)    ((((unsigned int)(addr) >> 25) == (AIC_FLASH_MEM_BASE >> 25)) || \
                                    (((unsigned int)(addr) >> 26) == (AIC_CACHE_MEM_BASE >> 26)))   // 0x08000000 ~ 0x0BFFFFFF
#define IS_CODE_IN_FLASH()          (((CODE_START_ADDR >> 25) == (AIC_FLASH_MEM_BASE >> 25)) || ((CODE_START_ADDR >> 26) == (AIC_CACHE_MEM_BASE >> 26)))

/**
 * Structs
 */
/* calib info */
typedef struct {
    unsigned char cap;
    unsigned char cap_fine;
    unsigned char PADDING0[2];
} xtal_cap_info_t;

typedef struct {
    signed char ofst[3]; // TXPWR_OFST_BAND_2G4_NUM
    unsigned char ofstver;
} wifi2g4_txpwr_info_t;

typedef struct {
    signed char ofst[4]; // TXPWR_OFST_BAND_5G_NUM
} wifi5g_txpwr_info_t;

typedef struct {
    unsigned char pa_vl_vbit;
    unsigned char PADDING0[3];
} wifi2g4_txgain_info_t;

typedef struct {
    signed char agcgain_delta;
    unsigned char PADDING0[3];
} wifi2g4_rxgain_info_t;

typedef struct {
    unsigned char tone_pwr;
    unsigned char PADDING0[3];
} rf_tone_pwr_info_t;

typedef struct {
    unsigned int magic_num; /* "CALI" */
    unsigned int info_flag;
    unsigned int RESERVED_08;
    unsigned int RESERVED_0C;
    xtal_cap_info_t xtal;
    wifi2g4_txpwr_info_t wifi2g4_txpwr; // for chan 1~4, 5~9, 10~13
    wifi5g_txpwr_info_t  wifi5g_txpwr;  // for chan 36~64, 100~120, 122~140, 142~165
    wifi2g4_txgain_info_t wifi2g4_txgain;
    wifi2g4_rxgain_info_t wifi2g4_rxgain;
    rf_tone_pwr_info_t rf_tone_pwr;
    unsigned int RESERVED_28; // temp_info
} calib_info_t;

/**
 * Enums
 */
typedef enum {
    INFO_FLAG_INVALID =  1,
    INFO_READ_DONE    =  0,
    MAGIC_NUM_ERR     = -1,
    INFO_LEN_ERR      = -2,
} INFO_READ_STATUS_T;

/**
 * Get chip size as bytes
 */
unsigned int flash_chip_size_get(void);

/**
 * Get chip id
 */
unsigned int flash_chip_id_get(void);

/**
 * Erase all flash except for reserved area
 */
void flash_chip_erase(void);

/**
 * @brief       Erase flash
 * @param[in]   a4k Start address to erase, 4KB aligned
 * @param[in]   len Byte length to erase, 4KB aligned
 * @return      Error code, -4: invalid start address(null or not 4KB aligned)
 *                          -5: zero length
 *                           1: length not 4KB aligned
 */
int flash_erase(void *a4k, unsigned int len);

/**
 * @brief       Write flash
 * @param[in]   adr Start address to write, 256B aligned
 * @param[in]   len Byte length to write
 * @param[in]   buf Buffer address with data writen to flash
 * @return      Error code, -4: invalid start address(null or not 256B aligned)
 *                          -5: zero length
 *                          -6: null buffer address
 */
int flash_write(void *adr, unsigned int len, void *buf);

/**
 * @brief       Read flash
 * @param[in]   adr Start address to write, 4B aligned
 * @param[in]   len Byte length to read
 * @param[out]  buf Buffer address to store data read from flash
 * @return      Error code, -4: invalid start address(null or not 4B aligned)
 *                          -5: zero length
 *                          -6: null buffer address
 */
int flash_read(void *adr, unsigned int len, void *buf);

/**
 * Invalid all flash cache
 */
void flash_cache_invalid_all(void);

/**
 * Invalid the range of flash cache
 */
void flash_cache_invalid_range(void *adr, unsigned int len);

/*
 * Flash OTP Memory Block Address & Lock Bits
 * AIC8800MBW NNNN-N2P: (3 * 1024-Byte)
 * +-------+--------------+--------------+----------+
 * | Block | Address Base | Address End  | Lock Bit |
 * +-------+--------------+--------------+----------+
 * |  #0   |  0x00001000  |  0x000013FF  |    [0]   |
 * +-------+--------------+--------------+----------+
 * |  #1   |  0x00002000  |  0x000023FF  |    [1]   |
 * +-------+--------------+--------------+----------+
 * |  #2   |  0x00003000  |  0x000033FF  |    [2]   |
 * +-------+--------------+--------------+----------+
 * AIC8800MBW NNNN-N2G: (2 * 1024-Byte)
 * +-------+--------------+--------------+----------+
 * | Block | Address Base | Address End  | Lock Bit |
 * +-------+--------------+--------------+----------+
 * |  #0   |  0x00000000  |  0x000003FF  |          |
 * +-------+--------------+--------------+----------+
 * |  #1   |  0x00001000  |  0x000013FF  |    [0]   |
 * +-------+--------------+--------------+----------+
 */

/**
 * @brief Erase flash OTP memory
 * &param adr   Address base of block #N
 */
int flash_otp_memory_erase(void *adr);

/**
 * @brief Write flash OTP memory
 */
int flash_otp_memory_write(void *adr, unsigned int len, void *buf);

/**
 * @brief Read flash OTP memory
 */
int flash_otp_memory_read(void *adr, unsigned int len, void *buf);

/**
 * @brief Set flash OTP memory lock bits, the memory can be rw before locked
 * @param lck   bit[2:0]: block #[2:0]
 */
unsigned int flash_otp_memory_lock(unsigned int lck);

/**
 * @brief  Get erase/write protection for all flash block
 * @return 1: enable, 0:disable
 */
int flash_block_protect_all_get(void);

/**
 * @brief Set erase/write protection for all flash block
 * @param bp_en   1: enable, 0:disable
 */
void flash_block_protect_all_set(int bp_en);

/**
 * @brief Calculate crc32
 */
unsigned int flash_crc32(void *adr, unsigned int len);

/**
 * @brief       Check flash addr can be erased/written or not
 * @param[in]   adr Start address to erase/write
 * @param[in]   len Byte length to erase/write
 * @return      Non-zero means yes
 */
int flash_erase_write_addr_check(void *adr, unsigned int len);

/**
 * calib info api(read only)
 */
int flash_calib_xtal_cap_read(xtal_cap_info_t *xtal_cap);
int flash_calib_wifi2g4_txpwr_read(wifi2g4_txpwr_info_t *txpwr);
#if defined(CFG_SUPPORT_5G)
int flash_calib_wifi5g_txpwr_read(wifi5g_txpwr_info_t *txpwr);
#endif
int flash_calib_wifi2g4_txgain_read(wifi2g4_txgain_info_t *txgain);
int flash_calib_wifi2g4_rxgain_read(wifi2g4_rxgain_info_t *rxgain);
int flash_calib_rf_tone_pwr_read(rf_tone_pwr_info_t *tone_pwr);

int flash_user_data_addr_length_set(unsigned int addr, unsigned int len);
int flash_user_data_read(void *buf, unsigned int len);
int flash_user_data_write(void *buf, unsigned int len);

#endif /* _FLASH_API_H_ */

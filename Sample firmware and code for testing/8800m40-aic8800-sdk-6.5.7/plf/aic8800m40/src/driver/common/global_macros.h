

#ifndef _GLOBAL_MACROS_H_
#define _GLOBAL_MACROS_H_



// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================




#define KSEG0(addr)     (addr)
#define KSEG1(addr)     (addr)

#define REG_ACCESS_ADDRESS(addr)    KSEG1(addr)

/* Define access cached or uncached */
#define MEM_ACCESS_CACHED(addr)     (assert(0, "NOT SUPPORTED"))
#define MEM_ACCESS_UNCACHED(addr)   (assert(0, "NOT SUPPORTED"))

/* Register access for assembly */
#define BASE_HI(val) (((0xa0000000 | val) & 0xffff8000) + (val & 0x8000))
#define BASE_LO(val) (((val) & 0x7fff) - (val & 0x8000))


/* to extract bitfield from register value */
#define GET_BITFIELD(dword, bitfield) (((dword) & (bitfield ## _MASK)) >> (bitfield ## _SHIFT))

#define EXP2(n) (1<<(n))

#define REG32 volatile unsigned int
#define REG16 volatile unsigned short
#define REG8  volatile unsigned char

#define UINT32 unsigned int
#define UINT16 unsigned short 
#define UINT8  unsigned char 

#define REG_READ_UINT32( _reg_ )           (*(volatile unsigned int*)(_reg_))
#define REG_WRITE_UINT32( _reg_, _val_)    ((*(volatile unsigned int*)(_reg_)) = (unsigned int)(_val_))

#define REG_READ_U64( _reg_ )          (*(volatile unsigned long*)(_reg_))
#define REG_WRITE_U64( _reg_, _val_)   ((*(volatile unsigned long*)(_reg_)) = (unsigned long)(_val_))


#define write_reg32(addr,data)  (*((volatile unsigned int *)(addr)) = (data))
#define read_reg32(addr)        (*((volatile unsigned int *)(addr)))


#endif


#0x31F7
PLATFORMID=12791

PLATFORMOS=dryos

MEMBASEADDR=0x1900    # address where wif or diskboot code will be loaded by camera, ROM:FF810134
RESTARTSTART=0x50000   # size of memory region for CHDK
MEMISOSTART=0x14B394    # ROM:FF81014C
ROMBASEADDR=0xFF810000    # 0xFF810000 for S-, SD-, and G- series

PLFLAGS=-DMEMBASEADDR=$(MEMBASEADDR) -DMEMISOSTART=$(MEMISOSTART) -DMEMISOSIZE=$(MEMISOSIZE)
PLFLAGS+=-DRESTARTSTART=$(RESTARTSTART)

# type of diskboot encoding: undefined = none; 1 = original; 2 = sx200, d10; 3 = ixus200...
# Dancing Bits
NEED_ENCODED_DISKBOOT=4

# FIR (requires correct keys in platform/fi2.inc)
# FI2KEY: ROM:FFFF366C , Offset: 0x7E366C
# FI2IV: ROM:FFC15130 , Offset: 0x405130
KEYSYS=d4a

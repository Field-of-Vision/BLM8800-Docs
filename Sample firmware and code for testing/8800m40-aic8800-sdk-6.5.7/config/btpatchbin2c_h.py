import sys
from os.path import isfile, splitext
import binascii

def bin2patch_c(binf, patch_c, bytew):
    fh_bin = open(binf, 'rb')
    fh_patch_c = open(patch_c, 'wb')
    fh_patch_c.write('#include <stdint.h>\r\n')
    fh_patch_c.write('const uint32_t ')
    filename  = patch_c.rstrip('.c')
    fh_patch_c.write(filename)
    fh_patch_c.write('[] = \r\n')
    fh_patch_c.write('{\r\n')
    array_size = 0
    try:
        while True:
            chunk = fh_bin.read(bytew)
            if not chunk:
                break
            hexstr = binascii.b2a_hex(chunk)
            array_size += bytew
            if bytew > 1:
                hexstr = hexstr.decode('hex')[::-1].encode('hex_codec')
            fh_patch_c.write('0x')
            fh_patch_c.write(hexstr)
            fh_patch_c.write(',\r\n')
    finally:
        fh_patch_c.write('};\r\n')
        fh_patch_c.close()
        fh_bin.close()
    return array_size

def bin2patch_h(binf, patch_h, array_size):
    fh_patch_h = open(patch_h, 'wb')
    filename  = patch_h.rstrip('.h')
    fh_patch_h.write('#include <stdint.h>\r\n')
    fh_patch_h.write('/// ' + filename + '\r\n')
    fh_patch_h.write('extern const uint32_t ' + filename + '[];\r\n')
    fh_patch_h.write('/// size of ' + filename + '\r\n')
    fh_patch_h.write('#define AICBT_' + filename.upper() + '_SIZE' + '        ' + bytes(hex(array_size)) + '\r\n')
    fh_patch_h.close()

if __name__ == '__main__':
    bin_path = None
    if len(sys.argv) == 2 and isfile(sys.argv[1]):
        bin_path = sys.argv[1]
        out_path_c = splitext(bin_path)[0] + '.c'
        array_size = 0
        array_size = bin2patch_c(bin_path, out_path_c, 4)
        out_path_h = splitext(bin_path)[0] + '.h'
        bin2patch_h(bin_path, out_path_h, array_size)
    else:
        print 'Usage: ' + sys.argv[0] + ' [binary file]'

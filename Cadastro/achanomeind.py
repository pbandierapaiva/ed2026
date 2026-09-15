#

import sys
import struct

struct_format = "=200sl" 
struct_size = struct.calcsize(struct_format)


# if len(sys.argv) < 2:
#     print(f"Faltou parâmetro")
#     exit(-1)
# query = sys.argv[1].upper()


# fin = open("cadastro.ind","rb")   
with open("cadastro.ind", "rb") as fin:

    while True:

        data = fin.read(struct_size)
        if data=="": break
        if len(data) == struct_size:
                # Unpack the binary data into a Python tuple
                nome_bytes, avanco = struct.unpack(struct_format, data)
                
                # Decode the byte string to a normal Python string
                # nome = nome_bytes.decode('utf-8').strip('\x00')
                nome = nome_bytes.decode('utf-8', errors='ignore')   #.split('\x00')[0]
                
                n = nome.split('\x00')[0]
                print(f"Nome: {n}")
                print(f"Avanco: {avanco}")
    
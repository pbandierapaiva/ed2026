# Programa em python para achar um nome num cadastro
import sys

def pegaCpo(lin, ncpo):
    partes = lin.split(";")
    return partes[ncpo].strip('"')

if len(sys.argv) < 2:
    print(f"Faltou parâmetro")
    exit(-1)

query = sys.argv[1].upper()

fin = open("/home/pub/ed/Cadastro.csv")

while True:
    linha = fin.readline()
    if linha=="":
        break
    
    if  query in pegaCpo(linha,1):
        print("-------", pegaCpo(linha,0))
        print(pegaCpo(linha,1))
        print(pegaCpo(linha,3))
        print(pegaCpo(linha,4))
        print(pegaCpo(linha,5))
        print(pegaCpo(linha,16))
        print(pegaCpo(linha,18))

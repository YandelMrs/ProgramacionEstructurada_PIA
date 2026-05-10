import requests
import json
import sys

def conseguir_coordenadas(direccion):

    url = f"https://nominatim.openstreetmap.org/search?q={direccion}&format=json"
    headers = {'User-Agent': 'MiAppDeC++'}
    
    try:
        response = requests.get(url, headers=headers)
        data = response.json()
        
        if data:
            resultado = {"lat": data[0]["lat"], "lon": data[0]["lon"], "status": "ok"}
        else:
            resultado = {"status": "error", "message": "No se encontro la direccion"}
            
        with open("transferencia.json", "w") as f:
            json.dump(resultado, f)
            
    except Exception as e:
        with open("transferencia.json", "w") as f:
            json.dump({"status": "error", "message": str(e)}, f)

if __name__ == "__main__":
    
    if len(sys.argv) > 1:
        direccion_buscada = sys.argv[1]
        conseguir_coordenadas(direccion_buscada)
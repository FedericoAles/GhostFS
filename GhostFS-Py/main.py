import sys
from pathlib import Path
from core.controller import GhostController

def main():
  print("--- GhostFS: Python Interface ---")
  
  try:
    ghost = GhostController()
    print(f"[Init] Controlador conectado al binario: {ghost.binary_path.name}")

    # --- ZONA DE PRUEBAS ---
    input_png = ""
    secret_txt = ""
    output_png = ""
    recovered_txt = ""

    if not Path(input_png).exists() or not Path(secret_txt).exists():
      print(f"[Warning] No se encontraron {input_png} o {secret_txt} para la prueba automática.")
      print("Coloca archivos de prueba en esta carpeta y vuelve a ejecutar.")
      return

    # Prueba de Ocultamiento (Hide)
    print(f"\n[1/2] Ocultando '{secret_txt}' en '{input_png}'...")
    if ghost.hide(input_png, secret_txt, output_png):
      print(" -> Ocultamiento exitoso.")
    else:
      print(" -> Falló el ocultamiento.")
      return # Cortamos si falla

    # Prueba de Recuperación (Read)
    print(f"\n[2/2] Recuperando datos de '{output_png}'...")
    if ghost.read(output_png, recovered_txt):
      print(f" -> Recuperación exitosa. Datos guardados en '{recovered_txt}'.")
    else:
      print(" -> Falló la recuperación.")

  except FileNotFoundError as e:
    print(e)
  except Exception as e:
    print(f"[Error No Controlado] {e}")

# Para evitar ejecuciones no deseadas.
if __name__ == "__main__":
  main()
import subprocess
from pathlib import Path

class GhostController:
  def __init__(self):
    current_dir = Path(__file__).resolve().parent
    project_root = current_dir.parent.parent
    
    self.binary_path = project_root / "GhostFS-Core" / "bin" / "GhostLab.exe" # Construimos la ruta al binario de forma segura, sin estar hardcodeada.

    if not self.binary_path.exists():
      raise FileNotFoundError(f"[Error] No se encontró el ejecutable en: {self.binary_path}")

  def _run(self, args: list) -> bool:
    """Ejecuta el binario y captura el retorno."""
    args_str = [str(arg) for arg in args] # Convertimos todos los argumentos a string por seguridad (Windows a veces se queja con Path objects).

    result = subprocess.run(args_str, capture_output=True, text=True) 
      
    if result.returncode == 0:
      print("[Info] Operación exitosa del Core.")
      if result.stdout:
        print(f"[C++ Log]:\n{result.stdout}")
      return True
    else:
      print(f"[Error del Core] Código: {result.returncode}")
      print(f"Detalle: {result.stderr}")
      return False

  # Wrappers de los comandos de la terminal, tanto para hide como para read.
  def hide(self, input_img: str, secret_file: str, output_img: str) -> bool:
    """Wrapper para operación Hide."""
    if not Path(input_img).exists() or not Path(secret_file).exists():
      raise FileNotFoundError(f"[Error] (hide) - Alguno de los archivos input no existe.")

    cmd = [self.binary_path, "hide", input_img, secret_file, output_img] 
    
    return self._run(cmd)

  def read(self, input_img: str, output_file: str) -> bool:
    """Wrapper para operación Read."""
    if not Path(input_img).exists():
      raise FileNotFoundError(f"[Error] (read) - El archivo input no existe.")
    
    cmd = [self.binary_path, "read", input_img, output_file]
    
    return self._run(cmd)
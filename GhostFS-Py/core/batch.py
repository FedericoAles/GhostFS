from pathlib import Path
from typing import List, Tuple
from core.controller import GhostController

class BatchProcessor:
  def __init__(self):
    self.controller = GhostController()

  def _get_files(self, path: Path) -> List[Path]:
    """
    Helper privado.
    Retorna una lista ORDENADA alfabéticamente de los archivos de un path indicado.
    """
    items = [f for f in path.iterdir() if f.is_file()]
    return sorted(items)

  def process_pool(self, secrets_dir: str, pool_dir: str, output_dir: str) -> dict:
    """
    Toma TODOS los archivos de secrets_dir y busca portadores disponibles en pool_dir.
    """
    secrets_path = Path(secrets_dir) # Los archivos que quiero encriptar.
    pool_path = Path(pool_dir)       # Las potenciales imagenes portadoras de los archivos a encriptar.
    out_path = Path(output_dir)      # El resultado

    if not secrets_path.exists() or not pool_path.exists():
      raise FileNotFoundError(f"[Error] (batch) - Alguno de los input no existe.")
    
    if not out_path.exists():
      print(f"\n[WARNING] {out_path} no existe.\n[INFO] Creando {out_path}...")
      out_path.mkdir(parents=True, exist_ok=True)

    secrets: List[Path] = self._get_files(secrets_path) 
    extensions = ('.png', '.jpg', '.jpeg')
    covers: List[Path] = [f for f in self._get_files(pool_path) if f.suffix.lower() in extensions] # Me aseguro que son imagenes.

    print(f"\n[Batch] Detectados {len(secrets)} secretos y {len(covers)} imágenes disponibles.")

    if len(secrets) > len(covers):
      raise ValueError("[ERROR] Hay mas archivos a encriptar que imagenes portadoras.")

    report = {'processed': 0,'success': 0, 'errors': 0}

    for index, secret_file in enumerate(secrets):
      output_name = out_path / f"File-{index}.png"
      result = self.controller.hide(covers[index], secret_file, output_name)
      report['processed'] += 1
      if result:
        report['success'] += 1
        print(f"\n[INFO] {secret_file.name} encriptado en {covers[index].name}.")
      else:
        report['errors'] += 1
        print(f"\n[ERROR] {secret_file.name} no se pudo encriptar en {covers[index].name}.")
    
    return report
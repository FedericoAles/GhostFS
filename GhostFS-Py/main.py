from pathlib import Path
from core.batch import BatchProcessor

def main():
  print("--- GhostFS: Batch Integration Test ---")
  
  # Definimos rutas relativas a la raíz del proyecto
  # data/secrets: Pon aquí 3 archivos de texto/pdf
  # data/covers: Pon aquí 3 imágenes .png
  base_dir = Path(__file__).parent / "data"
  secrets_dir = base_dir / "secrets"
  covers_dir = base_dir / "covers"
  output_dir = base_dir / "output"

  try:
    processor = BatchProcessor()
    
    # Ejecutamos el procesamiento por lotes
    report = processor.process_pool(secrets_dir, covers_dir, output_dir)
    
    print("\n--- Reporte Final ---")
    print(f"Procesados: {report['processed']}")
    print(f"Éxitos:     {report['success']}")
    print(f"Errores:    {report['errors']}")

  except Exception as e:
    print(f"[Fatal Error] {e}")

if __name__ == "__main__":
  main()
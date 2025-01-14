from pathlib import Path

def renomear_arquivos(pasta):
    pasta = Path(pasta)

    if not pasta.exists():
        print(f"A pasta {pasta} não existe.")
        return

    for arquivo in pasta.iterdir():
        if arquivo.is_file() and arquivo.name.startswith("Atividade") and arquivo.suffix == ".c":
            try:
                numero = arquivo.stem.replace("Atividade", "")
                novo_nome = pasta / f"Exemplo{numero}.c"
                
                arquivo.rename(novo_nome)
                print(f"Renomeado: {arquivo.name} -> {novo_nome.name}")
            except Exception as e:
                print(f"Erro ao renomear {arquivo.name}: {e}")

caminho_da_pasta = input("Digite o caminho da pasta onde estão os arquivos: ")
renomear_arquivos(caminho_da_pasta)

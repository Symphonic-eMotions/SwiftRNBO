import os
import sys
import datetime

def find_swift_files(base_path):
    swift_files = []
    for root, dirs, files in os.walk(base_path):
        for f in files:
            if f.endswith(".swift"):
                swift_files.append(os.path.join(root, f))
    return swift_files

def extract_classes_and_structs(file_content):
    """
    Zoekt naar 'class' en 'struct' definities en extraheert de volledige code-blokken
    tot de bijbehorende sluitende accolade is gevonden.
    """
    results = []
    lines = file_content.split('\n')
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i].strip()
        # Controleer op een class of struct definitie
        if line.startswith("class ") or line.startswith("struct "):
            start_index = i
            # Zoek de eerste regel waar '{' in voorkomt, dit kan de start index zelf zijn of een daaropvolgende regel
            brace_line_index = i
            open_brace_pos = None
            while brace_line_index < n:
                brace_line = lines[brace_line_index]
                if '{' in brace_line:
                    open_brace_pos = brace_line_index
                    break
                brace_line_index += 1
            if open_brace_pos is None:
                # Geen accolades gevonden, overslaan
                i += 1
                continue
            
            brace_count = 0
            block_lines = []
            j = start_index
            found_start_brace = False
            
            # Doorloop alle regels vanaf de definitie tot we alle accolades gesloten hebben
            while j < n:
                cur_line = lines[j]
                for ch in cur_line:
                    if ch == '{':
                        brace_count += 1
                        found_start_brace = True
                    elif ch == '}':
                        brace_count -= 1
                block_lines.append(cur_line)
                j += 1
                if found_start_brace and brace_count == 0:
                    # Sluitend accolade gevonden; blok compleet
                    break
            
            results.append('\n'.join(block_lines))
            i = j
        else:
            i += 1
    return results

def main():
    if len(sys.argv) < 2:
        print("Gebruik: python summary_extractor.py /pad/naar/het/project")
        sys.exit(1)
        
    project_path = sys.argv[1]
    # Vind alle swift-bestanden
    swift_files = find_swift_files(project_path)
    
    # Maak een output-bestand met timestamp aan
    timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    output_file = os.path.join(os.path.dirname(__file__), f"samenvatting_{timestamp}.swift")

    summary = []
    for sf in swift_files:
        with open(sf, 'r', encoding='utf-8') as f:
            content = f.read()
            blocks = extract_classes_and_structs(content)
            if blocks:
                relative_path = os.path.relpath(sf, project_path)
                summary.append(f"//Bestand: {relative_path}")
                for b in blocks:
                    summary.append(b)
                summary.append("")  # lege regel als scheiding

    with open(output_file, 'w', encoding='utf-8') as outf:
        outf.write("\n".join(summary))

    print(f"Samenvatting opgeslagen in: {output_file}")

if __name__ == "__main__":
    main()

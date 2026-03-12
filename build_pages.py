import os

LIB_DIR = "cpp/library"
MANUAL_DOCS_DIR = "docs"
OUT_DIR = "_build"

os.makedirs(OUT_DIR, exist_ok=True)

# Check all the files in the library
for root, dirs, files in os.walk(LIB_DIR):
    for file in files:
        if not file.endswith(('.hpp', '.cpp')): continue
        
        rel_path = os.path.relpath(os.path.join(root, file), LIB_DIR)
        # doc_name = rel_path.replace(os.sep, "_") + ".md"
        
        # 1. Build Front Matter
        lang = "cpp"
        content = f"---\nlayout: default\ntitle: {file}\n---\n\n"
        content += f"# {file}\n\n"
        
        # 2. Concatenate files under docs/
        manual_path = os.path.join(MANUAL_DOCS_DIR, rel_path.replace(os.path.splitext(file)[1], ".md"))
        if os.path.exists(manual_path):
            with open(manual_path, "r") as f:
                content += "## 解説\n" + f.read() + "\n\n"
        
        content += f"## 実装コード\n{{% highlight {lang} %}}\n"
        with open(os.path.join(root, file), "r") as f:
            content += f.read()
        content += "\n{{% endhighlight %}}\n"
        
        # Make an output directory
        os.makedirs(os.path.join(OUT_DIR, os.path.dirname(rel_path)), exist_ok=True)
        # Make an output file
        output_path = rel_path + ".md"
        with open(os.path.join(OUT_DIR, output_path), "w") as f:
            f.write(content)

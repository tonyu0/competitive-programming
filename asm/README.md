# assembly-language
* アセンブリ言語実行用dockerイメージの作成
```sh
  make build
```

* src以下のasmファイルをアセンブルして実行
```sh
  make run file={filename}
```

* src以下のasmファイルをアセンブルして実行(input.txtを読み込む)
```sh
  make run-with-input file={filename}
```
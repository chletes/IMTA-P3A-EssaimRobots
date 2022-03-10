## LaTeX documentation

This folder keeps all the LaTeX files. To compile everything and get a PDF, we synchronized this git with Overleaf. 

Almost all diagrams were finally written in LaTeX using `tikz` package. In order to export them to PDF, you can use the `doc/diagrams/export_diagrams.tex` file. 

1. Change the desired diagram to export in line #9: 

```
\include{doc/diagrams/communication/sequence_diagram}
```

2. Select `doc/diagrams/export_diagrams.tex` as the main document under _Settings_ in Overleaf side-bar menu:

![](/assets/img/overleaf_change_main_document.png)

3. After exporting, change the main document again to `main.tex`.
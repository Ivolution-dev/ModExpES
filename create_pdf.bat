@echo off
setlocal enabledelayedexpansion

set pandoc_files=
for %%f in (.\Markdowns\*.md) do (
    set pandoc_files=!pandoc_files! "%%f"
)

pandoc %pandoc_files% -o .\Abgabe\parts\ba.pdf --toc --template=template.tex


pdftk .\Abgabe\parts\deckblatt.pdf .\Abgabe\parts\ba.pdf Fertigung\PCB\Schematic_ModExpES_2025-01-24.pdf \Fertigung\Montageplatte\Montageplatte_TechnicalDrawing.pdf cat output .\Abgabe\Bachelorarbeit.pdf

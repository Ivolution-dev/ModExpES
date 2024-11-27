@echo off
setlocal enabledelayedexpansion

set pandoc_files=
for %%f in (.\Markdowns\*.md) do (
    set pandoc_files=!pandoc_files! "%%f"
)

pandoc %pandoc_files% -o .\Abgabe\parts\ba.pdf --toc --template=template.tex


pdftk .\Abgabe\parts\deckblatt.pdf .\Abgabe\parts\ba.pdf cat output .\Abgabe\Bachelorarbeit.pdf

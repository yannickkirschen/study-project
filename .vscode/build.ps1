Push-Location .\Thesis

try {
    New-Item -ItemType Directory -Force -Path build

    Write-Output "Compile #1"
    pdflatex -output-directory build Thesis.tex

    Write-Output "Build glossaries"
    makeglossaries -d build Thesis.glo

    Write-Output "Build bibliography"
    biber --output-directory build Thesis.bcf

    Write-Output "Compile #2"
    pdflatex -output-directory build Thesis.tex

    Write-Output "Compile #3"
    pdflatex -output-directory build Thesis.tex
}
finally {
    Pop-Location
}

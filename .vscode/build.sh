cd ./$TEX_SOURCE_DIRECTORY

mkdir -p build

pdflatex -output-directory build $TEX_SOURCE.tex
makeglossaries -d build $TEX_SOURCE.glo
biber --output-directory build $TEX_SOURCE.bcf
pdflatex -output-directory build $TEX_SOURCE.tex
pdflatex -output-directory build $TEX_SOURCE.tex
mv build/$TEX_SOURCE.pdf build/$TEX_PDF_NAME.pdf

cd ..

#/bin/sh

mkdir -p .out
cd .out
cmake ../
make

for file in ../Tests/*.in
do	
	echo "${file}"
	filename="${file%.*}"
	./hw2 -t < "${filename}.in"
done

cd ..
rm -rf .out

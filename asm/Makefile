build:
	docker build . -t assembly-language

run:
	docker run --rm -v ${CURDIR}/src:/src -w /src assembly-language sh -c "nasm -f elf64 ${file}.asm && ld ${file}.o"
	docker run --rm -v ${CURDIR}/src:/src -w /src assembly-language sh -c "./a.out"

run-with-input:
	docker run --rm -v ${CURDIR}/src:/src -w /src assembly-language sh -c "nasm -f elf64 ${file}.asm && ld ${file}.o"
	docker run --rm -v ${CURDIR}/src:/src -w /src assembly-language sh -c "./a.out < input.txt"

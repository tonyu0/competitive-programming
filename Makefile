# =========================
# CONFIG
# =========================

CPP=g++
CPPFLAGS=-std=c++23 -O2 -Wall

RUST=rustc

HASKELL=runhaskell

ASM=nasm
ASMFLAGS=-felf64
LINKER=x86_64-linux-gnu-ld
# binutils-x86-64-linux-gnu: 
# Due to Docker's multi-platform capabilities, there are cases where "uname -m" in the container does not match the host.
# In that case, ld cannot link correctly because the target CPU architecture is different from that of nasm.
# This means trying to create an x86_64 executable from an ARM64 environment, so needs to install cross-build tools.

DOCKER=docker compose exec cp
# or "docker compose run --rm cp" (prevent orphan containers)

# =========================
# Run a solution program
# =========================

cpp-run:
	$(DOCKER) bash -c "$(CPP) $(CPPFLAGS) $(file) -o main && ./main"

rs-run:
	$(DOCKER) bash -c "$(RUST) $(file) -o main && ./main"

hs-run:
	$(DOCKER) bash -c "${HASKELL} $(file)"

asm-run:
	$(DOCKER) bash -c "$(ASM) $(ASMFLAGS) $(file) -o main.o && $(LINKER) main.o -o main && ./main"

# =========================
# Docker
# =========================

build:
	docker compose build

start:
	docker compose up -d

stop:
	docker compose down

shell:
	docker compose exec cp bash
	
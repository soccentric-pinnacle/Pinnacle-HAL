IMAGE_NAME ?= pinnacle

.PHONY: build run clean delete-images

build:
	@echo "Building Docker image $(IMAGE_NAME) for NXP i.MX 93 (ARM64)..."
	docker buildx build --platform linux/arm64 --load --build-arg UID=$(shell id -u) --build-arg GID=$(shell id -g) -t $(IMAGE_NAME) .

run:
	# No --gpus flag: NXP i.MX 93 has no CUDA-capable GPU
	docker run -it --rm --hostname "NXP i.MX 93" $(IMAGE_NAME)

clean:
	docker rmi $(IMAGE_NAME) || true

delete-images:
	docker rmi $(docker images -q) || true

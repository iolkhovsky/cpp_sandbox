CONTAINER_NAME := "dev-container"
IMAGE_NAME := "ubuntu-22-04-dev"
WORKSPACE_HOST_PATH := "/Users/iolkhovsky/repos"
WORKSPACE_CONTAINER_PATH := "/repos"
FORWARD_PORT := 55501

image: FORCE
	docker build -t $(IMAGE_NAME) .
FORCE:

container: FORCE
	docker run \
		-it \
		-d \
		--name $(CONTAINER_NAME) \
		-p $(FORWARD_PORT):$(FORWARD_PORT) \
		-v $(WORKSPACE_HOST_PATH):$(WORKSPACE_CONTAINER_PATH) \
		--env CUDA_VISIBLE_DEVICES=$(CUDA_VISIBLE_DEVICES) \
		$(IMAGE_NAME):latest
FORCE:

attach: FORCE
	docker start -ia $(CONTAINER_NAME)
FORCE:

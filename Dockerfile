# Base image
FROM ubuntu:latest

# Update packages of the system and install necessary dependencies
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:pistache+team/unstable -y && \
    apt-get update && \
    apt-get install -y libpistache-dev make g++

# Copy project files to container
COPY . /build

# Define directory of work
WORKDIR /build

# Define an necessary variable for run the app correctly
ENV LD_LIBRARY_PATH=/usr/local/lib

# Compile the app
RUN make

# Expose the port 8080 for run the api
EXPOSE 8080

# Finally, run the app
CMD ["./bankapp"]

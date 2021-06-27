# using existing docker image as base image
FROM ubuntu

#change the working dir

RUN apt-get -y update && apt-get install -y 
RUN apt-get -y install g++


WORKDIR /usr/app/


#copy the exe in container
COPY ./ ./



RUN g++ -o Test hello-world.c

# Step 3: Tell the image what to do when it starts as container
CMD ["./Test"]
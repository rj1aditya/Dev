# Specify a base image
FROM node:alpine
WORKDIR /usr/app

# Install some depenendencies
COPY ./ ./ 
# above command to copy all curr dir content to curr dir of container.
RUN npm install

# Default command
CMD ["npm", "start"]
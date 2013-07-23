#!/bin/sh
# This script adds ppa-repository which you may use
# bumblebee offers Nvidia Optimus tech, save energy and low temp
sudo add-apt-repository ppa:bumblebee/stable
# oracle-java offers more stable functions
sudo add-apt-repository ppa:webupd8team/java
# node.js offers Server-Side Javascript
sudo add-apt-repository ppa:chris-lea/node.js
# update your software information
sudo apt-get update
# update your pciids, this may take minutes, depend on lan speed
sudo update-pciids
# install bumblebee
sudo apt-get install bumblebee bumblebee-nvidia
# remove default openjdk
sudo apt-get remove openjdk-7-jre openjdk-7-jre-headless openjdk-7-jre-lib
# install oracle jave
sudo apt-get install oracle-java8-installer oracle-java8-set-default
# install node.js
sudo apt-get install nodejs

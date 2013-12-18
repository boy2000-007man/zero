#!/bin/bash -e
# This script adds ppa-repository which you may use
sudo add-apt-repository ppa:bumblebee/stable    # bumblebee offers Nvidia Optimus tech, save energy and low temp
sudo add-apt-repository ppa:webupd8team/java    # oracle-java offers more stable functions
sudo add-apt-repository ppa:ubuntu-x-swat/x-updates
sudo apt-get install ia32-libs
sudo add-apt-repository ppa:caffeine-developers/ppa
sudo apt-get install caffeine
sudo add-apt-repository ppa:chris-lea/node.js   # node.js offers Server-Side Javascript
sudo apt-get update                             # update your software information
sudo update-pciids                              # update your pciids, this may take minutes, depend on lan speed
sudo apt-get install bumblebee bumblebee-nvidia # install bumblebee
sudo apt-get remove openjdk-7-jre \
    openjdk-7-jre-headless openjdk-7-jre-lib    # remove default openjdk
sudo apt-get install oracle-java8-installer \
    oracle-java8-set-default                    # install oracle jave
sudo apt-get install nodejs                     # install node.js
sudo add-apt-repository ppa:ubuntu-wine/ppa
sudo add-apt-repository ppa:webupd8team/sublime-text-3
exit 0

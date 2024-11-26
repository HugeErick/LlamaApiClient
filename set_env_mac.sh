#!/bin/bash
read -p "Enter your GROG_CLOUD_API_DEV_TOKEN: " token
echo "export GROG_CLOUD_API_DEV_TOKEN=$token" >> ~/.bash_profile
source ~/.bash_profile

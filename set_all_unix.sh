#!/bin/bash

# Detect if the script is being run with sufficient privileges
if [[ $EUID -ne 0 ]]; then
  echo "Please run this script as root to proceed with system updates."
  exit 1
fi

echo "Checking for required dependencies..."
sudo apt-get update

# Install necessary packages if not already present
sudo apt-get install -y gcc make libcurl4-openssl-dev libcjson-dev

# Prompt user for token input
read -p "Enter your GROG_CLOUD_API_DEV_TOKEN: " token
if [ -z "$token" ]; then
  echo "No token entered. Exiting installation process."
  exit 1
fi

# Export token for current and future sessions
echo "export GROG_CLOUD_API_DEV_TOKEN=$token" >> ~/.bashrc
source ~/.bashrc

echo "Environment set up successfully!"


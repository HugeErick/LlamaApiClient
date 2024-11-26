#!/bin/bash

# Check for root privileges
if [[ $EUID -ne 0 ]]; then
  echo "Please run this script as root to proceed with the installation."
  exit 1
fi

echo "Starting macOS installation process..."

# Check for Homebrew
if ! command -v brew &> /dev/null; then
  echo "Homebrew not found. Installing Homebrew..."
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

# Update Homebrew and install dependencies
echo "Updating Homebrew..."
brew update

echo "Installing required dependencies..."
brew install gcc make curl cjson

# Prompt the user for the token
read -p "Enter your GROG_CLOUD_API_DEV_TOKEN: " token
if [ -z "$token" ]; then
  echo "No token entered. Exiting installation process."
  exit 1
fi

# Set up the environment variable
echo "Exporting GROG_CLOUD_API_DEV_TOKEN..."
echo "export GROG_CLOUD_API_DEV_TOKEN=$token" >> ~/.bash_profile
source ~/.bash_profile

echo "Installation and environment setup complete!"


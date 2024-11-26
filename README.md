# LlamaApiClient

## Description

LlamaApiClient is a high-performance C-based client for interacting with the Groq API, specifically designed for chat completions. This client utilizes the CURL library for HTTP requests and cJSON for JSON parsing, providing a robust and efficient interface to the Groq API's chat completion endpoint.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Installation

### Prerequisites

- GCC compiler
- Make build system
- libcurl
- cJSON library

### Steps

1. Install Make:
   - **Linux (Ubuntu/Debian)**: `sudo apt-get install make`
   - **macOS**: Install Xcode Command Line Tools: `xcode-select --install`
   - **Windows**: Install [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)

2. Open Terminal (macOS/Linux) or PowerShell (Windows)

3. Clone the repository:
   ```
   git clone https://github.com/HugeErick/LlamaApiClient.git
   cd LlamaApiClient
   ```

4. Build the project:
   ```
   make
   ```

## Usage

1. Set up your Groq API key:
   ```
   make set_env
   ```
   Follow the prompts to enter your API key.

2. Run the client:
   ```
   make run
   ```

3. Follow the on-screen prompts to interact with the Groq API.

## Features

- Seamless interaction with Groq API's chat completion endpoint
- Option to save API responses as JSON files
- Cross-platform compatibility (Linux, macOS, Windows)
- Robust error handling and memory management

## Configuration

The client uses the following environment variable:

- `GROG_CLOUD_API_DEV_TOKEN`: Your Groq API key

You can set this manually or use the provided `make set_env` command.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

Erick Gonzalez Parada - erick.parada101@gmail.com

Project Link: [https://github.com/HugeErick/LlamaApiClient](https://github.com/yourusername/LlamaApiClient)

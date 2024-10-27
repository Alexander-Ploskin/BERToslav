# BERToslav

BERToslav is a BERT-based Telegram bot designed to protect your chat from toxic behavior.

## Features

- Utilizes BERT (Bidirectional Encoder Representations from Transformers) technology
- Integrates with Telegram as a bot
- Monitors chat for toxic behavior
- Helps maintain a positive chat environment

## Build

To build the Docker image for BERToslav, use the following command:

```bash
docker build -t bertoslav .
```

## Run

To run the BERToslav bot, use the following Docker command:

```bash
docker run -v $(pwd)/data:/data bertoslav
```

## Prerequisites

- Docker installed on your system
<!-- - Telegram Bot API token (you'll need to set this up with BotFather on Telegram) -->

## Configuration

Before running the bot, make sure to:
<!-- - Set up your Telegram bot and obtain the API token -->
- Configure the bot token and any other necessary settings
- Install all necessary dependencies listed in ```requrements.txt``` file

## Contributing

Contributions to BERToslav are welcome! Please refer to the contributing guidelines for more information on how to submit pull requests, report issues, or request features.

## Contact
For questions, support, or to report issues, please open an issue on the GitHub repository.
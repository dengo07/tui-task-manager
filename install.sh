#!/bin/bash
set -e

APP_NAME="todo"
BIN_PATH="/usr/local/bin"
DATA_DIR="$HOME/.local/share/todo"

echo "▶ Building project..."
make

if [ ! -f "$APP_NAME" ]; then
    echo "❌ Binary '$APP_NAME' not found. Build failed?"
    exit 1
fi

echo "▶ Installing binary to $BIN_PATH"
sudo install -m 755 "$APP_NAME" "$BIN_PATH/$APP_NAME"

echo "▶ Creating data directory (if not exists)"
mkdir -p "$DATA_DIR"

echo "✅ Installation complete!"
echo "➡ Run with: $APP_NAME"
make clean
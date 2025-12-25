#!/bin/bash

APP_NAME="todo"
BIN_PATH="/usr/local/bin"
DATA_DIR="$HOME/.local/share/todo"
CONFIG_DIR="$HOME/.config/todo"

echo "⚠ Removing binary..."
sudo rm -f "$BIN_PATH/$APP_NAME"

echo "⚠ Remove user data?"
read -p "Delete todo data and config? [y/N]: " confirm

if [[ "$confirm" == "y" || "$confirm" == "Y" ]]; then
    rm -rf "$DATA_DIR"
    rm -rf "$CONFIG_DIR"
    echo "🗑 User data removed"
else
    echo "ℹ User data kept"
fi

echo "✅ Uninstall complete."

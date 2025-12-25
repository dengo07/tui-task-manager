#!/bin/bash
set -e

APP=todo

echo "▶ Building..."
make compile

echo "▶ Installing binary..."
sudo install -m 755 $APP /usr/local/bin/$APP

echo "▶ Creating data directory..."
mkdir -p "$HOME/.local/share/todo"

echo "✅ Installed. Run: todo"

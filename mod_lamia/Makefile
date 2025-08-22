# MedusaServ Authentication Module Makefile
# ========================================
# Version: 0.3.0c
# Author: roylepython
# Project: The Medusa Project

CXX = g++
CXXFLAGS = -std=c++17 -pthread -O2 -Wall -Wextra
TARGET = medusaserv_auth_production
SOURCE = medusaserv_auth_fixed.cpp

# Build targets
.PHONY: all clean install deploy test

all: $(TARGET)

$(TARGET): $(SOURCE)
	@echo "🔮 Compiling MedusaServ Authentication Server v0.3.0c..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)
	@echo "✅ Compilation successful!"

clean:
	@echo "🧹 Cleaning build artifacts..."
	rm -f $(TARGET)
	@echo "✅ Clean complete!"

install: $(TARGET)
	@echo "📦 Installing to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod +x /usr/local/bin/$(TARGET)
	@echo "✅ Installation complete!"

deploy: $(TARGET)
	@echo "🚀 Deploying to production server..."
	@echo "⚠️  Using secure credential vault for deployment"
	@./scripts/deploy_secure.sh $(TARGET)
	@echo "✅ Deployment complete!"

start-production: deploy
	@echo "⚡ Starting production server..."
	@echo "⚠️  Using secure credential vault for startup"
	@./scripts/start_secure.sh $(TARGET)
	@echo "✅ Production server started!"

test: $(TARGET)
	@echo "🧪 Testing authentication server..."
	@echo "Starting test server on port 8080..."
	sed 's/MedusaServAuth server(80)/MedusaServAuth server(8080)/' $(SOURCE) > test_server.cpp
	$(CXX) $(CXXFLAGS) -o test_server test_server.cpp
	./test_server &
	@sleep 2
	@echo "Testing login flow..."
	curl -X POST -d "username=test&password=test" http://localhost:8080/login
	@echo "✅ Test complete!"
	pkill -f test_server || true
	rm -f test_server test_server.cpp

help:
	@echo "MedusaServ Authentication Module v0.3.0c"
	@echo "========================================"
	@echo ""
	@echo "Available targets:"
	@echo "  all              - Build the authentication server"
	@echo "  clean            - Remove build artifacts"
	@echo "  install          - Install to system (/usr/local/bin)"
	@echo "  deploy           - Deploy to production server"
	@echo "  start-production - Deploy and start production server"
	@echo "  test             - Run test suite"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Features:"
	@echo "  ✅ IP Whitelisting (secure ranges authorized)"
	@echo "  ✅ Native Lamia Processing"
	@echo "  ✅ Corporate cPanel-style Interface"
	@echo "  ✅ 6 Admin Snippets with search capability"
	@echo "  ✅ 3D Emotions & GIF3D Integration"
	@echo "  ✅ ICEWALL Security System"
	@echo "  ✅ Yorkshire Champion Standards"
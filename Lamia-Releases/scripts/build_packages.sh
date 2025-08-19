#!/bin/bash
# Lamia Package Builder v0.3.0

echo "🔨 Building release packages..."

# Binary package
echo "Building binary package..."
mkdir -p lamia-v0.3.0/bin
mkdir -p lamia-v0.3.0/lib
mkdir -p lamia-v0.3.0/include

# Copy libraries
cp lib/*.so lamia-v0.3.0/lib/ 2>/dev/null || true
cp Lamia-Libs/lib/*.so lamia-v0.3.0/lib/ 2>/dev/null || true
cp manufacturing_bridges/*.so lamia-v0.3.0/lib/ 2>/dev/null || true

# Copy headers
cp Lamia-Libs/include/*.hpp lamia-v0.3.0/include/ 2>/dev/null || true
cp manufacturing_bridges/*.hpp lamia-v0.3.0/include/ 2>/dev/null || true

# Create tarball
tar -czf lamia-v0.3.0-linux-x86_64.tar.gz lamia-v0.3.0/

# Source package
echo "Building source package..."
tar --exclude='.git' --exclude='*.o' --exclude='*.so' \
    -czf lamia-v0.3.0-source.tar.gz \
    src/ lib/ Lamia-Libs/ manufacturing_bridges/ Lamia-Docs/ \
    Makefile README.md LICENSE

echo "✅ Packages built successfully!"
ls -la *.tar.gz
